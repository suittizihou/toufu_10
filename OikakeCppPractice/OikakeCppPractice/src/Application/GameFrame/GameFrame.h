#pragma once

#include"Application/GameApplication/GameApplication.h"

/**
 * @file GameFrame.h
 * @brief �Q�[���t���[�����[�N��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

#include"Scenes/Base/SceneManager.h"
#include"World/WorldPtr.h"

 /*! @class GameFrame
 *   @brief  �Q�[���t���[�����[�N
 */
class GameFrame : public GameApplication {
public:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameFrame();	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameFrame();

private:	
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() override;	
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="deltaTime">1�b</param>
	virtual void Update(float deltaTime) override;
	
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() override;

	virtual void Reset() override;
	
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() override;
private:
	//!�A�N�^�[�ŋ��L���郏�[���h�̃|�C���^
	WorldPtr world;
	//!�V�[���Ǘ��N���X
	SceneManager sceneManager;
};