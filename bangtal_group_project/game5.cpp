#define _CRT_SECURE_NO_WARNINGS
#define g5_ch_x 95*0.7
#define g5_ch_y 100*0.7
#define g5_effect_x 342*0.3 
#define g5_effect_y 261*0.3

#include <stdio.h>
#include <bangtal.h>

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SceneID mapscene;
extern bool g5_cleared;

void g5_exam(int x, int y);

int g5_skeleton3_x[32] = { 0,150,0,0,0,0,84,84,168,380,380,380,380,380,380,380,542,542,542,542,542,542,542,461,780,860,940,1020,1100,785,1100,785 };
int g5_skeleton3_y[32] = { 130,220,310,460,550,640,460,640,640,640,550,460,370,280,190,100,640,550,460,370,280,190,100,640,0,637,0,637,0,500,400,300 };
int g5_skeleton3_xb[32] = { 0,150,0,0,0,0,84,84,168,380,380,380,380,380,380,380,542,542,542,542,542,542,542,461,780,860,940,1020,1100,785,1100,785 };
int g5_skeleton3_yb[32] = { 130,220,310,460,550,640,460,640,640,640,550,460,370,280,190,100,640,550,460,370,280,190,100,640,0,637,0,637,0,500,400,300 };
int g5_box_xs3[6] = { 650,650,650,700,700,700 };
int g5_box_ys3[6] = { 0,50,100,0,50,100 };
int g5_box_xs3b[6] = { 650,650,650,700,700,700 };
int g5_box_ys3b[6] = { 0,50,100,0,50,100 };

int g5_speed = 8, g5dx = 0, g5dy = 0, g5cx = 0, g5cy = 0, g5_skeleton_speed = 3, g5_chway = 3, g5_attackeffectx, g5_attackeffecty, g5_effectspeed = 4;
long long g5_attacknum = 2;

int g5_skeletonway3[32][4] = { 0, };
int g1_skeletonway3b[32][4] = { 0, };

int g5_timecheck = 0;

bool g5_attacking = false;

SceneID g5_scene;
ObjectID g5_tree3[38], g5ch, g5_skeleton3[32][8], g5_clear_zone, g5_attackeffect[4], g5_boxs3[6], g5_gomapbutton, g5_restartbutton, g5_nextbutton, g5_deathback, g5_clearback;
TimerID g5_move_t, g5_moveskeleton_t, g5_update_t, g5_effectmove_t, g5_skeletoneimage_t;
SoundID g5_boxsound;

ObjectID g5_thorns3[42];

void g5_install_s3()
{
	int i;

	for (int i = 0; i < 32; i++)
	{
		g5_skeleton3_x[i] = g5_skeleton3_xb[i];
		g5_skeleton3_y[i] = g5_skeleton3_yb[i];
		for (int j = 0; j < 4; j++)
		{
			g5_skeletonway3[i][j] = g1_skeletonway3b[i][j];
		}
	}

	g5_clear_zone = createObject("image/game1/g1_clearzone.png", g5_scene, 1180, 0, true, 1.f);

	for (i = 0; i < 7; i++)
	{
		g5_tree3[i] = createObject("image/game1/g1_tree1.png", g5_scene, 200, i * 90, true, 1.f);
		g5_tree3[i + 7] = createObject("image/game1/g1_tree1.png", g5_scene, 270, i * 90, true, 1.f);
	}

	for (i = 0; i < 5; i++)
	{
		g5_tree3[i + 14] = createObject("image/game1/g1_tree1.png", g5_scene, 610, 150 + i * 90, true, 1.f);
		g5_tree3[i + 19] = createObject("image/game1/g1_tree1.png", g5_scene, 680, 150 + i * 90, true, 1.f);
	}

	for (i = 0; i < 7; i++)
	{
		g5_tree3[i + 24] = createObject("image/game1/g1_tree1.png", g5_scene, 1150, 100 + i * 90, true, 1.f);
		g5_tree3[i + 31] = createObject("image/game1/g1_tree1.png", g5_scene, 1220, 100 + i * 90, true, 1.f);
	}

	for (i = 0; i < 2; i++)
	{
		g5_thorns3[i] = createObject("image/game1/g1_thorn.png", g5_scene, 75, 560 + i * 25, true, 1);
		g5_thorns3[i + 2] = createObject("image/game1/g1_thorn.png", g5_scene, 100, 560 + i * 25, true, 1);
	}
	for (i = 0; i < 19; i++)
	{
		g5_thorns3[i + 4] = createObject("image/game1/g1_thorn.png", g5_scene, 465, 140 + i * 25, true, 1);
		g5_thorns3[i + 23] = createObject("image/game1/g1_thorn.png", g5_scene, 490, 140 + i * 25, true, 1);
	}

	for (i = 0; i < 6; i++)
	{
		g5_boxs3[i] = createObject("image/game1/g1_box.png", g5_scene, g5_box_xs3[i], g5_box_ys3[i], true, 1);
	}


	for (i = 0; i < 32; i++)
	{
		g5_skeleton3[i][0] = createObject("image/game1/g1_skeleton1.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][1] = createObject("image/game1/g1_skeleton2.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][2] = createObject("image/game1/g1_skeleton3.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][3] = createObject("image/game1/g1_skeleton4.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][4] = createObject("image/game1/g1_skeleton5.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][5] = createObject("image/game1/g1_skeleton6.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][6] = createObject("image/game1/g1_skeleton7.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
		g5_skeleton3[i][7] = createObject("image/game1/g1_skeleton8.png", g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i], false, 0.25f);
	}

}

