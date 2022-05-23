#pragma once

class Board
{
public:
	CRect m_board[36][36];  // 유저가 클릭할 상자의 주소가 있는 2차원 배열
	int mine[36][36]; // 지뢰가 있는 경우 음수 , 지뢰가 없는 경우 주위의 지뢰 개수만큼 해당 주소에 할열하는 2차원 배열
	int check[36][36]; // 유저가 해당 상자를 눌렀는지 확인하는 2차원 배열

	int chas_x; //유저가 클릭한 포인트 x 를 상자의 주소중 가로로 변환하여 저장할 변수
	int chas_y; //유저가 클릭한 포인트 y 를 상자의 주소중 세로로 변환하여 저장할 변수

	int boxCount; // 난이도에 따라 변화할 박스의 개수를 저장할 변수
	int boxSize; //난이도에 따라 변화할 박스의 크기를 저장할 변수
	int mineCount; //난이도에 따라 변화할 지뢰의 개수를 저장할 변수

	int timer; // 게임 시작 시간을 저장할 변수
	int score; // 점수를 저장할 변수


	void Difficulty(int mode); //난이도에 따라 박스의 개수나 상자의 크기를 변화시킬 메소드 (1 - Easy / 2 - Middle / 3 - Hard / 4 - Challange)
	void RandomMine(); // mine배열에 랜덤으로 지뢰를 할당하는 메소드
	void Scanbox(); // 지뢰를 설치한 후 주위의 박스에 숫자를 삽입하는 메소드
	
	void Reset(); //Reset,RandomMine,Scanbox를 합친 메소드
};

