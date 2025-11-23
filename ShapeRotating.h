#pragma once

#include <iostream>
#include "RotatableRectangle.h"

class ShapeRotating/* : public IShapeTransform*/
{

public:
    void Drag(int /*x*/, int /*y*/, RotatableRectangle& /*resultingShape*/)
    {
    }

    void Resize(int /*w*/, int /*h*/, RotatableRectangle& /*resultingShape*/)
    {
    }

    void Rotate(float angleRad, RotatableRectangle& resultingShape)
    {
        std::cout  <<"Rotating by " <<resultingShape.angle << std::endl;
        resultingShape.angle += angleRad;
    }
};
