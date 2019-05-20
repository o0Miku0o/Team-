#include "Eff1.h"

namespace Eff1
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iEff1Img.ImageCreate("./data/image/other/Effect/eff1.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iEff1Img.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName("�G�t�F�N�g�P�^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�G�t�F�N�g���\�[�X");
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		SetRenderPriority(0.3f);

		rEffBase = Rec(0.f, 0.f, 16.f, 16.f);
		fSpdX = 0;
		fSpdY = 0;
		fAngle = 0;
		fAddAngle = 0;
		bLife = 0;
		bLifeMax = 30;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		if (!Find<Obj>("�G�t�F�N�g�P�^�X�N"))
		{
			RB::Remove("�G�t�F�N�g���\�[�X");
		}
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (bLife >= bLifeMax)
		{
			Remove(this);
			return;
		}
		++bLife;
		Vector2 vSpd(fSpdX, fSpdY);
		rEffBase.Move(&vSpd);
		rEffBase.SetDeg(fAngle);
		fAngle = ModAngle(fAngle + fAddAngle);
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<RS>("�G�t�F�N�g���\�[�X"))
		{
			Frec src(0.f, 16.f * tType, 16.f, 16.f);
			rEffBase.Draw(&res->iEff1Img, &src, true);
		}
	}

	void Obj::SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const Type ctType, const fix cfAngle, const fix cfAddAngle)
	{
		rEffBase = *crpcEffBase;
		fSpdX = cvpcSpd->GetX();
		fSpdY = cvpcSpd->GetY();
		fAngle = cfAngle;
		fAddAngle = cfAddAngle;
		bLife = 0;
		bLifeMax = cbLifeMax;
		tType = ctType;
	}
}
