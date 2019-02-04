#pragma once

#include<memory>
class ShapeBase;

/**
 * @file ShapePtr.h
 * @brief あたり判定のポインタ定義ヘッダー
 * @author 阿曽
 * @date Unknown
 */

//!あたり判定のポインタ
using ShapePtr = std::shared_ptr<ShapeBase>;