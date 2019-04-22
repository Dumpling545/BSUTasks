#include "car.h"

Car::Car(int x, int y, int carHeight, COLORREF bodyColor, COLORREF topColor,
            COLORREF windowColor, COLORREF lightColor, COLORREF wheelColor){
    this->x = x;
    this->y = y;
    blockSize = carHeight / 20.0;
    initItems(bodyColor, topColor, windowColor, lightColor, wheelColor);
}
void Car::initItems(COLORREF bodyColor, COLORREF topColor,
            COLORREF windowColor, COLORREF lightColor, COLORREF wheelColor){
    items[ItemFlag::CarBody] = new RectangleItem(x, y + 2*blockSize,
                            40*blockSize, 8*blockSize, bodyColor);
    items[ItemFlag::CarTop] = new RectangleItem(x, y - 6*blockSize,
                            20*blockSize, 8*blockSize, topColor);
    items[ItemFlag::Window_1] = new RectangleItem(x - 5*blockSize, y - 6*blockSize,
                             6*blockSize, 4*blockSize, windowColor);
    items[ItemFlag::Window_2] = new RectangleItem(x + 5*blockSize, y - 6*blockSize,
                             6*blockSize, 4*blockSize, windowColor);
    items[ItemFlag::Light_1] = new RectangleItem(x - 19*blockSize, y + 2* blockSize,
                            2*blockSize, 4*blockSize, lightColor);
    items[ItemFlag::Light_2] = new RectangleItem(x + 19*blockSize, y + 2* blockSize,
                            2*blockSize, 4*blockSize, lightColor);
    items[ItemFlag::Wheel_1] = new Wheel(x - 10*blockSize, y + 6*blockSize,
                    4*blockSize, wheelColor);
    items[ItemFlag::Wheel_2] = new Wheel(x + 10*blockSize, y + 6*blockSize,
    4*blockSize, wheelColor);

}

COLORREF Car::getItemColor(ItemFlag flag){
    return items[flag]->color;
}
void Car::setItemColor(ItemFlag flag, COLORREF newColor){
    items[flag]->color = newColor;
}
