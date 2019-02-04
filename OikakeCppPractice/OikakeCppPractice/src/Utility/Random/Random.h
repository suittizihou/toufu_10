# pragma once

/**
 * @file Ramdom.h
 * @brief ランダム関数を定義するファイル
 * @author 堀
 * @date Unknown
 */


# include <algorithm>

# include <functional>

# include <random>

# include <iostream>


/*! @class Random
*   @brief ランダム関数をまとめたクラス
*/
class Random{
private:
	 /// <summary>
	 /// 乱数生成インスタンスを返す
	 /// </summary>
	 /// <returns>乱数生成インスタンス</returns>
	static std::mt19937& GetInstance();
public:
	 /// <summary>
	 /// [min～max]の乱数を返す　int版
	 /// </summary>
	 /// <param name="min">包括的最小値</param>
	 /// <param name="max">排他的最大値</param>
	 /// <returns>[min～max]の乱数</returns>
	static int Range(int min, int max);
	/// <summary>
	/// [min～max]の乱数を返す float版
	/// </summary>
	/// <param name="min">包括的最小値</param>
	/// <param name="max">排他的最大値</param>
	/// <returns>[min～max]の乱数</returns>
	static float Rangef(float min, float max);
	 /// <summary>
	 /// 0.0f～1.0fまでの乱数を返す
	 /// </summary>
	 /// <returns>0.0f～1.0fまでの乱数</returns>
	static float Normal();
	 /// <summary>
	 /// pの確率でtrueを返す
	 /// </summary>
	 /// <param name="p">trueを返す確率(0.0f ～ 1.0f)</param>
	 /// <returns>true : false</returns>
	static bool Bool(float p);
	 /// <summary>
	 /// 重みを考慮したインデックスを返す
	 /// </summary>
	 /// <param name="weight">重み</param>
	 /// <returns>インデックス</returns>
	static size_t Weight(const std::vector<size_t>& weight);
};
