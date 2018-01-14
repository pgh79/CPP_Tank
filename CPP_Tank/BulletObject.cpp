#include "stdafx.h"
#include "BulletObject.h"
#include "DrawObject.h"
#include "TankObject.h"
#include "GameObject.h"

//****************************************************************
// Brief 	: 初始化子弹;
// Method	: CBulletObject
// FullName	: CBulletObject::CBulletObject
// Access	: public 
// Returns	: 
// Parameter: const CTankObject & TankObject
//****************************************************************

CBulletObject::CBulletObject(const CTankObject& TankObject)
{
	*this = TankObject;
	switch (m_nDir)
	{
	case DIR_UP:		m_nPosY -= 2;		break;
	case DIR_DW:		m_nPosY += 2;		break;
	case DIR_LF:		m_nPosX -= 2;		break;
	case DIR_RH:		m_nPosX += 2;		break;
	}
	//初始化子弹在边框无效;
	if (m_pMapObject->GetMapValue(m_nPosX,GetPosY())==1)
	{
		m_bIsDie = false;
	}
	//子弹等级低于2初始化在钢板无效;
	else if (m_pMapObject->GetMapValue(m_nPosX, GetPosY()) == 2&&m_nLevel<2)
	{
		m_bIsDie = false;
	}

	return;
}


CBulletObject::~CBulletObject()
{
}

//****************************************************************
// Brief 	: 绘制子弹;
// Method	: DrawObject
// FullName	: CBulletObject::DrawObject
// Access	: public 
// Returns	: bool
//****************************************************************

bool CBulletObject::DrawObject()
{
	if (m_bGroup)
	{
		CDrawObject::DrawPencil(m_nPosX, m_nPosY, BULLETNODE, COLOUR_A);	
	}
	else
	{
		CDrawObject::DrawPencil(m_nPosX, m_nPosY, BULLETNODE, COLOUR_F);
	}

	//跳过河流和草;
	if (m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_WATER&&
		m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_FOREST)
	{
		m_pMapObject->SetMapValue(m_nPosX, m_nPosY, M_VALUE_BULLET);
	}
	return true;
}

//****************************************************************
// Brief 	: 清除子弹;
// Method	: ClsObject
// FullName	: CBulletObject::ClsObject
// Access	: public 
// Returns	: bool
//****************************************************************


bool CBulletObject::ClsObject()
{
	CDrawObject::DrawPencil(m_nPosX, m_nPosY, M_CLEAR, COLOUR_A);
	//跳过河流和草;
	if (m_pMapObject->GetMapValue(m_nPosX, m_nPosY)!=M_VALUE_WATER&&
		m_pMapObject->GetMapValue(m_nPosX, m_nPosY) != M_VALUE_FOREST)
	{
		m_pMapObject->SetMapValue(m_nPosX, m_nPosY, M_VALUE_EMPTY);
	}
	return true;
}



//****************************************************************
// Brief 	: 让子弹飞;
// Method	: BulletFly
// FullName	: CBulletObject::BulletFly
// Access	: public 
// Returns	: bool
//****************************************************************



bool CBulletObject::BulletFly( vector<CTankObject>& vecTank,  vector<CBulletObject>& vecBullet)
{
	CBulletObject BulletTemp = *this;
	switch (m_nDir)
	{
	case	DIR_UP:		BulletTemp.m_nPosY--;		break;
	case	DIR_DW:		BulletTemp.m_nPosY++;		break;
	case	DIR_LF:		BulletTemp.m_nPosX--;		break;
	case	DIR_RH:		BulletTemp.m_nPosX++;		break;
	}

	 //碰撞检测;
	if (BulletTemp.BulletCollisio(vecTank,vecBullet))
	{
		this->ClsObject();
		//重画河流;
		if (m_pMapObject->GetMapValue(m_nPosX, m_nPosY) == M_VALUE_WATER)
		{
			CDrawObject::DrawPencil(m_nPosX, m_nPosY, M_WATER, COLOUR_A);
			m_pMapObject->SetMapValue(m_nPosX, m_nPosY, M_VALUE_WATER);
		}

		//重画草;
		if (m_pMapObject->GetMapValue(m_nPosX, m_nPosY) == M_VALUE_FOREST)
		{
			CDrawObject::DrawPencil(m_nPosX, m_nPosY, M_FOREST, COLOUR_A);
			m_pMapObject->SetMapValue(m_nPosX, m_nPosY, M_VALUE_FOREST);
		}
		*this = BulletTemp;
		this->DrawObject();
	}
	else
	{
		//碰撞检测失败标记子弹失效;
		this->ClsObject();
		this->m_bIsDie = false;		
	}


	return true;
}


