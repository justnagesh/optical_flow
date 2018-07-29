#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>



using namespace std;
using namespace cv;

void drawOptFlowMap ( const Mat& flow, Mat& cflowmap, int step, const Scalar& color );

int main()
{

    Mat prev_im,curr_im,flow;
    
    namedWindow("opt_flow",1);
    VideoCapture capture ( 0 );
    if ( !capture.isOpened() ) {
        throw "cam not opened";
    }
    for ( ;; ) {
        capture >> curr_im;
        cvtColor ( curr_im,curr_im,CV_BGR2GRAY );

    
        if ( prev_im.data ) {
            calcOpticalFlowFarneback ( prev_im,curr_im,flow,0.4, 1, 12, 2, 8, 1.2, 0);
            Mat cflow;
            cvtColor ( prev_im, cflow, CV_GRAY2BGR );
            drawOptFlowMap ( flow, cflow, 10, CV_RGB ( 0, 255, 0 ) ); // visualize  
            imshow ( "opt_flow", cflow );
            prev_im=curr_im;
            waitKey ( 1 );

        }
        prev_im=curr_im;

    }
    return 0;
}


void drawOptFlowMap ( const Mat& flow, Mat& cflowmap, int step, const Scalar&
                      color )
{
    for ( int y = 0; y < cflowmap.rows; y += step )
        for ( int x = 0; x < cflowmap.cols; x += step ) {
            const Point2f& fxy = flow.at< Point2f> ( y, x );
            line ( cflowmap, Point ( x,y ), Point ( cvRound ( x+fxy.x ), cvRound
                                                    ( y+fxy.y ) ),color );
            circle ( cflowmap, Point ( cvRound ( x+fxy.x ), cvRound ( y+fxy.y ) ), 1, color, -1 );
        }
}
