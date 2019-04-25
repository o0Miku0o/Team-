#include "Hukidasi.h"

namespace Hukidasi
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
		SetName("�����o���^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�����o�����\�[�X");
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		rHukidasi = Rec();
		fAddScale = 0.f;
		fWidthMax = 0.f;
		fHeightMax = 0.f;
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove("�����o�����\�[�X");
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		Resize();
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (!rHukidasi.Zero())
		{
			rHukidasi.Draw();
		}
	}
	/*�����o���̃T�C�Y�ύX*/
	void Obj::Resize()
	{
		/*���݂̃T�C�Y*/
		const float fScaleW = rHukidasi.GetW();
		const float fScaleH = rHukidasi.GetH();
		/*�e������*/
		const float fAddW = (fAddScale < 0.f && fScaleH > 0.f) ? 0.f : fAddScale;
		const float fAddH = (fAddScale > 0.f && fScaleW < fWidthMax) ? 0.f : fAddScale;
		/*�T�C�Y�Ƒ����ʂ���T�C�Y�ύX*/
		const float fResizeW = Min(Max(fScaleW + fAddW, 0.f), fWidthMax);
		const float fResizeH = Min(Max(fScaleH + fAddH, 0.f), fHeightMax);
		rHukidasi.Scaling(fResizeW, fResizeH);
	}
	/*�T�C�Y�̕ω��ʂ�ݒ�*/
	void Obj::SetAddScale(const float afAddScale)
	{
		fAddScale = afAddScale;
	}
	/*�T�C�Y�̍ő�l��ݒ�*/
	void Obj::SetScaleMax(const float afWMax, const float afHMax)
	{
		fWidthMax = afWMax;
		fHeightMax = afHMax;
	}
	/*���W��ݒ�*/
	void Obj::SetPos(const Point * const appPos)
	{
		rHukidasi.SetPos(appPos);
	}
}
