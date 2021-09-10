#pragma once


//ぷよぷよが落下する時間
extern int down_timer;

//ゲームスコア
extern int GameScore;

//ぷよぷよの基礎情報
struct Puyo
{
	int i=0, x=0, y=0;
	int kx1=0, ky1=0, kx2=0, ky2=0;	// 仮の座標
	bool flag=false;				// 汎用フラグ
	int pnext1=0, pnext2=0;		// ネクストぷよ番号（０～４）
	int pno1=0, pno2=0;			// 現在のぷよ番号（０～４）
	int px1=0, py1=0, px2=0, py2=0;	// ぷよのＸ、Ｙ座標

	int CHAIN_NUMBER = 4;//ぷよぷよの消去条件
	int puyoType[6];//ぷよぷよの画像
};
extern Puyo g_puyo;

//ゲームメインの状態
extern void PuyoInit();
extern void PuyoStage();
extern void PuyoMove();
extern void PuyoDebug();

extern int CheckPuyo(int x, int y, int pno, int cno);

extern int PuyoField[15][8];// 画面データ