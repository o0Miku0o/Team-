#include "MeteoGenerator.h"
#include "Meteo.h"

namespace MeteoGenerator
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
		SetName("覐ΐ����^�X�N");
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
	void Obj::Bridge(const int iNum, const Point * const pPos, const Vector2 * const vSpd)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto met = Add<Meteo::Obj>();
			met->pInitPos.x = (pPos + i)->x;
			met->pInitPos.y = (pPos + i)->y;
			met->rMeteo.SetPos(pPos + i);
			met->cMeteoHitBase.SetPos(pPos + i);
			
			met->vSpd = *(vSpd + i);
		}
		Remove(this);
	}
}
