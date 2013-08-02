//
//  Hero.h
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-5.
//
//

#ifndef __CrazyRpg__Hero__
#define __CrazyRpg__Hero__

#include "cocos2d.h"
#include "GameMain.h"

USING_NS_CC;

class HeroClass: public CCObject
{
public:
    virtual ~HeroClass();
    CCArray *spOpenSteps;
    CCArray *spClosedSteps;
    GameMain *gameMainLayer;
    CCSprite *g_hero;
    
    bool init();
    static HeroClass* initWithLayer(GameMain *pLayer);
    void moveToward(CCPoint target);
};

#endif /* defined(__CrazyRpg__Hero__) */
