#pragma once

/**
 * @file Rect.h
 * @brief 矩形の定義ファイル
 * @author 大竹
 * @date 2016/6/10
 */

 /*! @class Rect
 *   @brief  矩形
 */
class Rect {
public:
	 /// <summary>
	 /// コンストラクタ<see cref="Rect"/>
	 /// </summary>
	 /// <param name="left">左上のx座標</param>
	 /// <param name="top">左上のy座標</param>
	 /// <param name="right">ｘの画像サイズ</param>
	 /// <param name="bottom">ｙの画像サイズ</param>
	Rect(float left = 0.0f, float top = 0.0f, float right = 1.0f, float bottom = 1.0f)
		: left(left)
		, top(top)
		, right(right)
		, bottom(bottom) {
	}
	Rect(const Vector2& leftposition,const Vector2& rectsize)
		: left(leftposition.x)
		, top(leftposition.y)
		, right(rectsize.x)
		, bottom(rectsize.y) {
	}
public:
	//!左上のx座標
	float left;
	//!左上のy座標
	float top;
	//!右下のx座標
	float right;
	//!右下のy座標
	float bottom;
};