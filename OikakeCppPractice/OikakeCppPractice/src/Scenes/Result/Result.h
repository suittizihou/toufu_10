#pragma once

#include "Scenes/Base/IScene.h"
#include"World/IWorld.h"
#include"World/WorldPtr.h"
#include "Actor/UI/ResultMenu/ResultMenu.h"
#include "Actor/UI/ResultCharacter/ResultCharacter.h"
#include "../FadeManager/FadeManager.h"

#include "ResultManager.h"

class Renderer;
enum class EventMessage;

/*! @class GameMainScene
*   @brief  �Q�[�����C���V�[��
*/
class Result : public IScene {
public:
	/**
	* @brief �R���X�g���N�^
	* @param world ���[���h�|�C���^
	*/
	explicit Result(WorldPtr& world);
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Result();
	/**
	* @brief �A�Z�b�g��ǂݍ���
	*/
	virtual void LoadAssets() override;
	/**
	* @brief ������
	*/
	virtual void Initialize() override;

	virtual void FirstUpdate(float deltaTime);

	/**
	* @brief �X�V
	* @param deltaTime �P�b
	*/
	virtual void Update(float deltaTime)override;
	/**
	* @brief �`��
	*/
	virtual void Draw() const override;
	/**
	* @brief �V�[�����I��������
	* @return [true �I��] : [false �܂��I�����Ă��Ȃ�]
	*/
	virtual bool IsEnd() const override;
	/**
	* @brief ���Ɉړ�����V�[�����擾
	* @return ���Ɉړ�����V�[��
	*/
	virtual Scene Next()const override;
	/**
	* @brief �I��
	*/
	virtual void Finalize() override;

private:
	/**
	* @brief �C�x���g���b�Z�[�W���󂯎��
	* @param message �o�^�����C�x���g���b�Z�[�W
	* @param param �C�x���g�ƈꏏ�ɑ���ϐ�
	*/
	void HandleMessage(EventMessage message, void* param);

private:
	//!���[���h�|�C���^
	WorldPtr world;
	//!�`��N���X
	Renderer& renderer;
	// ���U���g�}�l�[�W���[
	//ResultManager resultManager;
	// �t�F�[�h�A�E�g�����邽�߂�
	FadeManager fadeManager;
	//!�V�[�����I������������p
	bool isEnd{};
	// �Q�[���I���̃t�F�[�h�����邽�߂�
	bool checkGameEnd{};
	// ���ݑI�΂�Ă��郁�j���[�̔ԍ�������悤
	int select{};

	//BGM�悤�T�E���h�n���h��
	int bgmSh{};
};
