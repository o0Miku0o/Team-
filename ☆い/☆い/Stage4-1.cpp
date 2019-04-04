#include "Stage4-1.h"
#include "Stage4-2.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "Saturn.h"
#include "Neptune.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "StageSelect.h"

namespace Stage41
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
		SetName("�X�e�[�W�S�|�P�^�X�N");
		/*���\�[�X����*/
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");

		/*�^�X�N�̐���*/
		Add<Player::Obj>();
		Add<Saturn::Obj>();
		auto np = Add<Neptune::Obj>();
		np->rNeptune.Scaling(16.f * 30.f, 16.f * 30.f);
		np->rNeptune.SetPos(&Point(1900.f, 1000.f));


		auto fg = Add<FragmentGenerator::Obj>();
		int iColor[2] = {};
		Point pFPos[2] = { Point(500.f, Rec::Win.b*0.5f) ,Point(800.f, 150.f) };
		fg->Bridge(2, pFPos, iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange[2] = {24,24};
		Point pSPos[2] = { Point(1700.f, 400.f) ,Point(1200.f,900.f) };
		sg->Bridge(2, iChange, pSPos);

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 3;
		Point pPos[ceiNum] =
		{
			Point(1000.f, Rec::Win.b * 0.5f),
			Point(1700.f, 400.f),
			Point(700.f, 900.f),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveRotation,
			Alien::MoveRotation,
			Alien::MoveHorizontal,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectDL,
			Alien::BMReflectUR,
			Alien::BMRemove,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUL,
			Alien::FGReflectUL,
			Alien::FGReflectUL,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimRotation,
			Alien::AnimRotation,
			Alien::AnimReflectUL,
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
			Add<Stage42::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage41::Obj>();
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
