#include "Demo.h"
#include "JecLogo.h"
#include "StageManager.h"
#include "StageLoad.h"
#include "Player.h"
#include "FadeInOut.h"

#include <fstream>

namespace Demo
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
		RB::Add<RS>(caResName);
		/*�^�X�N�̐���*/

		RemoveAll({ Demo::caTaskName }, NOT_REMOVE_NAME);

		std::ifstream ifs("./data/demo/replay_stage.txt");
		if (!ifs) return;
		auto sm = Add<StageManager::Obj>();
		ifs >> sm->bStageNum;
		ifs.close();

		Add<StageLoad::Obj>();
		/*�f�[�^�̏�����*/
		bIsLoad = false;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (Find<StageLoad::Obj>(StageLoad::caTaskName)) return;
		if (!bIsLoad)
		{
			if (auto pl = Find<Player::Obj>(Player::caTaskName))
			{
				pl->ReplayLoad("./data/demo/replay.txt");
				bIsLoad = true;
			}
		}
		else if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			if (sm->bClearFragmentNum >= sm->bClearFragmentNumMax)
			{
				if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
				{
					if (!fade->bIsIn)
					{
						RemoveAll();
						Add<JecLogo::Obj>();
					}
				}
			}
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
