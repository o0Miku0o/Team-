#include "BreakStarGenerator.h"
#include "BreakStar.h"

namespace BreakStarGenerator
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
		SetName("�󂷐������^�X�N");
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
	void Obj::Bridge(const int iNum, const int* iChange, const Point* pPos)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto star = Add<BreakStar::Obj>();
			star->rStar.SetPos(pPos + i);
			star->cHitbase.SetPos(pPos + i);
			star->iChange = *(iChange+i);
		}
		Remove(this);
	}
}
