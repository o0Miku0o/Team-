#pragma once
#include "MyGame/MyApp.h"

namespace Result
{
	const char caTaskName[] = { "���U���g�^�X�N" };
	const char caResName[] = { "���U���g���\�[�X" };

	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iWord;

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
		Rec rBack;
		Rec rPlayer;
		Rec rWord;
		byte bNextStage;
		byte bMoveStarIdx;
		byte bScore;

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