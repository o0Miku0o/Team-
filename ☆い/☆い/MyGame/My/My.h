#pragma once
#include <Windows.h>
#include <stdarg.h>
#include <tchar.h>
#include <string>
#include <time.h>
#include <vector>
#include <mmsystem.h>
#include "FixedPoint.h"
#include "CGDM.h"

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

//��������
//Xinput
//Xaudio

#ifdef _DEBUG
#define DBG_OUT(ccpDbgText) MessageBox(nullptr, (const char * const)ccpDbgText, "DBG", MB_OK)
#else
#define DBG_OUT(ccpDbgText) __noop
#endif

//My�l�[���X�y�[�X���̃N���X�Ŏg�p���铧���F
constexpr COLORREF TRANSPARENT_COLOR = RGB(255, 0, 255);

constexpr char FTYPE_GOTHIC[] = "�l�r �S�V�b�N";
constexpr char FTYPE_MINCHOU[] = "�l�r ����";
constexpr char FTYPE_MEIRIO[] = "���C���I";

//�}�E�X�{�^���̃^�C�v
enum MouseButton
{
	MS_LB,
	MS_RB,
	MS_MB,
	MS_BUT_MAX
};

enum Rec_Point
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	CENTER,
	POINT_MAX
};

/*�~����*/
constexpr double PI = 3.141592653589793238;

//�p�x�ϊ��֐�
//�x���烉�W�A���ɕϊ�
inline constexpr float DtoR(const float angleD_)
{
	constexpr double cedTmp = PI / 180.0;
	return float(angleD_ * cedTmp);
}
//�p�x�ϊ��֐�
//���W�A������x�ɕϊ�
inline constexpr float RtoD(const float angleR_)
{
	constexpr double cedTmp = 180. / PI;
	return float(angleR_ * cedTmp);
}
inline constexpr int I_DtoR(const float angleD_)
{
	return int(DtoR(angleD_));
}
inline constexpr int I_RtoD(const float angleR_)
{
	return int(RtoD(angleR_));
}
//�p�x�̏C��
inline constexpr float ModAngle(const float angleD_)
{
	float ang = angleD_;
	if (ang > 180.f)
	{
		while (ang > 180.f)
		{
			ang -= 360.f;
		}
	}
	else if (ang < -180.f)
	{
		while (ang < -180.f)
		{
			ang += 360.f;
		}
	}
	return ang;
}
//�������v�Z�֐��i�W����荂���I�j
inline float Sqrt(const float val_)
{
	float xHalf = 0.5f * val_;
	int   tmp = 0x5F3759DF - (*(int*)&val_ >> 1); //initial guess
	float xRes = *(float*)&tmp;

	xRes *= float(1.5 - (xHalf * xRes * xRes));
	xRes *= float(1.5 - (xHalf * xRes * xRes));//�R�����g�A�E�g���O���Ɛ��x���オ��
	return xRes * val_;
}
//�������v�Z�֐��i�W����荂���I�j
inline double Sqrt(const double val_)
{
	double         xHalf = 0.5 * val_;
	long long int  tmp = 0x5FE6EB50C7B537AAl - (*(long long int*)&val_ >> 1);//initial guess
	double         xRes = *(double*)&tmp;

	xRes *= (1.5 - (xHalf * xRes * xRes));
	xRes *= (1.5 - (xHalf * xRes * xRes));//�R�����g�A�E�g���O���Ɛ��x���オ��
	return xRes * val_;
}
/*abs()*/
template<class Value>
inline constexpr Value Abs(const Value &x)
{
	return Value((x > 0) ? x : ((x < 0) ? -x : 0));
}
/*max(a, b)*/
template<class Value1, class Value2>
inline constexpr Value1 Max(const Value1 &a, const Value2 &b)
{
	return Value1((a > (Value1)b) ? a : (Value1)b);
}
/*min(a, b)*/
template<class Value1, class Value2>
inline constexpr Value1 Min(const Value1 a, const Value2 b)
{
	return Value1((a < (Value1)b) ? a : (Value1)b);
}

