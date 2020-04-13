#include <SFML/Graphics.hpp>
#include <iostream>	
#include "help.h"

using namespace sf;
using namespace std;

void Introdaction(float &speed, int &size) {
	system("cls");
	cout << "Some setting..." << endl << "If you want to skip this step and play with default options, just input 0" << endl <<
		"1) Speed snake (0.01 - fast; 1.0 - slow): " << endl << "> ";
	cin >> speed;
	if (speed > 0 && speed < 3) {
		cout << endl << "2) Size of snake (min 1; max 18): " << endl << "> ";
		cin >> size;
		if (size < 1 && size > 18) size = 3;
	}
	else {
		speed = 1;
		size = 3;
	}
	
}

int main()
{
	int score = 0;
	Apple apple(25, 0.65f);

	float speed = 1; int size = 3;
	
	Introdaction(speed, size);

	Timer timer(speed);
	RenderWindow window(VideoMode(500, 500), "Snake");
	Cell cell(25, 0.65f);
	Snake snake(size, cell);

	while (window.isOpen())
	{
		Event e;
		timer.Update();

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Right) && snake.cells[0].direct.x != -25) {
				snake.cells[0].direct = Vector2f(25, 0);
				//cout << snake.cells[0].direct.x << " " <<snake.cells[0].direct.y << endl;
			} else if (Keyboard::isKeyPressed(Keyboard::Left) && snake.cells[0].direct.x != 25) {
				snake.cells[0].direct = Vector2f(-25, 0);
				//cout << snake.cells[0].direct.x << " " << snake.cells[0].direct.y << endl;
			} else if (Keyboard::isKeyPressed(Keyboard::Down) && snake.cells[0].direct.y != -25) {
				snake.cells[0].direct = Vector2f(0, 25);
				//cout << snake.cells[0].direct.x << " " << snake.cells[0].direct.y << endl;
			} else if (Keyboard::isKeyPressed(Keyboard::Up) && snake.cells[0].direct.y != 25) {
				snake.cells[0].direct = Vector2f(0, -25);
				//cout << snake.cells[0].direct.x << " " << snake.cells[0].direct.y << endl;
			}

		}
		Color color(52, 235, 171);

		if (snake.Alive) {
			window.clear(color);
			snake.Draw(window);
			apple.DrawApple(window);
			if (timer.Check()) { // скорость перемещения змейки
				//cout << "Apple position is: "<< apple.pos.x << " " << apple.pos.y << endl;
				snake.TranslateSnake(apple);
				snake.ChangeDirect();
				snake.CheckCollectApple(apple, cell, score, timer, 0.05); 
				snake.CheckDeath();
				//cout << snake.cells[0].border.getPosition().x << " " << snake.cells[0].border.getPosition().y << endl;
			}
			window.display();
		}
		else {
			window.clear(Color::Red);
			window.display();
		}
	}
	return 0;
}