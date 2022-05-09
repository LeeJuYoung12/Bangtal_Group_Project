#define _CRT_SECURE_NO_WARNINGS
#define g1_ch_x 95*0.7
#define g1_ch_y 100*0.7
#define g1_effect_x 342*0.3 
#define g1_effect_y 261*0.3
#include <stdio.h>
#include <bangtal.h>

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SceneID mapscene;

int g1_pillar_x[26] = { 0, 50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250};
int g1_pillar_y[15] = { 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700};
int g1_ghost_x[17] = { 1000, 950, 900, 850, 800, 750, 700, 650, 600, 550, 500, 450, 400, 350 ,700, 750, 1100};
int g1_ghost_y[17] = { 400, 50, 400, 50, 400, 50, 400, 50, 400, 50, 400, 50, 400, 50 ,600,600,500};
int g1_box_x[16] = { 650,700,750,800,850,900,950,1000, 650,700,750,800,850,900,950,1000};
int g1_box_y[16] = { 600, 600, 600, 600, 600, 600, 600, 600, 550, 550, 550, 550, 550, 550, 550, 550};
int g1_speed = 1, g1dx = 0, g1dy = 0, g1cx = 52, g1cy= 52, g1_ghost_speed=5, g1_chway=3, g1_attackeffectx, g1_attackeffecty, g1_effectspeed = 4;
long long g1_attacknum = 1;

bool g1_ghostway[16] = { true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, true};
bool g1_attacking = false;

SceneID g1_scene;
ObjectID g1_pillar1[100], g1_pillar2[100], g1ch, g1_ghost[17], g1_clear_zone, g1_attackeffect[4], g1_box[16], g1_gomapbutton, g1_restartbutton, g1_nextbutton, g1_deathback, g1_clearback; //pillar1은 위에서 본버전, pillar2는 입체 버전
TimerID g1_move_t, g1_moveghost_t, g1_update_t, g1_effectmove_t;
SoundID g1_boxsound;

void g1_install() {
	//맨 밑 벽
	for (int i = 0; i < 26; i++) {
		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[i], g1_pillar_y[0], true, 1.f);

	}
	//왼쪽 벽
	for (int i = 27, k = 1; i < 42; i++) {

		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[0], g1_pillar_y[k], true, 1.f);
		k++;
	}
	//오른쪽 벽
	for (int i = 42, k = 1; i < 57; i++) {

		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[25], g1_pillar_y[k], true, 1.f);
		k++;
	}
	//위에 벽
	for (int i = 1; i < 25; i++) {
		g1_pillar2[i] = createObject("image/game1/pillar2.png", g1_scene, g1_pillar_x[i], g1_pillar_y[13] - 20, true, 1.f);
	}


	for (int i = 57, k = 1; i < 67; i++) {
		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[4], g1_pillar_y[k], true, 1.f);
		k++;
	}
	for (int i = 25, k = 5; i < 42; i++) {
		g1_pillar2[i] = createObject("image/game1/pillar2.png", g1_scene, g1_pillar_x[k], g1_pillar_y[9], true, 1.f);
		k++;
	}
	for (int i = 67, k = 9; i < 72; i++) {
		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[21], g1_pillar_y[k], true, 1.f);
		k--;
	}
	for (int i = 72, k = 1; i < 78; i++) {
		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[5], g1_pillar_y[k], true, 1.f);
		k++;
	}
	for (int i = 78, k = 1; i < 84; i++) {
		g1_pillar1[i] = createObject("image/game1/pillar1.png", g1_scene, g1_pillar_x[6], g1_pillar_y[k], true, 1.f);
		k++;
	}
	g1_pillar2[42] = createObject("image/game1/pillar2.png", g1_scene, g1_pillar_x[21], g1_pillar_y[3], true, 1.f);

}
void g1_block() {
	if (g1cx < 50 || g1cx + g1_ch_x>1250 || g1cy < 50 || g1cy + g1_ch_y>640) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if (((g1cx+g1_ch_x >200&& g1cx + g1_ch_x < 250 )||(g1cx<250&&g1cx>200)) && (g1cy < 500 && g1cy>50)) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if (g1cx < g1_pillar_x[21]+50 && g1cx > 150 && (g1cy < 520 && g1cy>450|| g1cy+g1_ch_y < 520 && g1cy + g1_ch_y>450)) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if ((g1cx < g1_pillar_x[21] + 50 && g1cx > g1_pillar_x[21]) && (g1cy < 500 && g1cy+g1_ch_y>150) || (((g1cx + g1_ch_x > g1_pillar_x[21] && g1cx + g1_ch_x < g1_pillar_x[21] + 50)|| (g1cx + g1_ch_x/2 > g1_pillar_x[21] && g1cx + g1_ch_x/2 < g1_pillar_x[21] + 50)) && (g1cy < 500 && g1cy+ g1_ch_y>150))) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if ((g1cx< 300+50 && g1cx > 200) && (g1cy < 350 && g1cy>50)) {
		g1cx -= g1dx; g1cy -= g1dy;
	}

	//박스 뚫고 지나지 못하게하는용
	for (int i = 0; i < 16; i++) {
		if ((g1cx < (g1_box_x[i] + 50)) && (g1cx + g1_ch_x > g1_box_x[i]) && (g1cy < (g1_box_y[i] + 50)) && (g1cy +g1_ch_y > g1_box_y[i])) {
			g1cx -= g1dx; g1cy -= g1dy;
		}
	}
}

