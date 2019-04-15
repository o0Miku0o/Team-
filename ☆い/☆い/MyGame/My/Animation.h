#ifndef ANIM
#define ANIM
typedef unsigned char byte;
using AnimFunc = void(*)(byte * const, byte * const, byte * const);
/*�A�j���[�V�����N���X*/
class Animation
{
	static Animation *apTop;
	Animation *apNext;
	Animation *apPrev;
	AnimFunc fpAnimFunc;
	byte bFrame;
	byte bAnimSrcX;
	byte bAnimSrcY;
	bool bUpdFlag;

	/*�A�j���[�V�����֐������s*/
	void Update();
public:
	/*�S�A�j���[�V�����֐������s*/
	static void UpdateAll();
	/*�R���X�g���N�^*/
	Animation();
	/*�f�X�g���N�^*/
	~Animation();
	/*�A�j���[�V�����֐��̓o�^�Ə����؂���ʒu��ݒ�*/
	void SetAnim(AnimFunc fpAnimFunc, const byte bAnimSrcX);
	/*���ݓo�^����Ă���A�j���[�V�����֐�*/
	const AnimFunc GetNowAnim() const;
	/*�摜�̐؂���ʒu��X���W*/
	const byte GetSrcX() const;
	/*�摜�̐؂���ʒu��Y���W*/
	const byte GetSrcY() const;
	/*�A�j���[�V�����Đ�*/
	void Play();
	/*�A�j���[�V������~*/
	void Stop();
};
#endif