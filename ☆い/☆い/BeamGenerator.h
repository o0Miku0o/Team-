#pragma once
#include "MyGame/MyApp.h"

namespace BeamGenerator
{
	const char caTaskName[] = { "�r�[�������^�X�N" };
	const char caResName[] = { "�r�[���������\�[�X" };

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
		byte bBeamCount;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void BeamCreate(TaskBase *atpPlayer);
		void TitleBeamCreate();
	public:
		void Update();
		void Render();

	}*Obj_ptr;
}