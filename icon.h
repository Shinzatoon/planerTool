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
	int id;//�ŗL�ԍ�
	Image image;
	Image selectFrame;
	int iconType;
	bool pressed;//��������Ă���
	bool enableFrame;//�t���[���L��
public:
	bool canDuplicate;//�����\
	Icon();
	~Icon();

	void initialize(int iconType, VECTOR2 pos,int id,float rotation);
	void initialize(int iconType);

	void draw();

	void update();
	bool exportUpdate();
	bool onCursor();
	void makePressed();//������Ԃɂ���
	void makeRelease();//�����Ԃɂ���
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
	float getAngle() { return image.angle; }
	int getID() { return id; }
	int getType() { return iconType; }


	VECTOR2 getPos() { return VECTOR2(image.position.x, image.position.y); };

};	