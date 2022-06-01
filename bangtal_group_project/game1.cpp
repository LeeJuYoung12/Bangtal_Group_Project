#define _CRT_SECURE_NO_WARNINGS
#define g1_ch_x 95*0.7
#define g1_ch_y 100*0.7
#define g1_effect_x 342*0.3 
#define g1_effect_y 261*0.3
#include <stdio.h>
#include <bangtal.h>
extern SoundID introbgm;
extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);
extern int nowgamenum;
extern SceneID mapscene;
extern bool g1_cleared;

int g1_tree_x[26] = { 0, 50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250 };
int g1_tree_y[15] = { 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700 };
int g1_skeleton1_x[15] = { 0, 400,825,400, 300, 750, 520, 620, 720, 820, 920, 995, 995, 1225 ,1225 };
int g1_skeleton1_y[15] = { 225, 425,350,275, 525, 250, 0, 150, 0, 150, 0, 260, 440,350 ,530 };
int g1_skeleton1_xb[15] = { 0, 400,825,400, 300, 750, 520, 620, 720, 820, 920, 995, 995, 1225 ,1225 };
int g1_skeleton1_yb[15] = { 225, 425,350,275, 525, 250, 0, 150, 0, 150, 0, 260, 440,350 ,530 };

int g1_skeleton2_x[11] = { 250,350,350,950,950,1000,1230,1000,520,520,0 };
int g1_skeleton2_y[11] = { 0,20 ,170,20,170,250,340,430,530,590,450 };
int g1_skeleton2_xb[11] = { 250,350,350,950,950,1000,1230,1000,520,520,0 };
int g1_skeleton2_yb[11] = { 0,20 ,170,20,170,250,340,430,530,590,450 };
int g1_box_xs2[8] = { 500,550,600,650,500,550,600,650 };
int g1_box_ys2[8] = { 280, 280, 280, 280, 450, 450, 450, 450 };
int g1_box_xs2b[8] = { 500,550,600,650,500,550,600,650 };
int g1_box_ys2b[8] = { 280, 280, 280, 280, 450, 450, 450, 450 };


int g1_speed = 8, g1dx = 0, g1dy = 0, g1cx = 0, g1cy = 0, g1_skeleton_speed = 3, g1_chway = 3, g1_attackeffectx, g1_attackeffecty, g1_effectspeed = 4;
long long g1_attacknum = 2;

int g1_clearcheck = 0;
int g1_stageclear_check = 0;
int g1_currentsence = 1;  // 스테이지 설정 변수

int g1_skeletonway1[15][4] = { 0, };
int g1_skeletonway2[11][4] = { 0, };

int g1_skeletonway1b[15][4] = { 0, };
int g1_skeletonway2b[11][4] = { 0, };


int g1_timecheck = 0;

bool g1_attacking = false;

SceneID g1_scene;
ObjectID g1_tree1[24], g1_tree2[50], g1ch, g1_skeleton1[15][8], g1_skeleton2[11][8], g1_clear_zone, g1_attackeffect[4], g1_boxs2[8], g1_gomapbutton, g1_restartbutton, g1_nextbutton, g1_deathback, g1_clearback;
TimerID g1_move_t, g1_moveskeleton_t, g1_update_t, g1_effectmove_t, g1_skeletoneimage_t, g1_clearcheck_t;
SoundID g1_boxsound, g1_mapbgm;

ObjectID g1_thorns1[92], g1_thorns2[70];

void g1_exam(int x, int y);
void g1_death_s1(); void g1_death_s2();
void g1_install_s1(); void g1_install_s2();

