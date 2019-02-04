#pragma once

/**
 * @file IScenePtr.h
 * @brief ISceneのポインタ定義ファイル
 * @author 阿曽
 * @date Unknown
 */

#include <memory>

class IScene;

//! 再定義
using IScenePtr = std::shared_ptr<IScene>;
