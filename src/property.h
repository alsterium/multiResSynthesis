#pragma once

#include<opencv2\opencv.hpp>
#include<iostream>
#include<vector>

class F_Property {
public:
	// �ߗ׉�f�Q�ineighbor�j�̑傫��
	//   nbr >= 1
	int nbr;

	// �ߗ׉�f�Q�̈�ӂ� 2 * nbr + 1 �ƂȂ�
	// ���̓e�N�X�`�����󂩂ǂ���
	//   0 : ��łȂ�
	//   1 : ��ł���
	int cyc;

	// �ߗ׉�f�Q�ineighbor�j�̑傫��
	//   nbr >= 1
	// �ߗ׉�f�Q�̈�ӂ� 2 * nbr + 1 �ƂȂ�
	// ���̓e�N�X�`�����󂩂ǂ���
	//   0 : ��łȂ�
	//   1 : ��ł���
	F_Property(int in_nbr, int in_cyc = 0) :nbr(in_nbr), cyc(in_cyc) {};
	F_Property(void) {
		nbr = 3;
		cyc = 0;
	}
};

	        
								
