#include "stdafx.h"
#include "GameObject.h"
#include "TankObject.h"
#include "MapObject.h"
#include "BulletObject.h"

#include <iostream>
#include <time.h>
#include <conio.h>
#include <atlstr.h>

using std::cout;

//声明子弹;
class CBulletObject;

//获取按键;
#define KEY_DOWN(key) (GetAsyncKeyState(key) & 0x8000) ? (1) : (0)


CGameObject::CGameObject()
{
	m_nRound = 1;

	//TANK
	TextTank.emplace_back(TEXTNODE{ 10,10 });
	TextTank.emplace_back(TEXTNODE{ 11,10 });
	TextTank.emplace_back(TEXTNODE{ 12,10 });
	TextTank.emplace_back(TEXTNODE{ 13,10 });
	TextTank.emplace_back(TEXTNODE{ 14,10 });
	TextTank.emplace_back(TEXTNODE{ 15,10 });
	TextTank.emplace_back(TEXTNODE{ 16,10 });
	TextTank.emplace_back(TEXTNODE{ 13,11 });
	TextTank.emplace_back(TEXTNODE{ 13,12 });
	TextTank.emplace_back(TEXTNODE{ 13,13 });
	TextTank.emplace_back(TEXTNODE{ 13,14 });
	TextTank.emplace_back(TEXTNODE{ 13,15 });
	TextTank.emplace_back(TEXTNODE{ 13,16 });
	TextTank.emplace_back(TEXTNODE{ 13,17 });


	TextTank.emplace_back(TEXTNODE{ 27,10 });	//A
	TextTank.emplace_back(TEXTNODE{ 26,11 });
	TextTank.emplace_back(TEXTNODE{ 27,11 });
	TextTank.emplace_back(TEXTNODE{ 28,11 });
	TextTank.emplace_back(TEXTNODE{ 26,12 });
	TextTank.emplace_back(TEXTNODE{ 28,12 });
	TextTank.emplace_back(TEXTNODE{ 25,13 });
	TextTank.emplace_back(TEXTNODE{ 29,13 });
	TextTank.emplace_back(TEXTNODE{ 25,14 });
	TextTank.emplace_back(TEXTNODE{ 26,15 });
	TextTank.emplace_back(TEXTNODE{ 27,15 });
	TextTank.emplace_back(TEXTNODE{ 28,15 });
	TextTank.emplace_back(TEXTNODE{ 29,14 });
	TextTank.emplace_back(TEXTNODE{ 24,15 });
	TextTank.emplace_back(TEXTNODE{ 30,15 });
	TextTank.emplace_back(TEXTNODE{ 24,16 });
	TextTank.emplace_back(TEXTNODE{ 30,16 });
	TextTank.emplace_back(TEXTNODE{ 24,17 });
	TextTank.emplace_back(TEXTNODE{ 30,17 });


	TextTank.emplace_back(TEXTNODE{ 45,10 });	//N
	TextTank.emplace_back(TEXTNODE{ 45,11 });
	TextTank.emplace_back(TEXTNODE{ 45,12 });
	TextTank.emplace_back(TEXTNODE{ 45,13 });
	TextTank.emplace_back(TEXTNODE{ 45,14 });
	TextTank.emplace_back(TEXTNODE{ 45,15 });
	TextTank.emplace_back(TEXTNODE{ 45,16 });
	TextTank.emplace_back(TEXTNODE{ 45,17 });
	TextTank.emplace_back(TEXTNODE{ 44,16 });
	TextTank.emplace_back(TEXTNODE{ 43,14 });
	TextTank.emplace_back(TEXTNODE{ 43,15 });
	TextTank.emplace_back(TEXTNODE{ 42,12 });
	TextTank.emplace_back(TEXTNODE{ 42,13 });
	TextTank.emplace_back(TEXTNODE{ 41,11 });
	TextTank.emplace_back(TEXTNODE{ 40,10 });
	TextTank.emplace_back(TEXTNODE{ 40,11 });
	TextTank.emplace_back(TEXTNODE{ 40,12 });
	TextTank.emplace_back(TEXTNODE{ 40,13 });
	TextTank.emplace_back(TEXTNODE{ 40,14 });
	TextTank.emplace_back(TEXTNODE{ 40,15 });
	TextTank.emplace_back(TEXTNODE{ 40,16 });
	TextTank.emplace_back(TEXTNODE{ 40,17 });

	TextTank.emplace_back(TEXTNODE{ 56,10 });	//K
	TextTank.emplace_back(TEXTNODE{ 56,11 });
	TextTank.emplace_back(TEXTNODE{ 56,12 });
	TextTank.emplace_back(TEXTNODE{ 56,13 });
	TextTank.emplace_back(TEXTNODE{ 56,14 });
	TextTank.emplace_back(TEXTNODE{ 56,15 });
	TextTank.emplace_back(TEXTNODE{ 56,16 });
	TextTank.emplace_back(TEXTNODE{ 56,17 });
	TextTank.emplace_back(TEXTNODE{ 60,10 });
	TextTank.emplace_back(TEXTNODE{ 59,11 });
	TextTank.emplace_back(TEXTNODE{ 58,12 });
	TextTank.emplace_back(TEXTNODE{ 57,13 });
	TextTank.emplace_back(TEXTNODE{ 57,14 });
	TextTank.emplace_back(TEXTNODE{ 58,15 });
	TextTank.emplace_back(TEXTNODE{ 59,16 });
	TextTank.emplace_back(TEXTNODE{ 60,17 });
}


