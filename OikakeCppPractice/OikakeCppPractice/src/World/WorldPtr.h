#pragma once

/**
 * @file WorldPtr.h
 * @brief ���[���h�N���X�̃|�C���^�̒�`�t�@�C��
 * @author ���]
 * @date 2015/9/12
 */

#include<memory>
class World;

//! �Ē�`
using WorldPtr = std::shared_ptr<World>;