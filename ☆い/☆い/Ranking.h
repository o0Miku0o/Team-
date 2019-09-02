#pragma once
#include "MyGame/MyApp.h"
#include "../����/MyGame/My/EventMsg.h"

namespace Ranking
{
	const char caTaskName[] = { "�����L���O�^�X�N" };
	const char caResName[] = { "�����L���O���\�[�X" };

	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iButton;

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
		Rec rButton;
		float width;
		float height;
		Point pos;
		std::string str;
		EventMsg titleMsg;
		std::string sName[5];
		float rwidth;
		float rheight;
		EventMsg rankMsg;
		Point rankpos;
		std::multimap<int, std::string> mRankmap;
		std::multimap<int, std::string>::iterator newData;
		int iNewindex;
		EventMsg newMsg;

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