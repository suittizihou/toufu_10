#pragma once

/**
 * @file CSVLoader.h
 * @brief CSV�t�@�C����ǂݍ��ރN���X�̒�`�t�@�C��
 * @author ���]
 * @date 2016/3/8
 */

#include<string>
#include<vector>

/*
*	 R o w ���@�s
C[][][]
o[][][]
l[][][]
u[]
m
n
��
��
*/

//!1�s
using StringVector = std::vector < std::string >;
//!�t�@�C���̂��ׂĂ̗�
using CSVData = std::vector < StringVector >;


/*! @class CSVLoader
*   @brief CSV�t�@�C���ǂݍ��݃N���X
*/
class CSVLoader {
public:
	 /// <summary>
	 /// �R���X�g���N�^<see cref="CSVLoader"/>
	 /// </summary>
	 /// <param name="fileName">CSV�t�@�C���̖��O</param>
	explicit CSVLoader(const std::string& fileName);
	 /// <summary>
	 /// �f�X�g���N�^
	 /// </summary>
	~CSVLoader();
	/// <summary>
	/// �S�Ă̗���擾
	/// </summary>
	/// <returns>�ǂݍ��񂾑S�Ă̗�@2�����z��@</returns>
	CSVData GetAllData() const;
	/// <summary>
	/// �w�肵���s�̃Z���̐����擾 �@���ɂ����v�f������̂����ׂ�
	/// </summary>
	/// <param name="rowIndex">���s��</param>
	/// <returns>�w�肵���s�̃Z���̐�</returns>
	int GetNumOfRow(int rowIndex = 0) const;
	 /// <summary>
	 /// 0�Ԗڂ̗�̃Z���̐����擾�@�c�ɂ����v�f������̂����ׂ�
	 /// </summary>
	 /// <returns>0�Ԗڂ̗�̃Z���̐�</returns>
	int GetNumOfColumn() const;
	 /// <summary>
	 /// �w�肵���s�E��̃Z���̃f�[�^���擾�@string��
	 /// </summary>
	 /// <param name="rowIndex">�s�ԍ�</param>
	 /// <param name="columnIndex">��ԍ�</param>
	 /// <returns>�w�肵���s�E��̃Z���̃f�[�^</returns>
	std::string GetDataString(int rowIndex, int columnIndex) const;
	/// <summary>
	/// �w�肵���s�E��̃Z���̃f�[�^���擾  int��
	/// </summary>
	/// <param name="rowIndex">�s�ԍ�</param>
	/// <param name="columnIndex">��ԍ�</param>
	/// <returns>�w�肵���s�E��̃Z���̃f�[�^</returns>
	int GetDataInt(int rowIndex, int columnIndex) const;
	/// <summary>
	/// �w�肵���s�E��̃Z���̃f�[�^���擾�@float��
	/// </summary>
	/// <param name="rowIndex">�s�ԍ�</param>
	/// <param name="columnIndex">��ԍ�</param>
	/// <returns>�w�肵���s�E��̃Z���̃f�[�^</returns>
	float GetDataFloat(int rowIndex, int columnIndex) const;

	/// <summary>
	/// CSV�t�@�C����ǂݍ���
	/// </summary>
	/// <param name="fileName">CSV�t�@�C���̖��O</param>
	void Load(const std::string& fileName);


private:
	/// <summary>
	/// �t�@�C��������ɓǂݍ��߂�������
	/// </summary>
	/// <param name="file">std::ifstream</param>
	/// <param name="fileName">�ǂݍ��ރt�@�C��</param>
	/// <returns>
	/// [true ����ɓǂݍ��߂�] : [false�@�ُ킪��������]
	/// </returns>
	bool IsReadFile(std::ifstream& file, const std::string& fileName);
	 /// <summary>
	 /// CSV�t�@�C����1�s���ǂݍ���
	 /// </summary>
	 /// <param name="file">std::ifstream</param>
	void LoadRaw(std::ifstream& file);
private:
	//!�ǂݍ���CSV�f�[�^�������Ă���2�����z��
	CSVData data;
public:
	//!�ǂݍ��݊J�n�ʒu
	static const int LoadableRaw = 1;
};
