//
//  Color.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 02/10/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Color_h
#define Color_h

#include "SDL.h"

struct Color
{
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

#endif /* Color_h */
