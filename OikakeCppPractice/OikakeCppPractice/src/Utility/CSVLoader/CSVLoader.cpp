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
	assert(!"ファイルが開けませんでした。");
	return false;
}

void CSVLoader::LoadRaw(std::ifstream & file)
{
	//!ファイルの末端
	static const std::string EndOfFile = "FOE";
	//!空白
	static const std::string Space = "\r";
	//!改行
	static const std::string LineBreak = "\n";

	std::string line;
	//!1行ずつ読み込む
	while (std::getline(file, line))
	{
		std::stringstream stream(line);
		//!１行入れる配列を用意
		StringVector row;
		std::string value = "";
		//!読み込んだ１行の１文字ずつ取得
		while (std::getline(stream, value, ',')) {
			//!ファイルの末端なら終了
			if (value == EndOfFile)return;
			//!空白、改行、「""」ならもう一度やり直す
			if (value == "" || value == Space || value == LineBreak) continue;
			//!１文字ずつ格納
			row.emplace_back(value);
		}
		//!１行ずつ格納
		data.emplace_back(row);
	}
}