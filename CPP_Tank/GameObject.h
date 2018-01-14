#pragma once

#include "MapObject.h"
#include "DrawObject.h"
#include "TankObject.h"
#include "BulletObject.h"

//��������;
#pragma comment(lib, "Winmm.lib")   

#include <vector>
using std::vector;

//����̹��;�ӵ�;
class CBulletObject;
class CTankObject;

//���ֽṹ��;
typedef struct _TEXTNODE
{
	int mPosX;
	int mPosY;
}TEXTNODE;

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	void InterFace();		//�볡����;
	void Welcome();			//ѡ��˵�;

private:
	bool StartGame();		//��Ϸ����;
	void KillBGM();			//ɱ����Ч;
	void Victory();			//ʤ��;
	void GameOver();		//ʧ��;
	void RestData();		//�������;

	void SaveData();		//�浵;
	void ReadData();		//����;

	void PlayerA();			//���A����;
	void PlayerB();			//���B����;
	void NPCAction();		//NPC����;
	void BulletAction();	//�ӵ�����;

	bool IniTank();			//��ʼ��̹��;
	bool SetWindowsInfo(char *pTitle, short nWidth, short nHeight);	//���ÿ���̨��Ϣ;
private:
	int PlayerACount;						//���A������;���Ʒ����ӵ��ٶ�;
	int PlayerBCount;						//���B������;���Ʒ����ӵ��ٶ�;

	bool m_bData;							//������־;
	bool m_bDouble;							//˫��ģʽ;
	int m_nRound;							//�ؿ�;
	int m_nEnemy;							//��������;

	CMapObject m_nMapObject;				//��ͼ;

	int m_nTank;							//̹������;�浵����ʹ��;
	vector<CTankObject> m_vecTankObject;	//̹����;
	int m_nBullet;							//�ӵ�����;�浵����ʹ��;
	vector<CBulletObject> m_vecBulletObject;//�ӵ���;
	vector<TEXTNODE> TextTank;				//TANK������;
};

