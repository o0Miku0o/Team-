#include "Stage5-2.h"
#include "Stage5-3.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "Jupitor.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "BlackHoleGenerator.h"
#include "StageSelect.h"

//#include "BlackHole.h"

namespace Stage52
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
		SetName("�X�e�[�W�T�|�Q�^�X�N");
		/*���\�[�X����*/
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");

		/*�^�X�N�̐���*/
		Add<Player::Obj>();
		//Add<BlackHole::Obj>();

		auto np = Add<Jupitor::Obj>();
		np->rJupitor.Scaling(16.f * 18.f, 16.f * 18.f);
		np->rJupitor.SetPos(&Point(1550.f, 540.f));


		auto fg = Add<FragmentGenerator::Obj>();
		int iColor = 0;
		fg->Bridge(1, &Point(500.f, 600.f), &iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		sg->Bridge(1, &iChange, &Point(1550.f, 260.f));

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 1;
		Point pPos[ceiNum] =
		{
			Point(1000.f, 850.f),
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveHorizontal,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMReflectUR,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGReflectUR,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimReflectUR,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		auto bf = Add<BlackHoleGenerator::Obj>();
		float fSize = 400.f;
		const int ciMode = 0;
		bf->Bridge(1, &Point(Rec::Win.r*0.3f, Rec::Win.b*0.3f), &fSize, &ciMode);
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
			Add<Stage53::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage52::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
