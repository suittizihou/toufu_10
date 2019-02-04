#include "ResultManager.h"

int ResultManager::value = 0;

ResultManager::~ResultManager()
{
}

void ResultManager::SetSelect(int select) {
	value = select;
}

int ResultManager::GetSelect() {
	return value;
}