//****************************************************************
// Brief 	: 子弹碰撞检测;
// Method	: BulletCollisio
// FullName	: CBulletObject::BulletCollisio
// Access	: public 
// Returns	: bool
// Parameter: vector<CTankObject> vecTank
// Parameter: vector<CBulletObject> vecBullet
//****************************************************************



bool CBulletObject::BulletCollisio( vector<CTankObject>& vecTank,  vector<CBulletObject>& vecBullet)
{
	//临时TankID;
	int nID = -1;

	switch (m_pMapObject->GetMapValue(m_nPosX,m_nPosY))
	{
	case M_VALUE_EMPTY:
		return true;
		break;
	case M_VALUE_BORDER:
		return false;
		break;
	case M_VALUE_STEEL:
		if (this->m_nLevel<2)
		{
			return false;
			break;
		}
		CDrawObject::DrawPencil(this->m_nPosX, this->m_nPosY, M_CLEAR, COLOUR_A);
		m_pMapObject->SetMapValue(this->m_nPosX, this->m_nPosY, M_VALUE_EMPTY);
		BulletCrit();
		return false;
		break;
	case M_VALUE_WALL:
		CDrawObject::DrawPencil(this->m_nPosX, this->m_nPosY, M_CLEAR, COLOUR_A);
		m_pMapObject->SetMapValue(this->m_nPosX, this->m_nPosY, M_VALUE_EMPTY);
		BulletCrit();
		return false;
		break;
	case M_VALUE_FOREST:
	case M_VALUE_WATER:
		return true;
		break;
	case M_VALUE_HOME:
		//GG!
		vecTank[0].SetIsDie(false);
		vecTank[1].SetIsDie(false);
		break;
		//击中BUFF无效;
	case M_VALUE_REDBUFF:
	case M_VALUE_BLUEBUFF:
		return false;
		break;

		//子弹检测;
	case M_VALUE_BULLET:			
			//获取另一个子弹;
			for (auto& i:vecBullet)
			{
				//坐标相等且同阵营忽略;
				if (*this==i&&
					this->GetGroup()==i.GetGroup())
				{
					break;
				}
				//坐标相等阵营相反都失效;
				else if (*this == i&&
					this->GetGroup() != i.GetGroup())
				{
					i.m_bIsDie = false;
					i.ClsObject();
					this->m_bIsDie = false;
					return false;
					break;
				}
			}
			break;
	case  M_VALUE_TANK_PA:
	case  M_VALUE_TANK_PB:

		//打中玩家;		
		for (unsigned int i = 0; i < 2 ; i++)
		{
			if (*this == vecTank[i])
			{
				if (this->GetGroup() == vecTank[i].GetGroup())
				{
					return false;
					break;
				}
				else
				{
					nID = i;
				}
			}
		}

		//高级别降级;
		if (vecTank[nID].GetLevel()>0)
		{
			int nLevel = vecTank[nID].GetLevel();
			nLevel -= 1;
			vecTank[nID].SetLevel(nLevel);
			return false;
			break;
		}
		else
		{
			//低级GG！
			vecTank[nID].ClsObject();
			vecTank[nID].SetIsDie(false);
			
		}

		return false;
		break;			
	case  M_VALUE_TANK_N2:
	case  M_VALUE_TANK_N3:
	case  M_VALUE_TANK_N4:
	case  M_VALUE_TANK_N5:
	case  M_VALUE_TANK_N6:
	case  M_VALUE_TANK_N7:
	case  M_VALUE_TANK_N8:
	case  M_VALUE_TANK_N9:
		//打中敌军;		
		for (unsigned int i = 2; i < (vecTank.size());i++)
		{
			if (*this==vecTank[i])
			{
				if (this->GetGroup()==vecTank[i].GetGroup())
				{
					return false;
					break;
				}
				else
				{
					nID = i;
				}				
			}
		}

		//高级别降级;
		if (vecTank[nID].GetLevel()>0)
		{
			int nLevel = vecTank[nID].GetLevel();
			nLevel -= 1;
			vecTank[nID].SetLevel(nLevel);

			//加分;
			int nScore = vecTank[this->m_nID % 10].GetScores();
			nScore += 100;
			vecTank[this->m_nID % 10].SetScores(nScore);

			//刷新分数;
			m_pMapObject->DrawScore(vecTank);

			return false;
			break;
		}

		else
		{
			//低级别GG!
			vecTank[nID].ClsObject();
			vecTank[nID].SetIsDie(false);

			//加分;
			int nScore = vecTank[this->m_nID % 10].GetScores();
			nScore += 200;
			vecTank[this->m_nID % 10].SetScores(nScore);

			//刷新分数;
			m_pMapObject->DrawScore(vecTank);

			return false;
			break;
		}
	default:
		break;
	}
	return true;
}


