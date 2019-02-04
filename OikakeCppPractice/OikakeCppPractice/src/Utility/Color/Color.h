#pragma once

/**
 * @file Color.h
 * @brief �F���̒�`�t�@�C��
 * @author ���]
 * @date Unknown
 */

#include"Math/Math.h"
#include<DxLib.h>

#define COLORTOINT(t) ((int)(t*255.0f))
#define COLORTOFLOAT(t) ((float)t/ 255.0f)

 /*! @class Color
 *   @brief  �F���
 */
class Color {
public:
	Color();
	 /// <summary>
	 /// �R���X�g���N�^<see cref="Color"/>
	 /// </summary>
	 /// <param name="r">�� (0.0f�`1.0f)</param>
	 /// <param name="g">�� (0.0f�`1.0f)</param>
	 /// <param name="b">�� (0.0f�`1.0f)</param>
	 /// <param name="a">�A���t�@�l (0.0f�`1.0f)</param>
	Color(float r, float g, float b, float a = 1.0f)
		: r(Math::Clamp(r, 0.0f, 1.0f))
		, g(Math::Clamp(g, 0.0f, 1.0f))
		, b(Math::Clamp(b, 0.0f, 1.0f))
		, a(Math::Clamp(a, 0.0f, 1.0f)) {
	}
	Color(int r, int g, int b, int a = 255)
		: r(Math::Clamp(COLORTOFLOAT(r), 0.0f, 1.0f))
		, g(Math::Clamp(COLORTOFLOAT(g), 0.0f, 1.0f))
		, b(Math::Clamp(COLORTOFLOAT(b), 0.0f, 1.0f))
		, a(Math::Clamp(COLORTOFLOAT(a), 0.0f, 1.0f)) {
	}
	 /// <summary>
	 /// �F�̕��
	 /// </summary>
	 /// <param name="color">��Ԃ���F</param>
	 /// <param name="t">��Ԃ̔�(0.0f�`1.0f)</param>
	 /// <returns>��Ԃ����F</returns>
	Color Lerp(const Color& color, float t) const;
	static Color Lerp(const Color& color1,  const Color& color2, float t);
	 /// <summary>
	 /// DXLIB�̐F���ɕϊ�
	 /// </summary>
	 /// <returns>DXLIB�̐F���</returns>
	unsigned int ToCOLOR() const {
		return GetColor(COLORTOINT(r), COLORTOINT(g), COLORTOINT(b));
	}

	//!��
	static const Color Red;
	//!��
	static const Color Green;
	//!��
	static const Color Blue;
	//!��
	static const Color Yellow;
	//!��
	static const Color Black;
	//!��
	static const Color White;

public:
	//!��
	float r;
	//!��
	float g;
	//!��
	float b;
	//!�A���t�@�l
	float a;
};