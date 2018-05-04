#include<iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

RenderWindow window({ 1024,760 }, L"Crossing Street - Đồ án TH KTLT 1712834");

// ================================

struct SndEff {
	SoundBuffer buff;
	Sound s;
};

// Nền
Texture background;
Sprite BG;

Texture MenuBG;
Sprite Menu;
Music menu;

Texture Title;
Sprite title;

Music city;
SndEff crashed[2];
SndEff sucess;
Music Win_s;

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
Texture die;
Sprite dead;

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

	die.loadFromFile("Res/dead.png");
	dead.setTexture(die);
	dead.setOrigin(Vector2f(dead.getTexture()->getSize().x * 0.5, dead.getTexture()->getSize().y*0.5));
	dead.scale(2.0f, 2.0f);
	
	menu.openFromFile("Res/menu.wav");
	menu.setVolume(50);
	city.openFromFile("Res/traffic.wav");
	crashed[0].buff.loadFromFile("Res/crashed1.wav");
	crashed[0].s.setBuffer(crashed[0].buff);
	crashed[1].buff.loadFromFile("Res/crashed2.wav");
	crashed[1].s.setBuffer(crashed[1].buff);
	crashed[1].s.setVolume(50);

	sucess.buff.loadFromFile("Res/Win2.wav");
	sucess.s.setBuffer(sucess.buff);
	sucess.s.setVolume(50);
	Win_s.openFromFile("Res/Win.wav");
}

// ================================

struct Point {
	float x;
	float y;
	Sprite p;
};

Point Player;
bool endgame = false;
bool win = false;
bool again = true;
int lv = 0;
Point *finished = NULL; int fn = 0;

Point *R1 = NULL; int cr1 = 0;
Point *R2 = NULL; int cr2 = 0;
Point *L3 = NULL; int cl3 = 0;
Point *L4 = NULL; int cl4 = 0;

bool PlayerColision (Sprite a) {
	FloatRect c_m = Player.p.getGlobalBounds();		

	FloatRect collision_mask(c_m.left + c_m.width/3,c_m.top + c_m.height*0.85, c_m.width/3, c_m.height*0.01);
	
	return a.getGlobalBounds().intersects(collision_mask);
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

	addCars(R1, cr1, 'R', 615, random(1,2+lv));
	addCars(R2, cr2, 'R', 460, random(1,2+lv));
	addCars(L3, cl3, 'L', 320, random(1,2+lv));
	addCars(L4, cl4, 'L', 200, random(1,2+lv));
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
			Player.x -= 8;
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
			Player.x += 8;
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
			Player.y += 12;
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
			Player.y -= 12;
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

void moveAcarR(Point &car) {
	float x = (float)lv / 100;
	if (car.x + 0.02 + x < 1024)
		car.x += (0.02 + x);
	else {
		car.p = C_R[random(0, 3)];
		car.x = 0;
	}
	car.p.setPosition(car.x, car.y);
}

void moveAcarL(Point &car) {
	float x = (float)lv / 100;
	if (car.x - 0.02 - x > 0)
		car.x -= (0.02 + x);
	else {
		car.p = C_L[random(0, 3)];
		car.x = 1023;
	}
	car.p.setPosition(car.x, car.y);
}

void MoveCars() {
	for (int i = 0; i < cr1; i++)
		moveAcarR(R1[i]);
	for (int i = 0; i < cr2; i++)
		moveAcarR(R2[i]);
	for (int i = 0; i < cl3; i++)
		moveAcarL(L3[i]);
	for (int i = 0; i < cl4; i++)
		moveAcarL(L4[i]);
}

void RunMenu() {
	menu.setLoop(true);
	menu.play();
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
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
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

	menu.stop();
}

bool CheckWin(int n) {
	if (Player.y <= 95) {
		PushFn(finished, fn);
		finished[fn - 1] = Player;
		finished[fn - 1].p.setPosition(finished[fn - 1].x, finished[fn - 1].y);

		Player.x = 500;
		Player.y = 720;
		Player.p.setPosition(Player.x, Player.y);
		sucess.s.play();
	}
	if (fn == n) {
		if(fn == 3) 
			endgame = true;
		win = true;
		sucess.s.play();
		while (sucess.s.getStatus() == Sound::Playing) {}
		return true;
	}
	return false;
}

bool CheckLose() {
	for (int i = 0; i < fn; i++)
		if (PlayerColision(finished[i].p))
			return true;
	for (int i = 0; i < cr1; i++)
		if (PlayerColision(R1[i].p))
			return true;
	for (int i = 0; i < cr2; i++)
		if (PlayerColision(R2[i].p))
			return true;
	for (int i = 0; i < cl3; i++)
		if (PlayerColision(L3[i].p))
			return true;
	for (int i = 0; i < cl4; i++)
		if (PlayerColision(L4[i].p))
			return true;
	return false;
}

void Pross_Win() {
	lv++;
}

void Pross_Lose() {
	// Do st
	again = false;
}

void Pross_End() {
	// do st
	again = false;
}

void Run() {
	city.setLoop(true);
	city.play();
	while (window.isOpen() && !endgame) {
		window.pollEvent(event);
		if (event.type == Event::Closed)
			window.close();

		if (event.type == Event::KeyPressed)
			Move();
		MoveCars();

		if (CheckLose()) {
			city.stop();
			crashed[0].s.play();
			crashed[1].s.play();
			Player.p = dead;
			Player.p.setPosition(Player.x, Player.y);

			window.clear();
			window.draw(BG);
			DrawCars();
			for (int i = 0; i < fn; i++)
				window.draw(finished[i].p);
			window.draw(Player.p);
			window.display();
			while (crashed[1].s.getStatus() != Sound::Stopped) {}
			break;
		}
		if (CheckWin(lv+1))
			break;
		window.clear();
		window.draw(BG);
		DrawCars();
		for (int i = 0; i < fn; i++)
			window.draw(finished[i].p);
		window.draw(Player.p);
		window.display();
	}
	if (win)
		if (endgame)
			Pross_End();
		else
			Pross_Win();
	else
		Pross_Lose();

	city.stop();
}

void Reset() {
	if (finished) {
		delete[] finished;
		finished = NULL;
		fn = 0;
	}
	delete[] R1;
	R1 = NULL;
	cr1 = 0;
	delete[] R2;
	R2 = NULL;
	cr2 = 0;
	delete[] L3;
	L3 = NULL;
	cl3 = 0;
	delete[] L4;
	L4 = NULL;
	cl4 = 0;
}

void ResetGame() {
	lv = 0;
	win = false;
	endgame = false;
	again = true;
}

int main() {
	srand(time(NULL));
    LoadResources();
	while (window.isOpen()) {
		RunMenu();
		while (again && window.isOpen()) {
			Setup();
			Run();
			Reset();
		}
		ResetGame();
	}
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