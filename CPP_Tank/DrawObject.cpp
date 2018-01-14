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
// Brief 	: �����ַ�;
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
	//��ȡ���;
	HANDLE sh = GetStdHandle(STD_OUTPUT_HANDLE);

	//����������Ϣ;
	COORD ps;
	ps = { nPosX * 2,nPosY };
	SetConsoleCursorPosition(sh, ps);

	//������ɫ;
	SetConsoleTextAttribute(sh,Color);

	cout << pStr;

	return true;
}


//****************************************************************
// Brief 	: ��������;
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
	//��ȡ���;
	HANDLE sh = GetStdHandle(STD_OUTPUT_HANDLE);

	//����������Ϣ;
	COORD ps;
	ps = { nPosX * 2,nPosY };
	SetConsoleCursorPosition(sh, ps);

	//������ɫ;
	SetConsoleTextAttribute(sh, Color);

	cout << nNum<<" ";

	return true;
}
