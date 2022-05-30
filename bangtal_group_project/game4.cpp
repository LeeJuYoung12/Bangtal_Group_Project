#define _CRT_SECURE_NO_WARNINGS
#define g4_ch_width 45*0.7
#define g4_ch_height 85*0.7
#include <stdio.h>
#include <bangtal.h>

extern SceneID mapscene;
extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SoundID introbgm;

int g4_speed = 4, g4dx = 0, g4cx = 30, g4cy = 290*0.4-1, g4_attackeffectx[2], g4_attackeffecty[2], g4_effectspeed = 25;
int g4_bottomy[4] = { 0, 240, 390, 540 };
int g4_bottomx[4] = { -150, 50, 50, 50 };
int g4_gravity = 20, g4_jumpcount;
int g4_bossx = 850, g4_bossy = 300, g4_bossspeed=12;
int g4_firex, g4_firey, g4_beamx, g4_beamy, g4_firecount = 0, g4_heartnum = 15;
int g4_endingchx=100, g4_endingchy=150;
bool g4_attacking1 = false, g4_attacking2 = false, g4_jumping = false, g4_rising = false, g4_downing = false, g4_island= true, g4_posture1=true, g4_posture2 =true;
bool g4_bossway = true, g4_beaming = false, g4_beamok=false, g4_playing=false;
bool g4_attackable1 = true, g4_attackable2 = true;
long long g4_bossanimation_count = 0, g4_endcount = 0;
const char* g4_bossimage[4] = { "image/game4/dragon1.png" , "image/game4/dragon2.png" , "image/game4/dragon3.png" , "image/game4/dragon4.png" };
const char* g4_heartimage[16] = { "image/game4/heart1.png" ,  "image/game4/heart2.png" ,  "image/game4/heart3.png" ,  "image/game4/heart4.png" ,  "image/game4/heart5.png" ,  "image/game4/heart6.png" ,  "image/game4/heart7.png" ,  "image/game4/heart8.png" ,  "image/game4/heart9.png" ,  "image/game4/heart10.png" ,  "image/game4/heart11.png" ,  "image/game4/heart12.png" ,  "image/game4/heart13.png" ,  "image/game4/heart14.png" ,  "image/game4/heart15.png" ,  "image/game4/heart16.png" };

SceneID g4_scene, g4_scene2;
ObjectID g4ch, g4_attackeffect[2], g4_floor[4], g4_boss, g4_fire, g4_square, g4_beam[2], g4_heart;
ObjectID g4_gomapbutton, g4_restartbutton, g4_endingbutton, g4_deathback, g4_clearback, g4_startbutton;
ObjectID g4_endingch, g4_endgame;
TimerID g4_move_t, g4_update_t, g4_effectmove_t, g4_effectmove2_t, g4_jump_t, g4_block_t, g4_posture1_t, g4_posture2_t, g4_bossmove_t;
TimerID g4_bossanimation_t, g4_firemove_t, g4_firecool_t, g4_hidesquare_t,g4_hidebeam_t, g4_beam_t, g4_beamcool_t, g4_heart_t;
TimerID g4_ending_t, g4_endanimation_t;
SoundID g4_mapbgm,g4_endingbgm, g4_breathbgm, g4_firebgm;

