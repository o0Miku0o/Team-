#include "FadeInOut.h"
#include "StageManager.h"

namespace FadeInOut
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
		SetName("�t�F�C�h�C���A�E�g�^�X�N");
		/*���\�[�X����*/
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		SetRenderPriority(1.f);

		fSize = 960.f;

		//���E�㉺
		rSquere[0] = Rec(0, 0, 1000, 1080);
		rSquere[1] = Rec(0, 0, 1000, 1080);
		rSquere[2] = Rec(0, 0, 1920, 1000);
		rSquere[3] = Rec(0, 0, 1920, 1000);

		fStarSize = 0;
		fStarSizeValue = 0.f;
		rStar = Rec(Rec::Win.r *0.5f, Rec::Win.b *0.5f, fStarSize, fStarSize);

		bIsIn = true;
		bActive = false;

	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		//fsize��2120�ɂȂ����u�Ԕw�i���S�����߂�
		if (!bActive) {
			if (bIsIn) {
				fStarSizeValue = -32.f;
				fStarSize = 1920.f;
			}
			else {
				fStarSizeValue = 32.f;
				fStarSize = 0.f;
			}
			bActive = true;
		}
		else {
			if (bIsIn) {
				if (fStarSize < 0) {
					Remove(this);
				}
			}
			else {
				if (fStarSize >= 3840) {
					Remove(this);
				}
			}
		}
		fStarSize += fStarSizeValue;

		rStar.Scaling(fStarSize, fStarSize);
		rSquere[0].SetPos(&Point(rStar.GetPosX() - rSquere[0].GetW() * 0.45f - fStarSize * 0.45f, rStar.GetPosY()));
		rSquere[1].SetPos(&Point(rStar.GetPosX() + rSquere[1].GetW() * 0.45f + fStarSize * 0.45f, rStar.GetPosY()));
		rSquere[2].SetPos(&Point(rStar.GetPosX(), rStar.GetPosY() - rSquere[2].GetH() * 0.45f - fStarSize * 0.45f));
		rSquere[3].SetPos(&Point(rStar.GetPosX(), rStar.GetPosY() + rSquere[3].GetH() * 0.45f + fStarSize * 0.45f));
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>("�X�e�[�W�������\�[�X")) {
			for (int i = 0; i < 4; ++i) {
				Frec src(16, 0, 16, 16);
				rSquere[i].Draw(&res->iStageImg, &src, false);
			}
			rStar.Draw(&res->tese, &Frec(0, 0, 16, 16), false);
		}
	}
}
