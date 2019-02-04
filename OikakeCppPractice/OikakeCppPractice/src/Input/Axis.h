#pragma once

/**
 * @file Axis.h
 * @brief 入力の縦軸・横軸定義ヘッダー
 * @author 阿曽
 * @date Unknown
 */

/**
 * @enum Axis
 * 入力の縦軸・横軸 参考：Unity
 */
enum class Axis {
	//!WSキー, LStickの上下
	Vertical,
	//!ADキー, LStickの左右
	Horizontal,
	//!上下キー, RStickの上下
	Vertical2,
	//!左右キー, RStickの左右
	Horizontal2,
	//!最大定義数
	Max_Of_Num
};
