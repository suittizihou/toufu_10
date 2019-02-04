#pragma once

/**
 * @file WorldPtr.h
 * @brief ワールドクラスのポインタの定義ファイル
 * @author 阿曽
 * @date 2015/9/12
 */

#include<memory>
class World;

//! 再定義
using WorldPtr = std::shared_ptr<World>;