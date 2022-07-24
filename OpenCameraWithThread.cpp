// Uncomment the following line if you are compiling this code in Visual Studio

//#include "stdafx.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <condition_variable>

// #include<opencv2/highgui/highgui.hpp>
// #include<opencv2/imgproc/imgproc.hpp>

static bool work = true;
static bool read = false;
std::mutex Frame_mutex;
std::condition_variable cond;
std::mutex Frame_mutex1;


void Producer(std::shared_ptr<cv::Mat> ptr1){
    cv::VideoCapture cap(0);
    int index = 1;
    // if not success, exit program
    if (cap.isOpened() == false){
        std::cout << "Cannot open the video camera" << std::endl;
    } else {
        while (work){
            std::unique_lock<std::mutex> lock(Frame_mutex);
            bool reading = cap.read(*ptr1); // read a new frame from video   
            cv::putText(*ptr1,std::to_string(index),cv::Point(50,50),cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(0,255,255),2,false);
            if(reading){
                index++;
                read = true;
            }
            cond.notify_one();
            cond.wait(lock, []{return read==false;});
        }                           
    }
}

void Consumer(std::shared_ptr<cv::Mat> ptr1){
    std::string window_name = "Firas Romaneh";
    cv::namedWindow(window_name); // create a window called "Firas Romaneh"
    while (work){
        std::unique_lock<std::mutex> lock(Frame_mutex);  
        cond.wait(lock, []{return read;});   
        // Frame_mutex1.lock();
        cv::imshow(window_name, *ptr1);
        cv::waitKey(10);
        // Frame_mutex.unlock(); 
        read = false;
        lock.unlock();
        cond.notify_one();
    }                       
}

int main(int argc, char *argv[]){
    cv::Mat frame;
    std::shared_ptr<cv::Mat> ptr1 = std::make_shared<cv::Mat>(frame);
    // Frame_mutex1.lock();
    std::thread ProducerThread(Producer, ptr1);
    
    std::thread ConsumerThread(Consumer, ptr1);
    int read1 = 0;
    while (work){
        std::cin >> read1;
        if (read1 == 5){
            std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
            work = false;
            Frame_mutex.unlock();   
        }  
    }
    ProducerThread.join();
    ConsumerThread.join();
    return 0;
}