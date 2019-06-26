#pragma once
#include "MyGame/MyApp.h"

namespace Eff1
{
	const char caTaskName[] = { "�G�t�F�N�g�P�^�X�N" };
	const char caResName[] = { "�G�t�F�N�g�P���\�[�X" };

	enum ChipType
	{
		TYPE_BEAM,
		TYPE_R_FRG,
		TYPE_Y_FRG,
		TYPE_B_FRG,
		TYPE_Y_STAR,
		TYPE_R_STAR,
		TYPE_B_STAR,
		TYPE_MAX
	};
	enum EffGroupType
	{
		EFFECT_TYPE_HOUKI,
		EFFECT_TYPE_HANABI
	};
	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iEff1Img;

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
		Rec rEffBase;
		float fSpdX;
		float fSpdY;
		float fAddSpdX;
		float fAddSpdY;
		float fAngle;
		float fAddAngle;
		byte bLifeMax;
		byte bLife;
		ChipType tType;

		void Init();
		void Finalize();
	public:
		void Update();
		void Render();

		void SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const ChipType ctType, const float cfAngle = 0.f, const float cfAddAngle = 0.f, const Vector2 * const vAddSpd = &Vector2::zero);
	}*Obj_ptr;
	void CreateOugi(const int iNum, const ChipType cType, const Point * const pPos, const float fW, const float fH, const float fInitAngle, const float fMax, const float fMin, const byte bLife = 20, const float fSpd = 1.f, const Vector2 * const vAddSpd = &Vector2::zero);
	void CreateHanabi(const int iNum, const ChipType cType, const Point * const pPos, const float fW, const float fH, const float fInitAngle, const byte bLife = 20, const float fSpd = 1.f, const Vector2 * const vAddSpd = &Vector2::zero);
	void Create(const std::string &asEfFileName, const Point * const apPos, const float afAngle);
}