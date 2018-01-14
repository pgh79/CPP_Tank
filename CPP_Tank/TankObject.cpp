#include "stdafx.h"
#include "TankObject.h"
#include "DrawObject.h"
#include "MapObject.h"
#include "AStar.h"

#include <time.h>

//类外初始化静态成员;
const int  CTankObject::m_ColorPlayer[3] = { COLOUR_A,COLOUR_B,COLOUR_9 };
const int  CTankObject::m_ColorNPC[3] = { COLOUR_F,COLOUR_D,COLOUR_C };
const int  CTankObject::m_TankSpeed[3] = {100,75,50};
const int  CTankObject::m_TankShape[4][3][3] =

{
	{//上;
		{ 0,1,0 },
		{ 1,1,1 },
		{ 1,0,1 }
	},
	{//下;
		{ 1,0,1 },
		{ 1,1,1 },
		{ 0,1,0 }
	},
	{//左;
		{ 0,1,1 },
		{ 1,1,0 },
		{ 0,1,1 }
	},
	{//右;
		{ 1,1,0 },
		{ 0,1,1 },
		{ 1,1,0 }
	}
};


//****************************************************************
// Brief 	: 初始化坦克;
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
// Brief 	: 绘制坦克;
// Method	: DrawObject
// FullName	: CTankObject::DrawObject
// Access	: public 
// Returns	: bool
//****************************************************************


bool CTankObject::DrawObject()
{
	//遍历坦克形状;
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 3;j++)
		{
			if (m_TankShape[m_nDir][j][i])
			{
				
				int nTempX = m_nPosX + i - 1;
				int nTempY = m_nPosY + j - 1;

				//跳过草;
				if (m_pMapObject->GetMapValue(nTempX,nTempY)==M_VALUE_FOREST||
					m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_WATER)
				{
					continue;
				}

				//绘制玩家坦克;
				if (m_bGroup)
				{
					CDrawObject::DrawPencil(nTempX, nTempY, TANKNODE, m_ColorPlayer[m_nLevel]);
					m_pMapObject->SetMapValue(nTempX, nTempY, m_nID);
				}
				//绘制敌军坦克;
				if (!m_bGroup)
				{
					CDrawObject::DrawPencil(nTempX, nTempY, TANKNODE, m_ColorNPC[m_nLevel]);
					m_pMapObject->SetMapValue(nTempX, nTempY, m_nID);
				}
			}
		}
	}

	//涉水模式标记;
	if (m_bWade && m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_FOREST &&
		m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_WATER)
	{
		CDrawObject::DrawPencil(m_nPosX, m_nPosY, TANKNODE, COLOUR_E);
	}
	return true;
}


//****************************************************************
// Brief 	: 擦除坦克;
// Method	: ClsObject
// FullName	: CTankObject::ClsObject
// Access	: public 
// Returns	: bool
//****************************************************************


