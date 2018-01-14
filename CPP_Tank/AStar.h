#pragma once
#include "TankObject.h"

class CTankObject;
class CAStar
{
public:
	CAStar();
	~CAStar();	
private:
	//������������;
	typedef struct _MY_COORD :public COORD
	{
		bool operator==(const COORD&cod)
		{
			return (X == cod.X) && (Y == cod.Y);
		}
		void operator=(const COORD& cod)
		{
			X = cod.X;
			Y = cod.Y;
		}
		int NewDir;				 //�·���;		
	}MY_COORD, *PMY_CORRD;

	//Ѱ·��;
	typedef struct _NODE_INFO
	{
		int GPath;	//�ƶ����;
		int HPath;	//�����յ���̾���;
		int FPath;	//G+H;

		void SetH_F(const COORD& cod1, const COORD& cod2)
		{
			HPath = abs(cod1.X - cod2.X) + abs(cod1.Y - cod2.Y);
			FPath = GPath + HPath;
		}

		MY_COORD codSelf;		 //��������;
		MY_COORD codParent;		 //������;			
	}NODE_INFO, *PNODE_INFO;

	//��ͼ����;
	int nArr[M_HEIGHT][M_WIDTH] = {};

	COORD m_Star;				//���;
	COORD m_End;				//�յ�;

	vector<NODE_INFO> m_Open;	//������;
	vector<NODE_INFO> m_Close;	//�Ѽ���;

	bool m_bIsMapInit;			//�жϵ�ͼ��ʼ�����;
	bool m_bIsCoordInit;		//�ж������ʼ�����;	

	bool InitCoord(const CTankObject& TankObj,const vector<CTankObject>& vecTank);	//��ʼ������;
	void InitMapInfo(const CTankObject& TankObj,CMapObject * pMap);					//��ʼ����ͼ;

	bool FindPath();			//�������·���ĵ�;
	void GetPath();				//�õ����·��;
	CMapObject* m_pMapObject;	//��ͼ;

public:
	bool Astar(CMapObject* pMap, const CTankObject& TankObj, const vector<CTankObject>& vecTank);//������;
	vector<MY_COORD>  m_Path;	//���·������;
};

