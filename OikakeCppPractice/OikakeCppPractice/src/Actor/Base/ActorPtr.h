#pragma once

#include <memory>

class ActorBase;

/************************************************************
* File Name	: ActorPtr.h
* Description	: アクターのShared_ptr作成クラス
*																Date		:	2015-09-12.
*															  Author	:	阿曽
*************************************************************/
using ActorPtr = std::shared_ptr < ActorBase >;