//캐릭터 움직임 제어
void g4_block() {

	if (g4_rising == false) {
		if ((((g4cx + 65 * 0.7) < 50) || (((g4cx) > 200))) && ((g4cy >= (g4_bottomy[0] + 290 * 0.4)))) {
			g4cy -= (g4_gravity - 5);
			locateObject(g4ch, g4_scene, g4cx, g4cy);
		}
		else if ((g4cx > (-150 + 1100 * 0.4)) && (g4cy > -100)) {
			g4cy -= (g4_gravity - 5);
			locateObject(g4ch, g4_scene, g4cx, g4cy);
		}
		else if ((((((g4cx) > 50) && (((g4cx) < 200)))|| ((g4cx+95*0.7) > 50) && (((g4cx+95*0.7) < 200)))) && (((g4cy > (g4_bottomy[1] + 35)) && ((g4cy < (g4_bottomy[1] + 150)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[2] + 35)) && ((g4cy < (g4_bottomy[2] + 150)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[3] + 35)) && ((g4cy < (g4_bottomy[3] + 150)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그
		else if ((((((g4cx) > 50) && (((g4cx) < 20))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[0]+290*0.4)) && ((g4cy < (g4_bottomy[0] +290*0.4+10)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[1])) && ((g4cy < (g4_bottomy[1]+25)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[2])) && ((g4cy < (g4_bottomy[2] + 25)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[3])) && ((g4cy < (g4_bottomy[3] + 25)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그2
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[1]-130)) && ((g4cy < (g4_bottomy[1] + 25)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그2
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[2]-150+40)) && ((g4cy < (g4_bottomy[2] + 25)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}
		//버그2
		else if ((((((g4cx) > 50) && (((g4cx) < 200))) || ((g4cx + 95 * 0.7) > 50) && (((g4cx + 95 * 0.7) < 200)))) && (((g4cy > (g4_bottomy[3]-150+40)) && ((g4cy < (g4_bottomy[3] + 25)))))) {
			if (g4_downing == false) {
				g4cy -= (g4_gravity - 5);
				locateObject(g4ch, g4_scene, g4cx, g4cy);
			}
		}


	}

	

	if ((g4cx < -5)) {
		g4cx=-5;
		locateObject(g4ch, g4_scene, g4cx, g4cy);
	}
	//버그방지
	if ((g4cx < (1100 * 0.4 - 150)) && (g4cy < (290 * 0.4))) {
		g4cy = (290-13) * 0.4;
		locateObject(g4ch, g4_scene, g4cx, g4cy);
	}

}


//점프
void g4_jump() {

	if (g4_rising) { //상승
		g4cy += g4_gravity;

		if (g4_jumpcount>=8) {
			g4cy -= (g4_gravity-5);
			g4_rising = false;
			g4_downing = true;
		}
		locateObject(g4ch, g4_scene, g4cx, g4cy);

		g4_jumpcount++;
		setTimer(g4_jump_t, 0.03f);
		startTimer(g4_jump_t);
	}
	else //착지
	{
		g4cy -= g4_gravity-5;
		//ch사진에서 20*0.7은 가로의 왼쪽 여백, 10*0.7은 세로의 아래부분 여백
		if (((g4cx+20*0.7) < (g4_bottomx[0] + 1100*0.4)) && ((g4cx + 20*0.7 +g4_ch_width) > g4_bottomx[0]) && ((g4cy+10*0.7) < (g4_bottomy[0] + (290-20)*0.4)) && ((g4cy+10*0.7 + g4_ch_height) > g4_bottomy[0])) {
			g4cy += (g4_gravity-5);
			g4_island = true;
			stopTimer(g4_jump_t);
	 	}
		for (int i = 1; i <= 3; i++) {
			if (((g4cx + 20 * 0.7) < (g4_bottomx[i] + 150)) && ((g4cx + 20 * 0.7 + g4_ch_width) > g4_bottomx[i]) && ((g4cy + 10 * 0.7) < (g4_bottomy[i]+4 + 27)) && ((g4cy + 10 * 0.7 + g4_ch_height) > g4_bottomy[i]+4)) {
				g4cy += (g4_gravity-5);
				g4_island = true;
				g4_downing = false;
				stopTimer(g4_jump_t);
			}
		}

		locateObject(g4ch, g4_scene, g4cx, g4cy);
		if (g4_island == false) {
			setTimer(g4_jump_t, 0.03f);
			startTimer(g4_jump_t);
		}
	}
}

//캐릭터 공격
void g4_attack() {

		g4_attackeffectx[0] = g4cx + 5;
		g4_attackeffecty[0] = g4cy + 50 * 0.7;
		locateObject(g4_attackeffect[0], g4_scene, g4_attackeffectx[0], g4_attackeffecty[0]);
		showObject(g4_attackeffect[0]);
		startTimer(g4_effectmove_t);
}
//캐릭터 공격
void g4_attack2() {

	g4_attackeffectx[1] = g4cx + 5;
	g4_attackeffecty[1] = g4cy + 50 * 0.7;
	locateObject(g4_attackeffect[1], g4_scene, g4_attackeffectx[1], g4_attackeffecty[1]);
	showObject(g4_attackeffect[1]);
	startTimer(g4_effectmove2_t);
}


// boss 움직임
void g4_bossmove() {
	if (g4_beaming == false) {
		//방향 정하기
		if (g4_bossy <= -100) {
			g4_bossway = true;
		}
		if (g4_bossy >= 500) {
			g4_bossway = false;
		}

		//좌표 바꾸기
		if (g4_bossway == false) {
			g4_bossy -= g4_bossspeed;
		}
		if (g4_bossway == true) {
			g4_bossy += g4_bossspeed;
		}

		//이동하기
		locateObject(g4_boss, g4_scene, g4_bossx, g4_bossy);
	}
}

//보스 공격1
void g4_bossattack() {
	if (g4_beaming == false) {
		g4_firex = 750;
		g4_firey = g4cy;

		locateObject(g4_fire, g4_scene, g4_firex, g4_firey);
		locateObject(g4_square, g4_scene, g4_firex, g4_firey - 10);
		showObject(g4_fire);
		showObject(g4_square);
		playSound(g4_firebgm);
		startTimer(g4_firemove_t);
	}
}
//보스 공격2 빔
void g4_beamfunc() {
	g4_bossy = g4cy - 100;
	locateObject(g4_boss, g4_scene, g4_bossx, g4_bossy);
	g4_beamx = -400;
	g4_beamy = g4_bossy + 150;
	locateObject(g4_beam[0], g4_scene, g4_beamx, g4_beamy);
	setObjectImage(g4_boss, "image/game4/dragon3.png");
	showObject(g4_beam[0]);
	startTimer(g4_beam_t);
	playSound(g4_breathbgm);
}
//보스 체력
void g4_heartfunc() {
	if (g4_attackable1&&((g4_attackeffectx[0]) < (g4_bossx + 30)) && ((g4_attackeffectx[0]) > (g4_bossx)) && ((g4_attackeffecty[0]) < (g4_bossy + 270*1.2)) && ((g4_attackeffecty[0]+15) > (g4_bossy))) {
		if(g4_heartnum>0)g4_heartnum--;
		setObjectImage(g4_heart, g4_heartimage[g4_heartnum]);
		g4_attackable1 = false;
	}
	if (g4_attackable2&&((g4_attackeffectx[1]) < (g4_bossx + 30)) && ((g4_attackeffectx[1]) > (g4_bossx)) && ((g4_attackeffecty[1]) < (g4_bossy + 270 * 1.2)) && ((g4_attackeffecty[1] + 15) > (g4_bossy))) {
		if (g4_heartnum > 0)g4_heartnum--;
		setObjectImage(g4_heart, g4_heartimage[g4_heartnum]);
		g4_attackable2 = false;
	}
}
//초기화
void g4_restart() {
	stopTimer(g4_move_t);
	stopTimer(g4_update_t);
	stopTimer(g4_block_t);
	stopTimer(g4_effectmove_t);
	stopTimer(g4_effectmove2_t);
	stopTimer(g4_posture1_t);
	stopTimer(g4_posture2_t);
	stopTimer(g4_jump_t);
	stopTimer(g4_bossmove_t);
	stopTimer(g4_bossanimation_t);
	stopTimer(g4_beam_t);
	stopTimer(g4_firecool_t);
	stopTimer(g4_beamcool_t);
	stopTimer(g4_hidesquare_t);
	stopTimer(g4_hidebeam_t);
	stopTimer(g4_heart_t);
	setTimer(g4_move_t, 0.01f);
	setTimer(g4_update_t, 0.01f);
	setTimer(g4_block_t, 0.03f);
	setTimer(g4_effectmove_t, 0.01f);
	setTimer(g4_effectmove2_t, 0.01f);
	setTimer(g4_posture1_t, 0.03f);
	setTimer(g4_posture2_t, 0.03f);
	setTimer(g4_jump_t, 0.03f);
	setTimer(g4_bossmove_t, 0.01f);
	setTimer(g4_bossanimation_t, 0.2f);
	setTimer(g4_firemove_t, 0.01f);
	setTimer(g4_beam_t, 0.9f);
	setTimer(g4_firecool_t, 2.0f);
	setTimer(g4_beamcool_t, 5.f);
	setTimer(g4_hidesquare_t, 1.f);
	setTimer(g4_hidebeam_t, 1.5f);
	setTimer(g4_heart_t, 0.01f);
	locateObject(g4ch, g4_scene, 30, 390 * 0.4 - 1);
	locateObject(g4_attackeffect[0], g4_scene, 1500, 800);
	locateObject(g4_attackeffect[1], g4_scene, 1500, 800);
	locateObject(g4_fire, g4_scene, 1500, 800);
	locateObject(g4_square, g4_scene, 1500, 800);
	locateObject(g4_beam[0], g4_scene, 1500, 800);
	locateObject(g4_beam[1], g4_scene, 1500, 800);
	setObjectImage(g4ch, "image/game4/ch1.png");
	setObjectImage(g4_boss, "image/game4/dragon1.png");
	setObjectImage(g4_heart, "image/game4/heart16.png");
	setObjectImage(g4_fire, "image/game4/fire1.png");
	setObjectImage(g4_square, "image/game4/square1.png");
	g4dx = 0, g4cx = 30, g4cy = 270 * 0.4 - 1;
	g4_firex = 1500, g4_firey = 1500, g4_beamx = 1500, g4_beamy = 1500, g4_firecount = 0, g4_heartnum = 15;
	g4_bossx = 850, g4_bossy = 300;
	g4_attacking1 = false, g4_attacking2 = false, g4_jumping = false, g4_rising = false, g4_downing = false, g4_island = true, g4_posture1 = true, g4_posture2 = true;
	g4_bossway = true, g4_beaming = false, g4_beamok = false;
	g4_bossanimation_count = 0;
	g4_playing = false;
}
//death
void g4_death() {
		if (((g4cx + 20 * 0.7) < (g4_firex + 100)) && ((g4cx + 20 * 0.7 + g4_ch_width) > g4_firex) && ((g4cy + 10 * 0.7) < (g4_firey + 67)) && ((g4cy + 10 * 0.7 + g4_ch_height) > (g4_firey + 22))) {
			
			g4_restart();
			showObject(g4_deathback);
			showObject(g4_gomapbutton);
			showObject(g4_restartbutton);
		}
		if (g4_beamok == true) {
			if (((g4cx + 20 * 0.7) < (g4_beamx + 1280)) && ((g4cx + 20 * 0.7 + g4_ch_width) > g4_beamx) && ((g4cy + 10 * 0.7) < (g4_beamy - 50 + 150)) && ((g4cy + 10 * 0.7 + g4_ch_height) > (g4_beamy - 50))) {

				g4_restart();
				showObject(g4_deathback);
				showObject(g4_gomapbutton);
				showObject(g4_restartbutton);
			}
		}
		if (g4cy <= 0) {
			g4_restart();
			showObject(g4_deathback);
			showObject(g4_gomapbutton);
			showObject(g4_restartbutton);
		}
}
void g4_clear() {
	if (g4_heartnum == 0) {

		g4_restart();
		hideObject(g4_boss);
		hideObject(g4_heart);
		showObject(g4_clearback);
		showObject(g4_endingbutton);
	}
}

// ending ch 움직임
void g4_endingchmove() {
		//좌표 바꾸기
			g4_endingchx += 10;
		//이동하기
		locateObject(g4_endingch, g4_scene2, g4_endingchx, g4_endingchy);
	
}

// 마우스콜백함수
void game4_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g4_gomapbutton) {
		hideObject(g4_deathback);
		hideObject(g4_gomapbutton);
		hideObject(g4_restartbutton);
		showObject(g4_startbutton);
		enterScene(mapscene);
		stopSound(g4_mapbgm);
		playSound(introbgm);
	}
	if (object == g4_restartbutton) {
		hideObject(g4_deathback);
		hideObject(g4_gomapbutton);
		hideObject(g4_restartbutton);
		showObject(g4_startbutton);
	}

	if (object == g4_startbutton) {
		g4_playing = true;
		startTimer(g4_beamcool_t);
		startTimer(g4_firecool_t);
		startTimer(g4_bossanimation_t);
		startTimer(g4_bossmove_t);
		startTimer(g4_block_t);
		startTimer(g4_update_t);
		startTimer(g4_move_t);
		startTimer(g4_heart_t);
		hideObject(g4_startbutton);
		hideObject(g4_deathback);
		hideObject(g4_gomapbutton);
		hideObject(g4_restartbutton);
	}

	if (object == g4_endingbutton) {
		showObject(g4_startbutton);
		hideObject(g4_clearback);
		hideObject(g4_endingbutton);
		enterScene(g4_scene2);
		startTimer(g4_ending_t);
		startTimer(g4_endanimation_t);
		stopSound(g4_mapbgm);
		playSound(g4_endingbgm);

	}
	if (object == g4_endgame) {
		endGame();
	}
}

//타이머콜백함수
void game4_timerCallback(TimerID timer) {
	//캐릭터 움직임
	if (timer == g4_move_t) {
		g4cx += g4dx; 

		locateObject(g4ch, g4_scene, g4cx, g4cy);
		setTimer(g4_move_t, 0.01f);
		startTimer(g4_move_t);
	}
	//점프
	if (timer == g4_jump_t) {
		g4_jump();

	}

	if (timer == g4_update_t) {
		//점프 관련
		if (g4_jumping == true) {
			if (g4_island == true) {
				g4_jumpcount = 0;
				g4_rising = true;
				g4_island = false;
				startTimer(g4_jump_t);
			}
		}

		setTimer(g4_update_t, 0.01f);
		startTimer(g4_update_t);
	}
	
	if (timer == g4_block_t) {
		g4_block();

		setTimer(g4_block_t, 0.03f);
		startTimer(g4_block_t);
	}

	//투사체
	if (timer == g4_effectmove_t) {

		g4_attackeffectx[0] += g4_effectspeed;
		locateObject(g4_attackeffect[0], g4_scene, g4_attackeffectx[0], g4_attackeffecty[0]);

		if (g4_posture1) {
			startTimer(g4_posture1_t);
			g4_posture1 = false;
		}
		//없어지는 조건
		if (g4_attackeffectx[0]>1280) {
			hideObject(g4_attackeffect[0]); locateObject(g4_attackeffect[0], g4_scene, 1500, 800);
			g4_attackable1 = true;
			g4_attacking1 = false;
			g4_posture1 = true;
		}
		//공격중이면 타이머 다시
		if (g4_attacking1 == true) {
			setTimer(g4_effectmove_t, 0.01f);
			startTimer(g4_effectmove_t);
		}
	}
	//투사체2
	if (timer == g4_effectmove2_t) {

		g4_attackeffectx[1] += g4_effectspeed;
		locateObject(g4_attackeffect[1], g4_scene, g4_attackeffectx[1], g4_attackeffecty[1]);

		if (g4_posture2) {
			startTimer(g4_posture1_t);
			g4_posture2 = false;
		}
		//없어지는 조건
		if (g4_attackeffectx[1] > 1280) {
			g4_attackable2 = true;
			hideObject(g4_attackeffect[1]); locateObject(g4_attackeffect[1], g4_scene, 1500, 800);
			g4_attacking2 = false;
			g4_posture2 = true;
		}
		//공격중이면 타이머 다시
		if (g4_attacking2 == true) {
			setTimer(g4_effectmove2_t, 0.01f);
			startTimer(g4_effectmove2_t);
		}
	}

	//공격후 자세바꾸기
	if (timer == g4_posture1_t) {
		setObjectImage(g4ch, "image/game4/ch3.png");
		startTimer(g4_posture2_t);
		setTimer(g4_posture1_t, 0.03f);
	}
	//공격후 자세바꾸기
	if (timer == g4_posture2_t) {
		setObjectImage(g4ch, "image/game4/ch1.png");
		setTimer(g4_posture2_t, 0.03f);
	}
	
	//드래곤 움직이기
	if (timer == g4_bossmove_t) {
		g4_bossmove();
		setTimer(g4_bossmove_t, 0.01f);
		startTimer(g4_bossmove_t);
	}
	//드래곤 날개 애니메이션
	if (timer == g4_bossanimation_t) {
		if (g4_beaming == false) {
			setObjectImage(g4_boss, g4_bossimage[g4_bossanimation_count % 2]);
			g4_bossanimation_count++;

			setTimer(g4_bossanimation_t, 0.2f);
			startTimer(g4_bossanimation_t);
		}
	}
	//드래곤 공격
	if (timer == g4_firemove_t) {
		g4_firex -= g4_effectspeed;
		locateObject(g4_fire, g4_scene, g4_firex, g4_firey);
		startTimer(g4_hidesquare_t);

		if (g4_firex < 0) {

			g4_firecount++;
			if (g4_firecount % 3 == 0) {
				setObjectImage(g4_fire, "image/game4/fire1.png");
				setObjectImage(g4_square, "image/game4/square1.png");
			}
			else if (g4_firecount % 3 == 1) {
				setObjectImage(g4_fire, "image/game4/fire2.png");
				setObjectImage(g4_square, "image/game4/square2.png");
			}
			else if (g4_firecount % 3 == 2) {
				setObjectImage(g4_fire, "image/game4/fire3.png");
				setObjectImage(g4_square, "image/game4/square3.png");
			}
			hideObject(g4_fire);
		}
		else {
			setTimer(g4_firemove_t, 0.05f);
			startTimer(g4_firemove_t);
		}
	}
	if (timer == g4_firecool_t) {
		g4_bossattack();
		setTimer(g4_firecool_t, 2.0f);
		startTimer(g4_firecool_t);
	}
	if (timer == g4_hidesquare_t) {
		hideObject(g4_square);
		setTimer(g4_hidesquare_t, 1.5f);
	}
	//드래곤 공격2
	if (timer == g4_beam_t) {
		setObjectImage(g4_boss, "image/game4/dragon4.png");
		locateObject(g4_beam[1], g4_scene, g4_beamx, g4_beamy);
		showObject(g4_beam[1]);
		g4_beamok = true;
		setTimer(g4_beam_t, 0.9f);
		startTimer(g4_hidebeam_t);


	}
	if (timer == g4_beamcool_t) {
		g4_beaming = true;
		g4_beamfunc();

		setTimer(g4_beamcool_t, 5.f);
		startTimer(g4_beamcool_t);
	}
	if (timer == g4_hidebeam_t) {
		hideObject(g4_beam[0]);
		hideObject(g4_beam[1]);
		g4_beaming = false;
		g4_beamok = false;
		g4_beamx = 900;
		g4_beamy = 900;
		setObjectImage(g4_boss, "image/game4/dragon2.png");
		locateObject(g4_beam[0], g4_scene, g4_beamx, g4_beamy);
		locateObject(g4_beam[1], g4_scene, g4_beamx, g4_beamy);
		setTimer(g4_hidebeam_t, 1.5f);
		setTimer(g4_bossanimation_t, 0.2f);
		startTimer(g4_bossanimation_t);
	}
	if (timer == g4_ending_t) {
		g4_endingchmove();
		startTimer(g4_endanimation_t);
		setTimer(g4_ending_t, 0.3f);
		startTimer(g4_ending_t);
	}
	if (timer == g4_endanimation_t) {
		g4_endcount++;
		if (g4_endcount % 3 == 0) {
			setObjectImage(g4_endingch, "image/game4/endingch1.png");
		}
		else if (g4_endcount % 3 == 1) {
			setObjectImage(g4_endingch, "image/game4/endingch2.png");
		}
		else if (g4_endcount % 3 == 2) {
			setObjectImage(g4_endingch, "image/game4/endingch3.png");
		}
		if (g4_endcount >= 100) {
			stopTimer(g4_endanimation_t);
			stopTimer(g4_ending_t);
			showObject(g4_endgame);
		}
		if (g4_endcount <= 100) {
			setTimer(g4_endanimation_t, 0.3f);
			startTimer(g4_endanimation_t);
		}
	}
	if (timer == g4_heart_t) {
		g4_heartfunc();
		setTimer(g4_heart_t, 0.01f);
		startTimer(g4_heart_t);
	}

}

//사운드콜백함수
void game4_soundCallback(SoundID sound) {
	if (sound == g4_mapbgm) {
		playSound(g4_mapbgm);
	}
}

//키보드콜백함수
void game4_keyboardCallback(KeyCode code, KeyState state) {
	if (nowgamenum == 4 && g4_playing) {
		if (code == KeyCode::KEY_UP_ARROW) {			// UP
			g4_jumping += (state == KeyState::KEY_PRESSED ? 1 : -1);

		}
		if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
			g4dx += (state == KeyState::KEY_PRESSED ? g4_speed : -g4_speed);
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
			g4dx -= (state == KeyState::KEY_PRESSED ? g4_speed : -g4_speed);

		}
		if (code == KeyCode::KEY_SPACE) {
			if (state == KeyState::KEY_PRESSED) {
				if (g4_attacking1 == false) {
					setObjectImage(g4ch, "image/game4/ch2.png");
					g4_attacking1 = true;
					g4_attack();
				}
				else if (g4_attacking2 == false) {
					setObjectImage(g4ch, "image/game4/ch2.png");
					g4_attacking2 = true;
					g4_attack2();
				}
			}
		}
	}
	else if (nowgamenum == 4 && !g4_playing) {
		if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
			g4dx += (state == KeyState::KEY_PRESSED ? g4_speed : -g4_speed);
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
			g4dx -= (state == KeyState::KEY_PRESSED ? g4_speed : -g4_speed);

		}
	}
}

void game4_main() {

	//배경
	g4_scene = createScene("game4", "image/game4/game4back.png");
	g4_scene2 = createScene("game4", "image/game4/gameending.png");
	//캐릭터
	g4ch = createObject("image/game4/ch1.png", g4_scene, g4cx, g4cy, true, 0.7f);
	g4_endingch = createObject("image/game4/endingch1.png", g4_scene2, g4_endingchx, g4_endingchy, true, 0.7f);
	//바닥
	g4_floor[0]= createObject("image/game4/floor1.png", g4_scene, -150, 0, true, 0.4f); // 가로: 1100*0.4 세로:290*0.4
	g4_floor[1] = createObject("image/game4/floor2.png", g4_scene, 50, 240, true, 1.f); // 가로 : 150     세로: 40
	g4_floor[2] = createObject("image/game4/floor2.png", g4_scene, 50, 390, true, 1.f); // 가로 : 150     세로: 40
	g4_floor[3] = createObject("image/game4/floor2.png", g4_scene, 50, 540, true, 1.f); // 가로 : 150     세로: 40
	//투사체
	g4_attackeffect[0] = createObject("image/game4/arrow.png", g4_scene, 1500, 800, false, 1.f);
	g4_attackeffect[1] = createObject("image/game4/arrow.png", g4_scene, 1500, 800, false, 1.f);
	//보스몹
	g4_boss = createObject("image/game4/dragon1.png", g4_scene, 850, 300, true, 1.2f);
	//보스몹 공격
	g4_fire = createObject("image/game4/fire1.png", g4_scene, 1500, 300, true, 1.f);
	g4_square = createObject("image/game4/square1.png", g4_scene, 1500, 300, true, 1.f);
	g4_beam[0] = createObject("image/game4/beam1.png", g4_scene, 1500, 300, true, 1.f);
	g4_beam[1] = createObject("image/game4/beam2.png", g4_scene, 1500, 300, true, 1.f);
	//체력바
	g4_heart = createObject(g4_heartimage[15], g4_scene, 400, 650, true, 0.6f);
	//버튼들
	g4_clearback = createObject("image/clear.png", g4_scene, 270, 300, false, 1.5f);
	g4_deathback = createObject("image/gameover.png", g4_scene, 270, 300, false, 1.5f);
	g4_restartbutton = createObject("image/restart.png", g4_scene, 700, 200, false, 1.3f);
	g4_startbutton = createObject("image/start.png", g4_scene, 450, 300, true, 0.8f);
	g4_endingbutton = createObject("image/ending.png", g4_scene, 500, 100, false, 1.3f);
	g4_endgame = createObject("image/end.png", g4_scene2, 550, 450, false, 0.8f);
	g4_gomapbutton = createObject("image/gomap.png", g4_scene, 300, 200, false, 1.3f);

	//타이머들
	g4_move_t = createTimer(0.01f);

	g4_update_t = createTimer(0.01f);

	g4_block_t = createTimer(0.03f);

	g4_effectmove_t = createTimer(0.01f);

	g4_effectmove2_t = createTimer(0.01f);

	g4_posture1_t = createTimer(0.03f);

	g4_posture2_t = createTimer(0.03f);

	g4_jump_t = createTimer(0.03f);

	g4_bossmove_t = createTimer(0.01f);

	g4_bossanimation_t = createTimer(0.2f);

	g4_firemove_t = createTimer(0.01f);

	g4_beam_t = createTimer(0.9f);

	g4_firecool_t = createTimer(2.0f);

	g4_beamcool_t = createTimer(5.f);

	g4_hidesquare_t = createTimer(1.f);

	g4_hidebeam_t = createTimer(1.5f);

	g4_endanimation_t = createTimer(0.3f);

	g4_ending_t = createTimer(0.3f);

	g4_heart_t = createTimer(0.01f);
	//소리
	g4_mapbgm = createSound("sound/game4/bossmap.mp3");
	g4_endingbgm = createSound("sound/game4/ending.mp3");
	g4_breathbgm = createSound("sound/game4/breath.mp3");
	g4_firebgm = createSound("sound/game4/fire.mp3");
}