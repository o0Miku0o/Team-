#include "BlackHole.h"
#include "BlackHoleGenerator.h"

namespace BlackHoleGenerator
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
		SetName("�u���b�N�z�[�������^�X�N");

		/*���\�[�X����*/

	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		/*���\�[�X�̏���*/
	}
	/*�^�X�N���Ƃ̍X�V����*/
	void Obj::Update()
	{
		Remove(this);
	}
	/*�^�X�N���Ƃ̕`�揈��*/
	void Obj::Render()
	{
	
	}

	void Obj::Bridge(Point *pPos, const float *pSize, const int mode, Point *pMovePos) {
		auto blackHole = Add<BlackHole::Obj>();
		blackHole->pPos = *pPos;
		blackHole->rBlackHole = Rec(pPos->x, pPos->y, *pSize, *pSize);
		if (mode == Bigger) {
			blackHole->bBigger = true;
		}
		else if (mode == Move) {
			blackHole->bMove = true;
			blackHole->pEndPos = *pMovePos;
		}
	}
}