#pragma warning(push)
#pragma warning(disable: 4244)
#include<iostream>
#include<cstdlib>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

using namespace std;
using namespace sf;

RenderWindow window({ 1024,760 }, L"Crossing Street - Đồ án TH KTLT 1712834");

// ================================

// Âm thanh
struct SndEff {
	SoundBuffer buff;
	Sound s;
};
// Hình ảnh
struct Sf {
	Texture t;
	Sprite s;
};

// Main menu
Sf BG;

Sf menuBG;
Music menu;

Texture Title;
Sprite title;

Music city;
SndEff crashed[2];
SndEff sucess;


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
Sf P[12];
Sf dead;

// Xe
Sf CR[4], CL[4];

// Lost screen
Sf l_menu;
button r_menu;
button retry;
SndEff lose_track;

// Win screen
Sf w_menu;
Music Win_s;

Event event;

// Pause Menu
Sf p_menu;
button resume;
button savegame;
button loadgame;
button quit;

// Đèn xanh đỏ
button r;
button l;

// Menu save
Sf savemenu;

// Menu load
Sf loadmenu;

// Text
Font font;

void LoadResources() {
	BG.t.loadFromFile("Res/Background.png");
	BG.s.setTexture(BG.t);
	menuBG.t.loadFromFile("Res/Menu.jpg");
	menuBG.s.setTexture(menuBG.t);
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

	P[0].t.loadFromFile("Res/Up1.png");
	P[1].t.loadFromFile("Res/Up2.png");
	P[2].t.loadFromFile("Res/Up3.png");
	P[3].t.loadFromFile("Res/Up2.png");
	P[4].t.loadFromFile("Res/R1.png");
	P[5].t.loadFromFile("Res/R2.png");
	P[6].t.loadFromFile("Res/R3.png");
	P[7].t.loadFromFile("Res/R2.png");
	P[8].t.loadFromFile("Res/L1.png");
	P[9].t.loadFromFile("Res/L2.png");
	P[10].t.loadFromFile("Res/L3.png");
	P[11].t.loadFromFile("Res/L2.png");
	for (int i = 0; i < 12; i++) {
		P[i].s.setTexture(P[i].t);
		P[i].s.setOrigin(Vector2f(P[i].s.getTexture()->getSize().x * 0.5, P[i].s.getTexture()->getSize().y*0.5));
		if (i < 2 || i == 3)
			P[i].s.setScale(2.0f, 2.0f);
	}

	CR[0].t.loadFromFile("Res/CarR1.png");
	CR[1].t.loadFromFile("Res/CarR2.png");
	CR[2].t.loadFromFile("Res/CarR3.png");
	CR[3].t.loadFromFile("Res/CarR4.png");
	for (int i = 0; i < 4; i++) {
		CR[i].s.setTexture(CR[i].t);
		CR[i].s.setOrigin(Vector2f(CR[i].s.getTexture()->getSize().x * 0.5, CR[i].s.getTexture()->getSize().y*0.5));
		CR[i].s.scale(0.75f, 0.75f);
	}

	CL[0].t.loadFromFile("Res/CarL1.png");
	CL[1].t.loadFromFile("Res/CarL2.png");
	CL[2].t.loadFromFile("Res/CarL3.png");
	CL[3].t.loadFromFile("Res/CarL4.png");
	for (int i = 0; i < 4; i++) {
		CL[i].s.setTexture(CL[i].t);
		CL[i].s.setOrigin(Vector2f(CL[i].s.getTexture()->getSize().x * 0.5, CL[i].s.getTexture()->getSize().y*0.5));
		CL[i].s.scale(0.75f, 0.75f);
	}

	dead.t.loadFromFile("Res/dead.png");
	dead.s.setTexture(dead.t);
	dead.s.setOrigin(Vector2f(dead.s.getTexture()->getSize().x * 0.5, dead.s.getTexture()->getSize().y*0.5));
	dead.s.scale(2.0f, 2.0f);

	l_menu.t.loadFromFile("Res/lose.jpg");
	l_menu.s.setTexture(l_menu.t);

	r_menu._normal.loadFromFile("Res/menu.png");
	r_menu.normal.setTexture(r_menu._normal);
	r_menu._pressed.loadFromFile("Res/menuP.png");
	r_menu.pressed.setTexture(r_menu._pressed);
	r_menu.Curr = &r_menu.normal;

	retry._normal.loadFromFile("Res/again.png");
	retry.normal.setTexture(retry._normal);
	retry.normal.setPosition(618, 36);
	retry._pressed.loadFromFile("Res/againP.png");
	retry.pressed.setTexture(retry._pressed);
	retry.pressed.setPosition(618, 36);
	retry.Curr = &retry.normal;

	w_menu.t.loadFromFile("Res/Win.jpg");
	w_menu.s.setTexture(w_menu.t);
	
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

	lose_track.buff.loadFromFile("Res/failed.wav");
	lose_track.s.setBuffer(lose_track.buff);
	lose_track.s.setVolume(60);

	p_menu.t.loadFromFile("Res/Paused.png");
	p_menu.s.setTexture(p_menu.t);
	p_menu.s.setOrigin(Vector2f(p_menu.s.getTexture()->getSize().x * 0.5, p_menu.s.getTexture()->getSize().y*0.5));
	p_menu.s.setPosition(512, 380);

	resume._normal.loadFromFile("Res/resume.png");
	resume.normal.setTexture(resume._normal);
	resume.normal.setOrigin(Vector2f(resume.normal.getTexture()->getSize().x*0.5, resume.normal.getTexture()->getSize().y*0.5));
	resume.normal.setPosition(512, 380 - 110);
	resume._pressed.loadFromFile("Res/resumeP.png");
	resume.pressed.setTexture(resume._pressed);
	resume.pressed.setOrigin(Vector2f(resume.pressed.getTexture()->getSize().x*0.5, resume.pressed.getTexture()->getSize().y*0.5));
	resume.pressed.setPosition(512, 380 - 110);
	resume.Curr = &resume.normal;

	savegame._normal.loadFromFile("Res/save.png");
	savegame.normal.setTexture(savegame._normal);
	savegame.normal.setOrigin(Vector2f(savegame.normal.getTexture()->getSize().x*0.5, savegame.normal.getTexture()->getSize().y*0.5));
	savegame.normal.setPosition(512, 380 - 110 + 87);
	savegame._pressed.loadFromFile("Res/saveP.png");
	savegame.pressed.setTexture(savegame._pressed);
	savegame.pressed.setOrigin(Vector2f(savegame.pressed.getTexture()->getSize().x*0.5, savegame.pressed.getTexture()->getSize().y*0.5));
	savegame.pressed.setPosition(512, 380 - 110 + 87);
	savegame.Curr = &savegame.normal;

	loadgame._normal.loadFromFile("Res/Load2.png");
	loadgame.normal.setTexture(loadgame._normal);
	loadgame.normal.setOrigin(Vector2f(loadgame.normal.getTexture()->getSize().x*0.5, loadgame.normal.getTexture()->getSize().y*0.5));
	loadgame.normal.setPosition(512, 380 - 110 + 87 * 2);
	loadgame._pressed.loadFromFile("Res/Load2P.png");
	loadgame.pressed.setTexture(loadgame._pressed);
	loadgame.pressed.setOrigin(Vector2f(loadgame.pressed.getTexture()->getSize().x*0.5, loadgame.pressed.getTexture()->getSize().y*0.5));
	loadgame.pressed.setPosition(512, 380 - 110 + 87 * 2);
	loadgame.Curr = &loadgame.normal;

	quit._normal.loadFromFile("Res/Quit.png");
	quit.normal.setTexture(quit._normal);
	quit.normal.setOrigin(Vector2f(quit.normal.getTexture()->getSize().x*0.5, quit.normal.getTexture()->getSize().y*0.5));
	quit.normal.setPosition(512, 380 - 110 + 87 * 3);
	quit._pressed.loadFromFile("Res/QuitP.png");
	quit.pressed.setTexture(quit._pressed);
	quit.pressed.setOrigin(Vector2f(quit.pressed.getTexture()->getSize().x*0.5, quit.pressed.getTexture()->getSize().y*0.5));
	quit.pressed.setPosition(512, 380 - 110 + 87 * 3);
	quit.Curr = &quit.normal;

	r._normal.loadFromFile("Res/green.png");
	r.normal.setTexture(r._normal);
	r.normal.setOrigin(Vector2f(r.normal.getTexture()->getSize().x*0.5, r.normal.getTexture()->getSize().y*0.5));
	r.normal.setPosition(945, 685);
	r._pressed.loadFromFile("Res/red.png");
	r.pressed.setTexture(r._pressed);
	r.pressed.setOrigin(Vector2f(r.pressed.getTexture()->getSize().x*0.5, r.pressed.getTexture()->getSize().y*0.5));
	r.pressed.setPosition(945, 685);
	r.Curr = &r.normal;

	l._normal.loadFromFile("Res/green.png");
	l.normal.setTexture(l._normal);
	l.normal.setOrigin(Vector2f(l.normal.getTexture()->getSize().x*0.5, l.normal.getTexture()->getSize().y*0.5));
	l.normal.setPosition(85, 100);
	l._pressed.loadFromFile("Res/red.png");
	l.pressed.setTexture(l._pressed);
	l.pressed.setOrigin(Vector2f(l.pressed.getTexture()->getSize().x*0.5, l.pressed.getTexture()->getSize().y*0.5));
	l.pressed.setPosition(85, 100);
	l.Curr = &l.normal;

	savemenu.t.loadFromFile("Res/SaveScr.png");
	savemenu.s.setTexture(savemenu.t);
	savemenu.s.setOrigin(Vector2f(savemenu.s.getTexture()->getSize().x*0.5, savemenu.s.getTexture()->getSize().y*0.5));
	savemenu.s.setPosition(512, 380);

	loadmenu.t.loadFromFile("Res/LoadScr.png");
	loadmenu.s.setTexture(loadmenu.t);
	loadmenu.s.setOrigin(Vector2f(loadmenu.s.getTexture()->getSize().x*0.5, loadmenu.s.getTexture()->getSize().y*0.5));
	loadmenu.s.setPosition(512, 380);

	font.loadFromFile("Res/font.ttf");
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
bool skipmenu = false;
bool skipsetup = false;
bool paused = false;
bool again = true;
int redlight = 0;
Clock cd;
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

void Resize(Point *&A, int &n) {
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
		Resize(A, n);
		A[n - 1].x = random(pos, pos + mid-CW);
		A[n - 1].y = yrow;
		if (c == 'L' || c == 'l')
			A[n - 1].p = CL[random(0, 3)].s;
		else
			A[n - 1].p = CR[random(0, 3)].s;
		A[n - 1].p.setPosition(A[n - 1].x, A[n - 1].y);
		pos += mid + CW;
	}
}

