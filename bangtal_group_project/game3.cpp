#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal.h>
#include <list>

#define INITIAL_PLAYER_X 700
#define INITIAL_PLAYER_Y 80

using namespace std;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SceneID mapscene;
extern SoundID introbgm;

bool g3_isPlaying = true;

int g3_player_x, g3_player_y;

SceneID g3_scene,g3_scene2,g3_scene3;
ObjectID g3_gomapbutton, g3_restartbutton, g3_endingbutton, g3_deathback, g3_clearback, g3_startbutton, g3_endgame;
ObjectID g3_player;

class GameObject {
public:
	int x, y, x_size, y_size;
	const char* tag;
	GameObject(int x_, int y_, int xSize, int ySize, const char* tag_) {
		x = x_;
		y = y_;
		x_size = xSize;
		y_size = ySize;
		tag = tag_;
	}
};


list<GameObject> gameObject;

void createGameObject(const char* c, SceneID scene, int x, int y, int x_size, int y_size,const char* tag_) {
	createObject(c, scene, x, y, true, 1);

	GameObject ob(x, y, x_size, y_size, tag_);

	gameObject.push_back(ob);
}


//충돌체크
bool checkCollision(int x, int y, int rx, int ry, float x_size, float y_size) {

	if ((rx <= x && x <= (rx + x_size)) && (ry <= y && y <= (ry + y_size))) {
		return true;
	}
	else {
		return false;
	}
}


void g3_settingMap() {
	createGameObject("image/game3/floor1.png", g3_scene, -20, 40, 1030, 33, "floor");
	createGameObject("image/game3/floor1.png", g3_scene, 980, 40, 1000, 40, "floor");
}

void startGame() {
	g3_isPlaying = true;
}

void gameOver() {
	g3_isPlaying = false;
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
		
	}
}

//사운드콜백함수
void game3_soundCallback(SoundID sound) {

}

//키보드콜백함수
void game3_keyboardCallback(KeyCode code, KeyState state) {

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

	//플레이어
	g3_player= createObject("image/game3/player_right.png", g3_scene, INITIAL_PLAYER_X, INITIAL_PLAYER_Y, true, 0.7f);


	//맵 세팅
	g3_settingMap();

	TimerID timer = createTimer(0.01f);
	startTimer(timer);

	
}