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

Image back;
Image back1;
Image back2;
Image back3;	//��Ŕz��ɂ��悤�I�I

Icon playerIcon;

Icon exportButton;
Cursor cursor;
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
	
	playerIcon.initialize(PLAYER_ICON);

	objList.Initialize();//���X�g�̏�����

	exportButton.initialize(EXPORT_ICON);
};

void updateTitle() {

	cursor.update();//�J�[�\���̍X�V

	exportButton.update();
	
	bool onCreateIcon = false;
	Icon obj;//�V���ɍ쐬����I�u�W�F�N�g�̏������p
	if (getMouseLTrigger())
	{// ���N���b�N���ꂽ��
		if (playerIcon.onCursor(cursor.position))
		{// �J�[�\�����v���C���[�A�C�R����ɂ������ꍇ
			obj.initialize(PLAYER_ICON,playerIcon.getPos());//�V���ɍ쐬����I�u�W�F�N�g�̏�����
			objList.InsertAfter(objList.crnt, &obj);//�I�u�W�F�N�g�̐���(���X�g�֓o�^)
			onCreateIcon = true;
			cursor.setTarget(&objList.crnt->data);//�J�[�\���̑I��ΏۂƂ��ăZ�b�g����B
		}
		
		//���X�g�̑S����


	}


	//�I��ΏۃI�u�W�F�N�g������΃h���b�O���s���B
	cursor.drag();

};

void drawTitle() {
	
	DrawImage(&back);
	DrawImage(&back1);
	DrawImage(&back2);
	DrawImage(&back3);

	playerIcon.draw();
	objList.Print();//���X�g����S�ĕ`�悷��

	exportButton.draw();

};

void printTitle() {

	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());


	//�v���p�e�B�̕\��
	if (getMouseLButton())
	{
		if (oncursor(back2))
		{
			printTextDX(getDebugFont(), "�� �v���C���[", 1230, 60);
			printTextDX(getDebugFont(), "����:", 1300, 80, back2.height);
			printTextDX(getDebugFont(), "���@:", 1300, 100, back2.width);
			if (!onDrag)
			{
			}
		}
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