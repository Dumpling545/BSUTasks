#include "../include/physicalsystem.h"

PhysicalSystem::PhysicalSystem()
{
    //ctor
}
PhysicalSystem::PhysicalSystem(int thread_x, int thread_y,
                       int length, int radius,double startAngle, int n){
    this->thread_x = thread_x;
    this->thread_y = thread_y;
    this->length = length;
    this->radius = radius;
    this->startAngle = startAngle;
    this->n = n;
    init();
}
void PhysicalSystem::init(){
    int x = thread_x + cos(1.5*M_PI - startAngle)*(length + radius);
    int y = thread_y - sin(1.5*M_PI - startAngle)*(length + radius);
    balls.clear();
    balls.push_back(BallOnThread(x, y, thread_x, thread_y, radius,
                                RGB(rand() % 256, rand() % 256, rand() % 256)));
    double delta_angle = 2 * asin(radius/((double) (length+radius)));
    double angle = 1.5*M_PI-delta_angle*(n-2)/2.0;
    for(int i = 1; i < n; i++){
        x = thread_x + cos(angle)*(length + radius);
        y = thread_y - sin(angle)*(length + radius);
        balls.push_back(BallOnThread(x, y, thread_x, thread_y, radius,
                                RGB(rand() % 256, rand() % 256, rand() % 256)));
        angle += delta_angle;
    }
}

void PhysicalSystem::draw(HDC &hdc){
    for(int i = 0; i < n; i++){
        balls[i].draw(hdc);
    }
}
bool PhysicalSystem::ballsTouched(int i, int j){
    int delta_x = balls[i].x - balls[j].x;
    int delta_y = balls[i].y - balls[j].y;
    return delta_x*delta_x + delta_y*delta_y <= 4*radius*radius;
}
void PhysicalSystem::setColor(int x, int y){
    for(int i = 0; i < n; i++){
        int dx = x - balls[i].x;
        int dy = y - balls[i].y;
        if(dx*dx + dy*dy <= radius*radius){
            COLORREF old = balls[i].color;
            int red = (256 - GetRValue(old)) % 256;
            int green = (256 - GetGValue(old)) % 256;
            int blue = (256 - GetBValue(old)) % 256;
            balls[i].color = RGB(red, green, blue);
            break;
        }
    }
}
void PhysicalSystem::execute(int delta_t){
    double cur_sin = (thread_x - balls[active].x)/
                            (1.0*(length + radius));
    double cur_cos = (balls[active].y - thread_y)/
                            (1.0*(length + radius));
    double cur_angle = 1.5*M_PI  - asin(cur_sin);
    double delta_angle = 2 * asin(radius/((double) (length+radius)));
    double end_angle = 1.5*M_PI-delta_angle*(n-2)/2.0;
    double v_len;
    switch(phase){
        case 1:{
            if(ballsTouched(active, active + 1)){
                phase = 2;
            } else {
                speed_current += g * delta_t;
                v_len = speed_coefficient*speed_current;
                balls[active].move(cur_cos*v_len, cur_sin*v_len);
            }
            break;
        }
        case 2:
            if(cur_angle >= end_angle){
                active = n-1;
                phase = 3;
            } else {
                for(int i = 0; i < n; i++){
                    double temp_cos = -sin(cur_angle);
                    double temp_sin = cos(cur_angle);
                    if(cur_angle >= 0) temp_sin *=-1;
                    v_len = speed_coefficient*speed_current;
                    balls[i].move(v_len*temp_cos, v_len*temp_sin);
                    cur_angle += delta_angle;
                }
            }
            break;
        case 3:
            if(ballsTouched(active, active - 1)){
                phase = 4;
            } else {
                speed_current -= g * delta_t;
                v_len = speed_coefficient*speed_current;
                balls[active].move(cur_cos*v_len, cur_sin*v_len);
            }
            break;
        case 4:
            if(cur_angle <= end_angle){
                active = 0;
                phase = 5;
            } else {
                for(int i = 0; i < n; i++){
                    double temp_cos = -sin(cur_angle);
                    double temp_sin = -cos(-cur_angle);
                    if(cur_angle >= 0) temp_sin *=-1;
                    v_len = speed_coefficient*speed_current;
                    balls[i].move(v_len*temp_cos, v_len*temp_sin);
                    cur_angle -= delta_angle;
                }
            }
            break;
        case 5:

            break;
    }
}
