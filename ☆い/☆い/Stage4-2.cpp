#include "Stage4-2.h"
#include "Stage4-3.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "MeteoGenerator.h"
#include "StageSelect.h"
#include "Back.h"

namespace Stage42
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
		SetName("�X�e�[�W�S�|�Q�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Back::Obj>();
		Add<Player::Obj>();

		auto met = Add<MeteoGenerator::Obj>();
		met->Bridge(1, &Point(1300.f, -300.f), &Vector2(0.f, 12.f));
	
		auto sg = Add<StarGenerator::Obj>();
		int iChange[3] = { 23,23,24 };
		Point pSPos[3] = { Point(1600.f, 200.f) ,Point(1600.f, 880.f) ,Point(1600.f,540.f) };
		sg->Bridge(3, iChange, pSPos);

		auto bs = Add<BreakStarGenerator::Obj>();
		int iChange4 = 25;
		bool bBSMode = false;
		bs->Bridge(1, &iChange4, &Point(600.f, 540.f),&bBSMode);
	
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
			Add<Stage43::Obj>();
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
