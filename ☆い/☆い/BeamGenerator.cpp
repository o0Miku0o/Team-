#include "BeamGenerator.h"
#include "Beam.h"
#include "Player.h"
#include "Title.h"
#include "StageManager.h"
#include "BreakStar.h"

namespace BeamGenerator
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
		bBeamCount = 0;

		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			++sm->usBeamCount;
		}
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (auto player = Find<Player::Obj>(Player::caTaskName))
		{
			if (bBeamCount > 5)
			{
				Remove(this);
				return;
			}
			auto beam = Add<Beam::Obj>();
			Point pPos
			(
				cos(DtoR(player->rBase.GetDeg() - 180)) * player->rBase.GetW() * 0.5f + player->rBase.GetPosX(),
				sin(DtoR(player->rBase.GetDeg() - 180)) * player->rBase.GetW() * 0.5f + player->rBase.GetPosY()
			);
			beam->rHitBase.SetPos(&pPos);
			beam->rHitBase.SetDeg(player->rBase.GetDeg() + 180);
		}
		else if (Find<Title::Obj>(Title::caTaskName))
		{
			if (bBeamCount > 13)
			{
				Remove(this);
				return;
			}
			auto beam = Add<Beam::Obj>();
			beam->rHitBase.SetPos(&Point(Rec::Win.l, Rec::Win.b * 0.423f));
			beam->rHitBase.Scaling(21.f, 16.f * 2.f);
			beam->rHitBase.SetDeg(0.f);
		}
		++bBeamCount;
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
