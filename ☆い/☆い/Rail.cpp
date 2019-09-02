#include "Rail.h"

namespace Rail
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iRailImg.ImageCreate("./data/image/main/rail.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iRailImg.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);
		/*���\�[�X����*/
		RB::Add<Rail::RS>(caResName);
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		SetRenderPriority(0.1f);

		rRailBase = Rec(100.f, Rec::Win.b * 0.5f, 16.f * 2.f, 880.f/*1080 - 200*/);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove(caResName);
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{

	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<Rail::RS>(caResName))
		{
			rRailBase.Draw(&res->iRailImg, &Frec(0.f, 0.f, 16.f, 96.f));
		}
	}
}
