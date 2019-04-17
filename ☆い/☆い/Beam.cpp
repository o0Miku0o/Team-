#include "StageManager.h"
#include "Beam.h"

namespace Beam
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
		SetName("�r�[���^�X�N");
		/*���\�[�X����*/
		//RB::Add<RS>("�r�[�����\�[�X");
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rHitBase = Rec(0.f, Rec::Win.b * 0.5f, 21.f, 16.f);
		bLifeCount = 0;
		vSpd = Vector2::zero;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		//RB::Remove("�r�[�����\�[�X");
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (bLifeCount >= 120) Remove(this);
		++bLifeCount;
		/*�ړ��x�N�g���ݒ�*/
		if (auto prev = FindPrev<Beam::Obj>("�r�[���^�X�N"))
		{
			const float ang = rHitBase.GetDeg(&prev->rHitBase);
			rHitBase.SetDeg(ang);
		}
		vSpd.SetVec(rHitBase.GetDeg(), 20.f);
		/*��`���ړ�*/
		rHitBase.Move(&vSpd);

		/*��ʊO�ɏo�������*/
		if (rHitBase.GetPosX() > Rec::Win.r + 10.f) Remove(this);
		if (rHitBase.GetPosX() < Rec::Win.l - 10.f) Remove(this);
		if (rHitBase.GetPosY() > Rec::Win.b + 10.f) Remove(this);
		if (rHitBase.GetPosY() < Rec::Win.t - 10.f) Remove(this);
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto stageRes = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			//rHitBase.Draw(&stageRes->iStageImg, 16 * 10, 0, 16, 16, true, true);

			Frec src(16.f * 10, 0.f, 16.f, 16.f);
			rHitBase.Draw(&stageRes->iStageImg, &src, true);
		}
	}
}
