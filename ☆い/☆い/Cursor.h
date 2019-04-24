#pragma once
#include "MyGame/MyApp.h"

namespace Cursor
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
		Rec rCursorBase;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void HukidasiSizeUp(TaskBase * const tSl, const float cfScaleWMax, const float cfScaleHMax, const float cfAddScale);
		void HukidasiSizeDown(TaskBase * const tSl, const float cfScaleWMax, const float cfAddScale);
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}