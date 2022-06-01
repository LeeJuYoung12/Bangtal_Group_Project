#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal.h>
#include <list>

#define INITIAL_PLAYER_X 600
#define INITIAL_PLAYER_Y 80
#define JUMP_POWER 7
#define PLAYER_SPEED 1
#define FIRE_ANIM_TIME 20

using namespace std;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SceneID mapscene, g4_scene;
extern SoundID introbgm;
extern bool g3_cleared;

bool g3_isPlaying = false, g3_isAttack = false;

float attack_anim_time = 3.f;

int nowStageNum = 0;

SceneID g3_scene;
ObjectID g3_gomapbutton, g3_restartbutton, g3_deathback, g3_clearback, g3_startbutton, g3_endgame;
ObjectID g3_attack_effect;
TimerID g3_timer;
SoundID g3_mapbgm, g3_dragonbgm;

class Floor;
class Enemy;
class Player;
class GameObject;
class Thorn;

list<Floor*> floors[3];
list<Enemy*> enemies[3];
list<Thorn*> thorn[3];
Player* g3_player;
GameObject* fire;
GameObject* g3_portal;

void gameOver();

template <class T1, class T2>
//충돌체크
bool checkCollision(T1* ob1, T2* ob2) {
	if (ob1->x + ob1->x_size > ob2->x
		&& ob2->x + ob2->x_size > ob1->x
		&& ob1->y + ob1->y_size > ob2->y
		&& ob2->y + ob2->y_size > ob1->y) {

		return true;
	}
	return false;
}


class GameObject {
public:
	float x, y, x_size, y_size;
	bool state;
	ObjectID* gameObject;
	SceneID scene;
	GameObject(int x_, int y_, int xSize, int ySize, const char* c, SceneID scene_) {
		x = x_;
		y = y_;
		x_size = xSize;
		y_size = ySize;
		scene = scene_;
		gameObject = new ObjectID;
		*gameObject = createObject(c, scene, x, y, true, 1);
	}
	void setLocation(int x, int y) {
		locateObject(*gameObject, scene, x, y);
		x = x; y = y;
	}
	void setLocation(int x, int y, SceneID scene) {
		locateObject(*gameObject, scene, x, y);
		this->x = x; this->y = y;
	}
	void setImage(const char* c) {
		setObjectImage(*gameObject, c);
	}
	void setState(bool b) { //true 면 씬에서 on, false면 off
		if (b) {
			showObject(*gameObject);
		}
		else {
			hideObject(*gameObject);
		}
		state = b;
	}
};

class Player :public GameObject {
public:
	int x_direction = 1; //1:오른쪽 -1:왼쪽
	int speed = PLAYER_SPEED;
	float dx = 0, dy = 0;
	bool isGround = false, isJumping = false;

	Player(int x_, int y_, SceneID scene_) : GameObject(x_, y_, 58, 15, "image/game3/player_right.png", scene_) {
	}

	void anim_controll() {
		if (g3_isAttack) {
			attack_anim_time -= 0.1f;
			if (attack_anim_time < 0) {
				attack_anim_time = 3;
				hideObject(g3_attack_effect);
				g3_isAttack = false;

				if (x_direction == 1) {
					setObjectImage(*gameObject, "image/game3/player_right.png");
				}
				else {
					setObjectImage(*gameObject, "image/game3/player_left.png");
				}
			}
		}
	}

	void move() {
		if (isJumping || !isGround)
			dy -= 0.1f;

		x += dx;
		y += dy;

		if (x < 0)
			x = 0;
		else if (x > 1200)
			x = 1200;

		if (dy < 0 && isJumping) {
			isJumping = false;
		}
		locateObject(*gameObject, scene, x, y);
	}

	void onGround(bool on) {
		if (on) {
			isJumping = false;
			isGround = true;
			dy = 0;
		}
		else {
			isGround = false;
			isJumping = true;
		}
	}
};

class Floor : public GameObject {
public:
	Floor(int x_, int y_, SceneID scene) :GameObject(x_, y_, 120, 35, "image/game3/floor2.png", scene) {
		setLocation(x, y);
	}
	Floor(int x_, int y_, int xSize, int ySize, const char* c, SceneID scene) :GameObject(x_, y_, xSize, ySize, c, scene) {
		setLocation(x, y);
	}

};

