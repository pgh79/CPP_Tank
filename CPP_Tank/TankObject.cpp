#include "stdafx.h"
#include "TankObject.h"
#include "DrawObject.h"
#include "MapObject.h"
#include "AStar.h"

#include <time.h>

//�����ʼ����̬��Ա;
const int  CTankObject::m_ColorPlayer[3] = { COLOUR_A,COLOUR_B,COLOUR_9 };
const int  CTankObject::m_ColorNPC[3] = { COLOUR_F,COLOUR_D,COLOUR_C };
const int  CTankObject::m_TankSpeed[3] = {100,75,50};
const int  CTankObject::m_TankShape[4][3][3] =

{
	{//��;
		{ 0,1,0 },
		{ 1,1,1 },
		{ 1,0,1 }
	},
	{//��;
		{ 1,0,1 },
		{ 1,1,1 },
		{ 0,1,0 }
	},
	{//��;
		{ 0,1,1 },
		{ 1,1,0 },
		{ 0,1,1 }
	},
	{//��;
		{ 1,1,0 },
		{ 0,1,1 },
		{ 1,1,0 }
	}
};


//****************************************************************
// Brief 	: ��ʼ��̹��;
// Method	: CTankObject
// FullName	: CTankObject::CTankObject
// Access	: public 
// Returns	: 
// Parameter: int PosX
// Parameter: int PosY
// Parameter: int Dir
// Parameter: bool Group
// Parameter: int ID
//****************************************************************


CTankObject::CTankObject(int PosX, int PosY, int Dir, bool Group, int ID, CMapObject* Object) :
	m_nPosX(PosX), m_nPosY(PosY), m_nDir(Dir),m_bGroup(Group),m_nID(ID)
{	
	m_nLevel = 1;
	m_bIsDie = true;
	m_pMapObject = Object;
	m_nSpeed = m_TankSpeed[m_nLevel];
	m_bWade = false;
}



CTankObject::~CTankObject()
{

}

//****************************************************************
// Brief 	: ����̹��;
// Method	: DrawObject
// FullName	: CTankObject::DrawObject
// Access	: public 
// Returns	: bool
//****************************************************************


bool CTankObject::DrawObject()
{
	//����̹����״;
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 3;j++)
		{
			if (m_TankShape[m_nDir][j][i])
			{
				
				int nTempX = m_nPosX + i - 1;
				int nTempY = m_nPosY + j - 1;

				//������;
				if (m_pMapObject->GetMapValue(nTempX,nTempY)==M_VALUE_FOREST||
					m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_WATER)
				{
					continue;
				}

				//�������̹��;
				if (m_bGroup)
				{
					CDrawObject::DrawPencil(nTempX, nTempY, TANKNODE, m_ColorPlayer[m_nLevel]);
					m_pMapObject->SetMapValue(nTempX, nTempY, m_nID);
				}
				//���Ƶо�̹��;
				if (!m_bGroup)
				{
					CDrawObject::DrawPencil(nTempX, nTempY, TANKNODE, m_ColorNPC[m_nLevel]);
					m_pMapObject->SetMapValue(nTempX, nTempY, m_nID);
				}
			}
		}
	}

	//��ˮģʽ���;
	if (m_bWade && m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_FOREST &&
		m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_WATER)
	{
		CDrawObject::DrawPencil(m_nPosX, m_nPosY, TANKNODE, COLOUR_E);
	}
	return true;
}


//****************************************************************
// Brief 	: ����̹��;
// Method	: ClsObject
// FullName	: CTankObject::ClsObject
// Access	: public 
// Returns	: bool
//****************************************************************


bool CTankObject::ClsObject()
{
	//����̹����״;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_TankShape[m_nDir][j][i])
			{

				int nTempX = m_nPosX + i - 1;
				int nTempY = m_nPosY + j - 1;
				//������;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_FOREST||
					m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_WATER)
				{
					continue;
				}
				//�������̹��;
				if (m_bGroup)
				{
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR, m_ColorPlayer[m_nLevel]);
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
				}
				if (!m_bGroup)
				{
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR, m_ColorNPC[m_nLevel]);
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
				}
			}
		}
	}
	return true;
}

//****************************************************************
// Brief 	: �ƶ����̹��;
// Method	: MoveTank
// FullName	: CTankObject::MoveTank
// Access	: public 
// Returns	: bool
// Parameter: int nDir
//****************************************************************

bool CTankObject::MoveTank(int nDir)
{	
	//���̹��;
	this->ClsObject();
	//������ʱ̹�˶���;
	CTankObject TankTemp = *this;
	//����ֻͬת��;����ԭ����ת;

	if (TankTemp.m_nDir!=nDir)
	{
		TankTemp.m_nDir = nDir;
	}
	else
	{
		switch (nDir)
		{
		case DIR_UP:	TankTemp.m_nPosY--;	break;
		case DIR_DW:	TankTemp.m_nPosY++;	break;
		case DIR_LF:	TankTemp.m_nPosX--;	break;
		case DIR_RH:	TankTemp.m_nPosX++;	break;
		}
	}
	//���ͨ������ʱ����ֵ����ǰ̹��;
	if (TankTemp.TankCollision())
	{
		*this = TankTemp;
	}

	//���»���;
	this->DrawObject();

	return true;
}

//****************************************************************
// Brief 	: TankNPC�ƶ�;
// Method	: MoveNpc
// FullName	: CTankObject::MoveNpc
// Access	: public 
// Returns	: bool
//****************************************************************

