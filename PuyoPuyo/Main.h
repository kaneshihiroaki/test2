#pragma once

//�Q�[�����
#define SCREEN_HEIGHT 930//�X�N���[���̍���
#define SCREEN_WIDTH 700//�X�N���[���̕�

//�Ղ�Ղ�̎��
#define PUYO_COLOR_MAX 6


class PuyoPuyo {

//�Q�[����ʊ֐��̏�����
public:

	//�Q�[���^�C�g������X�^�[�g
	int GameState=0;

	//�Q�[����ʂ̏��

	void GameTitle();//0

	void GameInit();//1

	int GameMain();//2

	void GameOver();//3

private:

};


//�Q�[���I�[�o�[��flg
extern bool GameOverflg;

//�f�o�b�N��flg
extern bool debugflg;

//�L�[�ǂݍ��݂̕ϐ�
extern int g_KeyFlg;
extern int g_NowKey;
extern int g_OldKey;
extern char key[256];



