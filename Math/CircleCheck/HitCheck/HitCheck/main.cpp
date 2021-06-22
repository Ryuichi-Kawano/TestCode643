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

/// <summary>
/// �~�Ɖ��̓����蔻��(�~A�Ɖ~B���������Ă���true��Ԃ�)
/// </summary>
/// <param name="cA">�~A</param>
/// <param name="cB">�~B</param>
/// <returns>�������Ă���true/�����łȂ��Ȃ�false</returns>
bool IsHit(const Circle& cA, const Circle& cB) {
	//���S�_�Ԃ̋����𑪂��āA���ꂪ�Q�̉~�̔��a�𑫂������̂��傫����
	//���������œ������Ă邩�ǂ����𔻒肷��B
	//�@���S�_�Ԃ̋����𑪂�
	//		i.x�����̍����𑪂�
	//		ii.y�����̍����𑪂�
	//		iii.i��ii�̍������Q�悵�đ���
	//�A�Q�̉~�̔��a�𑫂�
	//�B�@�ƇA���r����
	//		���������A�Q�悵�����̂ƁA���ĂȂ����͔̂�r���Ȃ��悤��
	//			�Q�悵�����̂͂Q�悵���ғ��m��r
	//			�Q�悵�Ȃ��Ȃ�����Ȃ�Ȃ�Ȃ肵�āA�Q�悵�Ȃ���ԂŔ�r
	//�B�̌��ʁA���v���a�̂ق����傫�����true�A�����łȂ��Ȃ�false��Ԃ��B
	auto diffVec = cA.center - cB.center;
	auto totalRadius = cA.radius + cB.radius;
	return diffVec.SQMagnitude() <= totalRadius * totalRadius;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetWindowText(L"�~�̓����蔻��");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Circle cA = { {100,100},50 };
	Circle cB = { {400,300},80 };
	
	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		//��
		if (keystate[KEY_INPUT_UP]) {
			cA.center.y -= speed;
		}
		//��
		if (keystate[KEY_INPUT_DOWN]) {
			cA.center.y += speed;
		}
		//�E
		if (keystate[KEY_INPUT_RIGHT]) {
			cA.center.x += speed;
		}
		//��
		if (keystate[KEY_INPUT_LEFT]) {
			cA.center.x -= speed;
		}

		UINT32 color = 0xffffff;
		//�����������Ă���F��ύX����
		if (IsHit(cA, cB)) {
			color = 0xffaaaa;
			auto diffV = cA.center - cB.center;
			auto d = (cA.radius + cB.radius) - diffV.Magnitude();
			auto vec = diffV.Normalized() * d/2.0f;
			cA.center += vec;
			cB.center -= vec;
		}

		//�~A
		DrawCircleAA(cA.center.x, cA.center.y, cA.radius, 32,color);

		//��`B
		DrawCircleAA(cB.center.x, cB.center.y, cB.radius, 32, color);


		ScreenFlip();
	}
	DxLib_End();
	return 0;
}