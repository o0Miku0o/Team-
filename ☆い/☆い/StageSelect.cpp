#include "StageSelect.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Cursor.h"
#include "Hukidasi.h"
#include "StageLoad.h"


namespace StageSelect
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
		SetName(caTaskName);
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<StageSelectObjGalaxy::Obj>();
		Add<StageSelectObjBH::Obj>();
		Add<StageSelectObjAsteroid::Obj>();
		auto es = Add<StageSelectObjEarth::Obj>();
		Add<StageSelectObjUS::Obj>();
		Add<Hukidasi::Obj>();
		auto cs = Add<Cursor::Obj>();
		//cs->pPos = es->rEarth.GetPos();
		cs->rCursorBase.SetPos(&es->rEarth.GetPos());

		/*�f�[�^�̏�����*/
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			res->wsBGM.Restart();
		}
		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			sm->bStageNum = 11;

		}
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		//tamesi
		const auto kb = KB::GetState();
		if (kb->Down('O'))
		{
			RemoveAll(StageManager::caTaskName, NOT_REMOVE_NAME);
			Add<StageLoad::Obj>();
			Pause(2);
			return;
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
