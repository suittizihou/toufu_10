#include "LoadData.h"
#include"Utility/Utility.h"

LoadData::LoadData()
	: container_option()
	, container_option_description()
{
}

LoadData::~LoadData()
{
	container_option.clear();
	container_option_description.clear();
}

void LoadData::Load()
{

}

void LoadData::WriteDataToFile()
{
}

float LoadData::GetData_Option(const std::string & key) const
{
	return container_option.at(key);
}

void LoadData::WriteData_Option(const std::string & key, float value)
{
	container_option.at(key) = value;
}

std::vector<std::string> LoadData::GetData_Option_Description(int index) const
{
	return container_option_description.at(index);
}


LoadData & LoadData::GetInstance()
{
	static LoadData instance;
	return instance;
}
