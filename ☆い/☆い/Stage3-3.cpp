#include "Stage3-3.h"
#include "Stage4-1.h"
#include "StageSelect.h"
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
		SetName("�X�e�[�W�R�|�R�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(300.f, Rec::Win.b*0.5f), &iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		//auto sg = Add<BreakStarGenerator::Obj>();
		//int iChange = 25;
		sg->Bridge(1, &iChange, &Point(1800.f, Rec::Win.b*0.25f));

		auto ag = Add<AlienGenerator::Obj>();
		constexpr int ceiNum = 25;
		Point pPos[ceiNum] =
		{
			Point(510.f, Rec::Win.b * 0.f),
			Point(760.f, Rec::Win.b * 0.f),
			Point(1010.f, Rec::Win.b * 0.f),
			Point(1260.f, Rec::Win.b * 0.f),
			Point(1510.f, Rec::Win.b * 0.f),
			Point(510.f, Rec::Win.b * 0.25f),
			Point(760.f, Rec::Win.b * 0.25f),
			Point(1010.f, Rec::Win.b * 0.25f),
			Point(1260.f, Rec::Win.b * 0.25f),
			Point(1510.f, Rec::Win.b * 0.25f),
			Point(510.f, Rec::Win.b * 0.5f),
			Point(760.f, Rec::Win.b * 0.5f),
			Point(1010.f, Rec::Win.b * 0.5f),
			Point(1260.f, Rec::Win.b * 0.5f),
			Point(1510.f, Rec::Win.b * 0.5f),
			Point(510.f, Rec::Win.b * 0.75f),
			Point(760.f, Rec::Win.b * 0.75f),
			Point(1010.f, Rec::Win.b * 0.75f),
			Point(1260.f, Rec::Win.b * 0.75f),
			Point(1510.f, Rec::Win.b * 0.75f),
			Point(510.f, Rec::Win.b),
			Point(760.f, Rec::Win.b),
			Point(1010.f, Rec::Win.b),
			Point(1260.f, Rec::Win.b),
			Point(1510.f, Rec::Win.b),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
			Alien::MoveStay,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectDR,
			Alien::BMReflectDR,
			Alien::BMReflectUR,
			Alien::BMReflectUR,
			Alien::BMReflectDR,
			Alien::BMReflectDR,
			Alien::BMReflectUR,
			Alien::BMReflectUR,
			Alien::BMReflectDR,
			Alien::BMReflectDR,
			Alien::BMReflectUR,
			Alien::BMReflectUR,
			Alien::BMReflectUR,
			Alien::BMReflectDR,
			Alien::BMReflectUR,
			Alien::BMReflectDR,
			Alien::BMReflectDR,
			Alien::BMReflectUR,
			Alien::BMReflectUL,
			Alien::BMReflectDL,
			Alien::BMReflectUR,
			Alien::BMReflectUR,
			Alien::BMReflectUR,
			Alien::BMReflectDL,
			Alien::BMReflectUR,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectDR,
			Alien::FGReflectDR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectDR,
			Alien::FGReflectDR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectDR,
			Alien::FGReflectDR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectDR,
			Alien::FGReflectUR,
			Alien::FGReflectDR,
			Alien::FGReflectDR,
			Alien::FGReflectUR,
			Alien::FGReflectUL,
			Alien::FGReflectDL,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectUR,
			Alien::FGReflectDL,
			Alien::FGReflectUR,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimReflectDR,
			Alien::AnimReflectDR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectDR,
			Alien::AnimReflectDR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectDR,
			Alien::AnimReflectDR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectDR,
			Alien::AnimReflectUR,
			Alien::AnimReflectDR,
			Alien::AnimReflectDR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUL,
			Alien::AnimReflectDL,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectUR,
			Alien::AnimReflectDL,
			Alien::AnimReflectUR,
		};
		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		/*�f�[�^�̏�����*/

		if (auto sm = Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
		{
			sm->bClearFragmentNumMax = 1;
			++sm->bNextStage;
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
		const auto pad = JoyPad::GetState(0);
		if (kb->Now('G') == 1 || pad->NowBut(J_BUT_8) == 1)
		{
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage41::Obj>();
			Pause(2);
		}

		if (pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
