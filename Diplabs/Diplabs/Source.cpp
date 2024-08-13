#include "cv.h"
#include "highgui.h"

int main(int argc, char* argv[]) {
	IplImage* img;
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!img)
	{
		printf("Could not load image");
		return -1;
	}

	int width = img->width;
	int height = img->height;
	int wstep = img->widthStep;
	int chnels = img->nChannels;

	// Print image properties
	printf("Height: %d\n", height);
	printf("Width: %d\n", width);
	printf("Width Step: %d\n", wstep);
	printf("Number of Channels: %d\n", chnels);

	uchar* data = (uchar*)img->imageData;

	printf("1st pixel Blue color level: %d\n", data[0]);
	printf("1st pixel Green color level: %d\n", data[1]);
	printf("1st pixel Red color level: %d\n", data[2]);

	//Convert 100*100 pixels to black color
	/*int i, j = 0;

	for ( i = 0; i < 100; i++)
	{
		for (j = 0; j < 100; j++) 
		{
			data[i * wstep + j * 3] = 0;
			data[i * wstep + j * 3 + 1] = 0;
			data[i * wstep + j * 3 + 2] = 0;
		}
	}*/

	//Gray Scale Conversion
	IplImage* gray = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* dataGray = (uchar*)gray->imageData;
	int wsGray = gray->widthStep;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dataGray[i * wsGray + j * 1] = 0.1140 * data[i * wstep + j * 3] + 0.5870 * data[i * wstep + j * 3 + 1] + 0.2989 * data[i * wstep + j * 3 + 2];
		}
	}

	cvNamedWindow("Image");
	cvShowImage("Image", img);
	cvNamedWindow("Gray");
	cvShowImage("Gray", gray);
	cvWaitKey(0);
	cvDestroyWindow("Image");
	cvDestroyWindow("Bnary");
	cvReleaseImage(&img);
	cvReleaseImage(&gray);
	return 0;
}