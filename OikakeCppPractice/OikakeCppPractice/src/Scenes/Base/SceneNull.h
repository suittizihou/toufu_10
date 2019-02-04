#pragma once

/**
 * @file SceneNull.h
 * @brief �k���|�C���^�ŃG���[��f�����Ȃ��悤�ɂ���f�t�H���g�V�[���̒�`�t�@�C��
 * @author ���]
 * @date Unknown
 */

#include "IScene.h"

 /*! @class SceneNull
 *   @brief  �k���|�C���^�ŃG���[��f�����Ȃ��悤�ɂ���f�t�H���g�V�[��
 */
class SceneNull : public IScene {
public:
	virtual void LoadAssets() override;
	virtual void Initialize() override;
	virtual void FirstUpdate(float deltaTime);
	virtual void Update(float deltaTime)override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void Finalize() override;
};
