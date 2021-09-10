#include "Dxlib.h"
#include "Main.h"
#include "image.h"
#include "PuyoPuyo.h"


// �Q�[���t�B�[���h�̉��Əc�̃}�X��
#define Stage_Width 8//Stage�̕�
#define Stage_Height 15//Stage�̍���

//�Ղ�Ղ�̃X�^�[�g�ʒu
#define PUYO_START_X 3
#define PUYO_START_Y 1

//�Ղ�Ղ�̃u���b�N�T�C�Y
#define PUYO_SIZE 64

//�\���̐錾
Puyo g_puyo;

//�Ղ�Ղ�̃X�e�[�W
int PuyoField[Stage_Height][Stage_Width];// ��ʃf�[�^
int PuyoCOMBO[Stage_Height][Stage_Width];// �����`�F�b�N�p
bool Puyodelete[30];// �������X�g


//�Q�[�����C���̃X�e�[�^�X
enum {					             // ���
	PUYO_NEXT,						// �l�N�X�g�Ղ�o��
	PUYO_NORMAL,					// ��������
	PUYO_FALL,						// �Ղ�Ղ旎��
	PUYO_ERASE,						// �Ղ�����O
	PUYO_ERASE2,					// �Ղ����
};

//�Q�[�����C���̃X�e�[�^�X
int GameMain_State;

int GameScore=0;

//��������
int down_timer;

//�A���J�E���g
int rensacount;

void PuyoInit() {

	//�Q�[�����C���̃X�e�[�^�X
	GameMain_State = PUYO_NEXT;// �l�N�X�g�Ղ�o��

	// �t�B�[���h���N���A
	for (g_puyo.y = 0; g_puyo.y < Stage_Height; g_puyo.y++) {
		for (g_puyo.x = 0; g_puyo.x < Stage_Width; g_puyo.x++) {
			if (g_puyo.x == 0 || g_puyo.x == Stage_Width - 1 || g_puyo.y == Stage_Height - 1) {
				PuyoField[g_puyo.y][g_puyo.x] = 5;
			}
			else {
				PuyoField[g_puyo.y][g_puyo.x] = -1;
			}
		}
	}
}

