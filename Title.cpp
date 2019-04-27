#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"
#include"input.h"
#include "CircDblLinkedList.h"

Image back;
Image back1;
Image back2;
Image back3;	//��Ŕz��ɂ��悤�I�I
Dlist objList;


bool checkin = false;

VECTOR2 cursorMoveAmount;//�ړ��� 
VECTOR2 recordCursor; //�N���b�N�����Ƃ��̃}�E�X���W
VECTOR2 recordIcon; //�N���b�N�����Ƃ��̃A�C�R�����W


bool onDrag = false;//�h���b�O����Ă��邩
bool onDrag2 = false;//�h���b�O����Ă��邩


bool oncursor(Image);

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0,WINDOW_WIDTH, WINDOW_HEIGHT);
	InitImage(&back1, getTexture(textureLoaderNS::ENEMY_ICON), 100, 160, 100, 100);
	InitImage(&back2, getTexture(textureLoaderNS::PLAYER_ICON), 100, 320, 100, 100);
	InitImage(&back3, getTexture(textureLoaderNS::STAR_ICON), 100, 480, 100, 100);
	
	Initialize(&objList);//���X�g�̏�����

	InsertAfter(&objList, objList.crnt, new Image());//�V����Image�\���̂�ǉ����� �o�^�@new
	InitImage(&objList.crnt->data, getTexture(textureLoaderNS::ENEMY_ICON), 100, 160, 100, 100);//���݂����Ă���m�[�h��������
	
};
void updateTitle() {

	moveControl(&back1);

	moveControl(&back2);
	//if (getMouseLButton())
	//{//���N���b�N��������Ă���Ƃ�
	//	if (oncursor(back1)) 
	//	{//�J�[�\�����A�C�R����ɂ���Ƃ�
	//		if (!onDrag)
	//		{//�������h���b�O���Ă��Ȃ����
	//			//���̃A�C�R�����h���b�O����
	//			recordCursor = VECTOR2(getMouseX(), getMouseY());//�N���b�N�����u�Ԃ̃J�[�\���ʒu��ۑ�
	//			recordIcon = (VECTOR2)back1.position;//�N���b�N�����u�Ԃ̃A�C�R���ʒu��ۑ�
	//			onDrag = true;//�h���b�O��Ԃɂ���
	//		}
	//	}
	//	//setPosition(&back1, back1.position.x += (float)getMouseRawX(), back1.position.y += (float)getMouseRawY());
	//	//setPosition(&back1, (float)getMouseRawX(), (float)getMouseRawY());
	//}
	//else if (onDrag)
	//{//���N���b�N��������Ă��āA�h���b�O��Ԃł������Ȃ��
	//	onDrag = false;//�h���b�O��Ԃ�OFF�ɂ���
	//}

	//if (onDrag)
	//{//�h���b�O��Ԃ̂Ƃ��ړ�
	//	cursorMoveAmount = VECTOR2(getMouseX(), getMouseY()) - recordCursor;//�J�[�\���ړ���
	//	VECTOR2 virtualPos = recordIcon + cursorMoveAmount;//���̕\���ʒu
	//	setPosition(&back1, virtualPos.x, virtualPos.y);
	//}
	

	


};
void drawTitle() {
	DrawImage(&back);
	DrawImage(&back1);
	DrawImage(&back2);
	DrawImage(&back3);


	DrawImage(&objList.crnt->data);//���݂����Ă���m�[�h��`�悷��

};
void printTitle() {
	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());
	if (getMouseLButton())
	{
		printTextDX(getDebugFont(), "mouseX:", 500, 0, getMouseRawX());
		printTextDX(getDebugFont(), "mouseY:", 500, 20, getMouseRawY());

	}
	if (oncursor(back1))
	{
		printTextDX(getDebugFont(), "�}������", 500, 0);
	}
	if (oncursor(back2))
	{
		printTextDX(getDebugFont(), "�}������", 500, 0);
	}
	if (oncursor(back3))
	{
		printTextDX(getDebugFont(), "�}������", 500, 0);
	}
};
bool oncursor(Image img)
{
	if (img.position.x < getMouseX() && img.position.x + img.height > getMouseX() &&
		img.position.y < getMouseY() && img.position.y + img.width > getMouseY())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Image a[1];
Image *Target;

void moveControl(Image *img)
{
	if (getMouseLButton())
	{//���N���b�N��������Ă���Ƃ�
		if (oncursor(*img))
		{//�J�[�\�����A�C�R����ɂ���Ƃ�
			if (!onDrag)
			{//�������h���b�O���Ă��Ȃ����
				//���̃A�C�R�����h���b�O����
				Target = img;

				recordCursor = VECTOR2(getMouseX(), getMouseY());//�N���b�N�����u�Ԃ̃J�[�\���ʒu��ۑ�
				recordIcon = (VECTOR2)Target->position;//�N���b�N�����u�Ԃ̃A�C�R���ʒu��ۑ�
				onDrag = true;//�h���b�O��Ԃɂ���
			}
		}
		//setPosition(&back1, back1.position.x += (float)getMouseRawX(), back1.position.y += (float)getMouseRawY());
		//setPosition(&back1, (float)getMouseRawX(), (float)getMouseRawY());
	}
	else if (onDrag)
	{//���N���b�N��������Ă��āA�h���b�O��Ԃł������Ȃ��
		onDrag = false;//�h���b�O��Ԃ�OFF�ɂ���
		Target = NULL;
	}

	if (onDrag && Target != NULL)
	{//�h���b�O��Ԃ̂Ƃ��ړ�
		cursorMoveAmount = VECTOR2(getMouseX(), getMouseY()) - recordCursor;//�J�[�\���ړ���
		VECTOR2 virtualPos = recordIcon + cursorMoveAmount;//���̕\���ʒu
		setPosition(Target, virtualPos.x, virtualPos.y);
	}
}

////malloc�T���v��
//int main()
//{
//	int i;
//	int *heep;
//	heep = (int*)malloc(sizeof(int) * 10);
//
//	if (heep == NULL)
//		exit(0);
//
//	for (i = 0; i < 10; i++)
//	{
//		heep[i] = i;
//	}
//	printf("%d\n", heep[5]);
//
//	free(heep);
//
//	return 0;
//}

void unInitializeTitle() {};