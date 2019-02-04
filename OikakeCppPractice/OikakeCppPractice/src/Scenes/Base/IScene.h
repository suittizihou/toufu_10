#pragma once

/**
 * @file IScene.h
 * @brief シーンのインターフェース定義ファイル
 * @author 阿曽
 * @date Unknown
 */

enum class Scene;

/*! @class IScene
*   @brief  シーンのインターフェース
*/
class IScene {
public:	
	/**
	 * @brief 仮想デストラクタ
	 */
	virtual ~IScene() {}	
	/**
	* @brief アセットを読み込む
	*/
	virtual void LoadAssets() = 0;
	/**
	* @brief 初期化
	*/
	virtual void Initialize() = 0;
	/**
	* @brief 最初に処理したいもの(更新処理)
	* @param deltaTime １秒
	*/
	virtual void FirstUpdate(float deltaTime) = 0;
	/**
	* @brief 更新	
	* @param deltaTime １秒
	*/
	virtual void Update(float deltaTime) = 0;
	/**
	* @brief 描画
	*/
	virtual void Draw() const = 0;
	/**
	 * @brief シーンが終了か判定
	 * @return [true 終了] : [false まだ終了していない]
	 */
	virtual bool IsEnd() const = 0;
	/**
	* @brief 次に移動するシーンを取得
	* @return 次に移動するシーン
	*/
	virtual Scene Next() const = 0;
	/**
	* @brief 終了
	*/
	virtual void Finalize() = 0;
};
