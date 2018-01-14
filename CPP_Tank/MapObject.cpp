#include "stdafx.h"
#include "MapObject.h"
#include "DrawObject.h"
#include "TankObject.h"



CMapObject::CMapObject()
{
}


CMapObject::~CMapObject()
{
}

//****************************************************************
// Brief 	: 设置地图中指定坐标值;
// Method	: SetMapValue
// FullName	: CMapObject::SetMapValue
// Access	: public 
// Returns	: bool
// Parameter: int nPosX
// Parameter: int nPosY
// Parameter: int Value
//****************************************************************

bool CMapObject::SetMapValue(int nPosX, int nPosY, int Value)
{
	if (nPosX < 0 || nPosX>59 || nPosY < 0 || nPosY>49)
	{
		return false;
	}	
	m_nMap[nPosY][nPosX] = Value;
	return true;
}

//****************************************************************
// Brief 	: 获取地图中指定坐标值;
// Method	: GetMapValue
// FullName	: CMapObject::GetMapValue
// Access	: public 
// Returns	: int
// Parameter: int nPosX
// Parameter: int nPosY
//****************************************************************

int CMapObject::GetMapValue(int nPosX, int nPosY)
{
	if (nPosX < 0 || nPosX>59 || nPosY < 0 || nPosY>49)
	{
		return -1;
	}
	return m_nMap[nPosY][nPosX];
}

//****************************************************************
// Brief 	: 随机生成Buff;
// Method	: Buff
// FullName	: CMapObject::Buff
// Access	: private 
// Returns	: void
//****************************************************************

void CMapObject::Buff()
{

	//清除上次的BUFF;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			//跳过非空的位置;
			if (m_nMap[i][j] == M_VALUE_REDBUFF||
				m_nMap[i][j] == M_VALUE_BLUEBUFF||
				m_nMap[i][j] == M_VALUE_YELLOW)
			{
				CDrawObject::DrawPencil(j, i, M_CLEAR, COLOUR_D);
				m_nMap[i][j] = M_VALUE_EMPTY;
			}
		}
	}


	//重新随机生成2个;
	int nBuff = 0;	
	while (nBuff != 3)
	{
		int nPosX = rand()% 50 + 5;
		int nPosY= rand() % 40 + 5;

		if (GetMapValue(nPosX,nPosY)==0&&nBuff==0)
		{
			m_nMap[nPosY][nPosX] = M_VALUE_REDBUFF;			
			CDrawObject::DrawPencil(nPosX, nPosY, M_BUFF, COLOUR_D);
			nBuff++;
		}
		if (GetMapValue(nPosX, nPosY) == 0 && nBuff == 1)
		{
			m_nMap[nPosY][nPosX] = M_VALUE_BLUEBUFF;			
			CDrawObject::DrawPencil(nPosX, nPosY, M_BUFF, COLOUR_B);
			nBuff++;
		}
		if (GetMapValue(nPosX, nPosY) == 0 && nBuff == 2)
		{
			m_nMap[nPosY][nPosX] = M_VALUE_YELLOW;
			CDrawObject::DrawPencil(nPosX, nPosY, M_BUFF, COLOUR_E);
			nBuff++;
		}
	}

	return;
}

//****************************************************************
// Brief 	: 初始化地图;
// Method	: IniMap
// FullName	: CMapObject::IniMap
// Access	: public 
// Returns	: bool
//****************************************************************

bool CMapObject::IniMap()
{

	for (int i = 0; i < M_HEIGHT;i++)
	{
		for (int j = 0; j < M_WIDTH;j++)
		{
			//写入边框值;
			if (i==0||j==0||i==M_HEIGHT-1||j==M_WIDTH-1||j==59)
			{
				m_nMap[i][j] = M_VALUE_BORDER;
			}
			//跳过非空的位置;
			else if (!m_nMap[i][j])
			{
				continue;
			}
			else
			{
				//其他填充0;
				m_nMap[i][j] = M_VALUE_EMPTY;
			}
	
		}
	}

	return true;
}

