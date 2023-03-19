/*************************************************************************
>> File Name: DisplayImage.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2023年03月16日 星期四 20时51分35秒

>> 此程序的功能是：
************************************************************************/

#include<opencv2/opencv.hpp>
/* #include "/home/jack/opencv_4_1/usr/local/include/opencv4/opencv2/opencv.hpp" */
#include <stdio.h>


using namespace cv;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 1);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
