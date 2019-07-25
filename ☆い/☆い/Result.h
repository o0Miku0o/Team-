#pragma once
#include "MyGame/MyApp.h"
#include "MyGame/My/EventMsg.h"
#include "Eff1.h"

namespace Result
{
	const char caTaskName[] = { "���U���g�^�X�N" };
	const char caResName[] = { "���U���g���\�[�X" };

	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		Image iResult;
		Image iHanko;
		Image iPaper;

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
		std::string sPercent;
		int iRandomTime;
		int iHanabiCount;
		int iHanabiTime;

		Rec rBack;
		Rec rResult;
		Rec rNumber;
		Rec rPercent;
		Rec rHanko;
		byte bNextStage;
		byte bMoveStarIdx;

		bool bPushHanko;
		//byte bScore;
		//EventMsg em;

		Rec rRestart;
		std::array<byte, 3> bScore;
		byte bScoreIdx;
		std::shared_ptr<Eff1::EffectCreater> sp_ef;
		byte bStageGroupNumber;

		void ButtonInit();
		//void ButtonResize();
		void DrawButton(RS * const rpRes, const Frec * const fpSrc);

		Obj() {}
		~Obj() {}
	private:
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
		void SetParam(const byte abStageGroupNumber, const std::array<byte, 3> &abScores);
	}*OBJ_ptr;
}