void g1_ghostmove() {
	//방향 정하기
	for (int i = 0; i < 14; i++) {
		if (g1_ghost_y[i] <= 50) {
			g1_ghostway[i] = true;
		}
		if (g1_ghost_y[i] >= 400) {
			g1_ghostway[i] = false;
		}
	}
	if (g1_ghost_x[16] <= 1100) {
		g1_ghostway[15] = true;
	}
	if (g1_ghost_x[16] >= 1200) {
		g1_ghostway[15] = false;
	}

	//좌표 바꾸기
	for (int i = 0; i < 14; i++) {
		if (g1_ghostway[i] == false) {
			g1_ghost_y[i] -= g1_ghost_speed;
		}
		if (g1_ghostway[i] == true) {
			g1_ghost_y[i] += g1_ghost_speed;
		}
	}
	if (g1_ghostway[15] == false) {
		g1_ghost_x[16] -= g1_ghost_speed-4;
	}
	if (g1_ghostway[15] == true) {
		g1_ghost_x[16] += g1_ghost_speed-4;
	}

	//이동하기
	for (int i = 0; i < 14; i++) {
		locateObject(g1_ghost[i], g1_scene, g1_ghost_x[i], g1_ghost_y[i]);
	}
	locateObject(g1_ghost[16], g1_scene, g1_ghost_x[16], g1_ghost_y[16]);
}

void g1_attack() {

	if (g1_chway == 0) {
		g1_attackeffectx = g1cx + 5;
		g1_attackeffecty = g1cy-5;
		locateObject(g1_attackeffect[0], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[0]);
		startTimer(g1_effectmove_t);
	}
	if (g1_chway == 1) {
		g1_attackeffectx = g1cx - 50;
		g1_attackeffecty = g1cy-5;
		locateObject(g1_attackeffect[1], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[1]);
		startTimer(g1_effectmove_t);
	}
	if (g1_chway == 2) {
		g1_attackeffectx = g1cx-10;
		g1_attackeffecty = g1cy-50;
		locateObject(g1_attackeffect[2], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[2]);
		startTimer(g1_effectmove_t);
	}
	if (g1_chway == 3) {
		g1_attackeffectx = g1cx-10;
		g1_attackeffecty = g1cy+50;
		locateObject(g1_attackeffect[3], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[3]);
		startTimer(g1_effectmove_t);
	}
}

void g1_boxdelete() {
	for (int i = 0; i < 16; i++) {
		if (((g1_attackeffectx+220*0.3 ) > g1_box_x[i]) && ((g1_attackeffectx+220*0.3) < (g1_box_x[i] + 50)) && ((g1_attackeffecty+130*0.3 )> g1_box_y[i]) && ((g1_attackeffecty+130*0.3 )< (g1_box_x[i] + 50))) {
			g1_box_x[i] = 1300, g1_box_y[i] = 800;
			playSound(g1_boxsound);
			locateObject(g1_box[i], g1_scene, g1_box_x[i],  g1_box_y[i]);
		}
	}
}

void g1_clear() {
	if ((g1cx+g1_ch_x/2 > g1_pillar_x[5]) && (g1cx + g1_ch_x / 2 < g1_pillar_x[7] - 1) && (g1cy > g1_pillar_y[7]) && (g1cy < g1_pillar_y[9] - 1)) {
		showObject(g1_clearback);
		showObject(g1_gomapbutton);
		showObject(g1_nextbutton);

		stopTimer(g1_move_t);
		stopTimer(g1_moveghost_t);
		stopTimer(g1_update_t);
		stopTimer(g1_effectmove_t);
	}

}

void g1_death() {
	for (int i = 0; i < 17; i++) {
		if ((((g1cx+30*0.7 > g1_ghost_x[i])&&(g1cx+30*0.7 <g1_ghost_x[i]+50))|| ((g1cx + 60*0.7 > g1_ghost_x[i]) && (g1cx + 60*0.7 < g1_ghost_x[i] + 50))) && ((((g1cy+5*0.7>g1_ghost_y[i])&& (g1cy + 5*0.7 < g1_ghost_y[i]+50)))||((g1cy+95*0.7>g1_ghost_y[i])&&(g1cy+95*0.7<g1_ghost_y[i]+50)))) {
			showObject(g1_deathback);
			showObject(g1_gomapbutton);
			showObject(g1_restartbutton);
			
			stopTimer(g1_move_t);		
			stopTimer(g1_moveghost_t);
			stopTimer(g1_update_t);
			stopTimer(g1_effectmove_t);
		}
	}
}

