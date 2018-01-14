#pragma once
#include <windows.h>
#include <vector>
using std::vector;

//����;
enum DIR_VALUE
{
	DIR_UP = 0,
	DIR_DW = 1,
	DIR_LF = 2,
	DIR_RH = 3,
};

//��ɫ;
enum COLOR
{
	COLOUR_A = 0x0A,
	COLOUR_B = 0x0B,
	COLOUR_9 = 0x09,
	COLOUR_F = 0x0F,
	COLOUR_D = 0x0D,
	COLOUR_C = 0x0C,
	COLOUR_E = 0x0E,
	COLOUR_BG = 0xA0
};

//��ͼ�����б����ֵ;
enum M_VALUE
{
	M_VALUE_EMPTY	=0,		//��;
	M_VALUE_BORDER	=1,		//�߿�;
	M_VALUE_STEEL	=2,		//�ְ�;
	M_VALUE_WALL	=3,		//��ǽ;
	M_VALUE_FOREST	=4,		//����;
	M_VALUE_WATER	=5,		//��ˮ;
	M_VALUE_HOME	=6,		//�ϼ�;
	M_VALUE_BULLET  =7,		//�ӵ�;

	M_VALUE_REDBUFF=8,		//��BUFF
	M_VALUE_BLUEBUFF=9,		//��BUFF
	M_VALUE_YELLOW = 20,	//��BUFF

	M_VALUE_TANK_PA = 10,	//���A
	M_VALUE_TANK_PB = 11,	//���B

	M_VALUE_TANK_N2 = 12,	//NPC
	M_VALUE_TANK_N3 = 13,
	M_VALUE_TANK_N4 = 14,
	M_VALUE_TANK_N5 = 15,
	M_VALUE_TANK_N6 = 16,
	M_VALUE_TANK_N7 = 17,
	M_VALUE_TANK_N8 = 18,
	M_VALUE_TANK_N9 = 19
};

//��ͼ���;
#define M_WIDTH	75
#define M_HEIGHT 50
#define M_WIDTH2 60

//�ϰ���ͼ��;
#define M_BORDER	"��"
#define M_WALL		"��"
#define M_STEEL		"��"
#define M_WATER		"��"
#define M_FOREST	"��"
#define M_HOME		"��"

#define M_CLEAR		"  "
#define TANKNODE	"��"
#define BULLETNODE	"��"
#define SELECT		"��"
#define M_BUFF		"��"


//����̹��;
class CTankObject;

class CMapObject
{
public:
	CMapObject();
	~CMapObject();
	bool SetMapValue(int nPosX,	int nPosY,int Value);	//���õ�ͼֵ;
	int  GetMapValue(int nPosX, int nPosY);				//��ȡ��ͼֵ;
	
	void Buff();										//�������BUFF
	bool DrawMap();										//���Ƶ�ͼ;
	void ReadMap(int m_nRound);							//���ݹؿ�ֵ��ȡ��Ӧ��ͼ;
	bool DIYMap();										//DIY��ͼ����;
	void DrawGanmeInfo();								//������Ϸ��Ϣ;
	void DrawScore(vector<CTankObject>& vecTank);		//���Ʒ���;
	void DrawScore(int nRound, int nEnemy);				//���ƹؿ�;��������;

	int** GetPMap() const { return (int **)m_nMap; };		//��ά����ǿתһά;A��Ѱ·��;
	
private:
	
	bool IniMap();										//��ʼ����ͼ;
	void DIYMapInfo();									//DIY��ͼ��Ϣ;
	void OutPutPos(int nPosX, int nPoxY);				//DIY��ͼ�������;
	bool MouseEventProc(MOUSE_EVENT_RECORD StcMouse);	//����¼�;
	bool MouseMove(MOUSE_EVENT_RECORD &StcMouse);		//����϶�;
	bool MouseClick(MOUSE_EVENT_RECORD &StcMouse);		//�����;
	bool KeyEventProc(KEY_EVENT_RECORD &StcKeyEvent);	//�����¼�;

	void BrushDraw(MOUSE_EVENT_RECORD &StcMouse, char *Pstr, WORD color);	//DIY��ͼ��ˢ��չ;
	void SaveMap();															//�����ͼ;
private:	
	int m_nMapVlue;						//DIYд���ͼֵ;
	int m_nBrush;						//DIY��ͼ��ˢ;
	int m_nMap[M_HEIGHT][M_WIDTH] = {};	//��ͼ;
};

