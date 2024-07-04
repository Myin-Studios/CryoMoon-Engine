/////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                   ///
///                                      THIS CODE IS PART OF:                                        ///
///                                       CryoMoon Engine (C)                                         ///
///                                                                                                   ///
///                                     WHICH IS LICENSED UNDER                                       ///
///                                          MIT License                                              ///
///                                      All Right Reserved.                                          ///
///                                                                                                   ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                   ///
///   Copyright (c) 2024 Myin Studios                                                                 ///
///                                                                                                   ///
///   Permission is hereby granted, free of charge,  to any person obtaining a copy of this software  ///
///   and associated documentation files (the "Software"), to deal in the Software without            ///
///   restriction, including without limitation the rights to use, copy, modify, merge, publish,      ///
///   distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the   ///
///   Software is furnished to do so, subject to the following conditions:                            ///
///                                                                                                   ///
///   The above copyright notice and this permission notice shall be included in all copies or        ///
///   substantial portions of the Software.                                                           ///
///                                                                                                   ///
///   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING   ///
///   BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND      ///
///   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    ///
///   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ///
///   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.         ///
///                                                                                                   ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "camera.h"
#include "light.h"
#include "GUI/MainWindow/colorpicker.h"
#include <QMimeData>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector3D>
#include <QBuffer>
#include <QFileInfo>
#include <vector>
#include <QApplication>
#include <QMainWindow>

struct Vertex
{
    QVector3D Position;
    QVector3D Normal;
};

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT

public:
    explicit Renderer(QWidget *parent = nullptr);
    ~Renderer();

    void setColors(QColor col)
    {
        this->_r = col.redF();
        this->_g = col.greenF();
        this->_b = col.blueF();
    }

    float r() const { return this->_r; }
    float g() const { return this->_g; }
    float b() const { return this->_b; }

    void setPosition(float x, float y, float z)
    {
        this->_x = x;
        this->_y = y;
        this->_z = z;
        updateVertices();
    }
    void setScale(float scale)
    {
        this->m_scale = scale;
        update();
    }

    void getMainWindowRect(const QMainWindow& mainWindow)
    {
        mainWindowRect = mainWindow.geometry();
    }

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    std::vector<Vertex> vertices{};
    std::vector<GLint> indices {1, 1, 1};

    float _x = 0.0;
    float _y = 0.0;
    float _z = 0.0;

    float _r = 0.0;
    float _g = 0.0;
    float _b = 0.0;

    float m_scale = 1.0f;
    std::vector<GLfloat> cubeVertices = {
            // Front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Bottom-left
            1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Bottom-right
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Top-right
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Bottom-left

            // Back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, // Bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, // Top-left
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, // Top-right
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, // Top-right
            1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, // Bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, // Bottom-left

            // Left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, // Top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, // Top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, // Bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, // Bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, // Bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, // Top-right

            // Right face
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, // Top-left
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, // Bottom-right
            1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, // Top-right
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, // Bottom-right
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, // Top-left
            1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, // Bottom-left

            // Top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, // Top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, // Bottom-left
            1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, // Bottom-right
            1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, // Bottom-right
            1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, // Top-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, // Top-left

            // Bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, // Top-right
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, // Bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, // Top-left
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, // Bottom-left
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, // Top-right
            1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f  // Bottom-right
    };

    // Vertici del piano con posizioni e normali
    const std::vector<GLfloat> planeVertices = {
            // Posizioni          // Normali
            -3.0f,  1.0f, -3.0f,  0.0f,  1.0f,  0.0f, // Top-left
            -3.0f,  1.0f,  3.0f,  0.0f,  1.0f,  0.0f, // Bottom-left
            3.0f,  3.0f,  3.0f,  0.0f,  1.0f,  0.0f, // Bottom-right
            3.0f,  3.0f,  3.0f,  0.0f,  1.0f,  0.0f, // Bottom-right
            3.0f,  3.0f, -3.0f,  0.0f,  1.0f,  0.0f, // Top-right
            -3.0f,  3.0f, -3.0f,  0.0f,  1.0f,  0.0f, // Top-left
    };

    Camera m_camera;
    QOpenGLShaderProgram *m_program;
    QOpenGLShaderProgram *shadowShader;
    QOpenGLBuffer m_vbo, ebo;
    QOpenGLVertexArrayObject m_vao;
    GLuint depthMapFBO;
    GLuint depthMap;
    QMatrix4x4 lightSpaceMatrix;
    QVector3D sunPosition;
    float timeOfDay = 0.0f;
    QSet<int> m_KeyPressed;
    QPoint lastPos{0, 0};
    QRect mainWindowRect;
    QVector2D smoothDelta;
    std::vector<QVector2D> smoothDeltas;

    //float deltaX = 0.0f, deltaY = 0.0f;
    float nonZeroDeltaX = 0.0f;
    float nonZeroDeltaY = 0.0f;

    QVector2D accumDeltas{0.0f, 0.0f};

    bool m_mouseRightPressed = false;

    QVector2D smoothMouseMovement(float deltaX, float deltaY);
    float getMouseSpeed();
    void updateCameraPos();
    void initShaders();
    void initShadowMap();
    void renderScene(QOpenGLShaderProgram &shader);
    void setupVertexAttribs();
    void updateVertices();
    void updateTimeOfDay();
    void shadowPass();
    void loadGLTF(const QString &fileName);
    void loadOBJ(const QString &filePath);
};

#endif // RENDERER_H
