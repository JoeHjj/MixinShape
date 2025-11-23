#pragma once

class IShapeTransform
{
public:
    virtual void Drag(int x, int y) const = 0;

    virtual void Resize(int /*w*/, int /*h*/) const = 0;

    virtual void Rotate(float /*angleRad*/) const = 0;
};
