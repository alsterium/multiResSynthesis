// multi_resolution_processing.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
//#include "pch.h"
#include <vector>
#include <iostream>
#include <opencv2\opencv.hpp>
#include "property.h"
#include "full_serch_l.h"
#include "full_search_o.h"

using namespace std;

constexpr float scale = 0;

constexpr int MultiResLevel = 4;
// *square*
constexpr int DstRes = 150;

int main() {
	cout << "---->main()\n";
	cout << "";
	cv::Mat src_image;
	src_image = cv::imread("./texture_o_icon.jpg");
	vector<cv::Mat> src_img_vector;
	vector<cv::Mat> dst_img_vector;

	//出力先のMattを生成
	cout << "--->Create dst Mat vector.";
	dst_img_vector.push_back(cv::Mat(cv::Size(DstRes,DstRes),CV_8UC3));
	cv::Mat tmp = dst_img_vector[0];
	cout << "-->execute pyrDown.";
	for (int i = 1; i < MultiResLevel; i++){
		cv::pyrDown(tmp, tmp);
		dst_img_vector.push_back(tmp);
	}

	//解像度を1/2した画像を生成
	cout << "-->Generate harf-size image.";
	src_img_vector.push_back(src_image);
	try {
		tmp = src_image;
		for (int i = 1; i < MultiResLevel; i++) {
			cv::pyrDown(tmp, tmp);
			src_img_vector.push_back(tmp);
		}
	}
	catch(cv::Exception& e){
		cerr << e.what() << endl;
		exit(1);
	}
	

	//出力先の画像をランダムな値で初期化
	cout << "-->initialize each image.\n";
	for (auto &e : dst_img_vector) { cv::randu(e, cv::Scalar(0, 0, 0), cv::Scalar(256, 256, 256));}

	//最低解像度の画像合成
	//cout << "--->lowest resolution image synthesis is running...\n";
	F_Property prop(3);
	//fullserch_L(src_img_vector[(int)(src_img_vector.size() - 1)], dst_img_vector[(int)(dst_img_vector.size() - 1)], prop);

	//各解像度ごとに一つ下のレベルの解像度を参照して画像合成
	cout << "--->multi resolution synthesis is begin!!\n";
	synthesis_multi(src_img_vector, dst_img_vector, prop);

	//合成結果を表示
	
	cout << "<---end synthesis process.\n";
	for (int i = 0; i < src_img_vector.size(); i++) {
		cv::String windowName = "src_image";
		try { 
			cv::imshow(windowName + to_string(i), src_img_vector[i]);
		}
		catch (cv::Exception& e) {
			cerr << e.what() << endl;
		}
	}

	int i = 0;
	for (auto &e : dst_img_vector) {
		cv::String windowName = "result";
		try {
			cv::imshow(windowName + to_string(i), e);
		}
		catch(cv::Exception& e){
			cerr << e.what() << endl;
			exit(1);
		}
		
		i++;
	}

	cout << "<----end main()\n";
	cv::waitKey(0);
}

