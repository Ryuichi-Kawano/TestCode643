#pragma once

//2Dベクトル
struct Vector2 {
	float x, y;
};
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

struct Circle {
	Position2 center;//中心点
	float radius;//半径
};


