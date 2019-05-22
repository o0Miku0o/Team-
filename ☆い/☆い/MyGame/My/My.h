#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <stdarg.h>
#include <tchar.h>
#include <string>
#include <time.h>
#include <vector>
#include <map>
#include <mmsystem.h>
#include <typeinfo>
#include "FixedPoint.h"
#include "CGDM.h"

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

//��������
//Xinput
//Xaudio

#ifdef _DEBUG
#define DBG_OUT(ccpDbgText) MessageBox(nullptr, (const char * const)ccpDbgText, "DBG", MB_OK)
#define DBG_SPRINTF(cStrName, cFmt, Src) char cStrName[1024]; sprintf_s(cStrName, cFmt, Src)
#define \
DBG_FONT(pPoint, cFmt, Src)\
{\
	char cDbg[1024];\
	sprintf_s(cDbg, cFmt, Src);\
	Font f;\
	f.FontCreate("���C���I");\
	f.Draw(&pPoint, cDbg);\
}
#else
#define DBG_OUT(ccpDbgText) __noop
#define DBG_SPRINTF(StrName, Fmt, StrSrc) __noop
#define DBG_FONT(pPoint, cStrName, cFmt, Src) __noop
#endif

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
/*����cos(x)*/
inline const double cos_fast(double angle)
{
	static const double waru[5] = { 1.0 / (3 * 4 * 5 * 6 * 7 * 8 * 9 * 10),-1.0 / (3 * 4 * 5 * 6 * 7 * 8),1.0 / (3 * 4 * 5 * 6),-1.0 / (3 * 4),1.0 };
	constexpr double cedVal1 = 1.0 / 32.0;
	constexpr double cedVal2 = -1.0 / (3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
	double y = cedVal2;
	const double *p = waru;
	/*int q = (int)(x / (2.0 * PI));*/
	//x = x - q * (2.0 * PI);
	angle = angle * cedVal1;
	angle = angle * angle;
	do 
	{
		y = y * angle + (*p);
		++p;
	} while (p < waru + 5);
	y = y * angle;
	for (byte b = 0; b < 5; ++b) y = y * (4.0 - y);
	return 1.0 - (y * 0.5);
}
/*����cos(x)*/
inline const float cos_fast(float angle)
{
	return (float)cos_fast((double)angle);
}
/*����sin(x)*/
inline const double sin_fast(double angle)
{ 
	return cos_fast(angle - PI * 0.5);
}
/*����sin(x)*/
inline const float sin_fast(float angle)
{
	return (float)cos_fast(angle - PI * 0.5);
}
/*����tan(x)*/
inline const double tan_fast(double angle)
{ 
	return FToD(Div(FP(cos_fast(angle - PI * 0.5)), FP(cos_fast(angle))));
}
/*����tan(x)*/
inline const float tan_fast(float angle)
{
	return (float)FToD(Div(FP(cos_fast(angle - PI * 0.5)), FP(cos_fast((double)angle))));
}
/*����sin(x)�ƍ���cos(x)�̓����擾*/
inline void sincos_fast(double angle, double * const x, double * const y)
{
	angle = angle / 32.0;
	static double waru[8] = { -1.0 / (3 * 4 * 5 * 6 * 7 * 8),-1.0 / (2 * 3 * 4 * 5 * 6 * 7),1.0 / (3 * 4 * 5 * 6),1.0 / (2 * 3 * 4 * 5),-1.0 / (3 * 4),-1.0 / (2 * 3),1.0,1.0 };
	double c = 1.0 / (3 * 4 * 5 * 6 * 7 * 8 * 9 * 10), s = 1.0 / (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9), *p = waru, z = angle * angle;
	do 
	{
		c = c * z + (*p);
		++p;
		s = s * z + (*p);
		++p;
	} while (p < waru + 8);
	c = c * z;
	s = s * angle;
	for (byte b = 0; b < 5; ++b) 
	{
		s = s * (2.0 - c);
		c = c * (4.0 - c);
	}
	*x = 1.0 - c / 2.0;
	*y = s;
}
/*����sin(x)�ƍ���cos(x)�̓����擾*/
inline void sincos_fast(float angle, float * const x, float * const y)
{
	double dX = 0.0, dY = 0.0;
	sincos_fast((double)angle, &dX, &dY);
	*x = (float)dX;
	*y = (float)dY;
}
/*abs(x)*/
template<class Value>
inline constexpr Value Abs(const Value &x)
{
	return Value((x > 0) ? x : ((x < 0) ? -x : 0));
}
/*max(a, b)*/
template<class Value>
inline constexpr Value Max(const Value &a, const Value &b)
{
	return Value((a > b) ? a : b);
}
/*min(a, b)*/
template<class Value>
inline constexpr Value Min(const Value &a, const Value &b)
{
	return Value((a < b) ? a : b);
}
/*min(max(v, l), h)*/
template<class Value>
inline constexpr Value Clamp(const Value &v, const Value &l, const Value &h)
{
	return Min(Max(v, l), h);
}
/*a��b�����ւ���*/
template<class Value>
inline void Swap(Value &a, Value &b)
{
	if (a == b) return;
	a ^= b ^= a ^= b;
}
/*a��b�����ւ���*/
template<>
inline void Swap(float &a, float &b)
{
	if (a == b) return;
	const float fTmp = a;
	a = b;
	b = fTmp;
}
/*a��b�����ւ���*/
template<>
inline void Swap(double &a, double &b)
{
	if (a == b) return;
	const double dTmp = a;
	a = b;
	b = dTmp;
}
/*a��b�����ւ���*/
template<class Value1, class Value2>
inline void Swap(double &a, float &b)
{
	if (a == (double)b) return;
	const double dTmp = a;
	a = (double)b;
	b = (float)dTmp;
}
/*a��b�����ւ���*/
template<class Value1, class Value2>
inline void Swap(float &a, double &b)
{
	if ((double)a == b) return;
	const double dTmp = (double)a;
	a = (float)b;
	b = dTmp;
}
/*rand��float��*/
inline const float randf()
{
	return (float)rand();
}
/*rand��float�Łin�Ŋ������]��j*/
inline const float randf(const int n)
{
	return float(rand() % n);
}
/*�t�@���X���ǂ���*/
inline constexpr bool IsFalse(const bool bResult)
{
	return !bResult;
}
//My�l�[���X�y�[�X���̃N���X�Ŏg�p���铧���F
constexpr COLORREF TRANSPARENT_COLOR = RGB(255, 0, 255);
constexpr COLORREF WHITE_COLOR = RGB(255, 255, 255);

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
	/*�������u��*/
	bool Down(const char cKey);
	/*�����Ă���*/
	bool On(const char cKey);
	/*�������u��*/
	bool Up(const char cKey);
	/*�����Ă���*/
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
	/*�}�E�X�J�[�\���̕\���̗L��*/
	static bool Visible(const bool bVisible);
	/*���݂̃}�E�X���͏�Ԃ��擾*/
	byte Now(const MouseButton but_);
	/*�O�t���[���̃}�E�X���͏�Ԃ��擾*/
	byte Prev(const MouseButton but_);
	/*�������u��*/
	bool Down(const MouseButton but_);
	/*�����Ă���*/
	bool On(const MouseButton but_);
	/*�������u��*/
	bool Up(const MouseButton but_);
	/*�����Ă���*/
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
	//�r�b�g�}�b�v���擾
	const BITMAP &GetBmpInfo() const;
	//�r�b�g�}�b�v�Ɗ֘A�t�����Ă���f�o�C�X���擾
	const HDC GetImageHandle() const;
	//�}�X�N�r�b�g�}�b�v�Ɗ֘A�t�����Ă���f�o�C�X���擾
	const HDC GetMaskHandle() const;
	//�}�X�N�r�b�g�}�b�v���擾
	const HBITMAP GetMaskBitMap() const;
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
	bool FontCreate(const char *fontname_, int h_ = 0, float angleD_ = 0, const FontOP *fontoption_ = &FOP_DEFAULT);
	//�t�H���g�̏���
	void Release();
	//�F�ݒ�
	const COLORREF SetColor(const COLORREF col_);
	//�F�ݒ�
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_);
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

	static bool bIsConnect;

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
	/*�{�^�����������u��*/
	bool Down(const Joy_Button but_);
	/*�{�^���������Ă���*/
	bool On(const Joy_Button but_);
	/*�{�^���𗣂����u��*/
	bool Up(const Joy_Button but_);
	/*�{�^���𗣂��Ă���*/
	bool Off(const Joy_Button but_);
	/*�����L�[���������u��*/
	bool Down(const Joy_Direct direct_);
	/*�����L�[�������Ă���*/
	bool On(const Joy_Direct direct_);
	/*�����L�[�𗣂����u��*/
	bool Up(const Joy_Direct direct_);
	/*�����L�[�𗣂��Ă���*/
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
	static HDC hAlphaDc;
	static HBITMAP hAlphaBmp;
	static BLENDFUNCTION bBlendFunc;
	static Frec frZoom;
	static Point Cam;
	static Point pAdjust;
	static POINT pDrawPoint[5];
	Point p[5];
	COLORREF cColor;
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
	//��ʂ�h��Ԃ�
	static void FullPaint(const COLORREF ccColor);
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
	//�g���̐F�ݒ�
	const COLORREF SetColor(const COLORREF ccColor);
	//�F�ݒ�
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_);
	//��`���ړ�������
	void SetPos(const Point * const pos_);
	//��`���g��k��������
	void Scaling(const float recw_, const float rech_);
	//�����̊p�x�i�f�B�O���[�j��ݒ肷�郁���o�֐�
	void SetDeg(const float angleD_);
	//�����̊p�x�i�f�B�O���[�j���擾���郁���o�֐�
	float GetDeg() const;
	//�ǂݍ���ł������r�b�g�}�b�v��`��
	void Draw(Image * const mybitmap_, const bool rot_ = false);
	//�ǂݍ���ł������r�b�g�}�b�v��`��
	void Draw(Image * const mybitmap_, const Frec * const frSrc, const bool rot_ = false);
	//�s�������瓧���܂Œl���w�肵�ĕ`��
	void DrawAlpha(Image * const mybitmap_, byte alpha_ = 255);
	//�s�������瓧���܂Œl���w�肵�ĕ`��
	void DrawAlpha(Image * const mybitmap_, const Frec * const frSrc, byte alpha_ = 255);
	//��`�̊O�g��`�悷�郁���o�֐�
	void Draw();
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
	//��`�̍���̍��W���擾
	const Point &GetTL() const;
	//��`�̉E��̍��W���擾
	const Point &GetTR() const;
	//��`�̍����̍��W���擾
	const Point &GetBL() const;
	//��`�̉E���̍��W���擾
	const Point &GetBR() const;
	//���݂̃T�C�Y���i0, 0�j���ǂ���
	const bool SizeZero() const;
};

