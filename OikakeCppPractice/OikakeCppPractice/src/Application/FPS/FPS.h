#pragma once

#include"Utility/Color/Color.h"

/**
 * @file FPS.h
 * @brief �Q�[����FPS���Ǘ�����N���X��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

 /*! @class FPS
 *   @brief �Q�[����FPS���Ǘ�����N���X
 *   @detail (�Q�l�@http://dixq.net/g/03_14.html)
 */
class FPS {
public:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FPS();	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FPS();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	
	/// <summary>
	/// �f�o�b�O�p��FPS�\��
	/// </summary>
	/// <param name="color">�F</param>
	void Draw(const Color& color = Color::White);
	/// <summary>
	/// ���̃t���[��(0.0�@�`�@60.0)���擾
	/// </summary>
	/// <returns>���̃t���[��</returns>
	float GetdeltaTime();
	/// <summary>
	/// �ݒ肵��FPS�𒴂�����ҋ@����
	/// </summary>
	void Wait();

public:
	//!�Q�[����FPS
	static const float fps;

private:
	//!���ς����T���v����
	const int AverageCount;
	//!fps
	float deltaTime;
	//!�J�E���^
	int counter;
	//!����J�n����
	int startTime;
};