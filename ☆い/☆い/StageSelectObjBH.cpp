#include "StageSelectObjBH.h"
#include "StageManager.h"

namespace StageSelectObjBH
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
		SetName("�u���b�N�z�[���n�у^�X�N");
		/*���\�[�X����*/
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rBH = Rec(1500, 600 - 200.f, 16 * 10, 16 * 10);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		//rBH.SetDeg(rBH.GetDeg() + 4);
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			Frec src(16.f * (iAnimCount + 53), 16, 16, 16);

			if (i >= 15)
			{
				i = 0;
				iAnimCount = (iAnimCount + 2) % 8;
			}
			++i;
			rBH.Draw(&res->iStageImg, &src);
		}
	}
}
