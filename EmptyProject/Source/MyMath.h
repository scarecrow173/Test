//=======================================================================================
//!	@file	:	MyMath.h
//!	@author	:	小山 瑛圭
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

static const F32	PI			= 3.1415926535897932384626433832795f;		//!< 円周率
static const F32	PI2			= 6.283185307179586476925286766559f;		//!< 円周率 * 2
static const F32	PI_HALF		= 1.5707963267948966192313216916398f;		//!< 円周率 * 0.5
static const F32	TO_RAD		= 0.01745329251994329576923690768489f;		//!< 
static const F32	TO_DEG		= 57.295779513082320876798154814105f;		//!< 
static const F32	EPSILON		= 0.00000011920928955078125f;				//!< F32の限界精度(1/2^23)
static const F32	F32_MAX		= 1.7014117331926442990585209174226e+38f;	//!< F32の最大値((2^24-1)/2^23 * 2^126 )
static const F32	F32_MIN		= 1.175494e-38f;							//!< F32の最小値
static const F32	F32_ERROR	= 1e-6f;									//!< 浮動小数点の誤差の範囲 ( 小数点第6位まで )

//  三角関数
F32 Sin( F32 rad );
F32 Cos( F32 rad );
F32 Tan( F32 rad );
//  逆三角関数
F32 ArcSin( F32 val );
F32 ArcCos( F32 val );
F32 ArcTan( F32 val);
F32 ArcTan2( F32 a, F32 b);
//  累乗( aのb乗 )
F32 Pow( F32 val, F32 exponent);
//  2を底とする対数
F32 Log2( F32 val);
//  10を底とする対数
F32 Log10( F32 val);
//  平方根
F32 Sqrt( F32 val);
//  非数チェック
bool isNaN( F32 val);
// ディグリーをラジアンへ変換
F32 DegToRad(F32 deg);
// ラジアンをディグリーへ変換
F32 RadToDeg(F32 rad);
// 角の正規化
F32 AngleNormalize( F32 rad );
// 2のべき乗
S32 PowerofTwo( S32 num );
bool isPowerofTwo( S32 num );
//  誤差を考慮した浮動小数点数等比判定
bool Equalf( F32 a, F32 b, F32 e = F32_ERROR );

Vector3 ScreenToWorld(const Vector2 pos, F32 z, F32 screenWidth, F32 screenHeight, const Matrix& view, const Matrix& proj);
Vector2 WorldToScreen(const Vector3 pos, S32 screenWidth, S32 screenHeight, const Matrix& viewProj);

//-------------------------------------------------------------
//!	@brief		: 絶対値
//!	@param[in]	: 数値
//!	@return		: 絶対値
//-------------------------------------------------------------
template< class T >
T Abs(T val)
{
    return (val < 0) ? -val : val;
}

//-------------------------------------------------------------
//!	@brief		: 数値比較(大きい方を返す)
//!	@param[in]	: 比較する値1
//!	@param[in]	: 比較する値2
//!	@return		: 大きい値
//-------------------------------------------------------------
template< class T >
T Max( T a, T b )
{
	return ( a > b )? a : b;
}
//-------------------------------------------------------------
//!	@brief		: 数値比較(小さい方を返す)
//!	@param[in]	: 比較する値1
//!	@param[in]	: 比較する値2
//!	@return		: 小さい値
//-------------------------------------------------------------
template< class T >
T Min( T a, T b )
{
	return  ( a < b )? a : b;
}
//-------------------------------------------------------------
//!	@brief		: 線形補間
//!	@param[in]	: 計算結果の格納先
//!	@param[in]	: 現在値
//!	@param[in]	: 目標値
//!	@param[in]	: 係数
//-------------------------------------------------------------
template< typename T >
inline void LinearInterpolation( T* Out, const T& src, const T& target, const F32 t )
{
	T temp;
    assert( Out );
    if( Equalf( t, 1.0f ) ) temp = target;  //  割合が1ならtargetセット
    else
	{
        temp = target;
        temp -= src;			
        temp *= (T)t;  //  割合
        temp += src;
    }
	*Out = temp;
}

};
};
//===============================================================
//	End of File
//===============================================================