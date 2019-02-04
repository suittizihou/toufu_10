#pragma once

class ResultManager {
public:
	ResultManager() = default;
	~ResultManager();

	// 入れ物に入れる
	static void SetSelect(int select);

	// 選ばれているメニューの番号を返す
	static int GetSelect();

private:
	// 選ばれているメニューの入れ物
	static int value;
};