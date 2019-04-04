#include "Stage3-3.h"
#include "Stage3-1.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"

namespace Stage33
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
		SetName("�X�e�[�W�P�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(500.f, Rec::Win.b*0.5f), &iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		//auto sg = Add<BreakStarGenerator::Obj>();
		//int iChange = 25;
		sg->Bridge(1, &iChange, &Point(1800.f, Rec::Win.b*0.5f));

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 5;
		Point pPos[ceiNum] =
		{
			Point(900.f, Rec::Win.b * 0.1f),
			Point(700.f, Rec::Win.b * 0.35f),
			Point(1100.f, Rec::Win.b * 0.65f),
			Point(1300.f, Rec::Win.b * 0.35f),
			Point(1500.f, Rec::Win.b * 0.35f),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMRemove,
			Alien::BMRemove,
			Alien::BMRemove,
			Alien::BMRemove,
			Alien::BMRemove,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectDR,
			Alien::FGReflectDR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimReflectDR,
			Alien::AnimReflectDR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		/*�f�[�^�̏�����*/

		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			res->wsBGM.PlayL();
		}
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		if (kb->Now('G') == 1)
		{
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage31::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
