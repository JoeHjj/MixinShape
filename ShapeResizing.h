#pragma once

#include <iostream>
#include "RotatableRectangle.h"

class ShapeResizing /*: public IShapeTransform*/
{

public:
    void Drag(int /*x*/, int /*y*/, RotatableRectangle& /*resultingShape*/)
    {
    }

    void Resize(int w, int h, RotatableRectangle& resultingShape)
    {
        std::cout  <<"Resizing by " <<w <<"," << h << std::endl;
        resultingShape.width += w;
        resultingShape.height += h;
    }

    void Rotate(float /*angleRad*/, RotatableRectangle& /*resultingShape*/)
    {
    }
};