void g1_install_s1() {
	int i, k;

	for (int i = 0; i < 15; i++)
	{
		g1_skeleton1_x[i] = g1_skeleton1_xb[i];
		g1_skeleton1_y[i] = g1_skeleton1_yb[i];
		for (int j = 0; j < 4; j++)
		{
			g1_skeletonway1[i][j] = g1_skeletonway1b[i][j];
		}
	}

	g1_clear_zone = createObject("image/game1/g1_clearzone.png", g1_scene, 1180, 620, true, 1.f);
	//나무
	for (i = 0, k = 0; i < 6; i++, k++)
	{
		g1_tree1[i] = createObject("image/game1/g1_tree1.png", g1_scene, g1_tree_x[5], g1_tree_y[k * 2] - 10 * k, true, 1.f);
		g1_tree1[i + 6] = createObject("image/game1/g1_tree1.png", g1_scene, g1_tree_x[6] + 20, g1_tree_y[k * 2] - 10 * k, true, 1.f);
	}
	for (i = 12, k = 0; i < 18; i++, k++)
	{
		g1_tree1[i] = createObject("image/game1/g1_tree1.png", g1_scene, g1_tree_x[17], g1_tree_y[k * 2 + 4] - 10 * k, true, 1.f);
	}
	for (i = 18, k = 0; i < 24; i++, k++)
	{
		g1_tree1[i] = createObject("image/game1/g1_tree1.png", g1_scene, g1_tree_x[18] + 20, g1_tree_y[k * 2 + 4] - 10 * k, true, 1.f);
	}


	//가시
	g1_thorns1[0] = createObject("image/game1/g1_thorn.png", g1_scene, 0, 200, true, 1);
	g1_thorns1[1] = createObject("image/game1/g1_thorn.png", g1_scene, 25, 200, true, 1);
	g1_thorns1[2] = createObject("image/game1/g1_thorn.png", g1_scene, 150, 200, true, 1);
	g1_thorns1[3] = createObject("image/game1/g1_thorn.png", g1_scene, 175, 200, true, 1);
	g1_thorns1[4] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 200, true, 1);
	g1_thorns1[5] = createObject("image/game1/g1_thorn.png", g1_scene, 225, 200, true, 1);

	g1_thorns1[6] = createObject("image/game1/g1_thorn.png", g1_scene, 75, 325, true, 1);
	g1_thorns1[7] = createObject("image/game1/g1_thorn.png", g1_scene, 100, 325, true, 1);
	g1_thorns1[8] = createObject("image/game1/g1_thorn.png", g1_scene, 125, 325, true, 1);
	g1_thorns1[9] = createObject("image/game1/g1_thorn.png", g1_scene, 150, 325, true, 1);
	g1_thorns1[10] = createObject("image/game1/g1_thorn.png", g1_scene, 75, 350, true, 1);
	g1_thorns1[11] = createObject("image/game1/g1_thorn.png", g1_scene, 100, 350, true, 1);
	g1_thorns1[12] = createObject("image/game1/g1_thorn.png", g1_scene, 125, 350, true, 1);
	g1_thorns1[13] = createObject("image/game1/g1_thorn.png", g1_scene, 150, 350, true, 1);

	g1_thorns1[14] = createObject("image/game1/g1_thorn.png", g1_scene, 75, 375, true, 1);
	g1_thorns1[15] = createObject("image/game1/g1_thorn.png", g1_scene, 100, 375, true, 1);
	g1_thorns1[16] = createObject("image/game1/g1_thorn.png", g1_scene, 75, 400, true, 1);
	g1_thorns1[17] = createObject("image/game1/g1_thorn.png", g1_scene, 100, 400, true, 1);
	g1_thorns1[18] = createObject("image/game1/g1_thorn.png", g1_scene, 75, 425, true, 1);
	g1_thorns1[19] = createObject("image/game1/g1_thorn.png", g1_scene, 100, 425, true, 1);
	g1_thorns1[20] = createObject("image/game1/g1_thorn.png", g1_scene, 75, 450, true, 1);
	g1_thorns1[21] = createObject("image/game1/g1_thorn.png", g1_scene, 100, 450, true, 1);

	g1_thorns1[22] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 460, true, 1);
	g1_thorns1[23] = createObject("image/game1/g1_thorn.png", g1_scene, 225, 460, true, 1);
	g1_thorns1[24] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 485, true, 1);
	g1_thorns1[25] = createObject("image/game1/g1_thorn.png", g1_scene, 225, 485, true, 1);
	g1_thorns1[26] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 510, true, 1);
	g1_thorns1[27] = createObject("image/game1/g1_thorn.png", g1_scene, 225, 510, true, 1);
	for (i = 0; i < 14; i++)
	{
		g1_thorns1[28 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 400 + i * 25, 475, true, 1);
		g1_thorns1[42 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 400 + i * 25, 500, true, 1);
	}

	for (i = 0; i < 14; i++)
	{
		g1_thorns1[56 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 525 + i * 25, 200, true, 1);
		g1_thorns1[70 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 525 + i * 25, 225, true, 1);
	}

	g1_thorns1[84] = createObject("image/game1/g1_thorn.png", g1_scene, 995, 200, true, 1);
	g1_thorns1[85] = createObject("image/game1/g1_thorn.png", g1_scene, 995, 225, true, 1);
	g1_thorns1[86] = createObject("image/game1/g1_thorn.png", g1_scene, 1020, 200, true, 1);
	g1_thorns1[87] = createObject("image/game1/g1_thorn.png", g1_scene, 1020, 225, true, 1);
	g1_thorns1[88] = createObject("image/game1/g1_thorn.png", g1_scene, 1225, 200, true, 1);
	g1_thorns1[89] = createObject("image/game1/g1_thorn.png", g1_scene, 1225, 225, true, 1);
	g1_thorns1[90] = createObject("image/game1/g1_thorn.png", g1_scene, 1250, 200, true, 1);
	g1_thorns1[91] = createObject("image/game1/g1_thorn.png", g1_scene, 1250, 225, true, 1);

	for (int i = 0; i < 15; i++) {
		g1_skeleton1[i][0] = createObject("image/game1/g1_skeleton1.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][1] = createObject("image/game1/g1_skeleton2.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][2] = createObject("image/game1/g1_skeleton3.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][3] = createObject("image/game1/g1_skeleton4.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][4] = createObject("image/game1/g1_skeleton5.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][5] = createObject("image/game1/g1_skeleton6.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][6] = createObject("image/game1/g1_skeleton7.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
		g1_skeleton1[i][7] = createObject("image/game1/g1_skeleton8.png", g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i], false, 0.25f);
	}
}

