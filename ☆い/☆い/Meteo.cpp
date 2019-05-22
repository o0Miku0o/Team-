#include "Meteo.h"
#include "Beam.h"
#include "Fragment.h"
#include "StageManager.h"
#include "MeteoGenerator.h"
#include "FadeInOut.h"

namespace Meteo
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
		rMeteo = Rec(950, -300, 16 * 18, 16 * 18);
		cMeteoHitBase = Circle(&rMeteo.GetPos(), rMeteo.GetW()*0.4f);
		iMeteoNum = 1;
		vSpd = Vector2(0.f, 0.f);
		//vSpd.SetVec(0.f, 0.f);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (auto beam = Find<Beam::Obj>(Beam::caTaskName))
		{
			Obj::BeamCheckhit(beam);
		}
		auto vFgm = FindAll <Fragment::Obj>(Fragment::caTaskName);
		if (vFgm.size())
		{
			for (auto &vf : vFgm)
			{
				FragmentCheckhit(vf);
			}
		}
		//if (auto fade = Find<FadeInOut::Obj>("�t�F�C�h�C���A�E�g�^�X�N")) {
		//	rMeteo.Move(&Vector2(0.f,0.f));
		//}
		//else {
			rMeteo.Move(&vSpd);
		//}
		rMeteo.SetDeg(rMeteo.GetDeg() + 2);
		cMeteoHitBase.SetPos(&rMeteo.GetPos());
		float fPosY = vSpd.GetY();
		if (fPosY > 0)
		{
			if (rMeteo.GetPosY() >= Rec::Win.b * 0.5f)
			{
				if (iMeteoNum)
				{
					auto met = Add<MeteoGenerator::Obj>();
					met->Bridge(1, &pInitPos/*Point(rMeteo.GetPos().x, Rec::Win.t - 300)*/, &vSpd);
					--iMeteoNum;
				}
			}
		}
		else if (fPosY < 0)
		{

			if (rMeteo.GetPosY() <= Rec::Win.b * 0.5f)
			{
				if (iMeteoNum)
				{
					auto met = Add<MeteoGenerator::Obj>();
					met->Bridge(1, &pInitPos/*Point(rMeteo.GetPos().x, Rec::Win.b + 300)*/, &vSpd);
					--iMeteoNum;
				}
			}
		}
		if (rMeteo.GetPosY() > Rec::Win.b + 300.f)
		{
			Remove(this);
		}
		if (rMeteo.GetPosY() < Rec::Win.t - 300.f)
		{
			Remove(this);
		}
	}

	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16 * 4, 16, 16, 16);
			rMeteo.Draw(&res->iStageImg, &src, true);
		}
		//cMeteoHitBase.Draw();
	}
	void Obj::BeamCheckhit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBmHit;
		cBmHit.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBmHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cMeteoHitBase.CheckHit(&cBmHit))
		{
			Remove(bm);
		}
	}
	void Obj::FragmentCheckhit(TaskBase* fr)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fr;
		Circle cFrHit;
		cFrHit.SetRadius(oFragment->rFragment.GetW()*0.5f);
		cFrHit.SetPos(&oFragment->rFragment.GetPos());
		if (cMeteoHitBase.CheckHit(&cFrHit))
		{
			oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;
		}
	}
}
