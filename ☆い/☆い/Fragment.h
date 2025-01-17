#pragma once
#include "MyGame/MyApp.h"
#include "Eff1.h"

namespace Fragment
{
	const char caTaskName[] = { "欠片タスク" };
	const char caResName[] = { "欠片リソース" };

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
		Rec rFragment;
		Circle cFragmentHitBase;
		Point pInitPos;
		Point pRotPos;
		Point pPrevPos;
		float fRotRadius;
		float fInitAngle;

		int iRotation;
		int iColor;/*黄色が0、赤が1、青が2*/
		bool bMoveActive;
		bool bRotationActive;
		Vector2 vMove;

		Animation aAnim;

		Eff1::EffectCreater::SP effsp;
		Eff1::EffectCreater::SP effsp1;
		
		bool bPreRotationActive;
		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void Checkhitbeam(TaskBase* bm);
		void Checkhitfagment(TaskBase* fg);
		void CheckhitAlien(TaskBase* al);

		void HitAfterInit();
	}*Obj_ptr;
	void AnimFragmentY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimFragmentR(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimFragmentB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);

}