/*BMP�t�@�C���Ƃ��ăr�b�g�}�b�v���o��*/
inline const bool SaveBitMap(HDC hSrc, const Frec * const cfrpSrc, const char * const ccpFileName)
{
	HANDLE hFile = CreateFile
	(
		ccpFileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) return 1;
	long lHeadSize = (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO));
	long lWidthSize = ((long)cfrpSrc->r * sizeof(DWORD));
	long lImageSize = (lWidthSize * (long)cfrpSrc->b);

	// BITMAPFILEHEADER�̏�����
	BITMAPFILEHEADER bmpHead = { 0 };
	bmpHead.bfType = 0x4D42;       // ���ʎq(BM)
	bmpHead.bfSize = lHeadSize + lImageSize;
	bmpHead.bfReserved1 = 0;
	bmpHead.bfReserved2 = 0;
	bmpHead.bfOffBits = lHeadSize;

	// BITMAPINFO�̏�����
	BITMAPINFO bmpInfo = { 0 };
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = (long)cfrpSrc->r;
	bmpInfo.bmiHeader.biHeight = (long)cfrpSrc->b;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;
	bmpInfo.bmiHeader.biXPelsPerMeter = 0;
	bmpInfo.bmiHeader.biYPelsPerMeter = 0;
	bmpInfo.bmiHeader.biClrUsed = 0;
	bmpInfo.bmiHeader.biClrImportant = 0;

	// DIB�Z�N�V�����̍쐬
	// �s�N�Z���z��
	LPDWORD lpPixel = nullptr;
	// �r�b�g�}�b�v
	HBITMAP hBitmap = CreateDIBSection(NULL, &bmpInfo, DIB_RGB_COLORS, (LPVOID*)&lpPixel, NULL, 0);
	// �ۑ��X�N���[��
	HDC hSaveDC = CreateCompatibleDC(hSrc);

	SelectObject(hSaveDC, hBitmap);
	// �ۑ��̈�̃R�s�[
	BitBlt(hSaveDC, 0, 0, (int)cfrpSrc->r, (int)cfrpSrc->b, hSrc, (int)cfrpSrc->l, (int)cfrpSrc->t, SRCCOPY);

	// �t�@�C���ɏ�������
	DWORD dwSize = 0; 
	WriteFile(hFile, &bmpHead, sizeof(BITMAPFILEHEADER), &dwSize, NULL);
	WriteFile(hFile, &bmpInfo, sizeof(BITMAPINFO), &dwSize, NULL);
	WriteFile(hFile, lpPixel, lImageSize, &dwSize, NULL);

	// DIB�Z�N�V�����̔j��
	DeleteDC(hSaveDC);
	DeleteObject(hBitmap);
	CloseHandle(hFile);
	return 0;
}

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
	const COLORREF SetColor(const COLORREF color_);
	/*�F�ݒ�*/
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_);
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
	const COLORREF SetColor(const COLORREF color_);
	/*�F�ݒ�*/
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_);
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
	void Draw(const u_int penstyle_ = PS_SOLID);
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
	HPEN hPen;
	HBRUSH hBrush;
	byte bSize;
