#pragma once
namespace Battle {
	//#include"Enemy.h"
	//Enemyプロトタイプ宣言
	//ただしstructかclassかなどは、しっかり区別しておきましょう。
	class Enemy;
	class Player
	{
		int x = 1, y = 2;
		int life_;
		Enemy* enemy_;//enemyポインタ
	public:
		int GetX()const;
		int GetY()const;
		void Attack();
		void OnDamage() {
			life_--;
		}
	};
}//namespace Battle;

