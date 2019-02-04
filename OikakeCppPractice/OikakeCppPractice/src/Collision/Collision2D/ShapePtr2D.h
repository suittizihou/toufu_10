#pragma once

#include<memory>
class ShapeBase2D;

/**
* @file ShapePtr2D.h
* @brief 2D基底あたり判定のポインタ定義ヘッダー
* @author 阿曽
* @date Unknown
*/

//!あたり判定のポインタ
using ShapePtr2D = std::shared_ptr<ShapeBase2D>;