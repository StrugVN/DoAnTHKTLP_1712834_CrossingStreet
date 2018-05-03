#include<iostream>
#include<cstdlib>
#include<conio.h>
#include <SFML/Graphics.hpp>
#include<Windows.h>

using namespace std;
using namespace sf;

RenderWindow window({ 1024,760 }, L"Crossing Street - Đồ án TH KTLT");

// ================================

// Nền
Texture background;
Sprite BG;
Texture MenuBG;
Sprite Menu;
Texture Title;
Sprite title;

// Nút
struct button {
	Texture _normal;
	Sprite normal;
	Texture _pressed;
	Sprite pressed;
	Sprite *Curr;
};

button Start;
button Load;
button Exit;

// Player
Texture P[12];
Sprite Sp[12];

// Xe
Texture CR[5], CL[4];
Sprite C_R[5], C_L[4];

Event event;

void LoadResources() {
	background.loadFromFile("Res/Background.png");
	BG.setTexture(background);
	MenuBG.loadFromFile("Res/Menu.jpg");
	Menu.setTexture(MenuBG);
	Title.loadFromFile("Res/name.png");
	title.setTexture(Title);
	title.setPosition(256, 150);

	Start._normal.loadFromFile("Res/Start.png");
	Start.normal.setTexture(Start._normal);
	Start.normal.setPosition(475, 565);
	Start._pressed.loadFromFile("Res/StartP.png");
	Start.pressed.setTexture(Start._pressed);
	Start.pressed.setPosition(475, 565);
	Start.Curr = &Start.normal;

	Exit._normal.loadFromFile("Res/Exit.png");
	Exit.normal.setTexture(Exit._normal);
	Exit.normal.setPosition(60, 670);
	Exit._pressed.loadFromFile("Res/ExitP.png");
	Exit.pressed.setTexture(Exit._pressed);
	Exit.pressed.setPosition(60, 670);
	Exit.Curr = &Exit.normal;

	Load._normal.loadFromFile("Res/Load.png");
	Load.normal.setTexture(Load._normal);
	Load.normal.setPosition(496, 652);
	Load._pressed.loadFromFile("Res/LoadP.png");
	Load.pressed.setTexture(Load._pressed);
	Load.pressed.setPosition(496, 652);
	Load.Curr = &Load.normal;

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

	CR[0].loadFromFile("Res/CarR1.png");
	CR[1].loadFromFile("Res/CarR2.png");
	CR[2].loadFromFile("Res/CarR3.png");
	CR[3].loadFromFile("Res/CarR4.png");
	for (int i = 0; i < 4; i++) {
		C_R[i].setTexture(CR[i]);
		C_R[i].setOrigin(Vector2f(C_R[i].getTexture()->getSize().x * 0.5, C_R[i].getTexture()->getSize().y*0.5));
		C_R[i].scale(0.75f, 0.75f);
	}

	CL[0].loadFromFile("Res/CarL1.png");
	CL[1].loadFromFile("Res/CarL2.png");
	CL[2].loadFromFile("Res/CarL3.png");
	CL[3].loadFromFile("Res/CarL4.png");
	for (int i = 0; i < 4; i++) {
		C_L[i].setTexture(CL[i]);
		C_L[i].setOrigin(Vector2f(C_L[i].getTexture()->getSize().x * 0.5, C_L[i].getTexture()->getSize().y*0.5));
		C_L[i].scale(0.75f, 0.75f);
	}
}

// ================================

struct Point {
	float x;
	float y;
	Sprite p;
};

Point Player;
bool endgame = false;
Point *finished = NULL; int fn = 0;

Point *R1 = NULL; int cr1 = 0;
Point *R2 = NULL; int cr2 = 0;
Point *L3 = NULL; int cl3 = 0;
Point *L4 = NULL; int cl4 = 0;

