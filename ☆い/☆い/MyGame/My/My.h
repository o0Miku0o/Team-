#pragma once
#include <Windows.h>
#include <stdarg.h>
#include <string>
#include <time.h>
#include <vector>
#include <array>
#include <map>
#include <mmsystem.h>
#include <thread>
#include <mutex>
#include <algorithm>
#include "Stream.h"
#include "FixedPoint.h"
#include "CADAM.h"
#include "Debug.h"
#include "MciScript.h"
#include "MciWnd.h"
#include "DShow.h"

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "winmm.lib")

//��������
//Xinput
//Xaudio

/*4������int�^�ɕϊ�(�G���[�`�F�b�N�Ȃǂ͂Ȃ�)*/
inline const int FourCharToInt(const BYTE *abpFourStr)
{
	return (*((int *)abpFourStr));
}
inline const int FourCharToInt(const char *abpFourStr)
{
	return (*((int *)abpFourStr));
}

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
inline void Swap(Value &a, Value &b);
/*a��b�����ւ���*/
template<class Value>
inline void Swap(Value &a, Value &b)
{
	const Value tmp = a;
	a = b;
	b = tmp;
}
/*a��b�����ւ���*/
template<>
inline void Swap<>(int &a, int &b)
{
	if (a == b) return;
	a ^= b ^= a ^= b;
}
/*a��b�����ւ���*/
template<>
inline void Swap<>(LONG &a, LONG &b)
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
//
inline constexpr bool LineCheckCross(const float ax, const float ay, const float bx, const float by, const float cx, const float cy, const float dx, const float dy)
{
	float ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
	float tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
	float tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
	float td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);

	return tc * td < 0.f && ta * tb < 0.f;
};
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
	Vector2(float x_, float y_)
		: x(x_), y(y_)
	{

	}
	//�R���X�g���N�^
	Vector2()
		: x(0.f), y(0.f)
	{

	}
	//�R�s�[�R���X�g���N�^
	Vector2(const Vector2 &cpy_)
		: x(cpy_.x), y(cpy_.y)
	{

	}
	//�p�x�ƒ�������x�N�g����ݒ�
	void SetVec(const float angleD_, const float len_)
	{
		const double ang = (double)DtoR(ModAngle(angleD_));
		x = (float)cos_fast(ang) * len_;
		y = (float)sin_fast(ang) * len_;

		//x = cos(DtoR(angleD_)) * dist_;
		//y = sin(DtoR(angleD_)) * dist_;
	}
	//X�̒l���擾
	const float GetX() const
	{
		return x;
	}
	//Y�̒l���擾
	const float GetY() const
	{
		return y;
	}
	//�x�N�g���̒������擾
	const float GetLen() const
	{
		return Sqrt(x * x + y * y);
	}
	//�x�N�g���̊p�x���擾
	const float GetDeg() const
	{
		return RtoD(atan2(y, x));
	}
	//���ς��v�Z
	const float Dot(const Vector2 *vec2_) const
	{
		return (x * vec2_->x + y * vec2_->y);
	}
	//�O�ς��v�Z
	const float Cross(const Vector2 *vec2_) const
	{
		return (x * vec2_->y - y * vec2_->x);
	}
	//�x�N�g���̃X�J���[�{
	Vector2 &MulVec(const float scalar_)
	{
		x *= scalar_;
		y *= scalar_;
		return *this;
	}
	//�x�N�g���̃X�J���[�{
	const Vector2 operator * (const float scalar_) const
	{
		return Vector2(x * scalar_, y * scalar_);
	}
	//�x�N�g���̔�r
	const bool operator == (const Vector2 &vec2_) const
	{
		return ((x == vec2_.x) ? ((y == vec2_.y) ? 1 : 0) : 0);
	}
	//�x�N�g���̔�r
	const bool operator != (const Vector2 &vec2_) const
	{
		return ((x != vec2_.x) ? 1 : ((y != vec2_.y) ? 1 : 0));
	}
};

//�񎟌����W�\����
struct Point
{
	float x;
	float y;
	/*�R���X�g���N�^*/
	Point()
		:
		x(0.f),
		y(0.f)
	{

	}
	/*�R���X�g���N�^*/
	Point(const float x_, const float y_)
		:
		x(x_),
		y(y_)
	{

	}
};

//�t���[�g�^RECT
struct Frec
{
	float l;
	float r;
	float t;
	float b;
	/*�R���X�g���N�^*/
	Frec()
		:
		l(0.f),
		r(0.f),
		t(0.f),
		b(0.f)
	{

	}
	/*�R���X�g���N�^*/
	Frec(const float l_, const float t_, const float r_, const float b_)
		:
		l(l_),
		r(r_),
		t(t_),
		b(b_)
	{

	}
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
	static std::shared_ptr<KB> instance;

	/*�R���X�g���N�^*/
	KB()
		: nowkey()
		, prevkey()
	{

	}
public:
	//�L�[���͂��擾���郁���o�֐�
	static bool GetKeyState()
	{
		if (!instance) return 1;
		CopyMemory(instance->prevkey, instance->nowkey, sizeof(instance->nowkey));
		GetKeyboardState(instance->nowkey);
		return 0;
	}
	/*�C���X�^���X�̃A�h���X���擾*/
	static std::shared_ptr<KB> &GetState()
	{
		return instance;
	}

	static void Create()
	{
		instance = std::shared_ptr<KB>(new KB);
	}
	/*�������u��*/
	bool Down(const char cKey)
	{
		const bool lcbNow = nowkey[cKey] & 0x80;
		const bool lcbPrev = prevkey[cKey] & 0x80;
		return (!lcbPrev && lcbNow);
	}
	/*�����Ă���*/
	bool On(const char cKey)
	{
		const bool lcbNow = nowkey[cKey] & 0x80;
		const bool lcbPrev = prevkey[cKey] & 0x80;
		return (lcbPrev && lcbNow);
	}
	/*�������u��*/
	bool Up(const char cKey)
	{
		const bool lcbNow = nowkey[cKey] & 0x80;
		const bool lcbPrev = prevkey[cKey] & 0x80;
		return (lcbPrev && !lcbNow);
	}
	/*�����Ă���*/
	bool Off(const char cKey)
	{
		const bool lcbNow = nowkey[cKey] & 0x80;
		const bool lcbPrev = prevkey[cKey] & 0x80;
		return (!lcbPrev && !lcbNow);
	}
};

//�}�E�X�N���X
class MS
{
private:
	static std::shared_ptr<MS> instance;
	static HWND hWnd;

	Point pos;
	short nowbut[MS_BUT_MAX];
	short prevbut[MS_BUT_MAX];

	/*�R���X�g���N�^*/
	MS()
		: nowbut()
		, prevbut()
		, pos(0.f, 0.f)
	{

	}
public:

	//�}�E�X���͂��擾���郁���o�֐�
	static bool GetMouseState()
	{
		if (!instance) return 1;
		CopyMemory(instance->prevbut, instance->nowbut, sizeof(instance->nowbut));
		static const char b[MS_BUT_MAX] = { VK_LBUTTON ,VK_RBUTTON ,VK_MBUTTON };
		for (int i = 0; i < MS_BUT_MAX; ++i)
		{
			instance->nowbut[i] = GetAsyncKeyState(b[i]);
		}
		if (!hWnd) return 1;
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);
		instance->pos.x = (float)point.x;
		instance->pos.y = (float)point.y;
		return 0;
	}
	/*�C���X�^���X�̃A�h���X���擾*/
	static std::shared_ptr<MS> &GetState()
	{
		return instance;
	}

	static void Create(const HWND aHwnd)
	{
		hWnd = aHwnd;
		instance = std::shared_ptr<MS>(new MS);
	}
	/*�}�E�X�J�[�\���̕\���̗L��*/
	static bool Visible(const bool bVisible)
	{
		while (ShowCursor(bVisible) != -1);
		return 0;
	}
	/*�������u��*/
	bool Down(const MouseButton but_)
	{
		const bool lcbNow = nowbut[but_] & (short)0x8000;
		const bool lcbPrev = prevbut[but_] & (short)0x8000;
		return (!lcbPrev && lcbNow);
	}
	/*�����Ă���*/
	bool On(const MouseButton but_)
	{
		const bool lcbNow = nowbut[but_] & (short)0x8000;
		const bool lcbPrev = prevbut[but_] & (short)0x8000;
		return (lcbPrev && lcbNow);
	}
	/*�������u��*/
	bool Up(const MouseButton but_)
	{
		const bool lcbNow = nowbut[but_] & (short)0x8000;
		const bool lcbPrev = prevbut[but_] & (short)0x8000;
		return (lcbPrev && !lcbNow);
	}
	/*�����Ă���*/
	bool Off(const MouseButton but_)
	{
		const bool lcbNow = nowbut[but_] & (short)0x8000;
		const bool lcbPrev = prevbut[but_] & (short)0x8000;
		return (!lcbPrev && !lcbNow);
	}
	/*�J�[�\���̈ʒu���擾*/
	const Point &GetPos()
	{
		return pos;
	}
	/*�J�[�\����X���W*/
	float GetPosX()
	{
		return pos.x;
	}
	/*�J�[�\����Y���W*/
	float GetPosY()
	{
		return pos.y;
	}
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
	Image()
		:hBmpDC(nullptr), hMaskBmpDC(nullptr),
		hBmp(nullptr), hMaskBmp(nullptr),
		oldBkColor(0),
		BmpInfo({})
	{

	}
	//�f�X�g���N�^
	~Image()
	{
		Release();
	}
	//BMP�t�@�C���ǂݍ��݃����o�֐�
	bool ImageCreate(const char * const bmpfilename_)
	{
		hBmp = (HBITMAP)LoadImage(NULL, bmpfilename_, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (!hBmp)
			return 1;
		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		hBmpDC = CreateCompatibleDC(NULL);
		if (!hBmpDC)
			return 1;

		SelectObject(hBmpDC, hBmp);

		oldBkColor = SetBkColor(hBmpDC, TRANSPARENT_COLOR);

		hMaskBmpDC = CreateCompatibleDC(NULL);
		if (!hMaskBmpDC)
			return 1;

		hMaskBmp = CreateBitmap(BmpInfo.bmWidth, BmpInfo.bmHeight, 1, 1, NULL);
		if (!hMaskBmp)
			return 1;

		SelectObject(hMaskBmpDC, hMaskBmp);

		BitBlt(hMaskBmpDC, 0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, hBmpDC, 0, 0, NOTSRCCOPY);//�F���]

		SetBkColor(hBmpDC, oldBkColor);
		return 0;
	}
	//�摜�̉��
	void Release()
	{
		if (hBmpDC)
		{
			DeleteDC(hBmpDC);
			hBmpDC = nullptr;
		}
		if (hMaskBmpDC)
		{
			DeleteDC(hMaskBmpDC);
			hMaskBmpDC = nullptr;
		}
		if (hBmp)
		{
			DeleteObject(hBmp);
			hBmp = nullptr;
		}
		if (hMaskBmp)
		{
			DeleteObject(hMaskBmp);
			hMaskBmp = nullptr;
		}
	}
	//�r�b�g�}�b�v���擾
	const BITMAP &GetBmpInfo() const
	{
		return BmpInfo;
	}
	//�r�b�g�}�b�v�Ɗ֘A�t�����Ă���f�o�C�X���擾
	const HDC GetImageHandle() const
	{
		return hBmpDC;
	}
	//�}�X�N�r�b�g�}�b�v�Ɗ֘A�t�����Ă���f�o�C�X���擾
	const HDC GetMaskHandle() const
	{
		return hMaskBmpDC;
	}
	//�}�X�N�r�b�g�}�b�v���擾
	const HBITMAP GetMaskBitMap() const
	{
		return hMaskBmp;
	}
};

