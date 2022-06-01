#define _CRT_SECURE_NO_WARNINGS
#define g2_ch_width 45*0.7
#define g2_ch_height 85*0.7
//1200 700 
#define JUMP_POWER 12
#define g2_display_height 720
#define max_speed 25

//69 34
#define g2_thorn "image/game2/thorn.png"
#define g2_floor "image/game2/floor.png"

//155px 40px
#define g2_bigStool "image/game2/big_stool.png"
//108 40
#define g2_midStool "image/game2/mid_stool.png"
//72 40
#define g2_smallStool "image/game2/small_stool.png"
//36 40
#define g2_small "image/game2/small.png"
#include <stdio.h>
#include <bangtal.h>
#include <list> 

using namespace std;

extern SceneID mapscene;
extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SoundID introbgm;
extern bool g2_cleared;
//게임은 6으로
int g2_speed = 6, g2dx = 0, g2cx = 100, g2cy = 75,g2_b4Count=0;

float g2_gravity = 9, g2_jumpPower=0,g2_jumpTime=0,height=0;
bool g2_jumping = true, g2_playing = false, g2_landing=false,g2_rightState=false,g2_leftState=false;


SceneID g2_scene, g2_scene2, g2_scene3;
ObjectID g2ch;
ObjectID g2_gomapbutton, g2_restartbutton, g2_endingbutton, g2_deathback, g2_clearback, g2_startbutton, g2_nextbutton;
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

list<Floor> scene_land, scene2_land, scene3_land;
list<Floor> scene_thorns, scene2_thorns, scene3_thorns;
list<Floor> scene_leftEscalator, scene2_leftEscalator, scene3_leftEscalator;
list<Floor> scene_rightEscalator, scene2_rightEscalator, scene3_rightEscalator;



void makeAndPush(const char* url, SceneID scene, int x, int y, int x_size, int y_size, const char* type) {
	if (type == "potal") {
		createObject(url, scene, x, y, true, 1.f);

	}else
	createObject(url, scene, x, y, true, 1);

	if (type == "floor") {
		Floor map1(x, y, x_size, y_size);

		if (scene == g2_scene) {
			scene_land.push_back(map1);
		}
		else if (scene == g2_scene2) {
			scene2_land.push_back(map1);
		}
		else if (scene == g2_scene3) {
			scene3_land.push_back(map1);
		}
	}

	else if (type == "thorn") {
		Floor thorn(x, y, x_size, y_size);

		if (scene == g2_scene) {
			scene_thorns.push_back(thorn);
		}
		else if (scene == g2_scene2) {
			scene2_thorns.push_back(thorn);
		}
		else if (scene == g2_scene3) {
			scene3_thorns.push_back(thorn);
		}
	}
	else if (type == "rightEscalator") {
		Floor escalator(x, y, x_size, y_size);

		if (scene == g2_scene) {
			scene_rightEscalator.push_back(escalator);
		}
		else if (scene == g2_scene2) {
			scene2_rightEscalator.push_back(escalator);
		}
		else if (scene == g2_scene3) {
			scene3_rightEscalator.push_back(escalator);
		}
	}
	else if (type == "leftEscalator") {
		Floor escalator(x, y, x_size, y_size);

		if (scene == g2_scene) {
			scene_leftEscalator.push_back(escalator);
		}
		else if (scene == g2_scene2) {
			scene2_leftEscalator.push_back(escalator);
		}
		else if (scene == g2_scene3) {
			scene3_leftEscalator.push_back(escalator);
		}
	}
	


}