//****************************************************************
// Brief 	: 子弹暴击;
// Method	: BulletCrit
// FullName	: CBulletObject::BulletCrit
// Access	: public 
// Returns	: void
// Parameter: vector<CBulletObject> & vecBullet
//****************************************************************

void CBulletObject::BulletCrit()
{
	if ((this->m_nPosX > 1 || this->m_nPosX < 57) &&
		(this->m_nDir == DIR_UP || this->m_nDir == DIR_DW)
		&& this->m_nLevel>0)
	{
		CDrawObject::DrawPencil(this->m_nPosX + 1, this->m_nPosY, M_CLEAR, COLOUR_A);
		m_pMapObject->SetMapValue(this->m_nPosX + 1, this->m_nPosY, M_VALUE_EMPTY);
		CDrawObject::DrawPencil(this->m_nPosX - 1, this->m_nPosY, M_CLEAR, COLOUR_A);
		m_pMapObject->SetMapValue(this->m_nPosX - 1, this->m_nPosY, M_VALUE_EMPTY);
		return;
	}
	else if ((this->m_nPosY > 1 || this->m_nPosY < 47) &&
		(this->m_nDir == DIR_LF || this->m_nDir == DIR_RH)
		&& this->m_nLevel>0)
	{
		CDrawObject::DrawPencil(this->m_nPosX, this->m_nPosY + 1, M_CLEAR, COLOUR_A);
		m_pMapObject->SetMapValue(this->m_nPosX, this->m_nPosY+1, M_VALUE_EMPTY);
		CDrawObject::DrawPencil(this->m_nPosX, this->m_nPosY - 1, M_CLEAR, COLOUR_A);
		m_pMapObject->SetMapValue(this->m_nPosX, this->m_nPosY-1, M_VALUE_EMPTY);
		return;
	}
}

//****************************************************************
// Brief 	: 子弹与子弹对比;
// Method	: operator==
// FullName	: CBulletObject::operator==
// Access	: public 
// Returns	: bool
// Parameter: CBulletObject & BulletObject
//****************************************************************



bool CBulletObject::operator==(CBulletObject & BulletObject)
{
	if (this->m_nPosX==BulletObject.GetPosX()&&
		this->m_nPosY==BulletObject.GetPosY())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//****************************************************************
// Brief 	: 子弹与坦克对比;
// Method	: operator==
// FullName	: CBulletObject::operator==
// Access	: public 
// Returns	: bool
// Parameter: CTankObject & TankObject
//****************************************************************


bool CBulletObject::operator==(CTankObject & TankObject)
{

	//遍历坦克形状;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//循环检测9个点;
			int nTempX = TankObject.GetPosX() + i - 1;
			int nTempY = TankObject.GetPosY() + j - 1;

			//存在相等即打中;
			if(nTempX==m_nPosX&&
				nTempY==nTempY)
			{
				return true;
			}

		}
	}
	//未检测到没打中;
	return false;
}


//****************************************************************
// Brief 	: 坦克信息赋值给子弹;等号重载;
// Method	: operator=
// FullName	: CBulletObject::operator=
// Access	: public 
// Returns	: bool
// Parameter: const CTankObject & TankObject
//****************************************************************


bool CBulletObject::operator=(const CTankObject& TankObject)
{
	m_bIsDie = TankObject.GetIsDie();
	m_bGroup = TankObject.GetGroup();

	m_nPosX = TankObject.GetPosX();
	m_nPosY = TankObject.GetPosY();
	m_nDir = TankObject.GetDir();

	m_nID = TankObject.GetID();
	m_nLevel = TankObject.GetLevel();
	m_nSpeed = TankObject.GetSpeed() * 2;
	m_pMapObject = TankObject.GetMapObject();

	return true;
}

