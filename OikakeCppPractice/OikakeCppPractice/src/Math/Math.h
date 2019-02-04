#pragma once

#include<cmath>

/**
 * @file Math.h
 * @brief 標準ライブラリの数学関数をラッピングしたクラス定義ファイル
 * @author 阿曽
 * @date Unknown
 */

/*! @class Math
 *   @brief  標準ライブラリの数学関数をラッピングしたクラス
 */
class Math {
public:
	/// <summary>
	/// 二乗根（ルート）を求める
	/// </summary>
	/// <param name="value">値</param>
	/// <returns>ルートの値</returns>
	static float SquareRoot(float value);

	/// <summary>小さい値を求める</summary>
	/// <param name="value1">値</param>
	/// <param name="value2">値</param>
	/// <returns>最小の値</returns>
	template<typename T = float>
	static T Min(T value1, T value2) {
		return (T)std::fminf(value1, value2);
	}

	/// <summary>大きい値を求める　</summary>
	/// <param name="value1">値</param>
	/// <param name="value2">値</param>
	/// <returns>最大の値</returns>
	template<typename T = float>
	static T Max(T value1, T value2) {
		return (T)std::fmaxf(value1, value2);
	}

	/// <summary>値を範囲内に収める　</summary>
	/// <param name="value">値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>範囲内の値</returns>
	template<typename T = float>
	static T Clamp(T value, T min, T max) {
		return (T)std::fmaxf(min, (T)std::fminf(value, max));
	}

	/// <summary> 三角関数のサインを求める　</summary>
	/// <param name="angle">角度(度)</param>
	/// <returns>サイン値(-1.0f～1.0f)</returns>
	static float Sin(float angle);

	/// <summary>三角関数のコサインを求める　</summary>
	/// <param name="angle">角度(度)</param>
	/// <returns>コサイン値(-1.0f～1.0f)</returns>
	static float Cos(float angle);

	/// <summary> 三角関数のタンジェントを求める　</summary>
	/// <param name="angle">角度(度)</param>
	/// <returns>タンジェント値(-1.0f～1.0f)</returns>
	static float Tan(float angle);

	/// <summary>三角関数のアークサインを求める　</summary>
	/// <param name="sin">サイン値(-1.0f～1.0f)</param>
	/// <returns>角度(度)</returns>
	static float ArcSin(float sin);

	/// <summary> 三角関数のアークコサインを求める　</summary>
	/// <param name="cos">コサイン値(-1.0f～1.0f)</param>
	/// <returns>角度(度)</returns>
	static float ArcCos(float cos);

	/// <summary> 三角関数のアークタンジェントを求める　</summary>
	/// <param name="tan">タンジェント値(-1.0f～1.0f)</param>
	/// <returns>角度(度)</returns>
	static float ArcTan(float y, float x);
	/// <summary> 三角関数のアークタンジェントを求める　</summary>
	/// <param name="tan">タンジェント値(-1.0f～1.0f)</param>
	/// <returns>角度(度)</returns>
	static float ArcTan(float tan);

	/// <summary>
	/// 絶対値を取得
	/// </summary>
	/// <param name="value">値</param>
	/// <returns>絶対値</returns>
	template<typename T = float>
	static T Abs(T value) {
		return (T)abs(value);
	}

	
	/// <summary>
	/// 値を補間する
	/// </summary>
	/// <param name="value1">value1</param>
	/// <param name="value2">value2</param>
	/// <param name="amount">補間値</param>
	/// <returns>amountで補間された値</returns>
	template<typename T = float>
	static T Lerp(T value1, T value2, float amount) {
		return (value1 * (1.0f - amount)) + (value2 * amount);
	}

	/// <summary>
	/// 値の符号を取得する
	/// </summary>
	/// <param name="value">値</param>
	/// <returns>符号（1 or -1）</returns>
	template<typename T = float>
	static int Sign(T value) {
		return static_cast<int>((value / Math::Abs<float>(value)));
	}

public:
	//!円周率(π)
	static const float PI;
	//!度数法に変換
	static const float toDegree;
	//!ラジアン角に変換
	static const float toRadian;
	//!閾値
	static const float Epsilon;
};
