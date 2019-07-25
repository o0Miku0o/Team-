#include "StarGenerator.h"
#include "Star.h"

namespace StarGenerator
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
	void Obj::Bridge(const int iNum, const int* iChange, const Point* pPos)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto star = Add<Star::Obj>();
			star->rStar.SetPos(pPos + i);
			star->cStarhitbase.SetPos(pPos + i);
	//		star->iChange = *(iChange+i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<int> &iChange, const vector<Point> &pPos) {
		for (int i = 0; i < iNum; ++i)
		{	
			auto star = Add<Star::Obj>();
			star->rStar.SetPos(&pPos.at(i));
			star->cStarhitbase.SetPos(&pPos.at(i));
			//star->iChange = iChange.at(i);
			star->starColor = (Star::Obj::StarColor)iChange.at(i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<int> &iChange, const vector<int> &iEffect, const vector<Point> &pPos)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto star = Add<Star::Obj>();
			star->rStar.SetPos(&pPos.at(i));
			star->cStarhitbase.SetPos(&pPos.at(i));
		//	star->iChange = iChange.at(i);
		//	star->iStarEffect = iEffect.at(i);
			star->starColor = (Star::Obj::StarColor)iChange.at(i);
			star->starEffect = (Star::Obj::StarEffect)iEffect.at(i);
		}
		Remove(this);
	}
	void Obj::Bridge(const int iNum, const vector<int> &iChange, const vector<int> &iEffect, const vector<Frec> &fRec)
	{
		Point pPos;
		for (int i = 0; i < iNum; ++i)
		{
			auto star = Add<Star::Obj>();
			pPos = Point(fRec.at(i).l, fRec.at(i).t);
			star->rStar.SetPos(&pPos);
			star->rStar.Scaling(fRec.at(i).r, fRec.at(i).b);
			star->cStarhitbase.SetPos(&pPos);
			//	star->iChange = iChange.at(i);
			//	star->iStarEffect = iEffect.at(i);
			star->starColor = (Star::Obj::StarColor)iChange.at(i);
			star->starEffect = (Star::Obj::StarEffect)iEffect.at(i);
		}
		Remove(this);
	}
}
