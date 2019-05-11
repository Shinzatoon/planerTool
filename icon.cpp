#include "icon.h"
#include "textureLoader.h"
#include "input.h"
Icon::Icon()
{	
	m_onCursor = false;
	m_shrinked = false;
}	
Icon::~Icon()
{

}

void Icon::initialize(int iconType, VECTOR2 pos)
{
	initialize(iconType);
	setPosition(&m_image, pos.x, pos.y);
	setPosition(&m_selectFrame, pos.x, pos.y);
}
void Icon::initialize(int iconType)
{
	switch (iconType)
	{
	case EXPORT_ICON:
		defaultPos = VECTOR2(10, 10);
		defaultSize = VECTOR2(192 / 2, 64 / 2);
		InitImage(&m_selectFrame, getTexture(textureLoaderNS::BUTTON_FRAME), defaultPos.x, defaultPos.y, defaultSize.x, defaultSize.y);//[������]
		InitImage(&m_image, getTexture(textureLoaderNS::EXPORT_ICON), defaultPos.x, defaultPos.y, defaultSize.x, defaultSize.y);//[������]
		break;
	case PLAYER_ICON:
		defaultPos = VECTOR2(10, 200);
		defaultSize = VECTOR2(64, 64);
		InitImage(&m_selectFrame, getTexture(textureLoaderNS::BUTTON_FRAME), defaultPos.x, defaultPos.y, defaultSize.x, defaultSize.y);//[������]
		InitImage(&m_image, getTexture(textureLoaderNS::PLAYER_ICON), defaultPos.x, defaultPos.y, defaultSize.x, defaultSize.y);//[������]
		break;
	}
}

void Icon::draw()
{	
	DrawImage(&m_image);
	DrawImage(&m_selectFrame);
}	
	
void Icon::update()
{	
	VECTOR2 mousePos((float)getMouseX(), (float)getMouseY());
	if (onCursor(mousePos))
	{//�����o���{�^���ɃJ�[�\�����������ꍇ
		if (getMouseLButton())
		{//���N���b�N��
			shrink();//�g���Ԃɂ���
		}
		else {
			reSize();//���̑傫���ɖ߂�
		}
	}
	else 
	{//�J�[�\�����{�^���O�̏ꍇ
		reSize();//���̑傫���ɖ߂�
	}

}	

void Icon::shrink()
{//�{�^���k��
	if (m_shrinked)return;
	float rate = 0.9f;
	setPosition(&m_image, m_image.position.x, m_image.position.y);
	setSize(&m_image, m_image.width*rate, m_image.height*rate);
	setSize(&m_selectFrame, m_selectFrame.width*rate, m_selectFrame.height*rate);
	m_shrinked = true;
}

void Icon::reSize()
{//���̑傫���ɖ߂�
	if (!m_shrinked)return;
	setSize(&m_image, defaultSize.x, defaultSize.y);
	setSize(&m_selectFrame, defaultSize.x, defaultSize.y);
	m_shrinked = false;
}


bool Icon::onCursor(VECTOR2 mousePos)
{		
	if (m_image.position.x < mousePos.x && m_image.position.x + m_image.width > mousePos.x &&
		m_image.position.y < mousePos.y && m_image.position.y + m_image.height > mousePos.y)
	{	
		m_selectFrame.renderFlag = true;
		return true;
	}	
	else
	{	
		m_selectFrame.renderFlag = false;
		return false;
	}	
}	