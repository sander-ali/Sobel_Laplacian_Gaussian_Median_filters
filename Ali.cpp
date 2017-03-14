// CV_homeworks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

//// properties, c/c++ C:\opencv\build\include
//// properties, linker general additional directories C:\opencv\build\x64\vc14\lib
//// properties, linker, input, additional dependencies, opencv_world320.lib (release) opencv_world320d.lib(debug)
//// copy opencv_world320.dll file from opencv folder to release exe file
//// copy opencv_world320d.dll file from opencv folder to debug exe file

//Global Variables

//sorting the window using insertionsort function
void insertionSort(int window[])
{
	int temp, i, j;
	for (i = 0; i < 9; i++) {
		temp = window[i];
		for (j = i - 1; j >= 0 && temp < window[j]; j--) {
			window[j + 1] = window[j];
		}
		window[j + 1] = temp;
	}
}
int main()
{
	//Defining the variables for images
	cv::Mat img;
	cv::Mat img1;
	cv::Mat img2;
	cv::Mat img3;
	cv::Mat img4;
	cv::Mat img5;
	float sum1;
	float sum2;
	//Reading the image for edge detection
	img = cv::imread("C:/Users/PC/Desktop/Lenna.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//Printing the statistics of the image
	cout << "The size of the image is :" << endl;
	cout << "Width :" << img.size().width << endl;
	cout << "Height :" << img.size().height << endl;
	cout << "Channels :" << img.channels() << endl;
	cout << "Image Type :" << img.type() << endl;
	cout << "Pixel Intensity values at (10,10) :" << img.at<Vec3b>(10, 10) << endl;

	//Reading the image for noisy image
	img3 = cv::imread("C:/Users/PC/Desktop/Lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//Printing the statistics of the image
	cout << "The size of the noisy image is :" << endl;
	cout << "Width of the noisy image is :" << img3.size().width << endl;
	cout << "Height of the noisy image is :" << img3.size().height << endl;
	cout << "Channels of the noisy image are :" << img3.channels() << endl;
	cout << "Image Type of the noisy image is :" << img3.type() << endl;
	cout << "Pixel Intensity values of the noisy image at (10,10) :" << img3.at<Vec3b>(10, 10) << endl;

	//showing the original image
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", img);

	//showing the Noisy image
	namedWindow("Noisy Image", CV_WINDOW_AUTOSIZE);
	imshow("Noisy Image", img3);

	//defining the 3 kernels i.e. Sobel horizontal and sobel vertical filters
	float kernel1[3][3] = {
						{ -1.0, 0.0, 1.0 },
						{ -2.0, 0.0, 2.0 },
						{ -1.0, 0.0, 1.0 }
					};
	float kernel2[3][3] = {
		{ 1.0, 2.0, 1.0 },
		{ 0.0, 0.0, 0.0 },
		{ -1.0, -2.0, 1.0 }
	};
	//Defining Laplacian filter
	float kernel3[3][3] = {
		{-1.0, -1.0, -1.0},
		{-1.0, 8.0, -1.0},
		{-1.0, -1.0, -1.0}
	};
	//defining the kernel for Gaussian Filter
	float kernel4[3][3] = {
		{ 0.01, 0.08, 0.01 },
		{ 0.08, 0.64, 0.08 },
		{ 0.01, 0.08, 0.01 }
	};
	//Cloning the image
	img1 = img.clone();
	img2 = img.clone();
	img4 = img3.clone();
	//Assigning dummy pixels to the cloned image
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			img1.at<uchar>(y, x) = 0.0;
	//Assigning dummy pixels to the cloned image
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			img2.at<uchar>(y, x) = 0.0;
	//Assigning dummy pixels to the cloned image
	for (int y = 0; y < img3.rows; y++)
		for (int x = 0; x < img3.cols; x++)
			img4.at<uchar>(y, x) = 0.0;
	//Using sliding window and convolution technique to apply the edge detection filters
	for (int y = 1; y < img.rows - 1; y++) {
	for (int x = 1; x < img.cols - 1; x++) {
		short x_weight = 0.0;
		short y_weight = 0.0;
		sum1 = 0.0;
	for (short i = -1; i <= 1; i++) {
		for (short j = -1; j <= 1; j++) {
			x_weight += kernel1[i+1][j+1] * img.at<uchar>(y, x);
			y_weight += kernel2[i+1][j+1] * img.at<uchar>(y, x);
			sum1 += kernel3[i + 1][j + 1] * img.at<uchar>(y, x);
			//cout << sum1 << "-" << endl;
			sum1 = abs(sum1);
		}
 	}
	//Normalizing the pixel values
	short val = abs(x_weight) + abs(y_weight);
	if (val > 180)
		val = 255;
	else if (val <= 180)
		val = 0;
	img1.at<uchar>(y, x) = (255 - (unsigned char)(val));
	if (sum1 > 200)
		sum1 = 255;
	else if (sum1 <= 50)
		sum1 = 0;
	img2.at<uchar>(y, x) = (255 - (unsigned char)(sum1));
		}
	}
	// Using sliding window to apply Gaussian Filter
	for (int y = 1; y < img3.rows - 1; y++) {
		for (int x = 1; x < img3.cols - 1; x++) {
			sum2 = 0.0;
			for (short i = -1; i <= 1; i++) {
				for (short j = -1; j <= 1; j++) {
					sum2 += kernel4[i + 1][j + 1] * img3.at<uchar>(y, x);
				}
			}
			img4.at<uchar>(y, x) = sum2;
		}
	}
//creating a sliding window of size 9 for median filter
	int window[9];
	img5 = img3.clone();
	
	for (int y = 0; y < img3.rows; y++)
		for (int x = 0; x < img3.cols; x++)
			img5.at<uchar>(y, x) = 0.0;
	//Picking up window element for median filtering
	for (int y = 1; y < img3.rows-1; y++) {
		for (int x = 1; x < img3.cols-1; x++) {
			window[0] = img3.at<uchar>(y - 1, x - 1);
			window[1] = img3.at<uchar>(y, x - 1);
			window[2] = img3.at<uchar>(y + 1, x - 1);
			window[3] = img3.at<uchar>(y - 1, x);
			window[4] = img3.at<uchar>(y, x);
			window[5] = img3.at<uchar>(y + 1, x);
			window[6] = img3.at<uchar>(y - 1, x + 1);
			window[7] = img3.at<uchar>(y, x + 1);
			window[8] = img3.at<uchar>(y + 1, x + 1);
			// sort the window to find median
			insertionSort(window);
			// assign the median to cenetered element of the matrix
			img5.at<uchar>(y, x) = window[4];
		}
	}
	

//Visualizing the images
namedWindow("Sobel Edge Filter", CV_WINDOW_AUTOSIZE);
imshow("Sobel Edge Filter", img1);

namedWindow("Laplacian Edge Filter", CV_WINDOW_AUTOSIZE);
imshow("Laplacian Edge Filter", img2);

namedWindow("Gaussian Filter", CV_WINDOW_AUTOSIZE);
imshow("Gaussian Filter", img4);

namedWindow("Median Filter", CV_WINDOW_AUTOSIZE);
imshow("Median Filter", img5);

	cv::waitKey();
	return 0;
}