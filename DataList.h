#pragma once
// �z�E�d�A�����X�g(�w�b�_��)
#include "main.h"
#include "icon.h"

// �m�[�h
typedef struct __node {
	Icon	data;				// �f�[�^
	struct __node *prev;		// ��s�m�[�h�ւ̃|�C���^
	struct __node *next;		// �㑱�m�[�h�ւ̃|�C���^
}Dnode;


// �z�E�d�A�����X�g
class Dlist {

public:
	Dnode * head;				// �擪�_�~�[�m�[�h�ւ̃|�C���^
	Dnode *crnt;				// ���ڃm�[�h�ւ̃|�C���^

	//���X�g�͋�
	int IsEmpty();

	// ���X�g��������
	void Initialize();

	// ���ڃm�[�h�̃f�[�^��\��
	void PrintCurrent();

	// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
	void PrintLnCurrent();

	// �֐�compare�ɂ����x�ƈ�v����Ɣ��肳���m�[�h��T��
	Dnode* Search(const Icon* x, int compare(const Icon* x, const Icon* y));

	//���ڃm�[�h��擪�w�b�_�ɂ���
	void setHead();

	// ���X�g�̃T�C�Y��߂�
	int size();

	// �S�m�[�h�̃f�[�^�����X�g���ɍX�V
	void update();

	// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
	void Print();

	// �S�m�[�h�̃f�[�^�����X�̋t���ɕ\��
	void PrintReverse();

	// ���ڃm�[�h�������ɐi�߂�
	int Next();

	// ���ڃm�[�h����O���ɖ߂�
	int Prev();

	// p���w���m�[�h�̒���Ƀm�[�h��}��
	void InsertAfter(Dnode* p, const Icon* x);

	// �擪�Ƀm�[�h��}��
	void InsertFront(const Icon* x);

	// �����Ƀm�[�h��}��
	void InsertRear(const Icon* x);

	// p���w���m�[�h���폜
	void Remove(Dnode* p);

	// �擪�m�[�h���폜
	void RemoveFront();

	// �����m�[�h���폜
	void RemoveRear();

	// ���ڃm�[�h���폜
	void RemoveCurrent();

	// �S�m�[�h���폜
	void Clear();

	// �z�E�d�A�����X�g�̌�n��
	void Terminate();
};
