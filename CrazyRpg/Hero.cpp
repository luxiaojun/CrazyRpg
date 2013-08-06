//
//  Hero.cpp
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-5.
//
//

#include "Hero.h"

HeroClass::~HeroClass()
{
    
}

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
    CCPoint pos = g_hero->getPosition();
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
    
    bool pathFound = false;
    spOpenSteps = CCArray::create();
    spClosedSteps = CCArray::create();
    spOpenSteps->autorelease();
    spClosedSteps->autorelease();
    
    ShortPathStep *myPos = ShortPathStep::initWithPosition(fromP);
    insertInOpenSteps( myPos );
    
    do
    {
        ShortPathStep *curStep = (ShortPathStep*)spOpenSteps->objectAtIndex(0);
        spClosedSteps->addObject(curStep);
        spOpenSteps->removeObjectAtIndex(0);
        
        if( (curStep->position).equals(toP) )
        {
            pathFound = true;
            ShortPathStep *tmp = curStep;
            CCLog("PATH FOUND:");
            do
            {
                CCLog("{%0.1f, %0.1f}", tmp->position.x, tmp->position.y);
                tmp = tmp->parent;
            } while (tmp != NULL);
            spOpenSteps->release();
            spClosedSteps->release();
            break;
        }
        
//        CCArray *adjStep = CCArray::create();
//        adjStep->retain();
        CCPoint adjStep[4] = {ccp(-1, -1), ccp(-1, -1), ccp(-1, -1), ccp(-1, -1)};
        
        gameMainLayer->walkableAdjacentTilesCoordForTileCoord(curStep->position, adjStep);
        CCLog("dfdfd");
        for(int i=0;i<4;i++)
        {
            CCPoint pos = adjStep[i];
            if( pos.x < 0 && pos.y < 0 )
                continue;
            ShortPathStep *step = ShortPathStep::initWithPosition(pos);
            
            if( spClosedSteps->containsObject(step) )
            {
                step->release();
                continue;
            }
            
            int moveCost = costToMoveFromStep(curStep, step);
            
            unsigned int index = spOpenSteps->indexOfObject(step);
            if( index == CC_INVALID_INDEX )
            {
                step->parent = curStep;
                step->gScore = curStep->gScore + moveCost;
                step->hScore = computeHScoreFromCoord(step->position, toP);
                
                insertInOpenSteps(step);
                step->release();
            }
            else
            {
                step->release();
                
                step = (ShortPathStep*)spOpenSteps->objectAtIndex(index);
                if( (curStep->gScore+moveCost) < step->gScore )
                {
                    step->gScore = curStep->gScore + moveCost;
                    
                    step->retain();
                    
                    spOpenSteps->removeObjectAtIndex(index);
                    
                    insertInOpenSteps(step);
                    
                    step->release();
                }
            }
        }
    } while ( spOpenSteps->count() > 0 );
    
    
    
    
    if( !pathFound )
    {
        CCLog("crazy path not found");
    }
}

void HeroClass::insertInOpenSteps(ShortPathStep *step)
{
    int stepFScore = step->getFscore();
    int count = spOpenSteps->count();
    int i = 0;
    for(;i<count;i++)
    {
        if( stepFScore <= ((ShortPathStep*)spOpenSteps->objectAtIndex(i))->getFscore() )
        {
            break;
        }
    }
    
    spOpenSteps->insertObject((CCObject*)step, i);
}

int HeroClass::computeHScoreFromCoord(cocos2d::CCPoint fromPos, cocos2d::CCPoint toPos)
{
    int ret = 0;
    ret = abs(fromPos.x - toPos.x) + abs(fromPos.y - fromPos.y);
    return ret;
}

int HeroClass::costToMoveFromStep(ShortPathStep *fromStep, ShortPathStep *toStep)
{
    return 1;
}