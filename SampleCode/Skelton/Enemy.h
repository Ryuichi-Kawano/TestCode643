#pragma once
namespace Battle {
//�^�̃v���g�^�C�v�錾
class Player;//�uPlayer�Ƃ������O�̃N���X������܂��v
class Enemy
{
	//�ׂ������e�͌ォ��(cpp����)�����邩��A���͂Ƃ�����
	//�A�h���X��������̈���m�ۂ��Ă�(8�o�C�g)
	Player* player_;
	int life_ = 100;
public:
	void OnDamage(int damage);///�_���[�W�H�炤
	void Attack();//�G�Ƀ_���[�W��^����
};
}


