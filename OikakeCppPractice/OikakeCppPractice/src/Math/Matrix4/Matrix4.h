#pragma once

#include<array>
#include"Math/Vector3/Vector3.h"
#include"Math/Vector2/Vector2.h"
class Quaternion;

/**
 * @file Matrix4.h
 * @brief 4x4の行列定義ファイル
 * @author 阿曽
 * @date Unknown
 */

 /*! @class Matrix4
 *   @brief  4x4の行列
 */
class Matrix4 {
public:	
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Matrix4();	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	explicit Matrix4(const Quaternion& q);	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Matrix4();	
	/// <summary>
	/// 拡大縮小のみの行列を生成
	/// </summary>
	/// <param name="x">x座標の大きさ</param>
	/// <param name="y">y座標の大きさ</param>
	/// <param name="z">z座標の大きさ</param>
	/// <returns>拡大縮小のみの行列</returns>
	static Matrix4 Scale(float x, float y, float z);	
	/// <summary>
	/// 拡大縮小のみの行列を生成
	/// </summary>
	/// <param name="scale">大きさのベクトル</param>
	/// <returns>拡大縮小のみの行列</returns>
	static Matrix4 Scale(const Vector3& scale);	
	/// <summary>
	/// この行列に大きさを設定する
	/// </summary>
	/// <param name="x">x座標の大きさ</param>
	/// <param name="y">y座標の大きさ</param>
	/// <param name="z">z座標の大きさ</param>
	/// <returns>大きさを設定したこの行列の参照</returns>
	Matrix4& SetScale(float x, float y, float z);	
	/// <summary>
	/// この行列に大きさを設定する
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <returns>大きさを設定したこの行列の参照</returns>
	Matrix4& SetScale(const Vector3& scale);	
	/// <summary>
	/// この行列の大きさを取得
	/// </summary>
	/// <returns>大きさ</returns>
	Vector3 GetScale() const;	
	/// <summary>
	/// 平行移動のみの行列を生成
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="z">z座標</param>
	/// <returns>平行移動のみの行列</returns>
	static Matrix4 Translate(float x, float y, float z);	
	/// <summary>
	/// 平行移動のみの行列を生成
	/// </summary>
	/// <param name="translate">移動量</param>
	/// <returns>平行移動のみの行列</returns>
	static Matrix4 Translate(const Vector3& translate);	
	/// <summary>
	/// この行列に座標を設定する
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="z">z座標</param>
	/// <returns>座標を設定したこの行列の参照</returns>
	Matrix4& SetPosition(float x, float y, float z);	
	/// <summary>
	/// この行列に座標を設定する
	/// </summary>
	/// <param name="position">座標</param>
	/// <returns>座標を設定したこの行列の参照</returns>
	Matrix4& SetPosition(const Vector3& position);	
	/// <summary>
	/// この行列の座標を取得
	/// </summary>
	/// <returns>この行列の座標</returns>
	Vector3 GetPosition() const;	
	/// <summary>
	/// X軸回転のみの行列を生成
	/// </summary>
	/// <param name="angle">回転角度：度数法</param>
	/// <returns>X軸回転のみの行列</returns>
	static Matrix4 RotateX(float angle);
	/// <summary>
	/// Y軸回転のみの行列を生成
	/// </summary>
	/// <param name="angle">回転角度：度数法</param>
	/// <returns>Y軸回転のみの行列</returns>
	static Matrix4 RotateY(float angle);
	/// <summary>
	/// Z軸回転のみの行列を生成
	/// </summary>
	/// <param name="angle">回転角度：度数法</param>
	/// <returns>Z軸回転のみの行列</returns>
	static Matrix4 RotateZ(float angle);	
	/// <summary>
	/// この行列にX軸回転の角度を設定する
	/// </summary>
	/// <param name="angle">角度：度数法</param>
	/// <returns>X軸回転の角度を設定したこの行列の参照</returns>
	Matrix4& SetRotateX(float angle);
	/// <summary>
	/// この行列にY軸回転の角度を設定する
	/// </summary>
	/// <param name="angle">角度：度数法</param>
	/// <returns>Y軸回転の角度を設定したこの行列の参照</returns>
	Matrix4& SetRotateY(float angle);
	/// <summary>
	/// この行列にZ軸回転の角度を設定する
	/// </summary>
	/// <param name="angle">角度：度数法</param>
	/// <returns>Z軸回転の角度を設定したこの行列の参照</returns>
	Matrix4& SetRotateZ(float angle);	
	/// <summary>
	/// この行列からクォータニオンを生成する
	/// </summary>
	/// <returns>クォータニオン</returns>
	Quaternion GetRotation() const;	
	/// <summary>
	/// この行列から回転行列を取得する
	/// </summary>
	/// <returns>回転行列</returns>
	Matrix4 GetRotationMatrix() const;	
	/// <summary>
	/// XYZ軸の回転量をラジアン角で取得する
	/// </summary>
	/// <returns>XYZ軸の回転量</returns>
	Vector3 GetRotateAngle_Radian() const;
	/// <summary>
	/// XYZ軸の回転量を度数法で取得する
	/// </summary>
	/// <returns>XYZ軸の回転量</returns>
	Vector3 GetRotateAngle_Degree() const;	
	/// <summary>
	/// 姿勢行列を生成する
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">平行移動</param>
	/// <returns>姿勢行列</returns>
	static Matrix4 CreateWorld(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);
	/// <summary>
	/// 姿勢行列を生成する
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">平行移動</param>
	/// <returns>姿勢行列</returns>
	static Matrix4 CreateWorld(const Vector3& scale, const Matrix4& rotate, const Vector3& translate);
	/// <summary>設定された前方向を向く行列を作成</summary>
	/// <param name="position">座標</param>
	/// <param name="forward">前方向</param>
	/// <param name="up">上方向</param>
	static Matrix4 CreateLookAt(const Vector3& position, const Vector3& forward, const Vector3& up);	
	/// <summary>
	/// 透視投影行列を生成
	/// </summary>
	/// <param name="fov">視野角</param>
	/// <param name="aspect">アスペクト比</param>
	/// <param name="near_">近クリップ</param>
	/// <param name="far_">遠クリップ</param>
	/// <returns>透視投影行列</returns>
	static Matrix4 CreatePerspective(float fov, float aspect, float near_, float far_);	
	/// <summary>
	/// カメラ行列を生成
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="target">注視点</param>
	/// <param name="up">カメラの上方向</param>
	/// <returns>カメラ行列</returns>
	static Matrix4 CreateView(const Vector3& position, const Vector3& target, const Vector3& up);	
	/// <summary>
	/// 回転行列を生成する
	/// </summary>
	/// <param name="axis">回転する軸</param>
	/// <param name="angle">角度：度数法</param>
	/// <returns>回転行列</returns>
	static Matrix4 CreateFromAxisAngle(const Vector3& axis, float angle);	
	/// <summary>
	/// 回転行列を生成する
	/// </summary>
	/// <param name="rotate">クォータニオン</param>
	/// <returns>回転行列</returns>
	static Matrix4 CreateFromQuaternion(const Quaternion& rotate);	
	/// <summary>
	/// 回転行列を生成する
	/// </summary>
	/// <param name="yaw">ヨーY軸回転：度数法</param>
	/// <param name="pitch">ピッチX軸回転：度数法</param>
	/// <param name="roll">ロールZ軸回転：度数法</param>
	/// <returns>回転行列</returns>
	static Matrix4 CreateFromYawPitchRoll(float yaw, float pitch, float roll);	

