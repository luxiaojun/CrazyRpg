//
//  ShortPathStep.cpp
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-4.
//
//

#include "ShortPathStep.h"

ShortPathStep* ShortPathStep::initWithPosition(cocos2d::CCPoint iPos)
{
    ShortPathStep *pRet = new ShortPathStep();
    if( pRet != NULL )
    {
        pRet->position = iPos;
        pRet->hScore = 0;
        pRet->gScore = 0;
        pRet->parent = NULL;
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ShortPathStep::isEqualOther(ShortPathStep *iOther)
{
    return position.equals(iOther->position);
}

int ShortPathStep::getFscore()
{
    return gScore + hScore;
}