#pragma once

//2D�x�N�g��
struct Vector2 {
	float x, y;
	Vector2(float inx, float iny) :x(inx), y(iny) {};
	//�x�N�g���̑傫����Ԃ��֐�
	float Magnitude()const;

	//�x�N�g���̑傫����2���Ԃ��֐�
	//�����I��sqrt���Ȃ����߁A��������������
	//�������A2���ԂȂ̂ň����ɂ͋C�����܂��傤�B
	float SQMagnitude()const;
	//�x�N�g���𐳋K������(�傫����1�ɂ���)
	void Normalize();
	//�x�N�g���𐳋K�������x�N�g����Ԃ�
	Vector2 Normalized()const;
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
};
//�x�N�g�������Z
Vector2 operator+(const Vector2& lval, const Vector2& rval);
//�����Z
Vector2 operator-(const Vector2& lval, const Vector2& rval);

//�x�N�g���̃X�J���[�{(n�{�̂���)nV=(na,nb)
Vector2 operator*(const Vector2& lval, float scale);

//�x�N�g���̃X�J���[��(n�Ŋ���������)V/n=(a/n,b/n)
Vector2 operator/(const Vector2& lval, float div);

//���W=�x�N�g���Ȃ̂ŁA���W�Ƃ��Ē�`����
using Position2 = Vector2;

struct Rect {
	Position2 center;//���S�_
	float w;//���̔���
	float h;//�����̔���
	/// <summary>
	/// ����X���W��Ԃ�
	/// </summary>
	/// <returns>��</returns>
	float Left()const;
	/// <summary>
	/// ���Y���W��Ԃ�
	/// </summary>
	/// <returns>��</returns>
	float Top()const;

	/// <summary>
	/// �E��X���W��Ԃ�
	/// </summary>
	/// <returns>�E</returns>
	float Right()const;

	/// <summary>
	/// ����Y���W��Ԃ�
	/// </summary>
	/// <returns>��</returns>
	float Bottom()const;

	float Width()const;
	float Height()const;

};

//�~�̍\����
struct Circle {
	Position2 center;//���S�_
	float radius;//���a
};


