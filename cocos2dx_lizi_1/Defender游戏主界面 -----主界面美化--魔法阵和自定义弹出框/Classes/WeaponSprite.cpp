#include "WeaponSprite.h"
#include "BaseLayer.h"
#include "MagicMatrixSprite.h"
// ���� ÿ������֮��ļ����20
#define  SPA 4

USING_NS_CC;
bool WeaponSprite::initWithTexture(CCTexture2D *pTexture){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture));	
		// ��ʼ���ܶ����ӵ�
		this->pRunBulletsPool=CCArray::create();
		this->pRunBulletsPool->retain();
		this->magicArray=CCArray::create();
		magicArray->retain();
		//this->speed=10;
		this->hudu=0;
		bRet=true;
	} while (0);
	return bRet;
}


void WeaponSprite::initIdleBulletSpool(CCLayer* player){
	// ���� 50�� �ӵ�������ͼƬ ��������Ŀ����Ϊ�� ������Ϸ�� �����ٶ�  
	CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey("game/wq0.png");
	batchNode = CCSpriteBatchNode::createWithTexture(texture,50);		
	batchNode->setPosition(CCPointZero); 
	player->addChild(batchNode,2); 
	// ��ʼ���ӵ���
	pIdleBulletsPool=CCArray::create();
	pIdleBulletsPool->retain();

	this->loadedArray=CCArray::create();
	loadedArray->retain();
	this->setZOrder(1);
	for(int i=0;i<50;i++){
		// �����ӵ�
		BulletsSprite* pbullet=BulletsSprite::createWithTexture(batchNode->getTexture());
		// ���ӵ����������óɺ͵�ǰ������������һ����
		pbullet->setPosition(this->getPosition());

		pbullet->setAnchorPoint(ccp(0,0.5));

		
		// �����ӵ����ƶ��ٶ�Ϊ50
		pbullet->setMovespeed(10);
		pbullet->setHurt(10);
		// ���ӵ��ŵ��ӵ�����
		this->pIdleBulletsPool->addObject(pbullet);
		pbullet->setVisible(false);
		// �Ѵ����õ��ӵ��ŵ� CCSpriteBatchNode ����һ����Ⱦ
		batchNode->addChild(pbullet,-1);
	}
	this->schedule(schedule_selector(WeaponSprite::loade),1);
}
void WeaponSprite::recoverBullet(BulletsSprite* pbullet){
	pbullet->setPosition(this->getPosition());
	pbullet->setRotation(0);
	pbullet->setVisible(false);
	pbullet->setFirstRoto(0);
	pbullet->setLastRoto(0);
	this->pIdleBulletsPool->addObject(pbullet);
	

}

