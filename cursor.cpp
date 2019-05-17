
#include "cursor.h"
#include "input.h"

Cursor::Cursor()
{
	onDrag = false;
	target = NULL;
	position.x = (float)getMouseX();
	position.y = (float)getMouseY();

}

void Cursor::update()
{

	position.x = (float)getMouseX();
	position.y = (float)getMouseY();
}

void Cursor::setTarget(Icon* icon)
{
	target = icon;//�h���b�O�Ώۂ��Z�b�g����B
}

void Cursor::drag()
{
	if (target == NULL)return;//�I��Ώۂ��Ȃ���΃��^�[��
	if (getMouseLButton())
	{//���N���b�N��������Ă���Ƃ�
		if (target->onCursor(position))
		{//�J�[�\�����A�C�R����ɂ���Ƃ�
			if (!onDrag)
			{//�������h���b�O���Ă��Ȃ����
			 //���̃A�C�R�����h���b�O����
				recordPos = VECTOR2((float)getMouseX(), (float)getMouseY());//�N���b�N�����u�Ԃ̃J�[�\���ʒu��ۑ�
				recordIconPos = target->getPos();//�N���b�N�����u�Ԃ̃A�C�R���ʒu��ۑ�
				onDrag = true;//�h���b�O��Ԃɂ���
			}
		}
	}
	else if (onDrag)
	{//���N���b�N��������Ă��āA�h���b�O��Ԃł������Ȃ��
		onDrag = false;//�h���b�O��Ԃ�OFF�ɂ���
		target = NULL;//�^�[�Q�b�g��������B
	}
	if (onDrag)
	{//�h���b�O��Ԃ̂Ƃ��ړ�
		moveAmount = VECTOR2((float)getMouseX(), (float)getMouseY()) - recordPos;//�J�[�\���ړ���
		VECTOR2 virtualPos = recordIconPos + moveAmount;//���̕\���ʒu	
		target->setPos(virtualPos);
	}
}