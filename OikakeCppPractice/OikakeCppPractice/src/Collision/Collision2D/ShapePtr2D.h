#pragma once

#include<memory>
class ShapeBase2D;

/**
* @file ShapePtr2D.h
* @brief 2D��ꂠ���蔻��̃|�C���^��`�w�b�_�[
* @author ���]
* @date Unknown
*/

//!�����蔻��̃|�C���^
using ShapePtr2D = std::shared_ptr<ShapeBase2D>;