class Thorn :public GameObject {
public:
	Thorn(int x_, int y_) :GameObject(x_, y_, 67, 35, "image/game3/thorn.png", g3_scene) {
		setLocation(x_, y_);
	}
};

class AttackArea {
public:
	int x = 0, y = 0, x_size = 0, y_size = 0;

	AttackArea(int x_, int y_, int xSize, int ySize) {
		x = x_;
		y = y_;
		x_size = xSize;
		y_size = ySize;
	}
	void setInit(int x_, int y_, int xSize, int ySize) {
		x = x_;
		y = y_;
		x_size = xSize;
		y_size = ySize;
	}
};

class Enemy :public GameObject {
public:
	bool isAttack = false;
	int direction = 1, hp = 2; //1:오른쪽, -1:왼
	float attack_time = FIRE_ANIM_TIME;
	int moveRange_left, moveRange_right;


	void move() {
		if (!isAttack) {
			if (x * 100 < moveRange_left) {
				direction = 1;
				setImage("image/game3/dragon_right.png");
			}
			else if (x * 100 > moveRange_right) {
				direction = -1;
				setImage("image/game3/dragon_left.png");
			}

			x += direction * 0.1f;
			locateObject(*gameObject, scene, x, y);

		}

	}

	void Update() {
		if (isAttack && state) {
			attack_time -= 0.1f;
			if (attack_time < 0) {
				attack_time = FIRE_ANIM_TIME;
				isAttack = false;
				hideObject(*fire->gameObject);
			}
			else if (attack_time < FIRE_ANIM_TIME / 3 * 2) {
				showObject(*fire->gameObject);
				fire->setLocation(x - 25 + (direction * 100), y, scene);
				if (checkCollision(fire, g3_player)) {
					gameOver();
				}
			}
		}
		move();
	}


	Enemy(int x_, int y_, int left, int right, SceneID scene) :GameObject(x_, y_, 69, 23, "image/game3/dragon_right.png", scene) {
		moveRange_left = left * 100;
		moveRange_right = right * 100;
	}

	void attack() {
		if (!isAttack)
			isAttack = true;

	}
};

void g3_changeStage(int n) {
	g3_portal->setState(false);

	if (nowStageNum == 1) {
		locateObject(g3_gomapbutton, g3_scene, 500, 200);
		showObject(g3_clearback);
		showObject(g3_gomapbutton);
		g3_isPlaying = false;
		g3_cleared = true;
	}
	else {
		for (Floor* floor : floors[n]) {
			floor->setState(false);
		}
		for (Enemy* enemy : enemies[n]) {
			enemy->setState(false);
		}
		for (Floor* floor : floors[n + 1]) {
			floor->setState(true);
		}
		for (Enemy* enemy : enemies[n + 1]) {
			enemy->setState(true);
		}
		for (Thorn* thorn : thorn[n]) {
			thorn->setState(false);
		}
		for (Thorn* thorn : thorn[n + 1]) {
			thorn->setState(true);
		}

		nowStageNum++;
	}
	printf("nowStageNum : %d", nowStageNum);
}


void gameOver() {
	g3_isPlaying = false;

	stopTimer(g3_timer);

	showObject(g3_deathback);
	showObject(g3_gomapbutton);
	showObject(g3_restartbutton);

	for (int i = 0; i < 3; i++) {
		for (Floor* floor : floors[i]) {
			if (i == 0) {
				floor->setState(true);
			}
			else {
				floor->setState(false);
			}
		}

		for (Enemy* enemy : enemies[i]) {
			if (i == 0) {
				enemy->setState(true);
				enemy->isAttack = false;
				enemy->attack_time = FIRE_ANIM_TIME;
			}
			else {
				enemy->setState(false);
				enemy->isAttack = false;
				enemy->attack_time = FIRE_ANIM_TIME;
			}
		}
		for (Thorn* thorn : thorn[i]) {
			if (i == 0) {
				thorn->setState(true);
			}
			else {
				thorn->setState(false);
			}
		}
	}
}


