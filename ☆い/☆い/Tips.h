#pragma once
#include "MyGame/MyApp.h"

namespace Tips
{
	const char caTaskName[] = { "�|�e�`�^�X�N" };
	const char caResName[] = { "�|�e�`���\�[�X" };


	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iTips;
		Image iGuideBase;

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
		Rec rTips;
		Rec rGuideBase;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	};
}