//****************************************************************
// Brief 	: 绘制地图;
// Method	: DrawMap
// FullName	: CMapObject::DrawMap
// Access	: public 
// Returns	: bool
//****************************************************************

bool CMapObject::DrawMap()
{
	system("color 0A");
	system("cls");
	
	for (int i = 0; i < M_HEIGHT; i++)
	{
		for (int j = 0; j < M_WIDTH; j++)
		{
			//绘制障碍物;
			switch (m_nMap[i][j])
			{
			case M_VALUE_BORDER:
				CDrawObject::DrawPencil(j, i, M_BORDER, COLOUR_A);				
				break;
			case M_VALUE_STEEL:
				CDrawObject::DrawPencil(j, i, M_STEEL, COLOUR_F);
				break;
			case M_VALUE_WALL:
				CDrawObject::DrawPencil(j, i, M_WALL, COLOUR_A);
				break;
			case M_VALUE_WATER:
				CDrawObject::DrawPencil(j, i, M_WATER, COLOUR_A);
				break;
			case M_VALUE_FOREST:
				CDrawObject::DrawPencil(j, i, M_FOREST, COLOUR_A);
				break;
			default:
				break;
			}

			//绘制老家;
			if ((j > 27 && j < 31) && (i>45 && i < 49))
			{
				CDrawObject::DrawPencil(j, i, M_HOME, COLOUR_C);
				m_nMap[i][j] = M_VALUE_HOME;
			}
		}
		//动画效果;
		Sleep(20);
	}
	return true;
}

//****************************************************************
// Brief 	: 读取地图;
// Method	: ReadMap
// FullName	: CMapObject::ReadMap
// Access	: public 
// Returns	: void
// Parameter: int m_nRound
//****************************************************************

void CMapObject::ReadMap(int m_nRound)
{
	//将关卡值转为地图名称;
	char MapBuf[20] = { 0 };
	sprintf_s(MapBuf, sizeof(MapBuf), "map\\%d.tmap", m_nRound);

	//根据m_nRound值加载对应地图文件;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, MapBuf, "rb");

	if (err != 0)
	{
		int mBoxID = MessageBoxA(NULL, "读取地图出错！\n点击【确定】返回主菜单设计地图！\n点击【取消】退出游戏!", "读取地图出错!", MB_OKCANCEL);
		if (mBoxID == IDOK)
		{
			//welcome();
		}
		else if (mBoxID == IDCANCEL)
		{
			exit(0);
		}

		return;
	}

	//读取文件;
	fread(m_nMap, sizeof(m_nMap), 1, pFile);

	//关闭文件;
	fclose(pFile);
}

//****************************************************************
// Brief 	: DIY地图主体;
// Method	: DIYMap
// FullName	: CMapObject::DIYMap
// Access	: public 
// Returns	: bool
//****************************************************************


