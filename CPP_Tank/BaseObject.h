#pragma once

class CBaseObject
{
public:
	CBaseObject();
	virtual ~CBaseObject();
	virtual bool DrawObject() = 0;		//���ƶ���;
	virtual bool ClsObject() = 0;		//��������;
};

