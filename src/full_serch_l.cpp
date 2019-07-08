#include "full_serch_l.h"

void fullserch_L(cv::Mat src, cv::Mat dst, F_Property prop) {
	//変数の初期化
	int nbr = prop.nbr;
	int in_cyc = prop.cyc;

	int in_x = src.cols;
	int in_y = src.rows;

	int out_x = dst.cols;
	int out_y = dst.rows;

	//入力テクスチャの探索範囲
	int in_x_min, in_x_max;
	int in_y_min, in_y_max;

	//環状でない
	if (in_cyc == 0) { // 環状でない
		in_x_min = nbr;
		in_x_max = in_x - nbr;
		in_y_min = nbr;
		in_y_max = in_y;
	}
	else {              // 環状である
		in_x_min = 0;
		in_x_max = in_x;
		in_y_min = 0;
		in_y_max = in_y;
	}

	/*=====================================

			出力テクスチャの合成

	======================================*/

	// 近隣画素群中の画素数
	int pxn = ((2 * nbr + 1) * (2 * nbr + 1)) / 2;

	// 最大 SSD (sum of squared differences) 値
	int ssd_max = 3 * 255 * 255 * pxn;

	// 出力テクスチャの画素のループ
	for (int oy = 0; oy < out_y; oy++) {
		for (int ox = 0; ox < out_x; ox++) {

			// 最小 SSD 値の初期化
			int ssd_min = ssd_max;

			// 入力テクスチャの選択画素の初期化
			int ix_s = -1;
			int iy_s = -1;

			// 入力テクスチャ上の探索
			for (int iy = in_y_min; iy < in_y_max; iy++) {
				for (int ix = in_x_min; ix < in_x_max; ix++) {

					// 近隣画素群の SSD 値の計算
					int s;
					int ssd = 0;
					for (int ny = (-nbr); ny <= 0; ny++) {
						for (int nx = (-nbr); nx <= nbr; nx++) {
							// 近隣画素群の中心に来たら計算終了
							if ((ny == 0) && (nx == 0))break;

							// 計算
							for (int c = 0; c < 3; c++) {
								s = dst.at <cv::Vec3b>((oy + ny + out_y) % out_y, (ox + nx + out_x) % out_x)[c] - src.at<cv::Vec3b>((iy + ny + in_y) % in_y, (ix + nx + in_x) % in_x)[c];
								ssd += (s * s);
							}
						}
					}

					// 最小 SSD 値と入力テクスチャの選択画素の更新
					if (ssd_min > ssd) {
						ssd_min = ssd;
						ix_s = ix;
						iy_s = iy;
					}

				} // ix
			} // iy

			// 出力テクスチャの画素色
			if (ssd_min == ssd_max) {  // 入力テクスチャの画素が選択されていない
				for (int c = 0; c < 3; c++) {
					dst.at<cv::Vec3b>(oy, ox)[c] = 0;
				}
			}
			else {                      // 入力テクスチャの画素が選択されている
				for (int c = 0; c < 3; c++) {
					dst.at<cv::Vec3b>(oy, ox)[c] = src.at<cv::Vec3b>(iy_s, ix_s)[c];
				}
			}

		} // ox
	} // oy
	
}