//�񎟌��x�N�g���N���X
class Vector2
{
private:
	float x;
	float y;

public:
	/*�[���x�N�g��*/
	static const Vector2 zero;
	/*�������P�ʃx�N�g��*/
	static const Vector2 left;
	/*�E�����P�ʃx�N�g��*/
	static const Vector2 right;
	/*������P�ʃx�N�g��*/
	static const Vector2 up;
	/*�������P�ʃx�N�g��*/
	static const Vector2 down;

	//�R���X�g���N�^
	Vector2(float x_, float y_);
	//�R���X�g���N�^
	Vector2();
	//�R�s�[�R���X�g���N�^
	Vector2(const Vector2 &cpy_);
	//�p�x�ƒ�������x�N�g����ݒ�
	void SetVec(const float angleD_, const float len_);
	//X�̒l���擾
	const float GetX() const;
	//Y�̒l���擾
	const float GetY() const;
	//�x�N�g���̒������擾
	const float GetLen() const;
	//�x�N�g���̊p�x���擾
	const float GetDeg() const;
	//���ς��v�Z
	const float Dot(const Vector2 *vec2_) const;
	//�O�ς��v�Z
	const float Cross(const Vector2 *vec2_) const;
	//�x�N�g���̃X�J���[�{
	void MulVec(const float scalar_);
	//�x�N�g���̃X�J���[�{
	const Vector2 operator * (const float scalar_) const;
	//�x�N�g���̔�r
	const bool operator == (const Vector2 &vec2_) const;
	//�x�N�g���̔�r
	const bool operator != (const Vector2 &vec2_) const;
};

//�񎟌����W�\����
struct Point
{
	float x;
	float y;
	/*�R���X�g���N�^*/
	Point();
	/*�R���X�g���N�^*/
	Point(const float x_, const float y_);
	/*POINT�ւ̃L���X�g*/
	operator POINT ();
};

//�t���[�g�^RECT
struct Frec
{
	float l;
	float r;
	float t;
	float b;
	/*�R���X�g���N�^*/
	Frec();
	/*�R���X�g���N�^*/
	Frec(const float l_, const float t_, const float r_, const float b_);
	/*RECT�ւ̃L���X�g*/
	operator RECT ();
};

//�L�[�{�[�h�N���X
class KB
{
private:
	/*���݂̃L�[���*/
	byte nowkey[256];
	/*�O�t���[���̃L�[���*/
	byte prevkey[256];
	/*�L�[�{�[�h��Ԏ擾�̂��߂̃C���X�^���X�̃|�C���^*/
	static KB *instance;

public:
	/*�R���X�g���N�^*/
	KB();
	//�L�[���͂��擾���郁���o�֐�
	static bool GetKeyState();
	/*�C���X�^���X�̃A�h���X���擾*/
	static KB *GetState();
	/*���݂̃L�[���͏�Ԃ��擾*/
	byte Now(const char key_);
	/*�O�t���[���̃L�[���͏�Ԃ��擾*/
	byte Prev(const char key_);

	bool Down(const char cKey);

	bool On(const char cKey);

	bool Up(const char cKey);

	bool Off(const char cKey);
};

//�}�E�X�N���X
class MS
{
private:
	static HWND hWnd;
	Point pos;
	byte nowbut[MS_BUT_MAX];
	byte prevbut[MS_BUT_MAX];

	static MS *instance;

public:

	/*�R���X�g���N�^*/
	MS(const HWND hWnd_);
	//�}�E�X���͂��擾���郁���o�֐�
	static bool GetMouseState();
	/*�C���X�^���X�̃A�h���X���擾*/
	static MS *GetState();
	/*���݂̃}�E�X���͏�Ԃ��擾*/
	byte Now(const MouseButton but_);
	/*�O�t���[���̃}�E�X���͏�Ԃ��擾*/
	byte Prev(const MouseButton but_);

	bool Down(const MouseButton but_);

