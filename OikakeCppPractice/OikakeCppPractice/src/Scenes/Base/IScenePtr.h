#pragma once

/**
 * @file IScenePtr.h
 * @brief IScene�̃|�C���^��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

#include <memory>

class IScene;

//! �Ē�`
using IScenePtr = std::shared_ptr<IScene>;
