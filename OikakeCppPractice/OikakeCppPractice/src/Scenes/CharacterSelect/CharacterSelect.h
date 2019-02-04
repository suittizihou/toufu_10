#pragma once


#include "Scenes/Base/IScene.h"
#include"World/IWorld.h"
#include"World/WorldPtr.h"
#include"Utility/Assets.h"

class Renderer;
enum class EventMessage;

/*! @class GameMainScene
*   @brief  �Q�[�����C���V�[��
*/
class CharacterSelect : public IScene
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param world ���[���h�|�C���^
	*/
	explicit CharacterSelect(WorldPtr& world);
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~CharacterSelect();
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

private:
	bool UpButton(bool p1select);
	bool DownButton(bool p1select);
	bool LeftButton(bool p1select);
	bool RightButton(bool p1select);
	bool AButton(bool p1select);

private:
	//!���[���h�|�C���^
	WorldPtr world;
	//!�`��N���X
	Renderer& renderer;
	//!�V�[�����I������������p
	bool isEnd;

	bool x = true;
	bool y = true;
	Assets::Texture tex_enum;
	Assets::Texture tex_enum_p1;
	Assets::Texture tex_enum_p2;

	bool awd = true;
	int time = 0;
	int a = 0;
};
