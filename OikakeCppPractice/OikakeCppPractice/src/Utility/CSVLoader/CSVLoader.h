#pragma once

/**
 * @file CSVLoader.h
 * @brief CSVファイルを読み込むクラスの定義ファイル
 * @author 阿曽
 * @date 2016/3/8
 */

#include<string>
#include<vector>

/*
*	 R o w →　行
C[][][]
o[][][]
l[][][]
u[]
m
n
↓
列
*/

//!1行
using StringVector = std::vector < std::string >;
//!ファイルのすべての列
using CSVData = std::vector < StringVector >;


/*! @class CSVLoader
*   @brief CSVファイル読み込みクラス
*/
class CSVLoader {
public:
	 /// <summary>
	 /// コンストラクタ<see cref="CSVLoader"/>
	 /// </summary>
	 /// <param name="fileName">CSVファイルの名前</param>
	explicit CSVLoader(const std::string& fileName);
	 /// <summary>
	 /// デストラクタ
	 /// </summary>
	~CSVLoader();
	/// <summary>
	/// 全ての列を取得
	/// </summary>
	/// <returns>読み込んだ全ての列　2次元配列　</returns>
	CSVData GetAllData() const;
	/// <summary>
	/// 指定した行のセルの数を取得 　横にいくつ要素があるのか調べる
	/// </summary>
	/// <param name="rowIndex">何行目</param>
	/// <returns>指定した行のセルの数</returns>
	int GetNumOfRow(int rowIndex = 0) const;
	 /// <summary>
	 /// 0番目の列のセルの数を取得　縦にいくつ要素があるのか調べる
	 /// </summary>
	 /// <returns>0番目の列のセルの数</returns>
	int GetNumOfColumn() const;
	 /// <summary>
	 /// 指定した行・列のセルのデータを取得　string版
	 /// </summary>
	 /// <param name="rowIndex">行番号</param>
	 /// <param name="columnIndex">列番号</param>
	 /// <returns>指定した行・列のセルのデータ</returns>
	std::string GetDataString(int rowIndex, int columnIndex) const;
	/// <summary>
	/// 指定した行・列のセルのデータを取得  int版
	/// </summary>
	/// <param name="rowIndex">行番号</param>
	/// <param name="columnIndex">列番号</param>
	/// <returns>指定した行・列のセルのデータ</returns>
	int GetDataInt(int rowIndex, int columnIndex) const;
	/// <summary>
	/// 指定した行・列のセルのデータを取得　float版
	/// </summary>
	/// <param name="rowIndex">行番号</param>
	/// <param name="columnIndex">列番号</param>
	/// <returns>指定した行・列のセルのデータ</returns>
	float GetDataFloat(int rowIndex, int columnIndex) const;

	/// <summary>
	/// CSVファイルを読み込む
	/// </summary>
	/// <param name="fileName">CSVファイルの名前</param>
	void Load(const std::string& fileName);


private:
	/// <summary>
	/// ファイルが正常に読み込めたか判定
	/// </summary>
	/// <param name="file">std::ifstream</param>
	/// <param name="fileName">読み込むファイル</param>
	/// <returns>
	/// [true 正常に読み込めた] : [false　異常が発生した]
	/// </returns>
	bool IsReadFile(std::ifstream& file, const std::string& fileName);
	 /// <summary>
	 /// CSVファイルを1行ずつ読み込む
	 /// </summary>
	 /// <param name="file">std::ifstream</param>
	void LoadRaw(std::ifstream& file);
private:
	//!読み込んだCSVデータが入っている2次元配列
	CSVData data;
public:
	//!読み込み開始位置
	static const int LoadableRaw = 1;
};