void g1_install_s2()
{
	int i, k;

	for (int i = 0; i < 11; i++)
	{
		g1_skeleton2_x[i] = g1_skeleton2_xb[i];
		g1_skeleton2_y[i] = g1_skeleton2_yb[i];
		for (int j = 0; j < 4; j++)
		{
			g1_skeletonway2[i][j] = g1_skeletonway2b[i][j];
		}
	}

	g1_clear_zone = createObject("image/game1/g1_clearzone.png", g1_scene, 0, 620, true, 1.f);

	for (i = 0; i < 7; i++)
	{
		g1_tree2[i] = createObject("image/game1/g1_tree1.png", g1_scene, -20 + i * 70, 250, true, 1.f);
		g1_tree2[i + 7] = createObject("image/game1/g1_tree1.png", g1_scene, -20 + i * 70, 340, true, 1.f);
	}
	g1_tree2[14] = createObject("image/game1/g1_tree1.png", g1_scene, 330, 430, true, 1.f);
	g1_tree2[15] = createObject("image/game1/g1_tree1.png", g1_scene, 400, 430, true, 1.f);

	for (i = 0; i < 4; i++)
	{
		g1_boxs2[i] = createObject("image/game1/g1_box.png", g1_scene, g1_box_xs2[i], g1_box_ys2[i], true, 1.f);
		g1_boxs2[i + 4] = createObject("image/game1/g1_box.png", g1_scene, g1_box_xs2[i + 4], g1_box_ys2[i + 4], true, 1.f);
	}

	for (i = 0; i < 4; i++)
	{
		g1_tree2[i + 16] = createObject("image/game1/g1_tree1.png", g1_scene, 700 + i * 70, 250, true, 1.f);
		g1_tree2[i + 20] = createObject("image/game1/g1_tree1.png", g1_scene, 700 + i * 70, 340, true, 1.f);
		g1_tree2[i + 24] = createObject("image/game1/g1_tree1.png", g1_scene, 700 + i * 70, 430, true, 1.f);
	}

	g1_thorns2[0] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 175, true, 1);
	g1_thorns2[1] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 200, true, 1);
	g1_thorns2[2] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 225, true, 1);
	g1_thorns2[3] = createObject("image/game1/g1_thorn.png", g1_scene, 300, 0, true, 1);
	g1_thorns2[4] = createObject("image/game1/g1_thorn.png", g1_scene, 300, 25, true, 1);
	g1_thorns2[5] = createObject("image/game1/g1_thorn.png", g1_scene, 300, 50, true, 1);

	for (i = 0; i < 4; i++)
	{
		g1_thorns2[6 + i * 4] = createObject("image/game1/g1_thorn.png", g1_scene, 425 + i * 150, 100, true, 1);
		g1_thorns2[7 + i * 4] = createObject("image/game1/g1_thorn.png", g1_scene, 425 + i * 150, 125, true, 1);
		g1_thorns2[8 + i * 4] = createObject("image/game1/g1_thorn.png", g1_scene, 450 + i * 150, 100, true, 1);
		g1_thorns2[9 + i * 4] = createObject("image/game1/g1_thorn.png", g1_scene, 450 + i * 150, 125, true, 1);
	}

	for (i = 0; i < 7; i++)
	{
		g1_thorns2[26 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 515 + i * 25, 695, true, 1);
		g1_thorns2[33 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 515 + i * 25, 670, true, 1);
		g1_thorns2[40 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 800 + i * 25, 695, true, 1);
		g1_thorns2[47 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 800 + i * 25, 670, true, 1);
	}
	for (i = 0; i < 8; i++)
	{
		g1_thorns2[54 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 200, 695 - i * 25, true, 1);
		g1_thorns2[62 + i] = createObject("image/game1/g1_thorn.png", g1_scene, 225, 695 - i * 25, true, 1);
	}


	for (int i = 0; i < 11; i++) {
		g1_skeleton2[i][0] = createObject("image/game1/g1_skeleton1.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][1] = createObject("image/game1/g1_skeleton2.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][2] = createObject("image/game1/g1_skeleton3.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][3] = createObject("image/game1/g1_skeleton4.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][4] = createObject("image/game1/g1_skeleton5.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][5] = createObject("image/game1/g1_skeleton6.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][6] = createObject("image/game1/g1_skeleton7.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
		g1_skeleton2[i][7] = createObject("image/game1/g1_skeleton8.png", g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i], false, 0.25f);
	}
}


void g1_blocks1() {
	if (g1cx < 0 || g1cx + g1_ch_x>1280 || g1cy < 0 || g1cy + g1_ch_y>720) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if ((g1cx + g1_ch_x < 460 && g1cx + g1_ch_x>270) && g1cy + g1_ch_y < 600) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if ((g1cx + g1_ch_x < 1060 && g1cx + g1_ch_x>870) && g1cy + g1_ch_y > 210) {
		g1cx -= g1dx; g1cy -= g1dy;
	}

}

void g1_blocks2()
{
	if (g1cx < 0 || g1cx + g1_ch_x>1280 || g1cy < 0 || g1cy + g1_ch_y>720) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if ((g1cx + g1_ch_x < 540) && (g1cy + g1_ch_y < 500 && g1cy + g1_ch_y > 260)) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	if ((g1cx + g1_ch_x < 540 && g1cx + g1_ch_x > 360) && (g1cy + g1_ch_y < 590 && g1cy + g1_ch_y > 260)) {
		g1cx -= g1dx; g1cy -= g1dy;
	}

	if ((g1cx + g1_ch_x < 1050 && g1cx + g1_ch_x > 730) && (g1cy + g1_ch_y < 590 && g1cy + g1_ch_y > 260)) {
		g1cx -= g1dx; g1cy -= g1dy;
	}
	for (int i = 0; i < 8; i++) {
		if ((g1cx < (g1_box_xs2[i] + 50)) && (g1cx + g1_ch_x > g1_box_xs2[i]) && (g1cy < (g1_box_ys2[i] + 50)) && (g1cy + g1_ch_y > g1_box_ys2[i])) {
			g1cx -= g1dx; g1cy -= g1dy;
		}
	}
}


