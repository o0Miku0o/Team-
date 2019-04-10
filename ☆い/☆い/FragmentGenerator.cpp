#include "FragmentGenerator.h"
#include "Fragment.h"

namespace FragmentGenerator
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
		SetName("���А����^�X�N");
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
	void Obj::Bridge(const int iNum, const Point *  pPos, const int * const iColor)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto fragment = Add<Fragment::Obj>();
			fragment->rFragment.SetPos(pPos + i);
			fragment->cFragmentHitBase.SetPos(pPos + i);
			fragment->pInitPos = *(pPos + i);
			fragment->iColor = *(iColor + i);
		}
		Remove(this);
	}
	void Obj::Bridge2(const int iNum, const vector<Point> pPos, const vector<int> iColor)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto fragment = Add<Fragment::Obj>();
			fragment->rFragment.SetPos(&pPos.at(i));
			fragment->cFragmentHitBase.SetPos(&pPos.at(i));
			fragment->pInitPos = pPos.at(i);
			fragment->iColor = iColor.at(i);
		}
		Remove(this);
	}
}
