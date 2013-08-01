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

    CCTMXTiledMap *gameMap;
    CCSize m_fMapSize;
    
public:
    CCPoint tilePositionFromLocation(CCPoint location);
    bool isValidTileCoord(CCPoint tileCoord);
    bool isPropAtTileCoordForLayer(char *pProp, CCPoint tileCoord, CCTMXLayer *pLayer);
};

#endif /* defined(__CrazyRpg__GameMain__) */
