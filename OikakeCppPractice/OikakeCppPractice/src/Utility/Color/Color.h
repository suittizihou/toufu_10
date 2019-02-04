#pragma once

/**
 * @file Color.h
 * @brief 色情報の定義ファイル
 * @author 阿曽
 * @date Unknown
 */

#include"Math/Math.h"
#include<DxLib.h>

#define COLORTOINT(t) ((int)(t*255.0f))
#define COLORTOFLOAT(t) ((float)t/ 255.0f)

 /*! @class Color
 *   @brief  色情報
 */
class Color {
public:
	Color();
	 /// <summary>
	 /// コンストラクタ<see cref="Color"/>
	 /// </summary>
	 /// <param name="r">赤 (0.0f～1.0f)</param>
	 /// <param name="g">緑 (0.0f～1.0f)</param>
	 /// <param name="b">青 (0.0f～1.0f)</param>
	 /// <param name="a">アルファ値 (0.0f～1.0f)</param>
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
	 /// 色の補間
	 /// </summary>
	 /// <param name="color">補間する色</param>
	 /// <param name="t">補間の比(0.0f～1.0f)</param>
	 /// <returns>補間した色</returns>
	Color Lerp(const Color& color, float t) const;
	static Color Lerp(const Color& color1,  const Color& color2, float t);
	 /// <summary>
	 /// DXLIBの色情報に変換
	 /// </summary>
	 /// <returns>DXLIBの色情報</returns>
	unsigned int ToCOLOR() const {
		return GetColor(COLORTOINT(r), COLORTOINT(g), COLORTOINT(b));
	}

	//!赤
	static const Color Red;
	//!緑
	static const Color Green;
	//!青
	static const Color Blue;
	//!黄
	static const Color Yellow;
	//!黒
	static const Color Black;
	//!白
	static const Color White;

public:
	//!赤
	float r;
	//!緑
	float g;
	//!青
	float b;
	//!アルファ値
	float a;
};