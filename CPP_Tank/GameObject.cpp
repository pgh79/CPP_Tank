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

//�����ӵ�;
class CBulletObject;

//��ȡ����;
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
// Brief 	: ��������;
// Method	: InterFace
// FullName	: CGameObject::InterFace
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::InterFace()
{
	//���ô�����Ϣ;
	SetWindowsInfo("CPP_Tank_By_D&K", 151, 51);

	int nLength = TextTank.size();

	//�������Ƴ�����;
	for (int i = 0; i < nLength; i++)
	{
		TextTank[i].mPosY += 40;
	}

	//TANK����;
	//�����ƶ���ָ��λ��[10]������������;
	while (!(TextTank[0].mPosY == 10))
	{
		//ÿ�������ƶ�1;
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

	//TANK��˸;
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
// Brief 	: ��ӭ����;
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

	
	//��ʼ���˵�;
	CDrawObject::DrawPencil(31, 24, "���¼�ѡ��  �س�ȷ��", COLOUR_A);

	CDrawObject::DrawPencil(31, 28, SELECT, COLOUR_E);
	CDrawObject::DrawPencil(33, 28, "�� ʼ �� Ϸ", COLOUR_A);
	CDrawObject::DrawPencil(33, 31, "˫ �� ģ ʽ", COLOUR_A);
	CDrawObject::DrawPencil(33, 34, "�� ȡ �� ��", COLOUR_A);
	CDrawObject::DrawPencil(33, 37, "�� �� �� ͼ", COLOUR_A);

	//ѡ���б�;
	int ch;
	int key = 1;
	bool Tflag = false;
	while (ch = _getch())
	{
		switch (ch)
		{
			//�Ϸ���;
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
			//�·���;
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
	//ֹͣ���Ų˵���������;
	mciSendString(L"stop sound\\bgmwelcom.mp3", NULL, 0, NULL);

	switch (key)
	{
	case 1:
		m_bDouble = false;
		m_bData = false;
		m_nEnemy = 10;
		if (m_nRound)
		{
			m_nRound = 1;;	//���Ƶ�ͼʱRoundΪ0����;
		}
		//��Ϸ����;		
		StartGame();
		break;
	case 2:
		m_bDouble = true;
		m_bData = false;
		m_nEnemy = 20;
		if (m_nRound)
		{
			m_nRound = 1;;	//���Ƶ�ͼʱRoundΪ0����;
		}
		//��Ϸ����;
		StartGame();
		break;
	case 3:
		ReadData();
		break;
	case 4:
		//DIY��ͼ;
		m_nMapObject.DIYMap();
		m_nRound = 0;
		Welcome();
		break;;
	default:
		break;
	}
}

//****************************************************************
// Brief 	: ��Ϸ����;
// Method	: StartGame
// FullName	: CGameObject::StartGame
// Access	: public 
// Returns	: bool
//****************************************************************

bool CGameObject::StartGame()
{	
	//����������;
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

	//�ָ�����״̬;
	if (m_bData)
	{
		m_bData = false;
	}

	//BGM
	mciSendString(L"play sound\\30.mp3", NULL, 0, NULL);

	//�о�����5�뵽��ս��;
	Sleep(3000);

	mciSendString(L"play sound\\bgm.mp3 repeat", NULL, 0, NULL);


	clock_t tPlayerA = clock(),
			tPlayerB = clock(),
			tTankNPC = clock(),
			tBullet  = clock();

	while (true)
	{
		
		
		//���A�ƶ�;
		if (clock() - tPlayerA > m_vecTankObject[0].GetSpeed() 
			&& m_vecTankObject[0].GetIsDie())
		{
			PlayerA();
			tPlayerA = clock();
		}

		

		//���B�ƶ�;
		if (clock() - tPlayerB > m_vecTankObject[1].GetSpeed()
			&& m_vecTankObject[1].GetIsDie())
		{
			PlayerB();
			tPlayerB = clock();
		}

	
		//�ƶ�TankNPC;
		if (clock()-tTankNPC>100)
		{
			NPCAction();
			tTankNPC = clock();
		}



		//�ӵ��ƶ�;
		if (clock()-tBullet>50)
		{
			BulletAction();
			tBullet = clock();
		}


		//���GG!
		if (!m_vecTankObject[0].GetIsDie() &&
			!m_vecTankObject[1].GetIsDie())
		{
			GameOver();
		}

		//���ʤ��;
		if (m_nEnemy == 0)
		{
			Victory();
		}
	}

	return true;
}


//****************************************************************
// Brief 	: ���A����!
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
	//B���浵;
	else if (KEY_DOWN('B'))
	{
		SaveData();
		//����;
		int mBoxID = MessageBoxA(NULL, "�浵�ɹ���\n�����ȷ����������Ϸ��\n�����ȡ�����뿪��Ϸ!", "V!", MB_OKCANCEL);
		if (mBoxID == IDOK)
		{
			;
		}
		else if (mBoxID == IDCANCEL)
		{
			exit(0);
		}
	}
	//ESC�������˵�;
	else if (KEY_DOWN(VK_ESCAPE))
	{
		mciSendString(L"stop sound\\bgm.mp3", NULL, 0, NULL);
		RestData();
		Welcome();
	}

	//ͨ�����������Ʒ����ٶ�;
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
// Brief 	: ���B����;
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
	//����;
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
// Brief 	: ����NPC;
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
			//ɾ��NPC;
			m_vecTankObject.erase(m_vecTankObject.begin() + i);
			m_nEnemy -= 1;		
			KillBGM();
			//ˢ��BUFF;
			m_nMapObject.Buff();

			//���µ�������;
			m_nMapObject.DrawScore(m_nRound, m_nEnemy);

			if (m_nEnemy > 2)
			{
				//NPC����;
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
// Brief 	: �ӵ��¼�;
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
			//�ƶ���Ч�ӵ�;
			m_vecBulletObject[i].BulletFly(m_vecTankObject, m_vecBulletObject);
			i++;
		}
		else
		{
			//ɾ����Ч�ӵ�;
			m_vecBulletObject.erase(m_vecBulletObject.begin() + i);
		}
	}
}

//****************************************************************
// Brief 	: ɱ����Ч;
// Method	: KillBGM
// FullName	: CGameObject::KillBGM
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::KillBGM()
{
	//�������������Ч;
	int nTemp = rand() % 5;

	char BgmBuf[30] = { 0 };
	sprintf_s(BgmBuf, sizeof(BgmBuf), "play sound\\%d.mp3", nTemp);

	CString string = BgmBuf;

	//GG BGM
	mciSendString(string, NULL, 0, NULL);
}

//****************************************************************
// Brief 	: ���V��
// Method	: Victory
// FullName	: CGameObject::Victory
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::Victory()
{
	mciSendString(L"stop sound\\bgm.mp3", NULL, 0, NULL);
	//ʤ��BGM
	mciSendString(L"play sound\\victor.mp3", NULL, 0, NULL);


	//ͨ��;
	if (m_nRound == 3)
	{
		//����;
		int mBoxID = MessageBoxA(NULL, "��ϲ����ս��ɣ�", "V!", MB_OKCANCEL);
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

	//��ʽ���ַ���;
	CStringA string;
	if (m_bDouble)
	{
		string.Format("Good Game !\nP1�˴ε÷�Ϊ��%d \nP2�˴ε÷�Ϊ��%d \n\n�����ȷ������ս��һ�أ�\n�����ȡ�����뿪��Ϸ��\n", nTemp, nTemp2);
	}
	else
	{
		string.Format("Good Game !\nP1�˴ε÷�Ϊ��%d \n\n�����ȷ������ս��һ�أ�\n�����ȡ�����뿪��Ϸ��\n", nTemp);
	}

	RestData();

	//����;
	int mBoxID = MessageBoxA(NULL, string, "V!", MB_OKCANCEL);
	if (mBoxID == IDOK)
	{
		//������1��
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
// Brief 	: ���GG��
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
	//��ʽ���ַ���;
	CStringA string;
	if (m_bDouble)
	{
		string.Format("Game Over !\nP1�˴ε÷�Ϊ��%d \nP2�˴ε÷�Ϊ��%d \n\n�����ȷ��������һ�֣�\n�����ȡ�����뿪��Ϸ��\n", nTemp, nTemp2);
	}
	else
	{
		string.Format("Game Over !\nP1�˴ε÷�Ϊ��%d \n\n�����ȷ��������һ�֣�\n�����ȡ�����뿪��Ϸ��\n", nTemp);
	}

	RestData();
	m_nRound = 1;

	//����;
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
// Brief 	: �������;
// Method	: RestData
// FullName	: CGameObject::RestData
// Access	: public 
// Returns	: void
//****************************************************************

void CGameObject::RestData()
{
	//�������;
	if (m_bDouble)
	{
		m_nEnemy = 20;
	}
	else
	{
		m_nEnemy = 10;
	}

	m_nMapObject = {};

	//���̹��;
	m_vecTankObject.clear();
	//����ӵ�;
	m_vecBulletObject.clear();

	return;

}

//****************************************************************
// Brief 	: �浵;
// Method	: SaveData
// FullName	: CGameObject::SaveData
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::SaveData()
{
	m_bData = true;

	//���ļ�;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "map\\tank.db", "wb");
	if (err != 0)
	{
		return;
	}

	//д���ļ�;

	fwrite(&m_bData, sizeof(m_bData), 1, pFile);
	fwrite(&m_bDouble, sizeof(m_bDouble), 1, pFile);
	fwrite(&m_nRound, sizeof(m_nRound), 1, pFile);
	fwrite(&m_nEnemy, sizeof(m_nEnemy), 1, pFile);
	fwrite(&m_nMapObject, sizeof(m_nMapObject), 1, pFile);


	
	//����̹������;
	m_nTank = m_vecTankObject.size();	
	fwrite(&m_nTank, sizeof(m_nTank), 1, pFile);
	//ѭ��д��̹��;
	for (int  i = 0; i < m_nTank; i++)
	{
		fwrite(&m_vecTankObject[i], sizeof(CTankObject), 1, pFile);
	}



	//�����ӵ�����;
	m_nBullet = m_vecBulletObject.size();
	fwrite(&m_nBullet, sizeof(m_nBullet), 1, pFile);
	//ѭ��д���ӵ�;
	for (int i = 0; i < m_nBullet; i++)
	{
		fwrite(&m_vecBulletObject[i], sizeof(CBulletObject), 1, pFile);
	}	

	fclose(pFile);

	m_bData = false;

	return;

}

//****************************************************************
// Brief 	: ����;
// Method	: ReadData
// FullName	: CGameObject::ReadData
// Access	: private 
// Returns	: void
//****************************************************************

void CGameObject::ReadData()
{
	//���ļ�;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "map\\tank.db", "rb");
	if (err != 0)
	{
		int mBoxID = MessageBoxA(NULL, "���޴浵�ļ���\n�����ȷ�����������˵���\n�����ȡ�����˳���Ϸ!", "��ȡ���ݳ���!", MB_OKCANCEL);
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

	//��ȡ�ļ�;
	fread(&m_bData, sizeof(m_bData), 1, pFile);
	fread(&m_bDouble, sizeof(m_bDouble), 1, pFile);
	fread(&m_nRound, sizeof(m_nRound), 1, pFile);
	fread(&m_nEnemy, sizeof(m_nEnemy), 1, pFile);
	fread(&m_nMapObject, sizeof(m_nMapObject), 1, pFile);



	//��ȡ̹������;
	fread(&m_nTank, sizeof(m_nTank), 1, pFile);
	//ѭ������̹��;
	for (int i = 0; i < m_nTank; i++)
	{
		CTankObject TankTemp;
		fread(&TankTemp, sizeof(CTankObject), 1, pFile);
		//�޸ĵ�ͼָ��;
		TankTemp.SetMapObject(&m_nMapObject);
		m_vecTankObject.push_back(TankTemp);
	}

	//��ȡ�ӵ�����;
	fread(&m_nBullet, sizeof(m_nBullet), 1, pFile);
	//ѭ��д���ӵ�;
	for (int i = 0; i < m_nBullet; i++)
	{
		CBulletObject BulletTemp;
		fread(&BulletTemp, sizeof(CBulletObject), 1, pFile);
		//�޸ĵ�ͼָ��;
		BulletTemp.SetMapObject(&m_nMapObject);
		m_vecBulletObject.push_back(BulletTemp);
	}

	//�ر��ļ�;												
	fclose(pFile);

	
	//��ʼ��Ϸ;
	StartGame();
	return;
}

//****************************************************************
// Brief 	: ��ʼ��̹��;
// Method	: IniTank
// FullName	: CGameObject::IniTank
// Access	: public 
// Returns	: bool
//****************************************************************

bool CGameObject::IniTank()
{
	//��ʼ�����;
	CTankObject PlayerA(23, 47, DIR_UP, true, 10, &m_nMapObject);
	m_vecTankObject.push_back(PlayerA);

	CTankObject PlayerB(35, 47, DIR_UP, true, 11, &m_nMapObject);
	//���BĬ��GG��
	PlayerB.SetLevel(0);
	PlayerB.SetIsDie(false);
	m_vecTankObject.push_back(PlayerB);

	//��ʼ��NPC;
	CTankObject NPC1(2, 2, DIR_DW, false, 12, &m_nMapObject);
	m_vecTankObject.push_back(NPC1);

	CTankObject NPC2(30,2, DIR_DW, false, 13, &m_nMapObject);
	m_vecTankObject.push_back(NPC2);

	CTankObject NPC3(57, 2, DIR_DW, false, 14, &m_nMapObject);
	m_vecTankObject.push_back(NPC3);
	
	return true;
}

//****************************************************************
// Brief 	: ���ÿ���̨������Ϣ;
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
	//ģ�ⰴ������ΪӢ�����뷨;
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);

	//���ô��ڱ���;
	SetConsoleTitleA(pTitle);

	//��ȡ���ھ��;
	HANDLE sh = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  cd = GetLargestConsoleWindowSize(sh);

	//���ù����Ϣ;
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(sh, &cci);

	//���û��������ֵ;
	if (!SetConsoleScreenBufferSize(sh, cd))
	{
		cout << "���û��������ڴ�Сʧ��";
		return false;
	}

	//���ô��ڴ�С;
	SMALL_RECT sr = { 0, 0 , nWidth - 1, nHeight - 1 };
	if (!SetConsoleWindowInfo(sh, true, &sr))
	{
		cout << "���ô��ڴ�Сʧ��";
		return false;
	}

	//�������û�������С;
	cd.X = nWidth;
	cd.Y = nHeight;
	if (!SetConsoleScreenBufferSize(sh, cd))
	{
		cout << "�������û�������Сʧ��";
		return false;
	}

	return true;
}