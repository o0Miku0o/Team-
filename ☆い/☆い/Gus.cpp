#include "Gus.h"
#include "Title.h"
#include "StageManager.h"

//�f�ނ�4(���)�~2(�A�j���[�V��������)
//�ʒu�͑���87����
//�����_���ŏo���悤�ɂ�����
//�^�C�g�����X�e�[�W�Ŏg����悤�ɂ�����
namespace Gus
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
		SetName("�K�X�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/

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
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			rGus.Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		}
		
	}
}