inline bool LoadWavFile(const char * const ccpFileName, WAVEFORMATEX *lpwfe, WAVEHDR *lpwhdr)
{
	/*�t�@�C���I�[�v�����R�s�[*/
	HANDLE lhFileHandle = CreateFile
	(
		ccpFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	);
	if (lhFileHandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "�t�@�C�����J���܂���", ccpFileName, MB_OK);
		return 1;
	}
	DWORD dwFileSize = GetFileSize(lhFileHandle, NULL);
	BYTE *lpBuf = (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
	DWORD dwReadSize;
	ReadFile(lhFileHandle, lpBuf, dwFileSize, &dwReadSize, NULL);
	CloseHandle(lhFileHandle);

	BYTE *lpIt = lpBuf;
	/*�t�@�C���̍Ō�łȂ���*/
	auto NotEOF = [=]()->bool
	{
		return (DWORD(lpIt - lpBuf) < dwReadSize);
	};
	/*�G���[�I��*/
	auto Error = [=]()->bool
	{
		HeapFree(GetProcessHeap(), 0, lpBuf);
		MessageBox(nullptr, "wav�t�@�C���̓ǂݍ��݂Ɏ��s", ccpFileName, MB_OK);
		return 1;
	};
	/*�t�@�C���`�F�b�N*/
	const int check_wave = FourCharToInt("WAVE");
	while (NotEOF())
	{
		const int check = FourCharToInt(lpIt);
		if (check == check_wave) break;
		++lpIt;
	}
	/*������Ȃ�������*/
	if (!NotEOF())
	{
		/*�G���[*/
		return Error();
	}
	lpIt += sizeof(int);
	/*�t�H�[�}�b�g���R�s�[*/
	CopyMemory(lpwfe, lpBuf + 20, sizeof(PCMWAVEFORMAT));
	/*WAVE�`���`�F�b�N*/
	if (lpwfe->wFormatTag != WAVE_FORMAT_PCM)
	{
		/*�G���[*/
		return Error();
	}
	/*�|�C���^���I�t�Z�b�g*/
	lpIt = lpBuf + 20 + sizeof(PCMWAVEFORMAT);
	/*data�`�����Nfact�`�����N�̃`�F�b�N*/
	const int check_data = FourCharToInt("data");
	const int check_fact = FourCharToInt("fact");
	while (NotEOF())
	{
		const int check = FourCharToInt(lpIt);
		if (check == check_data || check == check_fact) break;
		++lpIt;
	}
	/*������Ȃ�������*/
	if (!NotEOF())
	{
		/*�G���[*/
		return Error();
	}
	/*�|�C���^���I�t�Z�b�g*/
	lpIt += sizeof(int);
	/*�o�b�t�@�̃T�C�Y*/
	DWORD dwSize = (DWORD)FourCharToInt(lpIt);
	/*�|�C���^���I�t�Z�b�g*/
	lpIt += sizeof(int);
	/*�V�����o�b�t�@���m��*/
	BYTE *lpWave = (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
	/*�g�`�f�[�^���R�s�[*/
	CopyMemory(lpWave, lpIt, dwSize);
	/*�Â��o�b�t�@���J��*/
	HeapFree(GetProcessHeap(), 0, lpBuf);
	/*WAVEHDR�\���̂̐ݒ�*/
	lpwhdr->lpData = (LPSTR)lpWave;
	lpwhdr->dwBufferLength = dwSize;
	lpwhdr->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	lpwhdr->dwLoops = 1;
	return 0;
}

inline void CloseWaveFile(HWAVEOUT hWaveOut, WAVEHDR *lpwhdr)
{
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, lpwhdr, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
	if (lpwhdr->lpData) {
		HeapFree(GetProcessHeap(), 0, lpwhdr->lpData);
		lpwhdr->lpData = nullptr;
	};
}

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
	static void LoopProc(WPARAM wParam, LPARAM lParam)
	{
		for (auto it = pwsTop; it; it = it->next)
		{
			if (it->hCallBackWnd)
			{
				if (it->bIsPlaying)
				{
					if (it->hWaveOut == (HWAVEOUT)wParam && &it->wHdr == (WAVEHDR *)lParam)
					{
						it->Play();
					}
				}
			}
		}
	}
	/*�R���X�g���N�^*/
	WSound()
		:
		wFormatEx({}),
		wHdr({}),
		hWaveOut(nullptr),
		hCallBackWnd(nullptr),
		next(nullptr),
		prev(nullptr),
		bIsPlaying(false)
	{
		if (pwsTop)
		{
			WSound *it = pwsTop;
			WSound *buf = pwsTop;
			while (it->next)
			{
				buf = it;
				it = it->next;
				if (it) it->prev = it;
			}
			it->next = this;
			return;
		}
		pwsTop = this;
	}
	/*�f�X�g���N�^*/
	~WSound()
	{
		CloseWaveFile(hWaveOut, &wHdr);

		if (prev) prev->next = next;
		if (next) next->prev = prev;
	}
	/*�R�[���o�b�N�E�B���h�E��ݒ�*/
	/*�E�B���h�E���������Ɏw��*/
	bool CallBack(const char * const ccpWinName)
	{
		return (hCallBackWnd = FindWindow(nullptr, ccpWinName)) == nullptr;
	}
	/*wav�t�@�C���ǂݍ���*/
	bool SoundCreate(const char * const ccpWaveFileName)
	{
		if (LoadWavFile(ccpWaveFileName, &wFormatEx, &wHdr)) return 1;
		if (hCallBackWnd)
		{
			waveOutOpen(&hWaveOut, WAVE_MAPPER, &wFormatEx, (DWORD)hCallBackWnd, 0, CALLBACK_WINDOW);
			return 0;
		}
		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wFormatEx, (DWORD)nullptr, 0, CALLBACK_NULL);
		return 0;
	}
	/*�T�E���h�̔j��*/
	void Release()
	{
		CloseWaveFile(hWaveOut, &wHdr);
	}
	/*���Đ�*/
	void Play()
	{
		waveOutReset(hWaveOut);
		waveOutPrepareHeader(hWaveOut, &wHdr, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &wHdr, sizeof(WAVEHDR));
	}
	/*���[�v�Đ�*/
	/*�K�؂�LoopProc���Ă΂�Ă���΃��[�v���@�\����*/
	void PlayL()
	{
		if (!bIsPlaying)
		{
			bIsPlaying = true;
			Play();
		}
	}
	/*�ꎞ��~*/
	void Pause()
	{
		waveOutPause(hWaveOut);
	}
	/*�ꎞ��~����*/
	void Restart()
	{
		waveOutRestart(hWaveOut);
	}
	/*��~*/
	void Stop()
	{
		bIsPlaying = false;
		waveOutReset(hWaveOut);
	}
};

