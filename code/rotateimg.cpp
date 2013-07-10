#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    string filename;
    if (argc>=2) {
        filename = argv[1];
    }
    else {
        cout<<"No image found."<<endl;
        exit(-1);
    }

    Mat magI = imread(filename.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    if( magI.empty()) {
        cout<<"No image found."<<endl;
        exit(-1);
    }

    Point center = Point( magI.cols/2, magI.rows/2 );

    /// Get the rotation matrix with the specifications above
    Mat rot_mat = getRotationMatrix2D( center, 180, 1.0);

    Mat final;
    /// Rotate the warped image
    warpAffine( magI, final, rot_mat, magI.size(), INTER_CUBIC, BORDER_CONSTANT, Scalar(255,255,255));

    Mat image;
    cv::GaussianBlur(final, image, cv::Size(0, 0), 3);
    cv::addWeighted(final, 1.5, image, -0.5, 0, image);
    
    /// Storing and showing the first image.
    imwrite(filename.c_str(), image);

    return 0;
}
