
#include <math.h>
//#include <GL/glut.h>
#include <GL\freeglut.h>
#include <iostream>
/*
Neu thay chay loi xin thay hay thay thu vien a, em xai freeglut
*/


#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define M_PI 3.14159265358979323846

static float camZ = 10.f;
static float ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
static float camDirection = 2.f;
static int drawMode = GL_TRIANGLES;
static float camDistance = 40.f;
static bool wire = false;
static bool ortho = false;
static char floorMap[100];
static bool light2 = true;
static bool toggleAxes = false;
static bool animate = false;
static bool mouseControl = false;

static float animationStartAngle = 0.0f;
static bool firstTimeAnimate = false;

static float rotationSpeed = 0.5f;
static float FPS = 60;

static float smoothRate = 0.3f;

void animation(int animate);
void initGraphic() {
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
}

void drawAxes()
{
    if (toggleAxes == true) {
        /*  Length of axes */
        double len = 40.0f;
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(len, 0, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, len, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, len);
        glEnd();
    }
}
namespace floorTile {
    void drawTile(float x, float y) {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(4.f, 4.f, 1.f);
        //Gray layer
        glBegin(GL_QUADS); {
            glColor3f(0.5f, 0.5f, 0.5f);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
            glVertex2f(1.0f, 1.0f);
            glVertex2f(0.0f, 1.0f);
        }
        glEnd();
        //Black corner
        glBegin(GL_QUADS); {
            
            for (float x = 0; x < 1; x += 0.875f) {
                for (float y = 0; y < 1; y += 0.875f) {
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex2f(x + 0.0f, y + 0.0f);
                    glVertex2f(x + 0.125f, y + 0.0f);
                    glVertex2f(x + 0.125f, y + 0.125f);
                    glVertex2f(x + 0.0f, y + 0.125f);
                }
            }
        }
        glEnd();
        //Orange layer
        glBegin(GL_QUADS); {
            glColor3f(1.0f, 0.5f, 0.0f);
            glVertex2f(0.125f, 0.125f);
            glVertex2f(0.875f, 0.125f);
            glVertex2f(0.875f, 0.875f);
            glVertex2f(0.125f, 0.875f);
        }
        glEnd();
        glBegin(GL_TRIANGLES); {
            glColor3f(128.0f/255.0f, 0.0f, 64.0f/255.0f);
            glVertex2f(0.375f, 0.125f);
            glVertex2f(0.5f, 0.25f);
            glVertex2f(0.375f, 0.375f);

            glVertex2f(0.625f, 0.125f);
            glVertex2f(0.625f, 0.375f);
            glVertex2f(0.5f, 0.25f);

            glVertex2f(0.875f, 0.375f);
            glVertex2f(0.75f, 0.5f);
            glVertex2f(0.625f, 0.375f);

            glVertex2f(0.875f, 0.625f);
            glVertex2f(0.625f, 0.625f);
            glVertex2f(0.75f, 0.5f);

            glVertex2f(0.625f, 0.875f);
            glVertex2f(0.5f, 0.75f);
            glVertex2f(0.625f, 0.625f);

            glVertex2f(0.375f, 0.875f);
            glVertex2f(0.375f, 0.625f);
            glVertex2f(0.5f, 0.75f);

            glVertex2f(0.125f, 0.625f);
            glVertex2f(0.25f, 0.5f);
            glVertex2f(0.375f, 0.625f);

            glVertex2f(0.125f, 0.375f);
            glVertex2f(0.375f, 0.375f);
            glVertex2f(0.25f, 0.5f);

            //White triangle
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(0.5f, 0.25f);
            glVertex2f(0.625f, 0.375f);
            glVertex2f(0.375f, 0.375f);
            
            glVertex2f(0.75f, 0.5f);
            glVertex2f(0.625f, 0.625f);
            glVertex2f(0.625f, 0.375f);

            glVertex2f(0.625f, 0.625f);
            glVertex2f(0.5f, 0.75f);
            glVertex2f(0.375f, 0.625f);

            glVertex2f(0.375f, 0.625f);
            glVertex2f(0.25f, 0.5f);
            glVertex2f(0.375f, 0.375f);
        }
        glEnd();


        glPopMatrix();
    }
    void drawFloor() {
        glDisable(GL_DEPTH_TEST);
        for (int i = 0; i < 100; i++) {
            float x = (i % 10) * 4.f - 20.f;
            float y = (i / 10) * 4.f - 20.f;
            //std::cout << floorMap[i] <<"  " << x << "  " << y << std::endl;
            drawTile(x, y);
        }
    }
}
namespace base {
    void drawRay() {
        glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 8.0f);
        glScalef(0.5f, 2.5f, 7.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glTranslatef(-1.0f, 0.f, 0.0f);
        glScalef(0.5f, 2.5f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();

        glTranslatef(1.5f, 0.2f, 0.0f);
        glScalef(2.5f, 0.5f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();
        // Ray 2
        glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glRotatef(180, 0.0f, 0.0f, 1.0f);
        glTranslatef(-2.0f, 0.0f, 8.0f);
        glScalef(0.5f, 2.5f, 7.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glTranslatef(-1.0f, 0.f, 0.0f);
        glScalef(0.5f, 2.5f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();

        glTranslatef(1.5f, 0.2f, 0.0f);
        glScalef(2.5f, 0.5f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();
    }

    void drawChanDe() {
        glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.6f);
        glScalef(10.0f, 30.0f, 0.6f);
        glBegin(GL_QUADS); {
            glColor3f(1.0f, 0.5f, 0.5f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();
    }

    void drawHalfCircle() {
        float radius = 2;
        glPushMatrix();
        glTranslatef(4.8f, 0.0f, 0.0f);
        glScalef(0.8f, 1.0f, 1.0f);
        // Top
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            for (float i = 0.0; i <= M_PI; i += 0.01) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
                glVertex3f(4 , (cos(i) * radius), 1.0f);
            }
        }
        glEnd();

        // Bottom
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // Top
            for (float i = 0.0; i <= M_PI; i += 0.01) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), -1.0f);
                glVertex3f(4, (cos(i) * radius), -1.0f);
            }
        }
        glEnd();
        //Inner
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // Top
            for (float i = 0.0; i <= M_PI; i += 0.01) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), -1.0f);
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
            }
        }
        glEnd();

        // Front and side
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, -1.0f);
            glVertex3f(4.0f, 2.0f, -1.0f);
            glVertex3f(4.0f, 2.0f, 1.0f);

            // side
            glVertex3f(4.0f, -2.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, -1.0f);
            glVertex3f(0.0f, -2.0f, -1.0f);
            glVertex3f(0.0f, -2.0f, 1.0f);

            glVertex3f(4.0f, 2.0f, 1.0f);
            glVertex3f(4.0f, 2.0f, -1.0f);
            glVertex3f(0.0f, 2.0f, -1.0f);
            glVertex3f(0.0f, 2.0f, 1.0f);

        }
        glEnd();
        glPopMatrix();
    }

    void drawGiaDo() {
        float radius = 2;
        glPushMatrix();
        glScalef(0.8f, 0.5f, 0.3f);
        glTranslatef(0.0f, -3.0f, 26.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);

        //Upper half circle
        glPushMatrix();
        glTranslatef(6.0f, 0.0f, 0.0f);
        glScalef(0.5f, 1.0f, 1.0f);
        // Top
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            for (float i = 0.0; i <= M_PI + smoothRate; i += smoothRate) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
                glVertex3f(4, (cos(i) * radius), 1.0f);
            }
        }
        glEnd();

        // Bottom
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // Top
            for (float i = 0.0; i <= M_PI + smoothRate; i += smoothRate) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), -1.0f);
                glVertex3f(4, (cos(i) * radius), -1.0f);
            }
        }
        glEnd();
        //Inner
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // Top
            for (float i = 0.0; i <= M_PI + smoothRate; i += smoothRate) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), -1.0f);
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
            }
        }
        glEnd();

        // Front and side
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, -1.0f);
            glVertex3f(4.0f, 2.0f, -1.0f);
            glVertex3f(4.0f, 2.0f, 1.0f);

            // side
            glVertex3f(4.0f, -2.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, -1.0f);
            glVertex3f(0.0f, -2.0f, -1.0f);
            glVertex3f(0.0f, -2.0f, 1.0f);

            glVertex3f(4.0f, 2.0f, 1.0f);
            glVertex3f(4.0f, 2.0f, -1.0f);
            glVertex3f(0.0f, 2.0f, -1.0f);
            glVertex3f(0.0f, 2.0f, 1.0f);

        }
        glEnd();
        glPopMatrix();

        // Lower half circle
        glPushMatrix();
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        glTranslatef(6.0f, 0.0f, 0.0f);
        glScalef(0.5f, 1.0f, 1.0f);
        // Top
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            for (float i = 0.0; i <= M_PI + smoothRate; i += smoothRate) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
                glVertex3f(4, (cos(i) * radius), 1.0f);
            }
        }
        glEnd();

        // Bottom
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // Top
            for (float i = 0.0; i <= M_PI + smoothRate; i += smoothRate) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), -1.0f);
                glVertex3f(4, (cos(i) * radius), -1.0f);
            }
        }
        glEnd();
        //Inner
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // Top
            for (float i = 0.0; i <= M_PI + smoothRate; i += smoothRate) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), -1.0f);
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
            }
        }
        glEnd();

        // Front and side
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, -1.0f);
            glVertex3f(4.0f, 2.0f, -1.0f);
            glVertex3f(4.0f, 2.0f, 1.0f);

            // side
            glVertex3f(4.0f, -2.0f, 1.0f);
            glVertex3f(4.0f, -2.0f, -1.0f);
            glVertex3f(0.0f, -2.0f, -1.0f);
            glVertex3f(0.0f, -2.0f, 1.0f);

            glVertex3f(4.0f, 2.0f, 1.0f);
            glVertex3f(4.0f, 2.0f, -1.0f);
            glVertex3f(0.0f, 2.0f, -1.0f);
            glVertex3f(0.0f, 2.0f, 1.0f);

        }
        glEnd();
        glPopMatrix();


        // Two straight bar
        glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glScalef(8.0f, 4.0f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();

        glTranslatef(0.0f, -1.2f, 0.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();

        // Vertical bar
        glPushMatrix(); 
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glScalef(1.0f, 10.0f, 9.8f);
        glTranslatef(0.0f,-0.1f, -1.25f);

        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();
        glPopMatrix();
    }
}
namespace moving {
    float angle = 0.0f;
    float butvedis = 0.8f;
    float butvedis_max = butvedis;
    float butvedis_min = 0.1f;
    float butvex = 0.0f;
    float butvez = 0.0f;
    float lienketAngle = 0.0f;
    float thanhTruotDis = 8.0f;
    // Test draw 
    void drawHinhVuong() {

        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.2f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
    }
    void drawButVe() {
        if (butvedis > butvedis_max) {
            butvedis = butvedis_max;
        }
        else if (butvedis < butvedis_min) {
            butvedis = butvedis_min;
        }
        butvex = sin(-angle * M_PI / 180) * butvedis * 4.0f;
        butvez = cos(-angle * M_PI / 180) * butvedis * 5.0f ;
        glPushMatrix();
        //glTranslatef(butvex , 0.0f, -butvez -2.0f);
        glTranslatef(0.0f, 1.9f, 10.0f);
        glRotatef(270, 1.0f, 0.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 3.0f);
        glScalef(1.0f, 1.0f, 0.8f);
        glBegin(GL_TRIANGLES);
        for (float k = 0; k <= 2 * M_PI; k += 0.01f) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), sin(k), 0.0f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k + 0.01f), sin(k + 0.01f), 0.0f);
        }
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 2.0f, 0.0f);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI; k += 0.01f) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), +1.0f, sin(k));
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), -1.0f, sin(k));
        }
        glEnd();
        /* top and bottom circles */
        /* reuse the currentTexture on top and bottom) */
        for (float i = 1; i >= -1; i -= 2) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0f, i, 0.0f);
            for (float k = 0; k <= 2 * M_PI; k += 0.01f) {
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(i * cos(k), i, sin(k));
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
    }

    void drawThanhButVe() {
        if (butvedis > butvedis_max) {
            butvedis = butvedis_max;
        }
        else if (butvedis < butvedis_min) {
            butvedis = butvedis_min;
        }
        butvex = sin(-angle * M_PI / 180) * butvedis * 3.0f;
        butvez = cos(-angle * M_PI / 180) * butvedis * 3.0f;
        lienketAngle = atan2(butvex, butvez - 0.3f) / M_PI * 180;


        glPushMatrix();
        glTranslatef(0.0f, 2.0f, -butvez + thanhTruotDis);
        glRotatef(lienketAngle, 0.f, 1.0f, 0.f);
        //glRotatef(-180, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 4.0f);
        glScalef(0.5f, 2.0f, 4.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.3f, 0.9f, 0.4f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        //Reverse Transform 
        glScalef(1.0f/0.5f, 1.0f/2.0f, 1.0f / 5.0f);

        // Final touch
        glTranslatef(0.0f, -0.2f, 4.0f);
        glRotatef(270, 1.0f, 0.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);


        //Pointy part
        glTranslatef(0.0f, 0.0f, 3.0f);
        glScalef(0.9f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        for (float k = 0; k <= 2 * M_PI ; k += smoothRate) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), sin(k), 0.0f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k + smoothRate), sin(k + smoothRate), 0.0f);
        }
        glEnd();

        //Reverse transform
        glTranslatef(0.0f, 0.0f, -3.0f);
        glScalef(1.0f, 1.0f, 1.0f/0.8f);

        // Cylinder
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 1.4f, 0.0f);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), +1.0f, sin(k));
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), -1.0f, sin(k));
        }
        glEnd();
        /* top and bottom circles */
        /* reuse the currentTexture on top and bottom) */
        for (float i = 1; i >= -1; i -= 2) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0f, i, 0.0f);
            for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(i * cos(k), i, sin(k));
            }
            glEnd();
        }
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -2.0f, -10.0f);
        glPopMatrix();

        //Ve phan tru dep
        glPushMatrix();
        //glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(1.0f, 0.2f, 1.0f);
        glTranslatef(0.0f, 11.05f, -butvez + thanhTruotDis);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
            glColor3f(0.3f, 0.9f, 0.4f);
            glVertex3f(cos(k), +1.0f, sin(k));
            glColor3f(0.3f, 0.9f, 0.4f);
            glVertex3f(cos(k), -1.0f, sin(k));
        }
        glEnd();
        /* top and bottom circles */
        /* reuse the currentTexture on top and bottom) */
        for (float i = 1; i >= -1; i -= 2) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.3f, 0.9f, 0.4f);
            glVertex3f(0.0f, i, 0.0f);
            for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
                glColor3f(0.3f, 0.9f, 0.4f);
                glVertex3f(i * cos(k), i, sin(k));
            }
            glEnd();
        }
        glPopMatrix();
    }

    void drawChot1() {
        glPushMatrix();
        glTranslatef(0.0f, 1.1f, -butvez + thanhTruotDis);
        glScalef(0.5f, 2.0f, 0.5f);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), +1.0f, sin(k));
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), -1.0f, sin(k));
        }
        glEnd();
        /* top and bottom circles */
        /* reuse the currentTexture on top and bottom) */
        for (float i = 1; i >= -1; i -= 2) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, i, 0.0f);
            for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(i * cos(k), i, sin(k));
            }
            glEnd();
        }
        glPopMatrix();
    }

    void drawTamTruot() {
        
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -butvez + thanhTruotDis);
        glScalef(1.5f, 10.0f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 0.0f, 1.0f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        
        glTranslatef(-1.2f, 0.06f, 0.0f);
        glScalef(0.2f, 0.4f, 1.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 0.0f, 1.0f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        
        glTranslatef(12.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 0.0f, 1.0f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();
    }

    void drawThanhLienKet() {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -butvez +  thanhTruotDis);
        glRotatef(lienketAngle, 0.f, 1.0f, 0.f);
        glTranslatef(0.0f, -0.8f, 2.0f);
        glScalef(0.8f, 3.0f, 4.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.3f, 0.3f, 0.3f);
            // botom
            glNormal3f(0.f, 0.f, -1.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            // top
            glNormal3f(0.f, 0.0f, 1.0f);
            glVertex3f(-1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // front
            glNormal3f(0.f, 1.0f, 0.f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.2f, 1.f);
            // back
            glNormal3f(0.f, -1.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // left
            glNormal3f(-1.f, 0.f, 0.f);
            glVertex3f(-1.f, 0.f, -1.0f);
            glVertex3f(-1.f, 0.2f, -1.0f);
            glVertex3f(-1.f, 0.2f, 1.f);
            glVertex3f(-1.f, 0.f, 1.f);
            // right
            glNormal3f(1.f, 0.f, 0.f);
            glVertex3f(1.f, 0.f, -1.0f);
            glVertex3f(1.f, 0.2f, -1.0f);
            glVertex3f(1.f, 0.2f, 1.f);
            glVertex3f(1.f, 0.f, 1.f);
        }
        glEnd();
        glPopMatrix();
    }

    void drawChot2() {

        glPushMatrix();
        glTranslatef(butvex + 0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -1.1f, 7.8f);
        glScalef(0.6f, 1.0f, 0.6f);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), +1.0f, sin(k));
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(cos(k), -1.0f, sin(k));
        }
        glEnd();
        /* top and bottom circles */
        /* reuse the currentTexture on top and bottom) */
        for (float i = 1; i >= -1; i -= 2) {
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, i, 0.0f);
            for (float k = 0; k <= 2 * M_PI + smoothRate; k += smoothRate) {
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(i * cos(k), i, sin(k));
            }
            glEnd();
        }
        glPopMatrix();
    }

    void drawPoint2() {
        if (animate == true) {
            if (firstTimeAnimate == true) {
                animationStartAngle = angle;
                firstTimeAnimate = false;
            }
            int i = 0;
            for (i = 0; (animationStartAngle + (rotationSpeed * i)) <= angle; i += 4) {
                float butvexAnimate = sin(-(animationStartAngle + (rotationSpeed * i)) * M_PI / 180) * butvedis * 3.0f;
                float butvezAnimate = cos((animationStartAngle + (rotationSpeed * i)) * M_PI / 180) * butvedis * 3.0f;
                float lienketAngleAnimate = atan2(butvexAnimate, butvezAnimate - 0.4f) / M_PI * 180;
                //std::cout << "Ve " << i << " lan" << std::endl;
                glPushMatrix();
                //ý tưởng, giữ một bản ghi ban đầu, sau đó iterate lần lượt đến hiện tại.
                glTranslatef(0.0f, 0.0f, -butvezAnimate + thanhTruotDis);
                glRotatef(lienketAngleAnimate, 0.f, 1.0f, 0.f);
                glTranslatef(0.0f, 2.0f, 7.0f);
                glPointSize(2.0);
                glBegin(GL_POINTS); {
                    glColor3f(1.0f, 0.9f, 0.4f);
                    glVertex3f(0.2f, 2.0f, 0.2f);
                }
                glEnd();
                glPopMatrix();

            }
            if (i <= int(360.0f / rotationSpeed) && i >= int(359.0f / rotationSpeed)) {
                animate = false;
            }
        }
    }
}

