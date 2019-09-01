#include "MiniGame.h"
#include "Fragment.h"
#include "Star.h"
#include "Beam.h"
#include <fstream>

//�~�j�Q�[���Ŏg���^�X�N�ł�
//�J�E���g���Ȃ�������܂�
namespace MiniGame
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iButton.ImageCreate("./data/image/other/button.bmp");
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
		RB::Add<MiniGame::RS>(caResName);
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		SetRenderPriority(1.f);
		std::ifstream ifs("./data/log/log.txt");
		score = 0;
		if (ifs)
		{
			ifs >> score;
			ifs.close();
		}
		str[0] = "Your Score:";
		str[1] = "High Score:";
		myMsg.SetMsg(str[0]);
		myMsg.Color(RGB(255, 255, 255));
		highMsg.Color(RGB(255, 255, 255));
		width = 50.f;
		height = 100.f;
		pos1 = Point(Rec::Win.r*0.1f + width, Rec::Win.t + height - 30);
		pos2 = Point(pos1.x + width * str[0].length() + width * 6, Rec::Win.t + height - 30);
		rButton = Rec(1820.f, 980.f, 16.f * 11.f, 16.f * 11.f);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		if (score < fFragmentCnt)
		{
			std::ofstream ofs;
			ofs.open("./data/log/log.txt", std::ios_base::trunc);
			if (ofs)
			{
				ofs << fFragmentCnt;
				ofs.close();
			}
		}
		myMsg.Close();
		highMsg.Close();
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		auto pd = JoyPad::GetState(0);
		if (pd->Down(JOY_BUTTON6))
		{
			if (score < fFragmentCnt)
			{
				std::ofstream ofs;
				ofs.open("./data/log/log.txt", std::ios_base::trunc);
				if (ofs)
				{
					ofs << fFragmentCnt;
					ofs.close();
				}
			}
			myMsg.Close();
			highMsg.Close();
			std::ifstream ifs("./data/log/log.txt");
			if (ifs)
			{
				ifs >> score;
				ifs.close();
			}
			{
				float prefFragCnt = fFragmentCnt;
				auto fr = FindAll<Fragment::Obj>(Fragment::caTaskName);
				for (auto vf : fr)
				{
					if (vf->bMoveActive)
					{
						fFragmentCnt = prefFragCnt;
					}
					else
					{
						fFragmentCnt = 0;
					}
				}
			}
		}
		myMsg.SetMsg(str[0] + std::to_string((int)fFragmentCnt));
		highMsg.SetMsg(str[1] + std::to_string(score));
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		myMsg.DrawAscii(pos1, width, height);
		highMsg.DrawAscii(pos2, width, height);
		if (auto s = RB::Find<MiniGame::RS>(MiniGame::caResName))
		{
			rButton.Draw(&s->iButton, &Frec(16.f * 13.f, 0.f, 16.f, 16.f), true);
		}
	}
}