void g5_blocks3()
{
	if (g5cx < 0 || g5cx + g5_ch_x>1280 || g5cy < 0 || g5cy + g5_ch_y>720) {
		g5cx -= g5dx; g5cy -= g5dy;
	}
	if ((g5cx + g5_ch_x < 410 && g5cx + g5_ch_x>230) && g5cy + g5_ch_y < 690) {
		g5cx -= g5dx; g5cy -= g5dy;
	}
	if ((g5cx + g5_ch_x < 820 && g5cx + g5_ch_x>640) && (g5cy + g5_ch_y < 670 && g5cy + g5_ch_y >160)) {
		g5cx -= g5dx; g5cy -= g5dy;
	}
	if ((g5cx + g5_ch_x > 1180) && g5cy + g5_ch_y > 100) {
		g5cx -= g5dx; g5cy -= g5dy;
	}
	if (g5cx > 300)
	{
		for (int i = 0; i < 6; i++) {
			if ((g5cx < (g5_box_xs3[i] + 50)) && (g5cx + g5_ch_x > g5_box_xs3[i]) && (g5cy < (g5_box_ys3[i] + 50)) && (g5cy + g5_ch_y > g5_box_ys3[i])) {
				g5cx -= g5dx; g5cy -= g5dy;
			}
		}
	}

}

