//
//  ShortPathStep.h
//  CrazyRpg
//
//  Created by luxiaojun on 13-7-4.
//
//

#ifndef __CrazyRpg__ShortPathStep__
#define __CrazyRpg__ShortPathStep__

#include "cocos2d.h"

USING_NS_CC;

class ShortPathStep
{
public:
    CCPoint position;
    int gScore;
    int hScore;
    ShortPathStep *parent;
    
    static ShortPathStep* initWithPosition(CCPoint iPos);
    int getFscore();
    bool isEqualOther(ShortPathStep *iOther);
};

#endif /* defined(__CrazyRpg__ShortPathStep__) */