void g1_restart() {
	hideObject(g1_restartbutton);
	hideObject(g1_gomapbutton);
	hideObject(g1_nextbutton);
	hideObject(g1_clearback);
	hideObject(g1_deathback);
	
	g1cx = 52, g1cy = 52, g1_attacknum = 1;
	g1_attacking = false;
	g1_chway = 3, g1dx = 0, g1dy = 0;
	g1_attackeffectx = 1500, g1_attackeffecty = 800;

	for (int i = 0, k=650; i < 8; i++) {
		g1_box_x[i] = k;
		g1_box_y[i] = 600;
		k += 50;

	}
	for (int i = 8, k=650; i < 16; i++) {
		g1_box_x[i] = k;
		g1_box_y[i] = 550;
		k += 50;
	}
	//위치
	locateObject(g1ch, g1_scene, g1cx, g1cy);

	locateObject(g1_attackeffect[0], g1_scene, 1500, 800);
	locateObject(g1_attackeffect[1], g1_scene, 1500, 800);
	locateObject(g1_attackeffect[2], g1_scene, 1500, 800);
	locateObject(g1_attackeffect[3], g1_scene, 1500, 800);

	for (int i = 0; i < 16; i++) {
		locateObject(g1_box[i], g1_scene, g1_box_x[i], g1_box_y[i]);
	}

	setTimer(g1_move_t, 0.01f);
	setTimer(g1_moveghost_t, 0.01f);
	setTimer(g1_update_t, 0.01f);
	setTimer(g1_effectmove_t, 0.01f);

	startTimer(g1_move_t);
	startTimer(g1_moveghost_t);
	startTimer(g1_update_t);
}

// 마우스콜백함수
void game1_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g1_gomapbutton) {
		enterScene(mapscene);
		g1_restart();
	}
	if (object == g1_restartbutton) {
		g1_restart();
	}
	if (object == g1_nextbutton) {
		g1_restart();
	}

}

//타이머콜백함수
void game1_timerCallback(TimerID timer) {
	if (timer == g1_move_t) {
		g1cx += g1dx; g1cy += g1dy;
		g1_block();

		locateObject(g1ch, g1_scene, g1cx, g1cy);
		setTimer(g1_move_t, 0.01f);
		startTimer(g1_move_t);
	}
	
	if (timer == g1_moveghost_t) {
		g1_ghostmove();
		setTimer(g1_moveghost_t, 0.01f);
		startTimer(g1_moveghost_t);
	}
	if (timer == g1_update_t) {
		g1_clear();
		g1_death();
		g1_boxdelete();
		setTimer(g1_update_t, 0.01f);
		startTimer(g1_update_t);
	}
	if (timer == g1_effectmove_t) {
	//이동
		if (g1_chway == 0) {
			g1_attackeffectx += g1_effectspeed;
			locateObject(g1_attackeffect[0], g1_scene, g1_attackeffectx, g1_attackeffecty);
			g1_attacknum++;
		}
		if (g1_chway == 1) {
			g1_attackeffectx -= g1_effectspeed;
			locateObject(g1_attackeffect[1], g1_scene, g1_attackeffectx, g1_attackeffecty);
			g1_attacknum++;
		}
		if (g1_chway == 2) {
			g1_attackeffecty -= g1_effectspeed;
			locateObject(g1_attackeffect[2], g1_scene, g1_attackeffectx, g1_attackeffecty);
			g1_attacknum++;
		}
		if (g1_chway == 3) {
			g1_attackeffecty += g1_effectspeed;
			locateObject(g1_attackeffect[3], g1_scene, g1_attackeffectx, g1_attackeffecty);
			g1_attacknum++;
		}
	//없어지는 조건
		if (g1_attacknum % 10 == 0) {
			hideObject(g1_attackeffect[0]); locateObject(g1_attackeffect[0], g1_scene, 1500, 800);
			hideObject(g1_attackeffect[1]); locateObject(g1_attackeffect[1], g1_scene, 1500, 800);
			hideObject(g1_attackeffect[2]); locateObject(g1_attackeffect[2], g1_scene, 1500, 800);
			hideObject(g1_attackeffect[3]); locateObject(g1_attackeffect[3], g1_scene, 1500, 800);
			g1_attacking = false;
			if (g1_chway == 0) setObjectImage(g1ch, "image/game1/player1.png");
			if (g1_chway == 1) setObjectImage(g1ch, "image/game1/player2.png");
			if (g1_chway == 2) setObjectImage(g1ch, "image/game1/player1.png");
			if (g1_chway == 3) setObjectImage(g1ch, "image/game1/player3.png");
		}
		if (g1_attacking == true) {
			setTimer(g1_effectmove_t, 0.01f);
			startTimer(g1_effectmove_t);
		}
	}
	

}

