// multi_resolution_processing.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
//#include "pch.h"
#include <vector>
#include <iostream>
#include <atltime.h>
#include <opencv2\opencv.hpp>
#include "property.h"
#include "full_serch_l.h"
#include "full_search_o.h"

using namespace std;

//constexpr int MultiResLevel = 4;
// *square*
//constexpr int DstRes = 200;

int main(int argc, char* argv[]) {
	cout << "---->main()\n";

	if (argc != 5) {
		cout << "usage: [file] [MultiResLevel] [DstRes] [Nbr]";
		exit(-1);
	}

	int MultiResLevel = atoi(argv[2]);
	int DstRes = atoi(argv[3]);
	int Nbr = atoi(argv[4]);
	cv::String filepath = argv[1];

	cv::Mat src_image;
	src_image = cv::imread(filepath);
	vector<cv::Mat> src_img_vector;
	vector<cv::Mat> dst_img_vector;

	//出力先のMattを生成
	//cout << "--->Create dst Mat vector.";
	dst_img_vector.push_back(cv::Mat(cv::Size(DstRes,DstRes),CV_8UC3));
	cv::Mat tmp = dst_img_vector[0];
	//cout << "-->execute pyrDown.";
	for (int i = 1; i < MultiResLevel; i++){
		cv::pyrDown(tmp, tmp);
		dst_img_vector.push_back(tmp);
	}

	//解像度を1/2した画像を生成
	//cout << "-->Generate harf-size image.";
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
		exit(-2);
	}
	

	//出力先の画像をランダムな値で初期化
	//cout << "-->initialize each image.\n";
	for (auto &e : dst_img_vector) { cv::randu(e, cv::Scalar(0, 0, 0), cv::Scalar(256, 256, 256));}

	//各解像度ごとに一つ下のレベルの解像度を参照して画像合成

	F_Property prop(Nbr);
	cout << "--->multi resolution synthesis is begin!!\n";
	//時間計測スタート
	CFileTime cTimeStart, cTimeEnd;
	CFileTimeSpan cTimeSpan;
	cTimeStart = CFileTime::GetTickCount();

	synthesis_multi(src_img_vector, dst_img_vector, prop);

	//時間計測ストップ
	cTimeEnd = CFileTime::GetTickCount();
	cTimeSpan = cTimeEnd - cTimeStart;
	cout << "Processing Time: " << cTimeSpan.GetTimeSpan()/10000000.0<<"[sec]\n";
	//合成結果を表示
	
	cout << "<---end synthesis process.\n";
	/*for (int i = 0; i < src_img_vector.size(); i++) {
		cv::String windowName = "src_image";
		try { 
			cv::imshow(windowName + to_string(i), src_img_vector[i]);
		}
		catch (cv::Exception& e) {
			cerr << e.what() << endl;
		}
	}*/

	CTime time = CTime::GetTickCount();
	cv::String time_s = time.Format("%Y%m%d_%H%M%S");
	for (int i = 0; i < dst_img_vector.size(); i++) {
		cv::String windowName = "result";
		cv::String filename = "[MR-"+to_string(MultiResLevel) + "][DR-"+to_string(DstRes)+"][Nb-"+to_string(Nbr)+"][Dpth-"+to_string(i)+"]_"+time_s+".png";

		try {
			//cv::imshow(windowName + to_string(i), dst_img_vector[i]);
			cv::imwrite("./result/"+filename, dst_img_vector[i]);
			
		}
		catch(cv::Exception& e){
			cerr << e.what() << endl;
			exit(-3);
		}
	}
	cv::FileStorage outYml("./result/result.yml", cv::FileStorage::APPEND);
	outYml << "SynthesisDate" << time_s << "InputFile" << filepath << "MultiResLevel" << MultiResLevel << "DstSize" << DstRes << "Nbr" << Nbr << "ProcessTime" << cTimeSpan.GetTimeSpan() / 10000000.0;

	cout << "<----end main()\n";
	cv::waitKey(0);
}

