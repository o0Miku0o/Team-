#pragma once
#include "MyGame/MyApp.h"

using namespace std;

namespace BreakStarGenerator
{
	const char caTaskName[] = { "�󂷐������^�X�N" };
	const char caResName[] = { "�󂷐��������\�[�X" };

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

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void Bridge(const int iNum, const int* iChange, const Point* pPos, const bool* bMode);
		void Bridge(const int iNum, const vector<int> iChange, const vector<Point> pPos, const vector<bool> bMode);
	}*Obj_ptr;
}