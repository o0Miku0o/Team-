#pragma once
#include "MyGame/MyApp.h"

namespace StageSelectIcon
{
	const char caTaskName[] = { "�A�C�R���^�X�N" };
	const char caResName[] = { "�A�C�R�����\�[�X" };

	void AnimEarth(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	void AnimMeteo(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	void AnimGalaxy(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	void AnimUranus(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	void AnimBlackHole(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	void AnimTimeAttack(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	void AnimFragment(int* const iAnimCount, int* const iAddOffSet, int* const iOffSetX, int* const iOffSetY);

	enum Type
	{
		ET,     //Earth
		MT,     //Meteo
		GL,     //Galaxy
		US,     //Uranus
		BH,     //Black Hole
		FR,     //Fragment
		TA,     //Time Attack
		TYPEMAX
	};

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
	typedef RS* RS_ptr;
	/*�^�X�N�I�u�W�F�N�g�N���X*/
	typedef class Obj : public TaskBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Rec rIcon;
		int iAnimCount;
		int iAddOffSet;
		int iOffSetX;
		int iOffSetY;
		int i;


		Type type;

		void(*IconAnimation[TYPEMAX])(int* const, int* const, int* const, int* const) =
		{
			AnimEarth,
			AnimMeteo,
			AnimGalaxy,
			AnimUranus,
			AnimBlackHole,
			AnimFragment,
			AnimTimeAttack
		};

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