	bool On(const MouseButton but_);

	bool Up(const MouseButton but_);

	bool Off(const MouseButton but_);
	/*�J�[�\���̈ʒu���擾*/
	const Point &GetPos();
	/*�J�[�\����X���W*/
	float GetPosX();
	/*�J�[�\����Y���W*/
	float GetPosY();
};

//BMP�Ǘ��N���X
class Image
{
private:
	HDC hBmpDC, hMaskBmpDC;
	HBITMAP hBmp, hMaskBmp;
	COLORREF oldBkColor;
	BITMAP BmpInfo;

public:
	//�R���X�g���N�^
	Image();
	//�f�X�g���N�^
	~Image();
	//BMP�t�@�C���ǂݍ��݃����o�֐�
	bool ImageCreate(const char * const bmpfilename_);
	//�摜�̉��
	void Release();
	//
	const BITMAP &GetBmpInfo() const;
	//
	const HDC GetImageHandle() const;
	//
	const HBITMAP GetMaskHandle() const;
};

struct FontOP
{
	int Weight;          // ���� 
	DWORD Italic;        // �C�^���b�N 
	DWORD Underline;     // ���� 
	DWORD StrikeOut;     // ������ 
	DWORD CharSet;       // ���̐ݒ� 
	DWORD PitchAndFamily;// �����̊Ԋu

	FontOP();
	FontOP(const int Weight_, const DWORD Italic_, const DWORD Underline_, const DWORD StrikeOut_, const DWORD CharSet_, const DWORD PitchAndFamily_);
};

const FontOP FOP_DEFAULT(FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, FIXED_PITCH | FF_MODERN);

//�t�H���g�N���X
class Font
{
private:
	COLORREF col;
	HDC hOff;
	HFONT hf;
public:
	//�R���X�g���N�^
	Font();
	//�f�X�g���N�^
	~Font();
	//�t�H���g�쐬
	bool FontCreate(const char *fontname_, const FontOP *fontoption_ = &FOP_DEFAULT, int h_ = 0, float angleD_ = 0);
	//�t�H���g�̏���
	void Release();
	//�F�ݒ�
	void SetColor(COLORREF col_);
	//�F�ݒ�
	void SetColor(const byte r_, const byte g_, const byte b_);
	//�`��
	void Draw(const Point * const pos_, const char * const text_);
};

/*wave�t�@�C���Đ��N���X*/
class WSound
{
	/*���̃��X�g�̐擪�A�h���X*/
	static WSound *pwsTop;
	/*�E�F�[�u�t�H�[�}�b�g*/
	WAVEFORMATEX wFormatEx;
	/*�E�F�[�u�w�b�_*/
	WAVEHDR wHdr;
	/*�f�o�C�X�ւ̃|�C���^*/
	HWAVEOUT hWaveOut;
	/*�R�[���o�b�N�E�B���h�E*/
	HWND hCallBackWnd;
	/*���̗v�f*/
	WSound *next;
	/*�O�̗v�f*/
	WSound *prev;
	/*�Đ������ǂ���*/
	bool bIsPlaying;
public:
	/*MM_WOM_DONE���b�Z�[�W���|�X�g���ꂽ��Ă�*/
	/*���[�v�Đ����\�ɂ���*/
	static void LoopProc(WPARAM wParam, LPARAM lParam);
	/*�R���X�g���N�^*/
	WSound();
	/*�f�X�g���N�^*/
	~WSound();
	/*�R�[���o�b�N�E�B���h�E��ݒ�*/
	/*�E�B���h�E���������Ɏw��*/
	bool CallBack(const char * const ccpWinName);
	/*wav�t�@�C���ǂݍ���*/
	bool SoundCreate(const char * const ccpWaveFileName);
	/*�T�E���h�̔j��*/
	void Release();
	/*���Đ�*/
	void Play();
	/*���[�v�Đ�*/
	/*�K�؂�LoopProc���Ă΂�Ă���΃��[�v���@�\����*/
	void PlayL();
	/*�ꎞ��~*/
	void Pause();
	/*�ꎞ��~����*/
	void Restart();
	/*��~*/
	void Stop();
};

