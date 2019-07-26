#include "StageSelect.h"
#include "StageManager.h"
//<<<<<<< HEAD
//#include "StageSelectObjUS.h"
//#include "StageSelectObjEarth.h"
//#include "StageSelectObjGalaxy.h"
//#include "StageSelectObjBH.h"
//#include "StageSelectObjAsteroid.h"
//=======
#include "StageSelectIcon.h"
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
//<<<<<<< HEAD
//		/*���\�[�X����*/
//
//		/*�^�X�N�̐���*/
//		Add<StageSelectObjGalaxy::Obj>();
//		Add<StageSelectObjBH::Obj>();
//		Add<StageSelectObjAsteroid::Obj>();
//		auto es = Add<StageSelectObjEarth::Obj>();
//		Add<StageSelectObjUS::Obj>();
//		Add<Hukidasi::Obj>();
//		auto cs = Add<Cursor::Obj>();
//		//cs->pPos = es->rEarth.GetPos();
//		cs->rCursorBase.SetPos(&es->rEarth.GetPos());
//=======

		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		auto earth = Add<StageSelectIcon::Obj>();
		earth->type = StageSelectIcon::Type::ET;
		earth->rIcon.SetPos(&Point(400.f, 400.f));
		
		auto icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::MT;
		icon->rIcon.SetPos(&Point(650.f, 200.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::GL;
		icon->rIcon.SetPos(&Point(950.f, 400.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::US;
		icon->rIcon.SetPos(&Point(1250.f, 200.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::BH;
		icon->rIcon.SetPos(&Point(1500.f, 400.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::FR;
		icon->rIcon.SetPos(&Point(650.f, 600.f));

		icon = Add<StageSelectIcon::Obj>();
		icon->type = StageSelectIcon::Type::TA;
		icon->rIcon.SetPos(&Point(1250.f, 600.f));

		Add<Hukidasi::Obj>();
		auto cs = Add<Cursor::Obj>();
		cs->rCursorBase.SetPos(&earth->rIcon.GetPos());

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