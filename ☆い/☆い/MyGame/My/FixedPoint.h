#ifndef FIXEDPOINT
#define FIXEDPOINT
/*�Œ菬���_���C�u����*/

/*�����̊���Z*/
inline constexpr long Div(long n, long d)
{
	long m = 1, q = 0;
	while (d <= n) {
		d <<= 1;
		m <<= 1;
	}
	while (1 < m) {
		d >>= 1;
		m >>= 1;
		if (n >= d) {
			n -= d;
			q |= m;
		}
	}
	// q=�� / n=�]��
	return q;
}

/*�Œ菬���_���C�u�����֐��̏����r�b�g��*/
constexpr unsigned char DECIMAL_BITS = 8;
/*�l�̌ܓ�*/
inline constexpr long Round(const double dVal)
{
	return (long)(dVal + 0.5);
}
/*�Œ菬���_�ɕϊ�*/
inline constexpr long FP(const double dVal)
{
	return Round(dVal * (1 << DECIMAL_BITS));
}
/*�Œ菬���_�ɕϊ�*/
inline constexpr long FP(const long lVal)
{
	return lVal * (1 << DECIMAL_BITS);
}
/*�Œ菬���_�ɕϊ�*/
inline constexpr long FP(const unsigned long ulVal)
{
	return (long)ulVal * (1 << DECIMAL_BITS);
}
/*�����ɕϊ�*/
inline constexpr long FToL(const long lFPVal)
{
	return lFPVal >> DECIMAL_BITS;
}
/*���������_�ɕϊ�*/
inline constexpr double FToD(const long lFPVal)
{
	double dest = lFPVal >> DECIMAL_BITS;
	long mask = 1 << (DECIMAL_BITS - 1);
	double digit = 0.5;
	for (unsigned char b = 0; b < DECIMAL_BITS; ++b)
	{
		if (lFPVal & mask) dest += digit;
		mask >>= 1;
		digit *= 0.5;
	}
	return dest;
}
/*�Œ菬���_�̑����Z*/
inline constexpr long AddFP(const long lFPVal1, const long lFPVal2)
{
	return lFPVal1 + lFPVal2;
}
/*�Œ菬���_�̈����Z*/
inline constexpr long SubFP(const long lFPVal1, const long lFPVal2)
{
	return lFPVal1 - lFPVal2;
}
/*�Œ菬���_�̊|���Z*/
inline constexpr long MulFP(const long lFPVal1, const long lFPVal2)
{
	return (lFPVal1 * lFPVal2) >> DECIMAL_BITS;
}
/*�Œ菬���_�̊���Z�i�O�Ŋ��낤�Ƃ���ƂO���Ԃ�j*/
inline constexpr long DivFP(const long lFPVal1, const long lFPVal2)
{
	/**/
	return ((lFPVal2) ? Div(lFPVal1 << DECIMAL_BITS, lFPVal2) : 0);
	/*/
	return ((lFPVal2) ? ((lFPVal1 << DECIMAL_BITS) / lFPVal2) : 0);
	/**/
}