void g1_skeletonmoves1() {
	int i;
	//방향 정하기
	if (g1_skeleton1_y[0] >= 650)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[0][i] = 0;
		}
		g1_skeletonway1[0][1] = 1;
	}
	else if (g1_skeleton1_y[0] <= 230)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[0][i] = 0;
		}
		g1_skeletonway1[0][0] = 1;
	}

	if (g1_skeleton1_x[1] >= 820)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[1][i] = 0;
			g1_skeletonway1[3][i] = 0;
		}
		g1_skeletonway1[1][2] = 1;
		g1_skeletonway1[3][2] = 1;
	}
	else if (g1_skeleton1_x[1] <= 400)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[1][i] = 0;
			g1_skeletonway1[3][i] = 0;
		}
		g1_skeletonway1[1][3] = 1;
		g1_skeletonway1[3][3] = 1;
	}

	if (g1_skeleton1_x[2] >= 820)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[2][i] = 0;
		}
		g1_skeletonway1[2][2] = 1;
	}
	else if (g1_skeleton1_x[2] <= 400)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[2][i] = 0;
		}
		g1_skeletonway1[2][3] = 1;
	}

	if (g1_skeleton1_y[4] >= 660)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[4][i] = 0;
		}
		g1_skeletonway1[4][1] = 1;
	}
	else if (g1_skeleton1_y[4] <= 540)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[4][i] = 0;
		}
		g1_skeletonway1[4][0] = 1;
	}

	if (g1_skeleton1_y[5] >= 670)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[5][i] = 0;
		}
		g1_skeletonway1[5][1] = 1;
	}
	else if (g1_skeleton1_y[5] <= 250)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[5][i] = 0;
		}
		g1_skeletonway1[5][0] = 1;
	}
	if (g1_skeleton1_y[6] >= 150)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[6][i] = 0;
			g1_skeletonway1[8][i] = 0;
			g1_skeletonway1[10][i] = 0;
		}
		g1_skeletonway1[6][1] = 1;
		g1_skeletonway1[8][1] = 1;
		g1_skeletonway1[10][1] = 1;
	}
	else if (g1_skeleton1_y[6] <= 0)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[6][i] = 0;
			g1_skeletonway1[8][i] = 0;
			g1_skeletonway1[10][i] = 0;
		}
		g1_skeletonway1[6][0] = 1;
		g1_skeletonway1[8][0] = 1;
		g1_skeletonway1[10][0] = 1;
	}
	if (g1_skeleton1_y[7] >= 150)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[7][i] = 0;
			g1_skeletonway1[9][i] = 0;
		}
		g1_skeletonway1[7][1] = 1;
		g1_skeletonway1[9][1] = 1;
	}
	else if (g1_skeleton1_y[7] <= 0)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[7][i] = 0;
			g1_skeletonway1[9][i] = 0;
		}
		g1_skeletonway1[7][0] = 1;
		g1_skeletonway1[9][0] = 1;
	}

	if (g1_skeleton1_x[11] >= 1220)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[11][i] = 0;
			g1_skeletonway1[12][i] = 0;
		}
		g1_skeletonway1[11][2] = 1;
		g1_skeletonway1[12][2] = 1;
	}
	else if (g1_skeleton1_x[11] <= 1000)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[11][i] = 0;
			g1_skeletonway1[12][i] = 0;
		}
		g1_skeletonway1[11][3] = 1;
		g1_skeletonway1[12][3] = 1;
	}

	if (g1_skeleton1_x[13] >= 1220)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[13][i] = 0;
			g1_skeletonway1[14][i] = 0;
		}
		g1_skeletonway1[13][2] = 1;
		g1_skeletonway1[14][2] = 1;
	}
	else if (g1_skeleton1_x[13] <= 1000)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway1[13][i] = 0;
			g1_skeletonway1[14][i] = 0;
		}
		g1_skeletonway1[13][3] = 1;
		g1_skeletonway1[14][3] = 1;
	}

	//좌표 바꾸기
	if (g1_skeletonway1[0][0] == 1)
	{
		g1_skeleton1_y[0] += g1_skeleton_speed;
	}
	else if (g1_skeletonway1[0][1] == 1)
	{
		g1_skeleton1_y[0] -= g1_skeleton_speed;
	}

	if (g1_skeletonway1[1][2] == 1)
	{
		g1_skeleton1_x[1] -= g1_skeleton_speed;
		g1_skeleton1_x[3] -= g1_skeleton_speed;
	}
	else if (g1_skeletonway1[1][3] == 1)
	{
		g1_skeleton1_x[1] += g1_skeleton_speed;
		g1_skeleton1_x[3] += g1_skeleton_speed;
	}

	if (g1_skeletonway1[2][2] == 1)
	{
		g1_skeleton1_x[2] -= g1_skeleton_speed;
	}
	else if (g1_skeletonway1[2][3] == 1)
	{
		g1_skeleton1_x[2] += g1_skeleton_speed;
	}

	if (g1_skeletonway1[4][0] == 1)
	{
		g1_skeleton1_y[4] += g1_skeleton_speed;
	}
	else if (g1_skeletonway1[4][1] == 1)
	{
		g1_skeleton1_y[4] -= g1_skeleton_speed;
	}

	if (g1_skeletonway1[5][0] == 1)
	{
		g1_skeleton1_y[5] += g1_skeleton_speed;
	}
	else if (g1_skeletonway1[5][1] == 1)
	{
		g1_skeleton1_y[5] -= g1_skeleton_speed;
	}

	if (g1_skeletonway1[6][0] == 1)
	{
		g1_skeleton1_y[6] += g1_skeleton_speed;
		g1_skeleton1_y[8] += g1_skeleton_speed;
		g1_skeleton1_y[10] += g1_skeleton_speed;
	}
	else if (g1_skeletonway1[6][1] == 1)
	{
		g1_skeleton1_y[6] -= g1_skeleton_speed;
		g1_skeleton1_y[8] -= g1_skeleton_speed;
		g1_skeleton1_y[10] -= g1_skeleton_speed;
	}

	if (g1_skeletonway1[7][0] == 1)
	{
		g1_skeleton1_y[7] += g1_skeleton_speed;
		g1_skeleton1_y[9] += g1_skeleton_speed;
	}
	else if (g1_skeletonway1[7][1] == 1)
	{
		g1_skeleton1_y[7] -= g1_skeleton_speed;
		g1_skeleton1_y[9] -= g1_skeleton_speed;
	}

	if (g1_skeletonway1[11][2] == 1)
	{
		g1_skeleton1_x[11] -= g1_skeleton_speed;
		g1_skeleton1_x[12] -= g1_skeleton_speed;
	}
	else if (g1_skeletonway1[11][3] == 1)
	{
		g1_skeleton1_x[11] += g1_skeleton_speed;
		g1_skeleton1_x[12] += g1_skeleton_speed;
	}
	if (g1_skeletonway1[13][2] == 1)
	{
		g1_skeleton1_x[13] -= g1_skeleton_speed;
		g1_skeleton1_x[14] -= g1_skeleton_speed;
	}
	else if (g1_skeletonway1[13][3] == 1)
	{
		g1_skeleton1_x[13] += g1_skeleton_speed;
		g1_skeleton1_x[14] += g1_skeleton_speed;
	}

	//이동하기
	for (i = 0; i < 15; i++) {
		for (int j = 0; j < 8; j++)
		{
			locateObject(g1_skeleton1[i][j], g1_scene, g1_skeleton1_x[i], g1_skeleton1_y[i]);
		}
	}
}

