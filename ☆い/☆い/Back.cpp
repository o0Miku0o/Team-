#include "Back.h"
#include "StageManager.h"

namespace Back
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
		SetName("�w�i�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		for (auto &ap : pBackStar)
		{
			ap.SetPos(&Point(float(rand() % int(Rec::Win.r)), float(rand() % int(Rec::Win.b))));
		}
		rBackBase = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);
		bSSLife = 0;
		bSSLifeMax = 60;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		lShootingStar.Move(20.f);
		if (bSSLife >= bSSLifeMax)
		{
			bSSLife = 0;
			lShootingStar.SetLen(0.f);
			lShootingStar.SetPos(&Point(float(rand() % int(Rec::Win.r)), float(rand() % int(Rec::Win.b))));
			lShootingStar.SetDeg(float(rand() % 360));
		}
		else if(bSSLife < byte(bSSLifeMax * 0.5f))
		{
			lShootingStar.SetLen(lShootingStar.GetLen() + 10.f);
		}
		else
		{
			lShootingStar.SetLen(lShootingStar.GetLen() - 10.f);
		}
		++bSSLife;
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			rBackBase.Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		}
		for (auto &ap : pBackStar)
		{
			if (rand() % 91 == 1)
			{
				const byte bC = (byte)rand() % 206 + 50;
				ap.SetColor(RGB(bC, bC, bC));
			}
			ap.Draw();
		}
		if (lShootingStar.GetLen() > 0.f)
		{
			lShootingStar.Draw();
		}
	}
}
