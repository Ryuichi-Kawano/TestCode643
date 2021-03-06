#include<DxLib.h>
#include"Geometry.h"
#include<cmath>
/// <summary>
/// 矩形Aと矩形Bの当たり判定
/// </summary>
/// <param name="rcA">矩形A</param>
/// <param name="rcB">矩形B</param>
/// <returns>当たってたらtrue/外れてたらfalse</returns>
bool IsHit(const Rect& rcA, const Rect& rcB) {
	//rcAとrcBが当たってたらtrueを返すように書き換えて
	//ください。
	//手順
	//?@X方向を調べる
	//	?@-1中心と中心のX座標の差分の絶対値をとる
	//  ?@-2それぞれの幅を足したものと?@-1を比較する
	//  ?@-3幅を足したもの?@-2より差分?@-1がでかいならfalseを返す
	//?AY方向を調べる
	//	?A-1中心と中心のY座標の差分の絶対値をとる
	//  ?A-2それぞれの高さを足したものと?A-1を比較する
	//  ?A-3高さを足したもの?A-2より差分?A-1がでかいならfalseを返す
	//?Bもし、?@、?Aで返されてなければtrueを返す。
	if (fabsf(rcA.center.x - rcB.center.x) > rcA.w + rcB.w) {
		return false;
	}
	if (fabsf(rcA.center.y - rcB.center.y) > rcA.h + rcB.h) {
		return false;
	}
	return true;
}

/// <summary>
/// 円と縁の当たり判定(円Aと円Bが当たってたらtrueを返す)
/// </summary>
/// <param name="cA">円A</param>
/// <param name="cB">円B</param>
/// <returns>当たってたらtrue/そうでないならfalse</returns>
bool IsHit(const Circle& cA, const Circle& cB) {
	//中心点間の距離を測って、それが２つの円の半径を足したものより大きいか
	//小さいかで当たってるかどうかを判定する。
	//?@中心点間の距離を測る
	//		i.x方向の差分を測る
	//		ii.y方向の差分を測る
	//		iii.iとiiの差分を２乗して足す
	//?A２つの円の半径を足す
	//?B?@と?Aを比較する
	//		※ただし、２乗したものと、してないものは比較しないように
	//			２乗したものは２乗した者同士比較
	//			２乗しないなら√つけるなりなんなりして、２乗しない状態で比較
	//?Bの結果、合計半径のほうが大きければtrue、そうでないならfalseを返す。
	auto diffVec = cA.center - cB.center;
	auto totalRadius = cA.radius + cB.radius;
	return diffVec.SQMagnitude() <= totalRadius * totalRadius;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetWindowText(L"円の当たり判定");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Circle cA = { {100,100},50 };
	Circle cB = { {400,300},80 };
	
	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		//上
		if (keystate[KEY_INPUT_UP]) {
			cA.center.y -= speed;
		}
		//下
		if (keystate[KEY_INPUT_DOWN]) {
			cA.center.y += speed;
		}
		//右
		if (keystate[KEY_INPUT_RIGHT]) {
			cA.center.x += speed;
		}
		//左
		if (keystate[KEY_INPUT_LEFT]) {
			cA.center.x -= speed;
		}

		UINT32 color = 0xffffff;
		//もし当たってたら色を変更する
		if (IsHit(cA, cB)) {
			color = 0xffaaaa;
			auto diffV = cA.center - cB.center;
			auto d = (cA.radius + cB.radius) - diffV.Magnitude();
			auto vec = diffV.Normalized() * d/2.0f;
			cA.center += vec;
			cB.center -= vec;
		}

		//円A
		DrawCircleAA(cA.center.x, cA.center.y, cA.radius, 32,color);

		//矩形B
		DrawCircleAA(cB.center.x, cB.center.y, cB.radius, 32, color);


		ScreenFlip();
	}
	DxLib_End();
	return 0;
}