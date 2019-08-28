#include "StagePicture.h"

namespace StagePicture
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
		SetRenderPriority(0.5f);
		/*�܂��摜�͓ǂݍ��܂�Ă��܂���B*/
		bIsLoaded = false;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		if (!bIsLoaded) return;
		iStageImg.Release();
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{

	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (bIsLoaded)
		{
			rPictureBase.Draw(&iStageImg, false);
		}
#ifdef _DEBUG
		rPictureBase.SetColor(RGB(255, 0, 0));
		rPictureBase.Draw();
#endif
	}
	void Obj::LoadImg(const unsigned int auiStageNumber)
	{
		if (bIsLoaded) return;
		std::string sImgName = "./data/image/other/Stage/st";
		sImgName += std::to_string(auiStageNumber);
		sImgName += ".bmp";
		iStageImg.ImageCreate(sImgName.c_str());
		bIsLoaded = true;

	}
	void Obj::SetSize(const float afWidth, const float afHeight)
	{
		rPictureBase.Scaling(afWidth, afHeight);
	}
	void Obj::SetPos(const Point * const appPos)
	{
		rPictureBase.SetPos(appPos);
	}
}
