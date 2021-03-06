#pragma once

/**
 * @file Color.h
 * @brief FξρΜθ`t@C
 * @author ’]
 * @date Unknown
 */

#include"Math/Math.h"
#include<DxLib.h>

#define COLORTOINT(t) ((int)(t*255.0f))
#define COLORTOFLOAT(t) ((float)t/ 255.0f)

 /*! @class Color
 *   @brief  Fξρ
 */
class Color {
public:
	Color();
	 /// <summary>
	 /// RXgN^<see cref="Color"/>
	 /// </summary>
	 /// <param name="r">Τ (0.0f`1.0f)</param>
	 /// <param name="g">Ξ (0.0f`1.0f)</param>
	 /// <param name="b">Β (0.0f`1.0f)</param>
	 /// <param name="a">At@l (0.0f`1.0f)</param>
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
	 /// FΜβΤ
	 /// </summary>
	 /// <param name="color">βΤ·ιF</param>
	 /// <param name="t">βΤΜδ(0.0f`1.0f)</param>
	 /// <returns>βΤ΅½F</returns>
	Color Lerp(const Color& color, float t) const;
	static Color Lerp(const Color& color1,  const Color& color2, float t);
	 /// <summary>
	 /// DXLIBΜFξρΙΟ·
	 /// </summary>
	 /// <returns>DXLIBΜFξρ</returns>
	unsigned int ToCOLOR() const {
		return GetColor(COLORTOINT(r), COLORTOINT(g), COLORTOINT(b));
	}

	//!Τ
	static const Color Red;
	//!Ξ
	static const Color Green;
	//!Β
	static const Color Blue;
	//!©
	static const Color Yellow;
	//!
	static const Color Black;
	//!
	static const Color White;

public:
	//!Τ
	float r;
	//!Ξ
	float g;
	//!Β
	float b;
	//!At@l
	float a;
};