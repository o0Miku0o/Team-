#include "Tips.h"
//Tips�^�X�N
//�X�N�V�������H����bmp�񂐉摜��\��
namespace Tips
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		//iTips.ImageCreate("./data/image/other/.bmp");
		iGuideBase.ImageCreate("./data/image/other/GuideBook.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iGuideBase.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);

		/*���\�[�X����*/
		RB::Add<Tips::RS>(caResName);

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rGuideBase = Rec(Rec::Win.r * 0.5f, 700.f, 16.f * 95.f, 16.f * 100.f);

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
		if (auto res = RB::Find<Tips::RS>(caResName))
		{
			rGuideBase.Draw(&res->iGuideBase, &Frec(0.f, 0.f, 64.f, 80.f), true);
		}
	}
}