//사운드콜백함수
void game1_soundCallback(SoundID sound) {

}

//키보드콜백함수
void game1_keyboardCallback(KeyCode code, KeyState state) {
	if (nowgamenum == 1) {
		if (code == KeyCode::KEY_UP_ARROW) {			// UP
			g1dy += (state == KeyState::KEY_PRESSED ? g1_speed : -g1_speed);
			g1_chway = 3;
			setObjectImage(g1ch, "image/game1/player3.png");
		}
		if (code == KeyCode::KEY_DOWN_ARROW) {		// DOWN
			g1dy -= (state == KeyState::KEY_PRESSED ? g1_speed : -g1_speed);
			g1_chway = 2;
			setObjectImage(g1ch, "image/game1/player1.png");
		}
		if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
			g1dx += (state == KeyState::KEY_PRESSED ? g1_speed : -g1_speed);
			setObjectImage(g1ch, "image/game1/player1.png");
			g1_chway = 0;
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
			g1dx -= (state == KeyState::KEY_PRESSED ? g1_speed : -g1_speed);
			setObjectImage(g1ch, "image/game1/player2.png");
			g1_chway = 1;

		}
		if (code == KeyCode::KEY_SPACE) {
			if(state == KeyState::KEY_PRESSED){
				if (g1_attacking == false) {
					if (g1_chway == 0) setObjectImage(g1ch, "image/game1/player1-1.png");
					if (g1_chway == 1) setObjectImage(g1ch, "image/game1/player2-1.png");
					if (g1_chway == 2) setObjectImage(g1ch, "image/game1/player1-1.png");
					if (g1_chway == 3) setObjectImage(g1ch, "image/game1/player3-1.png");
					g1_attacking = true;
					g1_attack();
				}
			}
		}
	}
}

void game1_main() {

	g1_scene = createScene("game1", "image/game1/game1back.png");

	//clear zone
	g1_clear_zone = createObject("image/game1/clearzone.png", g1_scene, g1_pillar_x[5], g1_pillar_y[7], true, 1.f);

	//캐릭터
	g1ch = createObject("image/game1/player1.png", g1_scene, g1cx, g1cy, true, 0.7f);
	
	//벽 설치 길어서 지저분해서 함수로 만들었습니다.
	g1_install();

	//유령
	for (int i = 0; i < 14; i++) {
		g1_ghost[i] = createObject("image/game1/ghost1.png", g1_scene, g1_ghost_x[i], g1_ghost_y[i], true, 0.25f);
	}
	for (int i = 14; i < 17; i++) {
		g1_ghost[i] = createObject("image/game1/ghost2.png", g1_scene, g1_ghost_x[i], g1_ghost_y[i], true, 0.25f);
	}
	//상자
	for (int i = 0; i < 16; i++) {
		g1_box[i] = createObject("image/game1/box1.png", g1_scene, g1_box_x[i], g1_box_y[i], true, 1.f);
	}

	//검격
	g1_attackeffect[0] = createObject("image/game1/1.png", g1_scene, 1500, 800, false, 0.3f);
	g1_attackeffect[1] = createObject("image/game1/0.png", g1_scene, 1500, 800, false, 0.3f);
	g1_attackeffect[2] = createObject("image/game1/2.png", g1_scene, 1500, 800, false, 0.3f);
	g1_attackeffect[3] = createObject("image/game1/3.png", g1_scene, 1500, 800, false, 0.3f);

	//clearback, deathback, gomap, restart, next 용

	g1_clearback = createObject("image/clear.png", g1_scene, 270, 300, false, 1.5f);
	g1_deathback = createObject("image/gameover.png", g1_scene, 270, 300, false, 1.5f);
	g1_restartbutton = createObject("image/restart.png", g1_scene, 700, 200, false, 1.3f);
	g1_nextbutton = createObject("image/next.png", g1_scene, 700, 200, false, 1.3f);
	g1_gomapbutton = createObject("image/gomap.png", g1_scene, 300, 200, false, 1.3f);

	g1_boxsound = createSound("sound/game1/상자부수는소리.mp3");

	g1_move_t = createTimer(0.01f);
	startTimer(g1_move_t);

	g1_moveghost_t = createTimer(0.01f);
	startTimer(g1_moveghost_t);

	g1_update_t = createTimer(0.01f);
	startTimer(g1_update_t);

	g1_effectmove_t = createTimer(0.01f);
}