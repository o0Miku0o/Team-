#pragma once
#include "MyGame/MyApp.h"

namespace Gas
{
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
		Rec rGas;
		int iGasColor;
		Animation aAnim;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
	void AnimGasW(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimGasB(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimGasY(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
	void AnimGasP(byte * const bFrame, byte * const bSrcX, byte * const bSrcY);
}