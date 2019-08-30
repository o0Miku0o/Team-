#include "Tips.h"
#include "StagePicture.h"	
#include "StageManager.h"

//Tips�^�X�N
//�X�N�V�������H����bmp�摜��\��
namespace Tips
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		//iTips.ImageCreate("./data/image/other/Tips/.bmp");
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

		rBack = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, Rec::Win.r, Rec::Win.b);
		rGuideBase = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.5f, 16.f * 75.f, 16.f * 55.f);
		rTips = Rec(Rec::Win.r * 0.5f, Rec::Win.b * 0.57f, 16.f * 62.5f, 16.f * 37.5f);
		LoadImg(1);
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
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			rBack.Draw(&res->iStageImg, &Frec(16.f, 0.f, 16.f, 16.f));
		}
		if (auto res = RB::Find<Tips::RS>(caResName))
		{
			rGuideBase.Draw(&res->iGuideBase, &Frec(0.f, 0.f, 64.f, 80.f));
		}
		if (bIsLoaded)
		{
			rTips.Draw(&iTips, false);
		}
	}
	void Obj::LoadImg(const unsigned int auiStageNumber)
	{
		if (bIsLoaded) return;
		std::string sImgName = "./data/image/other/Tips/Tips(";
		sImgName += std::to_string(auiStageNumber);
		sImgName += ").bmp";
		iTips.ImageCreate(sImgName.c_str());
		bIsLoaded = true;

	}
}