void g3_settingMap() {

	floors[0].push_back(new Floor(-20, 40, 1030, 33, "image/game3/floor1.png", g3_scene));
	floors[0].push_back(new Floor(980, 40, 1030, 33, "image/game3/floor1.png", g3_scene));
	floors[0].push_back(new Floor(600, 200, g3_scene));
	floors[0].push_back(new Floor(740, 200, g3_scene));
	floors[0].push_back(new Floor(880, 200, g3_scene));
	floors[0].push_back(new Floor(1020, 200, g3_scene));
	floors[0].push_back(new Floor(1160, 200, g3_scene));
	floors[0].push_back(new Floor(0, 200, g3_scene));
	floors[0].push_back(new Floor(140, 200, g3_scene));
	floors[0].push_back(new Floor(280, 200, g3_scene));
	floors[0].push_back(new Floor(0, 370, g3_scene));
	floors[0].push_back(new Floor(140, 370, g3_scene));
	floors[0].push_back(new Floor(700, 370, g3_scene));
	floors[0].push_back(new Floor(1100, 370, g3_scene));
	floors[0].push_back(new Floor(170, 500, g3_scene));
	floors[0].push_back(new Floor(500, 500, g3_scene));
	floors[0].push_back(new Floor(800, 500, g3_scene));

	enemies[0].push_back(new Enemy(100, 233, 0, 330, g3_scene));
	enemies[0].push_back(new Enemy(800, 233, 600, 1200, g3_scene));
	enemies[0].push_back(new Enemy(20, 403, 0, 190, g3_scene));
	enemies[0].push_back(new Enemy(820, 533, 800, 870, g3_scene));


	floors[1].push_back(new Floor(-20, 40, 1030, 33, "image/game3/floor1.png", g3_scene));
	floors[1].push_back(new Floor(980, 40, 1030, 33, "image/game3/floor1.png", g3_scene));
	floors[1].push_back(new Floor(140, 200, g3_scene));
	floors[1].push_back(new Floor(280, 200, g3_scene));
	floors[1].push_back(new Floor(250, 370, g3_scene));
	floors[1].push_back(new Floor(390, 370, g3_scene));
	floors[1].push_back(new Floor(200, 570, g3_scene));
	floors[1].push_back(new Floor(700, 260, g3_scene));
	floors[1].push_back(new Floor(800, 400, g3_scene));
	floors[1].push_back(new Floor(960, 500, g3_scene));
	floors[1].push_back(new Floor(1100, 500, g3_scene));


	enemies[1].push_back(new Enemy(260, 403, 250, 440, g3_scene));
	enemies[1].push_back(new Enemy(230, 603, 200, 250, g3_scene));
	enemies[1].push_back(new Enemy(160, 233, 140, 330, g3_scene));
	enemies[1].push_back(new Enemy(970, 533, 960, 1200, g3_scene));

	thorn[1].push_back(new Thorn(0, 73));
	thorn[1].push_back(new Thorn(69, 73));
	thorn[1].push_back(new Thorn(140, 233));
	thorn[1].push_back(new Thorn(209, 233));
	thorn[1].push_back(new Thorn(300, 403));
	thorn[1].push_back(new Thorn(702, 295));



	for (int i = 0; i < 3; i++) {
		for (Floor* floor : floors[i]) {
			if (i == 0) {
				floor->setState(true);
			}
			else {
				floor->setState(false);
			}
		}

		for (Enemy* enemy : enemies[i]) {
			if (i == 0) {
				enemy->setState(true);
				enemy->isAttack = false;
				enemy->attack_time = FIRE_ANIM_TIME;
			}
			else {
				enemy->setState(false);
				enemy->isAttack = false;
				enemy->attack_time = FIRE_ANIM_TIME;
			}
		}
		for (Thorn* thorn : thorn[i]) {
			if (i == 0) {
				thorn->setState(true);
			}
			else {
				thorn->setState(false);
			}
		}

	}
}

