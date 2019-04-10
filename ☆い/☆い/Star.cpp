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
			cStarhitbase.Draw();
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
				switch (iChange)
				{
				case 22:
					if (oFragment->iColor == 0)
					{
						iChange = 23;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChange = 26;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iChange = 28;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 23:
					if (oFragment->iColor == 0)
					{
						iChange = 24;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChange = 27;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iChange = 29;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 24:
					if (oFragment->iColor == 0)
					{
						iChange = 25;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChange = 33;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						iChange = 32;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 25:
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					break;
				case 26:
					if (oFragment->iColor == 0)
					{
						iChange = 27;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					if (oFragment->iColor == 2)
					{
						iChange = 30;
						res->wsTest2.Play();
						Remove(fr);
					}
					break;
				case 27:
					if (oFragment->iColor == 2)
					{
						iChange = 31;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					
					}
					break;
				case 28:
					if (oFragment->iColor == 0)
					{
						iChange = 29;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 1)
					{
						iChange = 30;
						res->wsTest2.Play();
						Remove(fr);
					}
					if (oFragment->iColor == 2)
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 29:
					if (oFragment->iColor == 1)
					{
						iChange = 31;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 30:
					if (oFragment->iColor == 0)
					{
						iChange = 31;
						res->wsTest2.Play();
						Remove(fr);
					}
					else
					{
						oFragment->rFragment.SetPos(&oFragment->pInitPos);
						res->wsTest5.Play();
						oFragment->bMoveActive = false;
					}
					break;
				case 31:
					oFragment->rFragment.SetPos(&oFragment->pInitPos);
					res->wsTest5.Play();
					oFragment->bMoveActive = false;
					break;
				}
			}
			//iChange = min(iChange + 1, 22 + 13);
			//if (iChange > 4)
			//{
			//	iChange = 0;
			//}			
			/*oFragment->rFragment.SetPos(&oFragment->pInitPos);
			oFragment->bMoveActive = false;*/
		}
	}
}