void g5_skeletonmoves3()
{
	int i, j;

	if (g5_skeleton3_x[0] >= 145)
	{
		for (i = 0; i < 4; i++)
		{
			g5_skeletonway3[0][i] = 0;
			g5_skeletonway3[1][i] = 0;
			g5_skeletonway3[2][i] = 0;
		}
		g5_skeletonway3[0][2] = 1;
		g5_skeletonway3[1][3] = 1;
		g5_skeletonway3[2][2] = 1;
	}
	else if (g5_skeleton3_x[0] <= 5)
	{
		for (i = 0; i < 4; i++)
		{
			g5_skeletonway3[0][i] = 0;
			g5_skeletonway3[1][i] = 0;
			g5_skeletonway3[2][i] = 0;
		}
		g5_skeletonway3[0][3] = 1;
		g5_skeletonway3[1][2] = 1;
		g5_skeletonway3[2][3] = 1;
	}

	for (i = 3; i < 9; i++)
	{
		if (g5_skeleton3_x[i] <= 0 && g5_skeleton3_y[i] <= 460)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][0] = 1;
		}
		if (g5_skeleton3_x[i] >= 168 && g5_skeleton3_y[i] >= 640)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][1] = 1;
		}
		if (g5_skeleton3_y[i] >= 640 && g5_skeleton3_x[i] <= 0)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][3] = 1;
		}
		if (g5_skeleton3_y[i] <= 460 && g5_skeleton3_x[i] >= 168)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][2] = 1;
		}
	}

	for (i = 9; i < 24; i++)
	{
		if (g5_skeleton3_x[i] <= 380 && g5_skeleton3_y[i] >= 640)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][1] = 1;
		}
		if (g5_skeleton3_x[i] <= 380 && g5_skeleton3_y[i] <= 58)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][3] = 1;
		}
		if (g5_skeleton3_y[i] <= 58 && g5_skeleton3_x[i] >= 542)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][0] = 1;
		}
		if (g5_skeleton3_y[i] >= 640 && g5_skeleton3_x[i] >= 542)
		{
			for (j = 0; j < 4; j++)
			{
				g5_skeletonway3[i][j] = 0;
			}
			g5_skeletonway3[i][2] = 1;
		}
	}

	if (g5_skeleton3_y[24] >= 637)
	{
		for (i = 0; i < 4; i++)
		{
			g5_skeletonway3[24][i] = 0;
			g5_skeletonway3[25][i] = 0;
			g5_skeletonway3[26][i] = 0;
			g5_skeletonway3[27][i] = 0;
			g5_skeletonway3[28][i] = 0;
		}
		g5_skeletonway3[24][1] = 1;
		g5_skeletonway3[25][0] = 1;
		g5_skeletonway3[26][1] = 1;
		g5_skeletonway3[27][0] = 1;
		g5_skeletonway3[28][1] = 1;
	}
	else if (g5_skeleton3_y[24] <= 0)
	{
		for (i = 0; i < 4; i++)
		{
			g5_skeletonway3[24][i] = 0;
			g5_skeletonway3[25][i] = 0;
			g5_skeletonway3[26][i] = 0;
			g5_skeletonway3[27][i] = 0;
			g5_skeletonway3[28][i] = 0;
		}
		g5_skeletonway3[24][0] = 1;
		g5_skeletonway3[25][1] = 1;
		g5_skeletonway3[26][0] = 1;
		g5_skeletonway3[27][1] = 1;
		g5_skeletonway3[28][0] = 1;
	}


	if (g5_skeleton3_x[29] >= 1100)
	{
		for (i = 0; i < 4; i++)
		{
			g5_skeletonway3[29][i] = 0;
			g5_skeletonway3[30][i] = 0;
			g5_skeletonway3[31][i] = 0;
		}
		g5_skeletonway3[29][2] = 1;
		g5_skeletonway3[30][3] = 1;
		g5_skeletonway3[31][2] = 1;
	}
	else if (g5_skeleton3_x[29] <= 785)
	{
		for (i = 0; i < 4; i++)
		{
			g5_skeletonway3[29][i] = 0;
			g5_skeletonway3[30][i] = 0;
			g5_skeletonway3[31][i] = 0;
		}
		g5_skeletonway3[29][3] = 1;
		g5_skeletonway3[30][2] = 1;
		g5_skeletonway3[31][3] = 1;
	}

	//좌표변경
	for (i = 0; i < 32; i++)
	{
		if (g5_skeletonway3[i][0] == 1)
		{
			g5_skeleton3_y[i] += g5_skeleton_speed;
		}
		else if (g5_skeletonway3[i][1] == 1)
		{
			g5_skeleton3_y[i] -= g5_skeleton_speed;
		}
		else if (g5_skeletonway3[i][2] == 1)
		{
			g5_skeleton3_x[i] -= g5_skeleton_speed;
		}
		else if (g5_skeletonway3[i][3] == 1)
		{
			g5_skeleton3_x[i] += g5_skeleton_speed;
		}
	}

	//이동시키기
	for (i = 0; i < 32; i++) {
		for (int j = 0; j < 8; j++)
		{
			locateObject(g5_skeleton3[i][j], g5_scene, g5_skeleton3_x[i], g5_skeleton3_y[i]);
		}
	}
}

