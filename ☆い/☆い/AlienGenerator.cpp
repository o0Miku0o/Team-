#include "AlienGenerator.h"

namespace AlienGenerator
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{

	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}

	void Obj::Bridge(const int iNum, const Point* pPos, Alien::Move *fpMove, Alien::Hit *fpBMHit, Alien::Hit *fpFGHit, Alien::Anim *fpAnim)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto alien = Add<Alien::Obj>();
			alien->pCenter = *(pPos + i);
			alien->moveFunc = *(fpMove + i);
			alien->BMHitFunc = *(fpBMHit + i);
			alien->FGHitFunc = *(fpFGHit + i);
			alien->AnimFunc = *(fpAnim + i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<Point> pPos, const vector<Alien::Move> fpMove, const vector <Alien::Hit> fpBMHit,
		const vector<Alien::Hit> fpFGHit, const vector<Alien::Anim> fpAnim) {
		for (int i = 0; i < iNum; ++i)
		{
			auto alien = Add<Alien::Obj>();
			alien->pCenter = pPos.at(i);
			alien->moveFunc = fpMove.at(i);
			alien->BMHitFunc = fpBMHit.at(i);
			alien->FGHitFunc = fpFGHit.at(i);
			alien->AnimFunc = fpAnim.at(i);
		}
		Remove(this);
	}
}
