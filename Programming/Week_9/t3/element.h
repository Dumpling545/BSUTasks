#pragma once
class Element
{
    public:
        double value;
        Element * previous;
        Element * next;
        virtual double compute();
};
