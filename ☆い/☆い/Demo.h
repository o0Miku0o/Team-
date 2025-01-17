#pragma once
#include "MyGame/MyApp.h"

namespace Demo
{
	const char caTaskName[] = { "でもタスク" };
	const char caResName[] = { "でもリソース" };
	
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
		bool bIsLoad;
		byte bFadeCompCnt;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}