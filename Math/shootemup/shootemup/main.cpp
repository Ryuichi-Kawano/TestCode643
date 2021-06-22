#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径
bool IsHit(const Position2& posA, float radiusA, const Position2& posB,  float radiusB) {
	//当たり判定を実装してください
	auto diff = (posA - posB).Magnitude();
	return diff<=radiusA+radiusB;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("000000_川野竜一");
	if (DxLib_Init() != 0) {
		return -1;
	}
	int rt= MakeScreen(640, 480);
	//SetDrawScreen(rt);

	//背景用
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	int explosionH = LoadGraph("img/explosion.png");

	struct Bullet {
		Position2 pos;//座標
		Vector2 vel;//速度
		Vector2 accel;//加速度
		bool isActive = false;//生きてるか～？
	};

	//弾の半径
	float bulletRadius = 5.0f;

	//自機の半径
	float playerRadius = 10.0f;

	//適当に256個くらい作っとく
	Bullet bullets[512];

	Position2 enemypos(320,225);//敵座標
	Position2 playerpos(320, 400);//自機座標

	unsigned int frame = 0;//フレーム管理用

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	
	int explosionFrame = 0;
	bool isExploding = false;//爆発中
	while (ProcessMessage() == 0) {
		SetDrawScreen(rt);
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		//背景
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//プレイヤー
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640, playerpos.x + 4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0, playerpos.x - 4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0, playerpos.y - 4);
		}
		else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480, playerpos.y + 4);
		}

		int pidx = (frame / 4 % 2) * 5 + 3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//自機の本体(当たり判定)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}
		constexpr unsigned int period_frame = 180;
		const float speed = 5.0f;

		if (frame < period_frame) {//ただ下に
			if (frame % 12 == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.pos = enemypos;
						b.vel = { 0,speed };
						b.isActive = true;
						break;
					}
				}
			}

		}
		else if (frame < period_frame * 2) {//自機狙い
			//弾発射
			if (frame % 12 == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.pos = enemypos;
						b.vel = (playerpos - enemypos).Normalized() * speed;
						b.isActive = true;
						break;
					}
				}
			}
		}
		else if (frame < period_frame * 4) {//噴水
			//加速度あり弾
			if (frame % 12 == 0) {
				int count = -3;
				auto vel = Vector2(0.0f, -1.0f);
				float dAngle = DX_PI_F / 6.0f;
				auto angle = atan2f(vel.y, vel.x) + dAngle * count;
				for (auto& b : bullets) {
					if (count > 3) {
						break;
					}
					if (!b.isActive) {
						b.pos = enemypos;
						b.vel = Vector2(cos(angle), sin(angle)) * speed;
						b.accel = Vector2(0.0, 0.1f);
						b.isActive = true;
						angle += dAngle;
						++count;
					}
				}
			}
		}
		else if (frame <= period_frame * 5) {//nway弾
			if (frame % 5 == 0) {
				constexpr int n = 6;
				int count = -n / 2;
				auto vel = (playerpos - enemypos);
				float dAngle = DX_PI_F / 6.0f;
				auto angle = atan2f(vel.y, vel.x) + dAngle * count;
				for (auto& b : bullets) {
					if (count > n / 2) {
						break;
					}
					if (!b.isActive) {
						b.pos = enemypos;
						b.vel = Vector2(cos(angle), sin(angle)) * speed;
						b.accel = {};
						b.isActive = true;
						angle += dAngle;
						++count;
					}
				}
			}
		}
		else if (frame <= period_frame * 6) {
			//放射状弾
			if (frame % 12 == 0) {
				int count = -3;
				Vector2 vel = {1.0f,0.0f};
				float dAngle = DX_PI_F / 6.0f;
				auto angle = 0.0f;
				for (auto& b : bullets) {
					if (angle >= 2*DX_PI_F) {
						break;
					}
					if (!b.isActive) {
						b.pos = enemypos;
						b.vel = Vector2(cos(angle), sin(angle)) * speed ;
						b.accel = {};
						b.isActive = true;
						angle += dAngle;
						++count;
					}
				}
			}
		}
		else {
			//複数弾発射(ばらまき)
			if (frame % 12 == 0) {
				int count = -3;
				auto vel = (playerpos - enemypos);
				float dAngle = DX_PI_F / 6.0f;
				auto angle = atan2f(vel.y, vel.x) + dAngle * count;
				for (auto& b : bullets) {
					if (count > 3) {
						break;
					}
					if (!b.isActive) {
						b.pos = enemypos;
						auto rndSpd = (float)(rand() % 10 + 2) / 5.0f;
						b.vel = Vector2(cos(angle), sin(angle)) * speed * rndSpd;
						b.accel = {};
						b.isActive = true;
						angle += dAngle + (float)(rand() % 72) * DX_PI / 180.0f;
						++count;
					}
				}
			}
		}
	

		//弾の更新および表示
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//弾の現在座標に弾の現在速度を加算してください
			b.vel += b.accel;
			b.pos += b.vel;
			float angle = atan2(b.vel.y,b.vel.x);
			//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
			
			DrawRotaGraph(b.pos.x, b.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//弾を殺す
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//あたり！
			//↓のIsHitは実装を書いてません。自分で書いてください。
			if (!isExploding&&IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//当たった反応を書いてください。
				b.isActive = false;
				isExploding = true;
				explosionFrame = 0;
			}
		}

		if (isExploding) {
			if (explosionFrame > 60) {
				isExploding = false;
				explosionFrame = 0;
			}
			else {
				DrawRectRotaGraph2(
					playerpos.x, playerpos.y,
					(explosionFrame / 5) * 128, 0,//左上
					128, 128,
					64, 100, 1.0f, 0.0f,
					explosionH, true);
				++explosionFrame;
			}
		}

		//敵の表示
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//敵の本体(当たり判定)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		frame=(frame+1)%(period_frame*10);

		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		if (explosionFrame > 0) {
			DrawGraph((explosionFrame % 10 - 5) * 2, (explosionFrame % 5 - 2) * 5, rt, false);
		}
		else {
			DrawGraph(0,0, rt, false);
		}

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}