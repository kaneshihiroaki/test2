#pragma once

//�摜�ǂݍ���
int LoadImage();

//�摜�ǂݍ���
struct Image
{

    int PuyoStageBack;//�w�i�摜
	int PuyoFrame;  //�t���[���摜

	//�_�C���̉摜
	int Diamond[6][11];

};
extern Image g_image;

//�_�C�������鎞�̃A�j���[�V����
extern int Diamond_Anime[];
extern int DiamondDelete_Anime[];
extern int Diamond_ANI_SPEED;//���[�V�����̑���
extern int Diamond_act_wait;//1���[�V�����҂���
extern int Diamond_MOTION_INDEX;//���郂�[�V�����̐�
extern int DiamondDelete_MOTION_INDEX;//�j�󃂁[�V�����̐�
extern int Diamond_act_index;//���郂�[�V�����̓����Ă��鐔
extern int Diamond_act_index2;//�j�󃂁[�V�����̓����Ă��鐔
extern int Diamond_motion_index;//���郂�[�V�����ԍ����i�[����ϐ�
extern int Diamond_motion_index2;//�j�󃂁[�V�����ԍ����i�[����ϐ�

