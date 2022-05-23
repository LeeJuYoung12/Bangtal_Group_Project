#define _CRT_SECURE_NO_WARNINGS
#define g2_ch_width 45*0.7
#define g2_ch_height 85*0.7
#define JUMP_POWER 15
#include <stdio.h>
#include <bangtal.h>
#include <list> 

using namespace std;

extern SceneID mapscene;
extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SoundID introbgm;

int g2_speed = 4, g2dx = 0, g2cx = 30, g2cy = 1000;

float g2_gravity = 9, g2_jumpPower=0,g2_jumpTime=0,height;
bool g2_jumping = true, g2_playing = false, g2_landing=false;


SceneID g2_scene, g2_scene2;
ObjectID g2ch;
ObjectID g2_gomapbutton, g2_restartbutton, g2_endingbutton, g2_deathback, g2_clearback, g2_startbutton;
ObjectID g2_endingch, g2_endgame;
TimerID g2_move_t, g2_update_t, g2_jump_t, g2_block_t;

SoundID g2_mapbgm, g2_endingbgm, g2_breathbgm, g2_firebgm;

class Floor {

	public: 
		int x, y, x_size, y_size;

		Floor(int input_x,int input_y,int input_xSize,int input_ySize) {
		x = input_x;
		y = input_y;
		x_size = input_xSize;
		y_size = input_ySize;
		}

		void setLocation(int input_x, int input_y) {

			x = input_x;
			y = input_y;
		}
			
};

list<Floor> land;


bool pointInRectangle(int x, int y, int rx, int ry, float x_size,float y_size) {

	if ((rx <= x && x <= (rx + x_size)) && (ry <= y && y <= (ry + y_size))) {
		return true;
	}
	else {
		return false;
	}

}

//캐릭터 움직임 제어
bool g2_block() {
	for (Floor val : land) {

		bool b1 = pointInRectangle(g2cx+30, g2cy + 20, val.x, val.y, val.x_size, val.y_size);
		bool b2 = pointInRectangle(g2cx+30 , g2cy + 60, val.x, val.y, val.x_size, val.y_size);
		bool b3 = pointInRectangle(g2cx+15 , g2cy + 20, val.x, val.y, val.x_size, val.y_size);
		bool b4 = pointInRectangle(g2cx+30 , g2cy, val.x, val.y, val.x_size, val.y_size);
		if (b1 ) {
			printf("b1\n");
			/*
			g2_jumping = false;
			g2_jumpTime = 0;
			g2cy = val.y + val.y_size;
			*/

			g2cx -= g2_speed;

		}
				
		
		/**/
		else if (b2) {
			printf("b2\n");
			if (height > 0) {
				g2_jumpTime = 0.3;
				g2_jumpPower = -3;
				return true;
			}
			else {
				
				//g2cy = val.y + val.y_size;
			}
		}
		else if (b3){
			printf("b3\n");
			g2cx += g2_speed;
			//g2_jumping = false;
			//g2_jumpTime = 0;
			//g2cy = val.y + val.y_size;
		}
			
		else if (b4) {
			printf("b4\n");
			g2_jumpPower = JUMP_POWER;
			g2_jumping = false;
			g2_jumpTime = 0;
			//g2cy = val.y + val.y_size+5;
		}
	}
	
		locateObject(g2ch, g2_scene, g2cx, g2cy);
		return false;
}


//점프
void g2_jump() {

	height = (g2_jumpTime * g2_jumpTime * (-g2_gravity) / 2) + (g2_jumpPower);
	
		if (height > 0) {
			for (int i = 0; i < height; i++) {
				if (!g2_jumping)
					break;
				g2cy++;
				if(g2_block())
					break;
			}
		}
		else {
			for (int i = 0; i < - height; i++) {
				if (!g2_jumping)
					break;
				g2cy--;
				g2_block();
			}
		}

	g2_jumpTime += 0.1f;
	g2_block();
	
}
void makeAndPush(const char* url,int x, int y, int x_size, int y_size){

	createObject(url, g2_scene, x, y, true, 1); 

	Floor map1(x, y, x_size, y_size);
	land.push_back(map1);
}

void g2_settingMap() {
 // 가로: 1100*0.4 세로:290*0.4

	makeAndPush("image/game2/floor1.png", -20, 40, 1030, 33);
	makeAndPush("image/game2/floor1.png", 980, 40, 1000, 40);

	makeAndPush("image/game2/floor2.png", 200, 180, 150, 40);
	makeAndPush("image/game2/floor2.png", 400, 300, 155, 40);
	makeAndPush("image/game2/floor2.png", 600, 420, 155, 40);
	makeAndPush("image/game2/floor2.png", 400, 540, 155, 40);
	makeAndPush("image/game2/floor2.png", 200, 660, 155, 40);

	//150 40
	
}

