#include "StageSelect.h"
#include "StageManager.h"
#include "StageSelectObjUS.h"
#include "StageSelectObjEarth.h"
#include "StageSelectObjGalaxy.h"
#include "StageSelectObjBH.h"
#include "StageSelectObjAsteroid.h"
#include "Cursor.h"


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

		/*�f�[�^�̏�����*/

	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{

	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
