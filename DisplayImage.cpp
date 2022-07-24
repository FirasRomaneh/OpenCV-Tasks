//Uncomment the following line if you are compiling this code in Visual Studio
//#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
    // Read the image file
    Mat image = imread("image.png");
    // Check for failure
    cout << image.size() << endl;
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    cout << cv::mean(image) << endl;

    // int w  = 60;
    std::string txt = "hi";
    cv::putText(image,txt,cv::Point(50,50),cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(0,255,255),2,false);
    // cv::ellipse( image,
    //    Point( w/2, w/2 ),
    //    Size( w/4, w/16 ),
    //    90,
    //    0,
    //    360,
    //    Scalar( 255, 0, 0 ),
    //    1,
    //    8 );
    
    String windowName = "The Image"; //Name of the window
    namedWindow(windowName); // Create a window
    imshow(windowName, image); // Show our image inside the created window.
    waitKey(0); // Wait for any keystroke in the window
    destroyWindow(windowName); //destroy the created window
    return 0;
}