bool CTankObject::MoveNpc(const vector<CTankObject>& vecTank,vector<CBulletObject>& vecBullet)
{
	if (this->GetIsDie())
	{

		//���̹��;
		this->ClsObject();

		//������ʱ̹�˶���;
		CTankObject TankTemp = *this;

			switch (TankTemp.m_nDir)
			{
			case DIR_UP:	TankTemp.m_nPosY--;	break;
			case DIR_DW:	TankTemp.m_nPosY++;	break;
			case DIR_LF:	TankTemp.m_nPosX--;	break;
			case DIR_RH:	TankTemp.m_nPosX++;	break;
			}

			//���ͨ������ʱ����ֵ����ǰ̹��;
			if (TankTemp.TankCollision())
			{
				*this = TankTemp;
			}
			else
			{
				TankTemp = *this;
				TankTemp.m_nDir = rand() % 4;
				*this = TankTemp;
			}



			this->NPCCount++;

			//2��̹������;
			CAStar AstarObj;
			if (this->m_nLevel==2 && AstarObj.Astar(m_pMapObject,*this,vecTank)
				&&this->NPCCount>(8 - this->m_nLevel * 2))
			{
				this->m_nDir = AstarObj.m_Path[0].NewDir;
				CBulletObject BulletObject(*this);
				vecBullet.push_back(BulletObject);	
				this->NPCCount = 0;
			}	
			//1��̹������;
			if (this->m_nLevel>0&& Search() && 
				this->NPCCount>(10-this->m_nLevel*2))
			{
				CBulletObject BulletObject(*this);
				vecBullet.push_back(BulletObject);
				this->NPCCount = 0;
			}	
			//0��̹�˷����߼�̹��δ������Ŀ�귢��;
			else if (this->NPCCount > 15)
			{
				CBulletObject BulletObject(*this);
				vecBullet.push_back(BulletObject);		
				this->NPCCount = 0;
			}

		//���»���;
		this->DrawObject();

		return true;
	}
	else
	{
		return false;
	}		
}

//****************************************************************
// Brief 	: �о�1����Ŀ��;ʮ��Ѱ·��;
// Method	: Search
// FullName	: CTankObject::Search
// Access	: public 
// Returns	: bool
//****************************************************************

bool CTankObject::Search()
{

	//������Ѱ;
	//Ϊ�����Ч��;����x50-60��С����;
	for (int i = 0; i < 50; i++)
	{
		//����Y;//���ֺ�ת��;
		if (m_pMapObject->GetMapValue(m_nPosX, i)==10
			||m_pMapObject->GetMapValue(m_nPosX, i) == 11)
		{
			if (i < m_nPosY)
			{
				this->m_nDir = DIR_UP;
				return true;
			}
			else if (i > m_nPosY)
			{
				this->m_nDir = DIR_DW;
				return true;
			}

		}

		//����X;//���ֺ�ת��;
		if (m_pMapObject->GetMapValue(i, m_nPosY) == 10 
			||m_pMapObject->GetMapValue(i, m_nPosY) == 11)
			if (i < m_nPosX)
			{
				this->m_nDir = DIR_LF;
				return true;
			}
			else if (i > m_nPosX)
			{
				this->m_nDir = DIR_RH;
				return true;
			}

	}
	return false;
}


//****************************************************************
// Brief 	: ��ײ���;
// Method	: TankCollision
// FullName	: CTankObject::TankCollision
// Access	: public 
// Returns	: bool
//****************************************************************

bool CTankObject::TankCollision()
{
	//����̹����״;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{			
				//ѭ�����9����; ���6��������ת��ʧ������;
				int nTempX = m_nPosX + i - 1;
				int nTempY = m_nPosY + j - 1;

				//��BUFF����;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_REDBUFF
					&&this->m_nLevel < 2)
				{
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR, COLOUR_A);
					this->m_nLevel += 1;
				}


				//��BUFF����;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_BLUEBUFF
					&&this->m_nLevel>0)
				{
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR,COLOUR_A);
					this->m_nLevel -= 1;
				}

				//��BUFF��ˮ;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_YELLOW)
				{
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR, COLOUR_A);
					if (this->m_bWade)
					{
						this->m_bWade = false;
					}
					else
					{
						this->m_bWade = true;
					}
					
				}

				//��ˮģʽ�ж�;
				if (m_bWade)
				{
					//����һ�㲻Ϊ���Ҳ����Լ��ĵ㷵��ʧ��;
					if (m_pMapObject->GetMapValue(nTempX, nTempY) != 0 &&
						m_pMapObject->GetMapValue(nTempX, nTempY) != (this->m_nID) &&
						m_pMapObject->GetMapValue(nTempX, nTempY) != M_VALUE_FOREST&&
						m_pMapObject->GetMapValue(nTempX, nTempY) != M_VALUE_WATER)
					{
						return false;
					}
				}
				else
				{
					//����һ�㲻Ϊ���Ҳ����Լ��ĵ㷵��ʧ��;
					if (m_pMapObject->GetMapValue(nTempX, nTempY) != 0 &&
						m_pMapObject->GetMapValue(nTempX, nTempY) != (this->m_nID) &&
						m_pMapObject->GetMapValue(nTempX, nTempY) != M_VALUE_FOREST)
					{
						return false;
					}
				}			

		}
	}
	//�������Ϊ�տ�����;
	return true;
}

