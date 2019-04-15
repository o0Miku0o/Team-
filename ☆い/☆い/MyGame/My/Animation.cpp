#include "Animation.h"
Animation *Animation::apTop = nullptr;
/*�A�j���[�V�����֐������s*/
void Animation::Update()
{
	if (!this->fpAnimFunc) return;
	this->fpAnimFunc(&this->bFrame, &this->bAnimSrcX, &this->bAnimSrcY);
}
/*�S�A�j���[�V�����֐������s*/
void Animation::UpdateAll()
{
	auto apIt = apTop;
	while (apIt)
	{
		if(apIt->bUpdFlag) apIt->Update();
		apIt = apIt->apNext;
	}
}
/*�R���X�g���N�^*/
Animation::Animation()
	:
	apNext(nullptr),
	apPrev(nullptr),
	fpAnimFunc(nullptr),
	bFrame(0),
	bAnimSrcX(0),
	bAnimSrcY(0),
	bUpdFlag(false)
{
	if (apTop)
	{
		auto apIt = apTop;
		while (apIt->apNext)
		{
			apIt = apIt->apNext;
		}
		apIt->apNext = this;
		this->apPrev = apIt;
		return;
	}
	apTop = this;
}
/*�f�X�g���N�^*/
Animation::~Animation()
{
	if (this->apPrev) this->apPrev->apNext = this->apNext;
	else apTop = this->apNext;
	if (this->apNext) this->apNext->apPrev = this->apPrev;
}
/*�A�j���[�V�����֐��̓o�^�Ə����؂���ʒu��ݒ�*/
void Animation::SetAnim(AnimFunc fpAnimFunc, const byte bAnimSrcX)
{
	if (this->GetNowAnim() == fpAnimFunc) return;
	this->fpAnimFunc = fpAnimFunc;
	this->bFrame = 0;
	this->bAnimSrcX = bAnimSrcX;
}
/*���ݓo�^����Ă���A�j���[�V�����֐�*/
const AnimFunc Animation::GetNowAnim() const
{
	return this->fpAnimFunc;
}
/*�摜�̐؂���ʒu��X���W*/
const byte Animation::GetSrcX() const
{
	return this->bAnimSrcX;
}
/*�摜�̐؂���ʒu��Y���W*/
const byte Animation::GetSrcY() const
{
	return this->bAnimSrcY;
}
/*�A�j���[�V�����Đ�*/
void Animation::Play()
{
	if(!bUpdFlag) bUpdFlag = true;
}
/*�A�j���[�V������~*/
void Animation::Stop()
{
	if (bUpdFlag) bUpdFlag = false;
}