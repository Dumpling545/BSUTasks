#pragma once
enum Direction{
    BACKWARD = -1,
    FORWARD = 1
};
class Reversable
{
    public:
        Reversable();
        void reverse();
        virtual void onReverse() = 0;
        Direction direction = Direction::FORWARD;
};
