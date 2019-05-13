#include "Hukidasi.h"
#include "StageManager.h"
#include "StagePicture.h"

namespace Hukidasi
{
	/*リソースの初期化処理*/
	void RS::Init()
	{

	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{

	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName("吹き出しタスク");
		/*リソース生成*/
		RB::Add<RS>("吹き出しリソース");
		/*タスクの生成*/

		/*データの初期化*/
		rHukidasi = Rec();
		pFontPos[0] = Point(Rec::Win.r * 0.5f, Rec::Win.b * (0.25f * 0.25f));
		pFontPos[1] = Point(Rec::Win.r * 0.5f, Rec::Win.b * (0.75f * 0.75f));
		fAddScale = 0.f;
		fWidthMax = 0.f;
		fHeightMax = 0.f;
		bSetPictureCount = 0;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove("吹き出しリソース");
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		Resize();
		auto sp = Find<StagePicture::Obj>("ステージピクチャータスク");
		if (rHukidasi.GetW() >= fWidthMax && rHukidasi.GetH() >= fHeightMax)
		{
			if (!sp)
			{
				const float fHalfWidth = Rec::Win.r * 0.5f;
				const float fHalfHeight = Rec::Win.b * 0.5f;
				const float fQuarterWidth = fHalfWidth * 0.5f;
				const float fQuarterHeight = fHalfHeight * 0.5f;
				constexpr float cfDist = 30.f;
				const Point pPosArr[2][3] =
				{
					{
						Point(fQuarterWidth, fQuarterHeight - cfDist),
						Point(fHalfWidth, fQuarterHeight - cfDist),
						Point(fHalfWidth + fQuarterWidth, fQuarterHeight - cfDist)
					},
					{
						Point(fQuarterWidth, fHalfHeight + fQuarterHeight - cfDist),
						Point(fHalfWidth, fHalfHeight + fQuarterHeight - cfDist),
						Point(fHalfWidth + fQuarterWidth, fHalfHeight + fQuarterHeight - cfDist)
					},
				};
				constexpr float cfPicWidth = 1920.f * (0.125f * 1.5f);
				constexpr float cfPicHeight = 1080.f * (0.125f * 1.5f);

				for (byte b = 0; b < 3; ++b)
				{
					SetStagePicture(sGroup * 3 + b + 1, &Frec(pPosArr[pGroup][b].x, pPosArr[pGroup][b].y, cfPicWidth, cfPicHeight));
				}

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
				RemoveAll("ステージピクチャータスク");
				//Remove(sp);
			}
			bSetPictureCount = 0;
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (!rHukidasi.SizeZero())
		{
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				Frec src(16.f * 59, 16.f * 0, 16.f, 16.f);
				rHukidasi.Draw(&res->iStageImg, &src, false);
			}
		}
		if (!rHukidasi.GetH()) rHukidasi.Draw();
		if (rHukidasi.GetH() >= fHeightMax)
		{
			Font f;
			f.FontCreate("メイリオ", 100);
			f.SetColor(RGB(255, 0, 0));
			f.Draw(&pFontPos[pGroup], std::string("test").c_str(), false);
		}
	}
	/*吹き出しのサイズ変更*/
	void Obj::Resize()
	{
		/*現在のサイズ*/
		const float fScaleW = rHukidasi.GetW();
		const float fScaleH = rHukidasi.GetH();
		/*各増加量*/
		const float fAddW = (fAddScale < 0.f && fScaleH > 0.f) ? 0.f : fAddScale;
		const float fAddH = (fAddScale > 0.f && fScaleW < fWidthMax) ? 0.f : fAddScale;
		/*サイズと増加量からサイズ変更*/
		const float fResizeW = Min(Max(fScaleW + fAddW, 0.f), fWidthMax);
		const float fResizeH = Min(Max(fScaleH + fAddH, 0.f), fHeightMax);
		rHukidasi.Scaling(fResizeW, fResizeH);
	}
	/*サイズの変化量を設定*/
	void Obj::SetAddScale(const float afAddScale)
	{
		fAddScale = afAddScale;
	}
	/*サイズの最大値を設定*/
	void Obj::SetScaleMax(const float afWMax, const float afHMax)
	{
		fWidthMax = afWMax;
		fHeightMax = afHMax;
	}
	/*座標を設定*/
	void Obj::SetPos(const Point * const appPos)
	{
		rHukidasi.SetPos(appPos);
	}
	/*表示するステージの設定*/
	void Obj::SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize)
	{
		if (bSetPictureCount > 2) return;
		auto sp = Add<StagePicture::Obj>();
		sp->LoadImg(auiStageNumber);
		sp->SetPos(&Point(apfrPosSize->l, apfrPosSize->t));
		sp->SetSize(apfrPosSize->r, apfrPosSize->b);
		++bSetPictureCount;
	}
	/*ステージのグループの設定*/
	void Obj::SetStageGroup(const PictureGroup apStageGroup, const StageGroup asStageGroup)
	{
		pGroup = apStageGroup;
		sGroup = asStageGroup;
	}
}
