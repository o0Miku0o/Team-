#pragma once
#include "MyGame\TaskBase.h"

namespace BlackHoleGenerator
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
		enum SizeMode
		{
			Normal,	//����
			Bigger, //�ǂ�ǂ�傫������
			Move	//�ړ�����
		}sizeMode;

		//pPos���ʒu�ApSize�ő傫���Amode�Ŏ��(Normal,Bigger,Move)�AEndPos�͈ړ��̏ꍇ�����I�_���w��
		void Bridge(Point *pPos, const float *pSize, const int mode, Point *pMovePos = 0);

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