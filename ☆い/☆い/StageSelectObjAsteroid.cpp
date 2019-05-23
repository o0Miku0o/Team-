#include "StageSelectObjAsteroid.h"
#include "StageManager.h"

namespace StageSelectObjAsteroid
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

		/*�f�[�^�̏�����*/
		rAsteroid = Rec(650, 400 - 200.f, 16 * 10, 16 * 10);
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
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iAnimCount + 41), 16, 16, 16);

			if (i >= 13)
			{
				i = 0;
				iAnimCount = (iAnimCount + 1) % 4;
			}
			++i;
			rAsteroid.Draw(&res->iStageImg, &src, true);
		}
	}
}
