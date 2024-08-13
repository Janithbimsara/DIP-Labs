#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 3)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay threshold" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_COLOR); // Read the file
	int T = atoi(argv[2]);

    if(! image.data ) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }
	Mat gr;

	cvtColor(image, gr, CV_BGR2GRAY, 0); //Convert the colour image into Gray

	int h = gr.rows;
	int w = gr.cols;
	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;
	cout << "Threshhol: " << T << endl;

	Mat med = gr.clone();     //Copy of image for the output
	int Gx = 0;
	int Gy = 0;
	int G = 0;

	for (int i = 0; i < h-1; i++) {       // take difference
		for (int j = 0; j < w-1; j++) {
			Gx = gr.at<uchar>(i, j) - gr.at<uchar>(i, j + 1);
			Gy = gr.at<uchar>(i, j) - gr.at<uchar>(i+1, j );
			G = abs(Gx) + abs(Gy);
			if(G>=T)
			med.at<uchar>(i, j) = 0;
			else
			med.at<uchar>(i, j) = 255;
		}
	}

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", med ); // Show our image inside it.
	namedWindow("Display Gray", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display Gray", gr); // Show our image inside it.
	imwrite("different_op_image.jpg", med); // write the image to device.
	
    waitKey(0); // Wait for a keystroke in the window

	image.release();
	gr.release();
	med.release();

    return 0;
}
