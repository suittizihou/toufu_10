#pragma once

/**
 * @file SceneManager.h
 * @brief �V�[���Ǘ��N���X��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

#include "IScenePtr.h"
#include "..\FadeManager\FadeManager.h"

#include <unordered_map>
enum class Scene;

/*! @class SceneManager
*   @brief  �V�[���Ǘ��N���X
*/
class SceneManager {
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	SceneManager();
	/**
	* @brief �f�X�g���N�^
	*/
	~SceneManager();	
	/**
	* @brief ������
	*/
	void Initialize();
	/**
	* @brief �X�V
	* @param deltaTime �P�b
	*/
	void Update(float deltaTime);
	/**
	* @brief �`��
	*/
	void Draw() const;
	/**
	* @brief �I��
	*/
	void Finalize();
	/**
	 * @brief �V�[����ǉ�����
	 * @param name ��`�����V�[��
	 * @param scene �V�[���̃|�C���^
	 */
	void Add(Scene name, const IScenePtr& scene);	
	/**
	 * @brief �V�[����ς���
	 * @param name ��`�����V�[��
	 */
	void Change(Scene name);

private:
	// �V�[���ύX���邩�m�F
	void UpdateSceneChange();

private:
	//!�R�s�[�֎~
	SceneManager(const SceneManager& other) = delete;
	//!�R�s�[�֎~
	SceneManager& operator = (const SceneManager& other) = delete;
private:	
	//!�V�[�����Ǘ�����R���e�i
	std::unordered_map<Scene, IScenePtr> scenes;
	//!�����݂̃V�[���̃|�C���^
	IScenePtr currentScene;
	FadeManager fadeManager;
};
