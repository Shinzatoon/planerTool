#include "icon.h"
#include "textureLoader.h"
#include "input.h"
#include "fileLoader.h"
#include "exporter.h"

using namespace iconNS;
Icon::Icon()
{
	pressed = false;
}	
Icon::~Icon()
{
	UninitImage(&image);
}

void Icon::initialize(int _iconType, VECTOR2 pos, int _id, float rotation)
{
	initialize(_iconType);
	setPosition(&image, pos.x, pos.y);
	setAngle(&image, rotation);
	id = _id;
	if (enableFrame)
	{
		setPosition(&selectFrame, pos.x, pos.y);
		setAngle(&selectFrame, rotation);
	}
}
void Icon::initialize(int _iconType)
{
	iconType = _iconType;
	VECTOR2 size;
	VECTOR2 pos;
	LPDIRECT3DTEXTURE9* texture = NULL;
	int initializeMethod = DEFAULT;
	enableFrame = true;
	canDuplicate = true;
	switch (_iconType)
	{
	case EDITER_AREA:
		canDuplicate = false;
		texture = NULL;
		initializeMethod = COLOR;
		enableFrame = false;
		break;
	case EXPORT:
		canDuplicate = false;
		texture = getTexture(textureLoaderNS::EXPORT_ICON);
		setTextureList(&image, 2, *texture, *getTexture(textureLoaderNS::STAR_ICON));
		enableFrame = false;
		break;
	case PLAYER:
		texture = getTexture(textureLoaderNS::PLAYER_ICON);
		break;
	case ENEMY:
		texture = getTexture(textureLoaderNS::ENEMY_ICON);
		break;
	case STAR:
		texture = getTexture(textureLoaderNS::STAR_ICON);
		break;
	default:
		canDuplicate = false;//�����s��
		texture = NULL;//�e�N�X�`���Ȃ�
		initializeMethod = COLOR;//���������[�h�J���[
		enableFrame = false;//�t���[��������
		break;
	}
	//[�A�C�R���\���摜�{�̂̏�����]
	switch (initializeMethod)
	{
	case DEFAULT:
		InitImage(
		&image,
		texture,
		PARAMETER[iconType].x,
		PARAMETER[iconType].y,
		PARAMETER[iconType].width,
		PARAMETER[iconType].height);
		break;
	case ANIME:
		break;
	case COLOR:
		InitImage(
		&image,
		texture,
		PARAMETER[iconType].x,
		PARAMETER[iconType].y,
		PARAMETER[iconType].width,
		PARAMETER[iconType].height,
		PARAMETER[iconType].color);
		break;
	}
	
	//[�I��\�L�t���[���摜�̏�����]
	if (enableFrame){
		InitImage(&selectFrame,
			getTexture(textureLoaderNS::BUTTON_FRAME),
			PARAMETER[iconType].x,
			PARAMETER[iconType].y,
			PARAMETER[iconType].width,
			PARAMETER[iconType].height
		);
	}
}

void Icon::draw()
{	
	DrawImage(&image);
	if (enableFrame) {
		DrawImage(&selectFrame);
	}
}	
	
void Icon::update()
{	
	if (onCursor())
	{
	}
}	

bool Icon::exportUpdate()
{
	if (iconType != EXPORT)return false;
	if (onCursor())
	{//�����o���{�^���ɃJ�[�\�����������ꍇ
		if (getMouseLButton())
		{//���N���b�N��
			makePressed();//������Ԃɂ���
		}
		if(getMouseLRelease())
		{
			makeRelease();//�����Ԃɂ���
			const int BUF_SIZE = 1024;
			char buffer[BUF_SIZE];
			int onButton = NULL;
			_snprintf_s(buffer, BUF_SIZE, "%s%s%s",
				"�t�@�C���p�X[",
				getFileLoader()->getCurrentFile(),
				"]�Ƃ��ď����o�����s���܂����H");
			onButton = MessageBox(
				getHWnd(),
				buffer,
				"�G�N�X�|�[�g",
				MB_YESNO| MB_ICONWARNING);
			if (onButton == IDYES) return true;
		}
	}
	else
	{//�J�[�\�����{�^���O�̏ꍇ
		makeRelease();//�����Ԃɂ���
	}
	return false;
}

void Icon::makePressed()
{//�{�^���k��
	if (pressed)return;
	changeTexture(&image, 1);//1�Ԃɐؑ�
	pressed = true;
}

void Icon::makeRelease()
{//�����Ԃɂ���
	if (!pressed)return;
	changeTexture(&image, 0);//0�ԃe�N�X�`���ɐؑ�
	pressed = false;
}

bool Icon::onCursor()
{		
	VECTOR2 mousePos((float)getMouseX(), (float)getMouseY());
	if (image.position.x < mousePos.x && image.position.x + image.width > mousePos.x &&
		image.position.y < mousePos.y && image.position.y + image.height > mousePos.y)
	{	
		selectFrame.renderFlag = true;
		return true;
	}	
	else
	{	
		selectFrame.renderFlag = false;
		return false;
	}	
}	