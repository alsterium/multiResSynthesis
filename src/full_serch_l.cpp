#include "full_serch_l.h"

void fullserch_L(cv::Mat src, cv::Mat dst, F_Property prop) {
	//�ϐ��̏�����
	int nbr = prop.nbr;
	int in_cyc = prop.cyc;

	int in_x = src.cols;
	int in_y = src.rows;

	int out_x = dst.cols;
	int out_y = dst.rows;

	//���̓e�N�X�`���̒T���͈�
	int in_x_min, in_x_max;
	int in_y_min, in_y_max;

	//��łȂ�
	if (in_cyc == 0) { // ��łȂ�
		in_x_min = nbr;
		in_x_max = in_x - nbr;
		in_y_min = nbr;
		in_y_max = in_y;
	}
	else {              // ��ł���
		in_x_min = 0;
		in_x_max = in_x;
		in_y_min = 0;
		in_y_max = in_y;
	}

	/*=====================================

			�o�̓e�N�X�`���̍���

	======================================*/

	// �ߗ׉�f�Q���̉�f��
	int pxn = ((2 * nbr + 1) * (2 * nbr + 1)) / 2;

	// �ő� SSD (sum of squared differences) �l
	int ssd_max = 3 * 255 * 255 * pxn;

	// �o�̓e�N�X�`���̉�f�̃��[�v
	for (int oy = 0; oy < out_y; oy++) {
		for (int ox = 0; ox < out_x; ox++) {

			// �ŏ� SSD �l�̏�����
			int ssd_min = ssd_max;

			// ���̓e�N�X�`���̑I����f�̏�����
			int ix_s = -1;
			int iy_s = -1;

			// ���̓e�N�X�`����̒T��
			for (int iy = in_y_min; iy < in_y_max; iy++) {
				for (int ix = in_x_min; ix < in_x_max; ix++) {

					// �ߗ׉�f�Q�� SSD �l�̌v�Z
					int s;
					int ssd = 0;
					for (int ny = (-nbr); ny <= 0; ny++) {
						for (int nx = (-nbr); nx <= nbr; nx++) {
							// �ߗ׉�f�Q�̒��S�ɗ�����v�Z�I��
							if ((ny == 0) && (nx == 0))break;

							// �v�Z
							for (int c = 0; c < 3; c++) {
								s = dst.at <cv::Vec3b>((oy + ny + out_y) % out_y, (ox + nx + out_x) % out_x)[c] - src.at<cv::Vec3b>((iy + ny + in_y) % in_y, (ix + nx + in_x) % in_x)[c];
								ssd += (s * s);
							}
						}
					}

					// �ŏ� SSD �l�Ɠ��̓e�N�X�`���̑I����f�̍X�V
					if (ssd_min > ssd) {
						ssd_min = ssd;
						ix_s = ix;
						iy_s = iy;
					}

				} // ix
			} // iy

			// �o�̓e�N�X�`���̉�f�F
			if (ssd_min == ssd_max) {  // ���̓e�N�X�`���̉�f���I������Ă��Ȃ�
				for (int c = 0; c < 3; c++) {
					dst.at<cv::Vec3b>(oy, ox)[c] = 0;
				}
			}
			else {                      // ���̓e�N�X�`���̉�f���I������Ă���
				for (int c = 0; c < 3; c++) {
					dst.at<cv::Vec3b>(oy, ox)[c] = src.at<cv::Vec3b>(iy_s, ix_s)[c];
				}
			}

		} // ox
	} // oy
	
}
