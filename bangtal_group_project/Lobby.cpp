#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>

SceneID lobbyscene, mapscene;
ObjectID startbutton, portalbutton[5];
// 0�� ������, 1�� ���ʾƷ�, 2�� �����ʾƷ�, 3�� ��������, 4�� ���
int portalX[5] = { 240, 305, 920, 930, 580 };
int portalY[5] = { 500, 170, 140, 490, 310 };

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);




// ���콺�ݹ��Լ�
void lobby_mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startbutton) {
		enterScene(mapscene);
	}
}

//Ÿ�̸��ݹ��Լ�
void lobby_timerCallback(TimerID timer) {

}

//�����ݹ��Լ�
void lobby_soundCallback(SoundID sound) {

}

//Ű�����ݹ��Լ�
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