/*JoyPad�̕����L�[�i�X�e�B�b�N�j*/
enum Joy_Direct
{
	J_UP,
	J_DOWN,
	J_LEFT,
	J_RIGHT,
	J_DIR_MAX,
};
/*JoyPad�̃{�^��*/
enum Joy_Button
{
	//A
	J_BUT_1,
	//B
	J_BUT_2,
	//X
	J_BUT_3,
	//Y
	J_BUT_4,
	//LB
	J_BUT_5,
	//RB
	J_BUT_6,
	//BACK
	J_BUT_7,
	//START
	J_BUT_8,
	//L3
	J_BUT_9,
	//R3
	J_BUT_10,
	J_BUT_MAX,
};

/*JoyPad�i�Q�[���p�b�h�j�N���X*/
class JoyPad
{
private:
	/*�p�b�h�̗V��*/
	static long lStickTolerance;
	/*�Q�[���p�b�h�̍ő吔*/
	static constexpr byte PADNUM_MAX = 2;
	/*�Q�[���p�b�h����̏��i�[�ϐ�*/
	static JOYINFOEX joy_ex[PADNUM_MAX];
	/*���擾�p�C���X�^���X�ւ̃|�C���^�̓��I�z��*/
	static std::vector<JoyPad *> instance;
	/*���擾�p�C���X�^���X�̐�*/
	static byte inst_cnt;
	/*�X�e�B�b�N�������݃x�N�g��*/
	static Vector2 vec2[2][PADNUM_MAX];
	/*���݂̕����L�[�̏��*/
	static byte n_direct[PADNUM_MAX][J_DIR_MAX];
	/*���݂̃{�^���̏��*/
	static byte n_buttons[PADNUM_MAX][J_BUT_MAX];
	/*�O�t���[���̕����L�[�̏��*/
	static byte p_direct[PADNUM_MAX][J_DIR_MAX];
	/*�O�t���[���̃{�^���̏��*/
	static byte p_buttons[PADNUM_MAX][J_BUT_MAX];
	/*���X�e�B�b�N��X���������ݏ��*/
	static long axisx[PADNUM_MAX];
	/*���X�e�B�b�N��Y���������ݏ��*/
	static long axisy[PADNUM_MAX];
	/*���X�e�B�b�N��X���̏������*/
	static unsigned long initaxisx[PADNUM_MAX];
	/*���X�e�B�b�N��Y���̏������*/
	static unsigned long initaxisy[PADNUM_MAX];
	/*�E�X�e�B�b�N��X���������ݏ��*/
	static long Raxisx[PADNUM_MAX];
	/*�E�X�e�B�b�N��Y���������ݏ��*/
	static long Raxisy[PADNUM_MAX];
	/*�E�X�e�B�b�N��X���̏������*/
	static unsigned long Rinitaxisx[PADNUM_MAX];
	/*�E�X�e�B�b�N��Y���̏������*/
	static unsigned long Rinitaxisy[PADNUM_MAX];

	/*�C���X�^���X��ID*/
	byte joy_id;

public:
	/*�R���X�g���N�^*/
	JoyPad();
	/*JoyPad�N���X�̏�����*/
	static bool Init(const long lTolerance);
	/*�SJoyPad�̏��擾*/
	static bool GetStateAll();
	/*���ꂼ���JoyPad�̏����C���X�^���X����擾*/
	static JoyPad *GetState(const byte id_);
	/*���݂̃{�^���̏��擾*/
	byte NowBut(const Joy_Button button_);
	/*���݂̕����L�[�̏��擾*/
	byte NowDir(const Joy_Direct direct_);
	/*�O�t���[���̃{�^���̏��擾*/
	byte PreBut(const Joy_Button button_);
	/*�O�t���[���̕����L�[�̏��擾*/
	byte PreDir(const Joy_Direct direct_);

