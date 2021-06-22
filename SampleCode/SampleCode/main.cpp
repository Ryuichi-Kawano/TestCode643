#include<DxLib.h>
#include<sstream>
#include<cassert>
#include"Debug.h"
#include"Singleton.h"
#include"Game.h"
#include"Scene.h"
#include"Player.h"
#include"Enemy.h"

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

/// <summary>
/// �x���@���ʓx�@��
/// </summary>
/// <param name="deg">������</param>
/// <returns>���W�A���p</returns>
float DegreeToRadian(float deg) {
	return deg * DX_PI_F / 180.0f;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetWindowText(L"0000000_��엳��");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	constexpr size_t start_no = 13;
	constexpr size_t anim_pattern_num = 19-start_no;
	int graphH[anim_pattern_num] = {};
	for (int i = 0; i < anim_pattern_num; ++i) {
		std::wostringstream oss;
		oss << L"../../Asset/Player/Individual Sprites/" << i+start_no << ".png";
		graphH[i] = LoadGraph(oss.str().c_str());
		assert(graphH[i] >= 0);
	}

	int groundH = LoadGraph(L"img/ground.png");
	assert(groundH >= 0);

	int bgAssetsH = LoadGraph(L"img/bgAssets.png");
	assert(bgAssetsH >= 0);

	Singleton& singleton=Singleton::Instance();
	singleton.OutCounter();
	Singleton& singleton3= Singleton::Instance();
	singleton.OutCounter();
	Rect rc = { 200,200,50,100 };//200,200�̈ʒu�ɕ�100����200�̋�`
	char keystate[256];

	constexpr unsigned int frames_per_pic = 5;
	unsigned int frame = 0;

	//�}�E�X�̏�Ԃ�����Ă���
	//���}�E�X�̏�Ԃ̓r�b�g�t���O�Ŏ擾����
	//�Ⴆ�΁A�}�E�X�͍��N���b�N�A�E�N���b�N�݂̂Ƃ����
	//���N���b�N�̏ꍇ��1(01)���A�E�N���b�N�̏ꍇ��2(10)���Ԃ�
	//���ƉE�𓯎�����������3(11)���Ԃ�
	//�Ȃ̂ŁAtrue/false�ł���Ă�Ɛ������l������Ă���Ȃ��̂�
	//���ӂ��܂��傤�B��̓I�ɂ�MOUSE_INPUT_LEFT�Ƃ���&���Z����
	int lastMouseInput = GetMouseInput();
	bool isTurn = false;//���]���Ă邩�ǂ���
	int frameForAngle = 0;
	
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);


		constexpr int chip_size = 128;
		DrawModiGraph(
			320+32, 240, //����
			320+ chip_size-32, 240, //�E��
			320+ chip_size+32, 240+ chip_size, //�E��
			320-32, 240+ chip_size, //����
			groundH, true);

		constexpr int block_size = 32;
		//For�����g���āA32�Â��炢�Ń��C��������
		//�T�C���J�[�u�����܂��傤�B
		auto px = 0 * block_size;
		auto py = 240 + 100*sinf(0.5f*DegreeToRadian(0 * block_size+frameForAngle));
		Position2 currentPos = {px,py};//���ݍ��W
		for (int i = 1; i <= 20; ++i) {
			//������DrawLineAA���������ƂŃT�C���J�[�u��
			//��ʏ�ɕ\�����܂��B
			auto nextX = i * block_size;

			Vector2 deltaVec = { block_size ,block_size * 2.0f * sinf(0.5f * DegreeToRadian(i * block_size + frameForAngle)) };
			Position2 nextPos = currentPos + deltaVec;
			//auto nextY = 240 + 100*sinf(0.5f*DegreeToRadian(i * block_size+frameForAngle));

			//DrawModiGraph(
			//	px, py, //����
			//	nextX, nextY, //�E��
			//	nextX, nextY+block_size, //�E��
			//	px, py+block_size, //����
			//	groundH,true);

			//DrawRectModiGraph(
			//	px, py+100, //����
			//	nextX, nextY+100, //�E��
			//	nextX, nextY + block_size+100, //�E��
			//	px, py + block_size+100, //����
			//	48,0,//�؂蔲���Ă���摜�̍���
			//	16,16,//�؂蔲���Ă���摜�̕��A����
			//	bgAssetsH, true);

			//�l�p�`��\�����Ă݂�
			DrawLineAA(px, py, nextX, nextY, 0xffffff, 2.0f);//���
			DrawLineAA(nextX, nextY, nextX, nextY+block_size, 0xffffff, 2.0f);//�E��
			DrawLineAA(nextX, nextY+block_size, px, py+block_size, 0xffffff, 2.0f);//����
			DrawLineAA(px, py+block_size, px, py, 0xffffff, 2.0f);
			px = nextX;
			py = nextY;
		}


		int currentMouseInput = GetMouseInput();
		if (!(lastMouseInput & MOUSE_INPUT_LEFT) &&
			(currentMouseInput & MOUSE_INPUT_LEFT)) {
			isTurn = !isTurn;
		}
		lastMouseInput = currentMouseInput;

		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_LEFT]) {
			rc.center.x -= speed;
		}
		if (keystate[KEY_INPUT_RIGHT]) {
			rc.center.x += speed;
		}
		if (keystate[KEY_INPUT_UP]) {
			rc.center.y -= speed;
		}
		if (keystate[KEY_INPUT_DOWN]) {
			rc.center.y += speed;
		}
		auto count = 720 / 32;
		int x = 0;
		int y = 240;
		for (int i = 1; i <= count; ++i) {
			int tmpX = i * 32;
			int tmpY=240+100.0f*sin((float)(x) / 180.0f * DX_PI);
			//DrawLineAA(x, y, tmpX, tmpY, 0xffffff, 3.0f);
			x = tmpX;
			y = tmpY;
		}
		DrawFormatString(10, 10, 0xffaaaa, L"x=%f , y=%f", rc.center.x, rc.center.y);
		//wchar_t outStr[32] = {};
		//wsprintf(outStr, L"x=%d , y=%d\n", (int)rc.center.x, (int)rc.center.y);
		std::wostringstream oss;
		oss << L"x=" << rc.center.x << L" , y=" << rc.center.y << std::endl;
		OutputDebugString(oss.str().c_str());
		//��`�̕\��
		DrawBox(rc.Left(), rc.Top(), rc.Right(), rc.Bottom(), 0xffffff, true);

		int mx, my;
		GetMousePoint(&mx, &my);
		Vector2 dir = { static_cast<float>(mx) - rc.center.x,
							static_cast<float>(my) - rc.center.y };

		auto angle = atan2(dir.y, dir.x);

		auto pictNo = frame / frames_per_pic;

		int gw, gh;
		GetGraphSize(graphH[pictNo], &gw, &gh);
		int centerX = isTurn ? gw - 31 : 31;
		DrawRotaGraph2(rc.center.x, rc.center.y,
			centerX,35,//�摜�̂ق��̃s�N�Z���ʒu
			5.0f,0.0f,graphH[pictNo], true, isTurn);


		DrawCircleAA(rc.center.x, rc.center.y, 5, 16, 0xff0000);

		ScreenFlip();
		frame = (frame + 1) % (anim_pattern_num * frames_per_pic);
		frameForAngle = (frameForAngle + 1) % 720;
	}
	test++;
	Debug::Output("tekito");
	DxLib_End();
	return 0;
}