#pragma once
#include "MyGame/MyApp.h"
#include "Alien.h"

using namespace std;

namespace AlienGenerator
{
	const char caTaskName[] = { "�F���l�����^�X�N" };
	const char caResName[] = { "�F���l�������\�[�X" };

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

		void Bridge(const int iNum, const Point* pPos, Alien::Move *fpMove, Alien::Hit *fpBMHit, Alien::Hit *fpFGHit, Alien::Anim *fpAnim);
		void Bridge(const int iNum, const vector<Point> pPos, const vector<Alien::Move> fpMove, const vector <Alien::Hit> pBMHit, 
			const vector<Alien::Hit> fpFGHit, const vector<Alien::Anim> fpAnim);
	}*Obj_ptr;
}