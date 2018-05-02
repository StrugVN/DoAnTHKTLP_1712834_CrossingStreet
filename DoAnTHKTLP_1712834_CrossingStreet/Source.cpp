#include<iostream>
#include<cstdlib>
#include<conio.h>
#include <SFML/Graphics.hpp>
#include<Windows.h>

using namespace std;
using namespace sf;

// ================================

// Nền
Texture background;
Sprite BG;

// Nút
Texture Start;
Sprite Str;
Texture Exit;
Sprite Ex;
Texture LoadG;
Sprite Load;

// Player
Texture P[12];
Sprite Sp[12];

Event event;

void LoadResources() {
	background.loadFromFile("Res/Background.png");
	BG.setTexture(background);

	Start.loadFromFile("Res/Start.png");
	Str.setTexture(Start);
	Exit.loadFromFile("Res/Exit.png");
	Ex.setTexture(Exit);
	LoadG.loadFromFile("Res/Load.png");
	Load.setTexture(LoadG);

	P[0].loadFromFile("Res/Up1.png");
	P[1].loadFromFile("Res/Up2.png");
	P[2].loadFromFile("Res/Up3.png");
	P[3].loadFromFile("Res/Up2.png");
	P[4].loadFromFile("Res/R1.png");
	P[5].loadFromFile("Res/R2.png");
	P[6].loadFromFile("Res/R3.png");
	P[7].loadFromFile("Res/R2.png");
	P[8].loadFromFile("Res/L1.png");
	P[9].loadFromFile("Res/L2.png");
	P[10].loadFromFile("Res/L3.png");
	P[11].loadFromFile("Res/L2.png");
	for (int i = 0; i < 12; i++) {
		Sp[i].setTexture(P[i]);
		Sp[i].setOrigin(Vector2f(Sp[i].getTexture()->getSize().x * 0.5, Sp[i].getTexture()->getSize().y*0.5));
		if (i < 2 || i == 3)
			Sp[i].setScale(2.0f, 2.0f);
	}
}

// ================================

struct Point {
	float x;
	float y;
	Sprite *p;
};

Point Player;

void Setup() {
	Player.x = 500;
	Player.y = 720;
	Player.p = Sp;
	Player.p->setPosition(Player.x, Player.y);
}

void Move() {
	switch (event.key.code) {
	case Keyboard::A: {
		static int last = 0;
		if (Player.x - 1 > 0) {
			Player.x -= 5;
			Player.p = Sp + 8 + last;
			last++;
			if (last >= 4)
				last = 0;
			Player.p->setPosition(Player.x, Player.y);
		}
		break;
	}
	case Keyboard::D: {
		static int last = 0;
		if (Player.x + 1 < 1024) {
			Player.x += 5;
			Player.p = Sp + 4 + last;
			last++;
			if (last >= 4)
				last = 0;
			Player.p->setPosition(Player.x, Player.y);
		}
		break;
	}

	case Keyboard::S: {
		static int last = 0;
		if (Player.y + 1 < 760) {
			Player.y += 5;
			Player.p = Sp + last;
			last++;
			if (last >= 4)
				last = 0;
			Player.p->setPosition(Player.x, Player.y);
		}
		break;
	}

	case Keyboard::W: {
		static int last = 0;
		if (Player.y - 1 > 0) {
			Player.y -= 5;
			Player.p = Sp + last;
			last++;
			if (last >= 4)
				last = 0;
			Player.p->setPosition(Player.x, Player.y);
		}
		break;
	}

	default:
		break;
	}
}

int main()
{
	sf::RenderWindow window({ 1024,760 }, L"Crossing Street - Đồ án TH KTLT");

	LoadResources();
	Setup();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				Move();

		}

		window.clear();
		window.draw(BG);
		window.draw(*Player.p);
		window.display();
	}

	return 0;
}