void g1_skeletonmoves2()
{
	int i;
	//방향
	if (g1_skeleton2_y[0] >= 200)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[0][i] = 0;
		}
		g1_skeletonway2[0][1] = 1;
	}
	else if (g1_skeleton2_y[0] <= 0)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[0][i] = 0;
		}
		g1_skeletonway2[0][0] = 1;
	}
	if (g1_skeleton2_x[1] >= 950)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[1][i] = 0;
			g1_skeletonway2[2][i] = 0;
			g1_skeletonway2[3][i] = 0;
			g1_skeletonway2[4][i] = 0;
		}
		g1_skeletonway2[1][2] = 1;
		g1_skeletonway2[2][2] = 1;
		g1_skeletonway2[3][3] = 1;
		g1_skeletonway2[4][3] = 1;
	}
	else if (g1_skeleton2_x[1] <= 350)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[1][i] = 0;
			g1_skeletonway2[2][i] = 0;
			g1_skeletonway2[3][i] = 0;
			g1_skeletonway2[4][i] = 0;
		}
		g1_skeletonway2[1][3] = 1;
		g1_skeletonway2[2][3] = 1;
		g1_skeletonway2[3][2] = 1;
		g1_skeletonway2[4][2] = 1;
	}
	if (g1_skeleton2_x[5] >= 1230)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[5][i] = 0;
			g1_skeletonway2[6][i] = 0;
			g1_skeletonway2[7][i] = 0;
		}
		g1_skeletonway2[5][2] = 1;
		g1_skeletonway2[6][3] = 1;
		g1_skeletonway2[7][2] = 1;
	}
	else if (g1_skeleton2_x[5] <= 1000)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[5][i] = 0;
			g1_skeletonway2[6][i] = 0;
			g1_skeletonway2[7][i] = 0;
		}
		g1_skeletonway2[5][3] = 1;
		g1_skeletonway2[6][2] = 1;
		g1_skeletonway2[7][3] = 1;
	}
	if (g1_skeleton2_x[8] >= 900)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[8][i] = 0;
			g1_skeletonway2[9][i] = 0;
		}
		g1_skeletonway2[8][2] = 1;
		g1_skeletonway2[9][2] = 1;
	}
	else if (g1_skeleton2_x[8] <= 520)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[8][i] = 0;
			g1_skeletonway2[9][i] = 0;
		}
		g1_skeletonway2[8][3] = 1;
		g1_skeletonway2[9][3] = 1;
	}
	if (g1_skeleton2_x[10] >= 270)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[10][i] = 0;
		}
		g1_skeletonway2[10][2] = 1;
	}
	else if (g1_skeleton2_x[10] <= 0)
	{
		for (i = 0; i < 4; i++)
		{
			g1_skeletonway2[10][i] = 0;
		}
		g1_skeletonway2[10][3] = 1;
	}

	//좌표변경
	for (i = 0; i < 11; i++)
	{
		if (g1_skeletonway2[i][0] == 1)
		{
			g1_skeleton2_y[i] += g1_skeleton_speed;
		}
		else if (g1_skeletonway2[i][1] == 1)
		{
			g1_skeleton2_y[i] -= g1_skeleton_speed;
		}
		else if (g1_skeletonway2[i][2] == 1)
		{
			g1_skeleton2_x[i] -= g1_skeleton_speed;
		}
		else if (g1_skeletonway2[i][3] == 1)
		{
			g1_skeleton2_x[i] += g1_skeleton_speed;
		}
	}

	//이동시키기
	for (i = 0; i < 11; i++) {
		for (int j = 0; j < 8; j++)
		{
			locateObject(g1_skeleton2[i][j], g1_scene, g1_skeleton2_x[i], g1_skeleton2_y[i]);
		}
	}

}

void g1_attack() {

	if (g1_chway == 0) {
		g1_attackeffectx = g1cx + 5;
		g1_attackeffecty = g1cy - 5;
		locateObject(g1_attackeffect[0], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[0]);
		startTimer(g1_effectmove_t);
	}
	if (g1_chway == 1) {
		g1_attackeffectx = g1cx - 50;
		g1_attackeffecty = g1cy - 5;
		locateObject(g1_attackeffect[1], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[1]);
		startTimer(g1_effectmove_t);
	}
	if (g1_chway == 2) {
		g1_attackeffectx = g1cx - 10;
		g1_attackeffecty = g1cy - 50;
		locateObject(g1_attackeffect[2], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[2]);
		startTimer(g1_effectmove_t);
	}
	if (g1_chway == 3) {
		g1_attackeffectx = g1cx - 10;
		g1_attackeffecty = g1cy + 50;
		locateObject(g1_attackeffect[3], g1_scene, g1_attackeffectx, g1_attackeffecty);
		showObject(g1_attackeffect[3]);
		startTimer(g1_effectmove_t);
	}
}


void g1_boxdelete2() {

	for (int i = 0; i < 8; i++) {
			if (((g1_attackeffectx+50)  < (g1_box_xs2[i] + 50)) && ((g1_attackeffectx+50 + 342 * 0.3-50) > g1_box_xs2[i]) && ((g1_attackeffecty+50 ) < (g1_box_ys2[i]+50)) && ((g1_attackeffecty+50+261*0.3-50) > (g1_box_ys2[i]))) {
				g1_box_xs2[i] = 1300, g1_box_ys2[i] = 800;
				playSound(g1_boxsound);
				locateObject(g1_boxs2[i], g1_scene, g1_box_xs2[i], g1_box_ys2[i]);
			}
	}

}


