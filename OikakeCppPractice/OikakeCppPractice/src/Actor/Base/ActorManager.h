#pragma once

#include "ActorPtr.h"
#include "ActorBase.h"
#include <unordered_map>
#include <functional>

enum class ActorGroup;
class Renderer;

/************************************************************
* File Name	: ActorManager.h
* Description	: �A�N�^�[�Ǘ��N���X
*																Date		:	2015-09-12.
*															  Author	:	���]
*************************************************************/
class ActorManager {
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ActorManager();

	/// <summary>
	/// �������@
	/// </summary>
	void Initialize();

	void FirstUpdate(float deltaTime);

	/// <summary>
	/// �X�V�@
	/// </summary>
	void Update(float deltaTime);

	/// <summary>
	/// �`��
	/// �@</summary>
	void Draw(Renderer& renderer);

	/// <summary>
	/// �I���@
	/// </summary>
	void Finalize();

	/// <summary>
	/// �O�ɒǉ�
	/// </summary>
	/// <param name="group">�o�^����A�N�^�[�O���[�v</param>
	/// <param name="actor">�o�^����A�N�^�[</param>
	void AddActor_Front(ActorGroup group, const ActorPtr& actor);
	/// <summary>
	/// ���ɒǉ�
	/// </summary>
	/// <param name="group">�o�^����A�N�^�[�O���[�v</param>
	/// <param name="actor">�o�^����A�N�^�[</param>
	void AddActor_Back(ActorGroup group, const ActorPtr& actor);

	/// <summary>
	/// �A�N�^�[�O���[�v��ǉ�����
	/// </summary>
	/// <param name="group">�ǉ�����A�N�^�[�O���[�v</param>
	/// <param name="name">�A�N�^�[�O���[�v�̑�{�̃A�N�^�[�̖��O</param>
	/// <param name="actor">�A�N�^�[�O���[�v�̑�{�̃A�N�^�[</param>
	void AddGroup(ActorGroup group, const std::string& name = "none", const ActorPtr& actor = nullptr);

	/// <summary>
	/// �S�A�N�^�[�Ƀ��b�Z�[�W�𑗐M
	/// </summary>
	/// <param name="message">���b�Z�[�W�̎��</param>
	/// <param name="param">���b�Z�[�W�ƈꏏ�ɑ���ϐ�</param>
	void HandleMessage(EventMessage message, void* param);
	/// <summary>
	/// �S�A�N�^�[���疼�O�őΏۂ̃A�N�^�[��T��
	/// </summary>
	/// <param name="name">�A�N�^�[�̖��O</param>
	/// <returns>�ŏ��ɖ��O�ƈ�v�����A�N�^�[�̃|�C���^</returns>
	ActorPtr FindActor(const std::string& name);
	/// <summary>
	/// �O���[�v���疼�O�őΏۂ̃A�N�^�[��T��
	/// </summary>
	/// <param name="group">�A�N�^�[�O���[�v</param>
	/// <param name="name">�A�N�^�[�̖��O</param>
	/// <returns>�ŏ��ɖ��O�ƈ�v�����A�N�^�[�̃|�C���^</returns>
	ActorPtr FindActor(ActorGroup group, const std::string& name);
	/// <summary>
	/// �O���[�v�̑�{�̃A�N�^�[���擾
	/// </summary>
	/// <param name="group">�A�N�^�[�O���[�v</param>
	/// <returns>�O���[�v�̑�{�̃A�N�^�[</returns>
	ActorPtr GetRoot(ActorGroup group);
	/// <summary>
	/// �o�^�����A�N�^�[��S���폜
	/// </summary>
	void Clear();

	void sort(ActorGroup group);

private:
	/// <summary>
	/// �O���[�v��ǉ�
	/// </summary>
	void RegisterGroup();
	/// <summary>
	/// �����蔻�������O���[�v��o�^
	/// </summary>
	void Collide();

private:
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	//�S�A�N�^�[�̑�{
	ActorBase root;
	//�O���[�v�ʂɓo�^����A�N�^�[�z��
	std::unordered_map<ActorGroup, ActorPtr> actors;

	int a = 0;
};