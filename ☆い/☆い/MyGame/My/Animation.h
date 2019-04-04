#ifndef ANIM
#define ANIM
using AnimFunc = void(*)(byte * const, byte * const, byte * const);
typedef unsigned char byte;
/*�A�j���[�V�����N���X*/
class Animation
{
	AnimFunc fpAnimFunc;
	byte bFrame;
	byte bAnimSrcX;
	byte bAnimSrcY;
public:
	/*�R���X�g���N�^*/
	Animation()
		:
		fpAnimFunc(nullptr),
		bFrame(0),
		bAnimSrcX(0),
		bAnimSrcY(0)
	{

	}
	/*�A�j���[�V�����֐��̓o�^�Ə����؂���ʒu��ݒ�*/
	void SetAnim(AnimFunc fpAnimFunc, const byte bAnimSrcX)
	{
		if (this->GetNowAnim() == fpAnimFunc) return;
		this->fpAnimFunc = fpAnimFunc;
		this->bFrame = 0;
		this->bAnimSrcX = bAnimSrcX;
	}
	/*�A�j���[�V�����֐������s*/
	void Update()
	{
		if (!this->fpAnimFunc) return;
		this->fpAnimFunc(&this->bFrame, &this->bAnimSrcX, &this->bAnimSrcY);
	}
	/*���ݓo�^����Ă���A�j���[�V�����֐�*/
	const AnimFunc GetNowAnim() const
	{
		return this->fpAnimFunc;
	}
	/*�摜�̐؂���ʒu��X���W*/
	const byte GetSrcX() const
	{
		return this->bAnimSrcX;
	}
	/*�摜�̐؂���ʒu��Y���W*/
	const byte GetSrcY() const
	{
		return this->bAnimSrcY;
	}
};
#endif