#pragma once
#include <windows.h>
#include <vector>
using std::vector;

//方向;
enum DIR_VALUE
{
	DIR_UP = 0,
	DIR_DW = 1,
	DIR_LF = 2,
	DIR_RH = 3,
};

//颜色;
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

//地图数组中保存的值;
enum M_VALUE
{
	M_VALUE_EMPTY	=0,		//空;
	M_VALUE_BORDER	=1,		//边框;
	M_VALUE_STEEL	=2,		//钢板;
	M_VALUE_WALL	=3,		//土墙;
	M_VALUE_FOREST	=4,		//丛林;
	M_VALUE_WATER	=5,		//河水;
	M_VALUE_HOME	=6,		//老家;
	M_VALUE_BULLET  =7,		//子弹;

	M_VALUE_REDBUFF=8,		//红BUFF
	M_VALUE_BLUEBUFF=9,		//蓝BUFF
	M_VALUE_YELLOW = 20,	//黄BUFF

	M_VALUE_TANK_PA = 10,	//玩家A
	M_VALUE_TANK_PB = 11,	//玩家B

	M_VALUE_TANK_N2 = 12,	//NPC
	M_VALUE_TANK_N3 = 13,
	M_VALUE_TANK_N4 = 14,
	M_VALUE_TANK_N5 = 15,
	M_VALUE_TANK_N6 = 16,
	M_VALUE_TANK_N7 = 17,
	M_VALUE_TANK_N8 = 18,
	M_VALUE_TANK_N9 = 19
};

//地图宽高;
#define M_WIDTH	75
#define M_HEIGHT 50
#define M_WIDTH2 60

//障碍物图形;
#define M_BORDER	"□"
#define M_WALL		"▓"
#define M_STEEL		"■"
#define M_WATER		"∷"
#define M_FOREST	"※"
#define M_HOME		"★"

#define M_CLEAR		"  "
#define TANKNODE	"■"
#define BULLETNODE	"◆"
#define SELECT		"●"
#define M_BUFF		"☆"


//声明坦克;
class CTankObject;

class CMapObject
{
public:
	CMapObject();
	~CMapObject();
	bool SetMapValue(int nPosX,	int nPosY,int Value);	//设置地图值;
	int  GetMapValue(int nPosX, int nPosY);				//获取地图值;
	
	void Buff();										//随机生成BUFF
	bool DrawMap();										//绘制地图;
	void ReadMap(int m_nRound);							//根据关卡值读取相应地图;
	bool DIYMap();										//DIY地图主体;
	void DrawGanmeInfo();								//绘制游戏信息;
	void DrawScore(vector<CTankObject>& vecTank);		//绘制分数;
	void DrawScore(int nRound, int nEnemy);				//绘制关卡;敌人数量;

	int** GetPMap() const { return (int **)m_nMap; };		//二维数组强转一维;A星寻路用;
	
private:
	
	bool IniMap();										//初始化地图;
	void DIYMapInfo();									//DIY地图信息;
	void OutPutPos(int nPosX, int nPoxY);				//DIY地图输出坐标;
	bool MouseEventProc(MOUSE_EVENT_RECORD StcMouse);	//鼠标事件;
	bool MouseMove(MOUSE_EVENT_RECORD &StcMouse);		//鼠标拖动;
	bool MouseClick(MOUSE_EVENT_RECORD &StcMouse);		//鼠标点击;
	bool KeyEventProc(KEY_EVENT_RECORD &StcKeyEvent);	//键盘事件;

	void BrushDraw(MOUSE_EVENT_RECORD &StcMouse, char *Pstr, WORD color);	//DIY地图笔刷扩展;
	void SaveMap();															//保存地图;
private:	
	int m_nMapVlue;						//DIY写入地图值;
	int m_nBrush;						//DIY地图笔刷;
	int m_nMap[M_HEIGHT][M_WIDTH] = {};	//地图;
};

