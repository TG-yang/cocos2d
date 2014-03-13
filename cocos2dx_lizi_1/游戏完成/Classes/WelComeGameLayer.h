#ifndef __WELCOMEGAME_LAYER_H__
#define __WELCOMEGAME_LAYER_H__
#include "BaseLayer.h"
class WelComeGameLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(WelComeGameLayer);
	virtual void onEnter();
private:
	// s设置界面
	bool setUpdateView();
	// 播放或者暂停音乐回调函数
	void vedioOnAndOffCallBack(cocos2d::CCObject* pSend);
	// 跳转的 关于开发者界面的回调函数
	void menuCoderCallback(cocos2d::CCObject* pSend);
	// 开始游戏 按钮回调方法
	void menuStarGame(cocos2d::CCObject* pSend);
	// 升级系统回调方法
	void menuUpGameCallback(cocos2d::CCObject* pSend);
	//退出游戏回调方法
	void menuGameOverCallback(cocos2d::CCObject* pSend);
    
};
#endif