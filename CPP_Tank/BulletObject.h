#pragma once

#include "BaseObject.h"
#include "MapObject.h"
#include "TankObject.h"
#include "GameObject.h"

#include <vector>
using std::vector;

//����̹��;
class CTankObject;

class CBulletObject :
	public CBaseObject
{
public:
	CBulletObject()=default;							//Ĭ�Ϲ��캯��;
	CBulletObject(const CTankObject &TankObject);		//�����ӵ�;
	~CBulletObject();

	bool DrawObject();									//�����ӵ�;
	bool ClsObject();									//�����ӵ�;


	bool BulletFly( vector<CTankObject>& vecTank,  vector<CBulletObject>& vecBullet);			//���ӵ���;
	bool BulletCollisio( vector<CTankObject>& vecTank,  vector<CBulletObject>& vecBullet);		//�ӵ���ײ���;
	void BulletCrit();																			//�ӵ�����Ч��;һ�δ�һ������;

	bool operator=(const CTankObject& TankObject);					//�Ⱥ�����;��̹����Ϣ��ֵ���ӵ�;
	bool operator==(CTankObject & TankObject);						//����==;�Ա�̹����Ϣ;
	bool operator==(CBulletObject & BulletObject);					//����==;�Ա��ӵ���Ϣ;

	void SetMapObject(CMapObject* val) { m_pMapObject = val; }		//���õ�ͼֵ;���ڶ���;
public:
	bool GetIsDie() const { return m_bIsDie; }						//��ȡ������Ϣ;
	bool GetGroup() const { return m_bGroup; }						//��ȡ��Ӫ;
	int GetPosX() const { return m_nPosX; }							//��ȡX����;
	int GetPosY() const { return m_nPosY; }							//��ȡY����;
	int GetDir() const { return m_nDir; }							//��ȡ����;
	int GetID() const { return m_nID; }								//��ȡID;
	int GetLevel() const { return m_nLevel; }						//��ȡ�ȼ�;
	int GetSpeed() const { return m_nSpeed; }						//��ȡ�ٶ�;

private:
	bool m_bIsDie;	//������Ϣ;
	bool m_bGroup;	//��Ӫ;
	int m_nPosX;	//����X;
	int m_nPosY;	//����Y
	int m_nDir;		//����;
	int m_nID;		//ID��
	int m_nLevel;	//�ȼ�;
	int m_nSpeed;	//�ٶ�;
	CMapObject* m_pMapObject;//��ͼ;
};

