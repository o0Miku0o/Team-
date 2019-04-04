#include "Stage2.h"
#include "Stage3.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "Player.h"
#include "AlienGenerator.h"
#include "Alien.h"
#include "Meteo.h"

namespace Stage2
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
		SetName("�X�e�[�W�Q�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Player::Obj>();

		auto ag = Add<AlienGenerator::Obj>();

		constexpr int ceiNum = 1;
		Point pPos[ceiNum] =
		{
			Point(1400.f, Rec::Win.b * 0.5f),
			//Point(800.f, 100.f),
			//Point(500.f, 500.f)
		};
		Alien::Move fpMove[ceiNum] =
		{
			Alien::MoveVertical,
			//Alien::MoveHorizontal,
			//Alien::MoveRotation,
		};
		Alien::Hit fpBMHit[ceiNum] =
		{
			Alien::BMRemove,
			//Alien::BMReflectUR,
			//Alien::BMReflectDR,
		};
		Alien::Hit fpFGHit[ceiNum] =
		{
			Alien::FGRemove,
			//Alien::FGReflectDR,
			//Alien::FGReflectUR,
		};
		Alien::Anim fpAnim[ceiNum] =
		{
			Alien::AnimNomal,
			//Alien::AnimNomal,
			//Alien::AnimRotation,
		};

		ag->Bridge(ceiNum, pPos, fpMove, fpBMHit, fpFGHit, fpAnim);

		//Add<Alien::Obj>();
		Add<Meteo::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		fg->Bridge(1, &Point(Rec::Win.r * 0.4f, Rec::Win.b * 0.5f), 1);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 24;
		sg->Bridge(1, &iChange, &Point(1650.f, 700.f));
		/*�f�[�^�̏�����*/

	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		if (kb->Now('T') == 1)
		{
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage3::Obj>();
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
