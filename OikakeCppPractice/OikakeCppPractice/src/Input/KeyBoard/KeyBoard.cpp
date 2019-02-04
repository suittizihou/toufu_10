#include "KeyBoard.h"

KeyBoard::KeyBoard()
{
	//�L�[�������ꂽ���ǂ������i�[����z���������
	//������Ă��Ȃ��@�j���[�g����
	static const int NotPushed = 0;
	curKeys.fill(NotPushed);
	preKeys.fill(NotPushed);
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	//�X�V����O�Ɂ@�P�t���[���O�̏�Ԃ�ۑ�
	preKeys.swap(curKeys);
	//���݂̃L�[�����X�V
	GetHitKeyStateAll(curKeys.data());
}

bool KeyBoard::IsUp(int key) const
{
	return (!curKeys[key] && preKeys[key]);
}

bool KeyBoard::IsDown(int key) const
{
	return (curKeys[key] && !preKeys[key]);
}

bool KeyBoard::IsState(int key) const
{
	static const int HoldPushKey = 1;
	return curKeys[key] == HoldPushKey;
}

bool KeyBoard::IsAnyKeyDown() const
{
	for (int i = 0; i < Max_Key_Num; i++) {
		if (IsDown(i)) return true;
	}
	return false;
}
