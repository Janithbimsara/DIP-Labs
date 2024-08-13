/*----------------mean image filter----------------------*/

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

	Mat img, gr, cp;
	img = imread(argv[1], IMREAD_COLOR); // Load the image file as an 8-bit color image.
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	int w = img.cols;
	int h = img.rows;
	int t = img.channels();
	int s = img.step;
	double t1 = 0.0;

	cvtColor(img, gr, COLOR_BGR2GRAY); // Convert the image to grayscale.
	cp = gr.clone();

	// Apply the 3x3 mean filter to the converted image.
	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++) {

			for (int p = i - 1; p <= i + 1; p++) {
				for (int q = j - 1; q <= j + 1; q++) {
					t1 = t1 + (double)(gr.at<uchar>(p, q));
				}
			}
			cp.at<uchar>(i, j) = (uchar)(cvRound(t1 / 9)); /*Calculate the average value of the pixels in the window and set mean image values to average.*/
			t1 = 0.0;
		}
	}

	cout << "Width and Height :" << w << ", " << h << endl;
	cout << "Type :" << t << endl;

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("Mean_Image", WINDOW_AUTOSIZE);
	imshow("image", gr);
	imshow("Mean_Image", cp);
	imwrite("mean_image.jpg", cp);//write image to device
	waitKey(0);
	img.release();
	gr.release();
	cp.release();
	return 0;
}