class JoyPad
{
public:
	enum Stick
	{
		STK_LEFT,
		STK_RIGHT,
		STK_MAX,
	};
private:
	static std::vector<std::shared_ptr<JoyPad>> vpPadList;
	static constexpr float _diff = 2000.f;
	JOYINFOEX jInfoNow;
	JOYINFOEX jInfoPrev;
	Vector2 vStickAxis[Stick::STK_MAX];
	Vector2 vInitAxis[Stick::STK_MAX];
	bool bResult;
	JoyPad()
		: jInfoNow()
		, jInfoPrev()
		, vStickAxis()
		, vInitAxis()
		, bResult(false)
	{

	}
public:
	static const std::shared_ptr<JoyPad> &GetState(const unsigned int auiIdx)
	{
		return vpPadList.at(auiIdx);
	}
	static const bool Create(const unsigned int auiPadNum)
	{
		if (vpPadList.size()) vpPadList.clear();
		for (unsigned int ui = 0; ui < auiPadNum; ++ui)
		{
			vpPadList.emplace_back(new JoyPad);
			auto &spPad = vpPadList.at(ui);
			spPad->jInfoNow.dwSize = sizeof(JOYINFOEX);
			spPad->jInfoNow.dwFlags = JOY_RETURNALL;
			if (JOYERR_NOERROR == joyGetPosEx(ui, &spPad->jInfoNow))
			{
				spPad->vInitAxis[Stick::STK_LEFT] = Vector2((float)spPad->jInfoNow.dwXpos, (float)spPad->jInfoNow.dwYpos);
				spPad->vInitAxis[Stick::STK_RIGHT] = Vector2((float)spPad->jInfoNow.dwZpos, (float)spPad->jInfoNow.dwRpos);
				spPad->bResult = true;
			}
			else
			{
				spPad->bResult = false;
			}
			spPad->jInfoPrev = spPad->jInfoNow;
		}
		return 0;
	}
	static const bool GetStateAll()
	{
		unsigned int luiPadCount = 0;
		for (auto &spPad : vpPadList)
		{
			if (!spPad->bResult) continue;
			spPad->jInfoPrev = spPad->jInfoNow;
			if (JOYERR_NOERROR == joyGetPosEx(luiPadCount, &spPad->jInfoNow))
			{
				for (unsigned int ui = 0; ui < Stick::STK_MAX; ++ui)
				{
					const DWORD lcdwaAxisTable[2][2] =
					{
						{spPad->jInfoNow.dwXpos, spPad->jInfoNow.dwYpos},
						{spPad->jInfoNow.dwZpos, spPad->jInfoNow.dwRpos},
					};
					const float lcfAxisX = spPad->vInitAxis[ui].GetX();
					float lfAxisX = 0;
					if (lcdwaAxisTable[ui][0] < DWORD(lcfAxisX - _diff))
					{
						lfAxisX = lcdwaAxisTable[ui][0] - (lcfAxisX - _diff);
					}
					else if (lcdwaAxisTable[ui][0] > DWORD(lcfAxisX + _diff))
					{
						lfAxisX = lcdwaAxisTable[ui][0] - (lcfAxisX + _diff);
					}
					const float lcfAxisY = spPad->vInitAxis[ui].GetY();
					float lfAxisY = 0;
					if (lcdwaAxisTable[ui][1] < DWORD(lcfAxisY - _diff))
					{
						lfAxisY = lcdwaAxisTable[ui][1] - (lcfAxisY - _diff);
					}
					else if (lcdwaAxisTable[ui][1] > DWORD(lcfAxisY + _diff))
					{
						lfAxisY = lcdwaAxisTable[ui][1] - (lcfAxisY + _diff);
					}
					lfAxisX = ((int)lfAxisX / 3000) * 0.1f;
					lfAxisY = ((int)lfAxisY / 3000) * 0.1f;
					spPad->vStickAxis[ui] = Vector2(lfAxisX, lfAxisY);
				}
				spPad->bResult = true;
			}
			else
			{
				spPad->bResult = false;
			}
			++luiPadCount;
		}
		return 0;
	}
	const bool Down(const DWORD adwButton) const
	{
		const bool lcbPrev = jInfoPrev.dwButtons & adwButton;
		const bool lcbNow = jInfoNow.dwButtons & adwButton;
		return !lcbPrev && lcbNow;
	}
	const bool On(const DWORD adwButton) const
	{
		const bool lcbPrev = jInfoPrev.dwButtons & adwButton;
		const bool lcbNow = jInfoNow.dwButtons & adwButton;
		return lcbPrev && lcbNow;
	}
	const bool Up(const DWORD adwButton) const
	{
		const bool lcbPrev = jInfoPrev.dwButtons & adwButton;
		const bool lcbNow = jInfoNow.dwButtons & adwButton;
		return lcbPrev && !lcbNow;
	}
	const bool Off(const DWORD adwButton) const
	{
		const bool lcbPrev = jInfoPrev.dwButtons & adwButton;
		const bool lcbNow = jInfoNow.dwButtons & adwButton;
		return !lcbPrev && !lcbNow;
	}
	const Vector2 &Axis(const Stick asStick) const
	{
		return vStickAxis[asStick];
	}
	const float GetRad(const Stick asStick) const
	{
		const float lcfAxisX = vStickAxis[asStick].GetX(), lcfAxisY = vStickAxis[asStick].GetY();
		if (!lcfAxisX || !lcfAxisY)
		{
			return atan2(lcfAxisY, lcfAxisX);
		}
		return 0.f;
	}
	const float GetDeg(const Stick asStick) const
	{
		return RtoD(GetRad(asStick));
	}
};

