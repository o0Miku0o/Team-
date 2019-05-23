#include "Gas.h"
#include "Title.h"
#include "StageManager.h"

//�f�ނ�4(���)�~2(�A�j���[�V��������)
//�ʒu�͑���87����94
//�����_���ŏo���悤�ɂ�����
//�^�C�g�����X�e�[�W�Ŏg����悤�ɂ�����
//�O�}�搶����̂����t�u�Ō�̕��ł������ȁv
namespace Gas
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
		SetName(caTaskName);
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		bAlpha = 50;
		fMove = -3.0f;
		aAnim.SetAnim(AnimGasW, 0);
		aAnim.SetAnim(AnimGasB, 0);
		aAnim.SetAnim(AnimGasY, 0);
		aAnim.SetAnim(AnimGasP, 0);
		aAnim.Play();
		iGNum = sizeof(rGas) / sizeof(rGas[0]);

		for (int i = 0; i < iGNum; ++i)
		{
			const float fRandPosY = float(rand() % int(Rec::Win.b));
			const float fRandPosX = float(rand() % int(Rec::Win.r));
			gGasColor[i] = GasColor(rand() % 4);

			rGas[i] = Rec(fRandPosX, fRandPosY, 16.0f * 60.0f, 16.0f * 60.0f);
		}
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		for (int i = 0; i < iGNum; ++i)
		{
			if (rGas[i].GetPosX() + rGas[i].GetW() <= 0.0f)
			{
				const float fRandPosY = float(rand() % int(Rec::Win.b));
				rGas[i].SetPos(&Point(Rec::Win.r + rGas[i].GetW(), fRandPosY));
				gGasColor[i] = GasColor(rand() % 4);
			}
			rGas[i].Move(&Vector2(fMove, 0.0f));
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			/*Frec src(16.f * (aAnim.GetSrcX() + 87), 0.f, 16.f, 16.f);
			rGas.DrawAlpha(&stageRes->iStageImg, &src, bAlpha);*/
			for (int i = 0; i < iGNum; ++i)
			{
				if (gGasColor[i] == White)
				{
					Frec src(16.f * aAnim.GetSrcX() + 16 * 87, 0.f, 16.f, 16.f);
					rGas[i].DrawAlpha(&stageRes->iStageImg, &src, bAlpha);
				}
				else if (gGasColor[i] == Blue)
				{

					Frec src(16.f * aAnim.GetSrcX() + 16 * 89, 0.f, 16.f, 16.f);
					rGas[i].DrawAlpha(&stageRes->iStageImg, &src, bAlpha);
				}
				else if (gGasColor[i] == Yellow)
				{

					Frec src(16.f * aAnim.GetSrcX() + 16 * 91, 0.f, 16.f, 16.f);
					rGas[i].DrawAlpha(&stageRes->iStageImg, &src, bAlpha);
				}
				else if (gGasColor[i] == Purple)
				{

					Frec src(16.f * aAnim.GetSrcX() + 16 * 93, 0.f, 16.f, 16.f);
					rGas[i].DrawAlpha(&stageRes->iStageImg, &src, bAlpha);
				}
			}
		}

	}
	void AnimGasW(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 30)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 30)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 30)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasP(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 30)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
}