void Setup() {
	Player.x = 500;
	Player.y = 720;
	Player.p = P[0].s;
	Player.p.setPosition(Player.x, Player.y);

	addCars(R1, cr1, 'R', 615, random(1 + lv,3 + lv));
	addCars(R2, cr2, 'R', 460, random(1 + lv,3 + lv));
	addCars(L3, cl3, 'L', 320, random(1 + lv,3 + lv));
	addCars(L4, cl4, 'L', 200, random(1 + lv,3 + lv));
}

void Reset() {
	if (finished) {
		delete[] finished;
		finished = NULL;
		fn = 0;
	}
	if(R1)
		delete[] R1;
	R1 = NULL;
	cr1 = 0;
	if (R2)
		delete[] R2;
	R2 = NULL;
	cr2 = 0;
	if (L3)
		delete[] L3;
	L3 = NULL;
	cl3 = 0;
	if (L4)
		delete[] L4;
	L4 = NULL;
	cl4 = 0;
}

bool LoadToGame(const char* filepath) {
	ifstream f;
	f.open(filepath, ios::in);
	if (f.fail())
		return false;
	else
		Reset();
	skipsetup = true;
	double x, y;
	int n;
	f >> lv;
	f >> Player.x >> Player.y;
	Player.p = P[1].s;
	Player.p.setPosition(Player.x, Player.y);

	f >> n;
	if (n > 0)
		for (int i = 0; i < n; i++) {
			f >> x;
			f >> y;
			Resize(finished, fn);
			finished[i].x = x;
			finished[i].y = y;

			finished[i].p = P[i].s;

			finished[i].p.setPosition(finished[i].x, finished[i].y);
		}
	
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> x;
		f >> y;
		Resize(R1, cr1);
		R1[i].x = x;
		R1[i].y = y;
		R1[i].p = CR[random(0, 3)].s;
		R1[i].p.setPosition(R1[i].x, R1[i].y);
	}

	f >> n;
	for (int i = 0; i < n; i++) {
		f >> x;
		f >> y;
		Resize(R2, cr2);
		R2[i].x = x;
		R2[i].y = y;

		R2[i].p = CR[random(0, 3)].s;
		R2[i].p.setPosition(R2[i].x, R2[i].y);
	}

	f >> n;
	for (int i = 0; i < n; i++) {
		f >> x;
		f >> y;
		Resize(L3, cl3);
		L3[i].x = x;
		L3[i].y = y;

		L3[i].p = CL[random(0, 3)].s;
		L3[i].p.setPosition(L3[i].x, L3[i].y);
	}

	f >> n;
	for (int i = 0; i < n; i++) {
		f >> x;
		f >> y;
		Resize(L4, cl4);
		L4[i].x = x;
		L4[i].y = y;

		L4[i].p = CL[random(0, 3)].s;
		L4[i].p.setPosition(L4[i].x, L4[i].y);
	}

	f >> redlight;
	return true;
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
		if (Player.x - 1 > 130 && !paused) {
			Player.x -= 8;
			Player.p = P[8 + last].s;
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}
	case Keyboard::D: {
		static int last = 0;
		if (Player.x + 1 < 1024 && !paused) {
			Player.x += 8;
			Player.p = P[4 + last].s;
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}

	case Keyboard::S: {
		static int last = 0;
		if (Player.y + 1 < 760 && !paused) {
			Player.y += 12;
			Player.p = P[last].s;
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}

	case Keyboard::W: {
		static int last = 0;
		if (Player.y - 1 > 0 && !paused) {
			Player.y -= 12;
			Player.p = P[last].s;
			last++;
			if (last >= 4)
				last = 0;
			Player.p.setPosition(Player.x, Player.y);
		}
		break;
	}
	case Keyboard::Escape:
		paused = !paused;
		break;

	default:
		break;
	}
}

