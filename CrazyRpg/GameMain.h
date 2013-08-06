//
//  GameMain.h
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-1.
//
//

#ifndef __CrazyRpg__GameMain__
#define __CrazyRpg__GameMain__

#include "cocos2d.h"

USING_NS_CC;

class HeroClass;

class GameMain:public CCLayer
{
public:
    CREATE_FUNC(GameMain);
    
    virtual bool init();
    virtual void registerWithTouchDispatcher();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void draw();
    CCTMXTiledMap *gameMap;
    CCTMXLayer *m_groundLayer;
    CCSize m_fMapSize;
    HeroClass *m_hero;
    
public:
    CCPoint tilePositionFromLocation(CCPoint location);
    CCPoint locationPositionFromTile(CCPoint tilePos);
    bool isValidTileCoord(CCPoint tileCoord);
    bool isPropAtTileCoordForLayer(char *pProp, CCPoint tileCoord, CCTMXLayer *pLayer);
    bool isWallAtTileCoord(CCPoint tileCoord);
    void walkableAdjacentTilesCoordForTileCoord(CCPoint tileCoord, CCPoint *array);
};

#endif /* defined(__CrazyRpg__GameMain__) */
