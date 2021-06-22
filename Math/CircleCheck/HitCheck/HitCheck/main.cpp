#include<DxLib.h>
#include"Geometry.h"
#include<cmath>
/// <summary>
/// ‹éŒ`A‚Æ‹éŒ`B‚Ì“–‚½‚è”»’è
/// </summary>
/// <param name="rcA">‹éŒ`A</param>
/// <param name="rcB">‹éŒ`B</param>
/// <returns>“–‚½‚Á‚Ä‚½‚çtrue/ŠO‚ê‚Ä‚½‚çfalse</returns>
bool IsHit(const Rect& rcA, const Rect& rcB) {
	//rcA‚ÆrcB‚ª“–‚½‚Á‚Ä‚½‚çtrue‚ğ•Ô‚·‚æ‚¤‚É‘‚«Š·‚¦‚Ä
	//‚­‚¾‚³‚¢B
	//è‡
	//‡@X•ûŒü‚ğ’²‚×‚é
	//	‡@-1’†S‚Æ’†S‚ÌXÀ•W‚Ì·•ª‚Ìâ‘Î’l‚ğ‚Æ‚é
	//  ‡@-2‚»‚ê‚¼‚ê‚Ì•‚ğ‘«‚µ‚½‚à‚Ì‚Æ‡@-1‚ğ”äŠr‚·‚é
	//  ‡@-3•‚ğ‘«‚µ‚½‚à‚Ì‡@-2‚æ‚è·•ª‡@-1‚ª‚Å‚©‚¢‚È‚çfalse‚ğ•Ô‚·
	//‡AY•ûŒü‚ğ’²‚×‚é
	//	‡A-1’†S‚Æ’†S‚ÌYÀ•W‚Ì·•ª‚Ìâ‘Î’l‚ğ‚Æ‚é
	//  ‡A-2‚»‚ê‚¼‚ê‚Ì‚‚³‚ğ‘«‚µ‚½‚à‚Ì‚Æ‡A-1‚ğ”äŠr‚·‚é
	//  ‡A-3‚‚³‚ğ‘«‚µ‚½‚à‚Ì‡A-2‚æ‚è·•ª‡A-1‚ª‚Å‚©‚¢‚È‚çfalse‚ğ•Ô‚·
	//‡B‚à‚µA‡@A‡A‚Å•Ô‚³‚ê‚Ä‚È‚¯‚ê‚Îtrue‚ğ•Ô‚·B
	if (fabsf(rcA.center.x - rcB.center.x) > rcA.w + rcB.w) {
		return false;
	}
	if (fabsf(rcA.center.y - rcB.center.y) > rcA.h + rcB.h) {
		return false;
	}
	return true;
}

/// <summary>
/// ‰~‚Æ‰‚Ì“–‚½‚è”»’è(‰~A‚Æ‰~B‚ª“–‚½‚Á‚Ä‚½‚çtrue‚ğ•Ô‚·)
/// </summary>
/// <param name="cA">‰~A</param>
/// <param name="cB">‰~B</param>
/// <returns>“–‚½‚Á‚Ä‚½‚çtrue/‚»‚¤‚Å‚È‚¢‚È‚çfalse</returns>
bool IsHit(const Circle& cA, const Circle& cB) {
	//’†S“_ŠÔ‚Ì‹——£‚ğ‘ª‚Á‚ÄA‚»‚ê‚ª‚Q‚Â‚Ì‰~‚Ì”¼Œa‚ğ‘«‚µ‚½‚à‚Ì‚æ‚è‘å‚«‚¢‚©
	//¬‚³‚¢‚©‚Å“–‚½‚Á‚Ä‚é‚©‚Ç‚¤‚©‚ğ”»’è‚·‚éB
	//‡@’†S“_ŠÔ‚Ì‹——£‚ğ‘ª‚é
	//		i.x•ûŒü‚Ì·•ª‚ğ‘ª‚é
	//		ii.y•ûŒü‚Ì·•ª‚ğ‘ª‚é
	//		iii.i‚Æii‚Ì·•ª‚ğ‚Qæ‚µ‚Ä‘«‚·
	//‡A‚Q‚Â‚Ì‰~‚Ì”¼Œa‚ğ‘«‚·
	//‡B‡@‚Æ‡A‚ğ”äŠr‚·‚é
	//		¦‚½‚¾‚µA‚Qæ‚µ‚½‚à‚Ì‚ÆA‚µ‚Ä‚È‚¢‚à‚Ì‚Í”äŠr‚µ‚È‚¢‚æ‚¤‚É
	//			‚Qæ‚µ‚½‚à‚Ì‚Í‚Qæ‚µ‚½Ò“¯m”äŠr
	//			‚Qæ‚µ‚È‚¢‚È‚çã‚Â‚¯‚é‚È‚è‚È‚ñ‚È‚è‚µ‚ÄA‚Qæ‚µ‚È‚¢ó‘Ô‚Å”äŠr
	//‡B‚ÌŒ‹‰ÊA‡Œv”¼Œa‚Ì‚Ù‚¤‚ª‘å‚«‚¯‚ê‚ÎtrueA‚»‚¤‚Å‚È‚¢‚È‚çfalse‚ğ•Ô‚·B
	auto diffVec = cA.center - cB.center;
	auto totalRadius = cA.radius + cB.radius;
	return diffVec.SQMagnitude() <= totalRadius * totalRadius;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetWindowText(L"‰~‚Ì“–‚½‚è”»’è");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Circle cA = { {100,100},50 };
	Circle cB = { {400,300},80 };
	
	char keystate[256];
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		//ã
		if (keystate[KEY_INPUT_UP]) {
			cA.center.y -= speed;
		}
		//‰º
		if (keystate[KEY_INPUT_DOWN]) {
			cA.center.y += speed;
		}
		//‰E
		if (keystate[KEY_INPUT_RIGHT]) {
			cA.center.x += speed;
		}
		//¶
		if (keystate[KEY_INPUT_LEFT]) {
			cA.center.x -= speed;
		}

		UINT32 color = 0xffffff;
		//‚à‚µ“–‚½‚Á‚Ä‚½‚çF‚ğ•ÏX‚·‚é
		if (IsHit(cA, cB)) {
			color = 0xffaaaa;
			auto diffV = cA.center - cB.center;
			auto d = (cA.radius + cB.radius) - diffV.Magnitude();
			auto vec = diffV.Normalized() * d/2.0f;
			cA.center += vec;
			cB.center -= vec;
		}

		//‰~A
		DrawCircleAA(cA.center.x, cA.center.y, cA.radius, 32,color);

		//‹éŒ`B
		DrawCircleAA(cB.center.x, cB.center.y, cB.radius, 32, color);


		ScreenFlip();
	}
	DxLib_End();
	return 0;
}