WeaponSprite* WeaponSprite::createWithTexture(CCTexture2D *pTexture)
{
	WeaponSprite *pobSprite = new WeaponSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void WeaponSprite::loade(float tim){

	this->loadedBullet(5);

}
void WeaponSprite::loadedBullet(int cout){  
	if (this->loadedArray->count()!=cout){
		CCArray* tem=this->getIdleBullet(cout);
		for(int i=0;i<tem->count();i++){
		 BulletsSprite* pbul=(BulletsSprite*)tem->objectAtIndex(i);
		 this->loadedArray->addObject(pbul);
		}
	
	}
	// ��ʾ��Ҫ���� ��Ҫ�� ��ǹ���е��ӵ���ӵ� �����ӵ���
	if(this->stop){
		if(this->loadedArray->count()>0){	
			this->pRunBulletsPool->addObjectsFromArray(this->loadedArray);
			for(int i=0;i<this->loadedArray->count();i++){
				this->loadedArray->removeObjectAtIndex(0,false);
				i--;
			}
		}
	}

}
CCArray* WeaponSprite::getIdleBullet(int cout){
	CCArray* ptemar=CCArray::create();

	float zhuwuqi= this->hudu*180/PI;
	for(int i=0;i<cout;i++){
		CCObject* pbul=this->pIdleBulletsPool->objectAtIndex(0);		
		if(pbul){
			BulletsSprite* pbullet=(BulletsSprite*)pbul;
			ptemar->addObject(pbul);
			pbullet->setVisible(true);
			// һ����Щ�ر�ע���ڻ�ȡ  �ڻ�ȡ�ӵ���ʱ����г�ʼ��
			pbullet->setFirstRoto(0);
			pbullet->setLastRoto(zhuwuqi);
			pbullet->setRotation(zhuwuqi);
			this->pIdleBulletsPool->removeObjectAtIndex(0,false);		
		}else {
			BulletsSprite* pbullet=(BulletsSprite*)BulletsSprite::createWithTexture(batchNode->getTexture());
			pbullet->setMovespeed(50);		
			pbullet->setPosition(this->getPosition());
			pbullet->setRotation(0);
			pbullet->setVisible(false);
			pbullet->setFirstRoto(0);
			pbullet->setLastRoto(0);
			batchNode->addChild(pbullet,2);
			i--;

		}

	}


	if(cout>1){	
		// ��� �ڼ���������ӵ��� ���� 2 ��ʱ����Ҫ���ȵķֲ��� ���� ����  �涨���� ����֮��ĽǶ���20��
		bool isEven=cout%2==0?true:false;// �жϼ�������Ĺ����ǲ���ż��
		int  pair=cout/2;// �ֳܷɼ���	
		int  temsp=(cout-1)*SPA;// �õ����й���֮��ļн�
		for(int i=0;i<ptemar->count();i++){		
			BulletsSprite* pbul=(BulletsSprite*)ptemar->objectAtIndex(i);
			
		
			
			// ��ʾ�м�����û�й��� ��֮�պ��м������й���
			if (isEven){					
				if(i<pair){ // ��ʾ�ϰ벿�� 
					// ��ת �������ת�ĽǶ�
					float temro=i*SPA+SPA/2;
					
					pbul->setRotation(-temro+zhuwuqi);
					pbul->setFirstRoto(-temro);
					pbul->setLastRoto(-temro+zhuwuqi);
				}else{
					float temro=(i-pair)*SPA+SPA/2;
					pbul->setRotation(temro+zhuwuqi);
					pbul->setFirstRoto(temro+zhuwuqi);
					pbul->setLastRoto(temro+zhuwuqi);
				}			
			}else{
				if(i<pair){ // ��ʾ�ϰ벿�� 
					// ��ת �������ת�ĽǶ�
					float temro=i*SPA+SPA;
					pbul->setRotation(-temro+zhuwuqi);
					pbul->setFirstRoto(-temro);
					pbul->setLastRoto(-temro+zhuwuqi);
				}else if (i==pair){
					pbul->setRotation(zhuwuqi);
					pbul->setFirstRoto(0);
					pbul->setLastRoto(zhuwuqi);
				}
				else{
					float temro=(i-pair-1)*SPA+SPA;
					pbul->setRotation(temro+zhuwuqi);
					pbul->setFirstRoto(temro);
					pbul->setLastRoto(temro+zhuwuqi);
				}
			}
		}
		
	}



	return ptemar;
}

void WeaponSprite::setHudu(float hudu){
	this->hudu=hudu;	
}
void WeaponSprite::rotateLoadedBullets(){	
	// ��ȡ��ǰ������ת�ĽǶ�
	float zhuwuqi= this->hudu*180/PI;	
	
	if(this->loadedArray){
		if(this->loadedArray->count()>0){
			for(int i=0;i<this->loadedArray->count();i++){
			BulletsSprite* pbul=(BulletsSprite*)loadedArray->objectAtIndex(i);			
			float temr=pbul->getFirstRoto();
			pbul->setRotation(temr+zhuwuqi);
			// �������ǰ�������һ�ε� ��ת�Ƕ�
			pbul->setLastRoto(temr+zhuwuqi);
			}
		}
	}
}


void WeaponSprite::initIdleMagicSpool(cocos2d::CCLayer* pLayer){
	int cout=3;// ���� ħ�������
	for(int i=0;i<cout;i++){
		MagicMatrixSprite* magicMatrixSprite=MagicMatrixSprite::createWithPic("game/jnzt.png","game/jnl.png");
		this->magicArray->addObject(magicMatrixSprite);
		magicMatrixSprite->setAnchorPoint(ccp(0,0));
		float x=pLayer->getContentSize().width-magicMatrixSprite->getContentSize().width*(i+1)-(i+1)*20;
		magicMatrixSprite->setPosition(ccp(x,0));
		magicMatrixSprite->setActivation(true);
		magicMatrixSprite->runMagicCDAnimation();

		pLayer->addChild(magicMatrixSprite,2);
	}

}


WeaponSprite::WeaponSprite(void){
	this->stop=false;
	this->hudu=0;
}


WeaponSprite::~WeaponSprite()
{
	if (this->pIdleBulletsPool)
	{
		this->pIdleBulletsPool->release();
	}
	if (this->pRunBulletsPool)
	{
		this->pRunBulletsPool->release();
	}
	if (this->loadedArray)
	{
		this->loadedArray->release();
	}

	if(this->magicArray){
		this->magicArray->release();
	}
}