public:
	Pixel();
	~Pixel();
	Pixel(const Point &crefpPos, const COLORREF ccColor, const byte cbSize);
	Pixel(const Pixel &crefPixel);
	const Point SetPos(const Point * const cppPos);
	const COLORREF SetColor(const COLORREF ccColor);
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_);
	const byte SetSize(const byte cbSize);
	const Point &GetPos() const;
	const float GetPosX() const;
	const float GetPosY() const;
	void Draw() const;
};

class MyArc
{
private:
	Point pCenter;
	float fRadius;
	float fAngle;
	float fAngleRange;
	COLORREF cColor;
	HDC hOff;
	HPEN hPen;
public:
	MyArc()
		: pCenter({})
		, fRadius(0.f)
		, fAngle(0.f)
		, fAngleRange(0.f)
		, hOff(Rec::GetOffScreenHandle())
		, hPen(CreatePen(PS_SOLID, 1, RGB(255, 255, 255)))
	{

	}
	MyArc(const MyArc &raaOther)
		: pCenter(raaOther.pCenter)
		, fRadius(raaOther.fRadius)
		, fAngle(raaOther.fAngle)
		, fAngleRange(raaOther.fAngleRange)
		, hOff(Rec::GetOffScreenHandle())
		, hPen(CreatePen(PS_SOLID, 1, RGB(255, 255, 255)))
	{

	}
	~MyArc()
	{
		if (hPen) DeleteObject(hPen);
	}
	const Point SetPos(const Point * const appCenterPos)
	{
		pCenter.x = appCenterPos->x;
		pCenter.y = appCenterPos->y;
		return pCenter;
	}
	const float SetRadius(const float afRadius)
	{
		fRadius = afRadius;
		return fRadius;
	}
	void SetAngle(const float afAngle, const float afAngleRange)
	{
		fAngle = afAngle;
		fAngleRange = afAngleRange;
	}
	const COLORREF SetColor(const COLORREF color_)
	{
		cColor = color_;
		if (hPen) DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 1, cColor);
		return cColor;
	}
	const COLORREF SetColor(const byte abR, const byte abG, const byte abB)
	{
		cColor = RGB(abR, abG, abB);
		if (hPen) DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 1, cColor);
		return cColor;
	}
	void Draw() const
	{
		HGDIOBJ hOld = SelectObject(hOff, hPen);
		const Point pAdjust = Rec::AdjustCamPos(&pCenter);
		const float fModAngle = ModAngle(fAngle - (fAngleRange / 2));
		const float fModAngleMax = ModAngle(fAngle + (fAngleRange / 2));
		float fSinCosX = 0.f;
		float fSinCosY = 0.f;
		sincos_fast(DtoR(fModAngle), &fSinCosX, &fSinCosY);
		int iX = int(fSinCosX * fRadius + pAdjust.x);
		int iY = int(fSinCosY * fRadius + pAdjust.y);
		MoveToEx(hOff, iX, iY, nullptr);
		for (float f = 0; f < fAngleRange; ++f)
		{
			sincos_fast(DtoR(fModAngle + f), &fSinCosX, &fSinCosY);
			iX = int(fSinCosX * fRadius + pAdjust.x);
			iY = int(fSinCosY * fRadius + pAdjust.y);
			LineTo(hOff, iX, iY);
		}
		SelectObject(hOff, hOld);
	}
};

