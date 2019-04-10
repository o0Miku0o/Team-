#include "Stage5-1.h"
#include "Stage5-2.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "BlackHoleGenerator.h"
#include "StageSelect.h"
#include "Back.h"

//#include "BlackHole.h"

namespace Stage51
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
		SetName("�X�e�[�W�T�|�P�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Back::Obj>();
		Add<Player::Obj>();

		auto fg = Add<FragmentGenerator::Obj>();
		int iColor[2] = {};
		Point pFPos[2] = { Point(500.f, 200.f) ,Point(500.f, 800.f) };
		fg->Bridge(2, pFPos, iColor);

		auto sg = Add<StarGenerator::Obj>();
		int iChange = 23;
		sg->Bridge(1, &iChange, &Point(1700.f, 540.f));

		auto bf = Add<BlackHoleGenerator::Obj>();
		float fSize = 250.f;
		const int ciMode = 0;
		bf->Bridge(1, &Point(Rec::Win.r*0.5f, Rec::Win.b*0.5f), &fSize, &ciMode);

		/*�f�[�^�̏�����*/

		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			res->wsBGM.Restart();
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
			if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
			Add<Stage52::Obj>();
			Pause(2);
		}

		if (pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
			{
				res->wsBGM.Pause();
			}
			Add<Back::Obj>();
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
