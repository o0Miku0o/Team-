#pragma once
#include "MyGame/MyApp.h"

namespace StagePicture
{
	const char caTaskName[] = { "�X�e�[�W�s�N�`���[�^�X�N" };
	const char caResName[] = { "�X�e�[�W�s�N�`���[���\�[�X" };

	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*�^�X�N�I�u�W�F�N�g�N���X*/
	typedef class Obj : public TaskBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/

		Obj() {}
		~Obj() {}
	private:
		Image iStageImg;
		Rec rPictureBase;
		bool bIsLoaded;

		RS_ptr res;
		void Init();
		void Finalize();

	public:
		void Update();
		void Render();

		/*�X�e�[�W�̉摜�ǂݍ��݁B�p�X��./data/image/other/Stage/st(auiStageNumber �X�e�[�W�̔ԍ�).bmp�ɂȂ�B*/
		void LoadImg(const unsigned int auiStageNumber);
		/*�T�C�Y����*/
		void SetSize(const float afWidth, const float afHeight);
		/*���W����*/
		void SetPos(const Point * const appPos);
	}*Obj_ptr;
}