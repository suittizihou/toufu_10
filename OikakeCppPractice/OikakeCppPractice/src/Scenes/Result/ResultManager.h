#pragma once

class ResultManager {
public:
	ResultManager() = default;
	~ResultManager();

	// ���ꕨ�ɓ����
	static void SetSelect(int select);

	// �I�΂�Ă��郁�j���[�̔ԍ���Ԃ�
	static int GetSelect();

private:
	// �I�΂�Ă��郁�j���[�̓��ꕨ
	static int value;
};