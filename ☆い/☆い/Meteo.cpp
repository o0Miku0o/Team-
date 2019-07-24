#include "Meteo.h"
#include "Beam.h"
#include "Fragment.h"
#include "StageManager.h"
#include "MeteoGenerator.h"
#include "FadeInOut.h"
#include "Eff1.h"

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
		effsp = Eff1::EffectCreater::SP(new Eff1::EffectCreater("./data/effect/ef_remove_frgY.txt"));
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
			/*�G�t�F�N�g���o*/
			static std::string fileName[3] = { "y_frg","r_frg","b_frg" };
			//Eff1::Create(fileName[oFragment->iColor], &oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
			effsp->_set_chip_type(fileName[oFragment->iColor]);
			effsp->run(oFragment->rFragment.GetPos(), oFragment->rFragment.GetDeg());
			/*byte loopmax = 31;
			for (byte b = 0; b < loopmax; ++b)
			{
				auto ef1 = Add<Eff1::Obj>();
				const fix fAng = ModAngle(360.f/loopmax*b);
				Rec rEf(oFragment->rFragment.GetPosX(), oFragment->rFragment.GetPosY(), 5, 5);//const���Ȃ��Ă�OK
				Vector2 vSpd(cos(DtoR(fAng)) * 10, sin(DtoR(fAng)) * 10);
				ef1->SetParam(&rEf, &vSpd, 15, Eff1::Type::TYPE_Y_FRG, fAng);
			}*/
			oFragment->rFragment.SetDeg(rMeteo.GetDeg(&oFragment->rFragment));
			//oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//oFragment->bMoveActive = false;
		}
	}
}