void g2_settingMap() {
	// ����: 1100*0.4 ����:290*0.4

	makeAndPush(g2_floor, g2_scene, -20, 40, 1030, 33, "floor");
	makeAndPush(g2_floor, g2_scene, 980, 40, 1000, 40, "floor");


	makeAndPush(g2_bigStool, g2_scene, 50, 150, 155, 30, "floor");
	makeAndPush(g2_midStool, g2_scene, 250, 250, 108, 30, "floor");

	makeAndPush(g2_smallStool, g2_scene, 425, 350, 72, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene, 250, 450, 72, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene, 425, 550, 72, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene, 250, 650, 72, 30, "floor");


	makeAndPush(g2_bigStool, g2_scene2, 0, 30, 155, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene2, 135, 30, 72, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene2, 250, 120, 72, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene2, 400, 180, 72, 30, "floor");

	makeAndPush(g2_small, g2_scene2, 600, 250, 36, 30, "floor");
	makeAndPush(g2_small, g2_scene2, 725, 350, 36, 30, "floor");
	makeAndPush(g2_small, g2_scene2, 850, 450, 36, 30, "floor");
	makeAndPush(g2_small, g2_scene2, 975, 550, 36, 30, "floor");
	makeAndPush(g2_small, g2_scene2, 1100, 650, 36, 30, "floor");


	makeAndPush(g2_bigStool, g2_scene3, 765, 30, 155, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene3, 900, 30, 72, 30, "floor");

	makeAndPush(g2_bigStool, g2_scene3, 565, 30, 155, 30, "floor");
	makeAndPush(g2_thorn, g2_scene3, 605, 66, 69, 34, "thorn");

	makeAndPush(g2_bigStool, g2_scene3, 315, 130, 155, 30, "floor");
	makeAndPush(g2_thorn, g2_scene3, 355, 166, 69, 34, "thorn");

	makeAndPush(g2_bigStool, g2_scene3, 65, 230, 155, 30, "floor");
	makeAndPush(g2_thorn, g2_scene3, 105, 266, 69, 34, "thorn");


	makeAndPush(g2_bigStool, g2_scene3, 315, 330, 155, 30, "floor");
	makeAndPush(g2_thorn, g2_scene3, 355, 366, 69, 34, "thorn");

	makeAndPush(g2_bigStool, g2_scene3, 565, 430, 155, 30, "floor");
	makeAndPush(g2_thorn, g2_scene3, 605, 466, 69, 34, "thorn");


	makeAndPush(g2_bigStool, g2_scene3, 715, 530, 155, 30, "floor");
	makeAndPush(g2_smallStool, g2_scene3, 855, 530, 72, 30, "floor");

	
	

	makeAndPush("image/game2/portal.png", g2_scene3, 815, 560, 72, 30, "potal");
	/*

	makeAndPush(g2_smallStool, g2_scene, 200, 180, 71, 30, "floor");
	makeAndPush(g2_bigStool, g2_scene, 400, 300, 155, 40, "floor");
	makeAndPush(g2_midStool, g2_scene, 600, 420, 155, 40, "floor");
	makeAndPush(g2_midStool, g2_scene, 400, 540, 155, 40, "floor");
	makeAndPush(g2_midStool, g2_scene, 200, 660, 155, 40, "floor");
	makeAndPush(g2_midStool, g2_scene2, 400, 50, 155, 40, "floor");

	makeAndPush(g2_midStool, g2_scene2, 600, 200, 155, 40, "floor");
	makeAndPush(g2_midStool, g2_scene2, 400, 350, 155, 40, "floor");
	makeAndPush(g2_midStool, g2_scene2, 200, 500, 155, 40, "floor");

	makeAndPush("image/game2/a.png", g2_scene, 0, 180, 155, 40, "rightEscalator");

	
	makeAndPush(g2_thorn, g2_scene, 300, 77, 69, 34, "thorn");
	*/


	//150 40

}



