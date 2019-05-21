#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include "textureLoader.h"
#include "input.h"
#include "DataList.h"
#include "fileLoader.h"
#include "exporter.h"
#include "icon.h"
#include "cursor.h"
#include "inputDialog.h"

Image back;
Image back1;
Image back2;
Image back3;	//��Ŕz��ɂ��悤�I�I

Image heightBox;
Image widthBox;

//�����̒��g�\���p
Image heightProperty;

Icon playerIcon;

Icon exportButton;
Cursor cursor;
Dlist objList;
bool checkin = false;

InputDialog propertyDialog;

VECTOR2 cursorMoveAmount;//�ړ��� 
VECTOR2 recordCursor; //�N���b�N�����Ƃ��̃}�E�X���W
VECTOR2 recordIcon; //�N���b�N�����Ƃ��̃A�C�R�����W

bool onDrag = false;//�h���b�O����Ă��邩
bool onDrag2 = false;//�h���b�O����Ă��邩

bool doubleTrigger = false;//�_�u���N���b�N�t���O

bool propertyCheck1 = false; //�v���p�e�B���`�F�b�N�ł����Ԃ��ۂ�
bool propertyCheck2= false;

bool onPropertyInfo = false;

bool displayInfo = false;

bool oncursor(Image);

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0,WINDOW_WIDTH, WINDOW_HEIGHT);
	InitImage(&back1, getTexture(textureLoaderNS::ENEMY_ICON), 100, 160, 100, 100);
	InitImage(&back2, getTexture(textureLoaderNS::PLAYER_ICON), 100, 320, 100, 100);
	InitImage(&back3, getTexture(textureLoaderNS::STAR_ICON), 100, 480, 100, 100);
	
	InitImage(&heightBox, NULL, 1290, 81, 70, 22);
	SetColorImage(&heightBox, D3DXCOLOR(colorNS::RED));

	InitImage(&widthBox, NULL, 1290, 121, 70, 22);
	SetColorImage(&widthBox, D3DXCOLOR(colorNS::BLUE));

	InitImage(&heightProperty, NULL, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8);
	SetColorImage(&heightProperty, D3DXCOLOR(colorNS::GRAY));

	playerIcon.initialize(PLAYER_ICON);

	objList.Initialize();//���X�g�̏�����


	exportButton.initialize(EXPORT_ICON);


	///////
	propertyDialog.initialize(getHWnd());
};

void updateTitle() {

	cursor.update();//�J�[�\���̍X�V

	moveControl(&back1);
	moveControl(&back2);
	
	//playerIcon.update();
	exportButton.update();
	
	bool onCreateIcon = false;
	Icon i;
	if (getMouseLTrigger())
	{
		if (playerIcon.onCursor(cursor.position))
		{
			i.initialize(PLAYER_ICON,VECTOR2((float)getMouseX(), (float)getMouseY()));
			objList.InsertAfter(objList.crnt, &i);
			onCreateIcon = true;
		}
	}

	//�v���p�e�B�̕\��
	if (getMouseLRelease())
	{
		if (doubleTrigger == false)
		{
			if (oncursor(back1))
			{
				doubleTrigger = true;
			}
			else
			{
				doubleTrigger = false;
			}
		}

	}
	if (doubleTrigger == true)
	{
		if (getMouseLTrigger())
		{
			if (oncursor(back1))
			{
				propertyCheck1 = true;
			}
			else
			{
				propertyCheck1 = false;
				doubleTrigger = false;
			}
		}

	}

	if (getMouseLTrigger())
	{
		if (oncursor(back2))
		{
			propertyCheck2 = true;
		}
		else
		{
			propertyCheck2 = false;
		}
	}

	//�_�C�A���O�\��
	/*propertyDialog.update();
	if (getMouseLButton())
	{
		if (oncursor(heightBox))
		{
			propertyDialog.print("please InputText");
		}
	}*/


	if (getMouseLButton())
	{
		if (oncursor(heightBox))
		{
			displayInfo = true;
		}
	}

	//�A�C�R���ɃJ�[�\�������킹��
	//�z�[���h��ԂłȂ���΁A
	//�A�C�R���̏�ł��ށi�N���b�N�j���I�u�W�F�N�g�����
	//�z�[���h��Ԃɂ���
	//
};

