#include "Stage2-3.h"
#include "Stage3-1.h"
#include "StageSelect.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "MeteoGenerator.h"
#include "Alien.h"

namespace Stage23
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
		SetName("�X�e�[�W�Q�|�R�^�X�N");
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
		sg->Bridge(1, &iChange, &Point(1500.f, Rec::Win.b*0.5f));

		auto met = Add<MeteoGenerator::Obj>();
		Point pPos[2] = { Point(Rec::Win.r*0.4f, Rec::Win.t - 300),Point(Rec::Win.r*0.6f, Rec::Win.b + 300) };
		Vector2 vSpd[2] = { Vector2(0.f, 12.f) ,Vector2(0.f, -12.f) };
		met->Bridge(2, pPos, vSpd);
		//auto ag = Add<AlienGenerator::Obj>();

		//constexpr int ceiNum = 3;
		//Point pPos[ceiNum] =
		//{
		//	Point(1100.f, Rec::win.b * 0.5f),
		//	Point(800.f, 100.f),
		//	Point(500.f, 500.f)
		//};
		//Alien::Move fpMove[ceiNum] =
		//{
		//	Alien::MoveStay,
		//	Alien::MoveStay,
		//	Alien::MoveStay,
		//};
		//Alien::Hit fpBMHit[ceiNum] =
		//{
		//	Alien::BMRemove,
		//	Alien::BMReflectUR,
		//	Alien::BMReflectDR,
		//};
		//Alien::Hit fpFGHit[ceiNum] =
		//{
		//	Alien::FGReflectUR,
		//	Alien::FGReflectDR,
		//	Alien::FGReflectUR,
		//};
		//Alien::Anim fpAnim[ceiNum] =
		//{
		//	Alien::AnimNomal,
		//	Alien::AnimNomal,
		//	Alien::AnimNomal,
		//};

		//ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

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
			Add<Stage31::Obj>();
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
