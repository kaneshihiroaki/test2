///////////////////////////////////////////////////////////////////////////////
//	ぷよぷよ

#include "el.h"

#define MAIN_SCREEN 1

void MainScreen(void);

DDOBJ puyo;				// ぷよのビットマップ
int field[15][8];		// 画面データ
int cmb[15][8];			// 結合チェック用
bool elist[30];			// 消すリスト

///////////////////////////////////////////////////////////////////////////////
//	メイン関数

int elMain("ぷよぷよ");
{
	elWindow(256, 448, FALSE);
	elLoop()
	{
		elSetScreen(MAIN_SCREEN,MainScreen());
	}
	elExitMain();
}

///////////////////////////////////////////////////////////////////////////////
//	ウインドウ生成関数

void elCreate(void)
{
	elDraw::Screen(256, 448);
	// ぷよ画像読み込み
	puyo = elDraw::LoadObject("puyo.bmp");
	// フィールドをクリア
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 8; x++) {
			if (x == 0 || x == 7 || y == 14) field[y][x] = 5;
			else field[y][x] = -1;
		}
	}
	elCallScreen(MAIN_SCREEN);
}

///////////////////////////////////////////////////////////////////////////////
//	キーボード関数

void elKeyboard(void)
{
	case VK_ESCAPE:
	{
		elDraw::Exit();
		break;
	}
	elExitKeyboard();
}

///////////////////////////////////////////////////////////////////////////////
//	イベント関数

long elEvent(void)
{
	elExitEvent();
}

///////////////////////////////////////////////////////////////////////////////
//	メイン画面

// ぷよ結合チェック関数（再帰）
// 引数 x, y:調べるぷよ座標 pno:ぷよ番号 cno:結合番号
int CheckCombine(int x, int y, int pno, int cno)
{
	if (field[y][x] != pno || cmb[y][x] != 0) return 0;
	int ret = 1;
	cmb[y][x] = cno;
	if (y > 0) ret += CheckCombine(x, y - 1, pno, cno);		// 上
	ret += CheckCombine(x + 1, y, pno, cno);				// 右
	ret += CheckCombine(x, y + 1, pno, cno);				// 下
	ret += CheckCombine(x - 1, y, pno, cno);				// 左
	return ret;
}

