#pragma once
	
#include "Image.h"
	
enum ICON_TYPE
{
	EXPORT_ICON,
	ENEMY_ICON,
	PLAYER_ICON,
	STAR_ICON,
};
	
class Icon
{
private:
	Image m_image;
	Image m_selectFrame;
	VECTOR2 defaultSize;
	VECTOR2 defaultPos;
	bool m_onCursor;
	bool m_shrinked;//拡大されている
public:
	Icon();
	~Icon();

	void initialize(int iconType, VECTOR2 pos);
	void initialize(int iconType);

	void draw();

	void update();

	bool onCursor(VECTOR2 mousePos);
	void shrink();//縮小
	void reSize();//元の大きさに戻す
	void setPos(VECTOR2 pos) {
		setPosition(&m_image, pos.x, pos.y);
	};//

	VECTOR2 getPos() { return VECTOR2(m_image.position.x, m_image.position.y); };

};	