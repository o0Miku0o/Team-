#include "Title.h"
#include "StageManager.h"
#include "Cursor.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "FragmentGenerator.h"
#include "Fragment.h"

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
		int iColor = 0;
		fg->Bridge(1, &Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.428f), &iColor);
		/*�f�[�^�̏�����*/
		rHo = Rec(630, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rShi = Rec(Rec::Win.r*0.5f, Rec::Win.b * 0.6f, 16 * 18, 16 * 18);
		rBoshi = Rec(1290, Rec::Win.b * 0.5f, 16 * 18, 16 * 18);
		rStart = Rec(0.f, 0.f, 0.f, 0.f);
		fZoom = 1.8f;

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
		auto fgm = Find<Fragment::Obj>("���Ѓ^�X�N");
		if (!bm || !fgm) return;

		fgm->rFragment.Scaling(100.f * 1.7f, 100.f * 1.7f);

		byte bFlag = 0;
		if (fgm->bMoveActive)
		{
			if (fgm->rFragment.GetPosX() >= Rec::Win.r - 640.f)
			{
				++bFlag;
				fgm->rFragment.SetPos(&Point(Rec::Win.r - 640.f, fgm->rFragment.GetPosY()));
				Pause("���Ѓ^�X�N");
			}
			if (bm->rHitBase.GetPosX() <= Rec::Win.l + 500.f)
			{
				++bFlag;
				Pause("�r�[���^�X�N");
			}
		}

		if (bFlag == 2)
		{
			Rec::Zoom(fZoom);
			fZoom = Max(fZoom - 0.02f, 1.f);

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
			Frec src(160.f * aAnimator1.GetSrcX(), 0, 16 * 10, 16 * 10);
			rHo.Draw(&s->iHo, &src, true);

			src = Frec(160.f * aAnimator2.GetSrcX(), 0, 16 * 10, 16 * 10);
			rShi.Draw(&s->iShi, &src, true);

			rBoshi.Draw(&s->iBoshi, &src, true);

			src = Frec(16 * 0, 16 * 0, 16 * 5, 16);
			rStart.Draw(&s->iStart, &src, true);
		}
	}
	/*�A�j���[�V����*/
	void AnimHo(byte * const bFrame, byte * const bAnim, byte * const bAnim2)
	{
		*bAnim2 = 0;
		if (*bFrame == 15)
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
		if (*bFrame == 20)
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