/*fixed�̍ő�l*/
constexpr float FIXED_MAX = float(1 << ((sizeof(short) * 8) - 6));
/*�T�C�Y�Q�o�C�g�A�����r�b�g���U�̌Œ菬���^*/
/*�ő�l��1024.0�Ə������A�I�[�o�[�t���[���₷���̂Œ��ӁI*/
struct fixed
{
private:
	/*���������ϐ�*/
	short sVal;
	/*�Œ菬���_���Z�p�����o*/
	inline const short _Round(const double v) const
	{
		return (short)(v + 0.5);
	}
	inline const short _Round(const float v) const
	{
		return (short)(v + 0.5f);
	}
	inline const short _FP(const double v) const
	{
		return _Round(v * (1 << 6));
	}
	inline const short _FP(const float v) const
	{
		return _Round(v * (1 << 6));
	}
	inline const short _FP(const short v) const
	{
		return v * (1 << 6);
	}
	inline const short _FP(const int v) const
	{
		return short(v * (1 << 6));
	}
	inline const short _FToS(const short v) const
	{
		return v >> 6;
	}
	inline const double _FToD(const short v) const
	{
		double dest = v >> 6;
		short mask = 1 << (6 - 1);
		double digit = 0.5;
		for (unsigned char b = 0; b < 6; ++b)
		{
			if (v & mask) dest += digit;
			mask >>= 1;
			digit *= 0.5;
		}
		return dest;
	}
	inline const float _FToF(const short v) const
	{
		double dest = v >> 6;
		short mask = 1 << (6 - 1);
		double digit = 0.5;
		for (unsigned char b = 0; b < 6; ++b)
		{
			if (v & mask) dest += digit;
			mask >>= 1;
			digit *= 0.5;
		}
		return (float)dest;
	}
	inline const short _AddFP(const short v1, const short v2) const
	{
		return v1 + v2;
	}
	inline const short _SubFP(const short v1, const short v2) const
	{
		return v1 - v2;
	}
	inline const short _MulFP(const short v1, const short v2) const
	{
		return (v1 * v2) >> 6;
	}
	inline const short _DivFP(const short v1, const short v2) const
	{
		/**/
		return ((v2) ? (short)Div((long)v1 << 6, (long)v2) : 0);
		/*/
		return ((v2) ? ((v1 << 6) / v2) : 0);
		/**/
	}
public:
	/*�R���X�g���N�^*/
	inline fixed()
		:
		sVal(0)
	{

	}
	inline fixed(const fixed &f)
		:
		sVal(f.sVal)
	{

	}
	inline fixed(const float f)
		:
		sVal(_FP(f))
	{

	}
	inline fixed(const double d)
		:
		sVal(_FP(d))
	{

	}
	inline fixed(const int i)
		:
		sVal(_FP(i))
	{

	}
	/*���^�Ƃ̉��Z*/
	inline fixed &operator = (const fixed &f)
	{
		sVal = f.sVal;
		return *this;
	}
	inline const float operator + (const fixed &f) const
	{
		return _FToF(_AddFP(sVal, f.sVal));
	}
	inline const float operator - (const fixed &f) const
	{
		return _FToF(_SubFP(sVal, f.sVal));
	}
	inline const float operator * (const fixed &f) const
	{
		return _FToF(_MulFP(sVal, f.sVal));
	}
	inline const float operator / (const fixed &f) const
	{
		return _FToF(_DivFP(sVal, f.sVal));
	}
	inline fixed &operator += (const fixed &f)
	{
		sVal = _AddFP(sVal, f.sVal);
		return *this;
	}
	inline fixed &operator -= (const fixed &f)
	{
		sVal = _SubFP(sVal, f.sVal);
		return *this;
	}
	inline fixed &operator *= (const fixed &f)
	{
		sVal = _MulFP(sVal, f.sVal);
		return *this;
	}
	inline fixed &operator /= (const fixed &f)
	{
		sVal = _DivFP(sVal, f.sVal);
		return *this;
	}
	/*float�^�Ƃ̉��Z*/
	inline fixed &operator = (const float f)
	{
		sVal = _FP(f);
		return *this;
	}
	inline const float operator + (const float f) const
	{
		return _FToF(_AddFP(sVal, _FP(f)));
	}
	inline const float operator - (const float f) const
	{
		return _FToF(_SubFP(sVal, _FP(f)));
	}
	inline const float operator * (const float f) const
	{
		return _FToF(_MulFP(sVal, _FP(f)));
	}
	inline const float operator / (const float f) const
	{
		return _FToF(_DivFP(sVal, _FP(f)));
	}
	inline fixed &operator += (const float f)
	{
		sVal = _AddFP(sVal, _FP(f));
		return *this;
	}
	inline fixed &operator -= (const float f)
	{
		sVal = _SubFP(sVal, _FP(f));
		return *this;
	}
	inline fixed &operator *= (const float f)
	{
		sVal = _MulFP(sVal, _FP(f));
		return *this;
	}
	inline fixed &operator /= (const float f)
	{
		sVal = _DivFP(sVal, _FP(f));
		return *this;
	}
	/*double�^�Ƃ̉��Z*/
	inline fixed &operator = (const double d)
	{
		sVal = _FP(d);
		return *this;
	}
	inline const double operator + (const double d) const
	{
		return _FToD(_AddFP(sVal, _FP(d)));
	}
	inline const double operator - (const double d) const
	{
		return _FToD(_SubFP(sVal, _FP(d)));
	}
	inline const double operator * (const double d) const
	{
		return _FToD(_MulFP(sVal, _FP(d)));
	}
	inline const double operator / (const double d) const
	{
		return _FToD(_DivFP(sVal, _FP(d)));
	}
	inline fixed &operator += (const double d)
	{
		sVal = _AddFP(sVal, _FP(d));
		return *this;
	}
	inline fixed &operator -= (const double d)
	{
		sVal = _SubFP(sVal, _FP(d));
		return *this;
	}
	inline fixed &operator *= (const double d)
	{
		sVal = _MulFP(sVal, _FP(d));
		return *this;
	}
	inline fixed &operator /= (const double d)
	{
		sVal = _DivFP(sVal, _FP(d));
		return *this;
	}
	/*int�^�Ƃ̉��Z*/
	inline fixed &operator = (const int i)
	{
		sVal = _FP(i);
		return *this;
	}
	inline const float operator + (const int i) const
	{
		return _FToF(_AddFP(sVal, _FP(i)));
	}
	inline const float operator - (const int i) const
	{
		return _FToF(_SubFP(sVal, _FP(i)));
	}
	inline const float operator * (const int i) const
	{
		return _FToF(_MulFP(sVal, _FP(i)));
	}
	inline const float operator / (const int i) const
	{
		return _FToF(_DivFP(sVal, _FP(i)));
	}
	inline fixed &operator += (const int i)
	{
		sVal = _AddFP(sVal, _FP(i));
		return *this;
	}
	inline fixed &operator -= (const int i)
	{
		sVal = _SubFP(sVal, _FP(i));
		return *this;
	}
	inline fixed &operator *= (const int i)
	{
		sVal = _MulFP(sVal, _FP(i));
		return *this;
	}
	inline fixed &operator /= (const int i)
	{
		sVal = _DivFP(sVal, _FP(i));
		return *this;
	}
	/*�C���N�������g���Z�q*/
	inline fixed &operator ++ ()
	{
		sVal = _AddFP(sVal, _FP(1.0));
		return *this;
	}
	/*�f�N�������g���Z�q*/
	inline fixed &operator -- ()
	{
		sVal = _SubFP(sVal, _FP(1.0));
		return *this;
	}
	/*�C���N�������g���Z�q*/
	inline const fixed operator ++ (int)
	{
		const auto f = *this;
		sVal = _AddFP(sVal, _FP(1.0));
		return f;
	}
	/*�f�N�������g���Z�q*/
	inline const fixed operator -- (int)
	{
		const auto f = *this;
		sVal = _SubFP(sVal, _FP(1.0));
		return f;
	}
	/*���^�Ƃ̔�r*/
	inline const bool operator == (const fixed &f) const
	{
		return (sVal == f.sVal);
	}
	inline const bool operator != (const fixed &f) const
	{
		return (sVal != f.sVal);
	}
	inline const bool operator < (const fixed &f) const
	{
		return (sVal < f.sVal);
	}
	inline const bool operator > (const fixed &f) const
	{
		return (sVal > f.sVal);
	}
	inline const bool operator <= (const fixed &f) const
	{
		return (sVal <= f.sVal);
	}
	inline const bool operator >= (const fixed &f) const
	{
		return (sVal >= f.sVal);
	}
	/*float�^�Ƃ̔�r*/
	inline const bool operator == (const float f) const
	{
		return (sVal == _FP(f));
	}
	inline const bool operator != (const float f) const
	{
		return (sVal != _FP(f));
	}
	inline const bool operator < (const float f) const
	{
		return (sVal < _FP(f));
	}
	inline const bool operator > (const float f) const
	{
		return (sVal > _FP(f));
	}
	inline const bool operator <= (const float f) const
	{
		return (sVal <= _FP(f));
	}
	inline const bool operator >= (const float f) const
	{
		return (sVal >= _FP(f));
	}
	/*double�^�Ƃ̔�r*/
	inline const bool operator == (const double d) const
	{
		return (sVal == _FP(d));
	}
	inline const bool operator != (const double d) const
	{
		return (sVal != _FP(d));
	}
	inline const bool operator < (const double d) const
	{
		return (sVal < _FP(d));
	}
	inline const bool operator > (const double d) const
	{
		return (sVal > _FP(d));
	}
	inline const bool operator <= (const double d) const
	{
		return (sVal <= _FP(d));
	}
	inline const bool operator >= (const double d) const
	{
		return (sVal >= _FP(d));
	}
	/*int�^�Ƃ̔�r*/
	inline const bool operator == (const int i) const
	{
		return (sVal == _FP(i));
	}
	inline const bool operator != (const int i) const
	{
		return (sVal != _FP(i));
	}
	inline const bool operator < (const int i) const
	{
		return (sVal < _FP(i));
	}
	inline const bool operator > (const int i) const
	{
		return (sVal > _FP(i));
	}
	inline const bool operator <= (const int i) const
	{
		return (sVal <= _FP(i));
	}
	inline const bool operator >= (const int i) const
	{
		return (sVal >= _FP(i));
	}
	/*����+���Z�q*/
	inline const fixed operator + () const
	{
		const fixed f = +_FToD(sVal);
		return f;
	}
	/*����-���Z�q*/
	inline const fixed operator - () const
	{
		const fixed f = -_FToD(sVal);
		return f;
	}
	/*���]���Z�q*/
	inline const bool operator ! () const
	{
		return (!sVal);
	}
	/*float�^�ւ̃L���X�g*/
	inline operator float() const
	{
		return _FToF(sVal);
	}
	/*double�^�ւ̃L���X�g*/
	inline operator double() const
	{
		return _FToD(sVal);
	}
	/*int�^�ւ̃L���X�g*/
	inline operator int() const
	{
		return (int)(_FToD(sVal) + 0.5);
	}
	/*bool�^�ւ̃L���X�g*/
	inline operator bool() const
	{
		return (bool)_FToD(sVal);
	}
	/*�l�X�Ȍ^�ւ̃L���X�g*/
	template<class CastType>
	inline operator CastType() const
	{
		return (CastType)_FToD(sVal);
	}
};
/*�O���[�o�����Z�q�I�[�o�[���[�h*/
/*float�^�Ƃ̉��Z*/
inline const float operator + (const float v1, const fixed &v2)
{
	return v2 + v1;
}
inline const float operator - (const float v1, const fixed &v2)
{
	return v2 - v1;
}
inline const float operator * (const float v1, const fixed &v2)
{
	return v2 * v1;
}
inline const float operator / (const float v1, const fixed &v2)
{
	return v1 / (float)v2;
}

