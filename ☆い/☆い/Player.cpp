#include "Player.h"
#include "StageManager.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "Fragment.h"
#include "FadeInOut.h"

//#include "Rail.h"

namespace Player
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
		//Add<Rail::Obj>();
		/*�f�[�^�̏�����*/
		SetRenderPriority(0.2f);

		rBase = Rec(Rec::Win.l + 100.f, Rec::Win.b * 0.5f, 16 * 8.f, 16 * 8.f, 180);
		rImgBase = rBase;
		pStandardPoint = Point(Rec::Win.r - 500.f, Rec::Win.b * 0.5f);
		fSPDist = rBase.GetDist(&pStandardPoint);
		fSPAngle = (float)rBase.GetDeg(&pStandardPoint) + 180;
		fPAngle = fSPAngle;
		lGuideLine.SetLen(2000.f);
		lGuideLine.SetColor(130, 130, 255);
		lGuideLineFgm.SetColor(255, 130, 130);
		bIsReplay = false;

		//ReplayLoad("./data/demo/replay.txt");
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		Rep::SaveFile("./data/demo/replay.txt");
		//ReplayRelease();
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
		{
			/*�t�F�C�h�C���A�E�g���������Ă��Ȃ��Ȃ�I��*/
			if (!fade->IsComplete()) return;
		}
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();
		/*�r�[���𐶐�*/
		BeamCreateFromPad(pad);
		BeamCreateFromKeyBoard(kb);

		if(bIsReplay) BeamCreateFromReplay();
		else          Rep::Push(pad->Down(JOY_BUTTON6) || kb->Down(VK_RIGHT));

		float fSpdY = 0;
		float fPadSpd = 0;
		float fRepSpd = 0.f;
		if (!Find<Beam::Obj>(Beam::caTaskName))
		{
			/*���͂���X�s�[�h���擾*/
			fSpdY = GetSpdFromKeyBoard(kb);
			fPadSpd = GetSpdFromPad(pad);

			float fAng = 0.5f;

			ShotAngleFromPad(pad, fAng);
			ShotAngleFromKeyBoard(kb, fAng);
		}

		if (bIsReplay) fRepSpd = GetSpdFromReplay();
		else                     Rep::Push(fSpdY);

		fSpdY = ((fPadSpd) ? fPadSpd : fSpdY);
		fSpdY = ((fRepSpd) ? fRepSpd : fSpdY);

		float fPosX = rBase.GetPosX();
		float fAfterPosY = GetAfterPosY(fSpdY);
		pPos = Point(fPosX, fAfterPosY);
		rBase.SetPos(&pPos);

		if (bIsReplay) ShotAngleFromReplay();
		else           Rep::Push(fPAngle);
		/*�K�C�h���C��*/
		GuidLine();
		rBase.SetDeg(fPAngle);
		//if (fSPAngle >= 189.f)
		//{
		//	fSrcX = 6.f;
		//	rImgBase.SetPos(&rBase.GetPos());
		//	rImgBase.SetDeg(rBase.GetDeg() - 45.f);
		//}
		//else if (fSPAngle <= 171.f)
		//{
		//	fSrcX = 8.f;
		//	rImgBase.SetPos(&rBase.GetPos());
		//	rImgBase.SetDeg(rBase.GetDeg() + 45.f);
		//}
		//else
		//{
			fSrcX = 10.f;
			rImgBase.SetPos(&Point(cos(DtoR(rBase.GetDeg() + 90)) * 50.f + rBase.GetPosX(), sin(DtoR(rBase.GetDeg() + 90)) * 50.f + rBase.GetPosY()));
			rImgBase.SetDeg(rBase.GetDeg());
		//}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		lGuideLine.Draw();
		if (lGuideLineFgm.GetLen())
		{
			lGuideLineFgm.Draw(PS_DASH);
		}
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * fSrcX, 16.f, 16.f, 16.f);
			rImgBase.Draw(&res->iStageImg, &src);
		}
	}
	/*�p�b�h���͂���r�[���𐶐�*/
	void Obj::BeamCreateFromPad(std::shared_ptr<JoyPad> &apPad)
	{
		if (apPad->Down(JOY_BUTTON6))
		{
			if (!Find<Beam::Obj>(Beam::caTaskName))
			{
				auto bm = Add<BeamGenerator::Obj>();
				if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
				{
					res->wsTest4.Play();
				}
			}
		}
	}
	/*�L�[�{�[�h���͂���r�[���𐶐�*/
	void Obj::BeamCreateFromKeyBoard(std::shared_ptr<KB> &apKB)
	{
		if (apKB->Down(VK_RIGHT))
		{
			if (!Find<Beam::Obj>(Beam::caTaskName))
			{
				auto bm = Add<BeamGenerator::Obj>();
			}
		}
	}
	void Obj::BeamCreateFromReplay()
	{
		if (!bIsReplay) return;
		auto d = Rep::Read();
		if (d == DBL_MAX)
		{
			ReplaySeekZero();
			d = Rep::Read();
		}
		if (!d) return;
		if (Find<Beam::Obj>(Beam::caTaskName)) return;
		Add<BeamGenerator::Obj>();
	}
	/*�ړ����x����ړ���̍��W���擾*/
	const float Obj::GetAfterPosY(const float afSpdY)
	{
		const float fPosY = rBase.GetPosY();
		float fAfterPosY = fPosY + afSpdY;
		constexpr float cfWinRecDist = 100.f;
		constexpr float cfPlayerPosMin = 0.f + cfWinRecDist;
		constexpr float cfPlayerPosMax = 1080.f - cfWinRecDist;
		if (fAfterPosY >= cfPlayerPosMax) fAfterPosY = cfPlayerPosMax;
		if (fAfterPosY <= cfPlayerPosMin) fAfterPosY = cfPlayerPosMin;
		return fAfterPosY;
	}
	/*�L�[�{�[�h���͂���X�s�[�h���擾*/
	const float Obj::GetSpdFromKeyBoard(std::shared_ptr<KB> &apKB)
	{
		float fSpdY = 0.f;
		if (apKB->On('W'))
		{
			fSpdY = -5.f;
		}
		if (apKB->On('S'))
		{
			fSpdY = 5.f;
		}
		if (apKB->On(VK_LEFT))
		{
			fSpdY *= 0.5f;
		}
		return fSpdY;
	}
	/*�p�b�h���͂���X�s�[�h���擾*/
	const float Obj::GetSpdFromPad(std::shared_ptr<JoyPad> &apPad)
	{
		if (!apPad->Axis(JoyPad::Stick::STK_LEFT).GetY()) return 0.f;
		float fSpdY = apPad->Axis(JoyPad::Stick::STK_LEFT).GetY() * 5.0f;
		if (apPad->On(JOY_BUTTON5))
		{
			fSpdY *= 0.5f;
		}
		return fSpdY;
	}
	const float Obj::GetSpdFromReplay()
	{
		if (!bIsReplay) return 0;
		auto d = Rep::Read();
		if (d == DBL_MAX)
		{
			ReplaySeekZero();
			d = Rep::Read();
		}
		return (float)d;
	}
	/*�L�[�{�[�h���͂���ˌ��p�x���擾*/
	void Obj::ShotAngleFromKeyBoard(std::shared_ptr<KB> &apKB, float afAddAngle)
	{
		if (apKB->On(VK_LEFT))
		{
			afAddAngle *= 0.5f;
		}
		if (apKB->On(VK_UP))
		{
			fPAngle = Max(fPAngle - afAddAngle, rBase.GetDeg(&pStandardPoint) + 145);
		}
		if (apKB->On(VK_DOWN))
		{
			fPAngle = Min(fPAngle + afAddAngle, rBase.GetDeg(&pStandardPoint) + 215);
		}
	}
	/*�p�b�h���͂���ˌ��p�x���擾*/
	void Obj::ShotAngleFromPad(std::shared_ptr<JoyPad> &apPad, float afAddAngle)
	{
		if (apPad->On(JOY_BUTTON5))
		{
			afAddAngle *= 0.5f;
		}
		fPAngle = Clamp
		(
			fPAngle + apPad->Axis(JoyPad::Stick::STK_RIGHT).GetY() * afAddAngle,
			rBase.GetDeg(&pStandardPoint) + 145,
			rBase.GetDeg(&pStandardPoint) + 215
		);
		//fPAngle =
		//	Max
		//	(
		//		Min
		//		(
		//			fPAngle + apPad->GetAxisR().GetY() * afAddAngle,
		//			rBase.GetDeg(&pStandardPoint) + 215
		//		),
		//		rBase.GetDeg(&pStandardPoint) + 145
		//	);
	}

	void Obj::ShotAngleFromReplay()
	{
		if (!bIsReplay) return;
		auto d = Rep::Read();
		if (d == DBL_MAX)
		{
			ReplaySeekZero();
			d = Rep::Read();
		}
		fPAngle = (float)d;
	}
	/*�K�C�h���C���̏���*/
	void Obj::GuidLine()
	{
		/*�ʏ�̃K�C�h���C��*/
		lGuideLine.SetLen(2000.f);
		lGuideLineFgm.SetLen(0.f);
		lGuideLine.SetPos(&rBase.GetPos());
		lGuideLine.SetDeg(rBase.GetDeg() + 180);

		for (auto &vf : FindAll<Fragment::Obj>(Fragment::caTaskName))
		{
			/*���ЂƓ���������*/
			if (lGuideLine.CheckHit(&vf->cFragmentHitBase))
			{
				Point pIn = lGuideLine.GetPOI(&vf->cFragmentHitBase);
				lGuideLine.SetPos(&lGuideLine.GetSPos(), &pIn);
				if (!vf->bMoveActive)
				{
					/*����Ȃ�K�C�h���C��������*/
					lGuideLineFgm.SetPos(&vf->cFragmentHitBase.GetPos());
					lGuideLineFgm.SetDeg(vf->rFragment.GetDeg(&pIn) + 180);
					lGuideLineFgm.SetLen(2000.f);
				}
			}
		}
	}

	const Rep *Obj::ReplayLoad(const std::string &asRepFileName)
	{
		if (bIsReplay) return Rep::GetDataList();
		if (Rep::LoadFile(asRepFileName)) return nullptr;
		bIsReplay = true;
		return Rep::GetDataList();
	}
	void Obj::ReplayRelease()
	{
		if (!bIsReplay) return;
		Rep::Clear();
		bIsReplay = false;
	}
	void Obj::ReplaySeekZero()
	{
		if (!bIsReplay) return;
		Rep::SetPosition(0);
	}
}
