#include "Saturn.h"
#include "Beam.h"
#include "Fragment.h"
#include "StageManager.h"

namespace Saturn
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
		SetName("土星タスク");
		/*リソース生成*/
		/*タスクの生成*/

		/*データの初期化*/
		rSaturn = Rec(1000, 500, 16 * 14, 16 * 14);
		cSaturnHitBase = Circle(&rSaturn.GetPos(), rSaturn.GetW()*0.3f);
		cGravityCircle = Circle(&rSaturn.GetPos(), rSaturn.GetW()*0.8f);
		iAnimCount = 0;
		i = 12;
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		auto vf = FindAll<Fragment::Obj>("欠片タスク");
		for (auto &f : vf)
		{
			FragmentCheckhit(f);
			if (cGravityCircle.CheckHit(&f->rFragment.GetPos()) && !cGravityCircle.CheckHit(&f->pPrevPos))
			{
				if (!f->bRotationActive)
				{
					f->pRotPos = cGravityCircle.GetPos();
					f->fRotRadius = cGravityCircle.GetRadius() - 1;
					f->bRotationActive = true;
					f->bMoveActive = false;
				}
			}
		}
		if (auto beam = Find<Beam::Obj>("ビームタスク"))
		{
			Obj::BeamCheckhit(beam);
		}
		cSaturnHitBase.SetPos(&rSaturn.GetPos());
		cSaturnHitBase.SetRadius(rSaturn.GetW()*0.4f);
		cGravityCircle.SetPos(&rSaturn.GetPos());
		cGravityCircle.SetRadius(rSaturn.GetW()*0.8f);
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Frec src(16.f * (iAnimCount + 20), 16, 16, 16);
			if (i >= 25)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i;
			rSaturn.Draw(&res->iStageImg, &src, true);
		}
		cSaturnHitBase.Draw();
		cGravityCircle.Draw();
	}
	void Obj::BeamCheckhit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBmHit;
		cBmHit.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBmHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cSaturnHitBase.CheckHit(&cBmHit))
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
		if (cSaturnHitBase.CheckHit(&cFrHit))
		{
			oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;
		}
	}
}
