#include "icon.h"
#include "textureLoader.h"
#include "input.h"
using namespace iconNS;
Icon::Icon()
{
	shrinked = false;
}	
Icon::~Icon()
{
	UninitImage(&image);
}

void Icon::initialize(int _iconType, VECTOR2 pos, int id, float rotation)
{
	initialize(_iconType);
	setPosition(&image, pos.x, pos.y);
	setAngle(&image, rotation);

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
		canDuplicate = false;//複製不可
		texture = NULL;//テクスチャなし
		initializeMethod = COLOR;//初期化モードカラー
		enableFrame = false;//フレーム無効化
		break;
	}
	//[アイコン表示画像本体の初期化]
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
	
	//[選択表記フレーム画像の初期化]
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
	if(iconType == EXPORT)buttonUpdate();
}	

void Icon::buttonUpdate()
{
	if (onCursor())
	{//書き出しボタンにカーソルがあった場合
		if (getMouseLButton())
		{//左クリック時
			shrink();//拡大状態にする
		}
		else {
			reSize();//元の大きさに戻す
		}
	}
	else
	{//カーソルがボタン外の場合
		reSize();//元の大きさに戻す
	}
}

void Icon::shrink()
{//ボタン縮小
	if (shrinked)return;
	changeTexture(&image, 1);//1番に切替
	shrinked = true;
}

void Icon::reSize()
{//元の大きさに戻す
	if (!shrinked)return;
	changeTexture(&image, 0);//0番テクスチャに切替
	shrinked = false;
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