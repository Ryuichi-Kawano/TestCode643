#include<DxLib.h>
#include"Geometry.h"
#include<cmath>
/// <summary>
/// ��`A�Ƌ�`B�̓����蔻��
/// </summary>
/// <param name="rcA">��`A</param>
/// <param name="rcB">��`B</param>
/// <returns>�������Ă���true/�O��Ă���false</returns>
bool IsHit(const Rect& rcA, const Rect& rcB) {
	//rcA��rcB���������Ă���true��Ԃ��悤�ɏ���������
	//���������B
	//�菇
	//�@X�����𒲂ׂ�
	//	�@-1���S�ƒ��S��X���W�̍����̐�Βl���Ƃ�
	//  �@-2���ꂼ��̕��𑫂������̂Ƈ@-1���r����
	//  �@-3���𑫂������̇@-2��荷���@-1���ł����Ȃ�false��Ԃ�
	//�AY�����𒲂ׂ�
	//	�A-1���S�ƒ��S��Y���W�̍����̐�Βl���Ƃ�
	//  �A-2���ꂼ��̍����𑫂������̂ƇA-1���r����
	//  �A-3�����𑫂������̇A-2��荷���A-1���ł����Ȃ�false��Ԃ�
	//�B�����A�@�A�A�ŕԂ���ĂȂ����true��Ԃ��B
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
	SetWindowText(L"��`�����蔻��");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Rect rcA = { 100,100,75,75 };
	Rect rcB = { 400,300,75,125 };

	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		//��
		if (keystate[KEY_INPUT_UP]) {
			rcA.center.y -= speed;
		}
		//��
		if (keystate[KEY_INPUT_DOWN]) {
			rcA.center.y += speed;
		}
		//�E
		if (keystate[KEY_INPUT_RIGHT]) {
			rcA.center.x += speed;
		}
		//��
		if (keystate[KEY_INPUT_LEFT]) {
			rcA.center.x -= speed;
		}

		UINT32 color = 0xffffff;
		//�����������Ă���F��ύX����
		if (IsHit(rcA, rcB)) {
			color = 0xffaaaa;
			//�����������Ă��瓖�����ĂȂ���Ԃɕ��A����
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

		//��`A
		DrawBox(rcA.Left(), rcA.Top(),
			rcA.Right(), rcA.Bottom(), color, true);

		//��`B
		DrawBox(rcB.Left(), rcB.Top(),
			rcB.Right(), rcB.Bottom(), color, true);


		ScreenFlip();
	}
	DxLib_End();
	return 0;
}