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
    if( pRet )
    {
        pRet->autorelease();
        pRet->gameMainLayer = pLayer;
        pRet->init();
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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("walk/walk.plist");
    g_hero = CCSprite::createWithSpriteFrameName("walkF_1.png");
    gameMainLayer->addChild( g_hero );
    return true;
}

void HeroClass::moveToward(cocos2d::CCPoint target)
{
    CCPoint fromP = gameMainLayer->tilePositionFromLocation(g_hero->getPosition());
    CCPoint toP = gameMainLayer->tilePositionFromLocation(target);
    
    if( fromP.equals(toP) )
    {
        return;
    }
    
    if( gameMainLayer->isWallAtTileCoord(toP) )
    {
        return;
    }
    
    CCLog("crazy MoveToward from (%f, %f)", fromP.x, fromP.y);
    CCLog("crazy MoveToward to (%f, %f)", toP.x, toP.y);
}


