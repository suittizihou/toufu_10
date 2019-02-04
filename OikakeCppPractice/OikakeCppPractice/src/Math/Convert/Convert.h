#pragma once

class Vector3;
class Vector2;
class Matrix4;
#include<DxLib.h>

/**
 * @file Convert.h
 * @brief 変換クラス
 * @author 阿曽
 * @date Unknown
 */

/*! @class Convert
 *   @brief  変換クラス
 */
class Convert {
public:	
	/// <summary>
	/// VECTORに変換する
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>VECTOR</returns>
	static VECTOR ToVECTOR(const Vector2& vector);
	/// <summary>
	/// VECTORに変換する
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>VECTOR</returns>
	static VECTOR ToVECTOR(const Vector3& vector);
	/// <summary>
	/// MATRIXに変換する
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>MATRIX</returns>
	static MATRIX ToMATRIX(const Matrix4& matrix);	
	/// <summary>
	/// Vector2に変換する
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector2</returns>
	static Vector2 ToVector2(const VECTOR& vector);
	/// <summary>
	/// Vector2に変換する
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector2</returns>
	static Vector2 ToVector2(const Vector3& vector);
	/// <summary>
	/// Vector3に変換する
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector3</returns>
	static Vector3 ToVector3(const VECTOR& vector);	
	/// <summary>
	/// Vector2をVector3(x,0,z)に変換する
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector3</returns>
	static Vector3 ToVector3_xz(const Vector2& vector);
	/// <summary>
	/// Matrix4に変換する
	/// </summary>
	/// <param name="matrix">matrix</param>
	/// <returns>Matrix4</returns>
	static Matrix4 ToMatrix4(const MATRIX& matrix);

};