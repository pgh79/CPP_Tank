#pragma once

#include "MapObject.h"
#include "DrawObject.h"
#include "TankObject.h"
#include "BulletObject.h"

//播放音乐;
#pragma comment(lib, "Winmm.lib")   

#include <vector>
using std::vector;

//声明坦克;子弹;
class CBulletObject;
class CTankObject;

//文字结构体;
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

	void InterFace();		//入场动画;
	void Welcome();			//选项菜单;

private:
	bool StartGame();		//游戏主体;
	void KillBGM();			//杀敌音效;
	void Victory();			//胜利;
	void GameOver();		//失败;
	void RestData();		//清空数据;

	void SaveData();		//存档;
	void ReadData();		//读档;

	void PlayerA();			//玩家A操作;
	void PlayerB();			//玩家B操作;
	void NPCAction();		//NPC动作;
	void BulletAction();	//子弹动作;

	bool IniTank();			//初始化坦克;
	bool SetWindowsInfo(char *pTitle, short nWidth, short nHeight);	//设置控制台信息;
private:
	int PlayerACount;						//玩家A计数器;控制发射子弹速度;
	int PlayerBCount;						//玩家B计数器;控制发射子弹速度;

	bool m_bData;							//读档标志;
	bool m_bDouble;							//双人模式;
	int m_nRound;							//关卡;
	int m_nEnemy;							//敌人数量;

	CMapObject m_nMapObject;				//地图;

	int m_nTank;							//坦克数量;存档读档使用;
	vector<CTankObject> m_vecTankObject;	//坦克组;
	int m_nBullet;							//子弹数量;存档读档使用;
	vector<CBulletObject> m_vecBulletObject;//子弹组;
	vector<TEXTNODE> TextTank;				//TANK文字组;
};

