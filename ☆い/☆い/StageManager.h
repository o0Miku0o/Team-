#pragma once
#include "MyGame/MyApp.h"

namespace StageManager
{
	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iStageImg;
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
	/*�^�X�N�I�u�W�F�N�g�N���X*/
	typedef class Obj : public TaskBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		u_short usBeamCount;
		byte bClearFragmentNumMax;
		byte bClearFragmentNum;
		byte bNextStage;

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