#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>

//외부변수 선언
extern SceneID lobbyscene;


//외부함수 선언
extern void lobby_main();
extern void lobby_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void lobby_timerCallback(TimerID timer);
extern void lobby_soundCallback(SoundID sound);
extern void lobby_keyboardCallback(KeyCode code, KeyState state);


//물체 생성함수
ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size) {
	ObjectID object = createObject(name);
	locateObject(object, scene, x, y);
	scaleObject(object, size);
	if (shown) {
		showObject(object);
	}
	return object;
}

// 마우스콜백함수
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	lobby_mouseCallback(object, x, y, action);
}

//타이머콜백함수
void timerCallback(TimerID timer) {

	lobby_timerCallback(timer);
}

//사운드콜백함수
void soundCallback(SoundID sound) {

	lobby_soundCallback(sound);
}

//키보드콜백함수
void keyboardCallback(KeyCode code, KeyState state) {

	lobby_keyboardCallback(code, state);
}


int main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);	

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setSoundCallback(soundCallback);
	setKeyboardCallback(keyboardCallback);

	lobby_main();

	startGame(lobbyscene);
}