void startGame() {
	nowStageNum = 0;
	for (int i = 0; i < 3; i++) {
		for (Floor* floor : floors[i]) {
			if (i == 0) {
				floor->setState(true);
			}
			else {
				floor->setState(false);
			}
		}

		for (Enemy* enemy : enemies[i]) {
			if (i == 0) {
				enemy->setState(true);
				enemy->isAttack = false;
				enemy->attack_time = FIRE_ANIM_TIME;
			}
			else {
				enemy->setState(false);
				enemy->isAttack = false;
				enemy->attack_time = FIRE_ANIM_TIME;
			}
			enemy->hp = 2;
		}
		for (Thorn* thorn : thorn[i]) {
			if (i == 0) {
				thorn->setState(true);
			}
			else {
				thorn->setState(false);
			}
		}

	}

	g3_portal->setState(false);

	setTimer(g3_timer, 0.01f);
	startTimer(g3_timer);
	g3_isPlaying = true;

	g3_player->setLocation(INITIAL_PLAYER_X, INITIAL_PLAYER_Y, g3_scene);
	locateObject(g3_attack_effect, g3_scene, 0, 0);

	hideObject(*fire->gameObject);
	fire->setLocation(0, 0, g3_scene);

}



// 마우스콜백함수
void game3_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g3_gomapbutton) {
		hideObject(g3_deathback);
		hideObject(g3_gomapbutton);
		hideObject(g3_restartbutton);
		showObject(g3_startbutton);
		enterScene(mapscene);
		hideObject(g3_clearback);
		//stopSound(g3_mapbgm);
		stopSound(g3_mapbgm);
		playSound(introbgm);
		g3_isPlaying = false;
		locateObject(g3_gomapbutton, g3_scene, 300, 200);

	}
	if (object == g3_restartbutton) {
		hideObject(g3_deathback);
		hideObject(g3_gomapbutton);
		hideObject(g3_restartbutton);
		startGame();
	}

	if (object == g3_startbutton) {
		g3_isPlaying = true;
		hideObject(g3_startbutton);
		hideObject(g3_deathback);
		hideObject(g3_gomapbutton);
		hideObject(g3_restartbutton);
		startGame();
	}


	if (object == g3_endgame) {
		endGame();
	}
}

//타이머콜백함수
void game3_timerCallback(TimerID timer) {
	setTimer(g3_timer, 0.01f);
	startTimer(g3_timer);

	if (g3_isPlaying) {

		g3_player->move();
		g3_player->anim_controll();

		//충돌 검사
		if (!g3_player->isJumping) {
			for (Floor* floor : floors[nowStageNum]) {

				if (checkCollision(floor, g3_player)) {
					g3_player->onGround(true);
					break;
				}
				else {
					g3_player->onGround(false);
				}

			}
		}

		for (Thorn* thorn : thorn[nowStageNum]) {
			if (checkCollision(thorn, g3_player)) {
				gameOver();
			}
		}

		bool dragonExist = false;

		for (Enemy* enemy : enemies[nowStageNum]) {
			if (enemy->state) {
				dragonExist = true;
				if (checkCollision(enemy, g3_player)) {
					printf("gameOver\n");
					gameOver();
				}
				AttackArea a_(enemy->x - 100, enemy->y, 270, 77);
				AttackArea* a = &a_;

				//용 공격 가동 범위 체크
				if (checkCollision((a), g3_player)) {

					enemy->attack();

					if (enemy->x > g3_player->x) {
						enemy->direction = -1;
						enemy->setImage("image/game3/dragon_left.png");
						setObjectImage(*enemy->gameObject, "image/game3/dragon_left.png");

						fire->setImage("image/game3/fire_left.png");
					}
					else {
						enemy->direction = 1;
						setObjectImage(*enemy->gameObject, "image/game3/dragon_right.png");
						fire->setImage("image/game3/fire_right.png");
					}
					break;
				}
			}
			enemy->Update();
		}
		//용 다 죽였을 때
		if (dragonExist == false) {
			if (!g3_portal->state) {
				g3_portal->setState(true);
			}
			else if (checkCollision(g3_portal, g3_player)) {

				g3_changeStage(nowStageNum);
			}
		}

	}
}

//사운드콜백함수
void game3_soundCallback(SoundID sound) {
	if (sound == g3_mapbgm) {
		playSound(g3_mapbgm);
	}
}