CGameObject::~CGameObject()
{
}

//****************************************************************
// Brief 	: 开场动画;
// Method	: InterFace
// FullName	: CGameObject::InterFace
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::InterFace()
{
	//设置窗口信息;
	SetWindowsInfo("CPP_Tank_By_D&K", 151, 51);

	int nLength = TextTank.size();

	//将文字移出界面;
	for (int i = 0; i < nLength; i++)
	{
		TextTank[i].mPosY += 40;
	}

	//TANK进场;
	//坐标移动至指定位置[10]结束进场动画;
	while (!(TextTank[0].mPosY == 10))
	{
		//每次向上移动1;
		for (int i = 0; i < nLength; i++)
		{
			TextTank[i].mPosY -= 1;
		}

		system("color 0A");
		system("cls");

		for (int i = 0; i < nLength; i++)
		{
			if (TextTank[i].mPosY > 49)
			{
				continue;
			}
			CDrawObject::DrawPencil(TextTank[i].mPosX, TextTank[i].mPosY, TANKNODE, COLOUR_A);
		}

		Sleep(50);
	}

	//TANK闪烁;
	for (int m = 0; m < 2; m++)
	{

		for (int i = 0; i < nLength; i++)
		{
			CDrawObject::DrawPencil(TextTank[i].mPosX, TextTank[i].mPosY, TANKNODE, COLOUR_A);
		}
		Sleep(200);
		for (int i = 0; i < nLength; i++)
		{
			CDrawObject::DrawPencil(TextTank[i].mPosX, TextTank[i].mPosY, M_CLEAR, COLOUR_A);
		}
		Sleep(200);
	}

	for (int i = 0; i < nLength; i++)
	{
		CDrawObject::DrawPencil(TextTank[i].mPosX, TextTank[i].mPosY, TANKNODE, COLOUR_A);
	}

	return;
}

