#ifndef __MONSTER_SYSTEM_H__
#define __MONSTER_SYSTEM_H__
#include "cocos2d.h"
#include "MonsterSprite.h"

#include "BulletsSprite.h"
typedef struct MonsterUtils{
	float initBlood;// ��ʼ����Ѫ
	float initSpeed;// ��ʼ���ٶ�
	float defend;// ����ķ�����
	float hurt;// ������˺�ֵ
	char* monsName;// �����ù����ʱ���ͨ������
	char* picName;// �����ͼƬ
	char* fileName;// ��������Ӧ��plist �ļ�������
	int   type;// ��������
	int   runCount;// ���ܶ�������
	int   actCount;// ������������
	int   detCount;// ������������
	float maxRun;// ����ƶ�����	
	char* attackRangeRec;//���ڹ������ϻ���һ���ܵ��Ĺ�����Χ ���������ò������ ͼƬ �������ܵ�������ʱ�������һ�� �ַ����� ��ʽ��������{{x,y},{w, h}}
} Monster;
class DefenderGameLayer;
// ����������������ϵͳ
class MonsterSystem{
public:
	MonsterSystem();
	~MonsterSystem();
	cocos2d::CCArray* getIdleMonsterArry();// ����������еĹ���
	cocos2d::CCArray* getRunMonsterArray();// �����������ڱ����еĹ���
	void addMonster(int type,int count);// �������̵߳�����ԶԶ���ϵĲ�������
	void setDefenderGameLayer(DefenderGameLayer* defenderGameLayer);
	bool collisionDetection(BulletsSprite* bulletsSprite);// ���빭�� ����Ƿ�͹��﷢����ײ
	void recoverMonster(MonsterSprite* monsterSprite);// ���չ���
private:
	cocos2d::CCArray* idleMonsterArry;// ����������еĹ���
	cocos2d::CCArray* runMonsterArray;// �����������ڱ����еĹ���
    MonsterSprite*    productMonster(int type);//����������������Ӧ�Ĺ�������� 
	DefenderGameLayer* defenderGameLayer;// ��Ϸ����
	void addDefenderGameLayer(MonsterSprite* monsterSprite);// �ѱ����еĹ�����ӵ� ����������
	Monster dutu;// ÿ������µĹ��ﶼ��Ҫ���������һ�� �����ڹ��췽�������ʼ��
};
#endif