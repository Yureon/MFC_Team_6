#include "pch.h"
#include "Board.h"
#include <time.h>
#include <stdlib.h>

void Board::Difficulty(int mode) {
	srand(time(NULL));
	
	if (mode == 1) {
		boxCount = 12;
		boxSize = 35;
		mineCount = rand() % 6 + 5; // �ּ� 5�� �ִ� 10��
		m_flag = mineCount;
	}
	//���1 = Easy
	else if (mode == 2) {
		boxCount = 16;
		boxSize = 28;
		mineCount = rand() % 9 + 8; // �ּ� 8�� �ִ� 16��
		m_flag = mineCount;
	}
	//���2 = Middle
	else if (mode == 3) {
		boxCount = 28;
		boxSize = 16;
		mineCount = rand() % 40 + 40; //�ּ� 40�� �ִ� 79��
		m_flag = mineCount;
	}
	//���3 = Hard
	else if (mode == 4) {
		boxCount = 35;
		boxSize = 12;
		mineCount = rand() % 80 + 70; // �ּ� 70�� �ִ� 159��
		m_flag = mineCount;
	}
	//���4 = Challenge

}

void Board::RandomMine() {
	srand(time(NULL));
	int flag;
	m_flag = 0;

	for (int i = 0; i < boxCount; i++) {
		for (int j = 0; j < boxCount; j++) {
			mine[i][j] = 0;
		}
	} 
	// ������ �迭�� �ϰ������� 0���� �ʱ�ȭ��Ŵ.

	for (int i = 0;; i++) {
		flag = rand();
		
		if (flag == i % boxCount) {
			int x = rand() % boxCount;
			int y = rand()*rand() % boxCount;

			mine[x][y] = -100;
			mineCount--;
			m_flag++;
		}

		if (mineCount == 0) {
			break;
		}
	}
	//������ Ÿ�ֿ̹� ������ ����, ���ο��� ���ڸ� �����Ѵ�.
}

void Board::Scanbox() {

	for (int i = 1; i < boxCount; i++) {
		for (int j = 1; j < boxCount; j++) {
			if (mine[i][j] < 0) {
				
				mine[i - 1][j - 1]++;
				mine[i][j-1]++;
				mine[i + 1][j - 1]++;
				
				mine[i - 1][j]++;
				mine[i + 1][j]++;

				mine[i - 1][j + 1]++;
				mine[i][j + 1]++;
				mine[i + 1][j + 1]++;
			}
		}
	}
}

void Board::Reset_check() {

	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 36; j++) {
			check[i][j] = 0;
		}
	}
}

void Board::Reset() {
	Reset_check();
	RandomMine();
	Scanbox();
}