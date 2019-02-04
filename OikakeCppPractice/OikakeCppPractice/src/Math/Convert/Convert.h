#pragma once

class Vector3;
class Vector2;
class Matrix4;
#include<DxLib.h>

/**
 * @file Convert.h
 * @brief �ϊ��N���X
 * @author ���]
 * @date Unknown
 */

/*! @class Convert
 *   @brief  �ϊ��N���X
 */
class Convert {
public:	
	/// <summary>
	/// VECTOR�ɕϊ�����
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	/// <returns>VECTOR</returns>
	static VECTOR ToVECTOR(const Vector2& vector);
	/// <summary>
	/// VECTOR�ɕϊ�����
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	/// <returns>VECTOR</returns>
	static VECTOR ToVECTOR(const Vector3& vector);
	/// <summary>
	/// MATRIX�ɕϊ�����
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	/// <returns>MATRIX</returns>
	static MATRIX ToMATRIX(const Matrix4& matrix);	
	/// <summary>
	/// Vector2�ɕϊ�����
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector2</returns>
	static Vector2 ToVector2(const VECTOR& vector);
	/// <summary>
	/// Vector2�ɕϊ�����
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector2</returns>
	static Vector2 ToVector2(const Vector3& vector);
	/// <summary>
	/// Vector3�ɕϊ�����
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector3</returns>
	static Vector3 ToVector3(const VECTOR& vector);	
	/// <summary>
	/// Vector2��Vector3(x,0,z)�ɕϊ�����
	/// </summary>
	/// <param name="vector">vector</param>
	/// <returns>Vector3</returns>
	static Vector3 ToVector3_xz(const Vector2& vector);
	/// <summary>
	/// Matrix4�ɕϊ�����
	/// </summary>
	/// <param name="matrix">matrix</param>
	/// <returns>Matrix4</returns>
	static Matrix4 ToMatrix4(const MATRIX& matrix);

};