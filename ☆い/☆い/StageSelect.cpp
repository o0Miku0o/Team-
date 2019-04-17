#include "StageSelect.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Cursor.h"

//tamesi
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
		SetName("�X�e�[�W�I���^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<StageSelectObjGalaxy::Obj>();
		Add<StageSelectObjBH::Obj>();
		Add<StageSelectObjAsteroid::Obj>();
		Add<StageSelectObjEarth::Obj>();
		Add<StageSelectObjUS::Obj>();
		auto cs = Add<Cursor::Obj>();
		cs->rCursorBase.SetPos(&Point(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f));

		rHukidasi = Rec();
		rTongari = Rec();

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
		//tamesi
		const auto kb = KB::GetState();
		if (kb->Now('O') == 1)
		{
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageLoad::Obj>();
			Pause(2);
			return;
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		rHukidasi.Draw();
		rTongari.Draw();
	}
}
