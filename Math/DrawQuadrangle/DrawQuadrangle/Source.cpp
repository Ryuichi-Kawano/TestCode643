#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///とある点を中心に回転して、その回転後の座標を返します。
///@param center 回転中心点
///@param angle 回転角度
///@param pos 元の座標
///@return 変換後の座標
Position2 RotatePosition(const Position2& center, float angle, Position2 pos) {
	//①中心を原点に平行移動して
	//②原点中心に回転して
	//③中心を元の座標へ戻す
	// 
	Position2 ret;
	Position2 tmpPos = pos;
	//centerが中心にしたい座標
	//①centerの座標ぶんposから引く→ret
	//②回転
	//③centerの座標ぶんまた足す(中心を元に戻す)
	tmpPos -= center;
	ret.x = tmpPos.x * cos(angle) - tmpPos.y * sin(angle);
	ret.y = tmpPos.x * sin(angle) + tmpPos.y * cos(angle);
	ret += center;

	//ここに回転変換を書いてください
	return ret;//デフォルトはそのまま返してます。
	//これを書き換えて、特定の点を中心に回転を行うようにしてください。
}

int WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR,int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Position2 positions[4] = {
		{100,50},//左上
		{200,150},//右上
		{200,250},//右下
		{75,300},//左下
	};

	float angle = 0.0f;
	while (ProcessMessage()==0) {
		ClearDrawScreen();
		DrawBox(0, 0, 640, 480, 0xffffff, true);

		int mx, my;
		GetMousePoint(&mx, &my);

		int minput = GetMouseInput();

		if (minput&MOUSE_INPUT_LEFT) {
			angle = 0.05f;
		}
		else if (minput&MOUSE_INPUT_RIGHT) {
			angle = -0.05f;
		}
		else {
			angle = 0.0f;
		}

		//それぞれの頂点に回転変換を施す
		for (auto& pos : positions) {
			pos = RotatePosition(Position2(mx, my), angle, pos);
		}

		DrawQuadrangleAA(
			positions[0].x,positions[0].y,
			positions[1].x, positions[1].y,
			positions[2].x, positions[2].y, 
			positions[3].x, positions[3].y, 
			0x000000,false,3.0f);

		DrawCircle(positions[0].x, positions[0].y, 5, 0xff0000);
		DrawFormatString(positions[0].x, positions[0].y - 20,
			0xff0000,"P(%2.2f,%2.2f)", positions[0].x, positions[0].y);
		DrawCircle(positions[1].x, positions[1].y, 5, 0xff0000);
		DrawFormatString(positions[1].x, positions[1].y + 20,
			0xff0000, "P(%2.2f,%2.2f)", positions[1].x, positions[1].y);
		DrawCircle(positions[2].x, positions[2].y, 5, 0xff0000);
		DrawFormatString(positions[2].x, positions[2].y + 20,
			0xff0000, "P(%2.2f,%2.2f)", positions[2].x, positions[2].y);
		DrawCircle(positions[3].x, positions[3].y, 5, 0xff0000);
		DrawFormatString(positions[3].x, positions[3].y - 20,
			0xff0000, "P(%2.2f,%2.2f)", positions[3].x, positions[3].y);

		ScreenFlip();
	}
	DxLib_End();
}