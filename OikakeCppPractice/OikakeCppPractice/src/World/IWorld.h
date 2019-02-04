#pragma once

/**
 * @file IWorld.h
 * @brief �A�N�^�[�����L����C���^�[�t�F�[�X�N���X
 * @author ���]
 * @date 2015/09/12
 */

#include "Actor/Base/ActorPtr.h"
#include<string>

enum class ActorGroup;
enum class EventMessage;
struct SceneShareValue;

/*! @class IWorld
*	@brief  �A�N�^�[�����L����C���^�[�t�F�[�X�N���X
*/
class IWorld {
public:		
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IWorld() {}
	/// <summary>
	/// �O�ɃA�N�^�[��ǉ�����
	/// </summary>
	/// <param name="group">�ǉ�����O���[�v</param>
	/// <param name="actor">�ǉ�����A�N�^�[�|�C���^</param>
	virtual void AddActor_Front(ActorGroup group, const ActorPtr& actor) = 0;
	/// <summary>
	/// ���ɃA�N�^�[��ǉ�����
	/// </summary>
	/// <param name="group">�ǉ�����O���[�v</param>
	/// <param name="actor">�ǉ�����A�N�^�[�|�C���^</param>
	virtual void AddActor_Back(ActorGroup group, const ActorPtr& actor) = 0;
	/// <summary>
	/// �A�N�^�[����������
	/// </summary>
	/// <param name="name">��������A�N�^�[�̖��O</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(const std::string& name) = 0;
	/// <summary>
	/// �A�N�^�[����������
	/// </summary>
	/// <param name="group">��������A�N�^�[�̃O���[�v</param>
	/// <param name="name">��������A�N�^�[�̖��O</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(ActorGroup group, const std::string& name) = 0;
	/// <summary>
	/// �O���[�v�̐e�̃|�C���^���擾����
	/// </summary>
	/// <param name="group">�A�N�^�[�̃O���[�v</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr GetRoot(ActorGroup group) = 0;
	/// <summary>
	/// �S�A�N�^�[�ɃC�x���g���b�Z�[�W�𑗐M
	/// </summary>
	/// <param name="message">�o�^�����C�x���g���b�Z�[�W</param>
	/// <param name="param">�C�x���g�ƈꏏ�ɑ���ϐ�</param>
	virtual void SendEventMessage(EventMessage message, void* param = nullptr) = 0;
	/// <summary>
	/// �V�[���Ԃŋ��L����ϐ����擾
	/// </summary>
	/// <returns>�V�[���Ԃŋ��L����ϐ�</returns>
	virtual SceneShareValue& GetSceneShareValue() = 0;
};