void moveAcarR(Point &car) {
	float x = (float)lv / 2;
	if (car.x + 1.2 + x < 1024)
		car.x += (1 + x);
	else {
		car.p = CR[random(0, 3)].s;
		car.x = 0;
	}
	car.p.setPosition(car.x, car.y);
}

void moveAcarL(Point &car) {
	float x = (float)lv / 2;
	if (car.x - 1.2 - x > 0)
		car.x -= (1 + x);
	else {
		car.p = CL[random(0, 3)].s;
		car.x = 1023;
	}
	car.p.setPosition(car.x, car.y);
}

void red_light() {
	if (redlight == 0 && cd.getElapsedTime().asSeconds() >= 8.0f) {	// Ko dừng mỗi 5s
		int i = random(0, 100);
		if (i >= 0 && i <= 25 - lv * 5) {	// 25 - lv*5 % tạo đèn đỏ
			redlight = random(1, 2);
			cd.restart();
			if (redlight == 1)
				r.Curr = &r.pressed;
			else
				l.Curr = &l.pressed;
		}
	}
}

void green_light() {
	if (redlight != 0 && cd.getElapsedTime().asSeconds() >= 3.0f) {	// Dừng 3s
		if (redlight == 1)
			r.Curr = &r.normal;
		else
			l.Curr = &l.normal;
		redlight = 0;
	}
}

