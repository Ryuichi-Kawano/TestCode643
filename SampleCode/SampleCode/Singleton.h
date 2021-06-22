#pragma once
/// <summary>
/// �V���O���g���N���X
/// </summary>
/// �V���O���g���Ƃ́A�A�v���P�[�V��������
/// ���̂�������Ȃ����Ƃ�ۏ؂���N���X
class Singleton
{
public:
	//static�Ő錾���ꂽ�֐��́A�N���X��
	//�I�u�W�F�N�g�����ĂȂ��Ă��Ăяo����
	//�Ԃ��̂́u�Q�Ɓv�ł��邱�Ƃɒ���
	static Singleton& Instance() {
		//static�̓��[�J���ϐ��Ƃ���
		//�錾���Ă��u�ЂƂ����Ȃ��v�ۏ�
		static Singleton instance;
		return instance;
	}

	void OutCounter();
private:
	int counter = 0;
	Singleton() {};//�R���X�g���N�^��private�ɂ���
	//�R�s�[�֎~
	//�R�s�[�R���X�g���N�^(�����Ɏ������g�̌^������)
	Singleton(const Singleton&)=delete;
	//����֎~
	void operator=(const Singleton&)=delete;
};