void g1_clear() {
	if (g1_currentsence == 1 && (g1cx >= 1130 && g1cy >= 570)) {
		showObject(g1_clearback);
		showObject(g1_gomapbutton);
		showObject(g1_nextbutton);

		stopTimer(g1_move_t);
		stopTimer(g1_moveskeleton_t);
		stopTimer(g1_update_t);
		stopTimer(g1_effectmove_t);
		stopTimer(g1_skeletoneimage_t);
		for (int i = 0; i < 92; i++)
		{
			hideObject(g1_thorns1[i]);
		}
		for (int i = 0; i < 24; i++)
		{
			hideObject(g1_tree1[i]);
		}
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				hideObject(g1_skeleton1[i][j]);
			}
		}
		g1_stageclear_check = 1;
	}
	if (g1_currentsence >= 2 && (g1cx <= 100 && g1cy >= 570)) {
		locateObject(g1_gomapbutton, g1_scene, 500, 200);
		showObject(g1_clearback);
		showObject(g1_gomapbutton);

		stopTimer(g1_move_t);
		stopTimer(g1_moveskeleton_t);
		stopTimer(g1_update_t);
		stopTimer(g1_effectmove_t);
		stopTimer(g1_skeletoneimage_t);
		for (int i = 0; i < 70; i++)
		{
			hideObject(g1_thorns2[i]);
		}
		for (int i = 0; i < 50; i++)
		{
			hideObject(g1_tree2[i]);
		}
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				hideObject(g1_skeleton2[i][j]);
			}
		}
		g1_stageclear_check = 1;
		g1_cleared=true;
		g1_clearcheck = 1;
		g1_cleared = true;
	}

}

void g1_death_s1() {
	int i, j;
	for (i = 0; i < 15; i++) {
		g1_exam(g1_skeleton1_x[i] + 10, g1_skeleton1_y[i] + 6);
		g1_exam(g1_skeleton1_x[i] + 40, g1_skeleton1_y[i] + 6);
		g1_exam(g1_skeleton1_x[i] + 10, g1_skeleton1_y[i] + 50);
		g1_exam(g1_skeleton1_x[i] + 40, g1_skeleton1_y[i] + 50);
	}
	if (g1cx <= 260)
	{
		for (i = 0; i < 3; i++)
		{
			g1_exam(i * 25, 200);
			g1_exam(i * 25, 225);
		}
		for (i = 0; i < 5; i++)
		{
			g1_exam(i * 25 + 150, 200);
			g1_exam(i * 25 + 150, 225);
		}
		for (i = 0; i < 4; i++)
		{
			g1_exam(75, 325 + 50 * i);
			g1_exam(125, 325 + 50 * i);
		}
		g1_exam(175, 325);
		g1_exam(175, 375);
		for (i = 0; i < 4; i++)
		{
			g1_exam(200, 460 + i * 25);
			g1_exam(225, 460 + i * 25);
		}
	}
	if (g1cx >= 255 && g1cx <= 900)
	{
		for (i = 0; i < 8; i++)
		{
			g1_exam(400 + i * 50, 475);
			g1_exam(400 + i * 50, 525);
			g1_exam(525 + i * 50, 200);
			g1_exam(525 + i * 50, 250);
		}
	}
	if (g1cx >= 910)
	{
		for (i = 0; i < 2; i++)
		{
			g1_exam(995 + i * 50, 200);
			g1_exam(995 + i * 50, 250);
			g1_exam(1225 + i * 50, 200);
			g1_exam(1225 + i * 50, 250);
		}
	}
}

void g1_death_s2()
{
	int i, j;
	for (i = 0; i < 11; i++) {
		g1_exam(g1_skeleton2_x[i] + 10, g1_skeleton2_y[i] + 6);
		g1_exam(g1_skeleton2_x[i] + 40, g1_skeleton2_y[i] + 6);
		g1_exam(g1_skeleton2_x[i] + 10, g1_skeleton2_y[i] + 50);
		g1_exam(g1_skeleton2_x[i] + 40, g1_skeleton2_y[i] + 50);
	}
	for (i = 0; i < 3; i++)
	{
		g1_exam(200, 175 + i * 25);
		g1_exam(225, 175 + i * 25);
		g1_exam(300, i * 25 + 15);
		g1_exam(325, i * 25 + 15);
	}
	for (i = 0; i < 4; i++)
	{
		g1_exam(425 + 150 * i, 100);
		g1_exam(425 + 150 * i, 150);
		g1_exam(470 + 150 * i, 100);
		g1_exam(470 + 150 * i, 150);
	}
	for (i = 0; i < 5; i++)
	{
		g1_exam(200, 520 + i * 50);
		g1_exam(250, 520 + i * 50);
	}
	for (i = 0; i < 8; i++)
	{
		g1_exam(515 + i * 25, 670);
		g1_exam(515 + i * 25, 695);
		g1_exam(800 + i * 25, 670);
		g1_exam(800 + i * 25, 695);
	}
}


void g1_exam(int x, int y)
{
	if ((g1cx + 9 <= x && g1cx + 45 >= x) && (g1cy + 5 <= y && g1cy + 45 >= y))
	{
		showObject(g1_deathback);
		showObject(g1_gomapbutton);
		showObject(g1_restartbutton);

		stopTimer(g1_move_t);
		stopTimer(g1_moveskeleton_t);
		stopTimer(g1_update_t);
		stopTimer(g1_effectmove_t);
		stopTimer(g1_skeletoneimage_t);
	}
}

void g1_restart() {
	hideObject(g1_restartbutton);
	hideObject(g1_gomapbutton);
	hideObject(g1_nextbutton);
	hideObject(g1_clearback);
	hideObject(g1_deathback);

	g1cx = 0, g1cy = 0, g1_attacknum = 1;
	g1_attacking = false;
	g1_chway = 3, g1dx = 0, g1dy = 0;
	g1_attackeffectx = 1500, g1_attackeffecty = 800;

	if (g1_currentsence >= 2)
	{
		for (int i = 0; i < 8; i++)
		{
			g1_box_xs2[i] = g1_box_xs2b[i];
			g1_box_ys2[i] = g1_box_ys2b[i];
			locateObject(g1_boxs2[i], g1_scene, g1_box_xs2[i], g1_box_ys2[i]);
		}
	}


	//위치
	locateObject(g1ch, g1_scene, g1cx, g1cy);

	locateObject(g1_attackeffect[0], g1_scene, 1500, 800);
	locateObject(g1_attackeffect[1], g1_scene, 1500, 800);
	locateObject(g1_attackeffect[2], g1_scene, 1500, 800);
	locateObject(g1_attackeffect[3], g1_scene, 1500, 800);

	setTimer(g1_move_t, 0.015f);
	setTimer(g1_moveskeleton_t, 0.02f);
	setTimer(g1_update_t, 0.01f);
	setTimer(g1_effectmove_t, 0.01f);

	startTimer(g1_move_t);
	startTimer(g1_moveskeleton_t);
	startTimer(g1_update_t);
	startTimer(g1_skeletoneimage_t);
}

