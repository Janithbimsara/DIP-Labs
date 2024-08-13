/*----------------median image 7x7 filter----------------------*/

#include <stdio.h>
#include <iostream>
#include<opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Enter Project.exe ImgeFileName\n";
		return -1;
	}

	Mat img, gr, med;
	img = imread(argv[1], IMREAD_COLOR); // Load the image file as an 8-bit color image.
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}

	cvtColor(img, gr, COLOR_BGR2GRAY); // Convert the image to grayscale.
	med = gr.clone();

	int h = gr.rows;
	int w = gr.cols;
	
	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;

	int val = 0;
	int ar1[49];

	// Apply the 5x5 median filter to the converted image.
	for (int i = 3; i < h - 3; i++){
		for (int j = 3; j < w - 3; j++){
			int r = 0;
			for (int t1 = -3; t1 <= 3; t1++){
				for (int t2 = -3; t2 <= 3; t2++){
					val = gr.at<uchar>(i + t1, j + t2);
					ar1[r] = val;
					r = r + 1;
				}
			}
			sort(ar1, ar1 + 49);
			med.at<uchar>(i, j) = (uchar)ar1[24]; // Set the median value
		}
	}

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("Median_Image", WINDOW_AUTOSIZE);
	imshow("image", img);
	imshow("Median_Image", med);
	imwrite("median_image.jpg", med);//write image to device
	waitKey(0);
	img.release();
	gr.release();
	med.release();
	return 0;
}
