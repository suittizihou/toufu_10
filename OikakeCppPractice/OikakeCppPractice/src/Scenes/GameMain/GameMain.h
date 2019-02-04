#pragma once

/**
 * @file GameMainScene.h
 * @brief �Q�[�����C���V�[����`�t�@�C��
 * @author ���]
 * @date 2017/3/23
*/


#include "Scenes/Base/IScene.h"
#include"World/IWorld.h"
#include"World/WorldPtr.h"

#include "Actor/Map/MapGenerater/MapGenerater.h"

class Renderer;
enum class EventMessage;

/*! @class GameMainScene
 *   @brief  �Q�[�����C���V�[��
 */
class GameMain : public IScene {
public:
	/**
	* @brief �R���X�g���N�^
	* @param world ���[���h�|�C���^
	*/
	explicit GameMain(WorldPtr& world);
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~GameMain();
	/**
	* @brief �A�Z�b�g��ǂݍ���
	*/
	virtual void LoadAssets() override;
	/**
	* @brief ������
	*/
	virtual void Initialize() override;

	virtual void FirstUpdate(float deltaTime) override;
	
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

	// ������ǉ�����֐�
	void AddToufu();

private:
	//!���[���h�|�C���^
	WorldPtr world;
	//// �n�ʃN���X
	MapGenerater mapGenerater;
	//!�`��N���X
	Renderer& renderer;
	//!�V�[�����I������������p
	bool isEnd;

	int objNumber = 0;

	int RandomJudge(int value1, int value2);

	int random_toufu_time{};
	int toufu_spone_limit{ 300 };
};
