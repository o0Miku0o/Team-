#include "StageSelectObjGalaxy.h"
#include "StageManager.h"

namespace StageSelectObjGalaxy
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
		SetName("��̓^�X�N");
		/*���\�[�X����*/
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rGalaxy = Rec(950, 600 - 200.f, 16 * 10, 16 * 10);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		//rGalaxy.SetDeg(rGalaxy.GetDeg() + 3);

	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X"))
		{
			Frec src(16.f * (iAnimCount + 45), 16, 16, 16);

			if (i >= 15)
			{
				i = 0;
				iAnimCount = (iAnimCount + 2) % 8;
			}
			++i;
			rGalaxy.Draw(&res->iStageImg, &src);
		}
	}
}
