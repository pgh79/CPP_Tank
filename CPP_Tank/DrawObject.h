#pragma once
#include <windows.h>

class CDrawObject
{
public:
	CDrawObject();
	~CDrawObject();
	static bool DrawPencil(short nPosX, short nPosY, char* pStr, WORD Color);	//�����ַ�;
	static bool DrawPencil(short nPosX, short nPosY, int nNum, WORD Color);		//��������;
};

