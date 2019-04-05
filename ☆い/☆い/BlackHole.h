#pragma once
#include "MyGame\TaskBase.h"

namespace BlackHole
{
	/*���\�[�X*/
	class RS : public ResourceBase
	{
	public:
		/*�����ɋ��ʕϐ���ǉ�*/
		/*�ȉ��ύX�s�v*/
		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;

	/*�^�X�N�I�u�W�F�N�g*/
	typedef class Obj : public TaskBase
	{
	public:
		/*�����Ƀ^�X�N���Ƃ̕ϐ���ǉ�*/
		Rec	rBlackHole; //�`��p
		Circle cInnerCircle , cOutCircle; //�����~
		Point pPos;
		bool bBigger;
		bool bMove;
		bool bCreate;
		Point pEndPos;
		Point pStartPos;
		float fAngle;

		//����
		bool IsCreate();
		//�ǂ�ǂ�傫���Ȃ�
		bool IsBigger();
		//�ړ�����
		bool IsMove();

		void CheckHitBeam(TaskBase *bm);
		void CheckHitFragment(TaskBase *fg);
		float CalcAngle(const Point targetPos, const Point bhPos, const float targetAngle);
		//���ł܂ł̏���

		/*�ȉ��ύX�s�v*/
		Obj() { Init(); }
		~Obj() { Finalize(); }
	private:
		/*���\�[�X���Q��*/
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}