// 마우스콜백함수
void game1_mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == g1_gomapbutton) {

		if (g1_currentsence == 1)
		{
			if (g1_stageclear_check == 1)
			{
				g1_currentsence = 2;
				g1_stageclear_check = 0;
			}
			for (int i = 0; i < 92; i++)
			{
				hideObject(g1_thorns1[i]);
			}
			for (int i = 0; i < 24; i++)
			{
				hideObject(g1_tree1[i]);
			}
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					hideObject(g1_skeleton1[i][j]);
				}
			}
			hideObject(g1_clear_zone);
			if (g1_currentsence == 1)
			{
				g1_install_s1();
			}
			else if (g1_currentsence >= 2)
			{
				g1_install_s2();
			}

		}
		else if (g1_currentsence >= 2)
		{
	
			for (int i = 0; i < 70; i++)
			{
				hideObject(g1_thorns2[i]);
			}
			for (int i = 0; i < 28; i++)
			{
				hideObject(g1_tree2[i]);
			}
			for (int i = 0; i < 11; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					hideObject(g1_skeleton2[i][j]);
				}
			}
			for (int i = 0; i < 8; i++)
			{
				hideObject(g1_boxs2[i]);
			}
			hideObject(g1_clear_zone);
			if (g1_currentsence >= 2)
			{
				g1_install_s2();
			}

		}
	
		
		g1_restart();
		g1_clearback = createObject("image/clear.png", g1_scene, 270, 300, false, 1.5f);
		g1_deathback = createObject("image/gameover.png", g1_scene, 270, 300, false, 1.5f);
		g1_restartbutton = createObject("image/restart.png", g1_scene, 700, 200, false, 1.3f);
		g1_nextbutton = createObject("image/next.png", g1_scene, 700, 200, false, 1.3f);
		g1_gomapbutton = createObject("image/gomap.png", g1_scene, 300, 200, false, 1.3f);

		enterScene(mapscene);
		stopSound(g1_mapbgm);
		playSound(introbgm);
	}
	if (object == g1_restartbutton) {
		g1_restart();
	}
	if (object == g1_nextbutton) {
		g1_currentsence++;
		hideObject(g1_restartbutton);
		hideObject(g1_gomapbutton);
		hideObject(g1_nextbutton);
		hideObject(g1_clearback);
		hideObject(g1_deathback);
		hideObject(g1_clear_zone);

		g1cx = 0, g1cy = 0, g1_attacknum = 1;
		g1_attacking = false;
		g1_chway = 3, g1dx = 0, g1dy = 0;
		g1_attackeffectx = 1500, g1_attackeffecty = 800;

		//위치
		locateObject(g1ch, g1_scene, g1cx, g1cy);

		locateObject(g1_attackeffect[0], g1_scene, 1500, 800);
		locateObject(g1_attackeffect[1], g1_scene, 1500, 800);
		locateObject(g1_attackeffect[2], g1_scene, 1500, 800);
		locateObject(g1_attackeffect[3], g1_scene, 1500, 800);

		setTimer(g1_move_t, 0.015f);
		setTimer(g1_moveskeleton_t, 0.02f);
		setTimer(g1_update_t, 0.01f);
		setTimer(g1_effectmove_t, 0.01f);

		startTimer(g1_move_t);
		startTimer(g1_moveskeleton_t);
		startTimer(g1_update_t);
		startTimer(g1_skeletoneimage_t);

	
		if (g1_currentsence >= 2)
		{

			for (int i = 0; i < 92; i++)
			{
				hideObject(g1_thorns1[i]);
			}
			for (int i = 0; i < 24; i++)
			{
				hideObject(g1_tree1[i]);
			}
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					hideObject(g1_skeleton1[i][j]);
				}
			}
			g1_install_s2();
		}
		
		g1_clearback = createObject("image/clear.png", g1_scene, 270, 300, false, 1.5f);
		g1_deathback = createObject("image/gameover.png", g1_scene, 270, 300, false, 1.5f);
		g1_restartbutton = createObject("image/restart.png", g1_scene, 700, 200, false, 1.3f);
		g1_nextbutton = createObject("image/next.png", g1_scene, 700, 200, false, 1.3f);
		g1_gomapbutton = createObject("image/gomap.png", g1_scene, 300, 200, false, 1.3f);
	}

}