void drawTitle() {
	
	DrawImage(&back);
	DrawImage(&back1);
	DrawImage(&back2);
	DrawImage(&back3);

	DrawImage(&heightBox);
	DrawImage(&widthBox);

	//�����v���p�e�B�\��
	if (displayInfo == true)
	{
		DrawImage(&heightProperty);
	}

	playerIcon.draw();
	objList.Print();//���X�g����S�ĕ`�悷��

	exportButton.draw();

	propertyDialog.draw();

};

void printTitle() {

	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());

	
	if (propertyCheck1 == true)
	{
		printTextDX(getDebugFont(), "�� �G�l�~�[", 1230, 60);
		printTextDX(getDebugFont(), "����:", 1300, 80, back1.height);
		printTextDX(getDebugFont(), "���@:", 1300, 100, back1.width);
	}

	
	if (propertyCheck2 == true)
	{
		printTextDX(getDebugFont(), "�� �v���C���[", 1230, 60);
		printTextDX(getDebugFont(), "����:", 1250, 80, back2.height);
		printTextDX(getDebugFont(), "���@:", 1250, 120, back2.width);
	}


	if (displayInfo == true)
	{
		printTextDX(getDebugFont(), getTextIn(), WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 9 /32);
	}


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
	if (oncursor(heightBox))
	{
		printTextDX(getDebugFont(), "�}������", 500, 0);
	}
	if (oncursor(widthBox))
	{
		printTextDX(getDebugFont(), "�}������", 500, 0);
	}

	//�h���b�O�����t�@�C��������\��
	if (getFileLoader()->initialized())
	{
		printTextDX(getDebugFont(), "id", 0, WINDOW_HEIGHT / 2 - 20);
		printTextDX(getDebugFont(), ":objType", 100, WINDOW_HEIGHT / 2 -20);
		printTextDX(getDebugFont(), ":x", 200, WINDOW_HEIGHT / 2 -20);
		printTextDX(getDebugFont(), ":y", 300, WINDOW_HEIGHT / 2 -20);
		printTextDX(getDebugFont(), ":rot", 400, WINDOW_HEIGHT / 2 -20);
		int objNum = getFileLoader()->objNum();
		Object* o = getFileLoader()->getObj();
		for (int i = 0;i < objNum; i++)
		{
			printTextDX(getDebugFont(), "", 0, WINDOW_HEIGHT / 2 + (i * 20), o[i].id);
			printTextDX(getDebugFont(), ":", 100, WINDOW_HEIGHT / 2 + (i * 20), o[i].objType);
			printTextDX(getDebugFont(), ":", 200, WINDOW_HEIGHT / 2 + (i * 20), o[i].position.x);
			printTextDX(getDebugFont(), ":", 300, WINDOW_HEIGHT / 2 + (i * 20), o[i].position.y);
			printTextDX(getDebugFont(), ":", 400, WINDOW_HEIGHT / 2 + (i * 20), o[i].rotation);
		}
	}
};

bool oncursor(Image img)
{
	if (img.position.x < getMouseX() && img.position.x + img.width > getMouseX() &&
		img.position.y < getMouseY() && img.position.y + img.height > getMouseY())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool on(Image img)
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

				recordCursor = VECTOR2((float)getMouseX(), (float)getMouseY());//�N���b�N�����u�Ԃ̃J�[�\���ʒu��ۑ�
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
		cursorMoveAmount = VECTOR2((float)getMouseX(), (float)getMouseY()) - recordCursor;//�J�[�\���ړ���
		VECTOR2 virtualPos = recordIcon + cursorMoveAmount;//���̕\���ʒu
		setPosition(Target, virtualPos.x, virtualPos.y);
	}

}


void unInitializeTitle() 
{
	objList.Terminate();
};
 