void g5_attack() {

	if (g5_chway == 0) {
		g5_attackeffectx = g5cx + 5;
		g5_attackeffecty = g5cy - 5;
		locateObject(g5_attackeffect[0], g5_scene, g5_attackeffectx, g5_attackeffecty);
		showObject(g5_attackeffect[0]);
		startTimer(g5_effectmove_t);
	}
	if (g5_chway == 1) {
		g5_attackeffectx = g5cx - 50;
		g5_attackeffecty = g5cy - 5;
		locateObject(g5_attackeffect[1], g5_scene, g5_attackeffectx, g5_attackeffecty);
		showObject(g5_attackeffect[1]);
		startTimer(g5_effectmove_t);
	}
	if (g5_chway == 2) {
		g5_attackeffectx = g5cx - 10;
		g5_attackeffecty = g5cy - 50;
		locateObject(g5_attackeffect[2], g5_scene, g5_attackeffectx, g5_attackeffecty);
		showObject(g5_attackeffect[2]);
		startTimer(g5_effectmove_t);
	}
	if (g5_chway == 3) {
		g5_attackeffectx = g5cx - 10;
		g5_attackeffecty = g5cy + 50;
		locateObject(g5_attackeffect[3], g5_scene, g5_attackeffectx, g5_attackeffecty);
		showObject(g5_attackeffect[3]);
		startTimer(g5_effectmove_t);
	}
}

void g5_boxdelete3()
{
	for (int i = 0; i < 6; i++) {
		if (((g5_attackeffectx + 50) < (g5_box_xs3[i] + 50)) && ((g5_attackeffectx + 50 + 342 * 0.3 - 50) > g5_box_xs3[i]) && ((g5_attackeffecty + 50) < (g5_box_ys3[i] + 50)) && ((g5_attackeffecty + 50 + 261 * 0.3 - 50) > (g5_box_ys3[i]))) {
			g5_box_xs3[i] = 1300, g5_box_ys3[i] = 800;
			playSound(g5_boxsound);
			locateObject(g5_boxs3[i], g5_scene, g5_box_xs3[i], g5_box_ys3[i]);
		}
	}

}

void g5_clear() {

	if ( (g5cx >= 1130 && g5cy <= 100)) {
		locateObject(g5_gomapbutton, g5_scene, 500, 200);
		showObject(g5_clearback);
		showObject(g5_gomapbutton);
		g5_cleared = true;
		stopTimer(g5_move_t);
		stopTimer(g5_moveskeleton_t);
		stopTimer(g5_update_t);
		stopTimer(g5_effectmove_t);
		stopTimer(g5_skeletoneimage_t);
		
	}
}

void g5_death_s3()
{
	int i;
	if (g5cx < 200)
	{
		for (i = 0; i < 2; i++)
		{
			g5_exam(75, 560 + i * 50);
			g5_exam(125, 560 + i * 50);
		}
	}
	if (g5cx > 300)
	{
		for (i = 0; i < 10; i++)
		{
			g5_exam(465, 140 + i * 50);
			g5_exam(515, 140 + i * 50);
		}
	}
	for (i = 0; i < 4; i++) {
		g5_exam(g5_skeleton3_x[i] + 10, g5_skeleton3_y[i] + 6);
		g5_exam(g5_skeleton3_x[i] + 40, g5_skeleton3_y[i] + 6);
		g5_exam(g5_skeleton3_x[i] + 10, g5_skeleton3_y[i] + 50);
		g5_exam(g5_skeleton3_x[i] + 40, g5_skeleton3_y[i] + 50);
	}
	for (i = 4; i < 32; i++) {
		g5_exam(g5_skeleton3_x[i] + 10, g5_skeleton3_y[i] + 6);
		g5_exam(g5_skeleton3_x[i] + 40, g5_skeleton3_y[i] + 6);
		g5_exam(g5_skeleton3_x[i] + 10, g5_skeleton3_y[i] + 50);
		g5_exam(g5_skeleton3_x[i] + 40, g5_skeleton3_y[i] + 50);
	}
}

void g5_exam(int x, int y)
{
	if ((g5cx + 9 <= x && g5cx + 45 >= x) && (g5cy + 5 <= y && g5cy + 45 >= y))
	{
		showObject(g5_deathback);
		showObject(g5_gomapbutton);
		showObject(g5_restartbutton);

		stopTimer(g5_move_t);
		stopTimer(g5_moveskeleton_t);
		stopTimer(g5_update_t);
		stopTimer(g5_effectmove_t);
		stopTimer(g5_skeletoneimage_t);
	}
}

