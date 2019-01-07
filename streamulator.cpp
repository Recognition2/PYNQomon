/* Streamulator test platform
 * Original by Michiel van der Vlag, adapted by Matti Dreef
 */

#include "app_config.hpp"
#include <hls_stream.h>
#include <hls_opencv.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#define SIM


using namespace cv;

void stream(pixel_stream &src, pixel_stream &dst, u32 mask);

int main ()
{
	// Streams and data
	ap_uint<32> pixeldata[HEIGHT][WIDTH];
	hls::stream<pixel_data> inputStream;
	hls::stream<pixel_data> outputStream;
	pixel_data streamIn;
	pixel_data streamOut;


    VideoCapture cap(0);

    if (!cap.isOpened()){
        return -1;
    }

	for (int i = 0; i < 100; i++) {
        Mat frame;
		cap >> frame;
	    // Read input image
		char buffer[100];
		sprintf(buffer, "/home/admin/temp/src/afbeelding%d.jpg\0", i);
//		cv::Mat frame = cv::imread(buffer);
		Mat sourceImg;

	    // A necessary conversion to obtain the right format...
	    cv::cvtColor(frame, frame, CV_BGR2BGRA);
		resize(frame, sourceImg, Size(WIDTH, HEIGHT));

	    // Write input data
	    for (int rows=0; rows < HEIGHT; rows++)
	        for (int cols=0; cols < WIDTH; cols++)
	        {
	        	streamIn.data = sourceImg.at<int>(rows,cols);
	        	streamIn.user = (rows==0 && cols==0) ? 1 : 0;
	        	streamIn.last = (cols==WIDTH-1) ? 1 : 0;

	        	inputStream << streamIn;
	        }

	    // Call stream processing function
	    while (!inputStream.empty())
			stream(inputStream, outputStream, 1); // Add extra arguments here


	    // Read output data
	    for (int rows=0; rows < HEIGHT; rows++)
	        for (int cols=0; cols < WIDTH; cols++)
	        {
	        	outputStream.read(streamOut);
	        	pixeldata[rows][cols] = streamOut.data;
	        }


	    // Save image by converting data array to matrix
	    // Depth or precision: CV_8UC4: 8 bit unsigned chars x 4 channels = 32 bit per pixel;
	    cv::Mat imgCvOut(cv::Size(WIDTH, HEIGHT), CV_8UC4, pixeldata);
//	    cv::imshow("Ik ben een afbeelding", imgCvOut);
//		imshow("Ik ben een afbeelding", imgCvOut);
		sprintf(buffer, "/tmp/resultaten/afbeelding_%03d.png\0", i);
		imwrite(buffer, imgCvOut);
		printf("Afbeelding %d gehandeld\n", i);
	}

	return 0;
}

