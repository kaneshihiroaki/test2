#include "DxLib.h"
#include "Main.h"
#include "PuyoPuyo.h"
#include "image.h"


//�L�[�ݒ�
int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

//�Q�[���I�[�o�[�����ׂ�
bool GameOverflg = false;

//�f�o�b�N���[�h
bool debugflg = false;



// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)return -1;	// �G���[���N�����璼���ɏI��
	
	SetMainWindowText("Puyo Puyo");// �^�C�g��

	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetDrawScreen(DX_SCREEN_BACK);

	PuyoPuyo* puyopuyo = new PuyoPuyo();

	// �摜����������
	if (LoadImage() == -1)	return -1;	// �G���[���N�����璼���ɏI��	

	// ���C�����[�v(�����L�[�������ꂽ�烋�[�v�𔲂���)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 )
	{
		

		//���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// ��ʂ̏�����

		switch (puyopuyo->GameState)
		{
		case 0:
			//�Q�[���^�C�g��
			puyopuyo->GameTitle();
			break;
		case 1:
			//�Q�[��������
			puyopuyo->GameInit();
			break;
		case 2:
			//�Q�[�����C�����
			puyopuyo->GameMain();
			break;
		case 3:
			//���U���g���
			puyopuyo->GameOver();
			break;

		default:
			break;
		}

		
		// ����ʂ̓��e��\��ʂɔ��f����
		ScreenFlip();
	}
	// �L�[���͑҂�������
	//WaitKey();

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}



//�^�C�g��
void PuyoPuyo::GameTitle() {

	//��ʕ\��
	DrawGraph(0, 0, g_image.PuyoStageBack, TRUE);
	DrawGraph(45, 0, g_image.PuyoFrame, TRUE);

	SetFontSize(100);
	DrawFormatString(55, 40, 0xFFFFFF, "�Ղ�Ղ�");

	SetFontSize(50);
	DrawFormatString(65, 360, 0xFFFFFF, "A�L�[�ŃX�^�[�g");
	DrawFormatString(80, 440, 0xFFFFFF, "Esc�L�[�ŏI��");

	//A�L�[
	if (g_KeyFlg & PAD_INPUT_X || g_KeyFlg & PAD_INPUT_A) {
		GameState = 1;
	}
	

}

//������
void PuyoPuyo::GameInit() {

	//�Q�[���I�[�o�[�̃t���O
	GameOverflg = false;

	//�������Ԃ̏�����
	down_timer = 0;

	//�Q�[���X�R�A�̏������̏�����
	GameScore = 0;

	//�X�e�[�W������
	PuyoInit();

	//�Q�[���̃X�e�[�^�X
	GameState = 2;
}

//Ҳ݉��
int PuyoPuyo::GameMain() {
	

	//�X�e�[�W�`��
	PuyoStage();

	//�Ղ�Ղ�̃��C������
	PuyoMove();

	//�Ղ�Ղ�̃f�o�b�N�����\��
	PuyoDebug();

	if (GameOverflg == true) {
		//�Q�[���I�[�o�[��
		GameState = 3;
	}

	return 0;
}


void PuyoPuyo::GameOver() {

	//��ʕ\��
	DrawGraph(0, 0, g_image.PuyoStageBack, TRUE);
	DrawGraph(45, 0, g_image.PuyoFrame, TRUE);


	//�c���Ă���Ղ�\��
	for (g_puyo.y = 0; g_puyo.y < 15 - 1; g_puyo.y++) {
		for (g_puyo.x = 1; g_puyo.x < 8 - 1; g_puyo.x++) {
			if (PuyoField[g_puyo.y][g_puyo.x] != -1) {
				DrawGraph(g_puyo.x * 64, g_puyo.y * 64, g_image.Diamond[PuyoField[g_puyo.y][g_puyo.x]][Diamond_motion_index], TRUE);
				DrawGraph(g_puyo.x * 64, g_puyo.y * 64, g_image.Diamond[PuyoField[g_puyo.y][g_puyo.x]][Diamond_motion_index], TRUE);
			}
		}
	}

	//A�L�[
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
	DrawFormatString(170, 360, 0xFFFFFF, "A�L�[�ł�����x");
	DrawFormatString(190, 440, 0xFFFFFF, "Esc�L�[�ŏI��");

	
	
}



