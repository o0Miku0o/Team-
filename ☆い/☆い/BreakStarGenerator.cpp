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
	void Obj::Bridge(const int iNum, const int* iChange, const Point* pPos, const bool* bMode)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto star = Add<BreakStar::Obj>();
			star->rStar.SetPos(pPos + i);
			star->cHitbase.SetPos(pPos + i);
			star->iChange = *(iChange + i);
			star->bBlackMode = *(bMode + i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<int> iChange, const vector<Point> pPos, const vector<bool> bMode) {
		for (int i = 0; i < iNum; ++i) {
			auto star = Add<BreakStar::Obj>();
			star->rStar.SetPos(&pPos.at(i));
			star->cHitbase.SetPos(&pPos.at(i));
			star->iChange = iChange.at(i);
			star->bBlackMode = bMode.at(i);
			for (int j = 0; j < 5; ++j)
			{
				star->rFrg[j].SetPos(&star->rStar.GetPos());
			}
		}
	}
}
