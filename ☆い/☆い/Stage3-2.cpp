#include "Stage3-2.h"
#include "Stage3-3.h"
#include "StageSelect.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"

namespace Stage32
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
		SetName("�X�e�[�W�R�|�Q�^�X�N");
		/*���\�[�X����*/
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");
		/*�^�X�N�̐���*/
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(800.f, Rec::Win.b*0.5f), &iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		//auto sg = Add<BreakStarGenerator::Obj>();
		//int iChange = 25;
		sg->Bridge(1, &iChange, &Point(1350.f, 800.f));

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 6;
		Point pPos[ceiNum] =
		{
			Point(1000.f, Rec::Win.b * 0.5f),
			Point(600.f, Rec::Win.b * 0.5f),
			Point(600.f, 1100.f),
			Point(1600.f, 800.f),
			Point(1600.f, 250.f),
			Point(600.f, 0.f)
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::Move_Rotation,
			Alien::MoveRotation,
			Alien::MoveRotation,
			Alien::MoveVertical,
			Alien::Move_Vertical,
			Alien::Move_Horizontal,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUR,
			Alien::BMReflectDL,
			Alien::BMReflectUL,
			Alien::BMReflectDR,
			Alien::BMReflectDR,
			Alien::BMReflectDL,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUR,
			Alien::FGReflectDL,
			Alien::FGReflectUL,
			Alien::FGReflectUR,
			Alien::FGReflectDR,
			Alien::FGReflectDL,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimRotation,
			Alien::AnimRotation,
			Alien::AnimRotation,
			Alien::AnimNormal,
			Alien::AnimNormal,
			Alien::AnimHorizontal,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		/*�f�[�^�̏�����*/

		if (auto sm = Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
		{
			sm->usBeamCount = 0;
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
			Add<Stage33::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage32::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
