#include<DxLib.h>
#include<math.h>
#include"Geometry.h"

Position2 GetMousePosition2() {
	int mx, my;
	GetMousePoint(&mx, &my);
	return Position2(mx, my);
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
	SetGraphMode(640, 480, 32);
	ChangeWindowMode(true);
	SetWindowText("atan2ó˚èKÉTÉìÉvÉã");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_NEAREST);
	auto arrowcatH=LoadGraph("img/player.png");

	Position2 catpos = { 320,240 };
	float theta = 0.0f;
	Position2 bulletPos= { 320,240 };
	Position2 bulletVel = { 0,0 };


	int mouseInput = 0;

	while (!ProcessMessage()) {
		ClearDrawScreen();
		
		
		auto mpos = GetMousePosition2();
		auto direction = (mpos - catpos);
		auto angle = atan2(direction.y, direction.x);

		auto tmpMouseInput = DxLib::GetMouseInput();
		if ((mouseInput & MOUSE_INPUT_LEFT) == 0 && (tmpMouseInput & MOUSE_INPUT_LEFT) != 0) {
			bulletPos = { 320,240 };
			bulletVel =direction.Normalized()*10.0f;
		}
		mouseInput = tmpMouseInput;

		DrawFormatString(10, 10, 0xfffffff, "x=%d,y=%d", (int)mpos.x, (int)mpos.y);


		DrawRotaGraph(catpos.x, catpos.y, 8.0f, angle, arrowcatH,true);
		bulletPos = bulletPos +bulletVel;
		int x = bulletPos.x;
		int y = bulletPos.y;
		DrawCircleAA(x, y, 30, 24,0xffffff);
		//theta += 0.05f;
		ScreenFlip();
	}
	DxLib_End();
}