#pragma once
#include "MyGame/MyApp.h"

namespace Tutorial
{
	const char caTaskName[] = { "�`���[�g���A���^�X�N" };
	const char caResName[] = { "�`���[�g���A�����\�[�X" };

	enum Ttl_State
	{
		TTS_BUTTON,
		TTS_STICK,
	};
	enum Buttons
	{
		//4��
		BTN_B,
		BTN_Y,
		BTN_R,
		BTN_L,
		BTN_MAX
	};
	enum Btn_State
	{
		BS_UP,
		BS_DOWN,
	};
	enum Stk_State
	{
		STS_NEUTRAL,
		STS_UP,
		STS_DOWN,
		STS_MAX
	};
	struct TtlButton
	{
		Buttons bBtn;
		Btn_State bState;
	};

	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iTutoImg;

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
		Rec rTutoBase;
		Rec rEfBase;
		int iaStickState[4];
		TtlButton tBtn;
		Ttl_State tState;
		u_int uiStickStateCount;
		const Point *cppTarget;
		u_int uiLifeCount;
		int iOfsStickState;
		byte bAnimCount;
		bool bEfVisible;

		void Init();
		void Finalize();
	public:
		void Update();
		void Render();

		void SetParam(const unsigned int auiInitLife, const Ttl_State atState, const unsigned int auiBNumber, const Point * const appPos, const Point * const appTarget);
	}*OBJ_ptr;
}