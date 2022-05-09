#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal.h>

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;

SceneID g3_scene;

// 마우스콜백함수
void game3_mouseCallback(ObjectID object, int x, int y, MouseAction action) {


}

//타이머콜백함수
void game3_timerCallback(TimerID timer) {

}

//사운드콜백함수
void game3_soundCallback(SoundID sound) {

}

//키보드콜백함수
void game3_keyboardCallback(KeyCode code, KeyState state) {

}

void game3_main() {

}