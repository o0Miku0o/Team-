#pragma once
#include "MyGame/MyApp.h"

namespace Meteo
{
	const char caTaskName[] = { "隕石タスク" };
	const char caResName[] = { "隕石リソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*タスクオブジェクトクラス*/
	typedef class Obj : public TaskBase
	{
	public:
		/*必要なメンバはここに追加*/
		int iMeteoNum;
		Vector2 vSpd;

		Rec rMeteo;
		Circle cMeteoHitBase;

		Point pInitPos;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void BeamCheckhit(TaskBase* bm);
		void FragmentCheckhit(TaskBase* fr);
	}*Obj_ptr;
}