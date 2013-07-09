#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <iostream>

using namespace std;
using namespace cv;

float greaterthan, lesserthan;

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

int main(int argc, char** argv)
{
    const char* filename = argc >=2 ? argv[1] : "lena.jpg";

    Mat magI = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if( magI.empty())
        return -1;

    Mat dst, color_dst;

    Canny( magI, dst, 50, 200, 3 );
    cvtColor( dst, color_dst, CV_GRAY2BGR );

    vector<Vec4i> lines;
    vector<float> angles;
    HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Point a(lines[i][0], lines[i][1]), b(lines[i][2], lines[i][3]);
        line( color_dst, a, b, Scalar(0,0,255), 3, 8 );
        float height = (float)b.y - (float)a.y;
        float base =  (float)b.x - (float)a.x;
        float hyp = sqrt(base*base + height*height);
        float sinval = height/hyp;
        float angle  = asin(sinval)*180/CV_PI;
        angles.push_back(angle);
    }

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

    i=0;
    float sum = 0.0;
    for(vector<float>::iterator it=angles.begin(); it!=angles.end(); ++it) {
        if(!isOutlier(*it)) {
            i++;
            sum += *it;
        }
    }

    float meanangle = sum/(float)i;

    cout<<"Mean = "<<meanangle<<endl;

    Point center = Point( magI.cols/2, magI.rows/2 );

    /// Get the rotation matrix with the specifications above
    Mat rot_mat = getRotationMatrix2D( center, meanangle, 1.0);

    Mat final;
    /// Rotate the warped image
    warpAffine( magI, final, rot_mat, magI.size(), INTER_CUBIC, BORDER_CONSTANT, Scalar(255,255,255));

    /// Show what you got
    imshow( "Source", magI);

    imshow( "Rotated", final);

    Mat image;
    cv::GaussianBlur(final, image, cv::Size(0, 0), 3);
    cv::addWeighted(final, 1.5, image, -0.5, 0, image);

    imshow("Sharp", image);

    waitKey(0);
    return 0;
}