void PuyoStage(){
	//�_�C�������h�̃A�j���[�V�����ݒ�
	if (--Diamond_act_wait <= 0)
	{
		Diamond_act_index++;
		Diamond_act_index2++;
		Diamond_act_wait = Diamond_ANI_SPEED;
		Diamond_act_index %= Diamond_MOTION_INDEX;
		Diamond_act_index2 %= DiamondDelete_MOTION_INDEX;
	}

	Diamond_motion_index = Diamond_Anime[Diamond_act_index];
	Diamond_motion_index2 = DiamondDelete_Anime[Diamond_act_index2];

	//��ʕ\��
	DrawGraph(0, 0, g_image.PuyoStageBack, TRUE);
	DrawGraph(45, 0, g_image.PuyoFrame, TRUE);


	//�Q�[���I�[�o�[�̃��C��
	//DrawBox(512, 0, 0, PUYO_SIZE, 0xFF0000, false);


	//�X�e�[�W�̃}�X
	if (debugflg == true) {
		for (g_puyo.y = 0; g_puyo.y < Stage_Height + 1; g_puyo.y++) {
			for (g_puyo.x = 1; g_puyo.x < Stage_Width + 1; g_puyo.x++) {

				DrawBox(g_puyo.x * PUYO_SIZE, g_puyo.y * PUYO_SIZE, 0, 0, 0xFFFFFF, false);

			}
		}
	}

	//�c���Ă���Ղ�\��
		for (g_puyo.y = 0; g_puyo.y < Stage_Height - 1; g_puyo.y++) {
			for (g_puyo.x = 1; g_puyo.x < Stage_Width - 1; g_puyo.x++) {
				if (PuyoField[g_puyo.y][g_puyo.x] != -1) {
					DrawGraph(g_puyo.x * PUYO_SIZE, g_puyo.y * PUYO_SIZE, g_image.Diamond[PuyoField[g_puyo.y][g_puyo.x]][Diamond_motion_index], TRUE);
					DrawGraph(g_puyo.x * PUYO_SIZE, g_puyo.y* PUYO_SIZE, g_image.Diamond[PuyoField[g_puyo.y][g_puyo.x]][Diamond_motion_index], TRUE);
				}
			}
		}


	//��������Ղ�Ղ��\��
	if (GameMain_State == PUYO_NORMAL) {
		DrawGraph(g_puyo.px1 * PUYO_SIZE, g_puyo.py1 * PUYO_SIZE, g_image.Diamond[g_puyo.pno1][Diamond_motion_index], TRUE);
		DrawGraph(g_puyo.px2 * PUYO_SIZE, g_puyo.py2 * PUYO_SIZE, g_image.Diamond[g_puyo.pno2][Diamond_motion_index], TRUE);
	}

	
	//next�Ղ�\��
	SetFontSize(30);
	DrawFormatString(577, 20, 0xFFFFFF, "NEXT");
	DrawBox(560, 60,660,200, 0xFFFFFF,FALSE);
	DrawGraph(9 * PUYO_SIZE, 2 * PUYO_SIZE, g_image.Diamond[g_puyo.pnext2][Diamond_motion_index], TRUE);
	DrawGraph(9 * PUYO_SIZE, 1 * PUYO_SIZE, g_image.Diamond[g_puyo.pnext1][Diamond_motion_index], TRUE);


	//�X�R�A�\��
	DrawFormatString(577, 300, 0xFFFFFF, "Score");
	DrawFormatString(607, 340, 0xFFFFFF, "%d",GameScore);

	DrawFormatString(585, 375, 0xFFFFFF, "�A��");
	DrawFormatString(607, 410, 0xFFFFFF, "%d", rensacount);

}