void g5_restart() {
	hideObject(g5_restartbutton);
	hideObject(g5_gomapbutton);
	hideObject(g5_nextbutton);
	hideObject(g5_clearback);
	hideObject(g5_deathback);

	g5cx = 0, g5cy = 0, g5_attacknum = 1;
	g5_attacking = false;
	g5_chway = 3, g5dx = 0, g5dy = 0;
	g5_attackeffectx = 1500, g5_attackeffecty = 800;


	
	for (int i = 0; i < 6; i++)
		{
			g5_box_xs3[i] = g5_box_xs3b[i];
			g5_box_ys3[i] = g5_box_ys3b[i];
			locateObject(g5_boxs3[i], g5_scene, g5_box_xs3[i], g5_box_ys3[i]);
		}

	//위치
	locateObject(g5ch, g5_scene, g5cx, g5cy);

	locateObject(g5_attackeffect[0], g5_scene, 1500, 800);
	locateObject(g5_attackeffect[1], g5_scene, 1500, 800);
	locateObject(g5_attackeffect[2], g5_scene, 1500, 800);
	locateObject(g5_attackeffect[3], g5_scene, 1500, 800);

	setTimer(g5_move_t, 0.015f);
	setTimer(g5_moveskeleton_t, 0.02f);
	setTimer(g5_update_t, 0.01f);
	setTimer(g5_effectmove_t, 0.01f);

	startTimer(g5_move_t);
	startTimer(g5_moveskeleton_t);
	startTimer(g5_update_t);
	startTimer(g5_skeletoneimage_t);
}
// 마우스콜백함수
void game5_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g5_gomapbutton) {

		{
			for (int i = 0; i < 42; i++)
			{
				hideObject(g5_thorns3[i]);
			}
			for (int i = 0; i < 38; i++)
			{
				hideObject(g5_tree3[i]);
			}
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					hideObject(g5_skeleton3[i][j]);
				}
			}
			for (int i = 0; i < 6; i++)
			{
				hideObject(g5_boxs3[i]);
			}
			hideObject(g5_clear_zone);
			g5_install_s3();

		}
		g5_restart();
		g5_clearback = createObject("image/clear.png", g5_scene, 270, 300, false, 1.5f);
		g5_deathback = createObject("image/gameover.png", g5_scene, 270, 300, false, 1.5f);
		g5_restartbutton = createObject("image/restart.png", g5_scene, 700, 200, false, 1.3f);
		g5_nextbutton = createObject("image/next.png", g5_scene, 700, 200, false, 1.3f);
		g5_gomapbutton = createObject("image/gomap.png", g5_scene, 300, 200, false, 1.3f);

		enterScene(mapscene);

	}
	if (object == g5_restartbutton) {
		g5_restart();
	}


}