void drawSky() {
    glBegin(GL_QUADS); {
        glColor3f(1.f, 1.f, 0.8f);
        glVertex2f(-1.f, -1.f);
        glVertex2f(1.f, -1.f);
        glColor3f(0.3f, 0.6f, 0.8f);
        glVertex2f(1.f, 1.f);
        glVertex2f(-1.f, 1.f);
    }
    glEnd();
}

void enableLight() {
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat	lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_position1[] = { -10.0f, 4.0f, 2.0f, 0.0f };
    GLfloat light_position2[] = { 6.0f, -4.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
}

void displayFunc(void) {
    // sky
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    drawSky();
    // camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ortho) {
        glOrtho(-10.f * ratio, 10.f * ratio, -10.f, 20.f, -10.f, 10.f);
    }
    else {
        gluPerspective(45.f, ratio, 0.1f, 1000.0f);
        gluLookAt(camDistance * (float)cos(camDirection), camDistance * (float)sin(camDirection), camZ, 0.f, 0.f, 3.f, 0.f, 0.f, 1.f);
    }
    // Setup new frame
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Light
    enableLight();

    //Draw
    if (toggleAxes == true) {
        drawAxes();
    }

    // Floor first
    floorTile::drawFloor();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    // Enable light
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHT0);
    if (light2) glEnable(GL_LIGHT2); else glDisable(GL_LIGHT2);
    
    if (wire == true ) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    //Draw
    base::drawRay();
    base::drawChanDe();
    base::drawGiaDo();

    moving::drawThanhButVe();
    moving::drawChot1();
    moving::drawTamTruot();
    moving::drawThanhLienKet();
    moving::drawChot2();
    moving::drawPoint2();

    //buffer
    glutSwapBuffers();
    glutPostRedisplay();
}

