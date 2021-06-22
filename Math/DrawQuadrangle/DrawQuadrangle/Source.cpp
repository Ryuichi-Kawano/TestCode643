#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///�Ƃ���_�𒆐S�ɉ�]���āA���̉�]��̍��W��Ԃ��܂��B
///@param center ��]���S�_
///@param angle ��]�p�x
///@param pos ���̍��W
///@return �ϊ���̍��W
Position2 RotatePosition(const Position2& center, float angle, Position2 pos) {
	//�@���S�����_�ɕ��s�ړ�����
	//�A���_���S�ɉ�]����
	//�B���S�����̍��W�֖߂�
	// 
	Position2 ret;
	Position2 tmpPos = pos;
	//center�����S�ɂ��������W
	//�@center�̍��W�Ԃ�pos���������ret
	//�A��]
	//�Bcenter�̍��W�Ԃ�܂�����(���S�����ɖ߂�)
	tmpPos -= center;
	ret.x = tmpPos.x * cos(angle) - tmpPos.y * sin(angle);
	ret.y = tmpPos.x * sin(angle) + tmpPos.y * cos(angle);
	ret += center;

	//�����ɉ�]�ϊ��������Ă�������
	return ret;//�f�t�H���g�͂��̂܂ܕԂ��Ă܂��B
	//��������������āA����̓_�𒆐S�ɉ�]���s���悤�ɂ��Ă��������B
}

int WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR,int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Position2 positions[4] = {
		{100,50},//����
		{200,150},//�E��
		{200,250},//�E��
		{75,300},//����
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

		//���ꂼ��̒��_�ɉ�]�ϊ����{��
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