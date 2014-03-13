#ifndef __MAGICMATRIX_SPRITE_H__
#define __MAGICMATRIX_SPRITE_H__
#include "cocos2d.h"
//������ħ������
class MagicMatrixSprite:public cocos2d::CCNode{
public:
      MagicMatrixSprite();
	  ~MagicMatrixSprite();
	  CC_SYNTHESIZE(float,hurt,Hurt);// �˺�ֵ
	  CC_SYNTHESIZE(bool,avail,Avail);//�Ƿ����  
	  CC_PROPERTY(bool,activation,Activation);// �Ƿ񼤻�ħ����
	  // ע��һ��ͼƬ������ڻ�������
	  static MagicMatrixSprite* createWithPic(char* pMagicPic,char* pMagicPicBg); // ��һ������CD �ıȽϰ�����ͼƬ �ڶ����Ǳ����Ķ���
	  CC_SYNTHESIZE(float,mana,Mana);// ����ħ��ֵ
	  void runMagicCDAnimation();// ִ��ħ��CD ����
private:
	  bool setUpdateView(char* pMagicPic,char* pMagicPicBg );
	  cocos2d::CCProgressTimer *ptss;// ħ�����CD ����
	  void runMagicCDAnimationCallBack(cocos2d::CCNode* pSed);
};
#endif