//****************************************************************
// Brief 	: 欢迎界面;
// Method	: Welcome
// FullName	: CGameObject::Welcome
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::Welcome()
{

	system("color 0A");
	system("cls");

	for ( unsigned int i = 0; i < TextTank.size(); i++)
	{
		CDrawObject::DrawPencil(TextTank[i].mPosX, TextTank[i].mPosY, TANKNODE, COLOUR_A);
	}

	mciSendString(L"play sound\\bgmwelcom.mp3 repeat", NULL, 0, NULL);

	
	//初始化菜单;
	CDrawObject::DrawPencil(31, 24, "上下键选择  回车确认", COLOUR_A);

	CDrawObject::DrawPencil(31, 28, SELECT, COLOUR_E);
	CDrawObject::DrawPencil(33, 28, "开 始 游 戏", COLOUR_A);
	CDrawObject::DrawPencil(33, 31, "双 人 模 式", COLOUR_A);
	CDrawObject::DrawPencil(33, 34, "读 取 存 档", COLOUR_A);
	CDrawObject::DrawPencil(33, 37, "设 计 地 图", COLOUR_A);

	//选择列表;
	int ch;
	int key = 1;
	bool Tflag = false;
	while (ch = _getch())
	{
		switch (ch)
		{
			//上方向;
		case'W':
		case'w':
		case 72:			
			if (key > 1)
			{				
				switch (key)
				{
				case 2:					
					CDrawObject::DrawPencil(31, 31, M_CLEAR, COLOUR_A);
					CDrawObject::DrawPencil(31, 28, SELECT, COLOUR_E);
					key--;
					break;
				case 3:					
					CDrawObject::DrawPencil(31, 34, M_CLEAR, COLOUR_A);
					CDrawObject::DrawPencil(31, 31, SELECT, COLOUR_E);
					key--;
					break;
				case 4:					
					CDrawObject::DrawPencil(31, 37, M_CLEAR, COLOUR_A);
					CDrawObject::DrawPencil(31, 34, SELECT, COLOUR_E);				
					key--;
					break;
				}
			}
			break;
			//下方向;
		case 'S':
		case's':
		case 80:			
			if (key < 4)
			{	
				switch (key)
				{
				case 1:					
					CDrawObject::DrawPencil(31, 28, M_CLEAR, COLOUR_A);
					CDrawObject::DrawPencil(31, 31, SELECT, COLOUR_E);
					key++;
					break;
				case 2:					
					CDrawObject::DrawPencil(31, 31, M_CLEAR, COLOUR_A);
					CDrawObject::DrawPencil(31, 34, SELECT, COLOUR_E);
					key++;
					break;
				case 3:					
					CDrawObject::DrawPencil(31, 34, M_CLEAR, COLOUR_A);
					CDrawObject::DrawPencil(31, 37, SELECT, COLOUR_E);
					key++;
					break;
				}
			}
			break;
		case 13:
			//Move
			mciSendString(L"play sound\\bang.mp3", NULL, 0, NULL);
			Tflag = true;
			break;
		}
		if (Tflag)
		{
			break;
		}
	}
	//停止播放菜单背景音乐;
	mciSendString(L"stop sound\\bgmwelcom.mp3", NULL, 0, NULL);

	switch (key)
	{
	case 1:
		m_bDouble = false;
		m_bData = false;
		m_nEnemy = 10;
		if (m_nRound)
		{
			m_nRound = 1;;	//绘制地图时Round为0跳过;
		}
		//游戏主体;		
		StartGame();
		break;
	case 2:
		m_bDouble = true;
		m_bData = false;
		m_nEnemy = 20;
		if (m_nRound)
		{
			m_nRound = 1;;	//绘制地图时Round为0跳过;
		}
		//游戏主体;
		StartGame();
		break;
	case 3:
		ReadData();
		break;
	case 4:
		//DIY地图;
		m_nMapObject.DIYMap();
		m_nRound = 0;
		Welcome();
		break;;
	default:
		break;
	}
}

//****************************************************************
// Brief 	: 游戏主体;
// Method	: StartGame
// FullName	: CGameObject::StartGame
// Access	: public 
// Returns	: bool
//****************************************************************

