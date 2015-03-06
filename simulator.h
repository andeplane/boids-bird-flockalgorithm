#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <QObject>
#include <QVector2D>
#include <vector>

class Simulator : public QObject
{
    Q_OBJECT
public:
    float        dt;

    Simulator(QObject* parent = 0);
    ~Simulator();
    std::vector<QVector2D> pos;
    std::vector<QVector2D> vel;
    std::vector<QVector2D> acc;
    void createParticles(unsigned int numberOfParticles);
public slots:
    void step();

signals:
    void stepCompleted();
};

#endif // SIMULATOR_H