	static Vector3 CreateProjection(const Vector3& position, const Matrix4& screen, const Matrix4& perspective, const Matrix4& view, const Matrix4& world = IdentityMatrix);
	static Vector3 CreateUnProjection(const Vector3& position, const Matrix4& screen, const Matrix4& perspective, const Matrix4& view, const Matrix4& world = IdentityMatrix);	
	/// <summary>
	/// DirectXのスクリーン行列を生成
	/// </summary>
	/// <param name="position">スクリーン座標</param>
	/// <param name="width">スクリーン画面の横サイズ</param>
	/// <param name="height">スクリーン画面の縦サイズ</param>
	/// <returns>DirectXのスクリーン行列</returns>
	static Matrix4 CreateScreenDirectX(const Vector2& position, float width, float height);
	/// <summary>
	/// OpenGLのスクリーン行列を生成
	/// </summary>
	/// <param name="position">スクリーン座標</param>
	/// <param name="width">スクリーン画面の横サイズ</param>
	/// <param name="height">スクリーン画面の縦サイズ</param>
	/// <returns>OpenGLのスクリーン行列</returns>
	static Matrix4 CreateScreenOpenGL(const Vector2& position, float width, float height);	
	/// <summary>
	/// この行列から置換行列を生成
	/// </summary>
	/// <returns>置換行列</returns>
	Matrix4 Transpose();	
	/// <summary>
	/// 行列を補間する
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <param name="amount">比</param>
	/// <returns>補間した行列</returns>
	Matrix4 Lerp(const Matrix4& matrix, float amount);
	/// <summary>
	/// この行列から大きさ、回転、座標を取得する
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <param name="rotation">回転</param>
	/// <param name="translation">座標</param>
	void Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;	
	/// <summary>
	/// 左方向ベクトルを設定
	/// </summary>
	/// <param name="left">左方向ベクトル</param>
	/// <returns>左方向ベクトルを設定したこの行列の参照</returns>
	Matrix4& SetLeft(const Vector3& left);
	/// <summary>
	/// 上方向ベクトルを設定
	/// </summary>
	/// <param name="left">上方向ベクトル</param>
	/// <returns>上方向ベクトルを設定したこの行列の参照</returns>
	Matrix4& SetUp(const Vector3& up);
	/// <summary>
	/// 前方向ベクトルを設定
	/// </summary>
	/// <param name="left">前方向ベクトル</param>
	/// <returns>前方向ベクトルを設定したこの行列の参照</returns>
	Matrix4& SetFront(const Vector3& front);	
	/// <summary>
	/// この行列から左方向ベクトルを崇徳
	/// </summary>
	/// <returns>左方向ベクトル</returns>
	Vector3 GetLeft() const;
	/// <summary>
	/// この行列から上方向ベクトルを崇徳
	/// </summary>
	/// <returns>上方向ベクトル</returns>
	Vector3 GetUp() const;
	/// <summary>
	/// この行列から前方向ベクトルを崇徳
	/// </summary>
	/// <returns>前方向ベクトル</returns>
	Vector3 GetFront() const;
	/// <summary>
	/// この行列で座標変換を行う
	/// </summary>
	/// <param name="vector">座標変換する座標</param>
	/// <returns>
	/// この行列によって座標変換された座標
	/// </returns>
	Vector3 Transform(const Vector3& vector) const;	
	/// <summary>
	/// 単位行列
	/// </summary>
	/// <returns>単位行列にしたこの行列の参照</returns>
	Matrix4& Identity();	
	/// <summary>
	/// この行列の逆行列を取得
	/// </summary>
	/// <returns>逆行列</returns>
	Matrix4 Inverse() const;
	/// <summary>
	/// この行列から回転と平行移動のみの逆行列を取得
	/// </summary>
	/// <returns>回転と平行移動のみの逆行列</returns>
	Matrix4 InverseFast() const;	
	/// <summary>
	/// この行列から正規化した回転行列を取得
	/// </summary>
	/// <returns>正規化した回転行列</returns>
	Matrix4 GetNormalizeRotationMatrix() const;
	/// <summary>
	/// この行列を正規化する
	/// </summary>
	/// <returns>正規化した回転行列</returns>
	Matrix4& NormalizeRotationMatrix();

private:	
	/// <summary>
	/// 回転行列から角度を求める
	/// </summary>
	/// <returns>XYZ軸の回転量</returns>
	Vector3 CalculateAngleFromRotate() const;
public:
	//!単位行列
	static const Matrix4 IdentityMatrix;

public:
	Matrix4 operator * (const Matrix4& matrix);
	Vector3 operator * (const Vector3& vector);
	Matrix4& operator *= (const Matrix4& matrix);

public:	
	Matrix4 Multiply(const Matrix4& a, const Matrix4& b);
	Vector3 Multiply(const Vector3& vector, const Matrix4& matrix);

public:
	//!行列の定義
	using Matrix = std::array<std::array<float, 4>, 4>;
	//!4x4の行列
	Matrix m;
};

inline 	Vector3 operator * (const Vector3& vector, const Matrix4& matrix) {
	return Matrix4(matrix).Transform(vector);
}

inline Matrix4 operator * (const Matrix4& m1, const Matrix4& m2) {
	return Matrix4().Multiply(m1, m2);
}