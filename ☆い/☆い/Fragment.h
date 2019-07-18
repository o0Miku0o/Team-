#pragma once
#include "MyGame/MyApp.h"

namespace Fragment
{
	const char caTaskName[] = { "���Ѓ^�X�N" };
	const char caResName[] = { "���Ѓ��\�[�X" };

	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*�^�X�N�I�u�W�F�N�g�N���X*/
	typedef class Obj : public TaskBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Rec rFragment;
		Circle cFragmentHitBase;
		Point pInitPos;
		Point pRotPos;
		Point pPrevPos;
		float fRotRadius;

		int iRotation;
		int iColor;/*���F��0�A�Ԃ�1�A��2*/
		bool bMoveActive;
		bool bRotationActive;
		Vector2 vMove;

		Animation aAnim;

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