#include "JecLogo.h"
#include "GameInit.h"

namespace JecLogo
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iLogoImg.ImageCreate("./data/image/other/���{�d�q���S.bmp");
		iBlackImg.ImageCreate("./data/image/other/Black.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iLogoImg.Release();
		iBlackImg.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);
		/*���\�[�X����*/
		RB::Add<RS>(caResName);
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rLogoBase.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f));
		rLogoBase.Scaling(Rec::Win.r, Rec::Win.b);
		fAlpha = 255;
		iWaitCnt = 80;
		bRev = false;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (!bRev)
		{
			if (fAlpha > 0)
			{
				fAlpha -= 12.75f;//25.5;
			}
			else if (iWaitCnt > 0)
			{
				--iWaitCnt;
			}
			else bRev = true;
		}
		else
		{
			if (fAlpha < 255)
			{
				fAlpha += 12.75f;//25.5;
			}
			else
			{
				Remove(this);
				Add<GameInit::Obj>();
			}
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<RS>(caResName))
		{
			rLogoBase.Draw(&res->iLogoImg);
			rLogoBase.DrawAlpha(&res->iBlackImg, (byte)fAlpha);
		}
	}
}
