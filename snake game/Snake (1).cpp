#include "Snake.hpp"


SNAKE::SNAKE()
{
	Die = false;

	Status = RIGHT;

	sprite.setRadius(15);
	Amount = 3;
	Position[0].Column = 100;
	Position[0].Line = 100;
	Position[1].Column = 90;
	Position[1].Line = 100;
	Position[2].Column = 80;
	Position[2].Line = 100;

	for (int i = 3; i < 120; i++)
	{
		Position[i].Column = NULL;
		Position[i].Line = NULL;
	}
}
const int headofsnake = 0;

void SNAKE::ShowSnake(RenderWindow &window, Texture & Head, Texture & Body)
{

	// Vẽ Cái Đầu
	sprite.setTexture(&Head);
	sprite.setPosition(Position[0].Column, Position[0].Line);
	window.draw(sprite);

	// Vẽ Thân
	for (int i = 1; i < Amount; i++)
	{
		sprite.setTexture(&Body);
		sprite.setPosition(Position[i].Column, Position[i].Line);
		window.draw(sprite);
	}
}

bool SNAKE::Process(float Column, float Line)
{
	for (int i = Amount - 1; i > 0; i--)
		Position[i] = Position[i - 1];

	switch (Status)
	{
	case UP:
		Position[0].Line -= 10;
		break;
	case DOWN:
		Position[0].Line += 10;
		break;
	case LEFT:
		Position[0].Column -= 10;
		break;
	case RIGHT:
		Position[0].Column += 10;
		break;
	}

	// Xử Lí Chạm Thân
	SoundBuffer end;
	end.loadFromFile("sound/endgame.wav");
	Sound End;
	End.setBuffer(end);

	for (int i = 1; i < Amount; i++)
	{
		if (Position[0].Column == Position[i].Column && Position[0].Line == Position[i].Line)
		{
			End.play();
			Sleep(500);
			Die = true;
			break;
		}
	}

	if (Position[0].Column < 0.0 || Position[0].Column >= 750.0) {
		End.play();
		Sleep(500);
		Die = true;
	}
	if (Position[0].Line < 0.0 || Position[0].Line >= 412.0)
	{
		End.play();
		Sleep(500);
		Die = true;
	}

	if (Position[0].Column == Column && Position[0].Line == Line|| Position[0].Column == Column+2 && Position[0].Line == Line+3|| Position[0].Column == Column + 2 && Position[0].Line == Line + 4)
	{
		Amount++;
		for (int i = Amount - 1; i > 0; i--)
			Position[i] = Position[i - 1];
		return true;
	}
	else return false;
}

void SNAKE::setStatus(STATUS Tus)
{
	Status = Tus;
}

STATUS SNAKE::getStatus()
{
	return Status;
}

