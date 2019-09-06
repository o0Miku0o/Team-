#include "TimeAttack.h"
#include "FadeInOut.h"
#include <fstream>

//�^�C���A�^�b�N�Ŏg���^�X�N�ł�
//�J�E���g���Ȃ�������܂�
namespace TimeAttack
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
		SetRenderPriority(1.f);
		iTimeCnt = 0;
		iFrameCnt = 0;
		width = 50.f * 1.2f;
		height = 100.f * 1.2f;
		pos = Point(Rec::Win.r * 0.8f + width, Rec::Win.t + height - 30);
		str = "00:00";
		timeMsg.SetMsg(str);
		timeMsg.Color(RGB(255, 150, 150));
		bIsSaved = false;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		SaveTime();
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		auto kb = KB::GetState();
		if (auto fi = Find<FadeInOut::Obj>(FadeInOut::caTaskName))
		{
			if (fi->IsComplete() == false)
			{
				return;
			}
		}

		if (iFrameCnt >= 60 || kb->On('A'))
		{
			iFrameCnt = 0;
			iTimeCnt++;
			std::string mn = (iTimeCnt / 60) < 10 ? "0" + std::to_string(iTimeCnt / 60) : std::to_string(iTimeCnt / 60);
			std::string sc = (iTimeCnt % 60) < 10 ? "0" + std::to_string(iTimeCnt % 60) : std::to_string(iTimeCnt % 60);
			str = mn + ":" + sc;
			timeMsg.SetMsg(str);
		}
		iFrameCnt++;
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		timeMsg.DrawAscii(pos, width, height);
	}
	void Obj::SaveTime()
	{
		if (bIsSaved)return;
		std::ofstream off("./data/ta_data/ta.txt", std::ios_base::app);
		if (!off)return;
		off << iTimeCnt << "\n";
		off.close();
		bIsSaved = true;
	}
}