#include "Stage3-1.h"
#include "Stage3-2.h"
#include "StageSelect.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"

namespace Stage31
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
		SetName("�X�e�[�W�R�|�P�^�X�N");
		/*���\�[�X����*/
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");
		/*�^�X�N�̐���*/
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(500.f, 700.f), &iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		//auto sg = Add<BreakStarGenerator::Obj>();
		//int iChange = 25;
		sg->Bridge(1, &iChange, &Point(1500.f, 200.f));

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 3;
		Point pPos[ceiNum] =
		{
			Point(1300.f, Rec::Win.b * 0.5f),
			Point(1700.f, Rec::Win.b * 0.5f),
			Point(800.f, 400.f)
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveVertical,
			Alien::Move_Vertical,
			Alien::MoveHorizontal,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUL,
			Alien::BMReflectDL,
			Alien::BMReflectDL,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUL,
			Alien::FGReflectDR,
			Alien::FGReflectUL,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimNormal,
			Alien::AnimNormal,
			Alien::AnimHorizontal,
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
		const auto pad = JoyPad::GetState(0);
		if (kb->Now('G') == 1 || pad->NowBut(J_BUT_8) == 1)
		{
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage32::Obj>();
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
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(16.f * 0.f, 0.f, 16.f, 16.f));
		}
	}
}
