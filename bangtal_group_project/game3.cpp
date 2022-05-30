#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal.h>
#include <list>

#define INITIAL_PLAYER_X 700
#define INITIAL_PLAYER_Y 80
#define JUMP_POWER 7
#define PLAYER_SPEED 3

using namespace std;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SceneID mapscene;
extern SoundID introbgm;

bool g3_isPlaying = false, g3_isAttack = false;

float attack_anim_time = 3.f;

SceneID g3_scene,g3_scene2,g3_scene3;
ObjectID g3_gomapbutton, g3_restartbutton, g3_endingbutton, g3_deathback, g3_clearback, g3_startbutton, g3_endgame;
ObjectID g3_attack_effect;

class Floor;
class Enemy;
class Player;

list<Floor> floors;
list<Enemy> enemies;
Player* g3_player;


class GameObject {
public:
	int x, y, x_size, y_size;
	ObjectID* gameObject;
	SceneID scene;
	GameObject(int x_, int y_, int xSize, int ySize, const char* c, SceneID scene_) {
		x = x_;
		y = y_;
		x_size = xSize;
		y_size = ySize;
		scene = scene_;
		gameObject = new ObjectID;
		*gameObject = createObject(c, scene, x_,y_,true, 1);
	}
	void setLocation(int x, int y) {
		locateObject(*gameObject, scene, x, y);
	}
	void setLocation(int x, int y, SceneID scene) {
		locateObject(*gameObject, scene, x, y);
	}
	
};

class Floor : public GameObject{
public:
	Floor(int x_, int y_, SceneID scene) :GameObject(x_, y_, 120, 5, "image/game3/floor2.png", scene){
		floors.push_back(*this);
		setLocation(x, y-30);
	}
	Floor(int x_, int y_, int xSize, int ySize, const char* c, SceneID scene) :GameObject(x_, y_, xSize, ySize, c, scene) {
		floors.push_back(*this);
		setLocation(x, y);
	}
};

class Enemy :public GameObject {
public:

	class AttackArea {
	public:
		int x, y, x_size, y_size;
		void setInit (int x, int y, int xSize, int ySize) {
			x = x;
			y = y;
			x_size = xSize;
			y_size = ySize;
		}
	};
	AttackArea attackArea;

	bool isAttack=false;
	int playerDirection = 1; //1:오른쪽, -1:왼
	float attack_time = 10.f;
	ObjectID fire;

	void Update() {
		if (isAttack) {
			printf("isAttack");
			attack_time -= 0.1f;
			if (attack_time < 0) {
				attack_time = 10;
				hideObject(fire);
				isAttack = false;
			}
			else if (attack_time < 5.f)
				fire = createObject("image/game3/fire.png", scene, x+35+(100*playerDirection), y, true, 1);
		}
	}

	Enemy(int x_, int y_, SceneID scene) :GameObject(x_, y_, 70, 77, "image/game3/dragon_left.png", scene) { //fix size
		enemies.push_back(*this);
		attackArea.setInit(x_ - 100, y_, 270, 77);
	}

	void attack() {
		if(!isAttack)
			isAttack = true;

	}
};

class Player:public GameObject {
public:
	int x_direction = 1; //1:오른쪽 -1:왼쪽
	int speed = PLAYER_SPEED;
	float dx = 0, dy = 0;
	bool isGround=false, isJumping=false;

	Player(int x_, int y_, SceneID scene_): GameObject(x_,y_, 58,1, "image/game3/player_right.png", scene_) {
	}
	void setImage(const char* c) {
		setObjectImage(*this->gameObject, c);
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
		if (isJumping||!isGround)
			dy -= 0.1f;
	
		x += dx;
		y += dy;

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


template <class T1, class T2>
//충돌체크
bool checkCollision(T1 ob1, T2* ob2) {
	if (ob1.x + ob1.x_size > ob2->x
		&& ob2->x + ob2->x_size > ob1.x
		&& ob1.y + ob1.y_size > ob2->y
		&& ob2->y + ob2->y_size > ob1.y) {

		printf("x: %d, x: %d, y: %d, y: %d\n", ob1.x, ob2->x, ob1.y, ob2->y);
		return true;
	}
	return false;
}



void g3_settingMap() {
	Floor(-20, 40, 1030, 33, "image/game3/floor1.png", g3_scene);
	Floor(980, 40, 1030, 33, "image/game3/floor1.png", g3_scene);
	Floor(600, 200, g3_scene);
	Floor(740, 200, g3_scene);
	Floor(880, 200, g3_scene);
	Floor(1020, 200, g3_scene);
	Floor(1160, 200, g3_scene);
	Floor(0, 200, g3_scene);
	Floor(140, 200, g3_scene);
	Floor(280, 200, g3_scene);
	Floor(0, 350, g3_scene);


	Enemy(100, 70, g3_scene);
}

void startGame() {
	g3_isPlaying = true;
}

void gameOver() {
	//g3_isPlaying = false;
}


// 마우스콜백함수
void game3_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g3_gomapbutton) {
		hideObject(g3_deathback);
		hideObject(g3_gomapbutton);
		hideObject(g3_restartbutton);
		showObject(g3_startbutton);
		enterScene(mapscene);
		//stopSound(g3_mapbgm);
		playSound(introbgm);
	}
	if (object == g3_restartbutton) {
		hideObject(g3_deathback);
		hideObject(g3_gomapbutton);
		hideObject(g3_restartbutton);
		showObject(g3_startbutton);
	}