//타이머콜백함수
void game5_timerCallback(TimerID timer) {
	if (timer == g5_move_t) {
		if (nowgamenum == 5)
		{
			g5cx += g5dx; g5cy += g5dy;
			
			g5_blocks3();
			g5_boxdelete3();
			
		}
		locateObject(g5ch, g5_scene, g5cx, g5cy);
		setTimer(g5_move_t, 0.02f);
		startTimer(g5_move_t);
	}


	if (timer == g5_moveskeleton_t)
	{
		if (nowgamenum == 5)
		{
			g5_skeletonmoves3();
		}
		setTimer(g5_moveskeleton_t, 0.02f);
		startTimer(g5_moveskeleton_t);
	}

	

	if (timer == g5_skeletoneimage_t )
	{
		if (nowgamenum == 5)
		{
			if (g5_timecheck == 0)
			{
				g5_timecheck = 1;
			}
			else if (g5_timecheck == 1)
			{
				g5_timecheck = 0;
			}

			for (int i = 0; i < 32; i++)
			{
				if (g5_skeletonway3[i][0] == 1 && g5_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][6]);
				}
				else if (g5_skeletonway3[i][0] == 1 && g5_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][7]);
				}

				if (g5_skeletonway3[i][1] == 1 && g5_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][0]);
				}
				else if (g5_skeletonway3[i][1] == 1 && g5_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][1]);
				}

				if (g5_skeletonway3[i][2] == 1 && g5_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][2]);
				}
				else if (g5_skeletonway3[i][2] == 1 && g5_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][3]);
				}

				if (g5_skeletonway3[i][3] == 1 && g5_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][4]);
				}
				else if (g5_skeletonway3[i][3] == 1 && g5_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g5_skeleton3[i][j]);
					}
					showObject(g5_skeleton3[i][5]);
				}
			}
		}
		setTimer(g5_skeletoneimage_t, 0.25f);
		startTimer(g5_skeletoneimage_t);
	}

	if (timer == g5_update_t) {
		if (nowgamenum == 5)
		{
			g5_clear();
			g5_death_s3();
			
		}
		setTimer(g5_update_t, 0.01f);
		startTimer(g5_update_t);
	}

	if (timer == g5_effectmove_t) {
		//이동
		if (nowgamenum == 5)
		{
			if (g5_chway == 0) {
				g5_attackeffectx += g5_effectspeed;
				locateObject(g5_attackeffect[0], g5_scene, g5_attackeffectx, g5_attackeffecty);
				g5_attacknum++;
			}
			if (g5_chway == 1) {
				g5_attackeffectx -= g5_effectspeed;
				locateObject(g5_attackeffect[1], g5_scene, g5_attackeffectx, g5_attackeffecty);
				g5_attacknum++;
			}
			if (g5_chway == 2) {
				g5_attackeffecty -= g5_effectspeed;
				locateObject(g5_attackeffect[2], g5_scene, g5_attackeffectx, g5_attackeffecty);
				g5_attacknum++;
			}
			if (g5_chway == 3) {
				g5_attackeffecty += g5_effectspeed;
				locateObject(g5_attackeffect[3], g5_scene, g5_attackeffectx, g5_attackeffecty);
				g5_attacknum++;
			}
			//없어지는 조건
			if (g5_attacknum % 10 == 0) {
				hideObject(g5_attackeffect[0]); locateObject(g5_attackeffect[0], g5_scene, 1500, 800);
				hideObject(g5_attackeffect[1]); locateObject(g5_attackeffect[1], g5_scene, 1500, 800);
				hideObject(g5_attackeffect[2]); locateObject(g5_attackeffect[2], g5_scene, 1500, 800);
				hideObject(g5_attackeffect[3]); locateObject(g5_attackeffect[3], g5_scene, 1500, 800);
				g5_attacking = false;
				if (g5_chway == 0) setObjectImage(g5ch, "image/game1/player1.png");
				if (g5_chway == 1) setObjectImage(g5ch, "image/game1/player2.png");
				if (g5_chway == 2) setObjectImage(g5ch, "image/game1/player1.png");
				if (g5_chway == 3) setObjectImage(g5ch, "image/game1/player3.png");
			}
		}

		if (g5_attacking == true && nowgamenum == 5) {
			setTimer(g5_effectmove_t, 0.01f);
			startTimer(g5_effectmove_t);
		}
	}

}

//사운드콜백함수
void game5_soundCallback(SoundID sound) {

}

//키보드콜백함수
void game5_keyboardCallback(KeyCode code, KeyState state) {
	if (nowgamenum == 5) {
		if (code == KeyCode::KEY_UP_ARROW) {			// UP
			g5dy += (state == KeyState::KEY_PRESSED ? g5_speed : -g5_speed);
			g5_chway = 3;
			setObjectImage(g5ch, "image/game1/player3.png");
		}
		if (code == KeyCode::KEY_DOWN_ARROW) {		// DOWN
			g5dy -= (state == KeyState::KEY_PRESSED ? g5_speed : -g5_speed);
			g5_chway = 2;
			setObjectImage(g5ch, "image/game1/player1.png");
		}
		if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
			g5dx += (state == KeyState::KEY_PRESSED ? g5_speed : -g5_speed);
			setObjectImage(g5ch, "image/game1/player1.png");
			g5_chway = 0;
		}
		if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
			g5dx -= (state == KeyState::KEY_PRESSED ? g5_speed : -g5_speed);
			setObjectImage(g5ch, "image/game1/player2.png");
			g5_chway = 1;

		}
		if (code == KeyCode::KEY_SPACE) {
			if (state == KeyState::KEY_PRESSED) {
				if (g5_attacking == false) {
					if (g5_chway == 0) setObjectImage(g5ch, "image/game1/player1-1.png");
					if (g5_chway == 1) setObjectImage(g5ch, "image/game1/player2-1.png");
					if (g5_chway == 2) setObjectImage(g5ch, "image/game1/player1-1.png");
					if (g5_chway == 3) setObjectImage(g5ch, "image/game1/player3-1.png");
					g5_attacking = true;
					g5_attack();
				}
			}
		}
	}
}

