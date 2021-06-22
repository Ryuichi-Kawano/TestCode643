#pragma once

//2Dベクトル
struct Vector2 {
	float x, y;
	Vector2(float inx, float iny) :x(inx), y(iny) {};
	//ベクトルの大きさを返す関数
	float Magnitude()const;

	//ベクトルの大きさの2乗を返す関数
	//内部的にsqrtしないため、多少効率がいい
	//ただし、2乗状態なので扱いには気をつけましょう。
	float SQMagnitude()const;
	//ベクトルを正規化する(大きさを1にする)
	void Normalize();
	//ベクトルを正規化したベクトルを返す
	Vector2 Normalized()const;
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
};
//ベクトル足し算
Vector2 operator+(const Vector2& lval, const Vector2& rval);
//引き算
Vector2 operator-(const Vector2& lval, const Vector2& rval);

//ベクトルのスカラー倍(n倍のこと)nV=(na,nb)
Vector2 operator*(const Vector2& lval, float scale);

//ベクトルのスカラー割(nで割ったこと)V/n=(a/n,b/n)
Vector2 operator/(const Vector2& lval, float div);

//座標=ベクトルなので、座標として定義する
using Position2 = Vector2;

struct Rect {
	Position2 center;//中心点
	float w;//幅の半分
	float h;//高さの半分
	/// <summary>
	/// 左のX座標を返す
	/// </summary>
	/// <returns>左</returns>
	float Left()const;
	/// <summary>
	/// 上のY座標を返す
	/// </summary>
	/// <returns>上</returns>
	float Top()const;

	/// <summary>
	/// 右のX座標を返す
	/// </summary>
	/// <returns>右</returns>
	float Right()const;

	/// <summary>
	/// 下のY座標を返す
	/// </summary>
	/// <returns>下</returns>
	float Bottom()const;

	float Width()const;
	float Height()const;

};

//円の構造体
struct Circle {
	Position2 center;//中心点
	float radius;//半径
};


