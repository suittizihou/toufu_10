#pragma once

/**
 * @file Renderer.h
 * @brief 描画関係をまとめたクラス
 * @author 阿曽
 * @date 2015/12/7
 */

#include<string>
#include<unordered_map>
#include"Math/Vector2/Vector2.h"
#include"Utility/Rect/Rect.h"
#include"Utility/Color/Color.h"
#include"Utility/Assets.h"

/*! @class Renderer
 *  @brief  描画クラス
 */
class Renderer {
private:
	/**
	 * @brief コンストラクタ
	 */
	Renderer();
	/**
	* @brief デストラクタ
	*/
	~Renderer();
public:	
	/**
	 * @brief Rendererのポインタを取得
	 * @return Rendererのポインタ
	 */
	static Renderer& GetInstance();
	/**
	 * @brief テクスチャを読み込む
	 * @param id 登録する名前
	 * @param fileName 読み込むファイル名
	 */
	void LoadTexture(Assets::Texture id, const std::string& fileName);	
	/**
	 * @brief テクスチャを画面に描画
	 * @param id 登録した名前
	 * @param position 描画する座標
	 * @param center テクスチャの中心点
	 * @param scale テクスチャの大きさ
	 * @param angle テクスチャの回転角度（度数法）
	 * @param color テクスチャの色
	 */
	void DrawTexture(Assets::Texture id, const Vector2& position = Vector2(0, 0), const Vector2& center = Vector2(0, 0), const Vector2& scale = Vector2(1, 1), float angle = 0.0f, const Color& color = Color::White);
	/**
	* @brief 矩形を画面に描画
	* @param id 登録した名前
	* @param position 描画する座標
	* @param rect 切り取る範囲
	* @param alpha アルファ値
	*/
	void DrawRectangle(Assets::Texture id, const Vector2& position = Vector2(0, 0), const Rect& rect = Rect(0, 0, 1, 1), const Color& color = Color::White);
	/**
	* @brief 画像を使って数字を画面に描画する
	* @param id 登録した名前
	* @param position 座標
	* @param number 数値
	* @param width 数字１つあたりの横幅
	* @param height 数字１つあたりの縦幅
	* @param digit 桁数
	* @param fill 余った桁を何で埋めるか
	*/
	void DrawNumber(Assets::Texture id, const Vector2& position, int number, int width, int height, int digit = 0, char fill = '0');
	/**
	* @brief テクスチャを削除
	* @param id テクスチャのハンドル
	*/
	void DeleteTexture(Assets::Texture id);
	/**
	 * @brief 全リソースの削除
	 */
	void Clear();
private:
	//!テクスチャを管理するコンテナ
	std::unordered_map<Assets::Texture, int> textures;
};