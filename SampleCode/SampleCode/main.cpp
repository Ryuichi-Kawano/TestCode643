#include<DxLib.h>

/// <summary>
/// 2�����x�N�g��
/// </summary>
struct Vector2 {
	float x, y;
};

using Position2 = Vector2;///�x�N�g�������W������

/// <summary>
/// ��`�\����
/// </summary>
struct Rect {
	Position2 center;//��`�̒��S
	float w, h;//���S����̂��ꂼ��̒[���ǂꂭ�炢����Ă邩�܂蕝/2,��/2
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

	Rect rc = { 200,200,50,100 };//200,200�̈ʒu�ɕ�100����200�̋�`

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		//��`�̕\��
		DrawBox(rc.Left(), rc.Top(), rc.Right(), rc.Bottom(), 0xffffff, true);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}