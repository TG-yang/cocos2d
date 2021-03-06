#include "WeaponSprite.h"
#include "BaseLayer.h"
// 定义 每个弓箭之间的间距是20
#define  SPA 4

USING_NS_CC;
bool WeaponSprite::initWithTexture(CCTexture2D *pTexture){
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture));
		// 初始话跑动的子弹
		this->pRunBulletsPool=CCArray::create();
		this->pRunBulletsPool->retain();
		//this->speed=10;
		this->hudu=0;
		bRet=true;
	} while (0);
	return bRet;
}


void WeaponSprite::initIdleBulletSpool(CCLayer* player){
	// 创建 50个 子弹的纹理图片 这样做的目的是为了 加速游戏的 运行速度
	CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey("wq0.png");
	batchNode = CCSpriteBatchNode::createWithTexture(texture,50);
	batchNode->setPosition(CCPointZero);
	player->addChild(batchNode,2);
	// 初始化子弹池
	pIdleBulletsPool=CCArray::create();
	pIdleBulletsPool->retain();
    
	this->loadedArray=CCArray::create();
	loadedArray->retain();
	this->setZOrder(1);
	for(int i=0;i<50;i++){
		// 创建子弹
		BulletsSprite* pbullet=BulletsSprite::createWithTexture(batchNode->getTexture());
		// 把子弹的坐标设置成和当前武器的坐标是一样的
		pbullet->setPosition(this->getPosition());
        
		pbullet->setAnchorPoint(ccp(0,0.5));
        
		
		// 设置子弹的移动速度为50
		pbullet->setMovespeed(10);
		pbullet->setHurt(10);
		// 把子弹放到子弹池中
		this->pIdleBulletsPool->addObject(pbullet);
		pbullet->setVisible(false);
		// 把创建好的子弹放到 CCSpriteBatchNode 让其一次渲染
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
	// 表示需要发射 需要把 在枪膛中的子弹添加到 发射子弹中
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
			// 一下这些特别注意在获取  在获取子弹的时候进行初始化
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
		// 如果 在箭堂里面的子弹是 大于 2 的时候需要均匀的分布在 箭堂 里面  规定两个 弓箭之间的角度是20度
		bool isEven=cout%2==0?true:false;// 判断箭堂里面的弓箭是不是偶数
		int  pair=cout/2;// 能分成几对
		int  temsp=(cout-1)*SPA;// 得到所有弓箭之间的夹角
		for(int i=0;i<ptemar->count();i++){
			BulletsSprite* pbul=(BulletsSprite*)ptemar->objectAtIndex(i);
			
            
			
			// 表示中间哪里没有弓箭 反之刚好中间哪里有弓箭
			if (isEven){
				if(i<pair){ // 表示上半部分
					// 旋转 计算出旋转的角度
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
				if(i<pair){ // 表示上半部分
					// 旋转 计算出旋转的角度
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
	// 获取当前武器旋转的角度
	float zhuwuqi= this->hudu*180/PI;
	
	if(this->loadedArray){
		if(this->loadedArray->count()>0){
			for(int i=0;i<this->loadedArray->count();i++){
                BulletsSprite* pbul=(BulletsSprite*)loadedArray->objectAtIndex(i);
                float temr=pbul->getFirstRoto();
                pbul->setRotation(temr+zhuwuqi);
                // 设置最后当前武器最后一次的 旋转角度
                pbul->setLastRoto(temr+zhuwuqi);
			}
		}
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
}