void MoveCars() {
	if (redlight != 1) {
		for (int i = 0; i < cr1; i++)
			moveAcarR(R1[i]);
		for (int i = 0; i < cr2; i++)
			moveAcarR(R2[i]);
	}
	if (redlight != 2) {
		for (int i = 0; i < cl3; i++)
			moveAcarL(L3[i]);
		for (int i = 0; i < cl4; i++)
			moveAcarL(L4[i]);
	}
}

void Load_Menu() {
	String savepath;
	Text text;
	text.setFont(font);
	text.setPosition(512 - 120, 340);
	text.setCharacterSize(35);
	text.setFillColor(Color::Black);

	while (true) {
		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::TextEntered)
				if (event.text.unicode >= 49 && event.text.unicode <= 122) {
					if (savepath.getSize() < 10) {
						savepath += event.text.unicode;
						text.setString(savepath);
					}
				}
				else if (event.text.unicode == 8)
					if (savepath.getSize() > 0) {
						savepath.erase(savepath.getSize() - 1);
						text.setString(savepath);
					}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					break;
				else if (event.key.code == Keyboard::Return) {
					if (LoadToGame((savepath.toAnsiString() + ".txt").c_str())) {
						//do something
					}
					break;
				}

				window.clear();
				window.draw(menuBG.s);
				window.draw(title);
				window.draw(*Start.Curr);
				window.draw(*Load.Curr);
				window.draw(*Exit.Curr);
				window.draw(loadmenu.s);
				window.draw(text);
				window.display();
		}
	}
}

