#pragma once
#include "MyGame/MyApp.h"

namespace Back
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

		Obj() {}
		~Obj() {}
	private:
		Pixel pBackStar[560];
		Rec rBackBase;
		Line lShootingStar;
		byte bSSLife;
		byte bSSLifeMax;

		RS_ptr res;
		void Init();
		void Finalize();

		void ShootingStarUpdate();
		void BackStarUpdate();

		void BackBaseDraw();
		void ShootingStarDraw();
		void BackStarDraw();
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}