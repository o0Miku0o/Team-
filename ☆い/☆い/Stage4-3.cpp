#include "Stage4-3.h"
#include "Stage5-1.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "Neptune.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "MeteoGenerator.h"
#include "StageSelect.h"


namespace Stage43
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
		SetName("�X�e�[�W�S�|�R�^�X�N");
		/*���\�[�X����*/
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");

		/*�^�X�N�̐���*/
		Add<Player::Obj>();
		auto np = Add<Neptune::Obj>();
		np->rNeptune.Scaling(16.f * 13.f, 16.f * 13.f);
		np->rNeptune.SetPos(&Point(700.f, 850.f));

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor[2] = {};
		Point pFPos[2] = { Point(600.f, 300.f) ,Point(700.f, 650.f) };
		fg->Bridge(2, pFPos, iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange[3] = { 23,22,23 };
		Point pSPos[3] = { Point(1700.f, 200.f) ,Point(1600.f, 600.f),Point(1200.f, 900.f) };
		sg->Bridge(3, iChange, pSPos);

		auto bs = Add<BreakStarGenerator::Obj>();
		int iChange4 = 25;
		bool bBSMode = false;
		bs->Bridge(1, &iChange4, &Point(1250.f, 400.f),&bBSMode);

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 1;
		Point pPos[ceiNum] =
		{
			Point(600.f, 250.f),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveRotation,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUL,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUL,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimRotation,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		auto met = Add<MeteoGenerator::Obj>();
		met->Bridge(1, &Point(Rec::Win.r, -300), &Vector2(0.f, 15.f));
		/*�f�[�^�̏�����*/

		if (auto sm = Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
		{
			sm->usBeamCount = 0;
			sm->bClearFragmentNumMax = 7;
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
			Add<Stage51::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage43::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
