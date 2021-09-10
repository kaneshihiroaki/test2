#include "DxLib.h"
#include "Main.h"
#include "PuyoPuyo.h"
#include "image.h"


//キー設定
int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

//ゲームオーバーか調べる
bool GameOverflg = false;

//デバックモード
bool debugflg = false;



// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)return -1;	// エラーが起きたら直ちに終了
	
	SetMainWindowText("Puyo Puyo");// タイトル

	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetDrawScreen(DX_SCREEN_BACK);

	PuyoPuyo* puyopuyo = new PuyoPuyo();

	// 画像初期化処理
	if (LoadImage() == -1)	return -1;	// エラーが起きたら直ちに終了	

	// メインループ(何かキーが押されたらループを抜ける)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 )
	{
		

		//入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// 画面の初期化

		switch (puyopuyo->GameState)
		{
		case 0:
			//ゲームタイトル
			puyopuyo->GameTitle();
			break;
		case 1:
			//ゲーム初期化
			puyopuyo->GameInit();
			break;
		case 2:
			//ゲームメイン画面
			puyopuyo->GameMain();
			break;
		case 3:
			//リザルト画面
			puyopuyo->GameOver();
			break;

		default:
			break;
		}

		
		// 裏画面の内容を表画面に反映する
		ScreenFlip();
	}
	// キー入力待ちをする
	//WaitKey();

	// ＤＸライブラリの後始末
	DxLib_End();

	return 0;
}



//タイトル
void PuyoPuyo::GameTitle() {

	//画面表示
	DrawGraph(0, 0, g_image.PuyoStageBack, TRUE);
	DrawGraph(45, 0, g_image.PuyoFrame, TRUE);

	SetFontSize(100);
	DrawFormatString(55, 40, 0xFFFFFF, "ぷよぷよ");

	SetFontSize(50);
	DrawFormatString(65, 360, 0xFFFFFF, "Aキーでスタート");
	DrawFormatString(80, 440, 0xFFFFFF, "Escキーで終了");

	//Aキー
	if (g_KeyFlg & PAD_INPUT_X || g_KeyFlg & PAD_INPUT_A) {
		GameState = 1;
	}
	

}

//初期化
void PuyoPuyo::GameInit() {

	//ゲームオーバーのフラグ
	GameOverflg = false;

	//落下時間の初期化
	down_timer = 0;

	//ゲームスコアの初期化の初期化
	GameScore = 0;

	//ステージ初期化
	PuyoInit();

	//ゲームのステータス
	GameState = 2;
}

//ﾒｲﾝ画面
int PuyoPuyo::GameMain() {
	

	//ステージ描画
	PuyoStage();

	//ぷよぷよのメイン処理
	PuyoMove();

	//ぷよぷよのデバック文字表示
	PuyoDebug();

	if (GameOverflg == true) {
		//ゲームオーバーへ
		GameState = 3;
	}

	return 0;
}


void PuyoPuyo::GameOver() {

	//画面表示
	DrawGraph(0, 0, g_image.PuyoStageBack, TRUE);
	DrawGraph(45, 0, g_image.PuyoFrame, TRUE);


	//残っているぷよ表示
	for (g_puyo.y = 0; g_puyo.y < 15 - 1; g_puyo.y++) {
		for (g_puyo.x = 1; g_puyo.x < 8 - 1; g_puyo.x++) {
			if (PuyoField[g_puyo.y][g_puyo.x] != -1) {
				DrawGraph(g_puyo.x * 64, g_puyo.y * 64, g_image.Diamond[PuyoField[g_puyo.y][g_puyo.x]][Diamond_motion_index], TRUE);
				DrawGraph(g_puyo.x * 64, g_puyo.y * 64, g_image.Diamond[PuyoField[g_puyo.y][g_puyo.x]][Diamond_motion_index], TRUE);
			}
		}
	}

	//Aキー
	if (g_KeyFlg & PAD_INPUT_X || g_KeyFlg & PAD_INPUT_A) {
		GameState = 1;
	}
	DrawBox(150,200,560,500,0x000000,TRUE);
	SetFontSize(80);
	DrawFormatString(190, 220, 0xFF0000, "GameOver");
	SetFontSize(30);
	DrawFormatString(577, 300, 0xFFFFFF, "Score");
	DrawFormatString(607, 340, 0xFFFFFF, "%d", GameScore);
	SetFontSize(50);
	DrawFormatString(170, 360, 0xFFFFFF, "Aキーでもう一度");
	DrawFormatString(190, 440, 0xFFFFFF, "Escキーで終了");

	
	
}



