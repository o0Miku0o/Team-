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
		replayStage = "./data/demo/replay_stage.txt";
		replayFile = "./data/demo/replay.txt";
		__int64 temp = getFileSize(replayFile);
		if (temp < 1024) {
			std::string files[2] = { "./data/demo/replay_bac0.txt" ,"./data/demo/replay_bac1.txt" };
			std::string stages[2] = { "./data/demo/replay_stage_bac0.txt",  "./data/demo/replay_stage_bac1.txt" };
			//replayFile = "./data/demo/replay_bac.txt";
			//replayStage = "./data/demo/replay_stage_bac.txt";
			int random = rand() % 2;
			replayFile = files[random];
			replayStage += stages[random];
		}
		std::ifstream ifs(replayStage);
		//std::ifstream ifs("./data/demo/replay_stage.txt");
		if (!ifs)
		{
			Remove(this);
			return;
		}

		if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			int nb;
			ifs >> nb;
			sm->bStageNum = nb;

			/*����ւ�*/
			Swap(sm, this);
			///*�����I�ɓ���ւ�*/
			//auto smn = sm->next;
			//auto smp = sm->prev;
			//auto n = this->next;
			//auto p = this->prev;

			//if(p) p->next = sm;
			//else TB::top = sm;
			//if(n) n->prev = sm;
			//sm->next = n;
			//sm->prev = p;

			//if(smp) smp->next = this;
			//else TB::top = this;
			//if(smn) smn->prev = this;
			//this->next = smn;
			//this->prev = smp;
		}
		ifs.close();

		Add<StageLoad::Obj>();
		/*�f�[�^�̏�����*/
		bIsLoad = false;
		bFadeCompCnt = 0;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);
		if (kb->Down(VK_RETURN) || kb->Down(VK_RIGHT) || pad->Down(JOY_BUTTON6) || pad->Down(JOY_BUTTON2))
		{
			if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
			{
				res->wsBGM.Pause();
			}
			RemoveAll();
			Add<JecLogo::Obj>();
			return;
		}
		if (Find<StageLoad::Obj>(StageLoad::caTaskName)) return;
		if (!bIsLoad)
		{
			if (auto pl = Find<Player::Obj>(Player::caTaskName))
			{
				pl->ReplayLoad(replayFile);
				//pl->ReplayLoad("./data/demo/replay.txt");
				bIsLoad = true;
			}
		}
		else if (auto sm = Find<StageManager::Obj>(StageManager::caTaskName))
		{
			if (sm->bClearFragmentNum >= sm->bClearFragmentNumMax)
			{
				if (auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
				{
					if (fade->IsComplete())
					{
						if (bFadeCompCnt > 0)
						{
							bFadeCompCnt = 0;
							if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
							{
								res->wsBGM.Pause();
							}
							RemoveAll();
							Add<JecLogo::Obj>();
						}
						++bFadeCompCnt;
					}
				}
			}
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
	//�t�@�C���̑傫�����o�C�g�ŕԂ�
	//__int64 �� Long �^�C�v
	__int64 Obj::getFileSize(const std::string &asRepFileName) {
		struct _stati64 statbuf;
		if (_stati64(asRepFileName.c_str(), &statbuf)) return -1;
		return statbuf.st_size;
	}
}
