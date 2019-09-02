#pragma once
#include "MyGame/MyApp.h"
#include "StageSelectIcon.h"

namespace Hukidasi
{
	const char caTaskName[] = { "�����o���^�X�N" };
	const char caResName[] = { "�����o�����\�[�X" };

	enum StageGroup
	{
		GROUP_EARTH,
		GROUP_ASTEROID,
		GROUP_GALAXY,
		GROUP_URANUS,
		GROUP_BLACKHOLE
	};
	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iTextImg;

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
		Rec rHukidasi;
	private:
		StageSelectIcon::Type sGroup;
		float faWidth[StageSelectIcon::Type::TYPEMAX];
		float fAddScale;
		float fWidthMax;
		float fHeightMax;
		byte bSetPictureCount;

		RS_ptr res;
		void Init();
		void Finalize();

	public:
		Rec rTextBox;
		void Update();
		void Render();

		void Resize();
		void SetAddScale(const float afAddScale);
		void SetScaleMax(const float afWMax, const float afHMax);
		void SetPos(const Point * const appPos);
		void SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize);
		void SetStageGroup(const StageSelectIcon::Type asStageGroup);
	}*Obj_ptr;
}