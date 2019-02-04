#pragma once
/**
* @file Window.h
* @brief ウィンドウについてまとめたクラス
* @author 阿曽
* @date 2018/3/5
*/

/*! @class Window
* @brief ウィンドウについてまとめたクラス
*/
class Window {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Window();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Window();
public:
	//!ウィンドウの横幅
	static int width;
	//!ウィンドウの縦幅
	static int height;
};