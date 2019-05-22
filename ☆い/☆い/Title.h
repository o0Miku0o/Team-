#pragma once
#include "MyGame/MyApp.h"

namespace Title
{
	const char caTaskName[] = { "�^�C�g���^�X�N" };
	const char caResName[] = { "�^�C�g�����\�[�X" };
	
	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iHo;
		Image iHoOverride;
		Image iBoshi;
		Image iBoshiOverride;
		Image iStart;

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
		Rec rHo;
		Rec rBoshi;
		Rec rStart;
		Rec rMeteo;
		Vector2 vMSpd;
		fix fZoom;
		fix fStartImgSrcY;
		fix fMSpdBase;
		fix fMScale;
		byte bAlpha;
		char cAddAlpha;
		bool bShineFlag;

		Obj() {}
		~Obj() {}
	private:
		void Init();
		void Finalize();

		void LogoInit();
		void ButtonInit();
		void MeteoInit();
		void OtherInit();

		void LogoUpdate();
		void MeteoUpdate();

		void DrawMeteo();
		void DrawLogo(RS * const rpRes, const Frec * const fpSrc);
		void DrawButton(RS * const rpRes, const Frec * const fpSrc);

		void CreateBeam();
		void CreateFragment();
		void CreateCursor();
		void CreateStar();
		void PlayBgm();
		void ButtonResize();

	public:
		void Update();
		void Render();
	}*OBJ_ptr;
	void AnimHo(byte * const bFrame, byte * const bAnim, byte * const bAnim2);
	void AnimShiBoshi(byte * const bFrame, byte * const bAnim, byte * const bAnim2);
}