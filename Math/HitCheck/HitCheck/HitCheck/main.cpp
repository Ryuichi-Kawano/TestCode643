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


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetWindowText(L"矩形当たり判定");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Rect rcA = { 100,100,75,75 };
	Rect rcB = { 400,300,75,125 };

	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		//上
		if (keystate[KEY_INPUT_UP]) {
			rcA.center.y -= speed;
		}
		//下
		if (keystate[KEY_INPUT_DOWN]) {
			rcA.center.y += speed;
		}
		//右
		if (keystate[KEY_INPUT_RIGHT]) {
			rcA.center.x += speed;
		}
		//左
		if (keystate[KEY_INPUT_LEFT]) {
			rcA.center.x -= speed;
		}

		UINT32 color = 0xffffff;
		//もし当たってたら色を変更する
		if (IsHit(rcA, rcB)) {
			color = 0xffaaaa;
			//もし当たってたら当たってない状態に復帰する
			float diffX = rcB.center.x - rcA.center.x;
			float diffY = rcB.center.y - rcA.center.y;
			float signX = diffX < 0 ? -1.0f : 1.0f;
			float signY = diffY < 0 ? -1.0f : 1.0f;
			diffX = (rcA.w + rcB.w) - fabsf(rcA.center.x - rcB.center.x);
			diffY = (rcA.h + rcB.h) - fabsf(rcA.center.y - rcB.center.y);
			if (diffX < diffY) {
				rcA.center.x -= signX*diffX;
			}
			else {
				rcA.center.y -= signY * diffY;
			}
		}

		//矩形A
		DrawBox(rcA.Left(), rcA.Top(),
			rcA.Right(), rcA.Bottom(), color, true);

		//矩形B
		DrawBox(rcB.Left(), rcB.Top(),
			rcB.Right(), rcB.Bottom(), color, true);


		ScreenFlip();
	}
	DxLib_End();
	return 0;
}