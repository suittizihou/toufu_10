#pragma once

#include<array>
#include<functional>
#include"../ShapeType.h"
#include"ShapePtr2D.h"
#include"../HitInfo.h"
#include"Math/Vector2/Vector2.h"

class ShapeBase2D {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShapeBase2D();
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ShapeBase2D() {}

	/// <summary>
	/// あたり判定を行う関数
	/// </summary>
	/// <param name="shape">あたり判定用の形状</param>
	/// <param name="hitInfo">あたり判定情報</param>
	/// <returns></returns>
	bool Intersect(const ShapeBase2D& shape, HitInfo& hitInfo);

	/// <summary>
	/// 座標移動
	/// </summary>
	/// <param name="position">座標</param>
	/// <returns>移動した形状ポインタ</returns>
	virtual ShapePtr2D Translate(const Vector2& position) const = 0;

	/// <summary>
	/// 形状の種類を取得
	/// </summary>
	/// <returns>形状の種類</returns>
	virtual ShapeType2D GetShapeType() const { return ShapeType2D::Max_Num; }

	/// <summary>
	/// 球とのあたり判定
	/// </summary>
	/// <param name="shape">球のポインタ</param>
	/// <param name="hitInfo">あたり判定情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Circle(const ShapeBase2D& shape, HitInfo& hitInfo);

	/// <summary>
	/// カプセルとのあたり判定
	/// </summary>
	/// <param name="shape">カプセルのポインタ</param>
	/// <param name="hitInfo">あたり判定の情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Capsule(const ShapeBase2D& shape, HitInfo& hitInfo);

	/// <summary>
	/// 線分とのあたり判定
	/// </summary>
	/// <param name="shape">線分のポインタ</param>
	/// <param name="hitInfo">あたり判定の情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Line(const ShapeBase2D& shape, HitInfo& hitInfo);

	virtual bool Collide_Box(const ShapeBase2D& shape, HitInfo& hitInfo);

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
	using CollisionFunc = std::array < std::function<bool(const ShapeBase2D&, HitInfo& hitInfo)>, static_cast<int>(ShapeType2D::Max_Num)>;
	//!当たり判定の関数を入れる配列
	static CollisionFunc func;

};
