#include "Hukidasi.h"
#include "StageManager.h"
#include "StagePicture.h"

namespace Hukidasi
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
		SetName("�����o���^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�����o�����\�[�X");
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rHukidasi = Rec();
		fAddScale = 0.f;
		fWidthMax = 0.f;
		fHeightMax = 0.f;
		bIsSetPictureCount = 0;
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
				const Point pPosArr[2][3] =
				{
					{
						Point(fQuarterWidth, fQuarterHeight),
						Point(fHalfWidth, fQuarterHeight),
						Point(fHalfWidth + fQuarterWidth, fQuarterHeight)
					},
					{
						Point(fQuarterWidth, fHalfHeight + fQuarterHeight),
						Point(fHalfWidth, fHalfHeight + fQuarterHeight),
						Point(fHalfWidth + fQuarterWidth, fHalfHeight + fQuarterHeight)
					},
				};
				const float fPicWidth = 1920.f * (0.125f * 1.5f);
				const float fPicHeight = 1080.f * (0.125f * 1.5f);
				if (pGroup == PictureGroup::GROUP_UP)
				{
					for (byte b = 0; b < 3; ++b)
					{
						SetStagePicture(b + 1, &Frec(pPosArr[0][b].x, pPosArr[0][b].y, fPicWidth, fPicHeight));
					}
				}
				else
				{
					for (byte b = 0; b < 3; ++b)
					{
						SetStagePicture(b + 1, &Frec(pPosArr[1][b].x, pPosArr[1][b].y, fPicWidth, fPicHeight));
					}
				}
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
			bIsSetPictureCount = 0;
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
		if (bIsSetPictureCount > 2) return;
		auto sp = Add<StagePicture::Obj>();
		sp->LoadImg(auiStageNumber);
		sp->SetPos(&Point(apfrPosSize->l, apfrPosSize->t));
		sp->SetSize(apfrPosSize->r, apfrPosSize->b);
		++bIsSetPictureCount;
	}
	/*�X�e�[�W�̃O���[�v�̐ݒ�*/
	void Obj::SetStageGroup(const PictureGroup asStageGroup)
	{
		pGroup = asStageGroup;
	}
}
