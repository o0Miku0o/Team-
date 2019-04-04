#include "Stage1.h"
#include "Stage2.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"

namespace Stage1
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
		fg->Bridge(1, &Point(500.f, 400.f), 2);
		//auto sg = Add<StarGenerator::Obj>();
		//int iChange = 24;
		auto sg = Add<BreakStarGenerator::Obj>();
		int iChange = 25;
		sg->Bridge(1, &iChange, &Point(500.f, 400.f));

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
			Add<Stage2::Obj>();
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
