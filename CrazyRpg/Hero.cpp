//
//  Hero.cpp
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-5.
//
//

#include "Hero.h"

HeroClass* HeroClass::initWithLayer(GameMain *pLayer)
{
    HeroClass *pRet = new HeroClass();
    if( pRet && pRet->init() )
    {
        pRet->autorelease();
        pRet->gameMainLayer = pLayer;
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool HeroClass::init()
{
    CCSprite::init();
    
    return true;
}

void HeroClass::moveToward(cocos2d::CCPoint target)
{
    CCPoint fromP = gameMainLayer->tilePositionFromLocation(this->getPosition());
    CCPoint toP = gameMainLayer->tilePositionFromLocation(target);
    
    if( fromP.equals(toP) )
    {
        return;
    }
    
    
}


