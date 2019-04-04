#pragma once
#include "MyGame/MyApp.h"

namespace Stage3
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
		Rec rPlayer;   //�F����s�m
		Rec rStar;     //�����̐�
		Rec rStarM;    //�₤��("M"ake a star)
		Rec rStarR;    //Red
		Rec rStarB;    //Blue
		Rec rBack;     //�w�i
		Rec rPlanetJ;  //�f���P("J"upiter)
		Rec rPlanetN;  //�f���Q("N"eptune)

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
}