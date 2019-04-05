#include "BreakStar.h"
#include "Beam.h"
#include "StageManager.h"
#include "FragmentGenerator.h"
#include "BlackHoleGenerator.h"
#include "Title.h"

namespace BreakStar
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
		SetName("�󂷐��^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rStar = Rec(Rec::Win.r * 0.75f, Rec::Win.b * 0.5f, 100, 100);
		cHitbase = Circle(&rStar.GetPos(), rStar.GetW() / 2);
		iChange = 25;/*���ʂ̐���25��������36�ŏ����l��ݒ肷��*/
		bHitAct = false;
		bBlackMode = true;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (!bHitAct && !bBlackMode)
		{
			if (auto beam = Find<Beam::Obj>("�r�[���^�X�N"))
			{
				CheckHit(beam);
			}
		}
		if (!Find<Beam::Obj>("�r�[���^�X�N"))
		{
			bHitAct = false;
		}
		if (bBlackMode)
		{
			++iTime;
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			if (bBlackMode)
			{
				Frec src(16.f * (iChange + iTime / 100), 0, 16.f, 16.f);
				rStar.Draw(&res->iStageImg, &src, true);
			}
			else
			{
				Frec src(16.f * iChange, 0, 16.f, 16.f);
				rStar.Draw(&res->iStageImg, &src, true);

			}
			rStar.Draw();
			if (iTime > 299)
			{
				Remove(this);
				auto bf = Add<BlackHoleGenerator::Obj>();
				float size = 100.f;
				const int ciMode = 0;
				bf->Bridge(1, &Point(rStar.GetPosX(), rStar.GetPosY()), &size, &ciMode);
			}
			//else
			//{
			//	rStar.Draw(&res->iStageImg, &src, true);
			//	rStar.Draw();
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
			cHitbase.Draw();
#endif // _DEBUG
		}
	}
	void Obj::CheckHit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cHit;
		cHit.SetRadius(oBeam->rHitBase.GetH());
		cHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cHitbase.CheckHit(&cHit))
		{
			auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X");
			if (iChange > 25)
			{
				if (res)
				{
					res->wsTest6.Play();
				}
				++iChange;
			}
			else
			{
				if (res)
				{
					res->wsTest6.Play();
				}
				iChange = 34;
			}
			//if (bBlackMode)
			//{
			//	if (iChange > 38)
			//	{
			//		if (res)
			//		{
			//			res->wsTest3.Play();
			//		}
			//		Remove(this);
			//	}
			//}
			//else
			//{
			if (iChange > 35)
			{
				if (res)
				{
					res->wsTest3.Play();
				}
				auto fg = Add<FragmentGenerator::Obj>();
				//Point pArr[5] = {/*Point(1000.f, 300.f) , Point(800.f, 500.f),Point(1200.f,500.f),Point(900.f,700.f),Point(1100.f,700.f)*/ };
				Point pArr[5] = {
					Point(rStar.GetPosX(),rStar.GetPosY() - 200.f),Point(rStar.GetPosX() - 200.f,rStar.GetPosY()),Point(rStar.GetPosX() + 200.f,rStar.GetPosY()),
					Point(rStar.GetPosX() - 100.f,rStar.GetPosY() + 200.f), Point(rStar.GetPosX() + 100.f,rStar.GetPosY() + 200.f)
				};
				int iColor[5] = {};
				fg->Bridge(5, pArr, iColor);
				Remove(this);
			}
			//}
			Remove(bm);
			bHitAct = true;
		}
	}
}
