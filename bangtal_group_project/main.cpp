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

extern void game1_main();
extern void game1_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void game1_timerCallback(TimerID timer);
extern void game1_soundCallback(SoundID sound);
extern void game1_keyboardCallback(KeyCode code, KeyState state);

extern void game2_main();
extern void game2_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void game2_timerCallback(TimerID timer);
extern void game2_soundCallback(SoundID sound);
extern void game2_keyboardCallback(KeyCode code, KeyState state);

extern void game3_main();
extern void game3_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void game3_timerCallback(TimerID timer);
extern void game3_soundCallback(SoundID sound);
extern void game3_keyboardCallback(KeyCode code, KeyState state);

extern void game4_main();
extern void game4_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void game4_timerCallback(TimerID timer);
extern void game4_soundCallback(SoundID sound);
extern void game4_keyboardCallback(KeyCode code, KeyState state);

extern void game5_main();
extern void game5_mouseCallback(ObjectID object, int x, int y, MouseAction action);
extern void game5_timerCallback(TimerID timer);
extern void game5_soundCallback(SoundID sound);
extern void game5_keyboardCallback(KeyCode code, KeyState state);


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
	game1_mouseCallback(object, x, y, action);
	game2_mouseCallback(object, x, y, action);
	game3_mouseCallback(object, x, y, action);
	game4_mouseCallback(object, x, y, action);
	game5_mouseCallback(object, x, y, action);
}

//타이머콜백함수
void timerCallback(TimerID timer) {

	lobby_timerCallback(timer);
	game1_timerCallback(timer);
	game2_timerCallback(timer);
	game3_timerCallback(timer);
	game4_timerCallback(timer);
	game5_timerCallback(timer);
}

//사운드콜백함수
void soundCallback(SoundID sound) {

	lobby_soundCallback(sound);
	game1_soundCallback(sound);
	game2_soundCallback(sound);
	game3_soundCallback(sound);
	game4_soundCallback(sound);
	game5_soundCallback(sound);
}

//키보드콜백함수
void keyboardCallback(KeyCode code, KeyState state) {

	lobby_keyboardCallback(code, state);
	game1_keyboardCallback(code, state);
	game2_keyboardCallback(code, state);
	game3_keyboardCallback(code, state);
	game4_keyboardCallback(code, state);
	game5_keyboardCallback(code, state);
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
	game1_main();
	game2_main();
	game3_main();
	game4_main();
	game5_main();


	startGame(lobbyscene);

}
