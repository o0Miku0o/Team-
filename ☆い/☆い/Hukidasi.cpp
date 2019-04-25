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
		rHukidasi.Draw();
	}
	/*�����o���̃T�C�Y�ύX*/
	void Obj::Resize()
	{
		const float fScaleW = rHukidasi.GetW() + fAddScale;
		const float fScaleH = rHukidasi.GetH() + fAddScale;
		const float fResizeW = Min(Max(fScaleW, 0.f), fWidthMax);
		const float fResizeH = Min(Max(fScaleH, 0.f), fHeightMax);
		rHukidasi.Scaling(fResizeW, fResizeH);
	}
	/**/
	void Obj::SetAddScale(const fix afAddScale)
	{
		fAddScale = afAddScale;
	}
	/**/
	void Obj::SetPos(const Point * const appPos)
	{
		rHukidasi.SetPos(appPos);
	}
}
