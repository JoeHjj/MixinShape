#include "Traits.h"

#include"ShapeDragging.h"
#include"ShapeResizing.h"
#include"ShapeRotating.h"

template<typename... Transforms>
class Shape: public Transforms...
{
    using transformTypesList = typeList_t<Transforms...>;

public:

    Shape(Transforms... transforms): Transforms{ std::move(transforms) }... { }

    template<size_t index, size_t lastIndex>
    struct DoTransform
    {
        static void Drag(Shape* shape, int x, int y, RotatableRectangle& resultingShape)
        {
            if constexpr(index < lastIndex)
            {
                using TransformType = selectTypeByIndex_t<index, Shape::transformTypesList>;

                static_cast<TransformType*>(shape)->Drag(x, y, resultingShape);
            }

            if constexpr(index + 1 < lastIndex)
            {
                DoTransform<index + 1, lastIndex>::Drag(shape, x, y, resultingShape);
            }
        }

        static void Resize(Shape* shape, int x, int y, RotatableRectangle& resultingShape)
        {
            if constexpr(index < lastIndex)
            {
                using TransformType = selectTypeByIndex_t<index, Shape::transformTypesList>;

                static_cast<TransformType*>(shape)->Resize(x, y, resultingShape);
            }

            if constexpr(index + 1 < lastIndex)
            {
                DoTransform<index + 1, lastIndex>::Resize(shape, x, y, resultingShape);
            }
        }

        static void Rotate(Shape* shape, float angleRad, RotatableRectangle& resultingShape)
        {
            if constexpr(index < lastIndex)
            {
                using TransformType = selectTypeByIndex_t<index, Shape::transformTypesList>;

                static_cast<TransformType*>(shape)->Rotate(angleRad, resultingShape);
            }

            if constexpr(index + 1 < lastIndex)
            {
                DoTransform<index + 1, lastIndex>::Rotate(shape, angleRad, resultingShape);
            }
        }
    };

    void UpdateShape(RotatableRectangle& resultingShape)
    {
        std::cout << "New shape (x="<<resultingShape.x<<",y="<<resultingShape.y<<")"
                  << " width="<<resultingShape.width<< " height="<<resultingShape.height
                  << " angle="<<resultingShape.angle << std::endl;
    }

    void Drag(int x, int y, RotatableRectangle& resultingShape)
    {
        DoTransform<0, typesCount_v<Transforms...> >::Drag(this, x, y, resultingShape);
        UpdateShape(resultingShape);
    }

    void Resize(int x, int y, RotatableRectangle& resultingShape)
    {
        DoTransform<0, typesCount_v<Transforms...> >::Resize(this, x, y, resultingShape);
        UpdateShape(resultingShape);
    }

    void Rotate(float angleRad, RotatableRectangle& resultingShape)
    {
        DoTransform<0, typesCount_v<Transforms...> >::Rotate(this, angleRad, resultingShape);
        UpdateShape(resultingShape);
    }
};

template<typename... Transforms>
Shape(Transforms...) -> Shape<Transforms...>;

/*
 * ################MAIN################8
 */

int main()
{
    Shape shape { ShapeDragging{}, ShapeResizing{}, ShapeRotating{} };
    RotatableRectangle resultingShape;

    std::cout << "Current shape (x="<<resultingShape.x<<",y="<<resultingShape.y<<")"
              << " width="<<resultingShape.width<< " height="<<resultingShape.height
              << " angle="<<resultingShape.angle << std::endl;


    shape.Drag(10,10, resultingShape);
    shape.Drag(10,10, resultingShape);

    shape.Resize(100,100, resultingShape);

    shape.Rotate(0.8, resultingShape);
    shape.Rotate(0.8, resultingShape);
}
