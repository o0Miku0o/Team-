#include "Stage1-2.h"
#include "Stage1-3.h"
#include "StageSelect.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "Meteo.h"
#include "StageManager.h"

namespace Stage12
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
		SetName("�X�e�[�W�P�|�Q�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Player::Obj>();

		//auto ag = Add<AlienGenerator::Obj>();

		//constexpr int ceiNum = 1;
		//Point pPos[ceiNum] =
		//{
		//	Point(1400.f, Rec::Win.b * 0.5f),
		//	//Point(800.f, 100.f),
		//	//Point(500.f, 500.f)
		//};
		//Alien::Move fpMove[ceiNum] =
		//{
		//	Alien::MoveVertical,
		//	//Alien::MoveHorizontal,
		//	//Alien::MoveRotation,
		//};
		//Alien::Hit fpBMHit[ceiNum] =
		//{
		//	Alien::BMRemove,
		//	//Alien::BMReflectUR,
		//	//Alien::BMReflectDR,
		//};
		//Alien::Hit fpFGHit[ceiNum] =
		//{
		//	Alien::FGRemove,
		//	//Alien::FGReflectDR,
		//	//Alien::FGReflectUR,
		//};
		//Alien::Anim fpAnim[ceiNum] =
		//{
		//	Alien::AnimNomal,
		//	//Alien::AnimNomal,
		//	//Alien::AnimRotation,
		//};

		//ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		//Add<Alien::Obj>();
		//Add<Meteo::Obj>();

		//auto fg = Add<FragmentGenerator::Obj>();
		//fg->Bridge(1, &Point(Rec::Win.r * 0.4f, Rec::Win.b * 0.5f), 1);
		//auto sg = Add<StarGenerator::Obj>();
		//int iChange = 24;
		//sg->Bridge(1, &iChange, &Point(1650.f, 700.f));
		auto fg = Add<FragmentGenerator::Obj>();
		Point pFgArr[3] = { Point(500.f,250.f),Point(800.f,550.f),Point(1200.f,700.f) };
		int iColor[3] = {};
		fg->Bridge(3, pFgArr, iColor);
		auto sg = Add<StarGenerator::Obj>();
		Point pStArr[2] = { Point(1500.f,400.f),Point(1200.f,900.f) };
		int iArr[2] = { 24,23 };
		sg->Bridge(2, iArr, pStArr);
		/*�f�[�^�̏�����*/
		if (auto sm = Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
		{
			sm->usBeamCount = 0;
			sm->bClearFragmentNumMax = 3;
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
			Add<Stage13::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage12::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
