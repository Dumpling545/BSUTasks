#include "../include/physicalsystem.h"

PhysicalSystem::PhysicalSystem()
{
}
PhysicalSystem::PhysicalSystem(int thread_x, int thread_y,
                       int length, int radius,double phi_start, int n){
    this->thread_x = thread_x;
    this->thread_y = thread_y;
    this->length = length;
    this->radius = radius;
    this->phi_start = phi_start;
    this->n = n;
    init();
}
void PhysicalSystem::init(){
    int x = thread_x  - (length + radius)*sin(phi_start);
    int y = thread_y + (length + radius)*cos(phi_start);
    balls.clear();
    balls.push_back(BallOnThread(x, y, thread_x, thread_y, radius,
                                RGB(rand() % 256, rand() % 256, rand() % 256)));
    delta_angle =asin(radius/((double) (length+radius)));
    w = sqrt(g / (1.0*(length + radius)));
    double angle = 1.5*M_PI- delta_angle*(n-2);
    phi_collision = delta_angle * n;
    offset_t_falsephysics = acos(phi_collision/phi_start)/w;
    double delta_t_falsephysics = 2.0* (0.5*M_PI / w - offset_t_falsephysics);
    angle_speed_falsephysics = 2 * delta_angle / delta_t_falsephysics;
    for(int i = 1; i < n; i++){
        x = thread_x + cos(angle)*(length + radius);
        y = thread_y - sin(angle)*(length + radius);
        balls.push_back(BallOnThread(x, y, thread_x, thread_y, radius,
                                RGB(rand() % 256, rand() % 256, rand() % 256)));
        angle += 2*delta_angle;
    }
}

void PhysicalSystem::draw(HDC &hdc){
    for(int i = 0; i < n; i++){
        balls[i].draw(hdc);
    }
}
void PhysicalSystem::setAcceleration(int a){
    g = a;
    w = sqrt(g / (1.0*(length + radius)));
    offset_t_falsephysics = acos(phi_collision/phi_start)/w;
    double delta_t_falsephysics = 2.0* (0.5*M_PI / w - offset_t_falsephysics);
	angle_speed_falsephysics = 2 * delta_angle / delta_t_falsephysics;
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
void PhysicalSystem::execute(int ms){
    double seconds = ms / 1000.0;
    double phi = phi_start*cos(w*seconds);
    double period = 2*M_PI / w;
    seconds -= floor(seconds/period)*period;
    switch(phase){
        case 1:
            if(phi <= phi_collision){
                phase = 2;
            } else {
                balls[active].x = thread_x  - (length + radius)*sin(phi);
                balls[active].y = thread_y + (length + radius)*cos(phi);
            }
            break;
        case 2:
            if(phi <= -phi_collision){
                phase = 3;
                active = n-1;
            } else {
                double iter_phi = phi_collision -
                (seconds - offset_t_falsephysics)*angle_speed_falsephysics;
                for(int i = 0; i < n; i++){
                    balls[i].x = thread_x  - (length + radius)*sin(iter_phi);
                    balls[i].y = thread_y + (length + radius)*cos(iter_phi);
                    iter_phi -= 2*delta_angle;
                }
            }
            break;
        case 3:
            if(phi >= -phi_collision){
                phase = 4;
            } else {
                balls[active].x = thread_x  - (length + radius)*sin(phi);
                balls[active].y = thread_y + (length + radius)*cos(phi);
            }
            break;
        case 4:
            if(phi >= phi_collision){
               phase = 5;
               active = 0;
            } else {
                double iter_phi = -(phi_collision -
                    (seconds - offset_t_falsephysics - period/2.0)
                                    *angle_speed_falsephysics);
                for(int i = n-1; i >= 0; i--){
                    balls[i].x = thread_x  - (length + radius)*sin(iter_phi);
                    balls[i].y = thread_y + (length + radius)*cos(iter_phi);
                    iter_phi += 2*delta_angle;
                }
            }
            break;
        case 5:
            if(phi < phi_collision){
                phase = 2;
            } else {
                balls[active].x = thread_x  - (length + radius)*sin(phi);
                balls[active].y = thread_y + (length + radius)*cos(phi);
            }
            break;
    }
}
