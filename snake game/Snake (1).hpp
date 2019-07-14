#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include<Windows.h>
#include <iostream>
#define WEIGHT 750
#define HEIGHT 412

using namespace sf;
using namespace std;

// Trạng Thái Của Con Rắn
enum STATUS {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// Tọa Độ Cho Một Đốt Của Con Rắn

struct bodySnake {
	CircleShape _sprite;
	STATUS _direction;
};
struct POSITION
{
	float Column;
	float Line;
};

class SNAKE
{
private:
	bodySnake m_body[100];
	CircleShape sprite;
	STATUS Status;
	POSITION Position[120];
	int Amount;       // Số Đốt Của Con Rắn
	int Bonus;         // Thang Điểm Thưởng
public:
	// Constructor
	SNAKE();

	bool Die;               // True Là Rắn Chết
							// False Là Rắn Chưa Chết

	void ShowSnake(RenderWindow &, Texture &, Texture &);

	// Hàm Để Xử Lí Di Chuyển
	bool Process(float, float);           // Trả Vể True Là Ăn Được Mồi
										  // Trả Về False Là Chưa Ăn Được Mồi

	void setStatus(STATUS);
	STATUS getStatus();
};


#endif