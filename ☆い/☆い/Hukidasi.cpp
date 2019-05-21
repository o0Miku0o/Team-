#include "Hukidasi.h"
#include "StageManager.h"
#include "StagePicture.h"
#include "StarGenerator.h"

namespace Hukidasi
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iTextImg.ImageCreate("./data/image/other/stagelogo.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iTextImg.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName("�����o���^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�����o�����\�[�X");
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		faWidth[0] = 16.f * 4;
		faWidth[1] = 16.f * 6;
		faWidth[2] = 16.f * 8;
		faWidth[3] = 16.f * 6;
		faWidth[4] = 16.f * 7;

		rTextBox.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * (0.75f * 0.75f) + 38.f));
		fAddScale = 0.f;
		fWidthMax = 1800.f;
		fHeightMax = 400.f;
		//constexpr float fScaleWMax = 1800.f;
		//constexpr float fScaleHMax = 400.f;
		bSetPictureCount = 0;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove("�����o�����\�[�X");
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		Resize();
		auto sp = Find<StagePicture::Obj>("�X�e�[�W�s�N�`���[�^�X�N");
		if (rHukidasi.GetW() >= fWidthMax && rHukidasi.GetH() >= fHeightMax)
		{
			if (!sp)
			{
				const float fHalfWidth = Rec::Win.r * 0.5f;
				const float fHalfHeight = Rec::Win.b * 0.5f;
				const float fQuarterWidth = fHalfWidth * 0.5f;
				const float fQuarterHeight = fHalfHeight * 0.5f;
				constexpr float cfDist = 30.f;
				const Point pPosArr[3] =
				{
					Point(fQuarterWidth, fHalfHeight + fQuarterHeight - cfDist),
					Point(fHalfWidth, fHalfHeight + fQuarterHeight - cfDist),
					Point(fHalfWidth + fQuarterWidth, fHalfHeight + fQuarterHeight - cfDist)
				};
				constexpr float cfPicWidth = 1920.f * (0.125f * 1.5f);
				constexpr float cfPicHeight = 1080.f * (0.125f * 1.5f);

				for (byte b = 0; b < 3; ++b)
				{
					SetStagePicture(sGroup * 3 + b + 1, &Frec(pPosArr[b].x, pPosArr[b].y, cfPicWidth, cfPicHeight));
				}

				//auto sg = Add<StarGenerator::Obj>();
				//constexpr int iNum = 9;
				//vector<int> viChange;
				//vector<int> viEffect;
				//vector<Frec> viRec;				
				//sg->Bridge(iNum, { 25, 25, 25, 25, 25, 25, 25, 25, 25 }, {}, vector<Frec>({}));

				//if (pGroup == PictureGroup::GROUP_UP)
				//{
				//	for (byte b = 0; b < 3; ++b)
				//	{
				//		SetStagePicture(sGroup * 3 + b + 1, &Frec(pPosArr[pGroup][b].x, pPosArr[pGroup][b].y, fPicWidth, fPicHeight));
				//	}
				//}
				//else
				//{
				//	for (byte b = 0; b < 3; ++b)
				//	{
				//		SetStagePicture(sGroup * 3 + b + 1, &Frec(pPosArr[1][b].x, pPosArr[1][b].y, fPicWidth, fPicHeight));
				//	}
				//}

				//SetStagePicture(1, &Frec(fHalfWidth, fHalfHeight, 100.f, 100.f));

				//sp = Add<StagePicture::Obj>();
				//sp->LoadImg(1);
				//sp->SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f));
				//sp->SetSize(100.f, 100.f);
			}
		}
		else
		{
			if (sp)
			{
				RemoveAll("�X�e�[�W�s�N�`���[�^�X�N");
				//Remove(sp);
			}
			bSetPictureCount = 0;
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (!rHukidasi.SizeZero())
		{
			if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
			{
				Frec src(16.f * 59, 16.f * 0, 16.f, 16.f);
				rHukidasi.Draw(&res->iStageImg, &src, false);
			}
		}
		if (!rHukidasi.GetH()) rHukidasi.Draw();
		if (rHukidasi.GetH() >= fHeightMax)
		{
			if (auto res = RB::Find<Hukidasi::RS>("�����o�����\�[�X"))
			{
				Frec src(0.f, 16.f * sGroup, faWidth[sGroup], 16.f);
				rTextBox.Scaling(faWidth[sGroup] * 4.f, 16.f * 4.f);
				rTextBox.Draw(&res->iTextImg, &src, false);
			}
		}
	}
	/*�����o���̃T�C�Y�ύX*/
	void Obj::Resize()
	{
		/*���݂̃T�C�Y*/
		const float fScaleW = rHukidasi.GetW();
		const float fScaleH = rHukidasi.GetH();
		/*�e������*/
		const float fAddW = (fAddScale < 0.f && fScaleH > 0.f) ? 0.f : fAddScale;
		const float fAddH = (fAddScale > 0.f && fScaleW < fWidthMax) ? 0.f : fAddScale;
		/*�T�C�Y�Ƒ����ʂ���T�C�Y�ύX*/
		const float fResizeW = Min(Max(fScaleW + fAddW, 0.f), fWidthMax);
		const float fResizeH = Min(Max(fScaleH + fAddH, 0.f), fHeightMax);
		rHukidasi.Scaling(fResizeW, fResizeH);
	}
	/*�T�C�Y�̕ω��ʂ�ݒ�*/
	void Obj::SetAddScale(const float afAddScale)
	{
		fAddScale = afAddScale;
	}
	/*�T�C�Y�̍ő�l��ݒ�*/
	void Obj::SetScaleMax(const float afWMax, const float afHMax)
	{
		fWidthMax = afWMax;
		fHeightMax = afHMax;
	}
	/*���W��ݒ�*/
	void Obj::SetPos(const Point * const appPos)
	{
		rHukidasi.SetPos(appPos);
	}
	/*�\������X�e�[�W�̐ݒ�*/
	void Obj::SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize)
	{
		if (bSetPictureCount > 2) return;
		auto sp = Add<StagePicture::Obj>();
		sp->LoadImg(auiStageNumber);
		sp->SetPos(&Point(apfrPosSize->l, apfrPosSize->t));
		sp->SetSize(apfrPosSize->r, apfrPosSize->b);
		++bSetPictureCount;
	}
	/*�X�e�[�W�̃O���[�v�̐ݒ�*/
	void Obj::SetStageGroup(const StageGroup asStageGroup)
	{
		sGroup = asStageGroup;
	}
}
