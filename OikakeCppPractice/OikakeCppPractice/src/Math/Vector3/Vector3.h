#pragma once

class Matrix4;

/**
 * @file Vector3.h
 * @brief ３次元ベクトル定義ファイル
 * @author 阿曽
 * @date Unknown
 */

/*! @class Vector3
 *   @brief  ３次元ベクトル
 */
class Vector3 {
public:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="z">z座標</param>
	Vector3(float x, float y, float z);	
	/// <summary>
	///コンストラクタ
	/// </summary>
	/// <param name="vector">3次元ベクトル</param>
	Vector3(const Vector3& vector);	
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Vector3();	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Vector3();

	/// <summary>
	/// 正規化
	/// </summary>
	void Normalize();
	/// <summary>
	/// 法線ベクトルを取得
	/// </summary>
	/// <returns>法線ベクトル</returns>
	Vector3 GetNormal() const;
	/// <summary>
	/// ベクトルの長さを取得
	/// </summary>
	/// <returns>ベクトルの長さ</returns>
	float Length()const;
	/// <summary>
	/// ベクトルの長さの2乗の値を取得
	/// </summary>
	/// <returns>ベクトルの長さの2乗の値</returns>
	float SquareLength() const;
	/// <summary>
	/// コンソール画面に出力
	/// </summary>
	void Print();


	/// <summary>
	/// ベクトルを範囲内に収める
	/// </summary>
	/// <param name="min">収める範囲の最小のベクトル</param>
	/// <param name="max">収める範囲の最大のベクトル</param>
	void Clamp(const Vector3& min, const Vector3& max);

	/// <summary>
	/// ２点間の距離を求める
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <returns>
	/// ２点間の距離
	/// </returns>
	float Distance(const Vector3& vec) const;
	
	/// <summary>
	/// ２点間の距離の　二乗　を求める
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <returns>
	/// ２点間の距離の　二乗
	/// </returns>
	float DistanceSquare(const Vector3& vec) const;

	/// <summary>
	/// 2つのベクトルの角度を求める
	/// </summary>
	/// <param name="vec">vec</param>
	/// <returns>
	/// 2つのベクトルの角度(度)
	/// </returns>
	float Angle(const Vector3& vec) const;

	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <returns>
	/// スカラー
	/// </returns>
	float Dot(const Vector3& vec) const;
	/// <summary>
	/// 外積
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <returns>
	/// ベクトル
	/// </returns>
	Vector3 Cross(const Vector3& vec);

	/// <summary>
	/// 2つのベクトルの線形補間
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="lerpTime">値(0.0f～1.0f)</param>
	/// <returns>
	/// 補間されたベクトル
	/// </returns>
	Vector3 Lerp(const Vector3& vec, float lerpTime);

	
	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="matrix">座標変換させる行列</param>
	/// <returns>
	/// 座標変換したベクトル
	/// </returns>
	Vector3 Transform(const Matrix4& matrix);
	/// <summary>
	/// 回転行列で変換する
	/// </summary>
	/// <param name="matrix">変換させる行列</param>
	/// <returns>
	/// 回転行列で変換したベクトル
	/// </returns>
	Vector3 TransformNormal(const Matrix4& matrix) const;
	/// <summary>
	/// ヨー・ピッチからベクトルを作成
	/// </summary>
	/// <param name="yaw">ヨー(Z軸回転)：度数法</param>
	/// <param name="pitch">ピッチ(Y軸回転)：度数法</param>
	/// <returns>
	/// ヨー・ピッチから作られたベクトル
	/// </returns>
	static Vector3 CreateFromYawPitch(float yaw, float pitch);
	
	/// <summary>
	/// ベクトルからピッチを取得（Y軸回転）
	/// </summary>
	/// <returns>
	/// Y軸の回転角度：度数法
	/// </returns>
	float Pitch()const;

	/// <summary>
	/// ベクトルからヨーを取得（Z軸回転）
	/// </summary>
	/// <returns>
	/// Z軸の回転角度：度数法
	/// </returns>
	float Yaw() const;

public:
	//!X座標
	float x;
	//!Y座標
	float y;
	//!Z座標
	float z;

public:	
	Vector3 operator + ();
	Vector3 operator - ();
	Vector3 operator + (const Vector3& vector) const;
	Vector3 operator - (const Vector3& vector) const;
	Vector3 operator * (float scalar) const;
	Vector3 operator / (float scalar) const;
	Vector3& operator += (const Vector3& vector);
	Vector3& operator -= (const Vector3& vector);
	Vector3& operator *= (float scalar);
	Vector3& operator /= (float scalar);

public:
	//! Vector3( 0,  1,  0)
	static const Vector3 Up;			
	//! Vector3( 0, -1,  0)
	static const Vector3 Down;			
	//! Vector3(-1,  0,  0)
	static const Vector3 Left;			
	//! Vector3( 1,  0,  0)
	static const Vector3 Right;		
	//! Vector3( 0,  0, -1)
	static const Vector3 Backward;		
	//! Vector3( 0,  0,  1)
	static const Vector3 Forward;		
	//! Vector3( 1,  0,  0)
	static const Vector3 UnitX;		
	//! Vector3( 0,  1,  0)
	static const Vector3 UnitY;			
	//! Vector3( 0,  1,  1)
	static const Vector3 UnitZ;		
	//! Vector3( 1,  1,  1)
	static const Vector3 One;			
	//! Vector3( 0,  0,  0)
	static const Vector3 Zero;			
};
// scalar * vector を定義
inline Vector3 operator*(float scalar, const Vector3 & vector)
{
	return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}
