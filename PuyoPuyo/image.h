#pragma once

//画像読み込み
int LoadImage();

//画像読み込み
struct Image
{

    int PuyoStageBack;//背景画像
	int PuyoFrame;  //フレーム画像

	//ダイヤの画像
	int Diamond[6][11];

};
extern Image g_image;

//ダイヤが光る時のアニメーション
extern int Diamond_Anime[];
extern int DiamondDelete_Anime[];
extern int Diamond_ANI_SPEED;//モーションの速さ
extern int Diamond_act_wait;//1モーション待つ時間
extern int Diamond_MOTION_INDEX;//光るモーションの数
extern int DiamondDelete_MOTION_INDEX;//破壊モーションの数
extern int Diamond_act_index;//光るモーションの動いている数
extern int Diamond_act_index2;//破壊モーションの動いている数
extern int Diamond_motion_index;//光るモーション番号を格納する変数
extern int Diamond_motion_index2;//破壊モーション番号を格納する変数

