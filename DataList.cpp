// �z�E�d�A�����X�g�i�\�[�X���j
#include <stdio.h>
#include <stdlib.h>
#include "DataList.h"

// ��̃m�[�h�𓮓I�ɐ���
static Dnode* AllocDnode(void)
{
	return (Dnode*)calloc(1, sizeof(Dnode));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode(Dnode* n, const Icon* x, Dnode* prev, Dnode* next)
{
	n->data = *x;		// �f�[�^
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// ���X�g�͋�
int Dlist::IsEmpty()
{
	return head->next == head;
}

// ���X�g��������
void Dlist::Initialize()
{
	Dnode* dummyNode = AllocDnode(); // �_�~�[�m�[�h�𐶐�
	head = crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// ���ڃm�[�h�̃f�[�^��\��
void Dlist::PrintCurrent()
{
	if (IsEmpty()){}
		//printf("���ڃm�[�h������܂���B");
	//else
		//PrintImage(&list->crnt->data);
}

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void Dlist::PrintLnCurrent()
{
	PrintCurrent();
	putchar('\n');
}

// �֐�compare�ɂ����x�ƈ�v����Ɣ��肳���m�[�h��T��
Dnode* Dlist::Search(const Icon* x, int compare(const Icon* x, const Icon* y))
{
	Dnode* ptr = head->next;
	while (ptr != head)
	{
		if (compare(&ptr->data, x) == 0)
		{
			crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

//���ڃm�[�h��擪�w�b�_�ɂ���
void Dlist::setHead()
{
	if (IsEmpty() || crnt == head->next)return;	// ���ɐ擪�w�b�_�ł��閔�͋�
	
	crnt = head->next;//�擪�w�b�_�ɍ��킹��
}

// ���X�g�̃T�C�Y��߂�
int Dlist::size()
{
	int listSize = 0;
	if (IsEmpty()) {
		return listSize;
	}
	else {
		//�S�I�u�W�F�N�g�̑���
		Dnode* ptr = head->next;//�|�C���^��擪�w�b�_�ɍ��킹��B
		while (ptr != head) {
			listSize++;
			ptr = ptr->next;	// �㑱�m�[�h�ɒ���	
		}
	}
	return listSize;
}

// �S�m�[�h�̃f�[�^�����X�g���ɍX�V
void Dlist::update()
{
	if (IsEmpty()) {
		//���̏������s���܂���B
		//puts("�m�[�h������܂���B");
	}
	else {
		//�S�I�u�W�F�N�g�̑���
		Dnode* ptr = head->next;//�|�C���^��擪�w�b�_�ɍ��킹��B
		while (ptr != head) {
			ptr->data.update();	//�X�V����
			ptr = ptr->next;	// �㑱�m�[�h�ɒ���	
		}
	}
};


// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Dlist::Print()
{
	if (IsEmpty()){
		//puts("�m�[�h������܂���B");
	} else {
		//�S�I�u�W�F�N�g�̑���
		Dnode* ptr = head->next;//�|�C���^��擪�w�b�_�ɍ��킹��B
		while (ptr != head) {
			ptr->data.draw();	//���s����������
			ptr = ptr->next;	// �㑱�m�[�h�ɒ���	
		}
	}
};


// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void Dlist::PrintReverse()
{
	if (IsEmpty()) {
		//puts("�m�[�h������܂���B");
	} else {
		Dnode* ptr = head->prev;
		//puts("�y�ꗗ�\�z");
		while (ptr != head) {
			//PrintLnImage(&ptr->data);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

bool Dlist::IsLast()
{
	if (IsEmpty() || crnt->next == head)
		return true;	// �Ō�̃m�[�h�ł���
	return false;
}

// ���ڃm�[�h�������ɐi�߂�
int Dlist::Next()
{
	if (IsEmpty() || crnt->next == head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	crnt = crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Dlist::Prev()
{
	if (IsEmpty() || crnt->prev == head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	crnt = crnt->prev;
	return 1;
};


// p���w���m�[�h�̒���Ƀm�[�h��}��
void Dlist::InsertAfter(Dnode* p, const Icon* x)
{
	Dnode* ptr = AllocDnode();
	Dnode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	crnt = ptr;

};

// �擪�Ƀm�[�h��}��
void Dlist::InsertFront(const Icon* x)
{
	InsertAfter(head, x);
};

// �����Ƀm�[�h��}��
void Dlist::InsertRear(const Icon* x)
{
	InsertAfter(head->prev, x);
};

// p���w���m�[�h���폜
void Dlist::Remove(Dnode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
	if (crnt == head)
		crnt = head->next;
};

// �擪�m�[�h���폜
void Dlist::RemoveFront()
{
	if (!IsEmpty())
		Remove(head->next);
};

// �����m�[�h���폜
void Dlist::RemoveRear()
{
	if (!IsEmpty())
		Remove(head->prev);
};

// ���ڃm�[�h���폜
void Dlist::RemoveCurrent()
{
	if (crnt != head)
		Remove(crnt);
};

// �S�m�[�h���폜
void Dlist::Clear()
{
	while (!IsEmpty())	// ��ɂȂ�܂�
		RemoveFront();	// �擪�m�[�h���폜
};

// �z�E�d�A�����X�g�̌�n��
void Dlist::Terminate()
{
	Clear();			// �S�m�[�h���폜
	free(head);		// �_�~�[�m�[�h���폜
};
