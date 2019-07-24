#pragma once
#include "MyGame/MyApp.h"
#include "../����/MyGame/My/EventMsg.h"

namespace TimeAttack
{
	const char caTaskName[] = { "�^�C���A�^�b�N�^�X�N" };
	const char caResName[] = { "�^�C���A�^�b�N���\�[�X" };

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
		int iTimeCnt;
		int iFrameCnt;
		std::string str;
		Point pos;
		float width, height;
		EventMsg timeMsg;

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