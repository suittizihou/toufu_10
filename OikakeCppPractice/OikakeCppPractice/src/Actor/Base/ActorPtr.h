#pragma once

#include <memory>

class ActorBase;

/************************************************************
* File Name	: ActorPtr.h
* Description	: �A�N�^�[��Shared_ptr�쐬�N���X
*																Date		:	2015-09-12.
*															  Author	:	���]
*************************************************************/
using ActorPtr = std::shared_ptr < ActorBase >;