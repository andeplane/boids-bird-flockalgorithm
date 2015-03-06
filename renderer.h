#pragma once

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QElapsedTimer>
#include <QMatrix4x4>
#include <QQuickFramebufferObject>
#include <QThread>
#include <QMutex>
#include "points.h"
#include "billboards.h"

namespace CompPhys {
struct VisualData {
    BillboardsData billboardsData;
};

class Renderer : public QQuickFramebufferObject::Renderer
{
public:
    Renderer();
    ~Renderer();

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size);
    void synchronize(QQuickFramebufferObject *item);
    void render();

private:
    bool m_skipNextFrame;
    Billboards m_billboards;
    VisualData m_data;

    int m_syncCount;
    int m_renderCount;
    int m_dirtyCount;
};
}
