#include "Star.h"
#include "Fragment.h"
#include "StageManager.h"
#include "Title.h"

namespace Star
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
		SetName("���^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rStar = Rec(Rec::Win.r * 0.75f, Rec::Win.b * 0.5f, 100, 100);
		cStarhitbase = Circle(&rStar.GetPos(), rStar.GetW() / 2);
		iChange = 0;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		auto vFgm = FindAll <Fragment::Obj>("���Ѓ^�X�N");
		if (vFgm.size())
		{
			for (auto &vf : vFgm)
			{
				CheckHit(vf);
			}
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			Frec src(16.f * iChange, 0, 16.f, 16.f);
			rStar.Draw(&res->iStageImg, &src, true);
			//rStar.Draw();
			//if (iChange == 0)
			//{
			//	
			//}
			//if (iChange == 1)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
			//if (iChange == 2)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
			//if (iChange == 3)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
			//if (iChange == 4)
			//{
			//	rStar.Draw(&res->iStarimage, tmp*iChange, 0, tmp, tmp);
			//}
#ifdef _DEBUG
			cStarhitbase.Draw();
#endif // _DEBUG	
		}
	}
	void Obj::CheckHit(TaskBase* fr)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fr;
		Circle cHit;
		cHit.SetRadius(oFragment->cFragmentHitBase.GetRadius());
		cHit.SetPos(&oFragment->cFragmentHitBase.GetPos());
		if (cStarhitbase.CheckHit(&cHit))
		{
			if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
			{
				res->wsTest2.Play();
				//res->wsTest1.Restart();
			}
			iChange = min(iChange + 1, 22 + 13);
			//if (iChange > 4)
			//{
			//	iChange = 0;
			//}
			Remove(fr);
			/*oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;*/
		}
	}
}
