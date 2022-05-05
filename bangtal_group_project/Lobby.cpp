#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>

SceneID lobbyscene, mapscene;
ObjectID startbutton, portalbutton[5];
// 0가 왼쪽위, 1이 왼쪽아래, 2가 오른쪽아래, 3이 오른쪽위, 4가 가운데
int portalX[5] = { 240, 305, 920, 930, 580 };
int portalY[5] = { 500, 170, 140, 490, 310 };

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);




// 마우스콜백함수
void lobby_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startbutton) {
		enterScene(mapscene);
	}
}

//타이머콜백함수
void lobby_timerCallback(TimerID timer) {

}

//사운드콜백함수
void lobby_soundCallback(SoundID sound) {

}

//키보드콜백함수
void lobby_keyboardCallback(KeyCode code, KeyState state) {

}

void lobby_main() {
	
	lobbyscene = createScene("lobby", "image/startback.png");
	mapscene = createScene("map", "image/map.png");

	startbutton = createObject("image/start.png", lobbyscene, 480, 200, true, 1.0f);
	
	for (int i = 0; i < 5; i++) {
		createObject("image/portal.png", mapscene, portalX[i], portalY[i], true, 0.2f);
	}
}