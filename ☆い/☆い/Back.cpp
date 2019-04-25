#include "Back.h"
#include "Title.h"
#include "StageManager.h"
#include "MeteoGenerator.h"

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
		lShootingStar = Line();
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
		BackStarUpdate();

		ShootingStarUpdate();
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		BackBaseDraw();

		BackStarDraw();

		ShootingStarDraw();
	}
	/*���ꐯ�̍X�V*/
	void Obj::ShootingStarUpdate()
	{
		lShootingStar.Move(20.f);
		if (bSSLife >= bSSLifeMax)
		{
			bSSLife = 0;
			lShootingStar.SetLen(0.f);
			lShootingStar.SetPos(&Point(float(rand() % int(Rec::Win.r)), float(rand() % int(Rec::Win.b))));
			lShootingStar.SetDeg(float(rand() % 360));
		}
		else if (bSSLife < byte(bSSLifeMax * 0.5f))
		{
			lShootingStar.SetLen(lShootingStar.GetLen() + 10.f);
		}
		else
		{
			lShootingStar.SetLen(lShootingStar.GetLen() - 10.f);
		}
		++bSSLife;
	}
	/*�w�i�̐��̍X�V*/
	void Obj::BackStarUpdate()
	{
		for (auto &ap : pBackStar)
		{
			if (rand() % 91 == 1)
			{
				const byte bC = (byte)rand() % 206 + 50;
				ap.SetColor(RGB(bC, bC, bC));
			}
		}
	}
	/*�w�i�摜�̕`��*/
	void Obj::BackBaseDraw()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			rBackBase.Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		}
	}
	/*���ꐯ�̕`��*/
	void Obj::ShootingStarDraw()
	{
		if (lShootingStar.GetLen() > 0.f)
		{
			lShootingStar.Draw();
		}
	}
	/*�w�i�̐��̍X�V*/
	void Obj::BackStarDraw()
	{
		auto ti = Find<Title::Obj>("�^�C�g���^�X�N");
		for (auto &ap : pBackStar)
		{
			if (ti)
			{
				if (ti->rBoshi.CheckHit(&ap.GetPos()) || ti->rHo.CheckHit(&ap.GetPos())) continue;
			}
			ap.Draw();
		}
	}
}
