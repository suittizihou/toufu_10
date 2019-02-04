#pragma once

/**
 * @file SceneManager.h
 * @brief シーン管理クラス定義ファイル
 * @author 阿曽
 * @date Unknown
 */

#include "IScenePtr.h"
#include "..\FadeManager\FadeManager.h"

#include <unordered_map>
enum class Scene;

/*! @class SceneManager
*   @brief  シーン管理クラス
*/
class SceneManager {
public:
	/**
	 * @brief コンストラクタ
	 */
	SceneManager();
	/**
	* @brief デストラクタ
	*/
	~SceneManager();	
	/**
	* @brief 初期化
	*/
	void Initialize();
	/**
	* @brief 更新
	* @param deltaTime １秒
	*/
	void Update(float deltaTime);
	/**
	* @brief 描画
	*/
	void Draw() const;
	/**
	* @brief 終了
	*/
	void Finalize();
	/**
	 * @brief シーンを追加する
	 * @param name 定義したシーン
	 * @param scene シーンのポインタ
	 */
	void Add(Scene name, const IScenePtr& scene);	
	/**
	 * @brief シーンを変える
	 * @param name 定義したシーン
	 */
	void Change(Scene name);

private:
	// シーン変更するか確認
	void UpdateSceneChange();

private:
	//!コピー禁止
	SceneManager(const SceneManager& other) = delete;
	//!コピー禁止
	SceneManager& operator = (const SceneManager& other) = delete;
private:	
	//!シーンを管理するコンテナ
	std::unordered_map<Scene, IScenePtr> scenes;
	//!今現在のシーンのポインタ
	IScenePtr currentScene;
	FadeManager fadeManager;
};
