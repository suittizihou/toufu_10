#pragma once

#include"Utility/CSVLoader/CSVLoader.h"
#include<unordered_map>
#include<sstream>
#include<string>

/**
 * @file LoadData.h
 * @brief ゲームで使う変数の初期値ファイルを読み込むクラス定義ファイル
 * @author 阿曽
 * @date 2017/4/1
 */

 /*! @class LoadData
 *   @brief  ゲームで使う変数の初期値ファイルを読み込むクラス
 */
class LoadData {

private:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LoadData();	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~LoadData();


public:	
	/// <summary>
	/// クラスの参照を取得
	/// </summary>
	/// <returns>このクラスの参照</returns>
	static LoadData& GetInstance();
	/// <summary>
	/// ファイルを読み込む
	/// </summary>
	void Load();
	/// <summary>
	/// ファイルに値を書き込む
	/// </summary>
	void WriteDataToFile();
	/// <summary>
	/// オプションの設定ファイルの情報を取得
	/// </summary>
	/// <param name="key">オプションの項目名</param>
	/// <returns>項目に応じた値</returns>
	float GetData_Option(const std::string& key) const;
	/// <summary>
	/// オプションの設定ファイルに情報を書き込む
	/// </summary>
	/// <param name="key">オプションの項目名</param>
	/// <param name="value">値</param>
	void WriteData_Option(const std::string& key, float value);
	/// <summary>
	/// オプションの説明を取得
	/// </summary>
	/// <param name="key">オプション説明の項目名</param>
	/// <returns>オプションの説明文</returns>
	std::vector<std::string> GetData_Option_Description(int index) const;

private:
	//!オプションのデータを格納するコンテナ
	std::unordered_map<std::string, float> container_option;
	//!オプションの説明文を格納するコンテナ
	std::vector<std::vector<std::string>> container_option_description;
};

