#pragma once

#include"../ShapeBase2D.h"

class Box : public ShapeBase2D {
public:

	Box(const Vector2& min, const Vector2& max);
	~Box();

	/// <summary>
	/// 座標移動
	/// </summary>
	/// <param name="position">座標</param>
	/// <returns>移動した形状ポインタ</returns>
	virtual ShapePtr2D Translate(const Vector2& position) const override;

	/// <summary>
	/// 形状の種類を取得
	/// </summary>
	/// <returns>形状の種類</returns>
	virtual ShapeType2D GetShapeType() const override { return ShapeType2D::Box; } 

	/// <summary>
	/// 球とのあたり判定
	/// </summary>
	/// <param name="shape">球のポインタ</param>
	/// <param name="hitInfo">あたり判定情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Circle(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	/// <summary>
	/// カプセルとのあたり判定
	/// </summary>
	/// <param name="shape">カプセルのポインタ</param>
	/// <param name="hitInfo">あたり判定の情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Capsule(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	/// <summary>
	/// 線分とのあたり判定
	/// </summary>
	/// <param name="shape">線分のポインタ</param>
	/// <param name="hitInfo">あたり判定の情報</param>
	/// <returns>[true 衝突した: false 衝突していない]</returns>
	virtual bool Collide_Line(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	virtual bool Collide_Box(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	/// <summary>
	/// 当たり判定をワイヤーフレームで描画
	/// </summary>
	virtual void Draw() const override;

public:
	Vector2 min;
	Vector2 max;
	Vector2 size;
};