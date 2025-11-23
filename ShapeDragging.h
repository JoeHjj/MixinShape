#pragma once

#include <iostream>
#include "RotatableRectangle.h"

class ShapeDragging /*: public IShapeTransform*/
{

public:
    void Drag(int x, int y, RotatableRectangle& resultingShape) /*override*/
    {
        std::cout  <<"dragging by " <<x <<"," << y << std::endl;
        resultingShape.x += x;
        resultingShape.y += y;
    }

    void Resize(int /*w*/, int /*h*/, RotatableRectangle& /*resultingShape*/) /*override*/
    {
    }

    void Rotate(float /*angleRad*/, RotatableRectangle& /*resultingShape*/) /*override*/
    {
    }
};
