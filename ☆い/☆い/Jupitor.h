#pragma once
#include "MyGame/MyApp.h"
#include "Eff1.h"

namespace Jupitor
{
	const char caTaskName[] = { "�ؐ��^�X�N" };
	const char caResName[] = { "�ؐ����\�[�X" };

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
		Rec rJupitor;
		Rec rGravityCircle;
		Circle cJupitorHitBase;
		Circle cGravityCircle;
		int iAnimCount;
		int i;
		Eff1::EffectCreater::SP effsp;

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