//타이머콜백함수
void game1_timerCallback(TimerID timer) {
	if (timer == g1_move_t) {
		if (nowgamenum == 1)
		{
			g1cx += g1dx; g1cy += g1dy;
			if (g1_currentsence == 1)
			{
				g1_blocks1();
			}
			else if (g1_currentsence >= 2)
			{
				g1_blocks2();
				g1_boxdelete2();
			}

		}
		locateObject(g1ch, g1_scene, g1cx, g1cy);
		setTimer(g1_move_t, 0.02f);
		startTimer(g1_move_t);
	}


	if (timer == g1_moveskeleton_t && g1_currentsence == 1) {
		if (nowgamenum == 1)
		{
			g1_skeletonmoves1();
		}
		setTimer(g1_moveskeleton_t, 0.02f);
		startTimer(g1_moveskeleton_t);
	}
	else if (timer == g1_moveskeleton_t && g1_currentsence >= 2)
	{
		if (nowgamenum == 1)
		{
			g1_skeletonmoves2();
		}
		setTimer(g1_moveskeleton_t, 0.02f);
		startTimer(g1_moveskeleton_t);
	}


	if (timer == g1_skeletoneimage_t && g1_currentsence == 1) {
		if (nowgamenum == 1)
		{
			if (g1_timecheck == 0)
			{
				g1_timecheck = 1;
			}
			else if (g1_timecheck == 1)
			{
				g1_timecheck = 0;
			}
			for (int i = 0; i < 15; i++)
			{
				if (g1_skeletonway1[i][0] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][6]);
				}
				else if (g1_skeletonway1[i][0] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][7]);
				}

				if (g1_skeletonway1[i][1] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][0]);
				}
				else if (g1_skeletonway1[i][1] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][1]);
				}

				if (g1_skeletonway1[i][2] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][2]);
				}
				else if (g1_skeletonway1[i][2] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][3]);
				}

				if (g1_skeletonway1[i][3] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][4]);
				}
				else if (g1_skeletonway1[i][3] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton1[i][j]);
					}
					showObject(g1_skeleton1[i][5]);
				}
			}
		}
		setTimer(g1_skeletoneimage_t, 0.25f);
		startTimer(g1_skeletoneimage_t);
	}
	else if (timer == g1_skeletoneimage_t && g1_currentsence >= 2)
	{
		if (nowgamenum == 1)
		{
			if (g1_timecheck == 0)
			{
				g1_timecheck = 1;
			}
			else if (g1_timecheck == 1)
			{
				g1_timecheck = 0;
			}

			for (int i = 0; i < 11; i++)
			{
				if (g1_skeletonway2[i][0] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][6]);
				}
				else if (g1_skeletonway2[i][0] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][7]);
				}

				if (g1_skeletonway2[i][1] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][0]);
				}
				else if (g1_skeletonway2[i][1] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][1]);
				}

				if (g1_skeletonway2[i][2] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][2]);
				}
				else if (g1_skeletonway2[i][2] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][3]);
				}

				if (g1_skeletonway2[i][3] == 1 && g1_timecheck == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][4]);
				}
				else if (g1_skeletonway2[i][3] == 1 && g1_timecheck == 1)
				{
					for (int j = 0; j < 8; j++)
					{
						hideObject(g1_skeleton2[i][j]);
					}
					showObject(g1_skeleton2[i][5]);
				}
			}
		}
		setTimer(g1_skeletoneimage_t, 0.25f);
		startTimer(g1_skeletoneimage_t);
	}


	if (timer == g1_update_t) {
		if (nowgamenum == 1)
		{
			g1_clear();
			if (g1_currentsence == 1)
			{
				g1_death_s1();
			}
			else if (g1_currentsence == 2)
			{
				g1_death_s2();
			}
	
		}
		setTimer(g1_update_t, 0.01f);
		startTimer(g1_update_t);
	}
	if (timer == g1_effectmove_t) {
		//이동
		if (nowgamenum == 1)
		{
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
		}

		if (g1_attacking == true && nowgamenum == 1) {
			setTimer(g1_effectmove_t, 0.01f);
			startTimer(g1_effectmove_t);
		}
	}
	if (timer = g1_clearcheck_t)
	{
		if (g1_clearcheck == 1 && nowgamenum == 1 && g1_currentsence == 0)
		{
			enterScene(mapscene);
		}
		setTimer(g1_clearcheck_t, 0.1f);
		startTimer(g1_clearcheck_t);
	}
}

//사운드콜백함수
void game1_soundCallback(SoundID sound) {
	if (sound == g1_boxsound)
	{
		playSound(g1_boxsound);
		stopSound(g1_boxsound);
	}
	if (sound == g1_mapbgm) {
		playSound(g1_mapbgm);
	}
}

//키보드콜백함수    (바꿀필요 X)
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
			if (state == KeyState::KEY_PRESSED) {
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

	g1_scene = createScene("game1", "image/game1/g1_background.png");


	g1_skeletonway1b[0][0] = 1;
	g1_skeletonway1b[1][3] = 1;
	g1_skeletonway1b[2][2] = 1;
	g1_skeletonway1b[3][3] = 1;
	g1_skeletonway1b[4][2] = 1;
	g1_skeletonway1b[5][0] = 1;

	g1_skeletonway1b[6][0] = 1;
	g1_skeletonway1b[8][0] = 1;
	g1_skeletonway1b[10][0] = 1;
	g1_skeletonway1b[7][1] = 1;
	g1_skeletonway1b[9][1] = 1;

	g1_skeletonway1b[11][2] = 1;
	g1_skeletonway1b[12][2] = 1;
	g1_skeletonway1b[13][3] = 1;
	g1_skeletonway1b[14][3] = 1;


	g1_skeletonway2b[0][0] = 1;

	g1_skeletonway2b[1][3] = 1;
	g1_skeletonway2b[2][3] = 1;
	g1_skeletonway2b[3][2] = 1;
	g1_skeletonway2b[4][2] = 1;

	g1_skeletonway2b[5][3] = 1;
	g1_skeletonway2b[6][2] = 1;
	g1_skeletonway2b[7][3] = 1;

	g1_skeletonway2b[8][3] = 1;
	g1_skeletonway2b[9][3] = 1;

	g1_skeletonway2b[10][3] = 1;



	if (g1_currentsence == 1)
	{
		g1_install_s1();

	}
	else if (g1_currentsence == 2)
	{
		g1_install_s2();
	}

	g1ch = createObject("image/game1/player1.png", g1_scene, g1cx, g1cy, true, 0.7f);

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

	g1_boxsound = createSound("sound/game1/g1_boxdeletesound.mp3");

	g1_move_t = createTimer(0.01f);
	startTimer(g1_move_t);

	g1_moveskeleton_t = createTimer(0.01f);
	startTimer(g1_moveskeleton_t);

	g1_update_t = createTimer(0.01f);
	startTimer(g1_update_t);

	g1_effectmove_t = createTimer(0.01f);

	g1_skeletoneimage_t = createTimer(0.01f);
	startTimer(g1_skeletoneimage_t);

	g1_clearcheck_t = createTimer(0.1f);
	startTimer(g1_clearcheck_t);

	g1_mapbgm = createSound("sound/game1/g1_mapsound.mp3");
}