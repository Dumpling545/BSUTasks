#pragma once
class ColouredDetail
{
    public:
        virtual int getColor();
        ColouredDetail();
        bool operator==(ColouredDetail detail);
        bool operator>=(ColouredDetail detail);
    protected:
        int color = 0;
};
