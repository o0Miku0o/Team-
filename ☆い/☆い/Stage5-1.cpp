#include "Stage5-1.h"
#include "Stage5-2.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "StageManager.h"
#include "Player.h"
#include "BlackHoleGenerator.h"
#include "StageSelect.h"

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
		RB::Add<StageManager::RS>("�X�e�[�W�������\�[�X");

		/*�^�X�N�̐���*/
		Add<Player::Obj>();
		//Add<BlackHole::Obj>();

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

		if (auto sm = Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
		{
			sm->usBeamCount = 0;
			sm->bClearFragmentNumMax = 2;
			sm->bNextStage = 14;
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
			Add<Stage52::Obj>();
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
