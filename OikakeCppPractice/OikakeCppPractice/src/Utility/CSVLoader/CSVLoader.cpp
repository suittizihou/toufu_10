#include "CSVLoader.h"

#include<fstream>
#include<cassert>
#include<iostream>
#include<sstream>

CSVLoader::CSVLoader(const std::string & fileName)
	: data()
{
	Load(fileName);
}

CSVLoader::~CSVLoader()
{
	data.clear();
}

CSVData CSVLoader::GetAllData() const
{
	return data;
}

int CSVLoader::GetNumOfRow(int rowIndex) const
{
	return data.at(rowIndex).size();
}

int CSVLoader::GetNumOfColumn() const
{
	return data.size();
}

std::string CSVLoader::GetDataString(int rowIndex, int columnIndex) const {
	return data.at(columnIndex).at(rowIndex);
}

int CSVLoader::GetDataInt(int rowIndex, int columnIndex) const {
	return std::atoi(data.at(columnIndex).at(rowIndex).c_str());
}


float CSVLoader::GetDataFloat(int rowIndex, int columnIndex) const {
	return (float)std::atof(data.at(columnIndex).at(rowIndex).c_str());
}

void CSVLoader::Load(const std::string & fileName)
{
	std::ifstream file(fileName);

	if (!IsReadFile(file, fileName))
		return;

	data.clear();
	LoadRaw(file);
}

bool CSVLoader::IsReadFile(std::ifstream& file, const std::string& fileName)
{
	if (!file.fail())
		return true;

	std::cerr << "Error Read File ->" << fileName << std::endl;
	assert(!"�t�@�C�����J���܂���ł����B");
	return false;
}

void CSVLoader::LoadRaw(std::ifstream & file)
{
	//!�t�@�C���̖��[
	static const std::string EndOfFile = "FOE";
	//!��
	static const std::string Space = "\r";
	//!���s
	static const std::string LineBreak = "\n";

	std::string line;
	//!1�s���ǂݍ���
	while (std::getline(file, line))
	{
		std::stringstream stream(line);
		//!�P�s�����z���p��
		StringVector row;
		std::string value = "";
		//!�ǂݍ��񂾂P�s�̂P�������擾
		while (std::getline(stream, value, ',')) {
			//!�t�@�C���̖��[�Ȃ�I��
			if (value == EndOfFile)return;
			//!�󔒁A���s�A�u""�v�Ȃ������x��蒼��
			if (value == "" || value == Space || value == LineBreak) continue;
			//!�P�������i�[
			row.emplace_back(value);
		}
		//!�P�s���i�[
		data.emplace_back(row);
	}
}