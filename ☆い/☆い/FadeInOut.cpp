#include "FadeInOut.h"
#include "StageManager.h"

namespace FadeInOut
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{

	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{

	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName("�t�F�C�h�C���A�E�g�^�X�N");
		/*���\�[�X����*/
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		SetRenderPriority(1.f);

		fSize = 0.f;

		rec[0] = Rec(Rec::Win.r, Rec::Win.t, fSize, fSize, 45.f);
		rec[1] = Rec(Rec::Win.l, Rec::Win.t, fSize, fSize, 135.f);
		rec[2] = Rec(Rec::Win.r, Rec::Win.b, fSize, fSize, 225.f);
		rec[3] = Rec(Rec::Win.l, Rec::Win.b, fSize, fSize, 315.f);

		bIsIn = true;
		bActive = false;
		fSizeValue = 0.f;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		//EndPositon<FadeInOut::Obj>("�t�F�C�h�C���A�E�g�^�X�N");
		//fsize��2120�ɂȂ����u�Ԕw�i���S�����߂�
		if (!bActive) {
			if (bIsIn) {
				fSizeValue = 16.f;
				fSize = 0.f;
			}
			else {
				fSizeValue = -16.f;
				fSize = 2120.f;
			}
			bActive = true;
		}
		else {
			if (!bIsIn) {
				if (fSize < 0) {
					Remove(this);
				}
			}
		}

		fSize += fSizeValue;
		for (int i = 0; i < 4; ++i)
			rec[i].Scaling(fSize, fSize);
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X")) {
			for (int i = 0; i < 4; ++i)
				rec[i].Draw(&res->iStageImg, &Frec(16, 0, 16, 16), false);
		}
	}
}
