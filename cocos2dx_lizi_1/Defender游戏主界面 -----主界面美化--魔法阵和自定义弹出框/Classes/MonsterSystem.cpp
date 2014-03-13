#include "MonsterSystem.h"
#include "DefenderGameLayer.h"
USING_NS_CC;
MonsterSystem::MonsterSystem(){

	idleMonsterArry= CCArray::create();// ����������еĹ���
	idleMonsterArry->retain();
	this->runMonsterArray=CCArray::create(); // �����������ڱ����еĹ���
	this->runMonsterArray->retain();
	/**********************************************************************
	float initBlood;// ��ʼ����Ѫ
	float initSpeed;// ��ʼ���ٶ�
	float defend;// ����ķ�����
	float hurt;// ������˺�ֵ
	char* picName;// �����ͼƬ
	char* fileName;// ��������Ӧ��plist �ļ�������
	int   type;// ��������
	int   runCount;// ���ܶ�������
	int   actCount;// ������������
	int   detCount;// ������������
	float maxRun;// ����ƶ�����
	float minX; // ��������ĸ�������ʵ ���ڹ������ϻ���һ���ܵ��Ĺ�����Χ ���������ò������ ͼƬ �������ܵ�������ʱ�������һ�� 
	float minY;
	float maxX;
	float maxY;                                                    
	************************************************************************/
	this->dutu.initBlood=100;
	this->dutu.initSpeed=5;
	this->dutu.defend=1;
	this->dutu.hurt=10;
	this->dutu.monsName="dutu";
	this->dutu.picName="monster/dutu.png";
	this->dutu.fileName="monster/dutu.plist";
	this->dutu.type=1;
	this->dutu.runCount=8;
	this->dutu.actCount=14;
	this->dutu.detCount=8;
	this->dutu.maxRun=800*0.14;
	this->dutu.attackRangeRec="{{70,45},{30,110}}";

}

////����������������Ӧ�Ĺ���
MonsterSprite*    MonsterSystem::productMonster(int type){
	if(type==1){
		MonsterSprite* sp=MonsterSprite::createWithMonsterRul(dutu.fileName,CCTextureCache::sharedTextureCache()->textureForKey(dutu.picName),dutu.monsName,dutu.runCount,dutu.actCount,dutu.detCount);
		sp->setHurt(dutu.hurt);
		sp->setDefense(dutu.defend);
		sp->setBlood(dutu.initBlood);
		sp->setSpeed(dutu.initSpeed);
		sp->setmaxRemoving(dutu.maxRun);
		sp->setMonType(dutu.type);
		sp->setMonState(1);
		sp->setAttackRange(CCRectFromString(dutu.attackRangeRec));
		sp->setMonsterSystemUtils(this);
		return sp;
	}
	return NULL;
}
// �ѱ����еĹ�����ӵ� ����������
void MonsterSystem::addDefenderGameLayer(MonsterSprite* monsterSprite){
	// ��ȡ0-1 ֮�����
	float ran=CCRANDOM_0_1();
	CCSize size=this->defenderGameLayer->getContentSize();
	float x=size.width;
	float temp=size.height*ran+monsterSprite->getContentSize().height/2;
	float y=0;
	if (temp>=size.height){
		y=size.height-monsterSprite->getContentSize().height/2;
	}else{
		if(ran!=0){
			if (size.height*ran<monsterSprite->getContentSize().height/2){
				y=temp+10;
			}else {
				y=size.height*ran;
			}

		}else {
			y=monsterSprite->getContentSize().height/2;
		}
	}
	monsterSprite->setAnchorPoint(ccp(0,0.5));
	monsterSprite->setPosition(ccp(x,y));

	if(this->defenderGameLayer){
		this->defenderGameLayer->addChild(monsterSprite,2);
		monsterSprite->runAnimation();
	}
	this->getRunMonsterArray()->addObject(monsterSprite);
}

// ���빭�� ����Ƿ�͹��﷢����ײ
bool MonsterSystem::collisionDetection(BulletsSprite* bulletsSprite){
	bool iscon=false;
	if (this->getRunMonsterArray())
	{
		// �����Ǽ�� ���� �Ƿ�͹��﷢����ײ
		for(int i=0;i<this->getRunMonsterArray()->count();i++){
			MonsterSprite* monsterSprite=(MonsterSprite*)this->getRunMonsterArray()->objectAtIndex(i);
			// �����״̬���벻��������״̬
			if (monsterSprite->getMonState()!=4) 
			{
				// �жϵ�ǰ�Ĺ������ܹ���������ʱ��͹��� �Ƿ�����ײ
			    iscon=bulletsSprite->boundingBox().intersectsRect(monsterSprite->converNowRect());
				if (iscon)
				{
					// ��ʾ�����ܵ����� ����Ҫ���е�Ѫ ����
					monsterSprite->fallBlood(bulletsSprite->getHurt());
					iscon=true;
					break;
				}else{
					continue;
				}
			}

		}
	}
	return iscon;
}

void MonsterSystem::recoverMonster(MonsterSprite* monsterSprite){
	// �������Ĺ����������
	this->getRunMonsterArray()->removeObject(monsterSprite,false);
	// �ӽ������Ƴ���
	this->defenderGameLayer->removeChild(monsterSprite,false);
	// ��ԭ����� ��������
	if(monsterSprite->getMonType()==1){
		monsterSprite->setBlood(dutu.initBlood);
		monsterSprite->setPosition(CCPointZero);
		monsterSprite->setMonType(dutu.type);
		// ͣ�����ж���
		monsterSprite->stopAllActions();
	}
	this->getIdleMonsterArry()->addObject(monsterSprite);
}

;// �������̵߳�����ԶԶ���ϵĲ�������
void MonsterSystem::addMonster(int type,int count){

	for(int i=0;i<count;i++){
		MonsterSprite* runmon=NULL;

		for(int j=0;j<this->getIdleMonsterArry()->count();j++){
			MonsterSprite* temmon=(MonsterSprite*)this->getIdleMonsterArry()->objectAtIndex(j);
			if (temmon->getMonType()==type){
				runmon=temmon;
				break;
			}

		}
		// ����ӿ��е��߳� �õ�����Ҫ�� ��������  ����ӵ������� ��֮ ����Ҫ����һ��
		if (runmon){
			this->getIdleMonsterArry()->removeObject(runmon,false);
			this->addDefenderGameLayer(runmon);
		}else {
			MonsterSprite* temmon= this->productMonster(type);
			if (temmon)
			{
				this->getIdleMonsterArry()->addObject( this->productMonster(type));
				i--;
			}else {
				break;
			}

		}


	}

}
void MonsterSystem::setDefenderGameLayer(DefenderGameLayer* defenderGameLayer){
	this->defenderGameLayer=defenderGameLayer;
}

CCArray* MonsterSystem::getRunMonsterArray(){
	return this->runMonsterArray;

}
CCArray* MonsterSystem::getIdleMonsterArry(){
	return this->idleMonsterArry;
}

MonsterSystem::~MonsterSystem(){
	if (idleMonsterArry)
	{
		this->idleMonsterArry->autorelease();
	}
	if (runMonsterArray)
	{
		this->runMonsterArray->autorelease();
	}

}