//초기화
void g2_restart() {
	stopTimer(g2_move_t);
	stopTimer(g2_update_t);
	stopTimer(g2_block_t);
	stopTimer(g2_jump_t);

	setTimer(g2_move_t, 0.01f);
	setTimer(g2_update_t, 0.01f);
	setTimer(g2_block_t, 0.03f);
	setTimer(g2_jump_t, 0.03f);

	locateObject(g2ch, g2_scene, 30, 390 * 0.4 - 1);
	
	g2dx = 0, g2cx = 30, g2cy = 270 * 0.4 - 1;
	


	g2_playing = false;
}
//death
void g2_death() {
	
}

void g2_clear() {
	
}


// 마우스콜백함수
void game2_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g2_gomapbutton) {
		hideObject(g2_deathback);
		hideObject(g2_gomapbutton);
		hideObject(g2_restartbutton);
		showObject(g2_startbutton);
		enterScene(mapscene);
		stopSound(g2_mapbgm);
		playSound(introbgm);
	}
	if (object == g2_restartbutton) {
		hideObject(g2_deathback);
		hideObject(g2_gomapbutton);
		hideObject(g2_restartbutton);
		showObject(g2_startbutton);
	}

	if (object == g2_startbutton) {
		g2_playing = true;
		startTimer(g2_block_t);
		startTimer(g2_update_t);
		startTimer(g2_move_t);
		hideObject(g2_startbutton);
		hideObject(g2_deathback);
		hideObject(g2_gomapbutton);
		hideObject(g2_restartbutton);
	}

	if (object == g2_endingbutton) {
		showObject(g2_startbutton);
		hideObject(g2_clearback);
		hideObject(g2_endingbutton);
		enterScene(g2_scene2);
		stopSound(g2_mapbgm);
		playSound(g2_endingbgm);

	}
	if (object == g2_endgame) {
		endGame();
	}
}

//타이머콜백함수
void game2_timerCallback(TimerID timer) {
	//캐릭터 움직임

	if (timer == g2_move_t) {
		g2cx += g2dx;

		if (g2_jumping) {
			g2_jump();
		}
		locateObject(g2ch, g2_scene, g2cx, g2cy);
		setTimer(g2_move_t, 0.01f);
		startTimer(g2_move_t);
	}

	if (timer == g2_update_t) {
		if (!g2_jumping) {
			g2_jumpPower = 0;
			g2_jumping = true;
			g2_jumpTime = 0;

			for (Floor val : land) {
				bool b4 = pointInRectangle(g2cx + 30, g2cy, val.x, val.y, val.x_size, val.y_size);
				if (b4) {
					printf("b4\n");
					g2_jumpPower = JUMP_POWER;
					g2_jumping = false;
					g2_jumpTime = 0;
					//g2cy = val.y + val.y_size+5;
				}
			}
		}
		setTimer(g2_update_t, 0.01f);
		startTimer(g2_update_t);
	}

	if (timer == g2_block_t) {
		//g2_block();

		setTimer(g2_block_t, 0.01f);
		startTimer(g2_block_t);
	}

}

//사운드콜백함수
void game2_soundCallback(SoundID sound) {
	if (sound == g2_mapbgm) {
		playSound(g2_mapbgm);
	}
}

//키보드콜백함수
void game2_keyboardCallback(KeyCode code, KeyState state) {
	if (nowgamenum == 2 && g2_playing) {
		if (code == KeyCode::KEY_UP_ARROW && g2_jumping==false) {			// UP
			//g2_gravity += (state == KeyState::KEY_PRESSED ? g2_jumpSpeed : 0);
			g2_jumping = true;


		}
		if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
			setObjectImage(g2ch, "image/game2/character.png");
			g2dx += (state == KeyState::KEY_PRESSED ? g2_speed : -g2_speed);
			
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
			setObjectImage(g2ch, "image/game2/character_left.png");
			g2dx -= (state == KeyState::KEY_PRESSED ? g2_speed : -g2_speed);


		}

	}
}

void game2_main() {

	//배경
	g2_scene = createScene("game4", "image/game2/background.png");
	
	//캐릭터
	g2ch = createObject("image/game2/character.png", g2_scene, g2cx, g2cy, true, 0.7f);

	//바닥
	g2_settingMap();


	//버튼들
	g2_clearback = createObject("image/clear.png", g2_scene, 270, 300, false, 1.5f);
	g2_deathback = createObject("image/gameover.png", g2_scene, 270, 300, false, 1.5f);
	g2_restartbutton = createObject("image/restart.png", g2_scene, 700, 200, false, 1.3f);
	g2_startbutton = createObject("image/start.png", g2_scene, 450, 300, true, 0.8f);
	g2_endingbutton = createObject("image/ending.png", g2_scene, 500, 100, false, 1.3f);
	g2_endgame = createObject("image/end.png", g2_scene2, 550, 450, false, 0.8f);
	g2_gomapbutton = createObject("image/gomap.png", g2_scene, 300, 200, false, 1.3f);

	//타이머들
	g2_move_t = createTimer(0.01f);
	g2_update_t = createTimer(0.01f);
	g2_block_t = createTimer(0.01f);
	g2_jump_t = createTimer(0.03f);


}