bool Collision(Sprite a, Sprite b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

int random(int a, int b) {
	if (a >= b)
		return a;

	return rand() % (b - a + 1) + a;
}

void PushFn(Point *&A, int &n) {
	if (n == 0) {
		A = new Point[1];
	}
	else {
		Point* temp = new Point[n + 1];
		for (int i = 0; i < n; i++)
			temp[i] = A[i];
		delete[] A;
		A = temp;
	}
	n++;
}

void addCars(Point *&A, int &n, char c, int yrow, int count) {
	float mid = 1000.0f / (count+1);
	float CW = 100;
	float pos = CW;
	while (pos + mid < 1024 - CW) {
		PushFn(A, n);
		A[n - 1].x = random(pos, pos + mid-CW);
		A[n - 1].y = yrow;
		if (c == 'L' || c == 'l')
			A[n - 1].p = C_L[random(0, 3)];
		else
			A[n - 1].p = C_R[random(0, 3)];
		A[n - 1].p.setPosition(A[n - 1].x, A[n - 1].y);
		pos += mid + CW;
		cout << "Car added at " << A[n - 1].x << " " << A[n - 1].y << endl;
	}
}

void Setup() {
	Player.x = 500;
	Player.y = 720;
	Player.p = Sp[0];
	Player.p.setPosition(Player.x, Player.y);

	srand(time(NULL));

	addCars(R1, cr1, 'R', 615, random(2,4));
	addCars(R2, cr2, 'R', 460, random(2,4));
	addCars(L3, cl3, 'L', 320, random(2,4));
	addCars(L4, cl4, 'L', 200, random(2,4));
}

void DrawCars() {
	for (int i = 0; i < cr1; i++)
		window.draw(R1[i].p);
	for (int i = 0; i < cr2; i++)
		window.draw(R2[i].p);
	for (int i = 0; i < cl3; i++)
		window.draw(L3[i].p);
	for (int i = 0; i < cl4; i++)
		window.draw(L4[i].p);
}

void Move() {
	switch (event.key.code) {
	case Keyboard::A: {
		static int last = 0;
		if (Player.x - 1 > 130) {
			Player.x -= 5;
			Player.p = Sp[8 + last];
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}
	case Keyboard::D: {
		static int last = 0;
		if (Player.x + 1 < 1024) {
			Player.x += 5;
			Player.p = Sp[4 + last];
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}

	case Keyboard::S: {
		static int last = 0;
		if (Player.y + 1 < 760) {
			Player.y += 5;
			Player.p = Sp[last];
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}

	case Keyboard::W: {
		static int last = 0;
		if (Player.y - 1 > 0) {
			Player.y -= 5;
			Player.p = Sp[last];
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}

	// ==== Để debug =====
	case Keyboard::L:
		cout << "Player pos: " << Player.x << " " << Player.y << endl;
		break;
	// ======================

	default:
		break;
	}
}

void CheckWin() {
	if (Player.y <= 95) {
		PushFn(finished,fn);
		finished[fn-1] = Player;
		finished[fn-1].p.setPosition(finished[fn-1].x, finished[fn-1].y);

		Player.x = 500;
		Player.y = 720;
		Player.p.setPosition(Player.x, Player.y);
	}
}



void RunMenu() {
	while (true) {
		if (Start.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			Start.Curr = &Start.pressed;
		else
			Start.Curr = &Start.normal;

		if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			Exit.Curr = &Exit.pressed;
		else
			Exit.Curr = &Exit.normal;

		if (Load.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			Load.Curr = &Load.pressed;
		else
			Load.Curr = &Load.normal;

		if (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				if (Start.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
					break;
				else if (Load.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					cout << "Load chua xai dc ahjhj" << endl;
				}
				else if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					window.close();
					break;
				}
			}
		}

		window.clear();
		window.draw(Menu);
		window.draw(title);
		window.draw(*Start.Curr);
		window.draw(*Load.Curr);
		window.draw(*Exit.Curr);
		window.display();
	}
}

void Run() {
	while (window.isOpen() && !endgame) {
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				Move();
		}

		CheckWin();
		window.clear();
		window.draw(BG);
		window.draw(Player.p);
		DrawCars();
		for (int i = 0; i < fn; i++)
			window.draw(finished[i].p);
		window.display();
	}
}

int main() {
    LoadResources();
	Setup();

	RunMenu();
	Run();

	return 0;
}

/*	Note to self:
   - 1024x760
   - Start: 500x720
   - Road 1: 615 R
   - Road 2: 460 R
   - Road 3: 320 L
   - Road 4: 200 L
   - Finish: 100 - 90
*/