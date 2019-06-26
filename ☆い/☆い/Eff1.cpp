#include "Eff1.h"

namespace Eff1
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
		iEff1Img.ImageCreate("./data/image/other/Effect/eff1.bmp");
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
		iEff1Img.Release();
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);
		/*���\�[�X����*/
		RB::Add<RS>(caResName);
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		SetRenderPriority(0.3f);

		rEffBase = Rec(0.f, 0.f, 16.f, 16.f);
		fSpdX = 0;
		fSpdY = 0;
		fAddSpdX = 0;
		fAddSpdY = 0;
		fAngle = 0;
		fAddAngle = 0;
		bLife = 0;
		bLifeMax = 30;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		if (!Find<Obj>(caTaskName))
		{
			RB::Remove(caResName);
		}
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		if (bLife >= bLifeMax)
		{
			Remove(this);
			return;
		}
		++bLife;
		Vector2 vSpd(fSpdX, fSpdY);
		rEffBase.Move(&vSpd);
		//rEffBase.SetDeg(fAngle);
		fSpdX += fAddSpdX;
		fSpdY += fAddSpdY;
		fAngle = ModAngle(fAngle + fAddAngle);
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<RS>(caResName))
		{
			Frec src(0.f, 16.f * tType, 16.f, 16.f);
			rEffBase.Draw(&res->iEff1Img, &src, false);
		}
	}

	void Obj::SetParam(const Rec * const crpcEffBase, const Vector2 * const cvpcSpd, const byte cbLifeMax, const ChipType ctType, const float cfAngle, const float cfAddAngle, const Vector2 * const vAddSpd)
	{
		rEffBase = *crpcEffBase;
		fAddSpdX = vAddSpd->GetX();
		fAddSpdY = vAddSpd->GetY();
		fSpdX = cvpcSpd->GetX() - (fAddSpdX * 10);
		fSpdY = cvpcSpd->GetY() - (fAddSpdY * 10);
		fAngle = cfAngle;
		fAddAngle = cfAddAngle;
		bLife = 0;
		bLifeMax = cbLifeMax;
		tType = ctType;
	}

	void CreateOugi(const int iNum, const ChipType cType, const Point * const pPos, const float fW, const float fH, const float fInitAngle, const float fMax, const float fMin, const byte bLife, const float fSpd, const Vector2 * const vAddSpd)
	{
		const float fIAngle = ModAngle(fInitAngle + 180.f);
		const float fRange = Abs((float)fMax - fMin);
		for (int i = 0; i < iNum; ++i)
		{
			auto ef1 = TB::Add<Eff1::Obj>();
			const float fAng = ModAngle(fIAngle - fMin + (fRange / iNum) * i + (rand() % 21 - 10.f));
			Vector2 vSpd;
			vSpd.SetVec(fAng, (rand() % 3 + fSpd));
			const Rec rEf(pPos->x, pPos->y, fW, fH/*, fAng*/);
			ef1->SetParam(&rEf, &vSpd, bLife, cType, fAng, 0.f, vAddSpd);
		}
	}
	void CreateHanabi(const int iNum, const ChipType cType, const Point * const pPos, const float fW, const float fH, const float fInitAngle, const byte bLife, const float fSpd, const Vector2 * const vAddSpd)
	{
		for (int i = 0; i < iNum; ++i)
		{
			auto ef1 = TB::Add<Eff1::Obj>();
			const float fAngle = ModAngle(fInitAngle + (360.f / iNum) * i);
			Vector2 vSpd;
			vSpd.SetVec(fAngle, (rand() % 3 + fSpd));
			const Rec rEf(pPos->x, pPos->y, fW, fH/*, fAngle*/);
			ef1->SetParam(&rEf, &vSpd, bLife, cType, fAngle, 0.f, vAddSpd);
		}
	}
	void Create(const std::string &asEfFileName, const Point * const apPos, const float afAngle)
	{
		static const std::map<const std::string, const Eff1::ChipType> mType =
		{
			{ "beam", Eff1::ChipType::TYPE_BEAM },
			{ "r_frg", Eff1::ChipType::TYPE_R_FRG },
			{ "y_frg", Eff1::ChipType::TYPE_Y_FRG },
			{ "b_frg", Eff1::ChipType::TYPE_B_FRG },
			{ "y_sta", Eff1::ChipType::TYPE_Y_STAR },
			{ "r_sta", Eff1::ChipType::TYPE_R_STAR },
			{ "b_sta", Eff1::ChipType::TYPE_B_STAR },
		};

		std::string lsEfType = "ougi", lsChipType = "y_sta";
		std::string lsCmd;
		int liNum = 4, liLife = 20;
		float lfSpd = 2.f, lfW = 8.f, lfH = 8.f, lfOp[2] = {};
		auto CmdComp = [&lsCmd](const std::string &r)
		{
			return lsCmd == r;
		};
		auto EfTypeComp = [&lsEfType](const std::string &r)
		{
			return lsEfType == r;
		};
		Stream<IOMode::IO_IN> ifs(asEfFileName);
		if (!ifs.IsOpened())
		{
			MsgBox(asEfFileName + "�t�@�C�����J���܂���");
			return;
		}
		for (;;)
		{
			/*�t�@�C���̏I�[*/
			if (ifs.Eof()) break;
			ifs >> lsCmd;
			/*�R�����g*/
			if (lsCmd.at(0) == '\'')
			{
				ifs.Ignore('\n');
				continue;
			}
			/*�I��*/
			if (CmdComp("end")) break;
			/*�G�t�F�N�g�^�C�v*/
			if (CmdComp("e_type"))
			{
				ifs >> lsEfType;
				continue;
			}
			/*�`�b�v�^�C�v*/
			if (CmdComp("c_type"))
			{
				ifs >> lsChipType;
				continue;
			}
			/*�T�C�Y*/
			if (CmdComp("c_size"))
			{
				ifs >> lfW >> lfH;
				continue;
			}
			/*��*/
			if (CmdComp("num"))
			{
				ifs >> liNum;
				continue;
			}
			/*����*/
			if (CmdComp("life"))
			{
				ifs >> liLife;
				continue;
			}
			/*����*/
			if (CmdComp("spd"))
			{
				ifs >> lfSpd;
				continue;
			}
			/*�I�v�V����*/
			if (CmdComp("op"))
			{
				int liIdx = 0;
				ifs >> liIdx;
				if (liIdx >= sizeof(lfOp) / sizeof(lfOp[0]))
				{
					MsgBox(asEfFileName + " �C���f�b�N�X���I�v�V�����̍ő吔�𒴂��Ă��܂��B");
					break;
				}
				ifs >> lfOp[liIdx];
				continue;
			}
			/*�G�t�F�N�g���s*/
			if (CmdComp("do"))
			{
				if (EfTypeComp("ougi"))
				{
					CreateOugi(liNum, mType.at(lsChipType), apPos, lfW, lfH, afAngle, lfOp[0], lfOp[1], liLife, lfSpd);
				}
				else if (EfTypeComp("hanabi"))
				{
					CreateHanabi(liNum, mType.at(lsChipType), apPos, lfW, lfH, afAngle, liLife, lfSpd, &Vector2(lfOp[0], lfOp[1]));
				}
				continue;
			}
		}
		ifs.Close();
	}
}
