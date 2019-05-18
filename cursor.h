#pragma once

#include "main.h"
#include "icon.h"

class Cursor
{
private:

public:
	bool onDrag;//�h���b�O�Ԃ��ǂ���
	VECTOR2 position;
	VECTOR2 recordPos;//�N���b�N�����Ƃ��̃}�E�X���W
	VECTOR2 recordIconPos;//�N���b�N�����Ƃ��̃A�C�R�����W
	VECTOR2 moveAmount;//�ړ��� 
	Icon* target;
	bool onCreateIcon;//�A�C�R��������
	Cursor();

	void update();

	void selectTarget(Icon* icon);

	void drag();
	
	void setTarget(Icon* icon);
};