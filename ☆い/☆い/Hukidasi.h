#pragma once
#include "MyGame/MyApp.h"

namespace Hukidasi
{
	enum PictureGroup
	{
		GROUP_UP,
		GROUP_DOWN,
	};
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
		PictureGroup pGroup;
		StageGroup sGroup;
		Rec rHukidasi;
		Point pFontPos[2];
		float fAddScale;
		float fWidthMax;
		float fHeightMax;
		byte bSetPictureCount;
			
		RS_ptr res;
		void Init();
		void Finalize();

		void Resize();
	public:
		void Update();
		void Render();

		void SetAddScale(const float afAddScale);
		void SetScaleMax(const float afWMax, const float afHMax);
		void SetPos(const Point * const appPos);
		void SetStagePicture(const unsigned int auiStageNumber, const Frec * const apfrPosSize);
		void SetStageGroup(const PictureGroup apStageGroup, const StageGroup asStageGroup);
	}*OBJ_ptr;
}