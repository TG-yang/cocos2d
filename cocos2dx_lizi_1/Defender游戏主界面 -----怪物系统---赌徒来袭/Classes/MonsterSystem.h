#ifndef __MONSTER_SYSTEM_H__
#define __MONSTER_SYSTEM_H__
#include "cocos2d.h"
#include "MonsterSprite.h"

#include "BulletsSprite.h"
typedef struct MonsterUtils{
	float initBlood;// 初始化气血
	float initSpeed;// 初始化速度
	float defend;// 怪物的防御力
	float hurt;// 怪物的伤害值
	char* monsName;// 在设置怪物的时候的通用名字
	char* picName;// 怪物的图片
	char* fileName;// 怪物所对应的plist 文件的名字
	int   type;// 怪物类型
	int   runCount;// 奔跑动画张数
	int   actCount;// 攻击动画张数
	int   detCount;// 死亡动画张数
	float maxRun;// 最大移动距离
	char* attackRangeRec;//是在怪物身上划定一个受到的攻击范围 这样可以让不规则的 图片 看起来受到攻击的时候更逼真一点 字符串的 格式是这样的{{x,y},{w, h}}
} Monster;
class DefenderGameLayer;
// 此类是生产和销毁系统
class MonsterSystem{
public:
	MonsterSystem();
	~MonsterSystem();
	cocos2d::CCArray* getIdleMonsterArry();// 用来保存空闲的怪物
	cocos2d::CCArray* getRunMonsterArray();// 用来保存正在奔跑中的怪物
	void addMonster(int type,int count);// 用于主线程调用来远远不断的产生怪物
	void setDefenderGameLayer(DefenderGameLayer* defenderGameLayer);
	bool collisionDetection(BulletsSprite* bulletsSprite);// 传入弓箭 检测是否和怪物发生碰撞
	void recoverMonster(MonsterSprite* monsterSprite);// 回收怪物
private:
	cocos2d::CCArray* idleMonsterArry;// 用来保存空闲的怪物
	cocos2d::CCArray* runMonsterArray;// 用来保存正在奔跑中的怪物
    MonsterSprite*    productMonster(int type);//根据类型来产生响应的怪物的数量
	DefenderGameLayer* defenderGameLayer;// 游戏主类
	void addDefenderGameLayer(MonsterSprite* monsterSprite);// 把奔跑中的怪物添加到 主界面里面
	Monster dutu;// 每次添加新的怪物都需要在这里添加一个 并且在构造方法里面初始化
};
#endif