	bool Down(const Joy_Button but_);

	bool On(const Joy_Button but_);

	bool Up(const Joy_Button but_);

	bool Off(const Joy_Button but_);

	bool Down(const Joy_Direct direct_);

	bool On(const Joy_Direct direct_);

	bool Up(const Joy_Direct direct_);

	bool Off(const Joy_Direct direct_);
	/*���X�e�B�b�N��XY���������ݏ�Ԏ擾*/
	const Vector2 &GetAxisL() const;
	/*���X�e�B�b�N��XY���������ݏ�Ԏ擾*/
	/*�����ɂ� "Horizontal","Vertical" �̂ǂ��炩���w��*/
	float GetAxisL(const char * const axis_) const;
	/*���X�e�B�b�N�̉������ݕ����i���W�A���j���擾*/
	float GetRadL() const;
	/*���X�e�B�b�N�̉������ݕ����i�f�B�O���[�j���擾*/
	float GetDegL() const;
	/*�E�X�e�B�b�N��XY���������ݏ�Ԏ擾�֐�*/
	const Vector2 &GetAxisR() const;
	/*�E�X�e�B�b�N��XY���������ݏ�Ԏ擾�֐�*/
	/*�����ɂ� "Horizontal","Vertical" �̂ǂ��炩���w��*/
	float GetAxisR(const char * const axis_) const;
	/*�E�X�e�B�b�N�̉������ݕ����i���W�A���j���擾�֐�*/
	float GetRadR() const;
	/*�E�X�e�B�b�N�̉������ݕ����i�f�B�O���[�j���擾�֐�*/
	float GetDegR() const;
};
/*JoyPad�N���X�̃C���X�^���X���Q�Ƃ���|�C���^*/
typedef JoyPad *PJoyPad;

