#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include <ctime>

using namespace std;
using namespace sf;

class Cell {
public:
	RectangleShape main, border;
	float size = 25;
	Vector2f direct;

	Cell(float _size, float proc) {
		size = _size;

		border.setSize(Vector2f(_size, _size));
		Color border_color(7, 2, 171);
		border.setFillColor(border_color);

		float size_main = _size * proc;
		main.setSize(Vector2f(size_main, size_main));
		Color main_color(94, 89, 255);
		main.setFillColor(main_color);
		main.setPosition(Vector2f((_size - size_main) / 2, (_size - size_main) / 2));
	}

	void DrawCell(RenderWindow& win) {
		win.draw(border);
		win.draw(main);
	}

	void TranslateCell(Vector2f v2) {
		border.move(v2);
		main.move(v2);
	}

	//RectangleShape returnMain() { return main; }
	//RectangleShape returnBorder() { return border; }
};

class Apple {
public:

	Vector2f pos;
	RectangleShape main, border;
	float size = 25, proc;

	Apple(float _size, float _proc) {
		size = _size;
		proc = _proc;

		border.setSize(Vector2f(_size, _size));
		Color border_color(255, 0, 0);
		border.setFillColor(border_color);

		float size_main = _size * _proc;
		main.setSize(Vector2f(size_main, size_main));
		Color main_color(145, 168, 10);
		main.setFillColor(main_color);
		main.setPosition(Vector2f((_size - size_main) / 2, (_size - size_main) / 2));
		Spawn();
	}

	void SetPosMainPart() { // вынес чтобы не повторять две строчки кода постоянно...
		float size_main = size * proc;
		main.setPosition(Vector2f((size - size_main) / 2, (size - size_main) / 2));
	}

	void Spawn() {
		srand(time(0));
		int x = (rand() % 18 + 2) * 25, y = (rand() % 18 + 2) * 25;
		cout << "Respawn Apple! New points are: x = " << x << " y = " << y << endl;
		Vector2f _pos = Vector2f(x, y);
		pos = _pos;
		SetPosMainPart(); // для того чтобы mainPart встала по центру
		main.move(_pos);
		border.setPosition(_pos);

	}

	void DrawApple(RenderWindow& win) {
		win.draw(border);
		win.draw(main);
	}
};

class Snake {
public:
	vector<Cell> cells;
	bool Alive = true;

	void TranslateSnake(Vector2f v2) {
		for (int i = 0; i < cells.size(); i++)
			cells[i].TranslateCell(v2);
	}

	void TranslateSnake() {
		for (int i = 0; i < cells.size(); i++)
			cells[i].TranslateCell(cells[i].direct);
	}

	Snake(int size, Cell cell) {
		for (int i = 0; i < size; i++) {
			cells.push_back(cell);
			TranslateSnake(Vector2f(0, cell.size));
			cells[i].direct = Vector2f(0, 25);
		}
		TranslateSnake(Vector2f(0, -cell.size));
	}

	void addCell(Cell cell) {
		cell = cells[cells.size() - 1];
		cell.border.move(Vector2f(-cells[cells.size() - 1].direct));
		cell.main.move(Vector2f(-cells[cells.size() - 1].direct));
		cells.push_back(cell);
	}

	void Draw(RenderWindow& win) {
		for (int i = 0; i < cells.size(); i++) {
			cells[i].DrawCell(win);
		}
	}

	void ChangeDirect() {
		for (int i = cells.size() - 1; i > 0; i--) {
			if (cells[i].direct != cells[i - 1].direct) {
				cells[i].direct = cells[i - 1].direct;
			}
		}
	}
	void CheckCollectApple(Apple &apple, Cell cell, int &score) {
		if (apple.pos == cells[0].border.getPosition()) {
			apple.Spawn();
			addCell(cell);
			score++;
			cout << "Now your score iqual to " << score << endl;
			cout << "Apple was collected! && snake size = " << cells.size() << endl;
		}
	}

	void Death() {
		cout << "Snake dead!";
	}

	void CheckDeath() {
		// 1 когда змейка коснулась себя
		for (int i = 0; i < cells.size(); i++) {
			for (int j = 0; j < cells.size(); j++) {
				if (cells[i].border.getPosition() == cells[j].border.getPosition() && i != j) {
					Alive = false;
				}
			}
		}

		// 2 когда змейка коснулась конца поля (за размер поля беряться размер 500х500)
		if (cells[0].border.getPosition().x == 500 || cells[0].border.getPosition().y == 500 || cells[0].border.getPosition().x == -25 || cells[0].border.getPosition().y == -25) Alive = false;
		if (!Alive) Death();
	}
};

class Timer {
public:
	Time time;
	Clock clock;
	float seconds = 0;

	void Update() {
		time = clock.restart();
		seconds += time.asSeconds();
	}

	bool Check(float per) {
		if (seconds >= per) {
			seconds = 0;
			return true;
		}
		else return false;
	}
};
