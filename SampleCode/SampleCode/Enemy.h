#pragma once
namespace Battle {
	class Player;//基本的にはプロトタイプ宣言だけ
	class Enemy
	{
		int x, y;
		int life_;
		//Player player_;//実体は持てません(サイズがわからないので)
		Player* player_;//ポインタならサイズが分かってるので持てる
	public:
		int GetX()const;
		int GetY()const;
		void Attack();
		void OnDamage() {
			life_--;
		}
	};
}//namespace Battle

