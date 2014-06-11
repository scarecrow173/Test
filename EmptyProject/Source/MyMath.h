//=======================================================================================
//!	@file	:	MyMath.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================

#pragma once
#include <math.h>

typedef D3DXVECTOR3	Vector3;
typedef D3DXVECTOR2	Vector2;
typedef D3DXMATRIX	Matrix;

namespace AK
{
namespace Math
{

static const F32	PI			= 3.1415926535897932384626433832795f;		//!< �~����
static const F32	PI2			= 6.283185307179586476925286766559f;		//!< �~���� * 2
static const F32	PI_HALF		= 1.5707963267948966192313216916398f;		//!< �~���� * 0.5
static const F32	TO_RAD		= 0.01745329251994329576923690768489f;		//!< 
static const F32	TO_DEG		= 57.295779513082320876798154814105f;		//!< 
static const F32	EPSILON		= 0.00000011920928955078125f;				//!< F32�̌��E���x(1/2^23)
static const F32	F32_MAX		= 1.7014117331926442990585209174226e+38f;	//!< F32�̍ő�l((2^24-1)/2^23 * 2^126 )
static const F32	F32_MIN		= 1.175494e-38f;							//!< F32�̍ŏ��l
static const F32	F32_ERROR	= 1e-6f;									//!< ���������_�̌덷�͈̔� ( �����_��6�ʂ܂� )

//  �O�p�֐�
F32 Sin( F32 rad );
F32 Cos( F32 rad );
F32 Tan( F32 rad );
//  �t�O�p�֐�
F32 ArcSin( F32 val );
F32 ArcCos( F32 val );
F32 ArcTan( F32 val);
F32 ArcTan2( F32 a, F32 b);
//  �ݏ�( a��b�� )
F32 Pow( F32 val, F32 exponent);
//  2���Ƃ���ΐ�
F32 Log2( F32 val);
//  10���Ƃ���ΐ�
F32 Log10( F32 val);
//  ������
F32 Sqrt( F32 val);
//  �񐔃`�F�b�N
bool isNaN( F32 val);
// �f�B�O���[�����W�A���֕ϊ�
F32 DegToRad(F32 deg);
// ���W�A�����f�B�O���[�֕ϊ�
F32 RadToDeg(F32 rad);
// �p�̐��K��
F32 AngleNormalize( F32 rad );
// 2�ׂ̂���
S32 PowerofTwo( S32 num );
bool isPowerofTwo( S32 num );
//  �덷���l���������������_�����䔻��
bool Equalf( F32 a, F32 b, F32 e = F32_ERROR );

Vector3 ScreenToWorld(const Vector2 pos, F32 z, F32 screenWidth, F32 screenHeight, const Matrix& view, const Matrix& proj);
Vector2 WorldToScreen(const Vector3 pos, S32 screenWidth, S32 screenHeight, const Matrix& viewProj);

//-------------------------------------------------------------
//!	@brief		: ��Βl
//!	@param[in]	: ���l
//!	@return		: ��Βl
//-------------------------------------------------------------
template< class T >
T Abs(T val)
{
    return (val < 0) ? -val : val;
}

//-------------------------------------------------------------
//!	@brief		: ���l��r(�傫������Ԃ�)
//!	@param[in]	: ��r����l1
//!	@param[in]	: ��r����l2
//!	@return		: �傫���l
//-------------------------------------------------------------
template< class T >
T Max( T a, T b )
{
	return ( a > b )? a : b;
}
//-------------------------------------------------------------
//!	@brief		: ���l��r(����������Ԃ�)
//!	@param[in]	: ��r����l1
//!	@param[in]	: ��r����l2
//!	@return		: �������l
//-------------------------------------------------------------
template< class T >
T Min( T a, T b )
{
	return  ( a < b )? a : b;
}
//-------------------------------------------------------------
//!	@brief		: ���`���
//!	@param[in]	: �v�Z���ʂ̊i�[��
//!	@param[in]	: ���ݒl
//!	@param[in]	: �ڕW�l
//!	@param[in]	: �W��
//-------------------------------------------------------------
template< typename T >
inline void LinearInterpolation( T* Out, const T& src, const T& target, const F32 t )
{
	T temp;
    assert( Out );
    if( Equalf( t, 1.0f ) ) temp = target;  //  ������1�Ȃ�target�Z�b�g
    else
	{
        temp = target;
        temp -= src;			
        temp *= (T)t;  //  ����
        temp += src;
    }
	*Out = temp;
}

};
};
//===============================================================
//	End of File
//===============================================================