/*�p�[�e�B�N���N���X*/
class Particle
{
	/*�p�[�e�B�N�����X�g�̐擪*/
	static Particle * sppTop;
	/*��*/
	struct _vP
	{
		Pixel pPix;
		Point pPos;
		Point pIniPos;
		COLORREF cColor;
		fix fSpd;
		fix fRandX;
		fix fRandY;
		fix fSpdX;
		fix fSpdY;
		fix fAngle;
		byte bLifeCount;
		_vP()
			:
			pPix(),
			pIniPos(),
			pPos(),
			bLifeCount(byte(rand() % 100)),
			cColor(RGB(255, 255, 255)),
			fSpd(1.f),
			fAngle(DtoR(ModAngle(270.f))),
			fRandX(DtoR(rand() % 61 - 30.f)),
			fRandY(DtoR(rand() % 61 - 30.f)),
			fSpdX(cos_fast(fAngle + fRandX) * fSpd),
			fSpdY(sin_fast(fAngle + fRandY) * fSpd)
		{

		}
	};
	/*���̂܂Ƃ܂�*/
	std::vector<_vP> vpPix;
	/*���̗v�f*/
	Particle *next;
	/*�O�̗v�f*/
	Particle *prev;
	/*����*/
	byte bLifeMax;
	/*�Đ��t���O*/
	bool bUpdateFlag;

