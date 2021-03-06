#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern SceneID g1_scene, g2_scene, g3_scene, g4_scene, g5_scene;
extern SoundID g1_mapbgm, g2_mapbgm, g3_mapbgm, g4_mapbgm, g5_mapbgm;

SceneID lobbyscene, mapscene;
ObjectID startbutton, endbutton, portalbutton[5];
ObjectID explain[5];
SoundID introbgm;
TimerID lobby_update_t;
// 0가 왼쪽위, 1이 왼쪽아래, 2가 오른쪽아래, 3이 오른쪽위, 4가 가운데
int portalX[5] = { 600, 470,420, 350, 400};
int portalY[5] = { 60, 150, 270,370, 580};
//게임 위치확인 (함수꼬이지 않게 하는용) 0은 로비 1,2,3,4,5 는 게임
int nowgamenum = 0;

bool g1_cleared = false, g2_cleared = false, g3_cleared = false, g4_cleared = false, g5_cleared = false; //g5가 2번쨰맵
bool lobby_check1 = true, lobby_check2 = true, lobby_check3 = true, lobby_check4 = true;


// 마우스콜백함수
void lobby_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startbutton) {
		enterScene(mapscene);
	}

	else if (object == portalbutton[0]) {
		showObject(explain[0]);

	}

	else if (object == portalbutton[1]&&g1_cleared) {
		showObject(explain[1]);

	}
	else if (object == portalbutton[2]&&g5_cleared) {
		showObject(explain[2]);

	}

	else if (object == portalbutton[3]&& g2_cleared) {
		showObject(explain[3]);

	}

	else if (object == portalbutton[4]&&g3_cleared){
		showObject(explain[4]);
	
	}

	else if (object == explain[0]) {
		enterScene(g1_scene);
		hideObject(explain[0]);
		stopSound(introbgm);
		playSound(g1_mapbgm);
		nowgamenum = 1;

	}
	else if (object == explain[1]) {
		enterScene(g5_scene);
		hideObject(explain[1]);
		stopSound(introbgm);
		playSound(g5_mapbgm);
		nowgamenum = 5;

	}
	else if (object == explain[2]) {
		enterScene(g2_scene);
		hideObject(explain[2]);
		stopSound(introbgm);
		playSound(g2_mapbgm);
		nowgamenum = 2;

	}
	else if (object == explain[3]) {
		enterScene(g3_scene);
		hideObject(explain[3]);
		stopSound(introbgm);
		playSound(g3_mapbgm);
		nowgamenum = 3;

	}
	else if (object == explain[4]) {
		enterScene(g4_scene);
		hideObject(explain[4]);
		stopSound(introbgm);
		playSound(g4_mapbgm);
		nowgamenum = 4;
	
	}

	else if (object == endbutton) {
		endGame();
	}
	
}

//타이머콜백함수
void lobby_timerCallback(TimerID timer) {
	if (timer == lobby_update_t) {
		if (g1_cleared&&lobby_check1) {
			lobby_check1 = false;
			setObjectImage(portalbutton[1], "image/portal.png");
		}
		if (g5_cleared&& lobby_check2) {
			lobby_check2 = false;
			setObjectImage(portalbutton[2], "image/portal.png");
		}
		if (g2_cleared&& lobby_check3) {
			lobby_check3 = false;
			setObjectImage(portalbutton[3], "image/portal.png");
		}
		if (g3_cleared && lobby_check4) {
			lobby_check4 = false;
			setObjectImage(portalbutton[4], "image/portal.png");
		}
		setTimer(lobby_update_t, 0.01f);
		startTimer(lobby_update_t);
	}
}

//사운드콜백함수
void lobby_soundCallback(SoundID sound) {
	if (sound == introbgm) {
		playSound(introbgm);
	}
}

//키보드콜백함수
void lobby_keyboardCallback(KeyCode code, KeyState state) {

}

void lobby_main() {
	
	lobbyscene = createScene("lobby", "image/startback.png");
	mapscene = createScene("map", "image/map.png");

	startbutton = createObject("image/start.png", lobbyscene, 150, 250, true, 0.7f);
	endbutton = createObject("image/end.png", lobbyscene, 150, 150, true, 0.7f);

	for (int i = 0; i < 5; i++) {
		portalbutton[i] = createObject("image/portal2.png", mapscene, portalX[i], portalY[i], true, 1.1f);
	}
	setObjectImage(portalbutton[0], "image/portal.png");

	introbgm = createSound("sound/lobby/intro.mp3");
	playSound(introbgm);

	lobby_update_t = createTimer(0.01f);
	startTimer(lobby_update_t);

	explain[0] = createObject("image/ex1.png", mapscene, 250, 150, false, 1.f);
	explain[1] = createObject("image/ex2.png", mapscene, 250, 150, false, 1.f);
	explain[2] = createObject("image/ex3.png", mapscene, 250, 150, false, 1.f);
	explain[3] = createObject("image/ex4.png", mapscene, 250, 150, false, 1.f);
	explain[4] = createObject("image/ex5.png", mapscene, 250, 150, false, 1.f);
}