bool CTankObject::ClsObject()
{
	//遍历坦克形状;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_TankShape[m_nDir][j][i])
			{

				int nTempX = m_nPosX + i - 1;
				int nTempY = m_nPosY + j - 1;
				//跳过草;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_FOREST||
					m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_WATER)
				{
					continue;
				}
				//绘制玩家坦克;
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
// Brief 	: 移动玩家坦克;
// Method	: MoveTank
// FullName	: CTankObject::MoveTank
// Access	: public 
// Returns	: bool
// Parameter: int nDir
//****************************************************************

bool CTankObject::MoveTank(int nDir)
{	
	//清除坦克;
	this->ClsObject();
	//建立临时坦克对象;
	CTankObject TankTemp = *this;
	//方向不同只转向;可以原地旋转;

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
	//检测通过将临时对象赋值给当前坦克;
	if (TankTemp.TankCollision())
	{
		*this = TankTemp;
	}

	//重新绘制;
	this->DrawObject();

	return true;
}

//****************************************************************
// Brief 	: TankNPC移动;
// Method	: MoveNpc
// FullName	: CTankObject::MoveNpc
// Access	: public 
// Returns	: bool
//****************************************************************

bool CTankObject::MoveNpc(const vector<CTankObject>& vecTank,vector<CBulletObject>& vecBullet)
{
	if (this->GetIsDie())
	{

		//清除坦克;
		this->ClsObject();

		//建立临时坦克对象;
		CTankObject TankTemp = *this;

			switch (TankTemp.m_nDir)
			{
			case DIR_UP:	TankTemp.m_nPosY--;	break;
			case DIR_DW:	TankTemp.m_nPosY++;	break;
			case DIR_LF:	TankTemp.m_nPosX--;	break;
			case DIR_RH:	TankTemp.m_nPosX++;	break;
			}

			//检测通过将临时对象赋值给当前坦克;
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

			//2级坦克搜索;
			CAStar AstarObj;
			if (this->m_nLevel==2 && AstarObj.Astar(m_pMapObject,*this,vecTank)
				&&this->NPCCount>(8 - this->m_nLevel * 2))
			{
				this->m_nDir = AstarObj.m_Path[0].NewDir;
				CBulletObject BulletObject(*this);
				vecBullet.push_back(BulletObject);	
				this->NPCCount = 0;
			}	
			//1级坦克搜索;
			if (this->m_nLevel>0&& Search() && 
				this->NPCCount>(10-this->m_nLevel*2))
			{
				CBulletObject BulletObject(*this);
				vecBullet.push_back(BulletObject);
				this->NPCCount = 0;
			}	
			//0级坦克发射或高级坦克未搜索到目标发射;
			else if (this->NPCCount > 15)
			{
				CBulletObject BulletObject(*this);
				vecBullet.push_back(BulletObject);		
				this->NPCCount = 0;
			}

		//重新绘制;
		this->DrawObject();

		return true;
	}
	else
	{
		return false;
	}		
}

//****************************************************************
// Brief 	: 敌军1搜索目标;十字寻路法;
// Method	: Search
// FullName	: CTankObject::Search
// Access	: public 
// Returns	: bool
//****************************************************************

bool CTankObject::Search()
{

	//遍历搜寻;
	//为了提高效率;放弃x50-60的小部分;
	for (int i = 0; i < 50; i++)
	{
		//遍历Y;//发现后转向;
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

		//遍历X;//发现后转向;
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
// Brief 	: 碰撞检测;
// Method	: TankCollision
// FullName	: CTankObject::TankCollision
// Access	: public 
// Returns	: bool
//****************************************************************

bool CTankObject::TankCollision()
{
	//遍历坦克形状;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{			
				//循环检测9个点; 检测6个点会存在转向失败问题;
				int nTempX = m_nPosX + i - 1;
				int nTempY = m_nPosY + j - 1;

				//红BUFF升级;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_REDBUFF
					&&this->m_nLevel < 2)
				{
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR, COLOUR_A);
					this->m_nLevel += 1;
				}


				//蓝BUFF降级;
				if (m_pMapObject->GetMapValue(nTempX, nTempY) == M_VALUE_BLUEBUFF
					&&this->m_nLevel>0)
				{
					m_pMapObject->SetMapValue(nTempX, nTempY, M_VALUE_EMPTY);
					CDrawObject::DrawPencil(nTempX, nTempY, M_CLEAR,COLOUR_A);
					this->m_nLevel -= 1;
				}

				//黄BUFF过水;
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

				//涉水模式判断;
				if (m_bWade)
				{
					//任意一点不为空且不是自己的点返回失败;
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
					//任意一点不为空且不是自己的点返回失败;
					if (m_pMapObject->GetMapValue(nTempX, nTempY) != 0 &&
						m_pMapObject->GetMapValue(nTempX, nTempY) != (this->m_nID) &&
						m_pMapObject->GetMapValue(nTempX, nTempY) != M_VALUE_FOREST)
					{
						return false;
					}
				}			

		}
	}
	//检测所有为空可以走;
	return true;
}

