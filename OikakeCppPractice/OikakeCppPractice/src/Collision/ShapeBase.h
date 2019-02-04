#pragma once

#include<array>
#include<functional>
#include"ShapeType.h"
#include"ShapePtr.h"

class Vector3;
class Matrix4;
class HitInfo;

/**
 * @file ShapeBase.h
 * @brief あたり判定のベースになるクラス定義ファイル
 * @author 阿曽
 * @date Unknown
 */

 /*! @class ShapeBase
 *   @brief あたり判定のベースになるクラス
 */
class ShapeBase {
public:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShapeBase();	
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ShapeBase() {}
	
	/// <summary>
	/// あたり判定を行う関数
	/// </summary>
	/// <param name="shape">あたり判定用の形状</param>
	/// <param name="hitInfo">あたり判定情報</param>
	/// <returns></returns>
	bool Intersect(const ShapeBase& shape, HitInfo& hitInfo);
	
	/// <summary>
	/// 座標移動
	/// </summary>
	/// <param name="position">座標</param>
	/// <returns>移動した形状ポインタ</returns>
	virtual ShapePtr Translate(const Vector3& position) const = 0;	
	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="matrix">姿勢行列</param>
	/// <returns>座標変換された形状ポインタ</returns>
	virtual ShapePtr Transform(const Matrix4& matrix) const = 0;
	
	/// <summary>
	/// 形状の種類を取得
	/// </summary>
	/// <returns>形状の種類</returns>
	virtual ShapeType GetShapeType() const { return ShapeType::Max_Num; }
	
	/// <summary>
	/// 球とのあたり判定
	/// </summary>
	/// <param name="shape">球のポインタ</param>
	/// <param name="hitInfo">あたり判定情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_BoundingSphere(const ShapeBase& shape, HitInfo& hitInfo);
	
	/// <summary>
	/// カプセルとのあたり判定
	/// </summary>
	/// <param name="shape">カプセルのポインタ</param>
	/// <param name="hitInfo">あたり判定の情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Capsule(const ShapeBase& shape, HitInfo& hitInfo);
	
	/// <summary>
	/// 線分とのあたり判定
	/// </summary>
	/// <param name="shape">線分のポインタ</param>
	/// <param name="hitInfo">あたり判定の情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Line(const ShapeBase& shape, HitInfo& hitInfo);
	
	virtual bool Collide_BoundingBox(const ShapeBase& shape, HitInfo& hitInfo);
	virtual bool Collide_OrientedBoundingBox(const ShapeBase& shape, HitInfo& hitInfo);

	/// <summary>
	/// 当たり判定をワイヤーフレームで描画
	/// </summary>
	virtual void Draw() const;

public:
	//!あたり判定を行うかどうか？
	bool isActive;
private:	
	/// <summary>
	/// あたり判定の関数を登録する
	/// </summary>
	void RegistFunc();
private:
	//!当たり判定の関数を入れる配列
	using CollisionFunc = std::array < std::function<bool(const ShapeBase&, HitInfo& hitInfo)>, static_cast<int>(ShapeType::Max_Num)>;
	//!当たり判定の関数を入れる配列
	static CollisionFunc func;
};