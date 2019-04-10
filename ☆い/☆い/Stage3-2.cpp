#include "Stage3-2.h"
#include "Stage3-3.h"
#include "StageSelect.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "Back.h"

namespace Stage32
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
		SetName("ステージ３−２タスク");
		/*リソース生成*/
		/*タスクの生成*/
		Add<Back::Obj>();
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(800.f, Rec::Win.b*0.5f), &iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		//auto sg = Add<BreakStarGenerator::Obj>();
		//int iChange = 25;
		sg->Bridge(1, &iChange, &Point(1350.f, 800.f));

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 6;
		Point pPos[ceiNum] =
		{
			Point(1000.f, Rec::Win.b * 0.5f),
			Point(600.f, Rec::Win.b * 0.5f),
			Point(600.f, 1100.f),
			Point(1600.f, 800.f),
			Point(1600.f, 250.f),
			Point(600.f, 0.f)
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::Move_Rotation,
			Alien::MoveRotation,
			Alien::MoveRotation,
			Alien::MoveVertical,
			Alien::Move_Vertical,
			Alien::Move_Horizontal,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUR,
			Alien::BMReflectDL,
			Alien::BMReflectUL,
			Alien::BMReflectDR,
			Alien::BMReflectDR,
			Alien::BMReflectDL,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUR,
			Alien::FGReflectDL,
			Alien::FGReflectUL,
			Alien::FGReflectUR,
			Alien::FGReflectDR,
			Alien::FGReflectDL,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimRotation,
			Alien::AnimRotation,
			Alien::AnimRotation,
			Alien::AnimNormal,
			Alien::AnimNormal,
			Alien::AnimHorizontal,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		/*データの初期化*/

		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			res->wsBGM.Restart();
		}
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{

	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);
		if (kb->Now('G') == 1 || pad->NowBut(J_BUT_8) == 1)
		{
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
			Add<Stage33::Obj>();
			Pause(2);
		}

		if (pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
			Add<StageSelect::Obj>();
			Pause(2);
		}
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

		if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
		{
			Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(16.f * 0.f, 0.f, 16.f, 16.f));
		}
	}
}