bool CGameObject::StartGame()
{	
	//读档后跳过;
	if (!m_bData)
	{
		m_nMapObject.ReadMap(m_nRound);
		IniTank();
	}

	m_nMapObject.DrawMap();
	m_nMapObject.DrawGanmeInfo();
	m_vecTankObject[0].DrawObject();

	if (m_bDouble)
	{
		m_vecTankObject[1].SetIsDie(true);
		m_vecTankObject[1].SetLevel(1);
		m_vecTankObject[1].DrawObject();
	}
	
	m_nMapObject.DrawScore(m_nRound, m_nEnemy);
	m_nMapObject.DrawScore(m_vecTankObject);

	//恢复读档状态;
	if (m_bData)
	{
		m_bData = false;
	}

	//BGM
	mciSendString(L"play sound\\30.mp3", NULL, 0, NULL);

	//敌军还有5秒到达战场;
	Sleep(3000);

	mciSendString(L"play sound\\bgm.mp3 repeat", NULL, 0, NULL);


	clock_t tPlayerA = clock(),
			tPlayerB = clock(),
			tTankNPC = clock(),
			tBullet  = clock();

	while (true)
	{
		
		
		//玩家A移动;
		if (clock() - tPlayerA > m_vecTankObject[0].GetSpeed() 
			&& m_vecTankObject[0].GetIsDie())
		{
			PlayerA();
			tPlayerA = clock();
		}

		

		//玩家B移动;
		if (clock() - tPlayerB > m_vecTankObject[1].GetSpeed()
			&& m_vecTankObject[1].GetIsDie())
		{
			PlayerB();
			tPlayerB = clock();
		}

	
		//移动TankNPC;
		if (clock()-tTankNPC>100)
		{
			NPCAction();
			tTankNPC = clock();
		}



		//子弹移动;
		if (clock()-tBullet>50)
		{
			BulletAction();
			tBullet = clock();
		}


		//玩家GG!
		if (!m_vecTankObject[0].GetIsDie() &&
			!m_vecTankObject[1].GetIsDie())
		{
			GameOver();
		}

		//玩家胜利;
		if (m_nEnemy == 0)
		{
			Victory();
		}
	}

	return true;
}


//****************************************************************
// Brief 	: 玩家A操作!
// Method	: PlayerA
// FullName	: CGameObject::PlayerA
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::PlayerA()
{
	if (KEY_DOWN('W'))
		m_vecTankObject[0].MoveTank(DIR_UP);
	else if (KEY_DOWN('S'))
		m_vecTankObject[0].MoveTank(DIR_DW);
	else if (KEY_DOWN('A'))
		m_vecTankObject[0].MoveTank(DIR_LF);
	else if (KEY_DOWN('D'))
		m_vecTankObject[0].MoveTank(DIR_RH);
	//B键存档;
	else if (KEY_DOWN('B'))
	{
		SaveData();
		//弹窗;
		int mBoxID = MessageBoxA(NULL, "存档成功！\n点击【确定】继续游戏！\n点击【取消】离开游戏!", "V!", MB_OKCANCEL);
		if (mBoxID == IDOK)
		{
			;
		}
		else if (mBoxID == IDCANCEL)
		{
			exit(0);
		}
	}
	//ESC返回主菜单;
	else if (KEY_DOWN(VK_ESCAPE))
	{
		mciSendString(L"stop sound\\bgm.mp3", NULL, 0, NULL);
		RestData();
		Welcome();
	}

	//通过计数器限制发射速度;
	this->PlayerACount++;

	if ((KEY_DOWN('J'))&&this->PlayerACount>
		(6- m_vecTankObject[0].GetLevel()*2))
	{
		CBulletObject BulletObject(m_vecTankObject[0]);
		m_vecBulletObject.push_back(BulletObject);
		this->PlayerACount = 0;
	}
}

//****************************************************************
// Brief 	: 玩家B操作;
// Method	: PlayerB
// FullName	: CGameObject::PlayerB
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::PlayerB()
{
	if (KEY_DOWN(VK_UP))
		m_vecTankObject[1].MoveTank(DIR_UP);
	else if (KEY_DOWN(VK_DOWN))
		m_vecTankObject[1].MoveTank(DIR_DW);
	else if (KEY_DOWN(VK_LEFT))
		m_vecTankObject[1].MoveTank(DIR_LF);
	else if (KEY_DOWN(VK_RIGHT))
		m_vecTankObject[1].MoveTank(DIR_RH);
	//发射;
	this->PlayerBCount++;
	if ((KEY_DOWN(VK_NUMPAD0)) && this->PlayerBCount >
			(6 - m_vecTankObject[0].GetLevel() * 2))
	{
		CBulletObject BulletObject(m_vecTankObject[1]);
		m_vecBulletObject.push_back(BulletObject);
		PlayerBCount = 0;
	}
}

