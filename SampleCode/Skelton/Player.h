#pragma once

namespace Battle {
class Enemy;//Enemy�Ƃ����N���X������܂���
class Player
{
	Enemy* enemy_;
	int life_ = 100;
public:
	void OnDamage(int damage);///�_���[�W�H�炤
	void Attack();//�G�Ƀ_���[�W��^����
};
}