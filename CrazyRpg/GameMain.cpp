//
//  GameMain.cpp
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-1.
//
//

#include "GameMain.h"
#include "Hero.h"

bool GameMain::init()
{
    CCLayer::init();
    
    return true;
}

void GameMain::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void GameMain::onEnter()
{
    CCLayer::onEnter();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);
    gameMap = CCTMXTiledMap::create("tileMap/crazyMap.tmx");
    
    gameMap->setPosition( ccp(winSize.width/2-gameMap->getContentSize().width/2, winSize.height/2-gameMap->getContentSize().height/2) );
    this->addChild( gameMap, 0 );
    m_groundLayer = gameMap->layerNamed("ground");
    m_fMapSize = gameMap->getMapSize();
    
    
    
    m_hero = HeroClass::initWithLayer(this);
    m_hero->g_hero->setPosition( locationPositionFromTile( ccp(0, 0) ) );
    m_hero->retain();
}

void GameMain::onExit()
{
    
}

void GameMain::draw()
{
    
}

bool GameMain::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void GameMain::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint local = pTouch->getLocationInView();
    CCPoint tp = CCDirector::sharedDirector()->convertToGL(local);
    
    m_hero->moveToward(tp);
}

CCPoint GameMain::tilePositionFromLocation(cocos2d::CCPoint location)
{
    CCPoint pos = ccpSub(location, gameMap->getPosition());
    float pointWidth = gameMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR();
    float pointHeight = gameMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
    
    pos.x = (int) (pos.x / pointWidth);
    pos.y = (int)((gameMap->getMapSize().height * pointHeight - pos.y) /pointHeight);
    
    pos.x = fmaxf(0, fminf(gameMap->getMapSize().width-1, pos.x));
    pos.y = fmaxf(0, fminf(gameMap->getMapSize().height-1, pos.y));
    return pos;
}

CCPoint GameMain::locationPositionFromTile(cocos2d::CCPoint tilePos)
{
    CCPoint pos = gameMap->getPosition();
    float pointWidth = gameMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR();
    float pointHeight = gameMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
    pos.x += tilePos.x * pointWidth + pointWidth/2;
    float addHeight = (gameMap->getMapSize().height*pointHeight) - (tilePos.y*pointHeight) - pointHeight/2;
    pos.y += addHeight;
    return pos;
}

bool GameMain::isValidTileCoord(cocos2d::CCPoint tileCoord)
{
    if( tileCoord.x < 0
       || tileCoord.y < 0
       || tileCoord.x >= m_fMapSize.width
       || tileCoord.y >= m_fMapSize.height )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GameMain::isPropAtTileCoordForLayer(char *pProp, cocos2d::CCPoint tileCoord, cocos2d::CCTMXLayer *pLayer)
{
    if( !isValidTileCoord(tileCoord) )
    {
        return false;
    }
    
    int gid = pLayer->tileGIDAt(tileCoord);
    
    CCDictionary *dic = gameMap->propertiesForGID(gid);
    if( dic == NULL )
    {
        return false;
    }
    std::string key = pProp;
    if( dic->objectForKey(key) == NULL )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GameMain::isWallAtTileCoord(cocos2d::CCPoint tileCoord)
{
    bool ret;
    ret = isPropAtTileCoordForLayer((char*)"Wall", tileCoord, m_groundLayer);
    return ret;
}

void GameMain::walkableAdjacentTilesCoordForTileCoord(cocos2d::CCPoint tileCoord, cocos2d::CCArray *array)
{
    CCPoint left = CCPointMake(tileCoord.x-1, tileCoord.y);
    if( isValidTileCoord(left) && !isWallAtTileCoord(left) )
    {
        array->addObject((CCObject*)&left);
    }
    
    CCPoint top = CCPointMake(tileCoord.x, tileCoord.y-1);
    if( isValidTileCoord(top) && !isWallAtTileCoord(top) )
    {
        array->addObject((CCObject*)&top);
    }
    
    CCPoint right = CCPointMake(tileCoord.x+1, tileCoord.y);
    if( isValidTileCoord(right) && !isWallAtTileCoord(right) )
    {
        array->addObject((CCObject*)&right);
    }
    
    CCPoint down = CCPointMake(tileCoord.x, tileCoord.y+1);
    if( isValidTileCoord(down) && !isWallAtTileCoord(down) )
    {
        array->addObject((CCObject*)&down);
    }
}