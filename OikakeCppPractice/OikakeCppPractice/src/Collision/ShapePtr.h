#pragma once

#include<memory>
class ShapeBase;

/**
 * @file ShapePtr.h
 * @brief �����蔻��̃|�C���^��`�w�b�_�[
 * @author ���]
 * @date Unknown
 */

//!�����蔻��̃|�C���^
using ShapePtr = std::shared_ptr<ShapeBase>;