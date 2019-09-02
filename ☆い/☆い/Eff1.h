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

	class EffectCreater
	{
	private:
		static const std::map<const std::string, const Eff1::ChipType> m_type;
		std::string ef_type, ch_type, ef_type_old, ch_type_old;
		int num, life, num_old, life_old;
		float w, h, op[2], spd, w_old, h_old, op_old[2], spd_old;
	public:
		using SP = std::shared_ptr<EffectCreater>;
		EffectCreater(const std::string &_filename)
			: ef_type("nothing")
			, ch_type("nothing")
			, ef_type_old(ef_type)
			, ch_type_old(ch_type)
		{
			std::ifstream _ifs(_filename);
			if (!_ifs) return;
			std::string _cmd;
			for (;;)
			{
				/*�t�@�C���̏I�[*/
				if (_ifs.eof()) break;
				_ifs >> _cmd;
				/*�R�����g*/
				if (_cmd.at(0) == '\'')
				{
					_ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				/*�I��*/
				if (_cmd == "end") break;
				/*�G�t�F�N�g�^�C�v*/
				if (_cmd == "e_type")
				{
					_ifs >> ef_type;
					ef_type_old = ef_type;
					continue;
				}
				/*�`�b�v�^�C�v*/
				if (_cmd == "c_type")
				{
					_ifs >> ch_type;
					ch_type_old = ch_type;
					continue;
				}
				/*�T�C�Y*/
				if (_cmd == "c_size")
				{
					_ifs >> w >> h;
					w_old = w;
					h_old = h;
					continue;
				}
				/*��*/
				if (_cmd == "num")
				{
					_ifs >> num;
					num_old = num;
					continue;
				}
				/*����*/
				if (_cmd == "life")
				{
					_ifs >> life;
					life_old = life;
					continue;
				}
				/*����*/
				if (_cmd == "spd")
				{
					_ifs >> spd;
					spd_old = spd;
					continue;
				}
				/*�I�v�V����*/
				if (_cmd == "op")
				{
					int _idx = 0;
					_ifs >> _idx;
					if (_idx >= sizeof(op) / sizeof(op[0]))
					{
						MsgBox(_filename + " �C���f�b�N�X���I�v�V�����̍ő吔�𒴂��Ă��܂��B");
						break;
					}
					_ifs >> op[_idx];
					op_old[_idx] = op[_idx];
					continue;
				}
			}
			_ifs.close();
		}
		void run(const Point &_pos, const float _angle)
		{
			if (ef_type == "nothing" || ch_type == "nothing") return;
			if (ef_type == "ougi")
			{
				CreateOugi(num, m_type.at(ch_type), &_pos, w, h, _angle, op[0], op[1], life, spd);
			}
			else if (ef_type == "hanabi")
			{
				CreateHanabi(num, m_type.at(ch_type), &_pos, w, h, _angle, life, spd, &Vector2(op[0], op[1]));
			}
			ef_type = ef_type_old;
			ch_type = ch_type_old;
			num = num_old;
			w = w_old;
			h = h_old;
			for (size_t i = 0; i < sizeof(op) / sizeof(op[0]); ++i) op[i] = op_old[i];
			life = life_old;
			spd = spd_old;
		}
		void _set_chip_type(const std::string &_ch_type)
		{
			ch_type = _ch_type;
		}
		void _set_life(const int _life)
		{
			life = _life;
		}
		void _set_spd(const float _spd)
		{
			spd = _spd;
		}
	};
}