void PuyoMove() {


	switch (GameMain_State) {

	case PUYO_NEXT://�l�N�X�g�Ղ�o��
		//�A���J�E���g������
		rensacount = 0;
		//���̂Ղ�
			g_puyo.px1 = PUYO_START_X;
			g_puyo.py1 = PUYO_START_Y;

		//���̂Ղ�̎��
			g_puyo.pno1 = g_puyo.pnext1;

		//��̂Ղ�
			g_puyo.px2 = PUYO_START_X;
			g_puyo.py2 = 0; 

		//��̂Ղ�̎��
			g_puyo.pno2 = g_puyo.pnext2;

		//���̂Ղ�̎�ނ����߂�
			g_puyo.pnext1 = rand() % 5;

		//��̂Ղ�̎�ނ����߂�
			g_puyo.pnext2 = rand() % 5;

			
		GameMain_State = PUYO_NORMAL;
	break;

	case PUYO_NORMAL:// ��������
		
	g_puyo.kx1 = g_puyo.px1; 
	g_puyo.ky1 = g_puyo.py1;

	g_puyo.kx2 = g_puyo.px2; 
	g_puyo.ky2 = g_puyo.py2;

	g_puyo.flag = false;

	if (g_puyo.flag == false) {
		//�������Ԍv��
		down_timer = (down_timer + 1) % 61;
	}

	//�X�y�[�X�L�[�ŉ�]
	if (g_KeyFlg & PAD_INPUT_10||g_KeyFlg & PAD_INPUT_A) {
	if (g_puyo.kx2 > g_puyo.kx1) {

	                 g_puyo.kx2 = g_puyo.kx1; g_puyo.ky2 = g_puyo.ky1 + 1;

	                             }
    else if (g_puyo.kx2 < g_puyo.kx1) {

			        g_puyo.kx2 = g_puyo.kx1; g_puyo.ky2 = g_puyo.ky1 - 1;

			}
	else if (g_puyo.ky2 > g_puyo.ky1) {

	               g_puyo.ky2 = g_puyo.ky1; g_puyo.kx2 = g_puyo.kx1 - 1;

	        }
	else {  

	               g_puyo.ky2 = g_puyo.ky1; g_puyo.kx2 = g_puyo.kx1 + 1;

	     }
    }
	//�ړ�
	
	//���L�[
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		g_puyo.ky1++;
		g_puyo.ky2++;
		g_puyo.flag = true;
	}
	//�E�L�[
	else if (g_KeyFlg & PAD_INPUT_RIGHT) {
		g_puyo.kx1++;
		g_puyo.kx2++;
	}
	//���L�[
	else if (g_KeyFlg & PAD_INPUT_LEFT) {
		g_puyo.kx1--;
		g_puyo.kx2--;
	}
	else  if (down_timer >= 60) {
		g_puyo.ky1++; g_puyo.ky2++;
		g_puyo.flag = true;
	}

	//�f�o�b�N��ԂȂ��L�[����
	else if (debugflg == true) {
		//��L�[
		if (g_KeyFlg & PAD_INPUT_UP) {
			g_puyo.ky1--;
			g_puyo.ky2--;
			g_puyo.flag = true;
		}

	}


	if (PuyoField[g_puyo.ky1][g_puyo.kx1] == -1 && PuyoField[g_puyo.ky2][g_puyo.kx2] == -1) {

		g_puyo.px1 = g_puyo.kx1; 
		g_puyo.py1 = g_puyo.ky1;
		g_puyo.px2 = g_puyo.kx2; 
		g_puyo.py2 = g_puyo.ky2;

		g_puyo.flag = true;
	}
	else if (g_puyo.flag) {

		//���̂Ղ�
		PuyoField[g_puyo.py1][g_puyo.px1] = g_puyo.pno1;

		//��̂Ղ�
		PuyoField[g_puyo.py2][g_puyo.px2] = g_puyo.pno2;

		GameMain_State = PUYO_FALL;
	}
	
	break;

	case PUYO_FALL://�Ղ�Ղ旎��

		Sleep(50);//������x�点��
		g_puyo.flag = false;
		for (g_puyo.y = Stage_Height-3; g_puyo.y >= 0; g_puyo.y--) {
			for (g_puyo.x = 1; g_puyo.x < Stage_Width-1; g_puyo.x++) {
				if (PuyoField[g_puyo.y][g_puyo.x] != -1 && PuyoField[g_puyo.y + 1][g_puyo.x] == -1) {
					PuyoField[g_puyo.y + 1][g_puyo.x] = PuyoField[g_puyo.y][g_puyo.x];
					PuyoField[g_puyo.y][g_puyo.x] = -1;
					g_puyo.flag = true;
				}
			}
		}
		if (g_puyo.flag == false) { 
			GameMain_State = PUYO_ERASE;
		}

	break;

	case PUYO_ERASE://�Ղ�Ղ�����O

		// �Ղ挋���`�F�b�N
		g_puyo.flag = false;
		for (g_puyo.y = 0; g_puyo.y < Stage_Height; g_puyo.y++) {
			for (g_puyo.x = 0; g_puyo.x < Stage_Width; g_puyo.x++) {
				PuyoCOMBO[g_puyo.y][g_puyo.x] = 0;
			}
		}
		for (g_puyo.i = 0; g_puyo.i < 30; g_puyo.i++) {
			Puyodelete[g_puyo.i] = false;
		}
		for (g_puyo.y = Stage_Height - 2, g_puyo.i = 0; g_puyo.y >= 0; g_puyo.y--) {
			for (g_puyo.x = 1; g_puyo.x < Stage_Width-1; g_puyo.x++) {
				if (PuyoCOMBO[g_puyo.y][g_puyo.x] == 0 && PuyoField[g_puyo.y][g_puyo.x] != -1) {
					g_puyo.i++;
					int ret = CheckPuyo(g_puyo.x, g_puyo.y, PuyoField[g_puyo.y][g_puyo.x], g_puyo.i);
					if (ret >= g_puyo.CHAIN_NUMBER) {
						GameScore += ret * 10;
						rensacount++;
						g_puyo.flag = true;
						Puyodelete[g_puyo.i] = true;
					}
				}
			}
		}
		if (g_puyo.flag) {
			// �����Ղ悪����ꍇ�͏����Ղ�Ɠ���ւ�
			for (g_puyo.y = Stage_Height-2; g_puyo.y >= 0; g_puyo.y--) {
				for (g_puyo.x = 1; g_puyo.x < Stage_Width-1; g_puyo.x++) {
					if (Puyodelete[PuyoCOMBO[g_puyo.y][g_puyo.x]]) PuyoField[g_puyo.y][g_puyo.x] = 5;
				}
			}
				GameMain_State = PUYO_ERASE2;
		}else{
			// �����Ղ悪�Ȃ��ꍇ�̓Q�[���I�[�o�[�`�F�b�N���Ď���
			for (g_puyo.y = 0; g_puyo.y < 2; g_puyo.y++) {
				for (g_puyo.x = 1; g_puyo.x < Stage_Width-1; g_puyo.x++) {
					if (PuyoField[g_puyo.y][g_puyo.x] != -1)GameOverflg= true;
				}
			}
			down_timer = 0;
			GameMain_State = PUYO_NEXT;
		}

	break;

	case PUYO_ERASE2://�Ղ�Ղ����

		Sleep(500);//������x�点��

		for (g_puyo.y = Stage_Height-2; g_puyo.y >= 0; g_puyo.y--) {
			for (g_puyo.x = 1; g_puyo.x < Stage_Width-1; g_puyo.x++) {
				if (PuyoField[g_puyo.y][g_puyo.x] == 5) PuyoField[g_puyo.y][g_puyo.x] = -1;
			}
		}
		GameMain_State = PUYO_FALL;

	break;
	}
	
}

