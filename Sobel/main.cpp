// ����
// �摜��p��
// �����摜���v�Z�B��f�l��float
// ��f�l�̏㉺����8bit�����l�Ɏ��܂�悤�ɕϊ�
// 臒l�����߂�B

// �Q�lURL
// http://opencv.jp/opencv2-x-samples/edge_detection


#ifdef _DEBUG
//Debug���[�h�̏ꍇ
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Release���[�h�̏ꍇ
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

		// �摜�𔒍��ɕϊ�
		cvtColor(src_image, src_image, CV_RGB2GRAY);

		// 1�����������߂�B
		// Sobel(���͉摜�A�o�͉摜�A�f�[�^�T�C�Y�A�������A�c����)
		Sobel(src_image, sobel_image, CV_32F, 1, 0);
		// ��f�l�̏㉺����ϊ�����B
		// convertScaleAbs(���͉摜�A�o�͉摜�Aa, b)
		// �o�͂� |src * a + b| ��8bit�ŏo�͂����B
		convertScaleAbs(sobel_image, sobel_image);
		// 臒l�����߂�
		// threshold(���͉摜�A�o�͉摜�A臒l�A��f�l�̍ő�l�A�^�C�v)
		threshold(sobel_image, sobel_image, 128, 255, THRESH_BINARY);

		// 2�����������߂�B
		// Laplacian(���͉摜�A�o�͉摜�A�f�[�^�T�C�Y�A�������A�c����)
		Laplacian(src_image, laplacian_image, CV_32F, 1, 0);
		convertScaleAbs(laplacian_image, laplacian_image);
		threshold(laplacian_image, laplacian_image, 128, 255, THRESH_BINARY);

		// Canny�A���S���Y��
		// Canny(���͉摜�A�o�͉摜�A�G�b�W�̏������o�A�������瑱���G�b�W�̐ڑ��ɗp������臒l)
		// ����2�̈����́C���l�̑召�ł��̈Ӗ��𔻒f�����̂ŁC������(50, 200) �ł�(200, 50) �ł������ł�
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