bool CMapObject::DIYMap()
{
	//加载绘图信息;
	DIYMapInfo();

	//BGM RAP
	mciSendString(L"play sound\\bgmmap.mp3 repeat", NULL, 0, NULL);

	HANDLE hiInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD StcRecord = {};
	DWORD dwRead = 0;

	//重设接受模式;避免受cls影响;
	SetConsoleMode(hiInput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	while (true)
	{
		ReadConsoleInput(hiInput, &StcRecord, 1, &dwRead);
		//鼠标事件;
		if (StcRecord.EventType == MOUSE_EVENT)
		{
			if (MouseEventProc(StcRecord.Event.MouseEvent))
			{
				SaveMap();
				//设置窗口标题;
				SetConsoleTitleA("CPP_Tank_By_D&K");

				//关闭地图BGM;
				mciSendString(L"stop sound\\bgmmap.mp3", NULL, 0, NULL);

				return true;
			}
		}
		//键盘事件;
		if (StcRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(StcRecord.Event.KeyEvent);
		}
	}
	return true;
}


//****************************************************************
// Brief 	: 绘制游戏信息;
// Method	: DrawGanmeInfo
// FullName	: CMapObject::DrawGanmeInfo
// Access	: public 
// Returns	: void
//****************************************************************

void CMapObject::DrawGanmeInfo()
{
	CDrawObject::DrawPencil(62, 3, "Round:", COLOUR_A);
	CDrawObject::DrawPencil(62, 5, "Enemy:", COLOUR_A);

	CDrawObject::DrawPencil(62, 8, "P1 Score:", COLOUR_A);
	CDrawObject::DrawPencil(62, 10, "P1 HP:", COLOUR_A);

	CDrawObject::DrawPencil(62, 12, "P2 Score:", COLOUR_A);
	CDrawObject::DrawPencil(62, 14, "P2 HP:", COLOUR_A);

	CDrawObject::DrawPencil(61, 17, "P1移动:W,A,S,D,发射:J", COLOUR_A);
	CDrawObject::DrawPencil(61, 19, "P2移动:↑,↓,←,→,发射:0", COLOUR_A);
	CDrawObject::DrawPencil(61, 21, "B键存档;Esc退出;空格暂停;", COLOUR_A);
}

//****************************************************************
// Brief 	: 绘制游戏分数;
// Method	: DrawScore
// FullName	: CMapObject::DrawScore
// Access	: public 
// Returns	: void
//****************************************************************

void CMapObject::DrawScore(vector<CTankObject>& vecTank)
{
 	//等级小于2，分数每增加1000,等级加1；
 	if ((vecTank[0].GetScores()) > 0 &&
 		(vecTank[0].GetScores()) % 1000 == 0 &&
 		(vecTank[0].GetLevel()) < 2)
 	{
		int nLevel = vecTank[0].GetLevel();
		nLevel += 1;
 		vecTank[0].SetLevel(nLevel);
 	}
 
 	if ((vecTank[1].GetScores())>0 &&
 		(vecTank[1].GetScores()) % 1000 == 0 &&
 			(vecTank[1].GetLevel()) < 2)
 	{
		int nLevel = vecTank[0].GetLevel();
		nLevel += 1;
		vecTank[0].SetLevel(nLevel);
 	}
 
 
	CDrawObject::DrawPencil(68, 8, vecTank[0].GetScores(), COLOUR_A);
	CDrawObject::DrawPencil(68, 10, vecTank[0].GetLevel(), COLOUR_A);
 
	CDrawObject::DrawPencil(68, 12, vecTank[1].GetScores(), COLOUR_A);
	CDrawObject::DrawPencil(68, 14, vecTank[1].GetLevel(), COLOUR_A);
 

}

//****************************************************************
// Brief 	: 绘制敌人数量;重载;
// Method	: DrawScore
// FullName	: CMapObject::DrawScore
// Access	: public 
// Returns	: void
// Parameter: int nRound
// Parameter: int nEnemy
//****************************************************************

void CMapObject::DrawScore(int nRound, int nEnemy)
{
	CDrawObject::DrawPencil(68, 3, nRound, COLOUR_A);
	CDrawObject::DrawPencil(68, 5, nEnemy, COLOUR_A);
}

//****************************************************************
// Brief 	: 绘制DIY地图右侧信息;
// Method	: DIYMapInfo
// FullName	: CMapObject::DIYMapInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CMapObject::DIYMapInfo()
{
	//绘制边框;
	IniMap();
	DrawMap();

	//文字信息;
	CDrawObject::DrawPencil(61, 3, "鼠标点击图形选择", COLOUR_A);
	CDrawObject::DrawPencil(61, 5, "键盘1,2,3,4,+,-,选择", COLOUR_A);
	CDrawObject::DrawPencil(61, 7, "钢板免疫低级攻击", COLOUR_A);
	CDrawObject::DrawPencil(61, 9, "围墙和丛林可被攻破", COLOUR_A);
	CDrawObject::DrawPencil(61, 11, "河流不阻止炮弹", COLOUR_A);
	CDrawObject::DrawPencil(61, 13, "B键保存;Esc退出;双击退出", COLOUR_A);

	CDrawObject::DrawPencil(64, 16, "  ① 钢 板  ", COLOUR_A);
	CDrawObject::DrawPencil(64, 17, "■■■■■■", COLOUR_F);
	CDrawObject::DrawPencil(64, 18, "■■■■■■", COLOUR_F);
	CDrawObject::DrawPencil(64, 19, "■■■■■■", COLOUR_F);

	CDrawObject::DrawPencil(64, 21, "  ② 围 墙  ", COLOUR_A);
	CDrawObject::DrawPencil(64, 22, "▓▓▓▓▓▓", COLOUR_A);
	CDrawObject::DrawPencil(64, 23, "▓▓▓▓▓▓", COLOUR_A);
	CDrawObject::DrawPencil(64, 24, "▓▓▓▓▓▓", COLOUR_A);

	CDrawObject::DrawPencil(64, 26, "  ③ 丛 林  ", COLOUR_A);
	CDrawObject::DrawPencil(64, 27, "※※※※※※", COLOUR_A);
	CDrawObject::DrawPencil(64, 28, "※※※※※※", COLOUR_A);
	CDrawObject::DrawPencil(64, 29, "※※※※※※", COLOUR_A);

	CDrawObject::DrawPencil(64, 31, "  ④ 河 流  ", COLOUR_A);
	CDrawObject::DrawPencil(64, 32, "∷∷∷∷∷∷", COLOUR_A);
	CDrawObject::DrawPencil(64, 33, "∷∷∷∷∷∷", COLOUR_A);
	CDrawObject::DrawPencil(64, 34, "∷∷∷∷∷∷", COLOUR_A);

	CDrawObject::DrawPencil(64, 36, " ⑤ 橡皮擦 ", COLOUR_A);
	CDrawObject::DrawPencil(64, 37, "□□□□□□", COLOUR_A);
	CDrawObject::DrawPencil(64, 38, "□□□□□□", COLOUR_A);
	CDrawObject::DrawPencil(64, 39, "□□□□□□", COLOUR_A);

	CDrawObject::DrawPencil(64, 41, "  笔  刷  ", COLOUR_A);
	CDrawObject::DrawPencil(63, 42, "+ + + +", COLOUR_A);
	CDrawObject::DrawPencil(63, 43, "+ + + +", COLOUR_A);
	CDrawObject::DrawPencil(63, 44, "+ + + +", COLOUR_A);

	CDrawObject::DrawPencil(68, 42, "- - - -", COLOUR_A);
	CDrawObject::DrawPencil(68, 43, "- - - -", COLOUR_A);
	CDrawObject::DrawPencil(68, 44, "- - - -", COLOUR_A);

	return;
}

//****************************************************************
// Brief 	: 控制台输出绘制地图坐标;
// Method	: OutPutPos
// FullName	: CMapObject::OutPutPos
// Access	: private 
// Returns	: void
// Parameter: int nPosX
// Parameter: int nPoxY
//****************************************************************

void CMapObject::OutPutPos(int nPosX, int nPoxY)
{
	char posBuf[100] = { 0 };
	sprintf_s(posBuf, sizeof(posBuf), "x=%2d,y=%2d", nPosX / 2, nPoxY);
	SetConsoleTitleA(posBuf);
	CDrawObject::DrawPencil(60, 1, posBuf, COLOUR_BG);
	return;
}

//****************************************************************
// Brief 	: 鼠标处理事件;
// Method	: MouseEventProc
// FullName	: CMapObject::MouseEventProc
// Access	: private 
// Returns	: bool
// Parameter: MOUSE_EVENT_RECORD StcMouse
//****************************************************************

bool CMapObject::MouseEventProc(MOUSE_EVENT_RECORD StcMouse)
{
	switch (StcMouse.dwEventFlags)
	{
	case 0:
		MouseClick(StcMouse);
		break;
	case  DOUBLE_CLICK:
		return true;
		break;
	case MOUSE_MOVED:
		MouseMove(StcMouse);
		break;
	default:
		break;
	}

	OutPutPos(StcMouse.dwMousePosition.X, StcMouse.dwMousePosition.Y);

	return false;
}

//****************************************************************
// Brief 	: 鼠标拖动事件;
// Method	: MouseMove
// FullName	: CMapObject::MouseMove
// Access	: private 
// Returns	: bool
// Parameter: MOUSE_EVENT_RECORD & StcMouse
//****************************************************************

bool CMapObject::MouseMove(MOUSE_EVENT_RECORD &StcMouse)
{
	//左键拖动;
	if (StcMouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		//界定绘制范围;
		if (m_nMapVlue < 6 &&
			StcMouse.dwMousePosition.X < 118 &&
			StcMouse.dwMousePosition.X>1 &&
			StcMouse.dwMousePosition.Y>0 &&
			StcMouse.dwMousePosition.Y < 49)
		{
			//根据地图值绘制相应图形;
			switch (m_nMapVlue)
			{
			case 2:
				CDrawObject::DrawPencil(StcMouse.dwMousePosition.X / 2, StcMouse.dwMousePosition.Y, M_STEEL, COLOUR_F);
				//根据笔刷扩大;
				BrushDraw(StcMouse, M_STEEL, COLOUR_F);
				break;
			case 3:
				CDrawObject::DrawPencil(StcMouse.dwMousePosition.X / 2, StcMouse.dwMousePosition.Y, M_WALL, COLOUR_A);
				//根据笔刷扩大;
				BrushDraw(StcMouse, M_WALL, COLOUR_A);
				break;
			case 4:
				CDrawObject::DrawPencil(StcMouse.dwMousePosition.X / 2, StcMouse.dwMousePosition.Y, M_FOREST, COLOUR_A);
				//根据笔刷扩大;
				BrushDraw(StcMouse, M_FOREST, COLOUR_A);
				break;
			case 5:
				CDrawObject::DrawPencil(StcMouse.dwMousePosition.X / 2, StcMouse.dwMousePosition.Y, M_WATER, COLOUR_A);
				//根据笔刷扩大;
				BrushDraw(StcMouse, M_WATER, COLOUR_A);
				break;
				//橡皮擦;
			case 0:
				CDrawObject::DrawPencil(StcMouse.dwMousePosition.X / 2, StcMouse.dwMousePosition.Y, M_CLEAR, COLOUR_A);
				//根据笔刷扩大;
				BrushDraw(StcMouse, M_CLEAR, COLOUR_A);
				break;
			default:
				break;
			}
			//输出坐标;
			m_nMap[StcMouse.dwMousePosition.Y][StcMouse.dwMousePosition.X / 2] = m_nMapVlue;

			//输出笔刷扩大的坐标;
			switch (m_nBrush)
			{
			case 4:
				if ((StcMouse.dwMousePosition.X / 2) < 56)
				{
					m_nMap[StcMouse.dwMousePosition.Y][(StcMouse.dwMousePosition.X / 2) + 3] = m_nMapVlue;
				}
			case 3:
				if ((StcMouse.dwMousePosition.X / 2) < 57)
				{
					m_nMap[StcMouse.dwMousePosition.Y][(StcMouse.dwMousePosition.X / 2) + 2] = m_nMapVlue;
				}
			case 2:
				if ((StcMouse.dwMousePosition.X / 2) < 58)
				{
					m_nMap[StcMouse.dwMousePosition.Y][(StcMouse.dwMousePosition.X / 2) + 1] = m_nMapVlue;
				}
				break;
			default:
				break;
			}

		}
	}

	return true;
}

//****************************************************************
// Brief 	: 鼠标点击事件;
// Method	: MouseClick
// FullName	: CMapObject::MouseClick
// Access	: private 
// Returns	: bool
// Parameter: MOUSE_EVENT_RECORD & StcMouse
//****************************************************************

bool CMapObject::MouseClick(MOUSE_EVENT_RECORD &StcMouse)
{
	//获取XY坐标;
	int x = StcMouse.dwMousePosition.X;
	int y = StcMouse.dwMousePosition.Y;

	if (x > 120)
	{
		if (x >= 124 && x <= 148)
		{
			if (y == 17 || y == 18 || y == 19)
			{
				m_nMapVlue = 2;
			}
			else if (y == 22 || y == 23 || y == 24)
			{
				m_nMapVlue = 3;
			}
			else if (y == 27 || y == 28 || y == 29)
			{
				m_nMapVlue = 4;
			}
			else if (y == 32 || y == 33 || y == 34)
			{
				m_nMapVlue = 5;
			}
			else if (y == 37 || y == 38 || y == 39)
			{
				m_nMapVlue = 0;
			}

			else if (y == 42 || y == 43 || y == 44)
			{

				if (x < 134 && m_nBrush < 4)
				{
					m_nBrush += 1;
				}
				else if (x > 140 && m_nBrush>1)
				{
					m_nBrush -= 1;
				}

			}
			else
			{
				m_nMapVlue = 7;
			}
		}
		else
		{
			m_nMapVlue = 7;
		}
	}
	
	return false;
}

//****************************************************************
// Brief 	: 键盘处理事件;
// Method	: KeyEventProc
// FullName	: CMapObject::KeyEventProc
// Access	: private 
// Returns	: bool
// Parameter: KEY_EVENT_RECORD & StcKeyEvent
//****************************************************************

bool CMapObject::KeyEventProc(KEY_EVENT_RECORD &StcKeyEvent)
{
	if (StcKeyEvent.bKeyDown)
	{
		switch (StcKeyEvent.wVirtualKeyCode)
		{
			//键盘上方的1,2,3,4，ASCII码值；
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
			m_nMapVlue = (StcKeyEvent.wVirtualKeyCode & 0x0F) + 1;
			break;

			//B键保存地图并返回主菜单;
		case  0x42:
		case  0x62:
			//菜单界面;
			mciSendString(L"stop sound\\bgmmap.mp3", NULL, 0, NULL);
			return true;
			break;
			//加号增大笔刷;
		case 107:
		case 187:
			if (m_nBrush < 4)
			{
				m_nBrush += 1;
			}

			break;
			//减号缩小笔刷;
		case 109:
		case 189:
			if (m_nBrush > 1)
			{
				m_nBrush -= 1;
			}
			break;
		case 27:
			//Stop BGM
			mciSendString(L"stop sound\\bgmmap.mp3", NULL, 0, NULL);
			//welcome();
			return false;
			break;
		default:
			break;
		}
	}
	return false;
}

//****************************************************************
// Brief 	: 笔刷绘制扩展区;
// Method	: BrushDraw
// FullName	: CMapObject::BrushDraw
// Access	: private 
// Returns	: void
// Parameter: MOUSE_EVENT_RECORD & StcMouse
// Parameter: char * Pstr
// Parameter: WORD color
//****************************************************************

void CMapObject::BrushDraw(MOUSE_EVENT_RECORD &StcMouse, char *Pstr, WORD color)
{
	switch (m_nBrush)
	{
	case 4:
		if (StcMouse.dwMousePosition.X / 2 < 56)
		{
			CDrawObject::DrawPencil((StcMouse.dwMousePosition.X / 2) + 3, StcMouse.dwMousePosition.Y, Pstr, color);
		}
	case 3:
		if (StcMouse.dwMousePosition.X / 2 < 57)
		{
			CDrawObject::DrawPencil((StcMouse.dwMousePosition.X / 2) + 2, StcMouse.dwMousePosition.Y, Pstr, color);
		}
	case 2:
		if (StcMouse.dwMousePosition.X / 2 < 58)
		{
			CDrawObject::DrawPencil((StcMouse.dwMousePosition.X / 2) + 1, StcMouse.dwMousePosition.Y, Pstr, color);
		}
	default:
		break;
	}
	return;
}

//****************************************************************
// Brief 	: 保存地图;
// Method	: SaveMap
// FullName	: CMapObject::SaveMap
// Access	: private 
// Returns	: void
//****************************************************************

void CMapObject::SaveMap()
{
	//打开文件;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "map\\0.tmap", "wb");
	if (err != 0)
	{

		return;
	}

	//读写文件;
	fwrite(m_nMap, sizeof(m_nMap), 1, pFile);	//将地图数组存入文件;

												//关闭文件;
	fclose(pFile);
}
