#pragma once
#include "MyGame/MyApp.h"

namespace Demo
{
	const char caTaskName[] = { "�ł��^�X�N" };
	const char caResName[] = { "�ł����\�[�X" };
	
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
		bool bIsLoad;
		byte bFadeCompCnt;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();

		std::string replayStage;
		std::string replayFile;

		//�t�@�C���̑傫�����o�C�g�ŕԂ�
		//__int64 �� Long �^�C�v
		__int64 getFileSize(const std::string &asRepFileName);
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}