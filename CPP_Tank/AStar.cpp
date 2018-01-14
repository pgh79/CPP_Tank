#include "stdafx.h"
#include "AStar.h"


CAStar::CAStar()
{
}


CAStar::~CAStar()
{
}


// ****************************************************************
// Brief 	: A��Ѱ·����;
// Method	: Astar
// FullName	: CAStar::AStar
// Access	: public 
// Returns	: bool
// Parameter: vector<CTankObject> & vecTank
// ****************************************************************

bool CAStar::Astar(CMapObject* pMap, const CTankObject& TankObj,const vector<CTankObject>& vecTank)
{

	//��ʼ������;
	if (!InitCoord(TankObj, vecTank))
	{
		return false;
	}


	//���µ�ͼ;
	InitMapInfo(TankObj,pMap);


	//Ѱ·;
	if (FindPath())
	{
		//��ȡ·��;
		GetPath();
		return true;
	}
	else
		return false;

}

// ****************************************************************
// Brief 	: ��ʼ������;
// Method	: InitCoord
// FullName	: CAStar::InitCoord
// Access	: private 
// Returns	: void
// Parameter: vector<CTankObject> & vecTank
// ****************************************************************

bool CAStar::InitCoord(const CTankObject& TankObj,const vector<CTankObject>& vecTank)
{
	m_Star.X = TankObj.GetPosX();
	m_Star.Y = TankObj.GetPosY();


	m_End.X = vecTank[0].GetPosX();
	m_End.Y = vecTank[0].GetPosY();

	//����ͬһ����ʹ��ʮ��Ѱ·;
	if (m_Star.X == m_End.X || m_Star.X == m_End.X + 1 || m_Star.X == m_End.X - 1
		|| m_Star.Y == m_End.Y || m_Star.Y == m_End.Y + 1 || m_Star.X == m_End.Y - 1)
	{
		return false;
	}


	//�޶�������Χ;
	if (abs(m_Star.X - m_End.X) > 20 || abs(m_Star.Y - m_End.Y) > 20)
	{
		return false;
	}

	m_bIsCoordInit = true;
	return true;

}

// ****************************************************************
// Brief 	: ��ʼ��Ѱ·��ͼ;
// Method	: InitMapInfo
// FullName	: CAStar::InitMapInfo
// Access	: private 
// Returns	: void
// ****************************************************************

void CAStar::InitMapInfo(const CTankObject& TankObj,CMapObject* pMap)
{
	//�����ͼ;
	m_pMapObject = pMap;
	memcpy_s(nArr, sizeof(int) * 75 * 50, m_pMapObject->GetPMap(), sizeof(int) * 75 * 50);

	for (int i = 1; i < M_HEIGHT - 1; i++)
	{
		for (int j = 1; j < M_WIDTH - 1; j++)
		{

			if (nArr[i][j] != M_VALUE_EMPTY
				|| nArr[i][j] != TankObj.GetID())
			{
				nArr[i][j] = 1;
			}
			else
			{
				nArr[i][j] = 0;
			}
		}
	}

	m_bIsMapInit = true;
}

// ****************************************************************
// Brief 	: ����·��;
// Method	: FindPath
// FullName	: CAStar::FindPath
// Access	: private 
// Returns	: bool
// ****************************************************************

