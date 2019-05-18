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
Icon icon[ICON_NUM];



Cursor cursor;
Dlist objList;
bool checkin = false;

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0,WINDOW_WIDTH, WINDOW_HEIGHT);
	
	//�A�C�R���̏�����
	for (int i = 0; i < ICON_NUM;i++)
	{
		icon[i].initialize(i);
	}
	objList.Initialize();//���X�g�̏�����
};


void updateTitle() {

	Icon obj;//�V���ɍ쐬����I�u�W�F�N�g�̏������p
	if (getFileLoader()->untreated())
	{//�t�@�C�����ǂݍ��܂�āA��������ԂɂȂ����ꍇ
		objList.Clear();//�S�m�[�h���폜
		int objNum = getFileLoader()->objNum();
		Object* o = getFileLoader()->getObj();
		for (int i = 0; i < objNum; i++)
		{//�ǂݍ��񂾃t�@�C���̏��ɏ]���āA���X�g��ǉ����Ă����B
			obj.initialize(
				o[i].objType,
				VECTOR2(
					o[i].position.x+icon[EDITER_AREA].getLeft(),
					o[i].position.y+icon[EDITER_AREA].getTop()),
				o[i].id,
				o[i].rotation
			);//�V���ɍ쐬����I�u�W�F�N�g�̏�����
			objList.InsertAfter(objList.crnt, &obj);//�I�u�W�F�N�g�̐���(���X�g�֓o�^)
		}
		getFileLoader()->processed();//������������Ԃɂ���
	}

	cursor.update();//�J�[�\���̍X�V
	for (int i = 0; i < ICON_NUM; i++) {
		icon[i].update();//�A�C�R���̍X�V
	}
	
	if (getMouseLTrigger())
	{// ���N���b�N���ꂽ��
		if (cursor.onCreateIcon==false)
		for (int i = 0; i < ICON_NUM; i++)
		{
			if (!icon[i].canDuplicate)continue;//�����\�A�C�R���̏ꍇ
			int id;//�ŗL�ԍ��̐ݒ�
			if (objList.IsEmpty()) {id = 0;}
			else {//objList.Search()//ID�̍ő�l��T������B
				//�Ƃ肠�����́A���ڃm�[�h��ID�̎��̔ԍ�����
				id = objList.crnt->prev->data.getID() + 1;}
			if (icon[i].onCursor())
			{// �J�[�\�����v���C���[�A�C�R����ɂ������ꍇ
				obj.initialize(i,
					icon[i].getPos(),
					id, 
					0
				);//�V���ɍ쐬����I�u�W�F�N�g�̏�����
				objList.InsertAfter(objList.crnt, &obj);//�I�u�W�F�N�g�̐���(���X�g�֓o�^)
				cursor.onCreateIcon = true;
				cursor.setTarget(&objList.crnt->data);//�J�[�\���̑I��ΏۂƂ��ăZ�b�g����B
			}
		}
	}

	objList.update();



	if (getMouseLRelease())
	{//���N���b�N�������ꂽ�Ƃ�
		if (cursor.onCreateIcon)//�I�u�W�F�N�g�𐶐����Ă����ꍇ
		{
			if (cursor.target == NULL)
			{//�J�[�\���̃^�[�Q�b�g��NULL�łȂ��ꍇ
				objList.RemoveCurrent();
			}
			else {//�J�[�\���̃^�[�Q�b�g��NULL�łȂ��ꍇ
				if (icon[EDITER_AREA].getLeft() > cursor.target->getLeft() ||
					icon[EDITER_AREA].getRight() < cursor.target->getRight() ||
					icon[EDITER_AREA].getTop() > cursor.target->getTop() ||
					icon[EDITER_AREA].getBottom() < cursor.target->getBottom())
				{//���������I�u�W�F�N�g���G���A���łȂ��ꍇ
					objList.RemoveCurrent();
				}
			}
			cursor.onCreateIcon = false;//������Ԃ�����
		}
	}


	//�I��ΏۃI�u�W�F�N�g������΃h���b�O���s���B
	cursor.drag();

};

void drawTitle() {

	DrawImage(&back);//�w�i�̕`��
	for (int i = 0; i < ICON_NUM; i++) {
		icon[i].draw();
	}
	objList.Print();//���X�g����S�ĕ`�悷��
};

void printTitle() {

	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());

	//�v���p�e�B�̕\��
	if (cursor.target == NULL) {
		printTextDX(getDebugFont(), "�� �I�u�W�F�N�g��I�����Ă��������B", 1230, 60);
		printTextDX(getDebugFont(), "����:", 1300, 80);
		printTextDX(getDebugFont(), "���@:", 1300, 100);
	}
	else if(cursor.target->onCursor())
	{
		printTextDX(getDebugFont(), "�� �v���C���[", 1230, 60);
		printTextDX(getDebugFont(), "����:", 1300, 80, cursor.target->getHeight());
		printTextDX(getDebugFont(), "���@:", 1300, 100, cursor.target->getWidth());
	}

	//�}�E�X���{�^���g���K�[
	if (getMouseLTrigger()){
		printTextDX(getDebugFont(), "MouseLButton[Trigger]:true", 500, 0);
	}else{
		printTextDX(getDebugFont(), "MouseLButton[Trigger]:false", 500, 0);}
	//�}�E�X���{�^�������[�X
	if (getMouseLRelease()){
		printTextDX(getDebugFont(), "MouseLButton[Release]:true", 500, 20);
	}else{
		printTextDX(getDebugFont(), "MouseLButton[Release]:false", 500, 20);}



	for (int i = 0; i < ICON_NUM; i++)
	{
		if (icon[i].onCursor())
		{
			printTextDX(getDebugFont(), "�}������", 200, 0);
		}
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

void unInitializeTitle() 
{
	UninitImage(&back);
	objList.Terminate();
};