bool pointInRectangle(int x, int y, int rx, int ry, float x_size,float y_size) {

	if ((rx <= x && x <= (rx + x_size)) && (ry <= y && y <= (ry + y_size))) {
		return true;
	}
	else {
		return false;
	}

}
bool g2_block() {
	list<Floor> land;
	int local_g2cy;
	if (g2cy > g2_display_height*2) {
		land = scene3_land;
		land.insert(land.end(), scene3_leftEscalator.begin(), scene3_leftEscalator.end());
		land.insert(land.end(), scene3_rightEscalator.begin(), scene3_rightEscalator.end());

		local_g2cy = g2cy - g2_display_height*2;
	}
	else if (g2cy > g2_display_height) {
		land = scene2_land;
		land.insert(land.end(), scene2_leftEscalator.begin(), scene2_leftEscalator.end());
		land.insert(land.end(), scene2_rightEscalator.begin(), scene2_rightEscalator.end());

		local_g2cy = g2cy - g2_display_height;
	}
	else {
		land = scene_land;
		land.insert(land.end(), scene_leftEscalator.begin(), scene_leftEscalator.end());
		land.insert(land.end(), scene_rightEscalator.begin(), scene_rightEscalator.end());

		local_g2cy = g2cy;
	}
	
	for (Floor val : land) {
		
		bool b1 = pointInRectangle(g2cx + 30, local_g2cy + 5, val.x, val.y, val.x_size, val.y_size);//����
		bool b1_mid = pointInRectangle(g2cx + 30, local_g2cy + 35, val.x, val.y, val.x_size, val.y_size);//����

		bool b2 = pointInRectangle(g2cx+30 , local_g2cy + 60, val.x, val.y, val.x_size, val.y_size);//���

		bool b3 = pointInRectangle(g2cx+15 , local_g2cy+5, val.x, val.y, val.x_size, val.y_size);//����
		bool b3_mid = pointInRectangle(g2cx + 15, local_g2cy + 35, val.x, val.y, val.x_size, val.y_size);//����
		bool b4 = pointInRectangle(g2cx+30 , local_g2cy, val.x, val.y, val.x_size, val.y_size);//�ϴ�
		if (b1||b1_mid ) {
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
		
		}
		else if (b3||b3_mid){
			printf("b3\n");
			g2cx += g2_speed;
			
			//g2_jumping = false;
			//g2_jumpTime = 0;
			//g2cy = val.y + val.y_size;
		}
			
		else if (b4) {
			printf("b4\n");
			g2_b4Count++;

			g2_jumpPower = JUMP_POWER;
			g2_jumping = false;
			g2_jumpTime = 0;

			if (g2_b4Count == 4) {
			g2cy = val.y + val.y_size;
			g2_b4Count = 0;
			}
		}
	}
	
		locateObject(g2ch, g2_scene, g2cx, g2cy);
		return false;
}
void g2_jump() {

	height = (g2_jumpTime * g2_jumpTime * (-g2_gravity) / 2) + (g2_jumpPower);

		if (height >= 0) {
			for (int i = 0; i < height; i++) {
				if (!g2_jumping)
					break;
				g2cy++;
				if(g2_block())
					break;
			}
		}

		else {
			height = (height < -max_speed) ? -max_speed : height;
			printf("%f\n", height);
			for (int i = 0; i < - height; i++) {
				if (!g2_jumping)
					break;
				g2cy--;
				g2_block();
			}
		}

	g2_jumpTime += 0.1f;
	
}


//restart
void g2_restart() {

	stopTimer(g2_move_t);
	stopTimer(g2_update_t);
	stopTimer(g2_block_t);
	stopTimer(g2_jump_t);

	setTimer(g2_move_t, 0.01f);
	setTimer(g2_update_t, 0.01f);
	setTimer(g2_block_t, 0.03f);
	setTimer(g2_jump_t, 0.10f);

	startTimer(g2_move_t);
	startTimer(g2_update_t);
	startTimer(g2_block_t);
	startTimer(g2_jump_t);
	
	hideObject(g2_restartbutton);
	hideObject(g2_gomapbutton);
	hideObject(g2_deathback);
	hideObject(g2_clearback);
	hideObject(g2_nextbutton);

	locateObject(g2ch, g2_scene, 30, 390 * 0.4 - 1);
	
	 g2cx = 100, g2cy =75;
	


	g2_playing = true;
}
//deat
void g2_death() {

	SceneID nowScene;
	if (g2cy > g2_display_height * 2) {
		nowScene = g2_scene3;

	}
	else if (g2cy > g2_display_height) {
		nowScene = g2_scene2;
	}
	else {
		nowScene = g2_scene;
	}

	locateObject(g2_deathback, nowScene, 270, 300);
	locateObject(g2_gomapbutton, nowScene, 300, 200);
	locateObject(g2_restartbutton, nowScene, 700, 200);

	showObject(g2_deathback);
	showObject(g2_gomapbutton);
	showObject(g2_restartbutton);

	stopTimer(g2_move_t);
	stopTimer(g2_update_t);
	stopTimer(g2_block_t);
	stopTimer(g2_jump_t);

	g2_playing = false;

}

