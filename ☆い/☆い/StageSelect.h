#pragma once
#include "MyGame/MyApp.h"

namespace StageSelect
{
	const char caTaskName[] = { "ステージ選択タスク" };
	const char caResName[] = { "ステージ選択リソース" };

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
		Obj() {}
		~Obj() {}
		int iCnt;
		Rec rHoudai;
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}