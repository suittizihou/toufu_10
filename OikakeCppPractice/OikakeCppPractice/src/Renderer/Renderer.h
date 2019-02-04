#pragma once

/**
 * @file Renderer.h
 * @brief �`��֌W���܂Ƃ߂��N���X
 * @author ���]
 * @date 2015/12/7
 */

#include<string>
#include<unordered_map>
#include"Math/Vector2/Vector2.h"
#include"Utility/Rect/Rect.h"
#include"Utility/Color/Color.h"
#include"Utility/Assets.h"

/*! @class Renderer
 *  @brief  �`��N���X
 */
class Renderer {
private:
	/**
	 * @brief �R���X�g���N�^
	 */
	Renderer();
	/**
	* @brief �f�X�g���N�^
	*/
	~Renderer();
public:	
	/**
	 * @brief Renderer�̃|�C���^���擾
	 * @return Renderer�̃|�C���^
	 */
	static Renderer& GetInstance();
	/**
	 * @brief �e�N�X�`����ǂݍ���
	 * @param id �o�^���閼�O
	 * @param fileName �ǂݍ��ރt�@�C����
	 */
	void LoadTexture(Assets::Texture id, const std::string& fileName);	
	/**
	 * @brief �e�N�X�`������ʂɕ`��
	 * @param id �o�^�������O
	 * @param position �`�悷����W
	 * @param center �e�N�X�`���̒��S�_
	 * @param scale �e�N�X�`���̑傫��
	 * @param angle �e�N�X�`���̉�]�p�x�i�x���@�j
	 * @param color �e�N�X�`���̐F
	 */
	void DrawTexture(Assets::Texture id, const Vector2& position = Vector2(0, 0), const Vector2& center = Vector2(0, 0), const Vector2& scale = Vector2(1, 1), float angle = 0.0f, const Color& color = Color::White);
	/**
	* @brief ��`����ʂɕ`��
	* @param id �o�^�������O
	* @param position �`�悷����W
	* @param rect �؂���͈�
	* @param alpha �A���t�@�l
	*/
	void DrawRectangle(Assets::Texture id, const Vector2& position = Vector2(0, 0), const Rect& rect = Rect(0, 0, 1, 1), const Color& color = Color::White);
	/**
	* @brief �摜���g���Đ�������ʂɕ`�悷��
	* @param id �o�^�������O
	* @param position ���W
	* @param number ���l
	* @param width �����P������̉���
	* @param height �����P������̏c��
	* @param digit ����
	* @param fill �]�����������Ŗ��߂邩
	*/
	void DrawNumber(Assets::Texture id, const Vector2& position, int number, int width, int height, int digit = 0, char fill = '0');
	/**
	* @brief �e�N�X�`�����폜
	* @param id �e�N�X�`���̃n���h��
	*/
	void DeleteTexture(Assets::Texture id);
	/**
	 * @brief �S���\�[�X�̍폜
	 */
	void Clear();
private:
	//!�e�N�X�`�����Ǘ�����R���e�i
	std::unordered_map<Assets::Texture, int> textures;
};