bool CAStar::FindPath()
{

	//�жϳ�ʼ��;
	if (!m_bIsMapInit || !m_bIsCoordInit)
	{
		return false;
	}

	//��ձ�;
	m_Open.clear();
	m_Close.clear();

	//������Open��;
	NODE_INFO nodeStart;
	nodeStart.codSelf = m_Star;
	nodeStart.codSelf.NewDir = 1;
	nodeStart.GPath = 0;
	nodeStart.SetH_F(m_Star, m_End);

	m_Open.push_back(nodeStart);

	//ѭ��Ѱ·;
	while (true)
	{
		//Open��Ϊ��;δ�ҵ�·��;
		if (m_Open.empty())
		{
			return false;
		}

		//��Open�����ҵ�Fֵ��С�ĵ���ɢ;
		int nIndex = 0;
		for (unsigned int i = 1; i < m_Open.size(); i++)
		{
			if (m_Open[nIndex].FPath > m_Open[i].FPath)
			{
				nIndex = i;
			}
		}

		//��ɢ�ĸ���;
		NODE_INFO nodeNew[4];
		//��;
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//��;
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;
		//��;
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//��;
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y;

		//��ֵ����;G;H;F;
		for (int j = 0; j < 4; j++)
		{
			nodeNew[j].codParent = m_Open[nIndex].codSelf;
			nodeNew[j].codSelf.NewDir = j;
			nodeNew[j].GPath = m_Open[nIndex].GPath + 1;

			nodeNew[j].SetH_F(nodeNew[j].codSelf, m_End);
		}

		//��ӻ��㵽Close��;����Open����ɾ��;
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//ѭ���ж��ĸ����Ƿ�ϸ�;
		for (int i = 0; i < 4; i++)
		{
			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//�ж��Ƿ����յ�;�Ǿ�ֱ�ӷ���;˵���ѵ���;
			//̹������ϴ�;�ж���̹���������ܵ��ĸ���;
			bool flag1 = nodeNew[i].codSelf.X == m_End.X && nodeNew[i].codSelf.Y == m_End.Y - 2;	//��;
			bool flag2 = nodeNew[i].codSelf.X == m_End.X && nodeNew[i].codSelf.Y == m_End.Y + 2;	//��;
			bool flag3 = nodeNew[i].codSelf.Y == m_End.Y && nodeNew[i].codSelf.X == m_End.X - 2;	//��;
			bool flag4 = nodeNew[i].codSelf.Y == m_End.Y && nodeNew[i].codSelf.X == m_End.X + 2;	//��;

			if (flag1 || flag2 || flag3 || flag4)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}

			//�ж��Ƿ�Խ��;
			if (x < 1 || x >= M_WIDTH2 - 2 ||
				y<1 || y >= M_HEIGHT - 2)
			{
				continue;
			}

			//������������;
			if (nodeNew[i].FPath>m_Close[nIndex].FPath)
			{
				continue;
			}


			bool flag5 = false;
			for (int k = x - 1; k <= x + 1; k++)
			{
				for (int m = y - 1; m <= y + 1; m++)
				{
					if (m_pMapObject->GetMapValue(k, m))
					{
						flag5 = true;
					}
				}
			}
			if (flag5)
			{
				continue;
			}



			//�ж��Ƿ���Open���Close����;
			bool bRet = false;
			for (unsigned int n = 0; n < m_Open.size(); n++)
			{
				if (nodeNew[i].codSelf == m_Open[n].codSelf)
				{
					bRet = true;
					break;
				}
			}
			if (bRet)
				continue;
			for (unsigned int m = 0; m < m_Close.size(); m++)
			{
				if (nodeNew[i].codSelf == m_Close[m].codSelf)
				{
					bRet = true;
					continue;
				}
			}
			if (bRet)
				continue;

			//���ϸ�����Open��;
			m_Open.push_back(nodeNew[i]);
		}

	}
}

// ****************************************************************
// Brief 	: ���ݲ���·��;
// Method	: GetPath
// FullName	: CAStar::GetPath
// Access	: private 
// Returns	: void
// ****************************************************************

void CAStar::GetPath()
{
	//���;
	m_Path.clear();

	int nIndex = m_Close.size() - 1;

	//ѭ������;����;
	while (true)
	{
		for (unsigned int i = 0; i < m_Close.size(); i++)
		{
			if (m_Close[nIndex].codSelf == m_Star)
			{
				return;
			}
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				m_Path.push_back(m_Close[nIndex].codParent);
				nIndex = i;
				break;
			}
		}
	}


	return;
}
