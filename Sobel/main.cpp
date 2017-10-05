// 流れ
// 画像を用意
// 微分画像を計算。画素値はfloat
// 画素値の上下限を8bit整数値に収まるように変換
// 閾値を決める。

// 参考URL
// http://opencv.jp/opencv2-x-samples/edge_detection


#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300.lib") 
#endif

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(){
	VideoCapture cap(0);


	Mat src_image;
	Mat sobel_image;
	Mat laplacian_image;
	Mat canny_image;

	while (1){
		cap >> src_image;

		// 画像を白黒に変換
		cvtColor(src_image, src_image, CV_RGB2GRAY);

		// 1次微分を求める。
		// Sobel(入力画像、出力画像、データサイズ、横微分、縦微分)
		Sobel(src_image, sobel_image, CV_32F, 1, 0);
		// 画素値の上下限を変換する。
		// convertScaleAbs(入力画像、出力画像、a, b)
		// 出力は |src * a + b| が8bitで出力される。
		convertScaleAbs(sobel_image, sobel_image);
		// 閾値を決める
		// threshold(入力画像、出力画像、閾値、画素値の最大値、タイプ)
		threshold(sobel_image, sobel_image, 128, 255, THRESH_BINARY);

		// 2次微分を求める。
		// Laplacian(入力画像、出力画像、データサイズ、横微分、縦微分)
		Laplacian(src_image, laplacian_image, CV_32F, 1, 0);
		convertScaleAbs(laplacian_image, laplacian_image);
		threshold(laplacian_image, laplacian_image, 128, 255, THRESH_BINARY);

		// Cannyアルゴリズム
		// Canny(入力画像、出力画像、エッジの初期検出、そこから続くエッジの接続に用いられる閾値)
		// この2つの引数は，数値の大小でその意味を判断されるので，順序は(50, 200) でも(200, 50) でも等価です
		Canny(src_image, canny_image, 50, 200);
		convertScaleAbs(canny_image, canny_image);
		threshold(canny_image, canny_image, 128, 255, THRESH_BINARY);

		imshow("sobel", sobel_image);
		imshow("laplacian", laplacian_image);
		imshow("canny", canny_image);
		waitKey(1);
	}
	return 0;
}
