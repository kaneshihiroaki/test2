#include "DxLib.h"
#include "Main.h"
#include "PuyoPuyo.h"
#include "image.h"

//構造体宣言
Image g_image;

//アニメーション
int Diamond_Anime[] = { 0,1,2,3,};//ダイヤが光る時のアニメーション
int DiamondDelete_Anime[] = { 4,5,6,7,8,9,10 };
int Diamond_ANI_SPEED = 10;//次のアニメーションまでにかかるフレーム数
int Diamond_act_wait = Diamond_ANI_SPEED;//次のアニメーションまで待つ時間
int Diamond_MOTION_INDEX = 4;//光るモーションの数
int DiamondDelete_MOTION_INDEX = 7;//破壊モーションの数
int Diamond_act_index = 0;//光るモーションの数
int Diamond_act_index2 = 0;//破壊モーションの数
int Diamond_motion_index;//光るモーション番号を格納する変数
int Diamond_motion_index2;//破壊モーション番号を格納する変数


int LoadImage() {

	if ((g_image.PuyoStageBack = LoadGraph("image/stage_back.png")) == -1)return -1;//ぷよぷよの背景
	if ((g_image.PuyoFrame = LoadGraph("image/stage_frame3.png")) == -1)return -1;//ぷよぷよのステージのフレーム
	if ((LoadDivGraph("image/puzzle/puyo/puyopuyo_Color2.png", 6, 6, 1, 64, 64, g_puyo.puyoType)) == -1)return -1;//ぷよぷよの種類
	
	for (int i = 0; i < 6; i++) {

		if (i == 0) {
			if ((g_image.Diamond[i][0] = LoadGraph("image/puzzle/blue/blue_01.png")) == -1)return -1;
			if ((g_image.Diamond[i][1] = LoadGraph("image/puzzle/blue/blue_02.png")) == -1)return -1;
			if ((g_image.Diamond[i][2] = LoadGraph("image/puzzle/blue/blue_03.png")) == -1)return -1;
			if ((g_image.Diamond[i][3] = LoadGraph("image/puzzle/blue/blue_04.png")) == -1)return -1;
			if ((g_image.Diamond[i][4] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete1.png")) == -1)return -1;
			if ((g_image.Diamond[i][5] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete2.png")) == -1)return -1;
			if ((g_image.Diamond[i][6] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete3.png")) == -1)return -1;
			if ((g_image.Diamond[i][7] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete4.png")) == -1)return -1;
			if ((g_image.Diamond[i][8] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete5.png")) == -1)return -1;
			if ((g_image.Diamond[i][9] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete6.png")) == -1)return -1;
			if ((g_image.Diamond[i][10] = LoadGraph("image/puzzle/blue/blue_delete/blue_delete7.png")) == -1)return -1;

		}
		if (i == 1) {
			if ((g_image.Diamond[i][0] = LoadGraph("image/puzzle/red/red_01.png")) == -1)return -1;
			if ((g_image.Diamond[i][1] = LoadGraph("image/puzzle/red/red_02.png")) == -1)return -1;
			if ((g_image.Diamond[i][2] = LoadGraph("image/puzzle/red/red_03.png")) == -1)return -1;
			if ((g_image.Diamond[i][3] = LoadGraph("image/puzzle/red/red_04.png")) == -1)return -1;
			if ((g_image.Diamond[i][4] = LoadGraph("image/puzzle/red/red_delete/red_delete1.png")) == -1)return -1;
			if ((g_image.Diamond[i][5] = LoadGraph("image/puzzle/red/red_delete/red_delete2.png")) == -1)return -1;
			if ((g_image.Diamond[i][6] = LoadGraph("image/puzzle/red/red_delete/red_delete3.png")) == -1)return -1;
			if ((g_image.Diamond[i][7] = LoadGraph("image/puzzle/red/red_delete/red_delete4.png")) == -1)return -1;
			if ((g_image.Diamond[i][8] = LoadGraph("image/puzzle/red/red_delete/red_delete5.png")) == -1)return -1;
			if ((g_image.Diamond[i][9] = LoadGraph("image/puzzle/red/red_delete/red_delete6.png")) == -1)return -1;
			if ((g_image.Diamond[i][10] = LoadGraph("image/puzzle/red/red_delete/red_delete7.png")) == -1)return -1;

		}
		if (i == 2) {
			if ((g_image.Diamond[i][0] = LoadGraph("image/puzzle/green/green_01.png")) == -1)return -1;
			if ((g_image.Diamond[i][1] = LoadGraph("image/puzzle/green/green_02.png")) == -1)return -1;
			if ((g_image.Diamond[i][2] = LoadGraph("image/puzzle/green/green_03.png")) == -1)return -1;
			if ((g_image.Diamond[i][3] = LoadGraph("image/puzzle/green/green_04.png")) == -1)return -1;
			if ((g_image.Diamond[i][4] = LoadGraph("image/puzzle/green/green_delete/green_delete1.png")) == -1)return -1;
			if ((g_image.Diamond[i][5] = LoadGraph("image/puzzle/green/green_delete/green_delete2.png")) == -1)return -1;
			if ((g_image.Diamond[i][6] = LoadGraph("image/puzzle/green/green_delete/green_delete3.png")) == -1)return -1;
			if ((g_image.Diamond[i][7] = LoadGraph("image/puzzle/green/green_delete/green_delete4.png")) == -1)return -1;
			if ((g_image.Diamond[i][8] = LoadGraph("image/puzzle/green/green_delete/green_delete5.png")) == -1)return -1;
			if ((g_image.Diamond[i][9] = LoadGraph("image/puzzle/green/green_delete/green_delete6.png")) == -1)return -1;
			if ((g_image.Diamond[i][10] = LoadGraph("image/puzzle/green/green_delete/green_delete7.png")) == -1)return -1;

		}
		if (i == 3) {
			if ((g_image.Diamond[i][0] = LoadGraph("image/puzzle/purple/purple_01.png")) == -1)return -1;
			if ((g_image.Diamond[i][1] = LoadGraph("image/puzzle/purple/purple_02.png")) == -1)return -1;
			if ((g_image.Diamond[i][2] = LoadGraph("image/puzzle/purple/purple_03.png")) == -1)return -1;
			if ((g_image.Diamond[i][3] = LoadGraph("image/puzzle/purple/purple_04.png")) == -1)return -1;
			if ((g_image.Diamond[i][4] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete1.png")) == -1)return -1;
			if ((g_image.Diamond[i][5] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete2.png")) == -1)return -1;
			if ((g_image.Diamond[i][6] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete3.png")) == -1)return -1;
			if ((g_image.Diamond[i][7] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete4.png")) == -1)return -1;
			if ((g_image.Diamond[i][8] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete5.png")) == -1)return -1;
			if ((g_image.Diamond[i][9] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete6.png")) == -1)return -1;
			if ((g_image.Diamond[i][10] = LoadGraph("image/puzzle/purple/purple_delete/purple_delete7.png")) == -1)return -1;

		}

		if (i == 4) {
			if ((g_image.Diamond[i][0] = LoadGraph("image/puzzle/yellow/yellow_01.png")) == -1)return -1;
			if ((g_image.Diamond[i][1] = LoadGraph("image/puzzle/yellow/yellow_02.png")) == -1)return -1;
			if ((g_image.Diamond[i][2] = LoadGraph("image/puzzle/yellow/yellow_03.png")) == -1)return -1;
			if ((g_image.Diamond[i][3] = LoadGraph("image/puzzle/yellow/yellow_04.png")) == -1)return -1;
			if ((g_image.Diamond[i][4] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete1.png")) == -1)return -1;
			if ((g_image.Diamond[i][5] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete2.png")) == -1)return -1;
			if ((g_image.Diamond[i][6] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete3.png")) == -1)return -1;
			if ((g_image.Diamond[i][7] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete4.png")) == -1)return -1;
			if ((g_image.Diamond[i][8] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete5.png")) == -1)return -1;
			if ((g_image.Diamond[i][9] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete6.png")) == -1)return -1;
			if ((g_image.Diamond[i][10] = LoadGraph("image/puzzle/yellow/yellow_delete/yellow_delete7.png")) == -1)return -1;

		}
		if (i == 5) {
			if ((g_image.Diamond[i][0] = LoadGraph("image/puzzle/gray/gray_01.png")) == -1)return -1;
			if ((g_image.Diamond[i][1] = LoadGraph("image/puzzle/gray/gray_02.png")) == -1)return -1;
			if ((g_image.Diamond[i][2] = LoadGraph("image/puzzle/gray/gray_03.png")) == -1)return -1;
			if ((g_image.Diamond[i][3] = LoadGraph("image/puzzle/gray/gray_04.png")) == -1)return -1;
			if ((g_image.Diamond[i][4] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete1.png")) == -1)return -1;
			if ((g_image.Diamond[i][5] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete2.png")) == -1)return -1;
			if ((g_image.Diamond[i][6] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete3.png")) == -1)return -1;
			if ((g_image.Diamond[i][7] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete4.png")) == -1)return -1;
			if ((g_image.Diamond[i][8] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete5.png")) == -1)return -1;
			if ((g_image.Diamond[i][9] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete6.png")) == -1)return -1;
			if ((g_image.Diamond[i][10] = LoadGraph("image/puzzle/gray/gray_delete/gray_delete7.png")) == -1)return -1;

		}
	}
	

	return 0;
}