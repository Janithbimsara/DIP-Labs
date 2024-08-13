#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cout << "Enter Project.exe ImageFileName Threshold\n";
		return -1;
	}

	Mat img, gr;
	img = imread(argv[1], IMREAD_COLOR);
	int T = atoi(argv[2]);

	if (img.empty()) {
		cout << "Could not open or find the image.\n";
		return -1;
	}

	int h = img.rows;
	int w = img.cols;

	Mat output = Mat::zeros(h, w, CV_8UC1); // Initialize the output as a single-channel image

	// Iterate through each channel (B, G, R)
	for (int c = 0; c < img.channels(); ++c) {
		Mat channel;
		extractChannel(img, channel, c); // Extract the current color channel
		Mat channelOutput = channel.clone();

		for (int i = 0; i < h - 1; i++) {
			for (int j = 0; j < w - 1; j++) {
				int Gx = channel.at<uchar>(i, j) - channel.at<uchar>(i, j + 1);
				int Gy = channel.at<uchar>(i, j) - channel.at<uchar>(i + 1, j);

				int G = abs(Gx) + abs(Gy);

				if (G >= T) {
					channelOutput.at<uchar>(i, j) = 255;
				}
				else {
					channelOutput.at<uchar>(i, j) = 0;
				}
			}
		}

		// Combine the results for each channel
		output |= channelOutput;
	}

	namedWindow("Color Image");
	imshow("Color Image", img);

	namedWindow("Color Edge Detection");
	imshow("Color Edge Detection", output);

	waitKey(0);
	return 0;
}
