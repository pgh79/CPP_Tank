#pragma once
#include "BaseObject.h"
#include "MapObject.h"
#include "GameObject.h"
#include <vector>
using std::vector;

class CBulletObject;

class CTankObject :
	public CBaseObject
{
public:
	CTankObject() = default;															//Ĭ�Ϲ��캯��;
	CTankObject(int PosX,int PosY,int Dir,bool Group,int ID,CMapObject* Object);		//��ʼ��̹��;
	~CTankObject();													
	bool DrawObject();																	//����̹��;
	bool ClsObject();																	//����̹��;
	bool MoveTank(int nDir);															//̹���ƶ�;
	bool MoveNpc(const vector<CTankObject>& vecTank,vector<CBulletObject>& vecBullet);	//NPC�ƶ�;
	bool Search();													//NPC����;ʮ��Ѱ·;
	
	bool TankCollision();											//̹����ײ;
	void SetLevel(int val) { m_nLevel = val; }						//����̹�˵ȼ�;
	void SetScores(int val) { m_nScores = val; }					//���ӷ���;
	void SetWade(bool val) { m_bWade = val; }						//��ˮ״̬;
	CMapObject* GetMapObject() const { return m_pMapObject; }		//��ȡ��ͼ;��ֵ���ӵ�;
	void SetMapObject(CMapObject* val) { m_pMapObject = val; }		//���õ�ͼ;������;		
	
public:	
	void SetIsDie(bool val) { m_bIsDie = val; }			//����������Ϣ;
	bool GetIsDie() const { return m_bIsDie; }			//��ȡ������Ϣ;
	bool GetGroup() const { return m_bGroup; }			//��Ӫ;
	int GetPosX() const { return m_nPosX; }				//X����;
	int GetPosY() const { return m_nPosY; }				//Y����;
	int GetDir() const { return m_nDir; }				//����;
	int GetLevel() const { return m_nLevel; }			//�ȼ�;
	int GetScores() const { return m_nScores; }			//����;
	int GetSpeed() const { return m_nSpeed; }			//�ٶ�;
	int GetID() const { return m_nID; }					//ID;

private:
	bool m_bIsDie;		//����;
	bool m_bGroup;		//��Ӫ;
	int m_nPosX;		//X����;
	int m_nPosY;		//Y����;
	int m_nDir;			//����;
	int m_nID;			//ID;
	int m_nLevel;		//�ȼ�;
	int m_nSpeed;		//�ٶ�;		
	int m_nScores;		//����;

	bool m_bWade;		//��ˮģʽ;
	int NPCCount;							//NPC������;����NPC�����ӵ��ٶ�;
	CMapObject* m_pMapObject;				//��ͼ;
	static const int m_TankShape[4][3][3];	//̹��ͼ��;
	static const int m_ColorPlayer[3];		//�����ɫ;
	static const int m_ColorNPC[3];			//NPC��ɫ;
	static const int m_TankSpeed[3];		//�ٶȿ���;�ȼ���Ϊ�±�;
};