//****************************************************************
// Brief 	: 操作NPC;
// Method	: MoveNPC
// FullName	: CGameObject::MoveNPC
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::NPCAction()
{
	for (unsigned int i = 2; i < m_vecTankObject.size();)
	{
		if (m_vecTankObject[i].GetIsDie())
		{
			m_vecTankObject[i].MoveNpc(m_vecTankObject,m_vecBulletObject);			
			i++;
		}
		else
		{
			//删除NPC;
			m_vecTankObject.erase(m_vecTankObject.begin() + i);
			m_nEnemy -= 1;		
			KillBGM();
			//刷新BUFF;
			m_nMapObject.Buff();

			//更新敌人数量;
			m_nMapObject.DrawScore(m_nRound, m_nEnemy);

			if (m_nEnemy > 2)
			{
				//NPC重生;
				int nTemp = rand() % 3;
				switch (nTemp)
				{
				case 0:
				{
					CTankObject NPC(2, 2, DIR_DW, false, 12, &m_nMapObject);
					NPC.SetLevel(rand() % 3);
					m_vecTankObject.push_back(NPC);
				}
				break;
				case 1:
				{
					CTankObject NPC(30, 2, DIR_DW, false, 13, &m_nMapObject);
					NPC.SetLevel(rand() % 3);
					m_vecTankObject.push_back(NPC);
				}
				break;
				case 2:
				{
					CTankObject NPC(57, 2, DIR_DW, false, 14, &m_nMapObject);
					NPC.SetLevel(rand() % 3);
					m_vecTankObject.push_back(NPC);
				}
				break;
				}
			}
		}
	}
	return;
}

//****************************************************************
// Brief 	: 子弹事件;
// Method	: BulletAction
// FullName	: CGameObject::BulletAction
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::BulletAction()
{
	for (unsigned int i = 0; i < m_vecBulletObject.size(); )
	{
		if (m_vecBulletObject[i].GetIsDie())
		{
			//移动有效子弹;
			m_vecBulletObject[i].BulletFly(m_vecTankObject, m_vecBulletObject);
			i++;
		}
		else
		{
			//删除无效子弹;
			m_vecBulletObject.erase(m_vecBulletObject.begin() + i);
		}
	}
}

//****************************************************************
// Brief 	: 杀敌音效;
// Method	: KillBGM
// FullName	: CGameObject::KillBGM
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::KillBGM()
{
	//随机播放人物音效;
	int nTemp = rand() % 5;

	char BgmBuf[30] = { 0 };
	sprintf_s(BgmBuf, sizeof(BgmBuf), "play sound\\%d.mp3", nTemp);

	CString string = BgmBuf;

	//GG BGM
	mciSendString(string, NULL, 0, NULL);
}

//****************************************************************
// Brief 	: 玩家V！
// Method	: Victory
// FullName	: CGameObject::Victory
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::Victory()
{
	mciSendString(L"stop sound\\bgm.mp3", NULL, 0, NULL);
	//胜利BGM
	mciSendString(L"play sound\\victor.mp3", NULL, 0, NULL);


	//通关;
	if (m_nRound == 3)
	{
		//弹窗;
		int mBoxID = MessageBoxA(NULL, "恭喜你挑战完成！", "V!", MB_OKCANCEL);
		if (mBoxID == IDOK)
		{
			m_nRound = 1;
			Welcome();
		}
		else if (mBoxID == IDCANCEL)
		{
			exit(0);
		}

	}

	int nTemp = m_vecTankObject[0].GetScores();
	int nTemp2 = m_vecTankObject[1].GetScores();

	//格式化字符串;
	CStringA string;
	if (m_bDouble)
	{
		string.Format("Good Game !\nP1此次得分为：%d \nP2此次得分为：%d \n\n点击【确定】挑战下一关！\n点击【取消】离开游戏！\n", nTemp, nTemp2);
	}
	else
	{
		string.Format("Good Game !\nP1此次得分为：%d \n\n点击【确定】挑战下一关！\n点击【取消】离开游戏！\n", nTemp);
	}

	RestData();

	//弹窗;
	int mBoxID = MessageBoxA(NULL, string, "V!", MB_OKCANCEL);
	if (mBoxID == IDOK)
	{
		//关数加1；
		if (m_nRound < 3)
		{
			m_nRound += 1;
		}
		StartGame();
	}
	else if (mBoxID == IDCANCEL)
	{
		exit(0);
	}

}

