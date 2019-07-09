#pragma once

#include<opencv2\opencv.hpp>
#include<iostream>
#include<vector>

class F_Property {
public:
	// 近隣画素群（neighbor）の大きさ
	//   nbr >= 1
	int nbr;

	// 近隣画素群の一辺が 2 * nbr + 1 となる
	// 入力テクスチャが環状かどうか
	//   0 : 環状でない
	//   1 : 環状である
	int cyc;

	// 近隣画素群（neighbor）の大きさ
	//   nbr >= 1
	// 近隣画素群の一辺が 2 * nbr + 1 となる
	// 入力テクスチャが環状かどうか
	//   0 : 環状でない
	//   1 : 環状である
	F_Property(int in_nbr, int in_cyc = 0) :nbr(in_nbr), cyc(in_cyc) {};
	F_Property(void) {
		nbr = 3;
		cyc = 0;
	}
};

	        
								
