#pragma once
#include "MyGame/MyApp.h"

namespace JecLogo
{
	const char caTaskName[] = { "Jec���S�^�X�N" };
	const char caResName[] = { "Jec���S���\�[�X" };
	
	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iLogoImg;
		Image iBlackImg;

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
		Rec rLogoBase;
		int iWaitCnt;
		float fAlpha;
		bool bRev;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}