void PuyoDebug() {
	if (debugflg == true) {
	
		SetFontSize(20);
		DrawFormatString(20, 40, 0xFFFFFF, "GameMain_State:%d", GameMain_State);
		DrawFormatString(20, 60, 0xFFFFFF, "g_puyo.flag:%d", g_puyo.flag);
		DrawFormatString(20, 80, 0xFFFFFF, "g_puyo.px1:%d", g_puyo.px1);
		DrawFormatString(20, 100, 0xFFFFFF, "g_puyo.py1:%d", g_puyo.py1);
		DrawFormatString(20, 120, 0xFFFFFF, "g_puyo.px2:%d", g_puyo.px2);
		DrawFormatString(20, 140, 0xFFFFFF, "g_puyo.py2:%d", g_puyo.py2);
		DrawFormatString(20, 160, 0xFFFFFF, "down_timer:%d", down_timer);
		DrawFormatString(20, 180, 0xFFFFFF, "Diamond_motion_index2:%d", Diamond_motion_index2);


	}
}


// �Ղ挋���`�F�b�N�֐��i�ċA�j
// ���� x, y:���ׂ�Ղ���W pno:�Ղ�ԍ� cno:�����ԍ�
int CheckPuyo(int x, int y, int pno, int cno)
{

	if (PuyoField[y][x] != pno || PuyoCOMBO[y][x] != 0) return 0;
	int ret = 1;
	PuyoCOMBO[y][x] = cno;
	if (y > 0) ret += CheckPuyo(x, y - 1, pno, cno);	// ��
	ret += CheckPuyo(x + 1, y, pno, cno);				// �E
	ret += CheckPuyo(x, y + 1, pno, cno);				// ��
	ret += CheckPuyo(x - 1, y, pno, cno);				// ��
	return ret;

}

