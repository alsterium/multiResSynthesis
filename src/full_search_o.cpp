#include "full_search_o.h"

std::pair<cv::Vec3b, int> full_search_o_select(cv::Mat ref_src, cv::Mat ref_dst, cv::Vec2i coord, F_Property prop)
{
	int nbr = prop.nbr;
	int src_cyc = prop.cyc;
	
	int src_x = ref_src.cols;
	int src_y = ref_src.rows;

	int dst_x = ref_dst.cols;
	int dst_y = ref_dst.rows;

	//���̓e�N�X�`���̒T���͈�
	int src_x_min, src_x_max;
	int src_y_min, src_y_max;

	//��łȂ�
	if (src_cyc == 0) {
		src_x_min = nbr;
		src_x_max = src_x - nbr;
		src_y_min = nbr;
		src_y_max = src_y - nbr;
	}
	else 
	{
		src_x_min = 0;
		src_x_max = src_x;
		src_y_min = 0;
		src_y_max = src_y;
	}

	// �ߗ׉�f���̉�f��
	int pxn = ((2 * nbr + 1) * (2 * nbr + 1)) / 2;
	
	// �ő�SSD�l
	int ssd_max = 3 * 255 * 255 * pxn;

	// �ŏ�SSD�l�̏�����
	int ssd_min = ssd_max;

	// ���̓e�N�X�`���̑I����f�̏�����
	int d_x_s = -1;
	int d_y_s = -1;

	// ���̓e�N�X�`����̒T��
	for (int s_y = src_y_min; s_y < src_y_max; s_y++) {
		for (int s_x = src_x_min; s_x < src_x_max; s_x++) {
			// �ߗ׉�f�Q��SSD�l�̌v�Z
			int s;
			int ssd = 0;

			for (int ny = (-nbr); ny <= nbr; ny++) {
				for (int nx = (-nbr); nx <= nbr; nx++) {
					// �v�Z
					for (int c = 0; c < 3; c++) {
						s = ref_dst.at<cv::Vec3b>((coord.val[1] + ny + dst_y) % dst_y, (coord.val[0] + nx + dst_x) % dst_x)[c] - ref_src.at<cv::Vec3b>((s_y + ny + src_y) % src_y,(s_x + ny + src_x)%src_x)[c];
						ssd += (s * s);
					}
				}
			}
			// �ŏ�SSD�l�Ɠ��̓e�N�X�`���̑I����f�̍X�V
			if (ssd_min > ssd) {
				ssd_min = ssd;
				d_x_s = s_x;
				d_y_s = s_y;
			}

		}//s_x
	}//s_y

	// �o�̓e�N�X�`���̉�f�F
	if (ssd_min == ssd_max) {//���̓e�N�X�`���̉�f���I������Ă��Ȃ�
		return {cv::Vec3b(0, 0, 0), ssd_min};
	}
	else {//���̓e�N�X�`���̉�f���I������Ă���
		return {
			cv::Vec3b(ref_src.at<cv::Vec3b>(d_y_s, d_x_s)[0], ref_src.at<cv::Vec3b>(d_y_s, d_x_s)[1], ref_src.at<cv::Vec3b>(d_y_s, d_x_s)[2]),
			ssd_min
		};
	}
}