void MainScreen(void)
{
	int i, x, y;
	int kx1, ky1, kx2, ky2;			// 仮の座標
	bool flag;						// 汎用フラグ
	static int pnext1, pnext2;		// ネクストぷよ番号（０～４）
	static int pno1, pno2;			// 現在のぷよ番号（０～４）
	static int px1, py1, px2, py2;	// ぷよのＸ、Ｙ座標
	static int keyLeft = FREE_KEY;	// 左キー
	static int keyRight = FREE_KEY;	// 右キー
	static int keyDown = FREE_KEY;	// 下キー
	static int keySpace = FREE_KEY;	// スペースキー
	static bool overFlag = false;	// ゲームオーバーフラグ
	static int score = 0;			// 得点
	static DWORD rpt = 0;			// キーリピート時間
	static DWORD downTime = 1000;	// 1ブロック落下する時間(ms)
	static DWORD downCount;			// 落下時間までの猶予(ms)
	static enum {					// 状態
		NEXT,						// ネクストぷよ出現
		NORMAL,						// 通常
		FALL,						// ぷよ落下
		ERASE1,						// ぷよ消し前
		ERASE2,						// ぷよ消し
	} status = NEXT;
	if (elChangeScreen()) {pnext1 = rand() % 5; pnext2 = rand() % 5;}
	elDraw::Clear();
	DWORD nowTime = timeGetTime();
	switch (status) {
	// ネクストぷよ出現
	case NEXT:
		px1 = 3; py1 = 1; px2 = 3; py2 = 0;
		pno1 = pnext1; pno2 = pnext2;
		pnext1 = rand() % 5; pnext2 = rand() % 5;
		downCount = timeGetTime();
		if (downTime > 100) downTime -= 10;
		else downTime--;
		if (downTime < 10) downTime = 10;
		status = NORMAL;
		break;
	// 通常
	case NORMAL:
		kx1 = px1; ky1 = py1;
		kx2 = px2; ky2 = py2;
		elSystem::GetKey(VK_LEFT, &keyLeft);
		elSystem::GetKey(VK_RIGHT, &keyRight);
		elSystem::GetKey(VK_DOWN, &keyDown);
		elSystem::GetKey(VK_SPACE, &keySpace);
		flag = false;
		if (keySpace == PUSH_KEY) {
			if (kx2 > kx1) {kx2 = kx1; ky2 = ky1 + 1;}
			else if (kx2 < kx1) {kx2 = kx1; ky2 = ky1 - 1;}
			else if (ky2 > ky1) {ky2 = ky1; kx2 = kx1 - 1;}
			else {ky2 = ky1; kx2 = kx1 + 1;}
		} else if (keyDown == PUSH_KEY || keyDown == HOLD_KEY && nowTime - rpt > 10) {
			ky1++; ky2++; flag = true; rpt = nowTime;
		} else if (keyLeft == PUSH_KEY || keyLeft == HOLD_KEY && nowTime - rpt > 150) {
			kx1--; kx2--; rpt = nowTime;
		} else if (keyRight == PUSH_KEY || keyRight == HOLD_KEY && nowTime - rpt > 150) {
			kx1++; kx2++; rpt = nowTime;
		} else if (nowTime - downCount > downTime) {
			ky1++; ky2++; flag = true; downCount = nowTime;
		}
		if (field[ky1][kx1] == -1 && field[ky2][kx2] == -1) {
			px1 = kx1; py1 = ky1;
			px2 = kx2; py2 = ky2;
		} else if (flag) {
			field[py1][px1] = pno1;
			field[py2][px2] = pno2;
			status = FALL;
		}
		break;
	// ぷよ落下
	case FALL:
		Sleep(50);
		flag = false;
		for (y = 12; y >= 0; y--) {
			for (x = 1; x < 7; x++) {
				if (field[y][x] != -1 && field[y + 1][x] == -1) {
					field[y + 1][x] = field[y][x];
					field[y][x] = -1;
					flag = true;
				}
			}
		}
		if (flag == false) status = ERASE1;
		break;
	// ぷよ消し前
	case ERASE1:
		// ぷよ結合チェック
		flag = false;
		for (y = 0; y < 15; y++) for (x = 0; x < 8; x++) cmb[y][x] = 0;
		for (i = 0; i < 30; i++) elist[i] = false;
		for (y = 13, i = 0; y >= 0; y--) {
			for (x = 1; x < 7; x++) {
				if (cmb[y][x] == 0 && field[y][x] != -1) {
					i++;
					int ret = CheckCombine(x, y, field[y][x], i);
					if (ret >= 4) {
						flag = true;
						elist[i] = true;
						score += ret * 10;
					}
				}
			}
		}
		if (flag) {
			// 結合ぷよがある場合は消しぷよと入れ替え
			for (y = 13; y >= 0; y--) {
				for (x = 1; x < 7; x++) {
					if (elist[cmb[y][x]]) field[y][x] = 5;
				}
			}
			status = ERASE2;
		} else {
			// 結合ぷよがない場合はゲームオーバーチェックして次へ
			for (y = 0; y < 2; y++) {
				for (x = 1; x < 7; x++) {
					if (field[y][x] != -1) overFlag = true;
				}
			}
			status = NEXT;
		}
		break;
	// ぷよ消し
	case ERASE2:
		Sleep(500);
		for (y = 13; y >= 0; y--) {
			for (x = 1; x < 7; x++) {
				if (field[y][x] == 5) field[y][x] = -1;
			}
		}
		status = FALL;
		break;
	}
	// 画面表示
	elDraw::Box(192, 0, 256, 448, RGB(150, 150, 150), RGB(150, 150, 150), 0);
	elDraw::Line(0, 64, 192, 64, RGB(255, 255, 255), 1);
	SHOW(210, 16, "SCORE");
	SHOW2(210, 32, "%d", score);
	SHOW(212, 128, "NEXT");
	for (y = 0; y < 14; y++) {
		for (x = 1; x < 7; x++) {
			if (field[y][x] != -1) {
				elDraw::Layer((x - 1) * 32, y * 32, puyo,
					field[y][x] * 32, 0, field[y][x] * 32 + 32, 32);
			}
		}
	}
	// 現在のぷよ表示
	if (status == NORMAL) {
		elDraw::Layer((px1 - 1) * 32, py1 * 32,
			puyo, pno1 * 32, 0, pno1 * 32 + 32, 32);
		elDraw::Layer((px2 - 1) * 32, py2 * 32,
			puyo, pno2 * 32, 0, pno2 * 32 + 32, 32);
	}
	// ネクストぷよ表示
	elDraw::Layer(208, 144, puyo, pnext2 * 32, 0, pnext2 * 32 + 32, 32);
	elDraw::Layer(208, 144 + 32, puyo, pnext1 * 32, 0, pnext1 * 32 + 32, 32);
	elDraw::Refresh();
	// ゲームオーバー処理
	if (overFlag) {
		elSystem::Message("ゲームオーバー");
		elDraw::Exit();
	}
}

