#include "StageManager.h"
#include "Beam.h"
#include "Effect.h"

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
		rHitBase = Rec(0.f, Rec::Win.b * 0.5f, 30.f, 16.f);
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
		/*�G�t�F�N�g���o*/
		for (byte b = 0; b < 2; ++b)
		{
			auto ef1 = Add<Eff1::Obj>();
			const fix fAng = ModAngle(rHitBase.GetDeg() + 180.f + (rand() % 21 - 10));
			const fix fRad = DtoR(fAng);
			const fix fSpdX = cos_fast((float)fRad) * 2.f;
			const fix fSpdY = sin_fast((float)fRad) * 2.f;
			Rec rEf(rHitBase.GetPosX() + cos_fast(DtoR(ModAngle(fAng + (b * 180.f - 90.f)))) * (rand() % 9 - 4.f), rHitBase.GetPosY() + sin_fast(DtoR(ModAngle(fAng + (b * 180.f - 90.f)))) * (rand() % 9 - 4.f), 24.f, 3.f, fAng);
			ef1->SetParam(&rEf, &Vector2(fSpdX, fSpdY), 20, Eff1::Type::TYPE_BEAM, fAng);
		}

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
