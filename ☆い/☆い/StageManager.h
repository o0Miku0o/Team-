#pragma once
#include "MyGame/MyApp.h"

namespace StageManager
{
	const char caTaskName[] = { "ステージ統括タスク" };
	const char caResName[] = { "ステージ統括リソース" };

	/*リソースクラス*/
	class RS : public ResourceBase
	{
	public:
		/*必要なメンバはここに追加*/
		Image iStageImg;
		Image tese;
		WSound wsTest;
		WSound wsTest2;
		WSound wsTest3;
		WSound wsTest4;
		WSound wsTest5;
		WSound wsTest6;
		WSound wsTest7;
		WSound wsTest8;
		WSound wsTest9;
		WSound wsTest10;
		WSound wsTest11;
		WSound wsTest12;
		WSound wsTest13;
		WSound wsBGM;
		WSound wsBGM1;
		WSound wsBGM2;

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
		Point pTutorialPos;
		std::array<byte, 3> bScores;
		u_short usBeamCount;
		byte bClearFragmentNumMax;
		byte bClearFragmentNum;
		byte bNextStage;
		byte bStageNum;
		bool bIsDebug;
		int iResultCnt;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}