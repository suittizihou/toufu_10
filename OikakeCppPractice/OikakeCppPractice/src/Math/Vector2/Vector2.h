#pragma once

/**
 * @file Vector2.h
 * @brief 2次元ベクトル定義ファイル
 * @author 阿曽
 * @date 2015/10/22
 */

 /*! @class Vector2
 *   @brief  2次元ベクトル
 */
class Vector2 {
public:	
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Vector2();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	Vector2(float x, float y);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="vector">２次元ベクトル</param>
	Vector2(const Vector2& vector);	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Vector2();

	/// <summary>
	/// ベクトルの長さを取得
	/// </summary>
	/// <returns>
	/// ベクトルの長さ
	/// </returns>
	float Length() const;

	/// <summary>
	/// ベクトルの2乗の長さを取得
	/// </summary>
	/// <returns>
	/// ベクトルの2乗の長さ
	/// </returns>
	float SquareLength() const;

	/// <summary>
	/// ベクトルを正規化(長さ１に)する
	/// </summary>
	void Normalize();

	/// <summary>
	/// 正規化(長さ１に)したベクトルを取得
	/// </summary>
	/// <returns>
	/// 正規化されたベクトル
	/// </returns>
	Vector2 GetNormal() const;

	/// <summary>
	/// XとYの要素をコンソール画面に表示
	/// </summary>
	void Print() const;

public:
	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>スカラー</returns>
	float Dot(const Vector2& vector);

	/// <summary>
	/// 外積
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>スカラー</returns>
	float Cross(const Vector2& vector);

	/// <summary>
	/// ２点間の距離を求める
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>2点間の距離</returns>
	float Distance(const Vector2& vector);

	/// <summary>
	/// ベクトルを範囲内に収める
	/// </summary>
	/// <param name="min">収める範囲の最小のベクトル</param>
	/// <param name="max">収める範囲の最大のベクトル</param>
	bool Clamp(const Vector2& min, const Vector2& max);

	/// <summary>
	/// 2つのベクトルの角度を求める
	/// </summary>
	/// <param name="vec">vec</param>
	/// <returns>
	/// 2つのベクトルの角度(度)
	/// </returns>
	float Angle(const Vector2& vector);

	/// <summary>
	/// 2つのベクトルの線形補間
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="lerpTime">値(0.0f～1.0f)</param>
	/// <returns>
	/// 補間されたベクトル
	/// </returns>
	Vector2 Lerp(const Vector2& vector, float lerpTime);

	/// <summary>
	/// 原点を中心に回転するベクトルを求める
	/// </summary>
	/// <param name="angle">角度：度数法</param>
	/// <returns>原点を中心に回転したベクトル</returns>
	Vector2 Rotate(float angle);

public:
	//!X要素
	float x;
	//!Y要素
	float y;

public:
	Vector2 operator + ();
	Vector2 operator - ();
	Vector2 operator + (const Vector2& vector) const;
	Vector2 operator - (const Vector2& vector) const;
	Vector2 operator * (float scalar) const;
	Vector2 operator / (float scalar) const;
	Vector2& operator += (const Vector2& vector);
	Vector2& operator -= (const Vector2& vector);
	Vector2& operator *= (float scalar);
	Vector2& operator /= (float scalar);

public:
	//! Vector2( 0,  1)
	static const Vector2 Up;			
	//! Vector2( 0, -1)
	static const Vector2 Down;			
	//! Vector2(-1,  0)
	static const Vector2 Left;			
	//! Vector2( 1,  0)
	static const Vector2 Right;			
	//! Vector2( 1,  0)
	static const Vector2 UnitX;			
	//! Vector2( 0,  1)
	static const Vector2 UnitY;			
	//! Vector2( 1,  1)
	static const Vector2 One;			
	//! Vector2( 0,  0)
	static const Vector2 Zero;			
};
