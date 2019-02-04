#pragma once

/**
 * @file IScene.h
 * @brief �V�[���̃C���^�[�t�F�[�X��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

enum class Scene;

/*! @class IScene
*   @brief  �V�[���̃C���^�[�t�F�[�X
*/
class IScene {
public:	
	/**
	 * @brief ���z�f�X�g���N�^
	 */
	virtual ~IScene() {}	
	/**
	* @brief �A�Z�b�g��ǂݍ���
	*/
	virtual void LoadAssets() = 0;
	/**
	* @brief ������
	*/
	virtual void Initialize() = 0;
	/**
	* @brief �ŏ��ɏ�������������(�X�V����)
	* @param deltaTime �P�b
	*/
	virtual void FirstUpdate(float deltaTime) = 0;
	/**
	* @brief �X�V	
	* @param deltaTime �P�b
	*/
	virtual void Update(float deltaTime) = 0;
	/**
	* @brief �`��
	*/
	virtual void Draw() const = 0;
	/**
	 * @brief �V�[�����I��������
	 * @return [true �I��] : [false �܂��I�����Ă��Ȃ�]
	 */
	virtual bool IsEnd() const = 0;
	/**
	* @brief ���Ɉړ�����V�[�����擾
	* @return ���Ɉړ�����V�[��
	*/
	virtual Scene Next() const = 0;
	/**
	* @brief �I��
	*/
	virtual void Finalize() = 0;
};
