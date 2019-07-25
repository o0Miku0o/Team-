#pragma once
#include "MyGame/MyApp.h"

namespace Player
{
	const char caTaskName[] = { "�v���C���[�^�X�N" };
	const char caResName[] = { "�v���C���[���\�[�X" };

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
		Rec rBase;
		Rec rImgBase;
		Line lGuideLine;
		Line lGuideLineFgm;
		Point pStandardPoint;
		Point pPos;
		float fSPDist;
		float fSPAngle;
		float fPAngle;
		float fSrcX;
		bool bIsReplay;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void BeamCreateFromPad(std::shared_ptr<JoyPad> &apPad);
		void BeamCreateFromKeyBoard(std::shared_ptr<KB> &apKB);
		void BeamCreateFromReplay();
		const float GetAfterPosY(const float afSpdY);
		const float GetSpdFromKeyBoard(std::shared_ptr<KB> &apKB);
		const float GetSpdFromPad(std::shared_ptr<JoyPad> &apPad);
		const float GetSpdFromReplay();
		void ShotAngleFromKeyBoard(std::shared_ptr<KB> &apKB, float afAddAngle);
		void ShotAngleFromPad(std::shared_ptr<JoyPad> &apPad, float afAddAngle);
		void ShotAngleFromReplay();
		void ReplaySeekZero();
		void GuidLine();
	public:
		void Update();
		void Render();
		const Rep *ReplayLoad(const std::string &asRepFileName);
		void ReplayRelease();
	}*Obj_ptr;
}