inline const float &operator += (float &v1, const fixed &v2)
{
	v1 += (float)v2;
	return v1;
}
inline const float &operator -= (float &v1, const fixed &v2)
{
	v1 -= (float)v2;
	return v1;
}
inline const float &operator *= (float &v1, const fixed &v2)
{
	v1 *= (float)v2;
	return v1;
}
inline const float &operator /= (float &v1, const fixed &v2)
{
	v1 /= (float)v2;
	return v1;
}
/*double�^�Ƃ̉��Z*/
inline const double operator + (const double v1, const fixed &v2)
{
	return v2 + v1;
}
inline const double operator - (const double v1, const fixed &v2)
{
	return v2 - v1;
}
inline const double operator * (const double v1, const fixed &v2)
{
	return v2 * v1;
}
inline const double operator / (const double v1, const fixed &v2)
{
	return v1 / (double)v2;
}

inline const double &operator += (double &v1, const fixed &v2)
{
	v1 += (double)v2;
	return v1;
}
inline const double &operator -= (double &v1, const fixed &v2)
{
	v1 -= (double)v2;
	return v1;
}
inline const double &operator *= (double &v1, const fixed &v2)
{
	v1 *= (double)v2;
	return v1;
}
inline const double &operator /= (double &v1, const fixed &v2)
{
	v1 /= (double)v2;
	return v1;
}
/*int�^�Ƃ̉��Z*/
inline const float operator + (const int v1, const fixed &v2)
{
	return v2 + v1;
}
inline const float operator - (const int v1, const fixed &v2)
{
	return v2 - v1;
}
inline const float operator * (const int v1, const fixed &v2)
{
	return v2 * v1;
}
inline const float operator / (const int v1, const fixed &v2)
{
	return v1 / (float)v2;
}

inline const int &operator += (int &v1, const fixed &v2)
{
	v1 = int(v1 + v2);
	return v1;
}
inline const int &operator -= (int &v1, const fixed &v2)
{
	v1 = int(v1 - v2);
	return v1;
}
inline const int &operator *= (int &v1, const fixed &v2)
{
	v1 = int(v1 * v2);
	return v1;
}
inline const int &operator /= (int &v1, const fixed &v2)
{
	v1 = int(v1 / v2);
	return v1;
}
/*abs(fixed)*/
inline const fixed Abs(const fixed &x)
{
	return ((x > 0.0) ? x : ((x < 0.0) ? -x : x));
}
#endif