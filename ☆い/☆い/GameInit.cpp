#include "GameInit.h"
#include "StageManager.h"
#include "Back.h"
#include "Title.h"

namespace GameInit
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
		SetName("�Q�[���J�n�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<StageManager::Obj>();
		Add<Back::Obj>();
		Add<Title::Obj>();
		Remove(this);
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