void motionFunc(int x, int y) {
    if (mouseControl == true) {
        static int px = 0;
        static int py = 0;

        if (px || py) {
            camDirection += (float)(x - px) / 50.f;
            camZ += (float)(y - py) / 10.f;
            if (camZ < 1.f) {
                camZ = 1.f;
            }
        }

        px = x;
        py = y;
    }

}
void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case '+': camDistance--; break;
        case '-': camDistance++; break;
        case 'v': case 'V': ortho = !ortho; break;
        case '1': moving::angle += 2.0f; break;
        case '2': moving::angle -= 2.0f; break;
        case 'x': case 'X': toggleAxes = !toggleAxes; break;
        case 'a': case 'A': animate = !animate; firstTimeAnimate = true;         glutTimerFunc(0, animation, 0); break;
        case 'w': case 'W': wire = !wire; break;
        case 'm': case 'M': mouseControl = !mouseControl; break;
    }
}

void mousewheelFunc(int button, int dir, int x, int y) {
    if (dir > 0) {
        //zoom in 
        camDistance--;
    }
    else {
        camDistance++;
    }
    return;
}

void reshapeFunc(int w, int h) {
    glViewport(0, 0, w, h);
    ratio = w / h;
    //std::cout << "W: " << w << " H: " << h << std::endl;
}