	if (object == g3_startbutton) {
		g3_isPlaying = true;
		hideObject(g3_startbutton);
		hideObject(g3_deathback);
		hideObject(g3_gomapbutton);
		hideObject(g3_restartbutton);
	}

	if (object == g3_endingbutton) {
		showObject(g3_startbutton);
		hideObject(g3_clearback);
		hideObject(g3_endingbutton);
		enterScene(g3_scene2);
		//stopSound(g3_mapbgm);
		//playSound(g3_endingbgm);

	}
	if (object == g3_endgame) {
		endGame();
	}
}

//타이머콜백함수
void game3_timerCallback(TimerID timer) {
	setTimer(timer, 0.01f);
	startTimer(timer);

	if (g3_isPlaying) {
		
		g3_player->move();
		g3_player->anim_controll();

		//충돌 검사
		if (!g3_player->isJumping) {
			for (Floor floor : floors) {

				if (checkCollision(floor, g3_player)) {
					g3_player->onGround(true);
					break;
				}
				else {
					g3_player->onGround(false);
				}
				
			}
		}
		for (Enemy enemy : enemies) {
			if (checkCollision(enemy, g3_player)) {
				printf("gmaeOver\n");
				gameOver();
			}
			
			//용 공격 가동 범위 체크
			if (checkCollision(enemy.attackArea, g3_player)) {
				printf("attackCollision\n");
				//enemy.attack();
			}

			enemy.Update();
		}
		
	}
}

//사운드콜백함수
void game3_soundCallback(SoundID sound) {

}

//키보드콜백함수
void game3_keyboardCallback(KeyCode code, KeyState state) {
	
	if (nowgamenum == 3 && g3_isPlaying) {
		//움직임
		if (code == KeyCode::KEY_UP_ARROW &&g3_player->isGround&&state==KeyState::KEY_PRESSED) {
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
				locateObject(g3_attack_effect, g3_scene, g3_player->x + 70, g3_player->y);
			}
			else {
				g3_player->setImage("image/game3/player_attack_left.png");
				setObjectImage(g3_attack_effect, "image/game3/attack_left1.png");
				locateObject(g3_attack_effect, g3_scene, g3_player->x - 90, g3_player->y);
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
	g3_scene2 = createScene("game3", "image/game3/background.png");
	g3_scene3 = createScene("game3", "image/game3/background.png");

	//UI button
	g3_clearback = createObject("image/clear.png", g3_scene, 270, 300, false, 1.5f);
	g3_deathback = createObject("image/gameover.png", g3_scene, 270, 300, false, 1.5f);
	g3_restartbutton = createObject("image/restart.png", g3_scene, 700, 200, false, 1.3f);
	g3_startbutton = createObject("image/start.png", g3_scene, 450, 300, true, 0.8f);
	g3_endingbutton = createObject("image/ending.png", g3_scene, 500, 100, false, 1.3f);
	g3_endgame = createObject("image/end.png", g3_scene2, 550, 450, false, 0.8f);
	g3_gomapbutton = createObject("image/gomap.png", g3_scene, 300, 200, false, 1.3f);


	//맵 세팅
	g3_settingMap();

	//플레이어
	g3_player = new Player(INITIAL_PLAYER_X, INITIAL_PLAYER_Y, g3_scene);
	g3_player->x = INITIAL_PLAYER_X;
	g3_player->y = INITIAL_PLAYER_Y;
	
	g3_attack_effect = createObject("image/game3/attack_right1.png", g3_scene,0,0,false,0.3f);


	

	TimerID timer = createTimer(0.01f);
	startTimer(timer);

	
}