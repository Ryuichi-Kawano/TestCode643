#include<DxLib.h>

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 {
	float x, y;
};

using Position2 = Vector2;///ベクトルも座標も同じ

/// <summary>
/// 矩形構造体
/// </summary>
struct Rect {
	Position2 center;//矩形の中心
	float w, h;//中心からのそれぞれの端がどれくらい離れてるかつまり幅/2,高/2
	float Left()const {
		return center.x - w;
	}
	float Right()const {
		return center.x + w;
	}
	float Top()const {
		return center.y - h;
	}
	float Bottom()const {
		return center.y + h;
	}
	float Width()const {
		return w * 2.0f;
	}
	float Height()const {
		return h * 2.0f;
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Rect rc = { 200,200,50,100 };//200,200の位置に幅100高さ200の矩形

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		//矩形の表示
		DrawBox(rc.Left(), rc.Top(), rc.Right(), rc.Bottom(), 0xffffff, true);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}