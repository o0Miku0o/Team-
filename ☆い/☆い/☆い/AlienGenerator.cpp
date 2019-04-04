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
		SetName("�F���l�����^�X�N");
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
}
