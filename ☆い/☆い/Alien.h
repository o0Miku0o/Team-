#pragma once
#include "MyGame/MyApp.h"

namespace Alien
{
	const char caTaskName[] = { "�F���l�^�X�N" };
	const char caResName[] = { "�F���l���\�[�X" };

	/*�����𐧌䂷��֐��|�C���^*/
	using Move = void(*)(Point*, const Point*, int * const, float * const);
	/*����������̓����𐧌䂷��֐��|�C���^*/
	using Hit = void(*)(TaskBase * const);
	/*�A�j���[�V�����𐧌䂷��֐��|�C���^*/
	using Anim = void(*)(int * const, int * const, int * const, int * const);

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
		Rec rAlienR;
		Circle cAlienRHitBase;
		Point pCenter;
		int iTime;
		int iAnimCount;
		int iOffSetX;
		int iOffSetY;
		int iAddOffSet;
		float fAddAngle;
		Move moveFunc;
		Hit BMHitFunc;
		Hit FGHitFunc;
		Anim AnimFunc;

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void BeamCheckhit(TaskBase* bm);
		void FragmentCheckhit(TaskBase* fr);
	}*Obj_ptr;
	void MoveHorizontal(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);
	void Move_Horizontal(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);
	void MoveVertical(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);
	void Move_Vertical(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);
	void MoveRotation(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);
	void Move_Rotation(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);
	void MoveStay(Point* pPos, const Point* pCenter, int * const iCount, float * const fAddAngle);

	void BMRemove(TaskBase * const tTask);
	void BMReflectDR(TaskBase * const tTask);
	void BMReflectUR(TaskBase * const tTask);
	void BMReflectDL(TaskBase * const tTask);
	void BMReflectUL(TaskBase * const tTask);

	void FGRemove(TaskBase * const tTask);
	void FGReflectDR(TaskBase * const tTask);
	void FGReflectUR(TaskBase * const tTask);
	void FGReflectDL(TaskBase * const tTask);
	void FGReflectUL(TaskBase * const tTask);

	void AnimNormal(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
	void AnimHorizontal(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
	void AnimRotation(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
	void AnimReflectDR(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
	void AnimReflectUR(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
	void AnimReflectUL(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
	void AnimReflectDL(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY);
}