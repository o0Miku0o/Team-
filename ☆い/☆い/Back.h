#pragma once
#include "MyGame/MyApp.h"

namespace Back
{
	const char caTaskName[] = { "�w�i�^�X�N" };
	const char caResName[] = { "�w�i���\�[�X" };

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
		Pixel pBackStar[320];
		Rec rBackBase;
		Line lShootingStar;
		byte bSSLife;
		byte bSSLifeMax;

		RS_ptr res;
		void Init();
		void Finalize();

		void ShootingStarInit();
		void BackStarInit();

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