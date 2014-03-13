#ifndef __WEAPON_SPRITE_H__
#define __WEAPON_SPRITE_H__
#include "cocos2d.h"
#include "BulletsSprite.h"
#include "MagicMatrixSprite.h"
// 这个是武器系统 用来发射子弹
class WeaponSprite:public cocos2d::CCSprite{
public:
	WeaponSprite();
	
	~WeaponSprite();
	
	CREATE_FUNC(WeaponSprite);
	
	virtual bool initWithTexture(cocos2d::CCTexture2D *pTexture);
	
	static WeaponSprite* createWithTexture(cocos2d::CCTexture2D *pTexture);
	cocos2d::CCArray* getIdleBullet(int cout);// 根据目前武器系 的级别获取当前 子弹的数量 默认级别是1个 空闲的子弹
	void recoverBullet(BulletsSprite* pbullet);// 回收掉一个子弹
	void initIdleBulletSpool(cocos2d::CCLayer* pLayer);// 初始化子弹池
	CC_SYNTHESIZE(bool,stop,Stop);
	// 设置当前的武器旋转的弧度制
	void setHudu(float hudu);
	inline cocos2d::CCSpriteBatchNode* getBatchNode(){
		return batchNode;
	}
	inline	cocos2d::CCArray* getRunBulletsPool(){
		return pRunBulletsPool;
	}
	
	inline	cocos2d::CCArray* getLoadedArray(){
		return loadedArray;
	}
	// 当武器旋转的时候 正在枪膛里面的弹药也是需要旋转的
	void rotateLoadedBullets();
	// 给武器装备子弹 cout 表示 一次上的子弹的个数
	void loadedBullet(int cout=1);
    
	inline cocos2d::CCArray* getMagicArray(){
		return magicArray;
	}
    
	void initIdleMagicSpool(cocos2d::CCLayer* pLayer);// 初始化魔法矩阵
    
	MagicMatrixSprite* touchMagic(cocos2d::CCPoint point);// 查看触摸的点是否在 魔法阵上 如果等于空表示没在魔法阵上 如果不为空返回当前魔法阵
	CC_SYNTHESIZE(bool, touchMg,TouchMg);// 如果等于true 表示当前在 正在点击 魔法阵
	CC_SYNTHESIZE(MagicMatrixSprite*, magicMatrixSprite,magicMatrixSprite);// 当前触发的魔法阵
    
	void initialization();
    
private:
	cocos2d::CCArray* pIdleBulletsPool;// 空闲子弹池
	cocos2d::CCArray* pRunBulletsPool;// 正在运行的子弹池
	cocos2d::CCSpriteBatchNode* batchNode;// 批量穿件子弹  优化方法
	cocos2d::CCArray* loadedArray;// 这是上膛的子弹 其实就是在弓箭上显示的子弹 这个时候的子弹是待发状态
	cocos2d::CCArray* magicArray;// 魔法阵
	float hudu;// 武器所旋转的弧度值
	void loade(float tim);
	
	
};
#endif