void Load_Paused() {
	String savepath;
	Text text;
	text.setFont(font);
	text.setPosition(512 - 120, 340);
	text.setCharacterSize(35);
	text.setFillColor(Color::Black);

	while (true) {
		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::TextEntered)
				if (event.text.unicode >= 49 && event.text.unicode <= 122) {
					if (savepath.getSize() < 15) {
						savepath += event.text.unicode;
						text.setString(savepath);
					}
				}
				else if (event.text.unicode == 8)
					if (savepath.getSize() > 0) {
						savepath.erase(savepath.getSize() - 1);
						text.setString(savepath);
					}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					break;
				else if (event.key.code == Keyboard::Return) {
					if (LoadToGame((savepath.toAnsiString() + ".txt").c_str())) {
						//do something
					}
					break;
				}

				window.clear();
				window.draw(BG.s);
				DrawCars();
				window.draw(*r.Curr);
				window.draw(*l.Curr);
				for (int i = 0; i < fn; i++)
					window.draw(finished[i].p);
				window.draw(Player.p);

				window.draw(p_menu.s);
				window.draw(*resume.Curr);
				window.draw(*savegame.Curr);
				window.draw(*loadgame.Curr);
				window.draw(*quit.Curr);

				window.draw(loadmenu.s);
				window.draw(text);
				window.display();
		}
	}
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
					Load_Menu();
					break;
				}
				else if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					window.close();
					break;
				}
			}
		}

		window.clear();
		window.draw(menuBG.s);
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
		Resize(finished, fn);
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
	lose_track.s.play();
	again = false;
	r_menu.normal.setPosition(70, 83);
	r_menu.pressed.setPosition(70, 83);
	while (true) {
		if (r_menu.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			r_menu.Curr = &r_menu.pressed;
		else
			r_menu.Curr = &r_menu.normal;

		if (retry.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			retry.Curr = &retry.pressed;
		else
			retry.Curr = &retry.normal;

		if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			Exit.Curr = &Exit.pressed;
		else
			Exit.Curr = &Exit.normal;

		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				if (r_menu.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
					break;
				else if (retry.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					skipmenu = true;
					break;
				}
				else if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					window.close();
					break;
				}
			}
		}

		window.clear();
		window.draw(l_menu.s);
		window.draw(*r_menu.Curr);
		window.draw(*retry.Curr);
		window.draw(*Exit.Curr);
		window.display();
	}
}

void Pross_End() {
	// do st
	again = false;
	Win_s.play();
	r_menu.normal.setPosition(595, 695);
	r_menu.pressed.setPosition(595, 695);
	while (true) {
		if (r_menu.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			r_menu.Curr = &r_menu.pressed;
		else
			r_menu.Curr = &r_menu.normal;

		if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			Exit.Curr = &Exit.pressed;
		else
			Exit.Curr = &Exit.normal;

		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				if (r_menu.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
					break;
				else if (Exit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					window.close();
					break;
				}
			}
		}

		window.clear();
		window.draw(w_menu.s);
		window.draw(*r_menu.Curr);
		window.draw(*Exit.Curr);
		window.display();
	}
}

