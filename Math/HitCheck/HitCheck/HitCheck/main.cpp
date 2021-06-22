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
	//①X方向を調べる
	//	①-1中心と中心のX座標の差分の絶対値をとる
	//  ①-2それぞれの幅を足したものと①-1を比較する
	//  ①-3幅を足したもの①-2より差分①-1がでかいならfalseを返す
	//②Y方向を調べる
	//	②-1中心と中心のY座標の差分の絶対値をとる
	//  ②-2それぞれの高さを足したものと②-1を比較する
	//  ②-3高さを足したもの②-2より差分②-1がでかいならfalseを返す
	//③もし、①、②で返されてなければtrueを返す。
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