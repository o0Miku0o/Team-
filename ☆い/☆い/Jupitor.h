#pragma once
#include "MyGame/MyApp.h"

namespace Jupitor
{
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
		int iAlpha;
		int iCnt;

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
	}*OBJ_ptr;
}