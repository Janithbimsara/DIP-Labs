#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << " Usage: ExeFile ImageToLoadAndDisplay Threshold" << endl;
		return -1;
	}
	Mat image;
	image = imread(argv[1], IMREAD_COLOR);
	int T = atoi(argv[2]);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	int h = image.rows;
	int w = image.cols;
	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;
	Mat gr(h, w, CV_8UC1, Scalar(0));
	cvtColor(image, gr, COLOR_BGR2GRAY);
	Mat med = gr.clone();
	int Gx = 0;
	int Gy = 0;
	int G = 0;
	int sobel_horizontal[3][3] = { {-1,-2,-1}, {0,0,0},{1,2,1} };
	int sobel_vertical[3][3] = { {-1,0,1}, {-2,0,2},{-1,0,1} };
	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++) {
			Gx = 0;
			Gy = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					Gx += sobel_horizontal[x + 1][y + 1] * gr.at<uchar>(i + x, j + y);
					Gy += sobel_vertical[x + 1][y + 1] * gr.at<uchar>(i + x, j + y);
				}
			}
			//Gx = (-1) * gr.at<uchar>(i - 1, j - 1) + (-2) * gr.at<uchar>(i - 1, j) + (-1) * gr.at<uchar>(i - 1, j + 1) + 1 * gr.at<uchar>(i +1, j - 1) + 2 * gr.at<uchar>(i + 1, j) + 1 * gr.at<uchar>(i + 1, j + 1);
			//Gy = (-1) * gr.at<uchar>(i - 1, j - 1) + (-2) * gr.at<uchar>(i, j - 1) + (-1) * gr.at<uchar>(i + 1, j - 1) + 1 * gr.at<uchar>(i -1, j + 1) + 2 * gr.at<uchar>(i, j + 1) + 1 * gr.at<uchar>(i + 1, j + 1);
			G = abs(Gx) + abs(Gy);
			if (G >= T) {
				med.at<uchar>(i, j) = 255;
			}
			else {
				med.at<uchar>(i, j) = 0;
			}
		}
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", med);
	namedWindow("Display Gray", WINDOW_AUTOSIZE);
	imshow("Display Gray", gr);
	waitKey(0);
	image.release();
	gr.release();
	med.release();
	return 0;
}