//****************************************************************
// Brief 	: 玩家GG！
// Method	: GameOver
// FullName	: CGameObject::GameOver
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::GameOver()
{
	mciSendString(L"stop sound\\bgm.mp3", NULL, 0, NULL);
	//GG BGM
	mciSendString(L"play sound\\gg.mp3", NULL, 0, NULL);

	int nTemp = m_vecTankObject[0].GetScores();
	int nTemp2 = m_vecTankObject[1].GetScores();
	//格式化字符串;
	CStringA string;
	if (m_bDouble)
	{
		string.Format("Game Over !\nP1此次得分为：%d \nP2此次得分为：%d \n\n点击【确定】再来一局！\n点击【取消】离开游戏！\n", nTemp, nTemp2);
	}
	else
	{
		string.Format("Game Over !\nP1此次得分为：%d \n\n点击【确定】再来一局！\n点击【取消】离开游戏！\n", nTemp);
	}

	RestData();
	m_nRound = 1;

	//弹窗;
	int mBoxID = MessageBoxA(NULL, string, "GG!", MB_OKCANCEL);
	if (mBoxID == IDOK)
	{
		m_nRound = 1;
		Welcome();
		exit(0);
	}
	else if (mBoxID == IDCANCEL)
	{
		exit(0);
	}

}



//****************************************************************
// Brief 	: 清空数据;
// Method	: RestData
// FullName	: CGameObject::RestData
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::RestData()
{
	//数据清空;
	if (m_bDouble)
	{
		m_nEnemy = 20;
	}
	else
	{
		m_nEnemy = 10;
	}

	m_nMapObject = {};

	//清空坦克;
	m_vecTankObject.clear();
	//清空子弹;
	m_vecBulletObject.clear();

	return;

}

//****************************************************************
// Brief 	: 存档;
// Method	: SaveData
// FullName	: CGameObject::SaveData
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::SaveData()
{
	m_bData = true;

	//打开文件;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "map\\tank.db", "wb");
	if (err != 0)
	{
		return;
	}

	//写入文件;

	fwrite(&m_bData, sizeof(m_bData), 1, pFile);
	fwrite(&m_bDouble, sizeof(m_bDouble), 1, pFile);
	fwrite(&m_nRound, sizeof(m_nRound), 1, pFile);
	fwrite(&m_nEnemy, sizeof(m_nEnemy), 1, pFile);
	fwrite(&m_nMapObject, sizeof(m_nMapObject), 1, pFile);


	
	//存入坦克数量;
	m_nTank = m_vecTankObject.size();	
	fwrite(&m_nTank, sizeof(m_nTank), 1, pFile);
	//循环写入坦克;
	for (int  i = 0; i < m_nTank; i++)
	{
		fwrite(&m_vecTankObject[i], sizeof(CTankObject), 1, pFile);
	}



	//存入子弹数量;
	m_nBullet = m_vecBulletObject.size();
	fwrite(&m_nBullet, sizeof(m_nBullet), 1, pFile);
	//循环写入子弹;
	for (int i = 0; i < m_nBullet; i++)
	{
		fwrite(&m_vecBulletObject[i], sizeof(CBulletObject), 1, pFile);
	}	

	fclose(pFile);

	m_bData = false;

	return;

}

