#pragma once

/**
* @file StickDirection.h
* @brief 入力の方向定義ヘッダー
* @author 阿曽
* @date 2017/12/8
*/

/**
* @enum StickDirection
* 入力の方向
*/
enum class StickDirection {
	//!前方向
	Forward,
	//!後方向
	Back,
	//!左方向
	Left,
	//!右方向
	Right,
	//!ヌル
	None
};
