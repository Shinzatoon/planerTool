
#include "cursor.h"
#include "input.h"

Cursor::Cursor()
{
	onDrag = false;

	position.x = (float)getMouseX();
	position.y = (float)getMouseY();

}

void Cursor::update()
{

	position.x = (float)getMouseX();
	position.y = (float)getMouseY();
}

void Cursor::drag(Icon* icon)
{
	if (getMouseLButton())
	{//���N���b�N��������Ă���Ƃ�
		if (icon->onCursor(position))
		{//�J�[�\�����A�C�R����ɂ���Ƃ�
			if (!onDrag)
			{//�������h���b�O���Ă��Ȃ����
			 //���̃A�C�R�����h���b�O����
				recordPos = VECTOR2((float)getMouseX(), (float)getMouseY());//�N���b�N�����u�Ԃ̃J�[�\���ʒu��ۑ�
				recordIconPos = icon->getPos();//�N���b�N�����u�Ԃ̃A�C�R���ʒu��ۑ�
				onDrag = true;//�h���b�O��Ԃɂ���
			}
		}
		//setPosition(&back1, back1.position.x += (float)getMouseRawX(), back1.position.y += (float)getMouseRawY());
		//setPosition(&back1, (float)getMouseRawX(), (float)getMouseRawY());
	}
	else if (onDrag)
	{//���N���b�N��������Ă��āA�h���b�O��Ԃł������Ȃ��
		onDrag = false;//�h���b�O��Ԃ�OFF�ɂ���
	}

	if (onDrag)
	{//�h���b�O��Ԃ̂Ƃ��ړ�
		moveAmount = VECTOR2((float)getMouseX(), (float)getMouseY()) - recordPos;//�J�[�\���ړ���
		VECTOR2 virtualPos = recordIconPos + moveAmount;//���̕\���ʒu
		
		icon->setPos(virtualPos);
		}
}
