#include "Title.h"
#include "StageManager.h"
#include "Cursor.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "FragmentGenerator.h"
#include "Fragment.h"
#include "MeteoGenerator.h"
#include "StarGenerator.h"
#include "Star.h"
#include "Gas.h"

namespace Title
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iHo.ImageCreate("./data/image/other/Title/ho.bmp");
		iHoOverride.ImageCreate("./data/image/other/Title/ho2.bmp");
		iBoshi.ImageCreate("./data/image/other/Title/boshi.bmp");
		iBoshiOverride.ImageCreate("./data/image/other/Title/boshi2.bmp");
		iStart.ImageCreate("./data/image/other/Title/word.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iHo.Release();
		iHoOverride.Release();
		iBoshi.Release();
		iBoshiOverride.Release();
		iStart.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);
		/*���\�[�X����*/
		RB::Add<RS>(caResName);
		RB::Add<StageManager::RS>(StageManager::caResName);
		/*�^�X�N�̐���*/
		CreateBeam();

		CreateFragment();

		CreateStar();

		/*�f�[�^�̏�����*/
		LogoInit();

		MeteoInit();

		ButtonInit();

		OtherInit();

		PlayBgm();

		//em.Open("./data/event/ev1.txt");
		//em.Color(RGB(0, 255, 0));
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();

		auto bm = Find<Beam::Obj>(Beam::caTaskName);
		if (!bm) return;

		bShineFlag = false;
		if (bm->vSpd != Vector2::right * 20.f && bm->rHitBase.GetPosX() <= Rec::Win.l + 600.f)
		{
			bShineFlag = true;
			Pause(Beam::caTaskName);
		}

		if (bShineFlag)
		{
			Rec::Zoom(fZoom);
			fZoom = Max(fZoom - 0.03f, 1.f);

			if (fZoom > 1.f) return;

			LogoUpdate();

			MeteoUpdate();

			if (Find<Cursor::Obj>(Cursor::caTaskName)) return;

			CreateCursor();

			ButtonResize();

			Add<Gas::Obj>();

		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		//if (em.Run() == EventMsg::Result::RES_EOF)
		//{
		//	em.Clear();
		//}
		//em.DrawAscii(Point(150, 150), 6 * 10, 24 * 10);

		DrawMeteo();

		if (auto s = RB::Find<Title::RS>(caResName))
		{
			Frec src(0.f, 0.f, 64.f, 64.f);
			DrawLogo(s, &src);

			src = Frec(16.f * 0, 16.f * fStartImgSrcY, 16.f * 5, 16.f);
			DrawButton(s, &src);
		}
	}
	/*���S�̏�����*/
	void Obj::LogoInit()
	{
		rHo = Rec(730, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rBoshi = Rec(1190, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
	}
	/*�X�^�[�g�{�^���̏�����*/
	void Obj::ButtonInit()
	{
		rStart = Rec(0.f, 0.f, 0.f, 0.f);
	}
	/*���e�I�̏�����*/
	void Obj::MeteoInit()
	{
		fMScale = rand() % (16 * 4 + 1) + 16.f * 14.f;
		rMeteo = Rec(Rec::Win.r * 0.5f, -300.f, fMScale, fMScale);
		fMSpdBase = 20.f;
		vMSpd.SetVec(rMeteo.GetDeg(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.f)), fMSpdBase);
	}
	void Obj::OtherInit()
	{
		fZoom = 1.8f;
		fStartImgSrcY = 0.f;
		bAlpha = 5;
		cAddAlpha = 5;

		Rec::Zoom(fZoom);
	}
	/*���S�̍X�V*/
	void Obj::LogoUpdate()
	{
		if (bAlpha <= 0 || bAlpha >= 255)
		{
			cAddAlpha = -cAddAlpha;
		}
		bAlpha += cAddAlpha;
	}
	void Obj::ButtonResize()
	{
		rStart = Rec(Rec::Win.r*0.5f, Rec::Win.b * 0.9f, 16 * 30, 16 * 5);
	}
	/*���e�I�̍X�V*/
	void Obj::MeteoUpdate()
	{
		rMeteo.SetDeg(rMeteo.GetDeg() + 2.f);

		if (!fMSpdBase)
		{
			const fix fRandAngle = rand() % 360;
			rMeteo.SetPos(&Point(cos(DtoR(fRandAngle)) * 1000.f + Rec::Win.r * 0.5f, sin(DtoR(fRandAngle)) * 1000.f + Rec::Win.b * 0.5f));
			fMSpdBase = 20.f;
			vMSpd.SetVec(rMeteo.GetDeg(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f)), fMSpdBase);
			fMScale = rand() % (16 * 4 + 1) + 16.f * 18.f;
			rMeteo.Scaling(fMScale, fMScale);
		}
		vMSpd.SetVec(vMSpd.GetDeg(), fMSpdBase);
		rMeteo.Move(&vMSpd);
		rMeteo.Scaling(fMScale, fMScale);
		fMScale = Max(fMScale - 4.f, 0.f);
		fMSpdBase = Max(fMSpdBase - 0.15f, 0.f);
	}
	/*���e�I�̕`��*/
	void Obj::DrawMeteo()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * 4, 16.f * 1, 16.f, 16.f);
			rMeteo.Draw(&res->iStageImg, &src, true);
		}
	}
	/*���S�̕`��*/
	void Obj::DrawLogo(RS * const rpRes, const Frec * const fpSrc)
	{
		rHo.Draw(&rpRes->iHo, fpSrc);
		rHo.DrawAlpha(&rpRes->iHoOverride, fpSrc, bAlpha);

		rBoshi.Draw(&rpRes->iBoshi, fpSrc);
		rBoshi.DrawAlpha(&rpRes->iBoshiOverride, fpSrc, bAlpha);
	}
	/*�{�^���̕`��*/
	void Obj::DrawButton(RS * const rpRes, const Frec * const fpSrc)
	{
		rStart.Draw(&rpRes->iStart, fpSrc);
	}
	/*�r�[������*/
	void Obj::CreateBeam()
	{
		Add<BeamGenerator::Obj>();
	}
	/*���А���*/
	void Obj::CreateFragment()
	{
		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = rand() % 3;
		fg->Bridge(1, &Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.423f), &iColor);
	}
	/*�J�[�\���̐���*/
	void Obj::CreateCursor()
	{
		auto cs = Add<Cursor::Obj>();
		//cs->pPos = Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.75f);
		cs->rCursorBase.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.75f));
	}
	/*���̐���*/
	void Obj::CreateStar()
	{
		auto sg = Add<StarGenerator::Obj>();
		sg->Bridge(1, { 24 }, { 46 }, { Point(1190.f, Rec::Win.b * 0.43f) });
		//sg->Bridge(1, &iChange, &Point(1190.f, Rec::Win.b * 0.43f));
		if (auto st = Find<Star::Obj>(Star::caTaskName))
		{
			st->rStar.Scaling(100 * 1.2f, 100 * 1.2f);
		}
	}
	/*BGM�̍Đ�*/
	void Obj::PlayBgm()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsBGM.PlayL();
		}
	}
	/*�A�j���[�V����*/
	void AnimHo(byte * const bFrame, byte * const bAnim, byte * const bAnim2)
	{
		*bAnim2 = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			/**/
			*bAnim = (*bAnim + 1) % 4;
			/*/
			*bAnim = ((*bAnim - 1) + 4) % 4;
			/**/
		}
		++*bFrame;
	}
	/*�A�j���[�V����*/
	void AnimShiBoshi(byte * const bFrame, byte * const bAnim, byte * const bAnim2)
	{
		*bAnim2 = 0;
		if (*bFrame == 10)
		{
			*bFrame = 0;
			/**/
			*bAnim = (*bAnim + 1) % 4;
			/*/
			*bAnim = ((*bAnim - 1) + 4) % 4;
			/**/
		}
		++*bFrame;
	}
}