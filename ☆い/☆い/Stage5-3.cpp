#include "Stage5-3.h"
#include "Stage5-1.h"
#include "StarGenerator.h"
#include "BreakStarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "StageSelect.h"
#include "Back.h"

namespace Stage53
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
		SetName("�X�e�[�W�T�|�R�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Back::Obj>();
		Add<Player::Obj>();
		//�������T��
		auto bs = Add<BreakStarGenerator::Obj>();
		int iChange[6] = { 36,36,36,36,36,25 };
		Point pBPos[6] = { Point(600.f, 0.f),Point(700.f,1080.f),Point(1600.f, 540.f),Point(1920.f, 0.f), Point(1900.f, 1000.f) ,Point(600.f, 540.f) };
		bool bBSMode[6] = { true,true, true, true, true, false };
		bs->Bridge(6, iChange, pBPos,bBSMode);

		//���鐯

		//�ړI�̐�
		auto sg = Add<StarGenerator::Obj>();
		int iChange3[2] = { 22,23 };
		Point pSPos[2] = { Point(1200.f, 850.f),Point(1100.f, 200.f) };
		sg->Bridge(2, iChange3, pSPos);

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
			Add<StageSelect::Obj>();
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
