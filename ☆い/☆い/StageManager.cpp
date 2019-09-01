#include "StageSelect.h"
#include "StageManager.h"
#include "Result.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "Player.h"
#include "FadeInOut.h"
#include "Back.h"
#include "StageLoad.h"
#include "TimeAttack.h"
#include "Ranking.h"
#include "Hukidasi.h"

namespace StageManager
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iStageImg.ImageCreate("./data/image/main/resource.bmp");

		tese.ImageCreate("./data/image/other/fade.bmp");

		wsTest.SoundCreate("./data/sound/������.wav");

		wsTest2.SoundCreate("./data/sound/�͂܂鉹.wav");

		wsTest3.SoundCreate("./data/sound/����鉹2.wav");

		wsTest4.SoundCreate("./data/sound/�r�[�����ˉ�2.wav");

		wsTest5.SoundCreate("./data/sound/���Г��m��������2.wav");

		wsTest6.SoundCreate("./data/sound/�Ђт�����.wav");

		wsTest7.SoundCreate("./data/sound/�e�މ�2.wav");

		wsTest8.SoundCreate("./data/sound/�X�e�[�W�ړ�.wav");

		wsTest9.SoundCreate("./data/sound/���j���[�\��1.wav");

		wsTest10.SoundCreate("./data/sound/�z�����މ�.wav");

		wsTest11.SoundCreate("./data/sound/���艹 1.wav");

		wsTest12.SoundCreate("./data/sound/�F���l�o��.wav");

		wsTest13.SoundCreate("./data/sound/���U���g.wav");

		wsBGM.CallBack(WINNAME);
		wsBGM.SoundCreate("./data/sound/BGM2.wav");

		wsBGM1.CallBack(WINNAME);
		wsBGM1.SoundCreate("./data/sound/BGM4.wav");

		wsBGM2.CallBack(WINNAME);
		wsBGM2.SoundCreate("./data/sound/BGM3.wav");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iStageImg.Release();

		wsTest.Release();

		wsTest2.Release();

		wsTest3.Release();

		wsTest4.Release();

		wsTest5.Release();

		wsTest6.Release();

		wsTest7.Release();

		wsTest8.Release();

		wsTest9.Release();

		wsTest10.Release();

		wsTest11.Release();

		wsTest12.Release();

		wsTest13.Release();

		wsBGM.Release();

		wsBGM1.Release();

		wsBGM2.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);
		/*���\�[�X����*/
		RB::Add<RS>(caResName);
		/*�^�X�N�̐���*/
		//Add<StageSelect::Obj>();
		/*�f�[�^�̏�����*/
		pTutorialPos = Point(0.f, 0.f);
		for (auto &it : bScores) it = 1;
		bClearFragmentNum = 0;
		bClearFragmentNumMax = 255;
		usBeamCount = 0;
		bStageNum = 11;
		bIsDebug = false;
		iResultCnt = 0;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		//RB::Remove("�X�e�[�W�������\�[�X");
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (auto pl = Find<Player::Obj>(Player::caTaskName))
		{
			pTutorialPos.x = pl->pPos.x + 130.f;
			pTutorialPos.y = pl->pPos.y - 130.f;
		}
		if (bClearFragmentNum >= bClearFragmentNumMax)
		{
			//���Ԃ��~�߂āI�I�I
			//�t�F�C�h�C�������t�F�C�h�A�E�g�̎��Ԃɓ���ւ�
			auto fade = Find<FadeInOut::Obj>(FadeInOut::caTaskName);
			++iResultCnt;
			if (iResultCnt == 1) {
				if (fade)
				{
					//fade->bActive = false;
					fade->Start();
					fade->bIsIn = true;
				}
				else
				{
					fade = Add<FadeInOut::Obj>();
					fade->bIsIn = true;
				}
			}
			else if (fade)//Find<FadeInOut::Obj>("�t�F�C�h�C���A�E�g�^�X�N") == nullptr)
			{
				if (fade->IsComplete())
				{
					bClearFragmentNum = 0;

					RemoveAll({ caTaskName, FadeInOut::caTaskName,TimeAttack::caTaskName }, NOT_REMOVE_NAME);
					//RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
					//Add<Back::Obj>();

					byte bStageGroup = 0, bNowStage = 0;
					bStageGroup = bStageNum / 10;
					bNowStage = bStageNum - bStageGroup * 10 - 1;
					if (usBeamCount <= bClearFragmentNumMax)
					{
						bScores.at(bNowStage) = 3;
					}
					else if (usBeamCount <= u_short(bClearFragmentNumMax * 2))
					{
						bScores.at(bNowStage) = 2;
					}

					std::ofstream ofs("./data/demo/replay_stage.txt", std::ios_base::trunc);
					if (ofs)
					{
						ofs << bStageNum;
						ofs.close();
					}

					if (bStageNum / 10 >= 7 && bStageNum - (bStageNum / 10 * 10) == 5)
					{
						if (auto ta = Find<TimeAttack::Obj>(TimeAttack::caTaskName))
						{
							ta->SaveTime();
						}
						RemoveAll();
						Add<StageManager::Obj>();
						Add<Back::Obj>();
						Add<Ranking::Obj>();
					}
					else {
						bStageNum = bNextStage;
						if (bStageNum == 255) {
							RemoveAll();

							Add<StageManager::Obj>();
							auto re = Add<Result::Obj>();
							re->SetParam(bStageGroup, bScores);
							Pause(2);
						}
						else {
							Add<StageLoad::Obj>();
						}
					}
					iResultCnt = 0;
				}
			}
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