//키보드콜백함수
void game3_keyboardCallback(KeyCode code, KeyState state) {

	if (nowgamenum == 3 && g3_isPlaying) {
		//움직임
		if (code == KeyCode::KEY_UP_ARROW && g3_player->isGround && state == KeyState::KEY_PRESSED) {
			g3_player->onGround(false);
			g3_player->dy += JUMP_POWER;
		}
		if (code == KeyCode::KEY_RIGHT_ARROW) {
			g3_player->x_direction = 1;
			setObjectImage(*g3_player->gameObject, "image/game3/player_right.png");

			g3_player->dx += (state == KeyState::KEY_PRESSED ? g3_player->speed : -g3_player->speed);
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {
			g3_player->x_direction = -1;
			setObjectImage(*g3_player->gameObject, "image/game3/player_left.png");
			g3_player->dx -= (state == KeyState::KEY_PRESSED ? g3_player->speed : -g3_player->speed);
		}

		//공격
		if (code == KeyCode::KEY_SPACE && !g3_isAttack && state == KeyState::KEY_PRESSED) {
			g3_isAttack = true;
			if (g3_player->x_direction == 1) {
				g3_player->setImage("image/game3/player_attack_right.png");
				setObjectImage(g3_attack_effect, "image/game3/attack_right1.png");

			}
			else {
				g3_player->setImage("image/game3/player_attack_left.png");
				setObjectImage(g3_attack_effect, "image/game3/attack_left1.png");
			}
			locateObject(g3_attack_effect, g3_scene, g3_player->x + 25 + (g3_player->x_direction * 90), g3_player->y);

			AttackArea a_(g3_player->x + 25 + (g3_player->x_direction * 90), g3_player->y, 20, 50);

			AttackArea* a = &a_;
			for (Enemy* enemy : enemies[nowStageNum]) {
				if (checkCollision(enemy, a)) {
					enemy->hp -= 1;
					if (enemy->hp <= 0) {
						enemy->setState(false);
					}
					printf("%d", enemy->hp);
				}
			}

			showObject(g3_attack_effect);


		}
	}
	else if (nowgamenum == 3 && !g3_isPlaying) {
		if (code == KeyCode::KEY_RIGHT_ARROW) {
			g3_player->x_direction = 1;

			g3_player->dx += (state == KeyState::KEY_PRESSED ? g3_player->speed : -g3_player->speed);
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {
			g3_player->x_direction = -1;
			g3_player->dx -= (state == KeyState::KEY_PRESSED ? g3_player->speed : -g3_player->speed);
		}
	}
}

void game3_main() {
	g3_scene = createScene("game3", "image/game3/background.png");

	g3_settingMap();


	//플레이어
	g3_player = new Player(INITIAL_PLAYER_X, INITIAL_PLAYER_Y, g3_scene);
	g3_player->x = INITIAL_PLAYER_X;
	g3_player->y = INITIAL_PLAYER_Y;

	g3_portal = new GameObject(INITIAL_PLAYER_X, INITIAL_PLAYER_Y - 20, 80, 80, "image/game3/portal.png", g3_scene);
	scaleObject(*g3_portal->gameObject, 0.15f);
	g3_portal->setState(false);

	g3_attack_effect = createObject("image/game3/attack_right1.png", g3_scene, 0, 0, false, 0.3f);

	fire = new GameObject(0, 0, 120, 90, "image/game3/fire_right.png", g3_scene);
	hideObject(*fire->gameObject);


	//UI button
	g3_clearback = createObject("image/clear.png", g3_scene, 270, 300, false, 1.5f);
	g3_deathback = createObject("image/gameover.png", g3_scene, 270, 300, false, 1.5f);
	g3_restartbutton = createObject("image/restart.png", g3_scene, 700, 200, false, 1.3f);
	g3_startbutton = createObject("image/start.png", g3_scene, 450, 300, true, 0.8f);
	g3_endgame = createObject("image/end.png", g3_scene, 550, 450, false, 0.8f);
	g3_gomapbutton = createObject("image/gomap.png", g3_scene, 300, 200, false, 1.3f);
	


	g3_timer = createTimer(0.01f);
	startTimer(g3_timer);

	g3_mapbgm = createSound("sound/game3/g3_mapsound.mp3");
	g3_dragonbgm = createSound("sound/game3/dragon.mp3");
}