#pragma once
	
#include "Image.h"
	
enum ICON_TYPE
{
	EDITER_AREA,
	PROPERTY_AREA,
	EXPORT,
	ENEMY,
	PLAYER,
	STAR,
	ICON_NUM
};

namespace iconNS
{
	struct IconParam { float x, y, width, height; D3DXCOLOR color; };
	const IconParam PARAMETER[ICON_NUM] =
	{
		{285, 60, 900, 675,colorNS::LTGRAY},  //EDITER_AREA
		{1215, 45, 210, 720,colorNS::NAVY},  //PROPERTY_AREA
		{10, 10, 96, 32,colorNS::WHITE},  //EXPORT
		{10, 100, 32, 32,colorNS::WHITE}, //ENEMY
		{10, 200, 32, 32,colorNS::WHITE}, //PLAYER
		{10, 300, 32, 32,colorNS::WHITE}, //STAR
	};
}

class Icon
{
private:
	int id;//固有番号
	Image image;
	Image selectFrame;
	int iconType;
	bool shrinked;//拡大されている
	bool enableFrame;//フレーム有効
public:
	bool canDuplicate;//複製可能
	Icon();
	~Icon();

	void initialize(int iconType, VECTOR2 pos,int id,float rotation);
	void initialize(int iconType);

	void draw();

	void update();
	void buttonUpdate();
	bool onCursor();
	void shrink();//縮小
	void reSize();//元の大きさに戻す
	void setPos(VECTOR2 pos) {
		setPosition(&image, pos.x, pos.y);
		if(enableFrame)setPosition(&selectFrame, pos.x, pos.y);
	};
	float getWidth() { return image.width; }
	float getHeight() { return image.height; }
	float getLeft() { return image.position.x; }
	float getRight() { return image.position.x+image.width; }
	float getTop() { return image.position.y; }
	float getBottom() { return image.position.y+image.height; }
	int getID() { return id; }

	VECTOR2 getPos() { return VECTOR2(image.position.x, image.position.y); };

};	