void g2_clear() {

	locateObject(g2_clearback, g2_scene3, 270, 300);
	locateObject(g2_gomapbutton, g2_scene3, 300, 100);
	locateObject(g2_nextbutton, g2_scene3, 700, 100);

	showObject(g2_clearback);
	showObject(g2_gomapbutton);
	showObject(g2_nextbutton);

	

	stopTimer(g2_move_t);
	stopTimer(g2_update_t);
	stopTimer(g2_block_t);
	stopTimer(g2_jump_t);

	g2_playing = false;
	g2_cleared = true;

}


void game2_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g2_gomapbutton) {
		hideObject(g2_deathback);
		hideObject(g2_clearback);
		hideObject(g2_gomapbutton);
		hideObject(g2_nextbutton);
		hideObject(g2_restartbutton);
		showObject(g2_startbutton);
		enterScene(mapscene);
		stopSound(g2_mapbgm);
		playSound(introbgm);
	}
	if (object == g2_restartbutton) {
		g2_restart();
	}

	if (object == g2_startbutton) {
		g2_playing = true;
		g2_restart();
		hideObject(g2_startbutton);
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
void game2_timerCallback(TimerID timer) {
	//moving timer
	if (timer == g2_move_t) {
		
		g2cx += g2dx;
		if (g2cx < 0)
			g2cx = 0;
		if (g2cx > 1200)
			g2cx = 1200;
		if (g2_jumping) {
			g2_jump();
		}
		if (g2cy > g2_display_height * 2) {

			locateObject(g2ch, g2_scene3, g2cx, g2cy - g2_display_height*2);
			enterScene(g2_scene3);
			printf("x:%d y:%d\n", g2cx,  g2cy);
			


		}
		else if (g2cy > g2_display_height) {
			locateObject(g2ch, g2_scene2, g2cx, g2cy-g2_display_height);
			enterScene(g2_scene2);

		}
		else {
		locateObject(g2ch, g2_scene, g2cx, g2cy);
		enterScene(g2_scene);

		}

		setTimer(g2_move_t, 0.01f);
		startTimer(g2_move_t);
	}

	if (timer == g2_update_t) {
		if ((820 < g2cx && g2cx < 900) && g2cy == 2000) {
			g2_clear();
			setTimer(g2_move_t, 10000);
			startTimer(g2_move_t);
			return;
		}

		if (g2dx > 0) {
		setObjectImage(g2ch, "image/game2/character.png");
		}
		else if(g2dx<0){
			setObjectImage(g2ch, "image/game2/character_left.png");
		}


		setTimer(g2_update_t, 0.01f);
		startTimer(g2_update_t);
	}

	//이동반경이 막혔나 확인
	if (timer == g2_block_t) {

		if (!g2_jumping) {
			g2_jumpPower = 0;
			g2_jumping = true;
			g2_jumpTime = 0;
			list<Floor> land,thorn,esca,leftEscalator, rightEscalator;
			int local_g2cy;
			if (g2cy > g2_display_height*2) {
				land = scene3_land;
				thorn = scene3_thorns;
				leftEscalator = scene3_leftEscalator;
				rightEscalator = scene3_rightEscalator;
				local_g2cy = g2cy - g2_display_height*2;
			}
			else if (g2cy > g2_display_height) {
				land = scene2_land;
				thorn = scene2_thorns;
				leftEscalator = scene2_leftEscalator;
				rightEscalator = scene2_rightEscalator;
				local_g2cy = g2cy - g2_display_height;
			}
			else {
				land = scene_land;
				thorn = scene_thorns;
				leftEscalator = scene_leftEscalator;
				rightEscalator = scene_rightEscalator;
				local_g2cy = g2cy;
			}

			for (Floor val : land) {
				bool b4 = pointInRectangle(g2cx + 30, local_g2cy, val.x, val.y, val.x_size, val.y_size);
				if (b4) {
					g2_b4Count++;
					g2_jumpPower = JUMP_POWER;
					g2_jumping = false;
					g2_jumpTime = 0;

				/*	if (g2_b4Count >= 3) {
						g2_b4Count = 0;
						g2cy = val.y + val.y_size;
					}
					*/
				}
			}

			for (Floor val : thorn) {
				bool b1 = pointInRectangle(g2cx + 40, local_g2cy + 20, val.x, val.y, val.x_size, val.y_size);//right
				bool b2 = pointInRectangle(g2cx + 30, local_g2cy + 60, val.x, val.y, val.x_size, val.y_size);//top
				bool b3 = pointInRectangle(g2cx + 25, local_g2cy + 20, val.x, val.y, val.x_size, val.y_size);//left
				bool b4 = pointInRectangle(g2cx + 30, local_g2cy, val.x, val.y, val.x_size, val.y_size);//bottom
				//game over
				if (b1 || b2 || b3 || b4) {
					g2_death();
				}
			}

			for (Floor val : scene_leftEscalator) {
				bool b1 = pointInRectangle(g2cx + 40, local_g2cy + 20, val.x, val.y, val.x_size, val.y_size);//right
				bool b2 = pointInRectangle(g2cx + 30, local_g2cy + 60, val.x, val.y, val.x_size, val.y_size);//top
				bool b3 = pointInRectangle(g2cx + 25, local_g2cy + 20, val.x, val.y, val.x_size, val.y_size);//left
				bool b4 = pointInRectangle(g2cx + 30, local_g2cy, val.x, val.y, val.x_size, val.y_size);//bottom
				if (b1 || b2 || b3 || b4) {
					g2_jumpPower = JUMP_POWER;
					g2_jumping = false;
					g2_jumpTime = 0;
					g2cx -= 3;
				}
			}

			for (Floor val : scene_rightEscalator) {
				bool b1 = pointInRectangle(g2cx + 40, local_g2cy + 20, val.x, val.y, val.x_size, val.y_size);//right
				bool b2 = pointInRectangle(g2cx + 30, local_g2cy + 60, val.x, val.y, val.x_size, val.y_size);//top
				bool b3 = pointInRectangle(g2cx + 25, local_g2cy + 20, val.x, val.y, val.x_size, val.y_size);//left
				bool b4 = pointInRectangle(g2cx + 30, local_g2cy, val.x, val.y, val.x_size, val.y_size);//bottom
				//game over
				if (b1 || b2 || b3 || b4) {
					g2_jumpPower = JUMP_POWER;
					g2_jumping = false;
					g2_jumpTime = 0;
					g2cx += 3;
				}
			}



		}

		setTimer(g2_block_t, 0.01f);
		startTimer(g2_block_t);
	}
	if (timer == g2_jump_t) {

		g2_b4Count = 0;

		setTimer(g2_jump_t, 0.10f);
		startTimer(g2_jump_t);
	}
}

void game2_soundCallback(SoundID sound) {
	if (sound == g2_mapbgm) {
		playSound(g2_mapbgm);
	}
}


void game2_keyboardCallback(KeyCode code, KeyState state) {


	if (nowgamenum == 2 && g2_playing) {
		if (code == KeyCode::KEY_UP_ARROW && g2_jumping == false) {			// UP
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
			else if (nowgamenum == 2 && !g2_playing) {
				if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
					g2dx += (state == KeyState::KEY_PRESSED ? g2_speed : -g2_speed);

				}
				if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
					g2dx -= (state == KeyState::KEY_PRESSED ? g2_speed : -g2_speed);
				}
			}
}


void game2_main() {

	//���
	g2_scene = createScene("game2", "image/game2/background1.png");
	g2_scene2 = createScene("game2", "image/game2/background2.png");
	g2_scene3 = createScene("game2", "image/game2/background3.png");

	//ĳ����
	g2ch = createObject("image/game2/character.png", g2_scene, g2cx, g2cy, true, 0.7f);

	//�ٴ�
	g2_settingMap();


	//��ư��
	g2_clearback = createObject("image/clear.png", g2_scene, 270, 300, false, 1.5f);
	g2_deathback = createObject("image/gameover.png", g2_scene, 270, 300, false, 1.5f);
	g2_restartbutton = createObject("image/restart.png", g2_scene, 700, 200, false, 1.3f);
	g2_startbutton = createObject("image/start.png", g2_scene, 450, 300, true, 0.8f);
	g2_endgame = createObject("image/end.png", g2_scene2, 550, 450, false, 0.8f);
	g2_gomapbutton = createObject("image/gomap.png", g2_scene, 500, 100, false, 1.3f);

	

	
	//Ÿ�̸ӵ�
	g2_move_t = createTimer(0.01f);
	g2_update_t = createTimer(0.01f);
	g2_block_t = createTimer(0.01f);
	g2_jump_t = createTimer(0.1f);


}