//****************************************************************
// Brief 	: 读档;
// Method	: ReadData
// FullName	: CGameObject::ReadData
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::ReadData()
{
	//打开文件;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "map\\tank.db", "rb");
	if (err != 0)
	{
		int mBoxID = MessageBoxA(NULL, "暂无存档文件！\n点击【确定】返回主菜单！\n点击【取消】退出游戏!", "读取数据出错!", MB_OKCANCEL);
		if (mBoxID == IDOK)
		{
			Welcome();
		}
		else if (mBoxID == IDCANCEL)
		{
			exit(0);
		}

		return;
	}

	//读取文件;
	fread(&m_bData, sizeof(m_bData), 1, pFile);
	fread(&m_bDouble, sizeof(m_bDouble), 1, pFile);
	fread(&m_nRound, sizeof(m_nRound), 1, pFile);
	fread(&m_nEnemy, sizeof(m_nEnemy), 1, pFile);
	fread(&m_nMapObject, sizeof(m_nMapObject), 1, pFile);



	//读取坦克数量;
	fread(&m_nTank, sizeof(m_nTank), 1, pFile);
	//循环读入坦克;
	for (int i = 0; i < m_nTank; i++)
	{
		CTankObject TankTemp;
		fread(&TankTemp, sizeof(CTankObject), 1, pFile);
		//修改地图指针;
		TankTemp.SetMapObject(&m_nMapObject);
		m_vecTankObject.push_back(TankTemp);
	}

	//读取子弹数量;
	fread(&m_nBullet, sizeof(m_nBullet), 1, pFile);
	//循环写入子弹;
	for (int i = 0; i < m_nBullet; i++)
	{
		CBulletObject BulletTemp;
		fread(&BulletTemp, sizeof(CBulletObject), 1, pFile);
		//修改地图指针;
		BulletTemp.SetMapObject(&m_nMapObject);
		m_vecBulletObject.push_back(BulletTemp);
	}

	//关闭文件;												
	fclose(pFile);

	
	//开始游戏;
	StartGame();
	return;
}

//****************************************************************
// Brief 	: 初始化坦克;
// Method	: IniTank
// FullName	: CGameObject::IniTank
// Access	: public 
// Returns	: bool
//****************************************************************

bool CGameObject::IniTank()
{
	//初始化玩家;
	CTankObject PlayerA(23, 47, DIR_UP, true, 10, &m_nMapObject);
	m_vecTankObject.push_back(PlayerA);

	CTankObject PlayerB(35, 47, DIR_UP, true, 11, &m_nMapObject);
	//玩家B默认GG！
	PlayerB.SetLevel(0);
	PlayerB.SetIsDie(false);
	m_vecTankObject.push_back(PlayerB);

	//初始化NPC;
	CTankObject NPC1(2, 2, DIR_DW, false, 12, &m_nMapObject);
	m_vecTankObject.push_back(NPC1);

	CTankObject NPC2(30,2, DIR_DW, false, 13, &m_nMapObject);
	m_vecTankObject.push_back(NPC2);

	CTankObject NPC3(57, 2, DIR_DW, false, 14, &m_nMapObject);
	m_vecTankObject.push_back(NPC3);
	
	return true;
}

//****************************************************************
// Brief 	: 设置控制台窗口信息;
// Method	: SetWindowsInfo
// FullName	: CGameObject::SetWindowsInfo
// Access	: private 
// Returns	: bool
// Parameter: char * pTitle
// Parameter: short nWidth
// Parameter: short nHeight
//****************************************************************

bool CGameObject::SetWindowsInfo(char *pTitle, short nWidth, short nHeight)
{
	//模拟按键设置为英文输入法;
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);

	//设置窗口标题;
	SetConsoleTitleA(pTitle);

	//获取窗口句柄;
	HANDLE sh = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  cd = GetLargestConsoleWindowSize(sh);

	//设置光标信息;
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(sh, &cci);

	//设置缓冲区最大值;
	if (!SetConsoleScreenBufferSize(sh, cd))
	{
		cout << "设置缓冲区窗口大小失败";
		return false;
	}

	//设置窗口大小;
	SMALL_RECT sr = { 0, 0 , nWidth - 1, nHeight - 1 };
	if (!SetConsoleWindowInfo(sh, true, &sr))
	{
		cout << "设置窗口大小失败";
		return false;
	}

	//二次设置缓冲区大小;
	cd.X = nWidth;
	cd.Y = nHeight;
	if (!SetConsoleScreenBufferSize(sh, cd))
	{
		cout << "二次设置缓冲区大小失败";
		return false;
	}

	return true;
}