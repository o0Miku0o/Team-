#include "StageSelect.h"
#include "StageManager.h"
#include "Stage.h"
#include "StageLoad.h"

namespace Stage
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
		SetName("ステージタスク");
		/*リソース生成*/

		/*タスクの生成*/

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
			Add<StageLoad::Obj>();
			Pause(2);
		}

		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>("ステージ統括リソース"))
			{
				res->wsBGM.Pause();
			}
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("ステージ統括タスク", NOT_REMOVE_NAME);
			Add<StageLoad::Obj>();
			Pause(2);
		}

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{

	}
}
