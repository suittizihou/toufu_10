#pragma once

#include"Utility/CSVLoader/CSVLoader.h"
#include<unordered_map>
#include<sstream>
#include<string>

/**
 * @file LoadData.h
 * @brief �Q�[���Ŏg���ϐ��̏����l�t�@�C����ǂݍ��ރN���X��`�t�@�C��
 * @author ���]
 * @date 2017/4/1
 */

 /*! @class LoadData
 *   @brief  �Q�[���Ŏg���ϐ��̏����l�t�@�C����ǂݍ��ރN���X
 */
class LoadData {

private:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	LoadData();	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LoadData();


public:	
	/// <summary>
	/// �N���X�̎Q�Ƃ��擾
	/// </summary>
	/// <returns>���̃N���X�̎Q��</returns>
	static LoadData& GetInstance();
	/// <summary>
	/// �t�@�C����ǂݍ���
	/// </summary>
	void Load();
	/// <summary>
	/// �t�@�C���ɒl����������
	/// </summary>
	void WriteDataToFile();
	/// <summary>
	/// �I�v�V�����̐ݒ�t�@�C���̏����擾
	/// </summary>
	/// <param name="key">�I�v�V�����̍��ږ�</param>
	/// <returns>���ڂɉ������l</returns>
	float GetData_Option(const std::string& key) const;
	/// <summary>
	/// �I�v�V�����̐ݒ�t�@�C���ɏ�����������
	/// </summary>
	/// <param name="key">�I�v�V�����̍��ږ�</param>
	/// <param name="value">�l</param>
	void WriteData_Option(const std::string& key, float value);
	/// <summary>
	/// �I�v�V�����̐������擾
	/// </summary>
	/// <param name="key">�I�v�V���������̍��ږ�</param>
	/// <returns>�I�v�V�����̐�����</returns>
	std::vector<std::string> GetData_Option_Description(int index) const;

private:
	//!�I�v�V�����̃f�[�^���i�[����R���e�i
	std::unordered_map<std::string, float> container_option;
	//!�I�v�V�����̐��������i�[����R���e�i
	std::vector<std::vector<std::string>> container_option_description;
};

