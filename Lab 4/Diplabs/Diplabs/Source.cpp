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

	Mat img, gr, contst;
	img = imread(argv[1], IMREAD_UNCHANGED);
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	int w = img.cols;
	int h = img.rows;
	int t = img.channels();
	int s = img.step;
	int t1 = 0;

	cvtColor(img, gr, COLOR_BGR2GRAY);
	contst = gr.clone(); //Copy of the converted gray image
	int hist[256];
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t1 = gr.at<uchar>(i, j);
			hist[t1] = hist[t1] + 1;
		}
	}
	int max = 0;
	for (int i = 0; i < 256; i++) {
		cout << "Gray Level-" << i << " = " << hist[i] << endl;
		if (max < hist[i])
			max = hist[i];
	}
	Mat him(601, 520, CV_8UC1, Scalar(255));
	int his[256];
	double maxd = max;
	for (int i = 0; i <= 255; i++) {
		his[i] = cvRound(double(hist[i] / maxd) * 600);
		Point pt1 = Point(2 * i, 600 - his[i]);
		Point pt2 = Point(2 * i, 600);
		line(him, pt1, pt2, Scalar(0), 1, 8, 0);
	}


	cout << "Width and Height :" << w << ", " << h << endl;
	cout << "Type :" << t << endl;

	//creating constrast stretched image
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) {
			int x = gr.at<uchar>(i, j);
			if (x<105)
			{
				contst.at<uchar>(i, j) = (uchar)(cvRound((double)(5 / 105) * (double)(x)));
			}
			else if (x<245) {
				contst.at<uchar>(i, j) = (uchar)(cvRound((double)(245 / 140) * ((double)(x)-105))+5);
			}
			else if (x < 255) {
				contst.at<uchar>(i, j) = (uchar)(cvRound((double)(5 / 10) * ((double)(x)-245)) + 250);
			}
		}
	}

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("Histogram", WINDOW_AUTOSIZE);
	namedWindow("High_Contrast", WINDOW_AUTOSIZE);
	imshow("image", gr);
	imshow("Histogram", him);
	imshow("High_Contrast", contst);
	waitKey(0);
	img.release();
	gr.release();
	him.release();
	contst.release();
	return 0;
}