#include "StageSelect.h"
#include "StageManager.h"
#include "BeamGenerator.h"
#include "Beam.h"
#include "Player.h"

namespace StageManager
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iStageImg.ImageCreate("./data/image/main/resource.bmp");
	
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

		wsBGM.CallBack(WINNAME);
		wsBGM.SoundCreate("./data/sound/BGM2.wav");
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

		wsBGM.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName("�X�e�[�W�����^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�X�e�[�W�������\�[�X");
		/*�^�X�N�̐���*/
		//Add<StageSelect::Obj>();
		/*�f�[�^�̏�����*/

	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		//RB::Remove("�X�e�[�W�������\�[�X");
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
			Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b).Draw(&res->iStageImg, &Frec(0.f, 0.f, 16.f, 16.f));
		}
	}
}
