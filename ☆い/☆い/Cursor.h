#pragma once
#include "MyGame/MyApp.h"
#include "MyGame/My/Move.h"

namespace Cursor
{
	const char caTaskName[] = { "�J�[�\���^�X�N" };
	const char caResName[] = { "�J�[�\�����\�[�X" };

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
		std::shared_ptr<Move> spMove;
		Rec rCursorBase;
		Point pPos;
		float fSpd;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();

		void MoveKeyBoard(std::shared_ptr<KB> &apKB, const float afX, const float afY, const float afW, const float afH);
		void MovePad(std::shared_ptr<JoyPad> &apPad, const float afX, const float afY, const float afW, const float afH);
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}