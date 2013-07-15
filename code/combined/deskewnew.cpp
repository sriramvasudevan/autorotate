#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <iostream>
#include "detectflip.h"

using namespace std;
using namespace cv;

float greaterthan, lesserthan;
string filename;
Mat magI, final;


void autoRotate();
vector<float> calcAngles(vector<Vec4i>);
void removeOutliers(vector<float>&);
float calcMean(vector<float>);
float calcMedian(vector<float>, vector<float>::iterator, vector<float>::iterator);
bool isOutlier(const float&);
string windowname = "Autorotate - Alpha Cloud Labs (press a to autorotate and q to quit)";


int main(int argc, char** argv)
{
    if (argc>=2) {
        filename = argv[1];
    }
    else {
        cout<<"No image found."<<endl;
        exit(-1);
    }

    namedWindow(windowname, CV_WINDOW_NORMAL);

    magI = imread(filename.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    if( magI.empty()) {
        cout<<"No image found."<<endl;
        exit(-1);
    }

    imshow( windowname, magI);
    while (true) {
        int c = waitKey(0);
        if ((char)c=='a') {
            autoRotate();
        }
        if ((char)c=='q') {
            break;
        }
    }

    return 0;
}


bool isOutlier(const float& value) {
    return (value>greaterthan || value<lesserthan);
}


float calcMedian(vector<float> values, vector<float>::iterator begin_it, vector<float>::iterator end_it) {
    int size = (int)distance(begin_it, end_it);
    float median;
    if (size%2) {
        return *(begin_it+(size-1)/2);
    }
    else {
        return ((*(begin_it+size/2-1) + *(begin_it+size/2))/2);
    }
}


float calcMean(vector<float> angles) {
    float sum = 0.0, i = 0.0;
    for(vector<float>::iterator it=angles.begin(); it!=angles.end(); ++it) {
        if(!isOutlier(*it)) {
            i++;
            sum += *it;
        }
    }
    return (sum/i);
}


void removeOutliers(vector<float> &angles) {
    sort(angles.begin(), angles.end());
    int angles_size = (int)distance(angles.begin(), angles.end());
    cout<<angles_size<<endl;
    float fqr, tqr;
    float anglestore[4];
    int i=0;
    if (angles_size%2) {
        fqr = calcMedian(angles, angles.begin(), angles.begin() + (angles_size-1)/2);
        tqr = calcMedian(angles, angles.begin() + (angles_size+1)/2, angles.end());
    }
    else {
        fqr = calcMedian(angles, angles.begin(),  angles.begin() + (angles_size)/2);
        tqr = calcMedian(angles, angles.begin() + (angles_size)/2, angles.end());
    }

    float iqr = tqr - fqr;
    lesserthan = fqr - 0.3*iqr;
    greaterthan = tqr + 0.3*iqr;
    cout<<fqr<<endl;
    cout<<tqr<<endl;
    cout<<"less="<<lesserthan<<endl;
    cout<<"great="<<greaterthan<<endl;
    cout<<"last="<<*(angles.end()-1)<<endl;
}


vector<float> calcAngles(vector<Vec4i> lines) {
    vector<float> angles;
    float height, base, hyp, angle;
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Point a(lines[i][0], lines[i][1]), b(lines[i][2], lines[i][3]);
        height = (float)b.y - (float)a.y;
        base =  (float)b.x - (float)a.x;
        hyp = sqrt(base*base + height*height);
        angle  = asin(height/hyp)*180/CV_PI;
        angles.push_back(angle);
    }
    return angles;
}


void autoRotate() {
    Mat dst;
    Canny( magI, dst, 50, 200, 3 );

    vector<Vec4i> lines;

    //Perform a probabilistic Hough Transform to detect lines
    HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );

    //calculate angles from the lines
    vector<float> angles = calcAngles(lines);

    //remove outliers
    removeOutliers(angles);

    //calculate mean
    float meanangle = calcMean(angles);
    cout<<"Mean = "<<meanangle<<endl;

    //get image centre
    Point center = Point( magI.cols/2, magI.rows/2 );

    /// Get the rotation matrix with the specifications above
    Mat rot_mat = getRotationMatrix2D( center, meanangle, 1.0);

    /// Rotate the image
    warpAffine( magI, final, rot_mat, magI.size(), INTER_CUBIC, BORDER_CONSTANT, Scalar(255,255,255));

    //Sharpen Image
    Mat image;
    //GaussianBlur(final, image, cv::Size(0, 0), 3);
    //addWeighted(final, 1.5, image, -0.5, 0, image);
    image=final;

    //Save the image in a temporary location, to be processed by Leptonica
    string tempname = "tempstore/temp" + filename.substr(filename.find_last_of("."));
    imwrite(tempname.c_str(), image);

    l_float32 conf1;
    PIX *pixs, *pixt1;

    //Open in Leptonica
    if ((pixt1 = pixRead(tempname.c_str())) == NULL) {
        fprintf(stderr, "Unable to open image.\n");
        exit(-1);
    }

    //Top level conversion to 1 bpp
    pixs = pixConvertTo1(pixt1, 130);
    int orientation = isRightsideUp(pixs, &conf1, 0, 10);
    pixDestroy(&pixt1);
    pixDestroy(&pixs);

    if (orientation==-1) {
        //Get rotation matrix with a 180 degree rotation 
        rot_mat = getRotationMatrix2D(center, 180, 1.0);

        /// Rotate the image
        warpAffine(image, final, rot_mat, magI.size(), INTER_CUBIC, BORDER_CONSTANT, Scalar(255,255,255));

        //Sharpen Image
        //GaussianBlur(final, image, cv::Size(0, 0), 3);
        //addWeighted(final, 1.5, image, -0.5, 0, image);
        image=final;
        imwrite(tempname.c_str(), image);
    }
    else if (orientation==0) {
        cerr<<"Image size too small. Please try using an image of higher resolution."<<endl;
        return;
    }

    //Show the autorotated image
    imshow(windowname, image);
}
