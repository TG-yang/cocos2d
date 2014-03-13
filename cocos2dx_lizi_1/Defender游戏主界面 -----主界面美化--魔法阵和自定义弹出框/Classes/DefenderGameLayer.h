#ifndef __DEFENDERGAME_LAYER_H__
#define __DEFENDERGAME_LAYER_H__
#include "BaseLayer.h"
#include "MonsterSystem.h"
// ���������Ϸ����
class DefenderGameLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(DefenderGameLayer);
	virtual void onEnter();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	~DefenderGameLayer();
private:
	bool setUpdateViews();
	void detectd(float tim);// �������������ȡ�ж��ӵ��Ƿ���ײ �Ƿ���Ի�ȡ�ӵ�
	// ��������ת����ִ�����ʱ��ִ������ص�����
	void weapCallBack(cocos2d::CCNode* pSend);
	MonsterSystem* monsterSystem;
    void releaseMonster(float tim);// ���������������ʱ�ͷŹ����
	void stopGameCallBack(cocos2d::CCObject* psed);
};
#endif