
#pragma once

/************************************************************
* File Name	: Status.h
* Description	: アクター状態クラス
*																Date		:	2015-09-12.
*															  Author	:	阿曽
*************************************************************/
enum class Status {
	//更新・描画を行う
	Active,
	//更新のみ
	UpdateOnly,
	//描画のみ
	DrawOnly,
	//削除はしないが、更新と描画はしない
	Rest,
	//削除する
	Dead,
};