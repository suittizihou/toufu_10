#pragma once

class Vector3;
class Matrix4;

/**
 * @file Quaternion.h
 * @brief クォータニオン定義ファイル
 * @author 阿曽
 * @date Unknown
 */

 /*! @class Quaternion
 *   @brief  クォータニオン
 */
class Quaternion {
public:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">x要素</param>
	/// <param name="y">y要素</param>
	/// <param name="z">z要素</param>
	/// <param name="w">w要素</param>
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="axis">回転の基準にする軸</param>
	/// <param name="angle">回転角度：度数法</param>
	Quaternion(const Vector3& axis, float angle);	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="m">行列</param>
	explicit Quaternion(const Matrix4& m);	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Quaternion();	
	/// <summary>
	/// 正規化する
	/// </summary>
	/// <returns>正規化したクォータニオン</returns>
	Quaternion& Normalize();	
	/// <summary>
	/// 正規化する
	/// </summary>
	/// <returns>正規化したクォータニオン</returns>
	Quaternion GetNormal();	
	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="q">クォータニオン</param>
	/// <returns>スカラー</returns>
	float Dot(const Quaternion& q);	
	/// <summary>
	/// 長さを取得
	/// </summary>
	/// <returns>長さ</returns>
	float Length();	
	/// <summary>
	/// 球面線形補間をする
	/// </summary>
	/// <param name="q">クォータニオン</param>
	/// <param name="amount">比</param>
	/// <returns>球面線形補間をしたクォータニオン</returns>
	Quaternion Slerp(const Quaternion& q, float amount);	
	/// <summary>
	/// 回転行列を取得する
	/// </summary>
	/// <returns>回転行列</returns>
	Matrix4 ToRotateMatrix();	
	/// <summary>
	/// 回転行列をクォータニオンに変換する
	/// </summary>
	/// <param name="m">回転行列</param>
	/// <returns>クォータニオン</returns>
	Quaternion CreateFromRotationMatrix(const Matrix4& m);

public:
	Quaternion operator - ();
	Quaternion& operator += (const Quaternion& q);
	Quaternion& operator -= (const Quaternion& q);
	Quaternion& operator *= (float scalar);
	Quaternion& operator *= (const Quaternion& q);
	Quaternion& operator /= (float scalar);
	Quaternion operator + (const Quaternion& q);
	Quaternion operator - (const Quaternion& q);
	Quaternion operator * (const Quaternion& q);
	Quaternion operator * (float scalar);
	Quaternion operator / (float scalar);

private:	
	/// <summary>
	/// クォータニオン同士掛け算をする
	/// </summary>
	/// <param name="q1">クォータニオン</param>
	/// <param name="q2">クォータニオン</param>
	/// <returns>掛け算したクォータニオン</returns>
	Quaternion Mul(const Quaternion& q1, const Quaternion& q2);

public:
	//!X要素
	float x;
	//!Y要素
	float y;
	//!Z要素
	float z;
	//!W要素
	float w;
};

inline Quaternion operator * (float scalar, const Quaternion& q) {
	return Quaternion(q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar);
}