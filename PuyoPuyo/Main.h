#pragma once

//ゲーム画面
#define SCREEN_HEIGHT 930//スクリーンの高さ
#define SCREEN_WIDTH 700//スクリーンの幅

//ぷよぷよの種類
#define PUYO_COLOR_MAX 6


class PuyoPuyo {

//ゲーム画面関数の初期化
public:

	//ゲームタイトルからスタート
	int GameState=0;

	//ゲーム画面の状態

	void GameTitle();//0

	void GameInit();//1

	int GameMain();//2

	void GameOver();//3

private:

};


//ゲームオーバーのflg
extern bool GameOverflg;

//デバックのflg
extern bool debugflg;

//キー読み込みの変数
extern int g_KeyFlg;
extern int g_NowKey;
extern int g_OldKey;
extern char key[256];



