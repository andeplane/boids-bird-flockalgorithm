#include "simulator.h"
#include "random.h"
#include <cmath>
#include <iostream>
#include <functional>
#include <QDebug>
using std::cout; using std::endl; using std::function;

Simulator::Simulator(QObject *parent) :
    QObject(parent)
{
    dt = 0.01;
    createParticles(10);
}


Simulator::~Simulator()
{

}

void Simulator::createParticles(unsigned int numberOfParticles) {
    for(unsigned int i=0; i<numberOfParticles; i++) {
        float x = 2*(rand() / float(RAND_MAX) - 1.0);
        float y = 2*(rand() / float(RAND_MAX) - 1.0);

        float vx = 2*(rand() / float(RAND_MAX) - 1.0) * 0.1;
        float vy = 2*(rand() / float(RAND_MAX) - 1.0) * 0.1;

        pos.push_back(QVector2D(x,y));
        vel.push_back(QVector2D(vx,vy));
        acc.push_back(QVector2D(0,0));
    }
}

void Simulator::step()
{
    for(unsigned int i=0; i<pos.size(); i++) {
        pos[i][0] += vel[i][0]*dt;
        pos[i][1] += vel[i][1]*dt;
        if(pos[i][0] < -1) pos[i][0] += 2;
        else if(pos[i][0] > 1) pos[i][0] -= 2;
        if(pos[i][1] < -1) pos[i][1] += 2;
        else if(pos[i][1] > 1) pos[i][1] -= 2;
    }

    emit stepCompleted();
}
