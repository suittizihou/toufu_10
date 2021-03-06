#pragma once

/**
 * @file CheckMemoryLeak.h
 * @brief メモリリークしているかチェックするクラスの定義ファイル
 * @author 阿曽
 * @date Unknown
 */

#include<crtdbg.h>

 /*! @class CheckMemoryLeak
 *   @brief  メモリリークしているかチェックするクラスの定義
 */
class CheckMemoryLeak {
public:
	 /// <summary>
	 /// コンストラクタ<see cref="CheckMemoryLeak"/>
	 /// </summary>
	CheckMemoryLeak() {
		//!メモリリークを出力ウィンドウに表示する関数
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_MODE_FILE);
	}
	/**
	* @brief number回目のメモリ確保時にブレイクするよう設定
	* @param number number回目のメモリ確保時
	* @detail
	* メモリリークしたとき、出力ウィンドウに
	* 
	* 	Detected memory leaks!
	* 	Dumping objects ->
	*   {52992} normal block at 0x000000001E27F290, 72 bytes long.
	* 	Data:                  01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	* 	Object dump complete.
	* 
	* 	みたいな文章が出てくる。
	* 
	* 	52992回目に確保した72バイトのメモリがリークしたという意味。
	* 	毎回52992回目でリークする場合は、そこでブレイクすることで、
	* 	原因がわかるかもしれない。
	* 
	* 	_CrtSetBreakAlloc(52992);
	* 
	* ↑の関数は52992回目のメモリ確保時にブレイクするという関数
	*/	
	void SetBreakPoint(int number) {
		_CrtSetBreakAlloc(number);
	}
};

