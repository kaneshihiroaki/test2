#pragma once


//�Ղ�Ղ悪�������鎞��
extern int down_timer;

//�Q�[���X�R�A
extern int GameScore;

//�Ղ�Ղ�̊�b���
struct Puyo
{
	int i=0, x=0, y=0;
	int kx1=0, ky1=0, kx2=0, ky2=0;	// ���̍��W
	bool flag=false;				// �ėp�t���O
	int pnext1=0, pnext2=0;		// �l�N�X�g�Ղ�ԍ��i�O�`�S�j
	int pno1=0, pno2=0;			// ���݂̂Ղ�ԍ��i�O�`�S�j
	int px1=0, py1=0, px2=0, py2=0;	// �Ղ�̂w�A�x���W

	int CHAIN_NUMBER = 4;//�Ղ�Ղ�̏�������
	int puyoType[6];//�Ղ�Ղ�̉摜
};
extern Puyo g_puyo;

//�Q�[�����C���̏��
extern void PuyoInit();
extern void PuyoStage();
extern void PuyoMove();
extern void PuyoDebug();

extern int CheckPuyo(int x, int y, int pno, int cno);

extern int PuyoField[15][8];// ��ʃf�[�^