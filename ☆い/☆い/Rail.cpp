#include "Rail.h"

namespace Rail
{
	/*リソースの初期化処理*/
	void RS::Init()
	{
		iRailImg.ImageCreate("./data/image/main/rail.bmp");
	}
	/*リソースの終了処理*/
	void RS::Finalize()
	{
		iRailImg.Release();
	}
	/*タスクの初期化処理*/
	void Obj::Init()
	{
		/*タスク名設定*/
		SetName(caTaskName);
		/*リソース生成*/
		RB::Add<Rail::RS>(caResName);
		/*タスクの生成*/

		/*データの初期化*/
		SetRenderPriority(0.1f);

		rRailBase = Rec(100.f, Rec::Win.b * 0.5f, 16.f * 2.f, 880.f/*1080 - 200*/);
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{

	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
		if (auto res = RB::Find<Rail::RS>(caResName))
		{
			rRailBase.Draw(&res->iRailImg, &Frec(0.f, 0.f, 16.f, 96.f));
		}
	}
}