void SaveMenu() {
	String savepath;
	Text text;
	text.setFont(font);
	text.setPosition(512 - 120, 370);
	text.setCharacterSize(35);
	text.setFillColor(Color::Black);
	while (true) {
		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::TextEntered)
				if (event.text.unicode >= 49 && event.text.unicode <= 122) {
					if (savepath.getSize() < 10) {
						savepath += event.text.unicode;
						text.setString(savepath);
					}
				}
				else if (event.text.unicode == 8) 
					if (savepath.getSize() > 0) {
						savepath.erase(savepath.getSize() - 1);
						text.setString(savepath);
					}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape) 
					break;
				else if (event.key.code == Keyboard::Return) {
					ofstream f;
					f.open((savepath.toAnsiString() + ".txt").c_str(), ios::out);

					f << lv << endl;
					f << Player.x << " " << Player.y << endl;

					f << fn << endl;
					for (int i = 0; i < fn; i++)
						f << finished[i].x << " " << finished[i].y << " ";
					f << endl;

					f << cr1 << endl;
					for (int i = 0; i < cr1; i++) 
						f << R1[i].x << " " << R1[i].y << "  ";
					f << endl;

					f << cr2 << endl;
					for (int i = 0; i < cr2; i++)
						f << R2[i].x << " " << R2[i].y << "  ";
					f << endl;

					f << cl3 << endl;
					for (int i = 0; i < cl3; i++) 
						f << L3[i].x << " " << L3[i].y << "  ";
					f << endl;

					f << cl4 << endl;
					for (int i = 0; i < cl4; i++) 
						f << L4[i].x << " " << L4[i].y << "  ";
					f << endl;

					f << redlight << endl;

					break;
				}
				

				window.clear();
				window.draw(BG.s);
				DrawCars();
				window.draw(*r.Curr);
				window.draw(*l.Curr);
				for (int i = 0; i < fn; i++)
					window.draw(finished[i].p);
				window.draw(Player.p);
				window.draw(savemenu.s);
				window.draw(text);
				window.display();
		}
	}
}

void Run_PausedMenu() {
	bool temp = true;
	while (temp) {
		if (resume.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			resume.Curr = &resume.pressed;
		else
			resume.Curr = &resume.normal;

		if (savegame.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			savegame.Curr = &savegame.pressed;
		else
			savegame.Curr = &savegame.normal;

		if (loadgame.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			loadgame.Curr = &loadgame.pressed;
		else
			loadgame.Curr = &loadgame.normal;

		if (quit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			quit.Curr = &quit.pressed;
		else
			quit.Curr = &quit.normal;

		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				paused = !paused;
				break;
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				if (resume.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					paused = !paused;
					break;
				}
				else if (quit.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					window.close();
					break;
				}
				else if (savegame.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					SaveMenu();
					temp = false;
				}
				else if (loadgame.Curr->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					Load_Paused();
					temp = false;
				}
			}
		}

		window.clear();
		window.draw(BG.s);
		DrawCars();
		window.draw(*r.Curr);
		window.draw(*l.Curr);
		for (int i = 0; i < fn; i++)
			window.draw(finished[i].p);
		window.draw(Player.p);

		window.draw(p_menu.s);
		window.draw(*resume.Curr);
		window.draw(*savegame.Curr);
		window.draw(*loadgame.Curr);
		window.draw(*quit.Curr);

		window.display();
	}
}

void Run() {
	city.setLoop(true);
	city.play();

	while (window.isOpen() && !endgame) {
		red_light();
		green_light();
		window.pollEvent(event);
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::KeyPressed)
			Move();

		if (!paused) {
			MoveCars();

			if (CheckLose()) {
				city.stop();
				win = false;
				crashed[0].s.play();
				crashed[1].s.play();
				Player.p = dead.s;
				Player.p.setPosition(Player.x, Player.y);

				window.clear();
				window.draw(BG.s);
				DrawCars();
				window.draw(*r.Curr);
				window.draw(*l.Curr);
				for (int i = 0; i < fn; i++)
					window.draw(finished[i].p);
				window.draw(Player.p);
				window.display();
				while (crashed[1].s.getStatus() != Sound::Stopped) {}
				break;
			}
			if (CheckWin(lv + 1))
				break;
			window.clear();
			window.draw(BG.s);
			DrawCars();
			window.draw(*r.Curr);
			window.draw(*l.Curr);
			for (int i = 0; i < fn; i++)
				window.draw(finished[i].p);
			window.draw(Player.p);
			window.display();
		}
		else
			Run_PausedMenu();

		Sleep(10);
	}
	
	if (window.isOpen())
		if (win)
			if (endgame)
				Pross_End();
			else
				Pross_Win();
		else
			Pross_Lose();

	city.stop();
}

void ResetGame() {
	lv = 0;
	win = false;
	endgame = false;
	again = true;
}

int main() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	srand(time(NULL));
    LoadResources();
	while (window.isOpen()) {
		if (!skipmenu)
			RunMenu();
		else
			skipmenu = false;
		while (again && window.isOpen()) {
			if (!skipsetup)
				Setup();
			else
				skipsetup = false;
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

/*
 http://flamingtext.com/
*/