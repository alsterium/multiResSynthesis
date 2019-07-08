#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "property.h"

//del
//cv::Vec2b convert_coord(cv::Vec2b coord);


std::pair<cv::Vec3b, int> full_search_o_select(cv::Mat ref_src, cv::Mat ref_dst, cv::Vec2i coord, F_Property prop);
std::pair<cv::Vec3b, int> full_search_l_select(cv::Mat ref_src, cv::Mat ref_dst, cv::Vec2i coord, F_Property prop);

void synthesis_multi(std::vector<cv::Mat> src_image_vector, std::vector<cv::Mat> dst_image_vector, F_Property prop);