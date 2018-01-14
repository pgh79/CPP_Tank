#include "stdafx.h"
#include "DrawObject.h"

#include <iostream>
using std::cout;

CDrawObject::CDrawObject()
{
}


CDrawObject::~CDrawObject()
{
}

//****************************************************************
// Brief 	: 绘制字符;
// Method	: DrawPencil
// FullName	: CDrawObject::DrawPencil
// Access	: public 
// Returns	: bool
// Parameter: short nPosX
// Parameter: short nPosY
// Parameter: char * pStr
// Parameter: WORD Color
//****************************************************************

bool CDrawObject::DrawPencil(short nPosX, short nPosY, char* pStr, WORD Color)
{
	//获取句柄;
	HANDLE sh = GetStdHandle(STD_OUTPUT_HANDLE);

	//设置坐标信息;
	COORD ps;
	ps = { nPosX * 2,nPosY };
	SetConsoleCursorPosition(sh, ps);

	//设置颜色;
	SetConsoleTextAttribute(sh,Color);

	cout << pStr;

	return true;
}


//****************************************************************
// Brief 	: 绘制数字;
// Method	: DrawPencil
// FullName	: CDrawObject::DrawPencil
// Access	: public 
// Returns	: bool
// Parameter: short nPosX
// Parameter: short nPosY
// Parameter: int nNum
// Parameter: WORD Color
//****************************************************************

bool CDrawObject::DrawPencil(short nPosX, short nPosY, int nNum, WORD Color)
{
	//获取句柄;
	HANDLE sh = GetStdHandle(STD_OUTPUT_HANDLE);

	//设置坐标信息;
	COORD ps;
	ps = { nPosX * 2,nPosY };
	SetConsoleCursorPosition(sh, ps);

	//设置颜色;
	SetConsoleTextAttribute(sh, Color);

	cout << nNum<<" ";

	return true;
}
