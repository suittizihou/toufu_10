#pragma once
/**
 * @file Timer.h
 * @brief �b�����J�E���g����N���X�̒�`�t�@�C��
 * @author ���]
 * @date 2017/1/23
 */

#include<functional>

 /*! @class Timer
 *   @brief  �ݒ肵���b�����J�E���g�_�E������N���X
 */
class Timer {
public:	
	 /// <summary>
	 ///  �R���X�g���N�^<see cref="Timer"/> 
	 /// </summary>
	 /// <param name="setTime">�ݒ肷��b���@1.0f = 1�b</param>
	 /// <param name="func">���ԂɂȂ�������s����֐�</param>
	explicit Timer(float setTime, std::function<void(void)> func = []() {});
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Timer();	
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();	
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="deltaTime">�P�b</param>
	void Update(float deltaTime);
	 /// <summary>
	 /// 0�b�ɂȂ���������
	 /// </summary>
	 /// <returns>
	 /// [true 0�b] : [false �܂�0�b�ł͂Ȃ�]
	 /// </returns>
	bool IsTimeUp() const;
	 /// <summary>
	 /// �v�����̕b�����擾
	 /// </summary>
	 /// <returns>�b��</returns>
	float GetSecond() const;	
	 /// <summary>
	 /// �ݒ肵���b�����擾
	 /// </summary>
	 /// <returns>�ݒ肵���b��</returns>
	float GetMaxTime() const;
private:	
	//!�ݒ肵���b��
	const float maxTime;
	//!�J�E���g�_�E���p�̕ϐ�
	float timer;
	//!���ԂɂȂ�������s�������֐�
	std::function<void(void)> func;
};