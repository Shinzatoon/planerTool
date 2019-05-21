#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "messageDialog.h"
#include "inputDialog.h"

MessageDialog mDialog;
InputDialog inDialog;
int i = 100;
const int BUF_SIZE = 255;
static char buffer[BUF_SIZE];

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
};
void updateStage() {
	inDialog.update();
	mDialog.update();
	if (getMouseMButton())
	{
		inDialog.print("please InputText");
	}
};
void drawStage() {
	inDialog.draw();
	//mDialog.draw();
};

void printStage() {
	//printTextDX(getDebugFont(), "Stage", 0, 0);

	/*_snprintf_s(buffer, BUF_SIZE, "%d", i);
	printTextDX(getDebugFont(), buffer, 0, 0);*/
	printTextDX(getDebugFont(), getTextIn(), 0, 0);
	
	printTextDX(getDebugFont(), "マウス中ボタンを押下で入力ダイアログボックスを表示する", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());
};
void unInitializeStage() {};