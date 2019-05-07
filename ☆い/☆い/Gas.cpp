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
		SetName("�K�X�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/

		iGasColor = 0;

		aAnim.SetAnim(AnimGasW, 0);
		aAnim.SetAnim(AnimGasB, 0);
		aAnim.SetAnim(AnimGasY, 0);
		aAnim.SetAnim(AnimGasP, 0);
		aAnim.Play();
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{

	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			if (iGasColor == 'W')
			{
				Frec src(16.f * (aAnim.GetSrcX() + 87), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iGasColor == 'B')
			{

				Frec src(16.f * (aAnim.GetSrcX() + 89), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iGasColor == 'Y')
			{

				Frec src(16.f * (aAnim.GetSrcX() + 91), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
			else if (iGasColor == 'P')
			{

				Frec src(16.f * (aAnim.GetSrcX() + 93), 0.f, 16.f, 16.f);
				rGas.Draw(&stageRes->iStageImg, &src, true);
			}
		}

	}
	void AnimGasW(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 1) % 2;
		}
		++*bFrame;
	}
	void AnimGasP(byte * const bFrame, byte * const bSrcX, byte * const bSrcY)
	{
		*bSrcY = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			*bSrcX = (*bSrcX + 2) % 8;
		}
		++*bFrame;
	}
}