std::pair<cv::Vec3b, int> full_search_l_select(cv::Mat ref_src, cv::Mat ref_dst, cv::Vec2i coord, F_Property prop)
{
	int nbr = prop.nbr;
	int src_cyc = prop.cyc;

	int src_x = ref_src.cols;
	int src_y = ref_src.rows;

	int dst_x = ref_dst.cols;
	int dst_y = ref_dst.rows;

	//���̓e�N�X�`���̒T���͈�
	int src_x_min, src_x_max;
	int src_y_min, src_y_max;

	//��łȂ�
	if (src_cyc == 0) {
		src_x_min = nbr;
		src_x_max = src_x - nbr;
		src_y_min = nbr;
		src_y_max = src_y;
	}
	else
	{
		src_x_min = 0;
		src_x_max = src_x;
		src_y_min = 0;
		src_y_max = src_y;
	}

	// �ߗ׉�f���̉�f��
	int pxn = ((2 * nbr + 1) * (2 * nbr + 1)) / 2;

	// �ő�SSD�l
	int ssd_max = 3 * 255 * 255 * pxn;

	// �ŏ�SSD�l�̏�����
	int ssd_min = ssd_max;

	// ���̓e�N�X�`���̑I����f�̏�����
	int d_x_s = -1;
	int d_y_s = -1;

	// ���̓e�N�X�`����̒T��
	for (int s_y = src_y_min; s_y < src_y_max; s_y++) {
		for (int s_x = src_x_min; s_x < src_x_max; s_x++) {
			// �ߗ׉�f�Q��SSD�l�̌v�Z
			int s;
			int ssd = 0;

			for (int ny = (-nbr); ny <= 0; ny++) {
				for (int nx = (-nbr); nx <= nbr; nx++) {
					if ((ny == 0) && (nx == 0))break;
					// �v�Z
					for (int c = 0; c < 3; c++) {
						s = ref_dst.at<cv::Vec3b>((coord.val[1] + ny + dst_y) % dst_y, (coord.val[0] + nx + dst_x) % dst_x)[c] - ref_src.at<cv::Vec3b>((s_y + ny + src_y) % src_y, (s_x + ny + src_x) % src_x)[c];
						ssd += (s * s);
					}
				}
			}
			// �ŏ�SSD�l�Ɠ��̓e�N�X�`���̑I����f�̍X�V
			if (ssd_min > ssd) {
				ssd_min = ssd;
				d_x_s = s_x;
				d_y_s = s_y;
			}

		}//s_x
	}//s_y

	// �o�̓e�N�X�`���̉�f�F
	if (ssd_min == ssd_max) {//���̓e�N�X�`���̉�f���I������Ă��Ȃ�
		return { cv::Vec3b(0, 0, 0), ssd_max };
	}
	else {//���̓e�N�X�`���̉�f���I������Ă���
		return {
			cv::Vec3b(ref_src.at<cv::Vec3b>(d_y_s, d_x_s)[0], ref_src.at<cv::Vec3b>(d_y_s, d_x_s)[1], ref_src.at<cv::Vec3b>(d_y_s, d_x_s)[2]),
			ssd_min
		};
	}
}

void synthesis_multi(std::vector<cv::Mat> src_image_vector, std::vector<cv::Mat> dst_image_vector, F_Property prop)
{
	// �Œ�𑜓x�̉摜����
	std::cout << "--->lowest resolution image synthesis is running...\n";

	for (int d_y = 0; d_y < dst_image_vector[dst_image_vector.size() - 1].rows; d_y++) {
		for (int d_x = 0; d_x < dst_image_vector[dst_image_vector.size() - 1].cols; d_x++) {
			auto [color, ssd_min] = full_search_l_select(src_image_vector[(int)(src_image_vector.size() - 1)], dst_image_vector[(int)(dst_image_vector.size() - 1)], cv::Vec2i(d_x, d_y), prop);
			dst_image_vector[dst_image_vector.size() - 1].at<cv::Vec3b>(d_y, d_x) = color;
		}
	}

	std::cout << "-->Recursive image synthesis is running...\n";

	for (int i = dst_image_vector.size() - 2; i >= 0; i--) {

		int dst_x = dst_image_vector[i].cols;
		int dst_y = dst_image_vector[i].rows;

		//�o�̓e�N�X�`���̃��[�v
		for (int d_y = 0; d_y < dst_y; d_y++) {
			for (int d_x = 0; d_x < dst_x; d_x++) {
				auto [o_color, o_ssd_min] = full_search_o_select(src_image_vector[(i + 1)], dst_image_vector[(i + 1)], cv::Vec2i((d_x / 2), (d_y / 2)), prop);
				auto [l_color, l_ssd_min] = full_search_l_select(src_image_vector[i], dst_image_vector[i], cv::Vec2i(d_x, d_y), prop);
				if (o_ssd_min > l_ssd_min)
					dst_image_vector[i].at<cv::Vec3b>(d_y, d_x) = l_color;
				else
					dst_image_vector[i].at<cv::Vec3b>(d_y, d_x) = o_color;
				//std::cout << "end in ( " << d_y << "," << d_x << " )...\n";
			}
		}
	}
}
