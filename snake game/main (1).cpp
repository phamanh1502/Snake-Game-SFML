#include "Snake.hpp"

enum STAGE {
	MENU,
	GAME,
	GAMEPLAY,
	RESULT
};

struct FRUIT
{
	int x;
	int y;
	CircleShape sprite;
	FRUIT(Texture &texture)
	{
		sprite.setTexture(&texture);
		x = (rand() % 39 + 1) * 10 + 50;
		y = (rand() % 29 + 1) * 10 + 50;
		sprite.setPosition(x, y);
		sprite.setRadius(15);
	}
};

void PlayGame(RenderWindow &window)
{
	Texture Head, Body, Fruits, Background;
	Background.loadFromFile("image/inferno.png");
	Head.loadFromFile("image/Head.png");
	Body.loadFromFile("image/snakebody.png");
	Fruits.loadFromFile("image/apple.png");

	Sprite MainBackground(Background);
	MainBackground.setPosition(0, 0);
	SNAKE Snake;
	FRUIT Fruit(Fruits);
	Background.setRepeated(true);
	MainBackground.setTextureRect({ 0, 0, 750, 412 });

	SoundBuffer beep, eat;
	beep .loadFromFile("sound/beep.wav");
	eat.loadFromFile("sound/EatFruit.wav");
	Sound Beep, Eat;
	Beep.setBuffer(beep);
	Eat.setBuffer(eat);

	int i = 0;
	while (!Snake.Die)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		window.clear();
		window.draw(MainBackground);
		window.draw(Fruit.sprite);

		if (Snake.Process(Fruit.x, Fruit.y))
		{
			Fruit.x = (rand() % 39 + 1) * 10 + 50;
			Fruit.y = (rand() % 29 + 1) * 10 + 50;
			Fruit.sprite.setPosition(Fruit.x, Fruit.y);
			Eat.play();
			i++;
		}
		Snake.ShowSnake(window, Head, Body);

		if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && Snake.getStatus() != RIGHT)
		{

			Snake.setStatus(LEFT);
			Beep.play();
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && Snake.getStatus() != LEFT)
		{
			Snake.setStatus(RIGHT);
			Beep.play();
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && Snake.getStatus() != DOWN)
		{
			Snake.setStatus(UP);
			Beep.play();
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && Snake.getStatus() != UP)
		{
			Snake.setStatus(DOWN);
			Beep.play();
		}
		window.display();
		sleep(milliseconds(50 - i));

	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		if (Snake.Die)
		{
			window.clear();
			Texture go;
			go.loadFromFile("image/gameover.jpg");
			Sprite gameover(go);
			window.clear();
			gameover.setPosition(0, 0);
			gameover.setScale(0.5625, 0.57);
			window.draw(gameover);
			window.display();
			if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x <= 750 && Mouse::getPosition(window).y >= 0 && Mouse::getPosition(window).y <= 412)
			{
				break;
			}
		}
	}
}
int main()
{
	RenderWindow window(VideoMode(750, 412), "Snake Game", Style::Resize|Style::Default);
	Texture image1, image2, image4, head, body, tail, background, app, head2, go;
	image1.loadFromFile("image/snake.png");
	image2.loadFromFile("image/start.png");
	Sprite sprite1(image1), sprite2(image2);
	Sprite Head(head);
	SoundBuffer buffer1;
	buffer1.loadFromFile("sound/soundstart.wav");
	Sound sound1;
	sound1.setBuffer(buffer1);

	STAGE stage = MENU;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}

		if (stage == MENU) {
			window.clear();
			sprite1.setPosition(0, 0);
			sprite2.setPosition(270, 290);
			sprite2.setScale(0.5, 0.4);
			window.draw(sprite1);
			window.draw(sprite2);
			window.display();

			//Lay toa do cua Start Image
			int x = Mouse::getPosition(window).x;
			int y = Mouse::getPosition(window).y;
			cout << x << " " << y << endl;
			if (Mouse::isButtonPressed(Mouse::Left) && x >= 283 && x <= 398 && y >= 313 && y <= 338) {
				window.clear();
				window.draw(sprite1);
				sprite2.setPosition(270, 260);
				sprite2.setScale(0.5, 0.5);
				window.draw(sprite2);
				window.display();
				Sleep(500);
				sound1.play();
				stage = GAME;
			}

		}
		else if (stage == GAME) {
			int x = Mouse::getPosition(window).x;
			int y = Mouse::getPosition(window).y;
			PlayGame(window);
			if (Mouse::isButtonPressed(Mouse::Left) && x >= 0 && x <= 750 && y >= 0 && y <= 412)
			{
				sound1.play();
				Sleep(300);
				stage = MENU;
			}
		}
	}
	if (stage == RESULT)
	{
		Texture go;
		go.loadFromFile("image/gameover.jpg");
		Sprite gameover(go);
		window.clear();
		gameover.setPosition(0, 0);
		gameover.setScale(0.5625, 0.57);
		window.draw(gameover);
		window.display();
	}
	return 0;
}