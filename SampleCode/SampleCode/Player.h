#pragma once
namespace Battle {
	//#include"Enemy.h"
	//Enemy�v���g�^�C�v�錾
	//������struct��class���Ȃǂ́A���������ʂ��Ă����܂��傤�B
	class Enemy;
	class Player
	{
		int x = 1, y = 2;
		int life_;
		Enemy* enemy_;//enemy�|�C���^
	public:
		int GetX()const;
		int GetY()const;
		void Attack();
		void OnDamage() {
			life_--;
		}
	};
}//namespace Battle;

