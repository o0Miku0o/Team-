#pragma once
#include "MyGame/MyApp.h"

namespace MiniGame
{
	const char caTaskName[] = { "�~�j�Q�[���^�X�N" };
	const char caResName[] = { "�~�j�Q�[�����\�[�X" };

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
		int iFragmentCnt;

		Obj() {}
		~Obj() {}
	private:

		RS_ptr res;
		void Init();
		void Finalize();

	public:
		void Update();
		void Render();

	}*OBJ_ptr;
}