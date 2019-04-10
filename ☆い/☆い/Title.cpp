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

namespace Title
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iHo.ImageCreate("./data/image/other/Title/ho.bmp");
		iShi.ImageCreate("./data/image/other/Title/shi.bmp");
		iBoshi.ImageCreate("./data/image/other/Title/boshi.bmp");
		iStart.ImageCreate("./data/image/other/Title/word.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName("�^�C�g���^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�^�C�g�����\�[�X");
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");
		/*�^�X�N�̐���*/

		Add<BeamGenerator::Obj>();
		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = rand() % 3;
		fg->Bridge(1, &Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.423f), &iColor);
		/*�f�[�^�̏�����*/
		rHo = Rec(630, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rShi = Rec(Rec::Win.r*0.5f, Rec::Win.b * 0.6f, 16 * 18, 16 * 18);
		rBoshi = Rec(1290, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rStart = Rec(0.f, 0.f, 0.f, 0.f);
		fZoom = 1.8f;
		fStartImgSrcY = 0.f;

		aAnimator1.SetAnim(AnimHo, 0);
		aAnimator2.SetAnim(AnimShiBoshi, 0);

		Rec::Zoom(fZoom);
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			res->wsBGM.PlayL();
			res->wsBGM1.PlayL();
			res->wsBGM1.Pause();
			res->wsBGM2.PlayL();
			res->wsBGM2.Pause();
		}
		//Add<MeteoGenerator::Obj>();
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		sg->Bridge(1, &iChange, &Point(1290.f, Rec::Win.b * 0.43f));
		if (auto st = Find<Star::Obj>("���^�X�N"))
		{
			st->rStar.Scaling(100 * 1.2f, 100 * 1.2f);
		}
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove("�^�C�g�����\�[�X");
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		auto pad = JoyPad::GetState(0);
		auto kb = KB::GetState();

		auto bm = Find<Beam::Obj>("�r�[���^�X�N");
		if (!bm) return;

		bShineFlag = false;
		if (bm->vSpd != Vector2::right * 20.f && bm->rHitBase.GetPosX() <= Rec::Win.l + 500.f)
		{
			bShineFlag = true;
			Pause("�r�[���^�X�N");
		}

		if (bShineFlag)
		{
			Rec::Zoom(fZoom);
			fZoom = Max(fZoom - 0.03f, 1.f);

			aAnimator1.Update();
			aAnimator2.Update();

			//if (fZoom > 1.f) return;
			if (Find<Cursor::Obj>("�J�[�\���^�X�N")) return;

			auto cs = Add<Cursor::Obj>();
			cs->rCursorBase.SetPos(&Point(Rec::Win.r * 0.25f, Rec::Win.b * 0.75f));
			rStart = Rec(Rec::Win.r*0.5f, Rec::Win.b * 0.9f, 16 * 30, 16 * 5);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		//if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		//{
		//	Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		//}
		if (auto s = RB::Find<Title::RS>("�^�C�g�����\�[�X"))
		{
			Frec src(64.f * aAnimator1.GetSrcX(), 0, 64.f, 64.f);
			rHo.Draw(&s->iHo, &src, true);

			src = Frec(64.f * aAnimator2.GetSrcX(), 0, 64.f, 64.f);
			rShi.Draw(&s->iShi, &src, true);

			rBoshi.Draw(&s->iBoshi, &src, true);

			src = Frec(16.f * 0, 16.f * fStartImgSrcY, 16.f * 5, 16.f);
			rStart.Draw(&s->iStart, &src, true);
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