void game5_main() {

	g5_scene = createScene("game5", "image/game1/g1_background.png");

	g5ch = createObject("image/game1/player1.png", g5_scene, g5cx, g5cy, true, 0.7f);

	g1_skeletonway3b[0][3] = 1;
	g1_skeletonway3b[1][2] = 1;
	g1_skeletonway3b[2][3] = 1;

	g1_skeletonway3b[3][0] = 1;
	g1_skeletonway3b[4][0] = 1;
	g1_skeletonway3b[5][0] = 1;
	g1_skeletonway3b[6][2] = 1;
	g1_skeletonway3b[7][3] = 1;
	g1_skeletonway3b[8][1] = 1;

	g1_skeletonway3b[9][1] = 1;
	g1_skeletonway3b[10][1] = 1;
	g1_skeletonway3b[11][1] = 1;
	g1_skeletonway3b[12][1] = 1;
	g1_skeletonway3b[13][1] = 1;
	g1_skeletonway3b[14][1] = 1;
	g1_skeletonway3b[15][1] = 1;
	g1_skeletonway3b[16][2] = 1;
	g1_skeletonway3b[17][0] = 1;
	g1_skeletonway3b[18][0] = 1;
	g1_skeletonway3b[19][0] = 1;
	g1_skeletonway3b[20][0] = 1;
	g1_skeletonway3b[21][0] = 1;
	g1_skeletonway3b[22][0] = 1;
	g1_skeletonway3b[23][2] = 1;

	g1_skeletonway3b[24][0] = 1;
	g1_skeletonway3b[25][1] = 1;
	g1_skeletonway3b[26][0] = 1;
	g1_skeletonway3b[27][1] = 1;
	g1_skeletonway3b[28][0] = 1;

	g1_skeletonway3b[29][3] = 1;
	g1_skeletonway3b[30][2] = 1;
	g1_skeletonway3b[31][3] = 1;


	g5_install_s3();
	

	//검격
	g5_attackeffect[0] = createObject("image/game1/1.png", g5_scene, 1500, 800, false, 0.3f);
	g5_attackeffect[1] = createObject("image/game1/0.png", g5_scene, 1500, 800, false, 0.3f);
	g5_attackeffect[2] = createObject("image/game1/2.png", g5_scene, 1500, 800, false, 0.3f);
	g5_attackeffect[3] = createObject("image/game1/3.png", g5_scene, 1500, 800, false, 0.3f);

	//clearback, deathback, gomap, restart, next 용

	g5_clearback = createObject("image/clear.png", g5_scene, 270, 300, false, 1.5f);
	g5_deathback = createObject("image/gameover.png", g5_scene, 270, 300, false, 1.5f);
	g5_restartbutton = createObject("image/restart.png", g5_scene, 700, 200, false, 1.3f);
	g5_nextbutton = createObject("image/next.png", g5_scene, 700, 200, false, 1.3f);
	g5_gomapbutton = createObject("image/gomap.png", g5_scene, 300, 200, false, 1.3f);

	g5_boxsound = createSound("sound/game1/g1_boxdeletesound.mp3");

	g5_move_t = createTimer(0.01f);
	startTimer(g5_move_t);

	g5_moveskeleton_t = createTimer(0.01f);
	startTimer(g5_moveskeleton_t);

	g5_update_t = createTimer(0.01f);
	startTimer(g5_update_t);

	g5_effectmove_t = createTimer(0.01f);

	g5_skeletoneimage_t = createTimer(0.01f);
	startTimer(g5_skeletoneimage_t);


}