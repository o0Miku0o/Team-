#pragma once
#include "MyGame/MyApp.h"

namespace FadeInOut
{
	const char caTaskName[] = { "�t�F�C�h�C���A�E�g�^�X�N" };
	const char caResName[] = { "�t�F�C�h�C���A�E�g���\�[�X" };

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
		bool bIsIn;			//�C�����A�E�g������

		Obj() {}
		~Obj() {}
	private:
		Rec rSquere[4];			//�t�F�C�h�C���A�E�g�p�̊p���ɔz�u
		float fSize;		//��`�̑傫��
		float fSizeValue;	//fSize�̕ω���
		bool bActive;		//�N���t���O

		Rec rStar;
		float fStarSize;
		float fStarSizeValue;
		
		float fStarSizeMax;
		float fStarSizeMin;

		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();

		/*��*/
		void Start();
		void Stop();
		const bool IsComplete() const;
	}*Obj_ptr;
}