//��`�N���X
class Rec
{
private:
	static HDC off;
	static HBITMAP hoffbmp;
	static Frec frZoom;
	static Point Cam;
	static Point pAdjust;
	Point p[5];
	float w;
	float h;
	float dx;
	float dy;
	float angle;

public:
	//�E�B���h�E�̋�`
	static Frec Win;
	//��`�N���X�ɕ`��o�b�t�@���쐬�iwindow�̃T�C�Y�擾�j
	static bool Init(HWND hWnd_);
	//�I�t�X�N���[�������Z�b�g����֐�
	static void ResetOff(const DWORD rop_);
	//WM_PAINT���b�Z�[�W�������ŃI���X�N���[���ɕ`��
	static void DrawBackToFront(HDC hOn_);
	//�I�t�X�N���[���ƃr�b�g�}�b�v��j��
	static void Release();
	//�J�����̍��W�ɍ��킹�Ĉʒu�𒲐�����
	static const Point &AdjustCamPos(const Point * const pPos);
	//�J�����̍��W��ݒ�
	static void SetCameraPos(const Point * const pPos);
	//�J�������ړ�
	static void MoveCamera(const Vector2 * const vMove);
	//�J�����̍��W���擾
	static const Point &GetCameraPos();
	//�J������X���W���擾
	static const float GetCameraPosX();
	//�J������Y���W���擾
	static const float GetCameraPosY();
	//�Y�[��
	static void Zoom(const float fMagni);
	//�I�t�X�N���[���̃n���h�����擾
	static HDC GetOffScreenHandle();
	//�R���X�g���N�^
	Rec(const float cx_, const float cy_, const float w_, const float h_, float angleD_ = 0);
	//�R���X�g���N�^
	Rec();
	//�R�s�[�R���X�g���N�^
	Rec(const Rec & cpyrec_);
	//��`���ړ�������
	void SetPos(const Point * const pos_);
	//��`���g��k��������
	void Scaling(const float recw_, const float rech_);
	//�����̊p�x�i�f�B�O���[�j��ݒ肷�郁���o�֐�
	void SetDeg(const float angleD_);
	//�����̊p�x�i�f�B�O���[�j���擾���郁���o�֐�
	float GetDeg() const;
	//�ǂݍ���ł������r�b�g�}�b�v��`��(��]����)
	void Draw(Image * const mybitmap_, const bool rot_ = false);
	//�ǂݍ���ł������r�b�g�}�b�v��`��(��]����)
	void Draw(Image * const mybitmap_, const Frec * const frSrc, const bool rot_ = false);
	//�s�������瓧���܂Œl���w�肵�ĕ`��(�����F�͖��������)
	void DrawAlpha(Image * const mybitmap_, byte alpha_ = 255);
	//��`�̊O�g��`�悷�郁���o�֐�
	void Draw(int r_ = 255, int g_ = 255, int b_ = 255);
	//��`���m�̐�����������p�����o�֐�
	bool CheckHit(const Rec * const rec_);
	//��`�Ɠ_�̐ڐG����p�����o�֐�
	bool CheckHit(const Point * const pos_);
	//��`�Ɠ_�̐ڐG����p�����o�֐�
	bool CheckHit(const float x_, const float y_);
	//�����̍����ڐG���Ă��邩
	//���肷�郁���o�֐�
	bool CheckHitLeft(const Rec * const rec_);
	//�����̉E���ڐG���Ă��邩
	//���肷�郁���o�֐�
	bool CheckHitRight(const Rec * const rec_);
	//�����̏オ�ڐG���Ă��邩
	//���肷�郁���o�֐�
	bool CheckHitTop(const Rec * const rec_);
	//�����̉����ڐG���Ă��邩
	//���肷�郁���o�֐�
	bool CheckHitBottom(const Rec * const rec_);
	//��`�̕�
	float GetW() const;
	//��`�̍���
	float GetH() const;
	//�w����W�Ƃ̊p�x(���W�A��)���擾���郁���o�֐�
	float GetRad(const float x_, const float y_) const;
	//�ʂ̋�`�Ƃ̊p�x(���W�A��)���擾���郁���o�֐�
	float GetRad(const Rec * const rec_) const;
	//�w����W�Ƃ̊p�x(�f�B�O���[)���擾���郁���o�֐�
	float GetDeg(const float x_, const float y_) const;
	//�w����W�Ƃ̊p�x(�f�B�O���[)���擾���郁���o�֐�
	float GetDeg(const Point * const pos_) const;
	//�ʂ̋�`�Ƃ̊p�x(�f�B�O���[)���擾���郁���o�֐�
	float GetDeg(const Rec * const rec_) const;
	//��`���ړ�������
	void Move(const Vector2 * const vec2_);
	//�_�Ƃ̋������擾���郁���o�֐�
	float GetDist(const float x_, const float y_) const;
	//�_�Ƃ̋������擾���郁���o�֐�
	float GetDist(const Point * const pos_) const;
	//�ʂ̋�`�Ƃ̋������擾���郁���o�֐�
	float GetDist(const Rec * const rec_) const;
	//��`�̒��S�_��Ԃ������o�֐�
	const Point &GetPos() const;
	//��`�̒��S�_��X���W
	float GetPosX() const;
	//��`�̒��S�_��Y���W
	float GetPosY() const;
	//
	const Point &GetTL() const;
	//
	const Point &GetTR() const;
	//
	const Point &GetBL() const;
	//
	const Point &GetBR() const;
};

/*�~�N���X*/
class Circle
{
private:
	/*���S���W*/
	Point center;
	/**/
	HDC hOff;
	/*�y��*/
	HPEN hPen;
	/*�J���[*/
	COLORREF color;
	/*���a*/
	float radius;

public:
	/*�R���X�g���N�^*/
	Circle();
	/*�R���X�g���N�^*/
	Circle(const Point * const position_, const float radius_);
	/*���S���W�ݒ�*/
	void SetPos(const Point * const pos_);
	/*���a�ݒ�*/
	void SetRadius(const float radius_);
	/*�F�ݒ�*/
	void SetColor(const byte r_, const byte g_, const byte b_);
	/*���W�擾*/
	const Point &GetPos() const;
	/*X���W�擾*/
	const float GetPosX() const;
	/*Y���W�擾*/
	const float GetPosY() const;
	/*���a�擾*/
	const float GetRadius() const;
	/*�`��*/
	void Draw();
	/*�����蔻��*/
	const bool CheckHit(const Circle * const circle_) const;
	/*�����蔻��*/
	const bool CheckHit(const Point * const point_) const;
};

