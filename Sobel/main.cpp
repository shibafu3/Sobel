#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300.lib") 
#endif
// http://opencv.jp/opencv2-x-samples/edge_detection

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(){
	VideoCapture cap(0);


	Mat src_image;
	Mat dest_image;

	while (1){
		cap >> src_image;
		cvtColor(src_image, src_image, CV_RGB2GRAY);


		Sobel(src_image, dest_image, CV_32F, 1, 0);
		convertScaleAbs(dest_image, dest_image);
		threshold(dest_image, dest_image, 60, 255, THRESH_BINARY);
		imshow("image", dest_image);
		waitKey(1);
	}
	return 0;
}