	/*�ꗱ�X�V*/
	void Update();
	/*�ꗱ�`��*/
	void Draw() const;
public:
	/*�S�̂̍X�V*/
	static void UpdateAll();
	/*�S�̂̕`��*/
	static void DrawAll();

	/*�R���X�g���N�^*/
	Particle();
	/*�f�X�g���N�^*/
	~Particle();
	/*���ݒ�*/
	void SetNum(const unsigned int cuiNum);
	/*�傫���ݒ�*/
	void SetSize(const byte cbSize);
	/*���̈ړ��O�̏����ʒu�ݒ�*/
	void SetInitPos(const Point * const cppPos, const short csMax = 10, const short csMin = -10);
	/*�����ݒ�*/
	void SetLife(const byte cbLifeMax);
	/*���̈ړ����x�ݒ�*/
	void SetSpd(const float cfSpd, const short csMax = 1, const short csMin = -1);
	/*���̈ړ��p�x�ݒ�*/
	void SetAngle(const float cfAngle, const short csMax = 45, const short csMin = -45);
	/*�F�ݒ�*/
	void SetColor(const COLORREF ccColor, const char ccMax = 100, const char ccMin = -100);
	/*�p�[�e�B�N���Đ�*/
	void Play();
	/*�p�[�e�B�N���X�g�b�v*/
	void Stop();
};
/*���v���C�Ǘ��N���X*/
class Rep
{
	/*���v���C�f�[�^���X�g�̐擪*/
	static Rep *rpTop;
	/*���v���C�f�[�^�ǂݍ��ݎ��̎Q�ƃ|�C���^*/
	static Rep *rpOut;
	/*�f�[�^�S�̂̃T�C�Y*/
	static size_t sDataSize;

	/*���ۂ̃f�[�^*/
	double dData;
	/*���̗v�f*/
	Rep *rpNext;
	/*�O�̗v�f*/
	Rep *rpPrev;
	/*����ɃC���X�^���X������Ȃ��悤�ɃR���X�g���N�^�𕕈�*/
	Rep();
public:
	/*�I�[�ɗv�f��ǉ�*/
	static bool Push(const double dData);
	/*�ǂݍ��݃f�[�^������擾*/
	static const double Output();
	/*�f�[�^�̓ǂݍ��ݒn�_��ݒ�*/
	static bool SetPosition(const u_int uiIdx);
	/*�f�[�^���X�g���擾*/
	static const Rep * const GetDataList();
	/*���v���C�f�[�^���X�g���t�@�C���֏�������*/
	static bool SaveFile(const char * const ccpFileName);
	/*�t�@�C�����烊�v���C�f�[�^���X�g��ǂݍ���*/
	static bool LoadFile(const char * const ccpFileName);
	/*���v���C�f�[�^���X�g���폜*/
	static bool Clear();
	/*���̗v�f���擾*/
	const Rep * const GetNext() const;
	/*�O�̗v�f���擾*/
	const Rep * const GetPrev() const;
	/*���ۂ̃f�[�^���擾*/
	const double GetData() const;
};