/*���N���X*/
class Line
{
	/*�n�_*/
	Point spos;
	/*�I�_*/
	Point epos;
	/*����~�Ƃ̌�_*/
	Point inter;
	/**/
	Vector2 vec2;
	/**/
	HDC hOff;
	/*�y��*/
	HPEN hPen;
	/*�J���[*/
	COLORREF color;
	/*�p�x*/
	float angle;
	/*��*/
	int width;
	/*����*/
	float len;
public:
	/*�R���X�g���N�^*/
	Line();
	/*�R���X�g���N�^*/
	Line(const Point * const spos_, const Point * const epos_);
	/*�n�_�ݒ�*/
	void SetPos(const Point * const spos_);
	/*�n�_�ƏI�_�ݒ�*/
	void SetPos(const Point * const spos_, const Point * const epos_);
	/*�n�_�ƏI�_�ݒ�*/
	void SetPos(const Point * const spos_, const float angleD_, const float len_);
	/*�n�_�ݒ�*/
	void SetSPos(const Point * const spos_);
	/*�I�_�ݒ�*/
	void SetEPos(const Point * const epos_);
	/*�F�ݒ�*/
	void SetColor(const byte r_, const byte g_, const byte b_);
	/*���ݒ�*/
	void SetWidth(const int width_);
	/*�p�x�ݒ�*/
	void SetDeg(const float angleD_);
	/*�����ݒ�*/
	void SetLen(const float len_);
	/*�n�_�擾*/
	const Point &GetSPos() const;
	/*�I�_�擾*/
	const Point &GetEPos() const;
	/*�p�x�擾*/
	float GetDeg() const;
	/*�p�x�擾*/
	float GetDeg(const Line * const line_) const;
	/*�p�x�擾*/
	float GetDeg(const Rec * const rec_) const;
	/*�p�x�擾*/
	float GetDeg(const Point * const pos_) const;
	/*�����擾*/
	float GetLen() const;
	/*�����擾*/
	float GetDist(const Circle * const circle_) const;
	/*�����擾*/
	float GetDist(const Point * const pos_) const;
	/*�x�N�g���擾*/
	const Vector2 &GetVec() const;
	/*���Ɖ~�̌�_���擾*/
	const Point &GetPOI(const Circle * const circle_);
	/*���Ɛ��̌�_���擾*/
	const Point &GetPOI(const Line * const line_);
	/*�ړ�*/
	void Move(const float movespd_);
	/*�`��*/
	void Draw();
	/*�����蔻��*/
	bool CheckHit(const Line * const line_);
	/*�����蔻��*/
	bool CheckHit(const Rec * const rec_);
	/*�����蔻��*/
	bool CheckHit(const Circle * const circle_);
};

//�t�@�C���𑀍삷��N���X
class FileIO
{
private:
	FILE * fp;

public:
	//�R���X�g���N�^
	FileIO();
	//�f�X�g���N�^
	~FileIO();
	//�t�@�C���֏������ރ����o�֐�
	bool SaveFile(const void * const buf_, const int elementsize_);
	//�t�@�C������ǂݍ��ރ����o�֐�
	bool LoadFile(void * const buf_, const int elementsize_);
	//�t�@�C���ւ̏�������
	template<class T>
	void operator << (const T &in_)
	{
		if (!fp) return;
		fwrite(&in_, sizeof(in_), 1, fp);
	}
	//�t�@�C������̓ǂݍ���
	template<class T>
	void operator >> (T &out_)
	{
		if (!fp && feof(fp) == EOF) return;
		fread(&out_, sizeof(out_), 1, fp);
	}
	//�t�@�C�����J�������o�֐�
	bool Open(const char *filename_, const char * const format_);
	//�t�@�C������郁���o�֐�
	bool Close();
};

