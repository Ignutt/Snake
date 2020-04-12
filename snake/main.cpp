#include <SFML/Graphics.hpp>
#include <iostream>	
#include "help.h"

using namespace sf;
using namespace std;

int main()
{
	int score = 0;
	Apple apple(25, 0.65f);

	Timer timer;
	RenderWindow window(VideoMode(500, 500), "Snake");
	Cell cell(25, 0.65f);
	Snake snake(3, cell);

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
		if (snake.Alive) {
			window.clear(Color::Green);
			snake.Draw(window);
			apple.DrawApple(window);
			if (timer.Check(0.5f)) { // скорость перемещения змейки
				//cout << "Apple position is: "<< apple.pos.x << " " << apple.pos.y << endl;
				snake.TranslateSnake();
				snake.ChangeDirect();
				snake.CheckCollectApple(apple, cell, score);
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