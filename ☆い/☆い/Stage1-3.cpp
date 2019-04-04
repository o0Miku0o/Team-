#include "Stage2-1.h"
#include "Stage1-3.h"
#include "StageSelect.h"
#include "StageManager.h"
#include "StarGenerator.h"
#include "FragmentGenerator.h"
#include "Player.h"
#include "Neptune.h"
#include "Jupitor.h"

namespace Stage13
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{

	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{

	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName("�X�e�[�W�P�|�R�^�X�N");
		/*���\�[�X����*/

		/*�^�X�N�̐���*/
		Add<Player::Obj>();
		auto np = Add<Neptune::Obj>();
		auto jp = Add<Jupitor::Obj>();

		Point pJp(jp->cGravityCircle.GetPos().x + jp->cGravityCircle.GetRadius()-1, jp->cGravityCircle.GetPos().y);
		Point pNp(np->cGravityCircle.GetPos().x + np->cGravityCircle.GetRadius()-1, np->cGravityCircle.GetPos().y);
		auto fg = Add<FragmentGenerator::Obj>();
		Point pArr[2] = { pJp , pNp };
		int iColor[2] = {};
		fg->Bridge(2, pArr, iColor);
		auto sg = Add<StarGenerator::Obj>();
		int iChange = 23;
		sg->Bridge(1, &iChange, &Point(1650.f, 500.f));
		/*�f�[�^�̏�����*/
		//�w�i
		rBack = Rec(Rec::Win.r / 2, Rec::Win.b / 2, Rec::Win.r, Rec::Win.b);

		//�����̃T�C�Y(�������邽�߂ɍD���ɕύX���Ă�������)
		rPlayer = Rec(250, 100, 16 * 8, 16 * 8);
		rStar = Rec(1600, 300, 16 * 7, 16 * 7);
		//rStarM = Rec(500, 500, 16 * 5, 16 * 5);
		rStarB = Rec(800, 500, 16 * 5, 16 * 5);
		rStarB.SetDeg(160);
		rStarR = Rec(1350, 500, 16 * 5, 16 * 5);
		rStarR.SetDeg(150);

		//�A�j���[�V��������(��قǒǉ�����̂ō���͔����v���ɉ摜����]�����Ă�������)
		rPlanetJ = Rec(800, 270, 16 * 20, 16 * 20);
		rPlanetJ.SetDeg(90);
		rPlanetN = Rec(1350, 680, 16 * 14, 16 * 14);
		rPlanetN.SetDeg(90);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);
		if (kb->Now('G') == 1 || pad->NowBut(J_BUT_8) == 1)
		{
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage21::Obj>();
			Pause(2);
		}
		if (kb->Now('F') == 1 || pad->NowBut(J_BUT_7) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<StageSelect::Obj>();
			Pause(2);
		}
		if (kb->Now('R') == 1 || pad->NowBut(J_BUT_4) == 1) {
			RemoveAll("�X�e�[�W�����^�X�N", NOT_REMOVE_NAME);
			Add<Stage13::Obj>();
			Pause(2);
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{

	}
}
