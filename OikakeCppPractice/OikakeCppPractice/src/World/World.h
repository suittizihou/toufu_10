#pragma once

/**
 * @file World.h
 * @brief �A�N�^�[�����L����N���X
 * @author ���]
 * @date 2015/9/12
 */

#include "IWorld.h"
#include "Actor/Base/ActorManager.h"
#include"SceneShareValue/SceneShareValue.h"

class Renderer;

/*! @class World
*   @brief  �A�N�^�[�����L����N���X
*/
class World : public IWorld {
public:
	/// <summary>
	 /// �R���X�g���N�^<see cref="World"/>
	 /// </summary>
	World();	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~World();	
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();	

	void FirstUpdate(float deltaTime);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="deltaTime">1�b</param>
	void Update(float deltaTime);	
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="renderer">�`��N���X</param>
	void Draw(Renderer& renderer);	
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();	
	/// <summary>
	/// �o�^�����A�N�^�[��S�폜
	/// </summary>
	void Clear();
	/// <summary>
	/// �O�ɃA�N�^�[��ǉ�����
	/// </summary>
	/// <param name="group">�ǉ�����O���[�v</param>
	/// <param name="actor">�ǉ�����A�N�^�[�|�C���^</param>
	virtual void AddActor_Front(ActorGroup group, const ActorPtr& actor) override;
	/// <summary>
	/// ���ɃA�N�^�[��ǉ�����
	/// </summary>
	/// <param name="group">�ǉ�����O���[�v</param>
	/// <param name="actor">�ǉ�����A�N�^�[�|�C���^</param>
	virtual void AddActor_Back(ActorGroup group, const ActorPtr& actor) override;
	/// <summary>
	/// �A�N�^�[����������
	/// </summary>
	/// <param name="name">��������A�N�^�[�̖��O</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(const std::string& name) override;
	/// <summary>
	/// �A�N�^�[����������
	/// </summary>
	/// <param name="group">��������A�N�^�[�̃O���[�v</param>
	/// <param name="name">��������A�N�^�[�̖��O</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(ActorGroup group, const std::string& name) override;
	/// <summary>
	/// �O���[�v�̐e�̃|�C���^���擾����
	/// </summary>
	/// <param name="group">�A�N�^�[�̃O���[�v</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr GetRoot(ActorGroup group) override;
	/// <summary>
	/// �S�A�N�^�[�ɃC�x���g���b�Z�[�W�𑗐M
	/// </summary>
	/// <param name="message">�o�^�����C�x���g���b�Z�[�W</param>
	/// <param name="param">�C�x���g�ƈꏏ�ɑ���ϐ�</param>
	virtual void SendEventMessage(EventMessage message, void* param = nullptr) override;

	/// <summary>
	/// �V�[���Ԃŋ��L����ϐ����擾
	/// </summary>
	/// <returns>�V�[���Ԃŋ��L����ϐ�</returns>
	virtual SceneShareValue& GetSceneShareValue() override;


	/// <summary>
	 /// EventMessage���󂯎��֐���o�^ ��ɃA�N�^�[�ȊO���o�^����
	 /// </summary>
	 /// <param name="listener">EventMessage���󂯎��֐�</param>
	void AddEventMessageListener(std::function<void(EventMessage, void*)> listener);
private:
	//!�A�N�^�[�Ǘ��N���X
	ActorManager actorManager;
	//!���X�i�[�p�̊֐�
	std::function<void(EventMessage, void*)> listener;
	//!�V�[���Ԃŋ��L����ϐ�
	SceneShareValue sceneShareValue;
};
