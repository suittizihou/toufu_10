# pragma once

/**
 * @file Ramdom.h
 * @brief �����_���֐����`����t�@�C��
 * @author �x
 * @date Unknown
 */


# include <algorithm>

# include <functional>

# include <random>

# include <iostream>


/*! @class Random
*   @brief �����_���֐����܂Ƃ߂��N���X
*/
class Random{
private:
	 /// <summary>
	 /// ���������C���X�^���X��Ԃ�
	 /// </summary>
	 /// <returns>���������C���X�^���X</returns>
	static std::mt19937& GetInstance();
public:
	 /// <summary>
	 /// [min�`max]�̗�����Ԃ��@int��
	 /// </summary>
	 /// <param name="min">��I�ŏ��l</param>
	 /// <param name="max">�r���I�ő�l</param>
	 /// <returns>[min�`max]�̗���</returns>
	static int Range(int min, int max);
	/// <summary>
	/// [min�`max]�̗�����Ԃ� float��
	/// </summary>
	/// <param name="min">��I�ŏ��l</param>
	/// <param name="max">�r���I�ő�l</param>
	/// <returns>[min�`max]�̗���</returns>
	static float Rangef(float min, float max);
	 /// <summary>
	 /// 0.0f�`1.0f�܂ł̗�����Ԃ�
	 /// </summary>
	 /// <returns>0.0f�`1.0f�܂ł̗���</returns>
	static float Normal();
	 /// <summary>
	 /// p�̊m����true��Ԃ�
	 /// </summary>
	 /// <param name="p">true��Ԃ��m��(0.0f �` 1.0f)</param>
	 /// <returns>true : false</returns>
	static bool Bool(float p);
	 /// <summary>
	 /// �d�݂��l�������C���f�b�N�X��Ԃ�
	 /// </summary>
	 /// <param name="weight">�d��</param>
	 /// <returns>�C���f�b�N�X</returns>
	static size_t Weight(const std::vector<size_t>& weight);
};