//�^�C�}�[�N���X
class Timer
{
private:
	bool active;
	int interval;
	int cntmax;
	int cnt;

public:
	//�R���X�g���N�^
	Timer(const int interval_);
	//�R���X�g���N�^
	Timer();
	//�C���^�[�o���ݒ�
	void Set(const int interval_);
	//�X�^�[�g
	void Start();
	//�C���^�[�o�����Ƃ�true��Ԃ�
	bool Tick();
	//�X�g�b�v
	void Stop();
};

class Pixel
{
	Point pPos;
	COLORREF cColor;
	HDC hOff;
public:
	Pixel()
		:
		pPos({}),
		cColor(0),
		hOff(Rec::GetOffScreenHandle())
	{
	}
	Pixel(const Point &crefpPos, const COLORREF ccColor)
		:
		pPos(crefpPos),
		cColor(ccColor),
		hOff(Rec::GetOffScreenHandle())
	{
	}
	Pixel(const Pixel &crefPixel)
		:
		pPos(crefPixel.pPos),
		cColor(crefPixel.cColor),
		hOff(Rec::GetOffScreenHandle())
	{
	}
	const Point SetPos(const Point * const cppPos)
	{
		const Point cpOld = pPos;
		pPos = *cppPos;
		return cpOld;
	}
	const COLORREF SetColor(const COLORREF ccColor)
	{
		const COLORREF ccOld = cColor;
		cColor = ccColor;
		return ccOld;
	}
	const Point &GetPos() const
	{
		return pPos;
	}
	const float GetPosX() const
	{
		return pPos.x;
	}
	const float GetPosY() const
	{
		return pPos.y;
	}
	void Draw() const
	{
		SetPixel(hOff, int(pPos.x), int(pPos.y), cColor);
	}
};

#ifdef _DEBUG
struct DBG
{
private:
	static Point spDrawPos;
	static Font sfFont;
public:
	static void ResetPos()
	{
		spDrawPos = { Rec::GetCameraPosX() - Rec::Win.r * 0.5f, Rec::GetCameraPosY() - Rec::Win.b * 0.5f };
	}
	template<class Type>
	static void OutPut(const Type &tValue)
	{
		sfFont.FontCreate("���C���I");
		sfFont.SetColor(RGB(150, 200, 255));
		sfFont.Draw(&spDrawPos, std::to_string(tValue).c_str());
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
	static void OutPut(const char(&ccaFmt)[])
	{
		sfFont.FontCreate("���C���I");
		sfFont.SetColor(RGB(150, 200, 255));
		sfFont.Draw(&spDrawPos, ccaFmt);
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
	template<unsigned short usBufSize, class Type>
	static void OutPut(const char(&ccaFmt)[], const Type &tValue)
	{
		sfFont.FontCreate("���C���I");
		sfFont.SetColor(RGB(150, 200, 255));
		char caText[usBufSize] = {};
		sprintf_s(caText, ccaFmt, tValue);
		sfFont.Draw(&spDrawPos, caText);
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
	template<unsigned short usBufSize, class Type>
	static void OutPut(const char * const ccpFmt, const Type &tValue)
	{
		sfFont.FontCreate("���C���I");
		sfFont.SetColor(RGB(150, 200, 255));
		char caText[usBufSize] = {};
		sprintf_s(caText, ccpFmt, tValue);
		sfFont.Draw(&spDrawPos, caText);
		sfFont.Release();
		spDrawPos.y += 20.f;
		if (spDrawPos.y >= Rec::GetCameraPosY() - Rec::Win.b * 0.5f + 1000.f)
		{
			spDrawPos.x += 200.f;
			spDrawPos.y = Rec::GetCameraPosY() - Rec::Win.b * 0.5f;
		}
	}
};
#endif