#include "Neptune.h"
#include "StageManager.h"
#include "Beam.h"
#include "Fragment.h"

namespace Neptune
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
		SetName("�C�����^�X�N");
		/*���\�[�X����*/
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rNeptune = Rec(1350, 680, 16 * 14, 16 * 14);
		cNeptuneHitBase = Circle(&rNeptune.GetPos(), rNeptune.GetW()*0.4f);
		cGravityCircle = Circle(&rNeptune.GetPos(), rNeptune.GetW()*0.8f);
		iAnimCount = 0;
		i = 12;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		auto vf = FindAll<Fragment::Obj>("���Ѓ^�X�N");
		for (auto &f : vf)
		{
			FragmentCheckhit(f);
			if (cGravityCircle.CheckHit(&f->rFragment.GetPos()) && !cGravityCircle.CheckHit(&f->pPrevPos))
			{
				if (!f->bRotationActive)
				{
					f->pRotPos = cGravityCircle.GetPos();
					f->fRotRadius = cGravityCircle.GetRadius()-1;
					f->bRotationActive = true;
					f->bMoveActive = false;
				}
			}
		}
		if (auto beam = Find<Beam::Obj>("�r�[���^�X�N"))
		{
			BeamCheckhit(beam);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			Frec src(16.f * (iAnimCount + 16), 16, 16, 16);
			if (i >= 25)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i; 
			rNeptune.Draw(&res->iStageImg, &src, true);
		}
		cNeptuneHitBase.Draw();
		cGravityCircle.Draw();
	}
	void Obj::BeamCheckhit(TaskBase* bm)
	{
		Beam::Obj* oBeam = (Beam::Obj*)bm;
		Circle cBmHit;
		cBmHit.SetRadius(oBeam->rHitBase.GetW()*0.5f);
		cBmHit.SetPos(&oBeam->rHitBase.GetPos());
		if (cNeptuneHitBase.CheckHit(&cBmHit))
		{
			Remove(bm);
		}
	}
	void Obj::FragmentCheckhit(TaskBase* fr)
	{
		Fragment::Obj* oFragment = (Fragment::Obj*)fr;
		Circle cFrHit;
		cFrHit.SetRadius(oFragment->rFragment.GetW()*0.5f);
		cFrHit.SetPos(&oFragment->rFragment.GetPos());
		if (cNeptuneHitBase.CheckHit(&cFrHit))
		{
			Remove(fr);
			//oFragment->rFragment.SetPos(&oFragment->pInitPos);
			//oFragment->bMoveActive = false;
		}
	}
}