void animation(int time_counter) {
    if (animate == true && time_counter == 0) {
        moving::angle += rotationSpeed;
        glutPostRedisplay();
        glutTimerFunc(1000 / FPS, animation, 0);
    }
    
}
void specialFunc(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        camDirection -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        camDirection += 0.1f;
        break;
    case GLUT_KEY_UP:
        camZ += 0.2f;
        break;
    case GLUT_KEY_DOWN:
        camZ -= 0.2f;
        break;
    }
    if (camZ < 1.f) camZ = 1.f;
}

int main(int argc, char** argv) {
    //Init GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Set window position
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);      // window size
    //glutInitWindowPosition(500, 500);  // distance from the top-left screen
    glutCreateWindow("NguyenDuyHung - 2013389");    // message displayed on top bar window

    glutDisplayFunc(displayFunc);
    // Maintain viewport
    glutReshapeFunc(reshapeFunc);
    //Recognize arrow
    glutSpecialFunc(specialFunc);
    //Recognize keyboard
    glutKeyboardFunc(keyboardFunc);
    //Set cam direction as mouse clicking position
    glutMotionFunc(motionFunc);

    //Set cam distance by mouse scroll
    glutMouseWheelFunc(mousewheelFunc);

    initGraphic();

    std::cout << "1     : Di chuyen tam truot len tren" << std::endl;
    std::cout << "2     : Di chuyen tam truot xuong duoi" << std::endl;
    std::cout << "W, w  : Chuyen doi qua lai giua che do khung day va to mau" << std::endl;
    std::cout << "V, v  : Chuyen doi qua lai giua che do 2D va 3D" << std::endl;
    std::cout << "A, a  : Bat tat che do hoat hinh" << std::endl;
    std::cout << "+     : Tang khoang cach camera" << std::endl;
    std::cout << "-     : Giam khoang cach camera" << std::endl;
    std::cout << "Up arrow     : Tang chieu cao camera" << std::endl;
    std::cout << "Down arrow   : Giam chieu cao camera" << std::endl;
    std::cout << "<-           : Quay camera theo chieu kim dong ho" << std::endl;
    std::cout << "->           : Quay camera nguoc chieu kim dong ho" << std::endl;
    std::cout << "Chuc nang them:" << std::endl;
    std::cout << "X, x  : Bat/tat truc xyz" << std::endl;
    std::cout << "M, m  : Bat/tat che do quay camera bang chuot" << std::endl;
    std::cout << "Lan chuot de dieu chinh do xa camera" << std::endl;

    glutMainLoop();

    
}