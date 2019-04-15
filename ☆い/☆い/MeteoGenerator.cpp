#include "MeteoGenerator.h"
#include "Meteo.h"

namespace MeteoGenerator
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
		SetName("隕石生成タスク");
		/*リソース生成*/

		/*タスクの生成*/

		/*データの初期化*/
	}
	/*タスクの終了処理*/
	void Obj::Finalize()
	{
	}
	/*タスクの更新処理*/
	void Obj::Update()
	{
	}
	/*タスクの描画処理*/
	void Obj::Render()
	{
	}
	void Obj::Bridge(const int iNum, const Point * const pPos, const Vector2 * const vSpd)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto met = Add<Meteo::Obj>();
			met->pInitPos.x = (pPos + i)->x;
			met->pInitPos.y = (pPos + i)->y;
			met->rMeteo.SetPos(pPos + i);
			met->cMeteoHitBase.SetPos(pPos + i);
			
			met->vSpd = *(vSpd + i);
		}
		Remove(this);
	}
}
