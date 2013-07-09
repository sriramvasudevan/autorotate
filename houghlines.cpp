#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <iostream>

using namespace std;
using namespace cv;

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
        if (angle<0) {
            angle = -angle;
        }
        cout<<angle<<endl;
        
    }

    namedWindow( "Source", 1 );
    imshow("Source", magI);

    namedWindow( "Detected Lines", 1 );
    imshow( "Detected Lines", color_dst );

    waitKey(0);
    return 0;
}