//��`�N���X
class Rec
{
private:
	static std::mutex mutex;

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
	static bool Init(HWND hWnd_)
	{
		//if (off = hOff_) return 0;
		//return 1;
		RECT winrect;
		//
		GetClientRect(hWnd_, &winrect);

		Win.l = (float)winrect.left;
		Win.r = (float)winrect.right;
		Win.t = (float)winrect.top;
		Win.b = (float)winrect.bottom;

		frZoom.l = 0.f;
		frZoom.r = 1.f;
		frZoom.t = 0.f;
		frZoom.b = 1.f;

		Cam = Point(Win.r * 0.5f, Win.b * 0.5f);

		HDC hdc = GetDC(hWnd_);
		//
		off = CreateCompatibleDC(hdc);

		if (!off) return 1;

		hoffbmp = CreateCompatibleBitmap(hdc, int(Win.r), int(Win.b));
		//
		SelectObject(off, hoffbmp);

		hAlphaDc = CreateCompatibleDC(off);
		hAlphaBmp = CreateCompatibleBitmap(off, int(Win.r), int(Win.b));
		SelectObject(hAlphaDc, hAlphaBmp);

		bBlendFunc.BlendOp = AC_SRC_OVER;

		//SetStretchBltMode(off, HALFTONE);
		return 0;
	}
	//�I�t�X�N���[�������Z�b�g����֐�
	static void ResetOff(const DWORD rop_)
	{
		PatBlt(off, 0, 0, int(Win.r), int(Win.b), rop_);
	}
	//WM_PAINT���b�Z�[�W�������ŃI���X�N���[���ɕ`��
	static void DrawBackToFront(HDC hOn_)
	{
		/**/
		BitBlt(hOn_, 0, 0, int(Win.r), int(Win.b), off, 0, 0, SRCCOPY);
		/*/
		StretchBlt(hOn_, 0, 0, int(Win.r), int(Win.b), off, int(Win.l + frZoom.l), int(Win.t + frZoom.t), int(Win.r * frZoom.r), int(Win.b * frZoom.b), SRCCOPY);
		/**/
	}
	//�I�t�X�N���[���ƃr�b�g�}�b�v��j��
	static void Release()
	{
		if (hoffbmp) DeleteObject(hoffbmp);
		if (off) DeleteDC(off);

		if (hAlphaBmp) DeleteObject(hAlphaBmp);
		if (hAlphaDc) DeleteDC(hAlphaDc);
	}
	//�J�����̍��W�ɍ��킹�Ĉʒu�𒲐�����
	static const Point &AdjustCamPos(const Point * const pPos)
	{
		pAdjust.x = -(Cam.x - Win.r * 0.5f) + pPos->x;
		pAdjust.y = -(Cam.y - Win.b * 0.5f) + pPos->y;
		return pAdjust;
	}
	static const POINT AdjustCamPosToPOINT(const Point * const pPos)
	{
		auto lpTmp = AdjustCamPos(pPos);
		return { (long)lpTmp.x, (long)lpTmp.y };
	}
	//�J�����̍��W��ݒ�
	static void SetCameraPos(const Point * const pPos)
	{
		Cam = *pPos;
	}
	//�J�������ړ�
	static void MoveCamera(const Vector2 * const vMove)
	{
		Cam.x += vMove->GetX();
		Cam.y += vMove->GetY();
	}
	//�J�����̍��W���擾
	static const Point &GetCameraPos()
	{
		return Cam;
	}
	//�J������X���W���擾
	static const float GetCameraPosX()
	{
		return Cam.x;
	}
	//�J������Y���W���擾
	static const float GetCameraPosY()
	{
		return Cam.y;
	}
	//��ʂ�h��Ԃ�
	static void FullPaint(const COLORREF ccColor)
	{
		auto hBlush = CreateSolidBrush(ccColor);
		auto hOld = SelectObject(off, hBlush);
		Rectangle(off, 0, 0, (int)Win.r, (int)Win.b);
		SelectObject(off, hOld);
		DeleteObject(hBlush);
	}
	//�Y�[��
	static void Zoom(const float fMagni)
	{
		if (fMagni < 1.f) return;
		frZoom.r = 1.f / fMagni;
		frZoom.b = 1.f / fMagni;
		frZoom.l = (Win.r * (1.f - frZoom.r)) * 0.5f;
		frZoom.t = (Win.b * (1.f - frZoom.b)) * 0.5f;
	}
	//�I�t�X�N���[���̃n���h�����擾
	static HDC GetOffScreenHandle()
	{
		return off;
	}
	//�R���X�g���N�^
	Rec(const float cx_, const float cy_, const float w_, const float h_, float angleD_ = 0)
		:w(w_), h(h_), cColor(WHITE_COLOR)
	{
		p[CENTER].x = cx_;
		p[CENTER].y = cy_;

		//���_�Ŋg�k
		p[TOP_LEFT].x = -(w_ * 0.5f);
		p[TOP_LEFT].y = -(h_ * 0.5f);
		p[TOP_RIGHT].x = +(w_ * 0.5f);
		p[TOP_RIGHT].y = -(h_ * 0.5f);
		p[BOTTOM_LEFT].x = -(w_ * 0.5f);
		p[BOTTOM_LEFT].y = +(h_ * 0.5f);
		p[BOTTOM_RIGHT].x = +(w_ * 0.5f);
		p[BOTTOM_RIGHT].y = +(h_ * 0.5f);

		float bufx = p[TOP_LEFT].x - p[TOP_RIGHT].x;
		float bufy = p[TOP_LEFT].y - p[TOP_RIGHT].y;

		//dx = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
		dx = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

		bufx = p[TOP_LEFT].x - p[BOTTOM_LEFT].x;
		bufy = p[TOP_LEFT].y - p[BOTTOM_LEFT].y;

		//dy = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
		dy = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

		angle = angleD_;

		//���_�𒆐S�Ƃ����ʒu�Ɉړ�
		float  pp[4][2] =
		{
			{ -dx , -dy },
			{  dx , -dy },
			{ -dx ,  dy },
			{  dx ,  dy },
		};

		//���_�ɍ��킹�ĉ�]
		const double ang = (double)DtoR(ModAngle(angleD_));
		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			p[i].x = float(cos_fast(ang) * pp[i][0] - sin_fast(ang) * pp[i][1]);
			p[i].y = float(sin_fast(ang) * pp[i][0] + cos_fast(ang) * pp[i][1]);

			//p[i].x = cos(DtoR(angle)) * pp[i][0] - sin(DtoR(angle)) * pp[i][1];
			//p[i].y = sin(DtoR(angle)) * pp[i][0] + cos(DtoR(angle)) * pp[i][1];
		}

		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			//���_�ɍ��킹�Ă������̂Ō��ɖ߂�
			p[i].x += p[CENTER].x;
			p[i].y += p[CENTER].y;
		}
	}
	//�R���X�g���N�^
	Rec()
		:dx(0.f), dy(0.f), angle(0), w(0.f), h(0.f), cColor(WHITE_COLOR)
	{
		for (int i = 0; i < POINT_MAX; ++i)
			p[i] = { 0.,0. };
	}
	//�R�s�[�R���X�g���N�^
	Rec(const Rec & cpyrec_)
		:dx(cpyrec_.dx), dy(cpyrec_.dy), angle(cpyrec_.angle), w(cpyrec_.w), h(cpyrec_.h), cColor(cpyrec_.cColor)
	{
		for (int i = 0; i < POINT_MAX; ++i)
			p[i] = cpyrec_.p[i];
	}
	//�g���̐F�ݒ�
	const COLORREF SetColor(const COLORREF ccColor)
	{
		auto cOld = cColor;
		cColor = ccColor;
		return cOld;
	}
	//�F�ݒ�
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_)
	{
		auto cOld = cColor;
		cColor = RGB(r_, b_, b_);
		return cOld;
	}
	//��`���ړ�������
	void SetPos(const Point * const pos_)
	{
		//���_�𒆐S�Ƃ����ʒu�Ɉړ�
		float  pp[4][2] =
		{
			{ -dx , -dy },
			{ dx , -dy },
			{ -dx ,  dy },
			{ dx ,  dy },
		};

		p[CENTER].x = pos_->x;
		p[CENTER].y = pos_->y;

		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			p[i].x = p[CENTER].x + pp[i][0];
			p[i].y = p[CENTER].y + pp[i][1];
		}
	}
	//��`���g��k��������
	void Scaling(const float recw_, const float rech_)
	{
		w = recw_;
		h = rech_;
		//���_�Ŋg�k
		p[TOP_LEFT].x = -(recw_ * 0.5f);
		p[TOP_LEFT].y = -(rech_ * 0.5f);
		p[TOP_RIGHT].x = +(recw_ * 0.5f);
		p[TOP_RIGHT].y = -(rech_ * 0.5f);
		p[BOTTOM_LEFT].x = -(recw_ * 0.5f);
		p[BOTTOM_LEFT].y = +(rech_ * 0.5f);
		p[BOTTOM_RIGHT].x = +(recw_ * 0.5f);
		p[BOTTOM_RIGHT].y = +(rech_ * 0.5f);

		float bufx = p[TOP_LEFT].x - p[TOP_RIGHT].x;
		float bufy = p[TOP_LEFT].y - p[TOP_RIGHT].y;

		//dx = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
		dx = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

		bufx = p[TOP_LEFT].x - p[BOTTOM_LEFT].x;
		bufy = p[TOP_LEFT].y - p[BOTTOM_LEFT].y;

		//dy = (float)Sqrt((unsigned long)(bufx * bufx + bufy * bufy)) * 0.5f;
		dy = Sqrt(bufx * bufx + bufy * bufy) * 0.5f;

		double ang = (double)ModAngle(angle);
		if (ang < -1.f || ang > 1.f)
		{
			//���_�𒆐S�Ƃ����ʒu�Ɉړ�
			float  pp[4][2] =
			{
				{ -dx , -dy },
				{  dx , -dy },
				{ -dx ,  dy },
				{  dx ,  dy },
			};
			ang = (double)DtoR((float)ang);
			for (int i = 0; i < POINT_MAX - 1; ++i)
			{
				p[i].x = float(cos_fast(ang) * pp[i][0] - sin_fast(ang) * pp[i][1]);
				p[i].y = float(sin_fast(ang) * pp[i][0] + cos_fast(ang) * pp[i][1]);

				//p[i].x = cos(DtoR(angle)) * pp[i][0] - sin(DtoR(angle)) * pp[i][1];
				//p[i].y = sin(DtoR(angle)) * pp[i][0] + cos(DtoR(angle)) * pp[i][1];
			}
		}
		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			//���_�ɍ��킹�Ă������̂Ō��ɖ߂�
			p[i].x += p[CENTER].x;
			p[i].y += p[CENTER].y;
		}
	}
	//�����̊p�x�i�f�B�O���[�j��ݒ肷�郁���o�֐�
	void SetDeg(const float angleD_)
	{
		angle = ModAngle(angleD_);
		float  pp[4][2] =
		{
			{ -dx , -dy },
			{  dx , -dy },
			{ -dx ,  dy },
			{  dx ,  dy },
		};
		for (int i = 0; i < POINT_MAX - 1; ++i)
		{
			const double newrad = DtoR(angle);
			p[i].x = float(cos_fast(newrad) * pp[i][0] - sin_fast(newrad) * pp[i][1]);
			p[i].y = float(sin_fast(newrad) * pp[i][0] + cos_fast(newrad) * pp[i][1]);

			p[i].x += p[CENTER].x;
			p[i].y += p[CENTER].y;
		}
	}
	//�����̊p�x�i�f�B�O���[�j���擾���郁���o�֐�
	float GetDeg() const
	{
		return angle;
	}
	//�ǂݍ���ł������r�b�g�}�b�v��`��
	void Draw(Image * const mybitmap_)
	{
		auto lpTmp = AdjustCamPos(&p[CENTER]);
		if (lpTmp.x - w > Win.r) return;
		if (lpTmp.y - h > Win.b) return;
		if (lpTmp.x + w < Win.l) return;
		if (lpTmp.y + h < Win.t) return;

		//POINT dp[3] = {};
		for (int i = 0; i < 3; ++i)
		{
			pDrawPoint[i] = AdjustCamPosToPOINT(&p[i]);
			//pDrawPoint[i].x = (long)AdjustCamPos(&p[i]).x;
			//pDrawPoint[i].y = (long)AdjustCamPos(&p[i]).y;
		}

		const float ang = ModAngle(angle);
		if ((ang >= 90.f && ang <= 180.f) || (ang <= -90.f && ang >= -180.f))
		{
			Swap(pDrawPoint[TOP_LEFT], pDrawPoint[BOTTOM_RIGHT]);
			Swap(pDrawPoint[TOP_RIGHT], pDrawPoint[BOTTOM_LEFT]);
			PlgBlt(off, pDrawPoint, mybitmap_->GetImageHandle(), mybitmap_->GetBmpInfo().bmWidth / 2, 0, mybitmap_->GetBmpInfo().bmWidth / 2, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), mybitmap_->GetBmpInfo().bmWidth / 2, 0);
		}
		else PlgBlt(off, pDrawPoint, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth / 2, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);
	}
	//�ǂݍ���ł������r�b�g�}�b�v��`��
	void Draw(Image * const mybitmap_, const Frec * const frSrc)
	{
		auto lpTmp = AdjustCamPos(&p[CENTER]);
		if (lpTmp.x - w > Win.r) return;
		if (lpTmp.y - h > Win.b) return;
		if (lpTmp.x + w < Win.l) return;
		if (lpTmp.y + h < Win.t) return;

		//POINT dp[3];
		for (int i = 0; i < POINT_MAX; ++i)
		{
			pDrawPoint[i] = AdjustCamPosToPOINT(&p[i]);
			//pDrawPoint[i].x = (long)AdjustCamPos(&p[i]).x;
			//pDrawPoint[i].y = (long)AdjustCamPos(&p[i]).y;
		}

		const float ang = ModAngle(angle);
		if ((ang >= 90.f && ang <= 180.f) || (ang <= -90.f && ang >= -180.f))
		{
			Swap(pDrawPoint[TOP_LEFT], pDrawPoint[BOTTOM_RIGHT]);
			Swap(pDrawPoint[TOP_RIGHT], pDrawPoint[BOTTOM_LEFT]);
			PlgBlt(off, pDrawPoint, mybitmap_->GetImageHandle(), int(frSrc->l + frSrc->r), (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), int(frSrc->l + frSrc->r), (int)frSrc->t);
		}
		else PlgBlt(off, pDrawPoint, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);
	}
	//�s�������瓧���܂Œl���w�肵�ĕ`��
	void DrawAlpha(Image * const mybitmap_, byte alpha_ = 255)
	{
		//POINT dp;
		pDrawPoint[0] = AdjustCamPosToPOINT(&p[TOP_LEFT]);
		//pDrawPoint[0].x = (long)AdjustCamPos(&p[TOP_LEFT]).x;
		//pDrawPoint[0].y = (long)AdjustCamPos(&p[TOP_LEFT]).y;

		if (pDrawPoint[0].x - w > Win.r) return;
		if (pDrawPoint[0].y - h > Win.b) return;
		if (pDrawPoint[0].x + w < Win.l) return;
		if (pDrawPoint[0].y + h < Win.t) return;

		static POINT pBufArr[3] = {};
		pBufArr[0] = { 0, 0 };
		pBufArr[1] = { mybitmap_->GetBmpInfo().bmWidth, 0 };
		pBufArr[2] = { 0, mybitmap_->GetBmpInfo().bmHeight };

		if (alpha_ >= 255)
		{
			PlgBlt(off, pDrawPoint, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);
			return;
		}

		//BLENDFUNCTION bfu = {};
		//bfu.BlendOp = AC_SRC_OVER;
		//bfu.SourceConstantAlpha = alpha_;

		bBlendFunc.SourceConstantAlpha = alpha_;

		//auto hBufDc = CreateCompatibleDC(off);
		//auto hBufBmp = CreateCompatibleBitmap(off, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight);
		//SelectObject(hBufDc, hBufBmp);

		PlgBlt(hAlphaDc, pBufArr, off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, nullptr, 0, 0);

		PlgBlt(hAlphaDc, pBufArr, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);

		AlphaBlend(off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, hAlphaDc, 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, bBlendFunc);

		//auto threadFunc1 = [this, mybitmap_]()
		//{
		//	std::lock_guard<std::mutex> lock(mutex);
		//	PlgBlt(hAlphaDc, pBufArr, off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, nullptr, 0, 0);
		//};
		//auto threadFunc2 = [this, mybitmap_]()
		//{
		//	std::lock_guard<std::mutex> lock(mutex);
		//	PlgBlt(hAlphaDc, pBufArr, mybitmap_->GetImageHandle(), 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, mybitmap_->GetMaskBitMap(), 0, 0);
		//};
		//auto threadFunc3 = [this, mybitmap_]()
		//{
		//	std::lock_guard<std::mutex> lock(mutex);
		//	AlphaBlend(off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, hAlphaDc, 0, 0, mybitmap_->GetBmpInfo().bmWidth, mybitmap_->GetBmpInfo().bmHeight, bBlendFunc);
		//};

		//std::thread th1(threadFunc1);
		//std::thread th2(threadFunc2);
		//std::thread th3(threadFunc3);
		//th1.join();
		//th2.join();
		//th3.join();

		//DeleteObject(hBufBmp);
		//DeleteDC(hBufDc);
	}
	//�s�������瓧���܂Œl���w�肵�ĕ`��
	void DrawAlpha(Image * const mybitmap_, const Frec * const frSrc, byte alpha_ = 255)
	{
		//POINT dp;
		pDrawPoint[0] = AdjustCamPosToPOINT(&p[TOP_LEFT]);
		//pDrawPoint[0].x = (long)AdjustCamPos(&p[TOP_LEFT]).x;
		//pDrawPoint[0].y = (long)AdjustCamPos(&p[TOP_LEFT]).y;

		if (pDrawPoint[0].x - w > Win.r) return;
		if (pDrawPoint[0].y - h > Win.b) return;
		if (pDrawPoint[0].x + w < Win.l) return;
		if (pDrawPoint[0].y + h < Win.t) return;

		static POINT pBufArr[3] = {};
		pBufArr[0] = { 0, 0 };
		pBufArr[1] = { (int)w, 0 };
		pBufArr[2] = { 0, (int)h };

		if (alpha_ >= 255)
		{
			PlgBlt(off, pDrawPoint, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);
			return;
		}

		//BLENDFUNCTION bfu = {};
		//bfu.BlendOp = AC_SRC_OVER;
		//bfu.SourceConstantAlpha = alpha_;

		bBlendFunc.SourceConstantAlpha = alpha_;

		//auto hBufDc = CreateCompatibleDC(off);
		//auto hBufBmp = CreateCompatibleBitmap(off, (int)w, (int)h);
		//SelectObject(hBufDc, hBufBmp);

		PlgBlt(hAlphaDc, pBufArr, off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, nullptr, 0, 0);

		PlgBlt(hAlphaDc, pBufArr, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);

		AlphaBlend(off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, hAlphaDc, 0, 0, (int)w, (int)h, bBlendFunc);

		//auto threadFunc1 = [this, mybitmap_, frSrc]()
		//{
		//	std::lock_guard<std::mutex> lock(mutex);
		//	PlgBlt(hAlphaDc, pBufArr, off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, nullptr, 0, 0);
		//};
		//auto threadFunc2 = [this, mybitmap_, frSrc]()
		//{
		//	std::lock_guard<std::mutex> lock(mutex);
		//	PlgBlt(hAlphaDc, pBufArr, mybitmap_->GetImageHandle(), (int)frSrc->l, (int)frSrc->t, (int)frSrc->r, (int)frSrc->b, mybitmap_->GetMaskBitMap(), (int)frSrc->l, (int)frSrc->t);
		//};
		//auto threadFunc3 = [this, mybitmap_]()
		//{
		//	std::lock_guard<std::mutex> lock(mutex);
		//	AlphaBlend(off, pDrawPoint[0].x, pDrawPoint[0].y, (int)w, (int)h, hAlphaDc, 0, 0, (int)w, (int)h, bBlendFunc);
		//};

		//std::thread th1(threadFunc1);
		//std::thread th2(threadFunc2);
		//std::thread th3(threadFunc3);
		//th1.join();
		//th2.join();
		//th3.join();

		//DeleteObject(hBufBmp);
		//DeleteDC(hBufDc);
	}
	//��`�̊O�g��`�悷�郁���o�֐�
	void Draw()
	{
		auto lpTmp = AdjustCamPos(&p[CENTER]);
		if (lpTmp.x - w > Win.r) return;
		if (lpTmp.y - h > Win.b) return;
		if (lpTmp.x + w < Win.l) return;
		if (lpTmp.y + h < Win.t) return;

		//POINT dp[5];
		for (int i = 0; i < 4; ++i)
		{
			pDrawPoint[i] = AdjustCamPosToPOINT(&p[i]);
			//pDrawPoint[i].x = (long)AdjustCamPos(&p[i]).x;
			//pDrawPoint[i].y = (long)AdjustCamPos(&p[i]).y;
		}

		Swap(pDrawPoint[BOTTOM_LEFT], pDrawPoint[BOTTOM_RIGHT]);

		pDrawPoint[4] = pDrawPoint[TOP_LEFT];

		HPEN hPen = CreatePen(PS_SOLID, 0, cColor);
		HGDIOBJ old = SelectObject(off, hPen);

		Polyline(off, pDrawPoint, sizeof(pDrawPoint) / sizeof(pDrawPoint[0]));

		SelectObject(off, old);
		DeleteObject(hPen);
	}
	//��`���m�̐�����������p�����o�֐�
	bool CheckHit(const Rec * const rec_)
	{
		const float ang = ModAngle(angle);
		if ((ang >= -1 && ang <= 1) || (ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
		{
			return (p[TOP_LEFT].x < rec_->p[TOP_RIGHT].x && p[TOP_RIGHT].x > rec_->p[TOP_LEFT].x &&
				p[TOP_LEFT].y < rec_->p[BOTTOM_LEFT].y && p[BOTTOM_LEFT].y > rec_->p[TOP_LEFT].y);
		}

		if (
			CheckHit(rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||
			CheckHit(rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
			CheckHit(rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
			CheckHit(rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y)
			)
		{
			return 1;
		}

		if (
			LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
			LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
			LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
			LineCheckCross(p[TOP_LEFT].x, p[TOP_LEFT].y, p[TOP_RIGHT].x, p[TOP_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||

			LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
			LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
			LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
			LineCheckCross(p[TOP_RIGHT].x, p[TOP_RIGHT].y, p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||

			LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
			LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
			LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
			LineCheckCross(p[BOTTOM_RIGHT].x, p[BOTTOM_RIGHT].y, p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y) ||

			LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y) ||
			LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[TOP_RIGHT].x, rec_->p[TOP_RIGHT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y) ||
			LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[BOTTOM_RIGHT].x, rec_->p[BOTTOM_RIGHT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y) ||
			LineCheckCross(p[BOTTOM_LEFT].x, p[BOTTOM_LEFT].y, p[TOP_LEFT].x, p[TOP_LEFT].y, rec_->p[BOTTOM_LEFT].x, rec_->p[BOTTOM_LEFT].y, rec_->p[TOP_LEFT].x, rec_->p[TOP_LEFT].y)
			)
		{
			return 1;
		}
		return 0;
	}
	//��`�Ɠ_�̐ڐG����p�����o�֐�
	bool CheckHit(const Point * const pos_)
	{
		double ang = (double)ModAngle(angle);
		if ((ang >= -1 && ang <= 1) || (ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
		{
			return (pos_->x > p[TOP_LEFT].x && pos_->x < p[TOP_RIGHT].x &&
				pos_->y > p[TOP_LEFT].y && pos_->y < p[BOTTOM_LEFT].y);
		}
		ang = (double)DtoR((float)ang);
		float dist = GetDist(pos_->x, pos_->y);
		Point pp = { pos_->x - p[CENTER].x,pos_->y - p[CENTER].y };
		double r1 = 0., r2 = 0.;
		if (pp.x != 0.f)
		{
			r1 = (double)atan(pp.y / pp.x);
		}
		else r1 = (double)DtoR(ModAngle(360.f));
		r2 = r1 - ang;

		pp = { dist * (float)cos_fast(r2),dist * (float)sin_fast(r2) };
		//pp = { dist * cos(r2),dist * sin(r2) };

		pp.x += p[CENTER].x;
		pp.y += p[CENTER].y;

		return(
			p[CENTER].x - dx <= pp.x && pp.x <= p[CENTER].x + dx &&
			p[CENTER].y - dy <= pp.y && pp.y <= p[CENTER].y + dy
			);
	}
	//��`�Ɠ_�̐ڐG����p�����o�֐�
	bool CheckHit(const float x_, const float y_)
	{
		double ang = (double)ModAngle(angle);
		if ((ang >= -1 && ang <= 1) || (ang >= 179.f && ang <= 181.f) || (ang <= -179.f && ang >= -181.f))
		{
			return (x_ > p[TOP_LEFT].x && x_ < p[TOP_RIGHT].x &&
				y_ > p[TOP_LEFT].y && y_ < p[BOTTOM_LEFT].y);
		}
		ang = (double)DtoR((float)ang);
		float dist = GetDist(x_, y_);
		Point pp = { x_ - p[CENTER].x,y_ - p[CENTER].y };
		double r1 = 0., r2 = 0.;
		if (pp.x != 0.f)
		{
			r1 = (double)atan(pp.y / pp.x);
		}
		else r1 = (double)DtoR(ModAngle(360.f));

		r2 = r1 - ang;

		pp = { dist * (float)cos_fast(r2),dist * (float)sin_fast(r2) };
		//pp = { dist * cos(r2),dist * sin(r2) };

		pp.x += p[CENTER].x;
		pp.y += p[CENTER].y;

		return(
			p[CENTER].x - dx <= pp.x && pp.x <= p[CENTER].x + dx &&
			p[CENTER].y - dy <= pp.y && pp.y <= p[CENTER].y + dy
			);
	}
	//��`�̕�
	float GetW() const
	{
		return w;
	}
	//��`�̍���
	float GetH() const
	{
		return h;
	}
	//�w����W�Ƃ̊p�x(���W�A��)���擾���郁���o�֐�
	float GetRad(const float x_, const float y_) const
	{
		return atan2(y_ - p[CENTER].y, x_ - p[CENTER].x);
	}
	//�ʂ̋�`�Ƃ̊p�x(���W�A��)���擾���郁���o�֐�
	float GetRad(const Rec * const rec_) const
	{
		return atan2(rec_->p[CENTER].y - p[CENTER].y, rec_->p[CENTER].x - p[CENTER].x);
	}
	//�w����W�Ƃ̊p�x(�f�B�O���[)���擾���郁���o�֐�
	float GetDeg(const float x_, const float y_) const
	{
		return RtoD(atan2(y_ - p[CENTER].y, x_ - p[CENTER].x));
	}
	//�w����W�Ƃ̊p�x(�f�B�O���[)���擾���郁���o�֐�
	float GetDeg(const Point * const pos_) const
	{
		return RtoD(atan2(pos_->y - p[CENTER].y, pos_->x - p[CENTER].x));
	}
	//�ʂ̋�`�Ƃ̊p�x(�f�B�O���[)���擾���郁���o�֐�
	float GetDeg(const Rec * const rec_) const
	{
		return RtoD(atan2(rec_->p[CENTER].y - p[CENTER].y, rec_->p[CENTER].x - p[CENTER].x));
	}
	//��`���ړ�������
	void Move(const Vector2 * const vec2_)
	{
		for (int i = 0; i < POINT_MAX; ++i)
		{
			p[i].x += vec2_->GetX();
			p[i].y += vec2_->GetY();
		}
	}
	//�_�Ƃ̋������擾���郁���o�֐�
	float GetDist(const float x_, const float y_) const
	{
		float dx = p[CENTER].x - x_;
		float dy = p[CENTER].y - y_;
		//return (float)Sqrt((unsigned long)(dx * dx + dy * dy));
		return Sqrt(dx * dx + dy * dy);
	}
	//�_�Ƃ̋������擾���郁���o�֐�
	float GetDist(const Point * const pos_) const
	{
		float dx = p[CENTER].x - pos_->x;
		float dy = p[CENTER].y - pos_->y;
		//return (float)Sqrt((unsigned long)(dx * dx + dy * dy));
		return Sqrt(dx * dx + dy * dy);
	}
	//�ʂ̋�`�Ƃ̋������擾���郁���o�֐�
	float GetDist(const Rec * const rec_) const
	{
		float dx = p[CENTER].x - rec_->p[CENTER].x;
		float dy = p[CENTER].y - rec_->p[CENTER].y;
		//return (float)Sqrt((unsigned long)(dx * dx + dy * dy));
		return Sqrt(dx * dx + dy * dy);
	}
	//��`�̒��S�_��Ԃ������o�֐�
	const Point &GetPos() const
	{
		return p[CENTER];
	}
	//��`�̒��S�_��X���W
	float GetPosX() const
	{
		return p[CENTER].x;
	}
	//��`�̒��S�_��Y���W
	float GetPosY() const
	{
		return p[CENTER].y;
	}
	//��`�̍���̍��W���擾
	const Point &GetTL() const
	{
		return p[TOP_LEFT];
	}
	//��`�̉E��̍��W���擾
	const Point &GetTR() const
	{
		return p[TOP_RIGHT];
	}
	//��`�̍����̍��W���擾
	const Point &GetBL() const
	{
		return p[BOTTOM_LEFT];
	}
	//��`�̉E���̍��W���擾
	const Point &GetBR() const
	{
		return p[BOTTOM_RIGHT];
	}
	//���݂̃T�C�Y���i0, 0�j���ǂ���
	const bool SizeZero() const
	{
		return (!w && !h);
	}
};

struct FontOP
{
	int Weight;          // ���� 
	DWORD Italic;        // �C�^���b�N 
	DWORD Underline;     // ���� 
	DWORD StrikeOut;     // ������ 
	DWORD CharSet;       // ���̐ݒ� 
	DWORD PitchAndFamily;// �����̊Ԋu

	FontOP()
		:
		Weight(FW_REGULAR),
		Italic(FALSE),
		Underline(FALSE),
		StrikeOut(FALSE),
		CharSet(SHIFTJIS_CHARSET),
		PitchAndFamily(FIXED_PITCH | FF_MODERN)
	{

	}
	FontOP(const int Weight_, const DWORD Italic_, const DWORD Underline_, const DWORD StrikeOut_, const DWORD CharSet_, const DWORD PitchAndFamily_)
		:
		Weight(Weight_),
		Italic(Italic_),
		Underline(Underline_),
		StrikeOut(StrikeOut_),
		CharSet(CharSet_),
		PitchAndFamily(PitchAndFamily_)
	{

	}
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
	Font()
		:
		hf(nullptr),
		hOff(Rec::GetOffScreenHandle()),
		col(WHITE_COLOR)
	{

	}
	//�f�X�g���N�^
	~Font()
	{
		Release();
	}
	//�t�H���g�쐬
	bool FontCreate(const char *fontname_, int h_ = 0, float angleD_ = 0, const FontOP *fontoption_ = &FOP_DEFAULT)
	{
		hf = CreateFont
		(
			h_,
			0,
			(int)angleD_,
			0,
			fontoption_->Weight,
			fontoption_->Italic,
			fontoption_->Underline,
			fontoption_->StrikeOut,
			fontoption_->CharSet,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,
			fontoption_->PitchAndFamily,
			fontname_
		);
		return 0;
	}
	//�t�H���g�̏���
	void Release()
	{
		if (hf) DeleteObject(hf);
	}
	//�F�ݒ�
	const COLORREF SetColor(const COLORREF col_)
	{
		auto cOld = col_;
		col = col_;
		return cOld;
	}
	//�F�ݒ�
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_)
	{
		auto cOld = col;
		col = RGB(r_, g_, b_);
		return cOld;
	}
	//�`��
	void Draw(const Point * const pos_, const char * const text_)
	{
		const POINT dp = { (long)Rec::AdjustCamPos(pos_).x, (long)Rec::AdjustCamPos(pos_).y };

		HGDIOBJ old = nullptr;
		if (hf) old = SelectObject(hOff, hf);
		//�����F����������w��
		SetTextColor(hOff, col);
		//�w�i�F�𓧉߂Ɏw��
		const int ioldMode = SetBkMode(hOff, TRANSPARENT);
		TextOut(hOff, dp.x, dp.y, text_, lstrlen(text_) + 1);
		SetBkMode(hOff, ioldMode);
		if (old) SelectObject(hOff, old);
	}
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
	Circle()
		: hPen(nullptr), hOff(Rec::GetOffScreenHandle()), color(WHITE_COLOR), center({ 0.f,0.f }), radius(1.f)
	{

	}
	/*�R���X�g���N�^*/
	Circle(const Point * const position_, const float radius_)
		: hPen(nullptr), hOff(Rec::GetOffScreenHandle()), color(WHITE_COLOR), center(*position_), radius(radius_)
	{

	}
	/*���S���W�ݒ�*/
	void SetPos(const Point * const pos_)
	{
		center = *pos_;
	}
	/*���a�ݒ�*/
	void SetRadius(const float radius_)
	{
		radius = radius_;
	}
	/*�F�ݒ�*/
	const COLORREF SetColor(const COLORREF color_)
	{
		auto cOld = color;
		color = color_;
		return cOld;
	}
	/*�F�ݒ�*/
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_)
	{
		auto cOld = color;
		//color = r_ | (unsigned short)g_ << 8 | (unsigned long)b_ << 16;
		color = RGB(r_, g_, b_);
		return cOld;
	}
	/*���W�擾*/
	const Point &GetPos() const
	{
		return center;
	}
	/*X���W�擾*/
	const float GetPosX() const
	{
		return center.x;
	}
	/*Y���W�擾*/
	const float GetPosY() const
	{
		return center.y;
	}
	/*���a�擾*/
	const float GetRadius() const
	{
		return radius;
	}
	/*�`��*/
	void Draw()
	{
		Point dp = Rec::AdjustCamPos(&center);
		if (dp.x - radius > Rec::Win.r) return;
		if (dp.y - radius > Rec::Win.b) return;
		if (dp.x + radius < Rec::Win.l) return;
		if (dp.x + radius < Rec::Win.t) return;

		/*�`��p�y�����쐬*/
		hPen = CreatePen(PS_INSIDEFRAME, 1, color);
		/*off���y�����g���悤�ɂ���*/
		HGDIOBJ hOldPen = SelectObject(hOff, hPen);
		HGDIOBJ hOldBlush = SelectObject(hOff, GetStockObject(NULL_BRUSH));

		/*�~�̕`��J�n*/
		Ellipse(hOff, int(dp.x - radius), int(dp.y - radius), int(dp.x + radius), int(dp.y + radius));

		/*off���g���`��I�u�W�F�N�g�����ɖ߂�*/
		SelectObject(hOff, hOldPen);
		SelectObject(hOff, hOldBlush);
		/*�y����j��*/
		DeleteObject(hPen);
		hPen = nullptr;
	}
	/*�����蔻��*/
	const bool CheckHit(const Circle * const circle_) const
	{
		/*���a�̍��v*/
		float dist = this->radius + circle_->radius;
		/*���S���m��X����̋���*/
		float distx = this->center.x - circle_->center.x;
		/*���S���m��Y����̋���*/
		float disty = this->center.y - circle_->center.y;
		/*���a�������S�_���m�̋������Z��������@true�@*/
		return ((dist * dist) > (distx * distx + disty * disty));
	}
	/*�����蔻��*/
	const bool CheckHit(const Point * const point_) const
	{
		/*���S����_�܂ł�X����̋���*/
		float distx = center.x - point_->x;
		/*���S����_�܂ł�Y����̋���*/
		float disty = center.y - point_->y;
		/*���a�����_�܂ł̋������Z��������@true�@*/
		return ((radius * radius) > (distx * distx + disty * disty));
	}
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
	Line()
		:
		hPen(nullptr),
		hOff(Rec::GetOffScreenHandle()),
		color(WHITE_COLOR),
		spos({ 0.f, 0.f }),
		epos({ 1.f, 0.f }),
		width(1)
	{
		const float dx = epos.x - spos.x;
		const float dy = epos.y - epos.y;

		angle = RtoD(atan2(dy, dx));

		len = Sqrt(dx * dx + dy * dy);

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�R���X�g���N�^*/
	Line(const Point * const spos_, const Point * const epos_)
		:
		hPen(nullptr),
		hOff(Rec::GetOffScreenHandle()),
		color(WHITE_COLOR),
		spos(*spos_),
		epos(*epos_),
		width(1)
	{
		const float dx = epos.x - spos.x;
		const float dy = epos.y - epos.y;

		angle = RtoD((float)atan2(dx, dy)) - 90;

		len = Sqrt(dx * dx + dy * dy);

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�n�_�ݒ�*/
	void SetPos(const Point * const spos_)
	{
		epos = Point(epos.x - spos.x, epos.y - spos.y);
		spos = *spos_;

		epos.x += spos_->x;
		epos.y += spos_->y;
	}
	/*�n�_�ƏI�_�ݒ�*/
	void SetPos(const Point * const spos_, const Point * const epos_)
	{
		spos = *spos_;
		epos = *epos_;

		const float dx = epos.x - spos.x;
		const float dy = epos.y - epos.y;

		angle = RtoD(atan2(dy, dx));

		len = Sqrt(dx * dx + dy * dy);

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�n�_�ƏI�_�ݒ�*/
	void SetPos(const Point * const spos_, const float angleD_, const float len_)
	{
		spos = *spos_;

		angle = angleD_;

		len = len_;

		const float ang = DtoR(ModAngle(angle));
		epos = Point((float)cos_fast(ang) * len, (float)sin_fast(ang) * len);

		//epos = Point(cos(DtoR(angle)) * len, sin(DtoR(angle)) * len);

		epos.x += spos.x;
		epos.y += spos.y;

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�n�_�ݒ�*/
	void SetSPos(const Point * const spos_)
	{
		spos = *spos_;

		const float dx = epos.x - spos.x;
		const float dy = epos.y - epos.y;

		angle = RtoD(atan2(dy, dx));

		len = Sqrt(dx * dx + dy * dy);

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�I�_�ݒ�*/
	void SetEPos(const Point * const epos_)
	{
		epos = *epos_;

		const float dx = epos.x - spos.x;
		const float dy = epos.y - epos.y;

		angle = RtoD(atan2(dy, dx));

		len = Sqrt(dx * dx + dy * dy);

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�F�ݒ�*/
	const COLORREF SetColor(const COLORREF color_)
	{
		auto cOld = color;
		color = color_;
		return cOld;
	}
	/*�F�ݒ�*/
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_)
	{
		auto cOld = color;
		color = RGB(r_, g_, b_);
		return cOld;
	}
	/*���ݒ�*/
	void SetWidth(const int width_)
	{
		width = width_;
	}
	/*�p�x�ݒ�*/
	void SetDeg(const float angleD_)
	{
		angle = angleD_;

		const float ang = DtoR(ModAngle(angle));
		epos = Point((float)cos_fast(ang) * len, (float)sin_fast(ang) * len);

		//epos = Point(cos(DtoR(angle)) * len, sin(DtoR(angle)) * len);

		epos.x += spos.x;
		epos.y += spos.y;

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�����ݒ�*/
	void SetLen(const float len_)
	{
		len = len_;
		if (len_)
		{
			const float ang = DtoR(ModAngle(angle));
			epos = Point((float)cos_fast(ang) * len_, (float)sin_fast(ang) * len_);

			//epos = Point(cos(DtoR(angle)) * len_, sin(DtoR(angle)) * len_);

			epos.x += spos.x;
			epos.y += spos.y;
		}
		else
		{
			epos = spos;
		}

		vec2 = Vector2(epos.x - spos.x, epos.y - spos.y);
	}
	/*�n�_�擾*/
	const Point &GetSPos() const
	{
		return spos;
	}
	/*�I�_�擾*/
	const Point &GetEPos() const
	{
		return epos;
	}
	/*�p�x�擾*/
	float GetDeg() const
	{
		return angle;
	}
	/*�p�x�擾*/
	float GetDeg(const Line * const line_) const
	{
		return RtoD(atan2(line_->spos.y - spos.y, line_->spos.x - spos.x));
	}
	/*�p�x�擾*/
	float GetDeg(const Rec * const rec_) const
	{
		return RtoD(atan2(rec_->GetPosY() - spos.y, rec_->GetPosX() - spos.x));
	}
	/*�p�x�擾*/
	float GetDeg(const Point * const pos_) const
	{
		return RtoD(atan2(pos_->y - spos.y, pos_->x - spos.x));
	}
	/*�����擾*/
	float GetLen() const
	{
		return len;
	}
	/*�����擾*/
	float GetDist(const Circle * const circle_) const
	{
		const float dx = spos.x - circle_->GetPos().x;
		const float dy = spos.y - circle_->GetPos().y;

		return Sqrt(dx * dx + dy * dy);
	}
	/*�����擾*/
	float GetDist(const Point * const pos_) const
	{
		const float dx = spos.x - pos_->x;
		const float dy = spos.y - pos_->y;

		return Sqrt(dx * dx + dy * dy);
	}
	/*�x�N�g���擾*/
	const Vector2 &GetVec() const
	{
		return vec2;
	}
	/*���Ɖ~�̌�_���擾*/
	const Point &GetPOI(const Circle * const circle_)
	{
		double xyr[3] = { circle_->GetPos().x, circle_->GetPos().y, circle_->GetRadius() };
		double pt1[2] = { spos.x, spos.y };
		double pt2[2] = { epos.x, epos.y };
		double xy[2] = {};
		if (lncl(pt1, pt2, xyr, pt1, xy) < 0)
		{
			inter = Point();
			return inter;
		}
		inter = Point((float)*(xy + 0), (float)*(xy + 1));
		return inter;
	}
	/*���Ɛ��̌�_���擾*/
	const Point &GetPOI(const Line * const line_)
	{
		double line1[2][2] =
		{
			{ spos.x, spos.y },
			{ epos.x, epos.y }
		};
		double line2[2][2] =
		{
			{ line_->spos.x, line_->spos.y },
			{ line_->epos.x, line_->epos.y }
		};
		double xy[2] = {};
		if (lnln(line1, line2, xy))
		{
			inter = Point();
			return inter;
		}
		inter = Point((float)*(xy + 0), (float)*(xy + 1));
		return inter;
	}
	/*�ړ�*/
	void Move(const float movespd_)
	{
		const double ang = (double)DtoR(ModAngle(angle));
		spos.x += (float)cos_fast(ang) * movespd_;
		spos.y += (float)sin_fast(ang) * movespd_;

		epos.x += (float)cos_fast(ang) * movespd_;
		epos.y += (float)sin_fast(ang) * movespd_;

		//spos.x += cos(DtoR(angle)) * movespd_;
		//spos.y += sin(DtoR(angle)) * movespd_;

		//epos.x += cos(DtoR(angle)) * movespd_;
		//epos.y += sin(DtoR(angle)) * movespd_;
	}
	/*�`��*/
	void Draw(const u_int penstyle_ = PS_SOLID)
	{
		const Point pS = Rec::AdjustCamPos(&spos);
		const Point pE = Rec::AdjustCamPos(&epos);
		if (pS.x > Rec::Win.r && pE.x > Rec::Win.r) return;
		if (pS.y > Rec::Win.b && pE.y > Rec::Win.b) return;
		if (pS.x < Rec::Win.l && pE.x < Rec::Win.l) return;
		if (pS.y < Rec::Win.t && pE.y < Rec::Win.t) return;

		hPen = CreatePen(penstyle_, width, color);
		HGDIOBJ old = SelectObject(hOff, hPen);

		const int ioldMode = SetBkMode(hOff, TRANSPARENT);
		MoveToEx(hOff, (int)pS.x, (int)pS.y, nullptr);
		LineTo(hOff, (int)pE.x, (int)pE.y);
		SetBkMode(hOff, ioldMode);

		//POINT dP[2] =
		//{
		//	{(LONG)pS.x, (LONG)pS.y},
		//	{(LONG)pE.x, (LONG)pE.y},
		//};
		//BYTE bT[2] =
		//{
		//	PT_MOVETO,
		//	PT_LINETO
		//};
		//Polyline(hOff, dP, 2);
		//PolyDraw(hOff, dP, bT, 2);

		SelectObject(hOff, old);
		DeleteObject(hPen);
	}
	/*�����蔻��*/
	bool CheckHit(const Line * const line_)
	{
		return LineCheckCross(spos.x, spos.y, epos.x, epos.y, line_->spos.x, line_->spos.y, line_->epos.x, line_->epos.y);
	}
	/*�����蔻��*/
	bool CheckHit(const Rec * const rec_)
	{
		return
			(
				LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetTL().x, rec_->GetTL().y, rec_->GetTR().x, rec_->GetTR().y) ||
				LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetTR().x, rec_->GetTR().y, rec_->GetBR().x, rec_->GetBR().y) ||
				LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetBR().x, rec_->GetBR().y, rec_->GetBL().x, rec_->GetBL().y) ||
				LineCheckCross(spos.x, spos.y, epos.x, epos.y, rec_->GetBL().x, rec_->GetBL().y, rec_->GetTL().x, rec_->GetTL().y)
				);
	}
	/*�����蔻��*/
	bool CheckHit(const Circle * const circle_)
	{
		Vector2 vecA(circle_->GetPos().x - spos.x, circle_->GetPos().y - spos.y);
		Vector2 vecB(circle_->GetPos().x - epos.x, circle_->GetPos().y - epos.y);
		const float d = abs(vec2.Cross(&vecA) / vec2.GetLen());
		if (d > circle_->GetRadius()) return 0;
		if ((vecA.Dot(&vec2) * vecB.Dot(&vec2)) <= 0.f)
		{
			return 1;
		}
		else if (circle_->GetRadius() > vecA.GetLen() || circle_->GetRadius() > vecB.GetLen())
		{
			return 1;
		}
		return 0;
	}
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
	Pixel()
		:
		pPos({}),
		cColor(0),
		hOff(Rec::GetOffScreenHandle()),
		bSize(3)
	{
	}
	~Pixel()
	{
		if (hPen) DeleteObject(hPen);
		if (hBrush) DeleteObject(hBrush);
	}
	Pixel(const Point &crefpPos, const COLORREF ccColor, const byte cbSize)
		:
		pPos(crefpPos),
		cColor(ccColor),
		hOff(Rec::GetOffScreenHandle()),
		bSize(cbSize)
	{
	}
	Pixel(const Pixel &crefPixel)
		:
		pPos(crefPixel.pPos),
		cColor(crefPixel.cColor),
		hOff(Rec::GetOffScreenHandle()),
		hPen(CreatePen(PS_SOLID, 1, cColor)),
		hBrush(CreateSolidBrush(cColor)),
		bSize(crefPixel.bSize)
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
		if (hPen) DeleteObject(hPen);
		if (hBrush) DeleteObject(hBrush);
		hPen = CreatePen(PS_SOLID, 1, cColor);
		hBrush = CreateSolidBrush(cColor);
		return ccOld;
	}
	const COLORREF SetColor(const byte r_, const byte g_, const byte b_)
	{
		const COLORREF ccOld = cColor;
		cColor = RGB(r_, g_, b_);
		if (hPen) DeleteObject(hPen);
		if (hBrush) DeleteObject(hBrush);
		hPen = CreatePen(PS_SOLID, 1, cColor);
		hBrush = CreateSolidBrush(cColor);
		return ccOld;
	}
	const byte SetSize(const byte cbSize)
	{
		const byte cbOld = bSize;
		bSize = cbSize;
		return cbOld;
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
		Point pDp = Rec::AdjustCamPos(&pPos);
		if (pDp.x < Rec::Win.l) return;
		if (pDp.x > Rec::Win.r) return;
		if (pDp.y < Rec::Win.t) return;
		if (pDp.y > Rec::Win.b) return;

		/**
		SetPixel(hOff, (int)pDp.x, (int)pDp.y, cColor);
		/*/
		auto hOldPen = SelectObject(hOff, hPen);
		auto hOldBrush = SelectObject(hOff, hBrush);
		Rectangle(hOff, int(pDp.x - ((bSize - 1) * 0.5f)), int(pDp.y - ((bSize - 1) * 0.5f)), int(pDp.x + ((bSize - 1) * 0.5f)), int(pDp.y + ((bSize - 1) * 0.5f)));
		SelectObject(hOff, hOldPen);
		SelectObject(hOff, hOldBrush);
		/**/
	}
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
	Rep()
		:
		dData(0.0),
		rpNext(nullptr),
		rpPrev(nullptr)
	{

	}
	Rep(const Rep &);
	Rep(const Rep &&);
	Rep &operator = (const Rep &) = default;
public:
	/*�I�[�ɗv�f��ǉ�*/
	static bool Push(const double dData)
	{
		Rep rTmp;
		rTmp.dData = (dData == DBL_MAX) ? dData - 1.0 : dData;
		if (rpTop)
		{
			auto rpIt = rpTop;
			while (rpIt->rpNext) rpIt = rpIt->rpNext;
			rpIt->rpNext = (Rep *)malloc(sizeof(Rep) * 1);
			if (!rpIt->rpNext) return 1;
			rTmp.rpPrev = rpIt;
			*rpIt->rpNext = rTmp;
			++sDataSize;
			return 0;
		}
		rpTop = (Rep *)malloc(sizeof(Rep) * 1);
		if (!rpTop) return 1;
		*rpTop = rTmp;
		sDataSize = 1;
		return 0;
	}
	/*�ǂݍ��݃f�[�^������擾*/
	static const double Read()
	{
		if (!rpOut) return DBL_MAX;
		const double dRet = rpOut->dData;
		rpOut = rpOut->rpNext;
		return dRet;
	}
	/*�f�[�^�̓ǂݍ��ݒn�_��ݒ�*/
	static bool SetPosition(const u_int uiIdx)
	{
		if (uiIdx < 0) return 1;
		rpOut = rpTop;
		for (u_int ui = 0; ui < uiIdx; ++ui)
		{
			if (!rpOut->rpNext) return 1;
			rpOut = rpOut->rpNext;
		}
		return 0;
	}
	/*�f�[�^���X�g���擾*/
	static const Rep * const GetDataList()
	{
		return rpTop;
	}
	/*���v���C�f�[�^���X�g���t�@�C���֏�������*/
	static bool SaveFile(const std::string &asFileName)
	{
		FILE *fpFile = nullptr;
		fopen_s(&fpFile, asFileName.c_str(), "wb");
		if (!fpFile) return 1;
		auto rpIt = rpTop;
		while (rpIt)
		{
			fprintf_s(fpFile, "%f\n", rpIt->dData);
			rpIt = rpIt->rpNext;
		}
		fclose(fpFile);
		return 0;
	}
	/*�t�@�C�����烊�v���C�f�[�^���X�g��ǂݍ���*/
	static bool LoadFile(const std::string &asFileName)
	{
		FILE *fpFile = nullptr;
		fopen_s(&fpFile, asFileName.c_str(), "rb");
		if (!fpFile) return 1;
		if (sDataSize) Clear();
		double dTmp = 0;
		while (fscanf_s(fpFile, "%lf", &dTmp) != EOF)
		{
			if (Push(dTmp))
			{
				rpOut = rpTop;
				fclose(fpFile);
				return 1;
			}
		}
		rpOut = rpTop;
		fclose(fpFile);
		return 0;
	}
	/*���v���C�f�[�^���X�g���폜*/
	static bool Clear()
	{
		if (!rpTop) return 1;
		auto rpIt = rpTop;
		while (rpIt)
		{
			auto rpNext = rpIt->rpNext;
			free(rpIt);
			rpIt = rpNext;
		}
		rpTop = nullptr;
		sDataSize = 0;
		return 0;
	}
	/*���̗v�f���擾*/
	const Rep * const GetNext() const
	{
		return this->rpNext;
	}
	/*�O�̗v�f���擾*/
	const Rep * const GetPrev() const
	{
		return this->rpPrev;
	}
	/*���ۂ̃f�[�^���擾*/
	const double GetData() const
	{
		return this->dData;
	}
};