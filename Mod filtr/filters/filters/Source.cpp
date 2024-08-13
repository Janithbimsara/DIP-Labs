/*----------------mode image filter----------------------*/

#include <stdio.h>
#include <iostream>
#include<opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

//calculate mode of an array
int calculateMode(int array[], int size)
{
	sort(array, array + size); // Sort the array

	int maxCount = 1;
	int mode = array[0];
	int currentCount = 1;

	for (int i = 1; i < size; i++)
	{
		if (array[i] == array[i - 1])
		{
			currentCount++;
			if (currentCount > maxCount)
			{
				maxCount = currentCount;
				mode = array[i];
			}
		}
		else
		{
			currentCount = 1;
		}
	}
	return mode;
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Enter Project.exe ImgeFileName\n";
		return -1;
	}

	Mat img, gr, med;
	img = imread(argv[1], IMREAD_COLOR); // Load the image file as color image.
	if (img.empty()) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}

	cvtColor(img, gr, COLOR_BGR2GRAY); // Convert the image to grayscale.
	med = gr.clone();

	int h = gr.rows;
	int w = gr.cols;
	int size;

	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;

	cout << "Enter the metrix size (e.g.: 3 for 3x3 metrix):\n";
	cin >> size;

	int val = 0;
	int* ar1 = new int[(size*size)];
	int mode;

	// Apply the mode filter to the converted image.
	for (int i = size/2; i < h - size / 2; i++) {
		for (int j = size / 2; j < w - size / 2; j++) {
			int r = 0;
			for (int t1 = -size / 2; t1 <= size / 2; t1++) {
				for (int t2 = -size / 2; t2 <= size / 2; t2++) {
					val = gr.at<uchar>(i + t1, j + t2);
					ar1[r] = val;
					r = r + 1;
				}
			}
			mode = calculateMode(ar1, (size*size));
			med.at<uchar>(i, j) = (uchar)mode;
		}
	}

	namedWindow("image", WINDOW_NORMAL);
	namedWindow("Mode_Image", WINDOW_AUTOSIZE);
	imshow("image", img);
	imshow("Mode_Image", med);
	imwrite("mode_image.jpg", med);//write image to device
	waitKey(0);
	img.release();
	gr.release();
	med.release();
	return 0;
}

