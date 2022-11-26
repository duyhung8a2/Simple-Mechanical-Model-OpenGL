
#include <math.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

/*
//Class Point3 to define a point in 3D world
class Point3
{
public:
    float x, y, z;
    void set(float dx, float dy, floatdz)
    {
        x = dx; y = dy; z = dz;
    }
    void set(Point3& p)
    {
        x = p.x; y = p.y; z = p.z;
    }
    Point3()
    {
        x = 0; y = 0; z = 0;
    }
    Point3(float dx, float dy, float dz)
    {
        x = dx; y = dy; z = dz;
    }
};

class Color3
{
public:
    float r, g, b;
    void set(float red, float green, float blue)
    {
        r = red; g = green; b = blue;
    }
    void set(Color3& c)
    {
        r = c.r; g = c.g; b = c.b;
    }
    Color3() { r = g = b = 0; }
    Color3(float red, float green, float blue)
    {
        r = red; g = green; b = blue;
    }
};

class Point2
{
public:
    Point2() { x = y = 0.0f; } // constructor 1
    Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
    void set(float xx, float yy) { x = xx; y = yy; }
    float getX() { return x; }
    float getY() { return y; }
    void draw() {
        glBegin(GL_POINTS);
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }
private:
    float 	x, y;
};

class RealRect
{
public:
    RealRect() { l = 0; r = 100; b = 0; t = 100; }
    RealRect(float left, float, right, float, bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    void set(float left, float, right, float, bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    float getWidth()
    {
        return (r - l);
    }
    float getHeight()
    {
        return (t - b);
    }
    void RealRect::draw()
    {
        glRectf(l, b, r, t);
        glFlush();
    };
private:
    float l, r, b, t;
};

class Vector3
{
public:
    float x, y, z;
    void set(float dx, float, dy, float dz)
    {
        x = dx; y = dy; z = dz;
    }
    void set(Vector3& v)
    {
        x = v.x; y = v.y; z = v.z;
    }
    void flip()
    {
        x = -x; y = -y; z = -z;
    }
    Vector3()
    {
        x = y = z = 0;
    }
    Vector3(float dx, float, dy, float dz)
    {
        x = dx; y = dy; z = dz;
    }
    Vector3(Vector3& v)
    {
        x = v.x; y = v.y; z = v.z;
    }
    void Vector3::normalize()
    {
        float temp = sqrt(x * x + y * y + z * z);
        x = x / temp;
        y = y / temp;
        z = z / temp;
    }
    float Vector3::dot(Vector3 b)
    {
        return x * b.x + y * b.y + z * b.z;
    }
    Vector3 Vector3::cross(Vector3 b)
    {
        Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
        return c;
    }
};


//Clear the current window and draw a triangle
void display(void) {
    //Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);

    //Drawing is done by specifying a sequence of vertices. The way these vertices are connected
    //depends on the argument to glBegin. GL_POLYGON construct a filled polygon.
    RealRect ex1;
    ex1.draw();
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
    glEnd();
    
    //Flush drawing command buffer to make drawing happen as soon as possible
    glFlush();
}

int main(int argc, char** argv) {
    //Init GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //Set window position
    glutInitWindowSize(600, 600);      // window size
    //glutInitWindowPosition(500, 500);  // distance from the top-left screen
    glutCreateWindow("Hello world");    // message displayed on top bar window

    //Tell GLUT whenever main window needs to be repainted that it should call the function display() 
    glutDisplayFunc(display);

    //Tell GLUT to start raeding and processing event. This function never return
    //The program only exit when user close the main window or kill the process
    glutMainLoop();
        
}
*/
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define M_PI 3.14159265358979323846

static float camZ = 10.f;
static float ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
static float camDirection = 2.f;
static int drawMode = GL_TRIANGLES;
static float camDistance = 30.f;
static bool wire = false;
static bool ortho = false;
static char floorMap[100];
static bool light2 = true;
static bool toggleAxes = true;
static bool animate = false;

void animation(int animate);

void drawGiaDo() {
    glPushMatrix();
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
    glScalef(0.2f, 0.2f, 15.f);
    glBegin(GL_QUADS); {
        glColor3f(0.1f, 0.4f, 0.9f);
        // botom
        glNormal3f(0.f, 0.f, -1.f);
        glVertex3f(-3.f, -1.f, 0.0f);
        glVertex3f(3.f, -1.f, 0.0f);
        glVertex3f(3.f, 1.f, 0.0f);
        glVertex3f(-3.f, 1.f, 0.0f);
        // top
        glNormal3f(0.f, 0.0f, 1.0f);
        glVertex3f(-3.f, -1.f, 0.5f);
        glVertex3f(3.f, -1.f, 0.5f);
        glVertex3f(3.f, 1.f, 0.5f);
        glVertex3f(-3.f, 1.f, 0.5f);
        // front
        glNormal3f(0.f, 1.f, 0.f);
        glVertex3f(-3.f, 1.f, 0.0f);
        glVertex3f(3.f, 1.f, 0.0f);
        glVertex3f(3.f, 1.f, 0.5f);
        glVertex3f(-3.f, 1.f, 0.5f);
        // back
        glNormal3f(0.f, -1.f, 0.f);
        glVertex3f(-3.f, -1.f, 0.0f);
        glVertex3f(3.f, -1.f, 0.0f);
        glVertex3f(3.f, -1.f, 0.5f);
        glVertex3f(-3.f, -1.f, 0.5f);
        // left
        glNormal3f(-1.f, 0.f, 0.f);
        glVertex3f(-3.f, -1.f, 0.0f);
        glVertex3f(-3.f, 1.f, 0.0f);
        glVertex3f(-3.f, 1.f, 0.5f);
        glVertex3f(-3.f, -1.f, 0.5f);
        // right
        glNormal3f(1.f, 0.f, 0.f);
        glVertex3f(3.f, -1.f, 0.0f);
        glVertex3f(3.f, 1.f, 0.0f);
        glVertex3f(3.f, 1.f, 0.5f);
        glVertex3f(3.f, -1.f, 0.5f);
    }
    glEnd();

}
namespace part2 {
    float angle = 0.0f;
    float chot2x = 0.f;
    float chot2z = 0.f;
    float chot2dis = 0.9f;
    float lienKetAngle = 0.f;

void drawThanhLienKet() {
    lienKetAngle = atan2(chot2x, chot2z - 1.f) / M_PI * 180;
    glPushMatrix();
    glTranslatef(0.f, 0.61f, 1.f);
    glRotatef(lienKetAngle, 0.f, 1.f, 0.f);
    glScalef(0.1f, 1.0f, 0.2f);
    glScalef(1.f, 1.f, 15.f);
    glTranslatef(-3.f, 0.f, 1.f);
    //thanh lien ket ben trai
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

    //thanh lien ket ben phai
    glTranslatef(6.f, 0.f, 0.f);
    glBegin(GL_QUADS); {
        glColor3f(0.2f, 0.9f, 0.4f);
        // bottom
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
    
    //glTranslatef(-3.f, 0.f, -0.9f);
    glTranslatef(-3.0f, 0.0f, -0.9f);
    glScalef(2.f, 1.f, 0.1f);
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
    //glTranslatef(0.f, 0.f, 34.f);
    //glScalef(1.f, 1.f, 2.f);
    //glBegin(GL_QUADS); {
    //    glColor3f(0.2f, 0.9f, 0.4f);
    //    // botom
    //    glNormal3f(0.f, 0.f, -1.f);
    //    glVertex3f(-1.f, 0.f, -1.0f);
    //    glVertex3f(1.f, 0.f, -1.0f);
    //    glVertex3f(1.f, 0.2f, -1.0f);
    //    glVertex3f(-1.f, 0.2f, -1.0f);
    //    // top
    //    glNormal3f(0.f, 0.0f, 1.0f);
    //    glVertex3f(-1.f, 0.f, 1.f);
    //    glVertex3f(1.f, 0.f, 1.f);
    //    glVertex3f(1.f, 0.2f, 1.f);
    //    glVertex3f(-1.f, 0.2f, 1.f);
    //    // front
    //    glNormal3f(0.f, 1.0f, 0.f);
    //    glVertex3f(-1.f, 0.2f, -1.0f);
    //    glVertex3f(1.f, 0.2f, -1.0f);
    //    glVertex3f(1.f, 0.2f, 1.f);
    //    glVertex3f(-1.f, 0.2f, 1.f);
    //    // back
    //    glNormal3f(0.f, -1.f, 0.f);
    //    glVertex3f(-1.f, 0.f, -1.0f);
    //    glVertex3f(1.f, 0.f, -1.0f);
    //    glVertex3f(1.f, 0.f, 1.f);
    //    glVertex3f(-1.f, 0.f, 1.f);
    //    // left
    //    glNormal3f(-1.f, 0.f, 0.f);
    //    glVertex3f(-1.f, 0.f, -1.0f);
    //    glVertex3f(-1.f, 0.2f, -1.0f);
    //    glVertex3f(-1.f, 0.2f, 1.f);
    //    glVertex3f(-1.f, 0.f, 1.f);
    //    // right
    //    glNormal3f(1.f, 0.f, 0.f);
    //    glVertex3f(1.f, 0.f, -1.0f);
    //    glVertex3f(1.f, 0.2f, -1.0f);
    //    glVertex3f(1.f, 0.2f, 1.f);
    //    glVertex3f(1.f, 0.f, 1.f);
    //}
    //glEnd();
    glPopMatrix();
}

void drawChot3() {
    glPushMatrix();
    glTranslatef(0.f, 0.61f, 1.f);
    glRotatef(lienKetAngle, 0.f, 1.f, 0.f);
    glScalef(0.4f, 1.0f, 0.4f);
    glBegin(GL_TRIANGLES); {
        glNormal3f(0.f, -1.f, 0.f);
        glColor3f(0.2f, 0.9f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i), 0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
        }
        glNormal3f(0.f, 1.f, 0.f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0.2f, 0);
            glVertex3f(cos(i), 0.2f, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.2f, 0.9f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glNormal3f(cos(i), 0.f, sin(i));
            glVertex3f(cos(i), 0.2, sin(i));
            glVertex3f(cos(i), 0.0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
            glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    //
    //
    glTranslatef(0.f, 0.f, 15.f);
    glBegin(GL_TRIANGLES); {
        glNormal3f(0.f, -1.f, 0.f);
        glColor3f(0.2f, 0.9f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i), 0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
        }
        glNormal3f(0.f, 1.f, 0.f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0.2f, 0);
            glVertex3f(cos(i), 0.2f, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.2f, 0.9f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glNormal3f(cos(i), 0.f, sin(i));
            glVertex3f(cos(i), 0.2, sin(i));
            glVertex3f(cos(i), 0.0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
            glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glTranslatef(0.f, -0.75f, -15.f);
    //
    glScalef(0.5f, 5.f, 0.5f);
    glBegin(GL_TRIANGLES); {
        glNormal3f(0.f, -1.f, 0.f);
        glColor3f(0.4f, 0.5f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i), 0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
        }
        glNormal3f(0.f, 1.f, 0.f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0.2f, 0);
            glVertex3f(cos(i), 0.2f, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.4f, 0.5f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glNormal3f(cos(i), 0.f, sin(i));
            glVertex3f(cos(i), 0.2, sin(i));
            glVertex3f(cos(i), 0.0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
            glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glPopMatrix();
}

void drawChot2() {
    chot2dis = chot2dis > 0.9f ? 0.9f : chot2dis < 0.1f ? 0.1f : chot2dis;
    std::cout << chot2dis;
    chot2x = cos(-angle * M_PI / 180) * chot2dis;
    chot2z = sin(-angle * M_PI / 180) * chot2dis + 3.5f;

    glPushMatrix();
    glTranslatef(chot2x, 0.61, chot2z);
    glRotatef(lienKetAngle, 0.f, 1.f, 0.f);
    glScalef(0.2f, 1.f, 0.2f);
    glBegin(GL_QUADS); {
        glColor3f(0.9f, 0.3f, 0.3f);
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
    //
    glTranslatef(0.f, 0.2f, 0.f);
    glScalef(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLES); {
        glNormal3f(0.f, -1.f, 0.f);
        glColor3f(0.4f, 0.5f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i), 0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
        }
        glNormal3f(0.f, 1.f, 0.f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0.2f, 0);
            glVertex3f(cos(i), 0.2f, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.4f, 0.5f, 0.4f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glNormal3f(cos(i), 0.f, sin(i));
            glVertex3f(cos(i), 0.2, sin(i));
            glVertex3f(cos(i), 0.0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
            glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glPopMatrix();
}

void drawTayQuay() {
    glPushMatrix();
    glTranslatef(0.f, 0.41f, 3.5f);
    glRotatef(angle, 0.f, 1.f, 0.f);
    glScalef(0.3f, 1.f, 0.3f);
    glBegin(GL_TRIANGLES); {
        glNormal3f(0.f, -1.f, 0.f);
        glColor3f(0.9f, 0.5f, 0.3f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i), 0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
        }
        glNormal3f(0.f, 1.f, 0.f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0.2f, 0);
            glVertex3f(cos(i), 0.2f, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.9f, 0.5f, 0.3f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glNormal3f(cos(i), 0.f, sin(i));
            glVertex3f(cos(i), 0.2, sin(i));
            glVertex3f(cos(i), 0.0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
            glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    //
    // 
    glBegin(GL_QUADS); {
        glColor3f(0.9f, 0.5f, 0.3f);
        // botom
        glNormal3f(0.f, 0.f, -1.f);
        glVertex3f(-0.f, 0.f, -1.0f);
        glVertex3f(3.f, 0.f, -1.0f);
        glVertex3f(3.f, 0.2f, -1.0f);
        glVertex3f(-0.f, 0.2f, -1.0f);
        // top
        glNormal3f(0.f, 0.0f, 1.0f);
        glVertex3f(-0.f, 0.f, 1.f);
        glVertex3f(3.f, 0.f, 1.f);
        glVertex3f(3.f, 0.2f, 1.f);
        glVertex3f(-0.f, 0.2f, 1.f);
        // front
        glNormal3f(0.f, 1.0f, 0.f);
        glVertex3f(-0.f, 0.2f, -1.0f);
        glVertex3f(3.f, 0.2f, -1.0f);
        glVertex3f(3.f, 0.2f, 1.f);
        glVertex3f(-0.f, 0.2f, 1.f);
        // back
        glNormal3f(0.f, -1.f, 0.f);
        glVertex3f(-0.f, 0.f, -1.0f);
        glVertex3f(3.f, 0.f, -1.0f);
        glVertex3f(3.f, 0.f, 1.f);
        glVertex3f(-0.f, 0.f, 1.f);
        // left
        glNormal3f(-1.f, 0.f, 0.f);
        glVertex3f(-0.f, 0.f, -1.0f);
        glVertex3f(-0.f, 0.2f, -1.0f);
        glVertex3f(-0.f, 0.2f, 1.f);
        glVertex3f(-0.f, 0.f, 1.f);
        // right
        glNormal3f(1.f, 0.f, 0.f);
        glVertex3f(3.f, 0.f, -1.0f);
        glVertex3f(3.f, 0.2f, -1.0f);
        glVertex3f(3.f, 0.2f, 1.f);
        glVertex3f(3.f, 0.f, 1.f);
    }
    glEnd();
//
glTranslatef(3.f, 0.f, 0.f);
glBegin(GL_TRIANGLES); {
    glNormal3f(0.f, -1.f, 0.f);
    glColor3f(0.9f, 0.5f, 0.3f);
    for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
        glVertex3f(0, 0, 0);
        glVertex3f(cos(i), 0, sin(i));
        glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
    }
    glNormal3f(0.f, 1.f, 0.f);
    for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
        glVertex3f(0, 0.2f, 0);
        glVertex3f(cos(i), 0.2f, sin(i));
        glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
    }
}
glEnd();
glBegin(GL_QUADS); {
    glColor3f(0.9f, 0.5f, 0.3f);
    for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
        glNormal3f(cos(i), 0.f, sin(i));
        glVertex3f(cos(i), 0.2, sin(i));
        glVertex3f(cos(i), 0.0, sin(i));
        glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
        glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
    }
}
glEnd();
glPopMatrix();
}

void drawBanQuay() {
    glPushMatrix();
    glTranslatef(0.f, 0.21f, 3.5f);
    glRotatef(angle, 0.f, 1.f, 0.f);
    glBegin(GL_TRIANGLES); {
        glNormal3f(0.f, -1.f, 0.f);
        glColor3f(0.9f, 0.3f, 0.3f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i), 0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0, sin(i + M_PI / 64.f));
        }
        glNormal3f(0.f, 1.f, 0.f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glVertex3f(0, 0.2f, 0);
            glVertex3f(cos(i), 0.2f, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.2f, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.9f, 0.3f, 0.3f);
        for (float i = 0; i < M_PI * 2; i += M_PI / 64.f) {
            glNormal3f(cos(i), 0.f, sin(i));
            glVertex3f(cos(i), 0.2, sin(i));
            glVertex3f(cos(i), 0.0, sin(i));
            glVertex3f(cos(i + M_PI / 64.f), 0.0, sin(i + M_PI / 64.f));
            glVertex3f(cos(i + M_PI / 64.f), 0.2, sin(i + M_PI / 64.f));
        }
    }
    glEnd();
    glPopMatrix();
}
}
void drawAxes()
{
    if (toggleAxes == true) {
        /*  Length of axes */
        double len = 20.0f;
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
            for (float i = 0.0; i <= M_PI; i += 0.01) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
                glVertex3f(4, (cos(i) * radius), 1.0f);
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

        // Lower half circle
        glPushMatrix();
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        glTranslatef(6.0f, 0.0f, 0.0f);
        glScalef(0.5f, 1.0f, 1.0f);
        // Top
        glBegin(GL_TRIANGLE_STRIP); {
            glColor3f(0.0f, 1.0f, 1.0f);
            for (float i = 0.0; i <= M_PI; i += 0.01) {
                glVertex3f((sin(i) * radius), (cos(i) * radius), 1.0f);
                glVertex3f(4, (cos(i) * radius), 1.0f);
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
    float angle = 0.01f;
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
        butvex = sin(-angle * M_PI / 180) * butvedis * 4.0f;
        butvez = cos(-angle * M_PI / 180) * butvedis * 5.0f;
        lienketAngle = atan2(butvex , butvez - 1.2f) / M_PI * 180;


        glPushMatrix();
        glTranslatef(0.0f, 2.0f, -butvez + thanhTruotDis);
        glRotatef(lienketAngle, 0.f, 1.0f, 0.f);
        //glRotatef(-180, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 5.0f);
        glScalef(0.5f, 2.0f, 5.0f);
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

        //Reverse transform
        glTranslatef(0.0f, 0.0f, -3.0f);
        glScalef(1.0f, 1.0f, 1.0f/0.8f);

        // Cylinder
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 1.4f, 0.0f);
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
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -2.0f, -10.0f);
        glPopMatrix();

        //Ve phan tru dep
        glPushMatrix();
        //glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(1.0f, 0.2f, 1.0f);
        glTranslatef(0.0f, 11.0f, -butvez + thanhTruotDis);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI; k += 0.01f) {
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
            for (float k = 0; k <= 2 * M_PI; k += 0.01f) {
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
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, i, 0.0f);
            for (float k = 0; k <= 2 * M_PI; k += 0.01f) {
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
        glTranslatef(0.0f,-0.8f, 5.5f);
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
        glTranslatef(0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -1.1f, 7.8f);
        glScalef(0.6f, 1.0f, 0.6f);
        glBegin(GL_QUAD_STRIP);
        for (float k = 0; k <= 2 * M_PI; k += 0.001f) {
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
            for (float k = 0; k <= 2 * M_PI; k += 0.001f) {
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(i * cos(k), i, sin(k));
            }
            glEnd();
        }
        glPopMatrix();
    }
}


//Clear the current window and draw a triangle
void displayFunc(void) {
    // sky
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ortho) {
        glOrtho(-10.f * ratio, 10.f * ratio, -10.f, 10.f, -10.f, 10.f);
    }
    else {
        gluPerspective(45.f, ratio, 0.1f, 1000.0f);
        gluLookAt(camDistance * (float)cos(camDirection), camDistance * (float)sin(camDirection), camZ, 0.f, 0.f, 3.f, 0.f, 0.f, 1.f);
    }
    // Setup new frame
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Draw
    drawAxes();
    // Floor first
    //floorTile::drawFloor();
    
    // Latter part
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //drawGiaDo();
    //part2::drawBanQuay();
    //part2::drawTayQuay();
    //part2::drawChot2();
    //part2::drawThanhLienKet();
    //part2::drawChot3();

    moving::drawThanhButVe();
    //moving::drawButVe();
    /*moving::drawChot1();
    moving::drawTamTruot();
    moving::drawThanhLienKet();
    moving::drawChot2();

    base::drawRay();
    base::drawChanDe();
    base::drawGiaDo();*/
    

    if (animate == true) {
        glutTimerFunc(1, animation, 0);
    }

    glFlush();

    //buffer
    glutSwapBuffers();
    glutPostRedisplay();
}

void motionFunc(int x, int y) {
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
void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case '+': camDistance--; break;
        case '-': camDistance++; break;
        case 'v': case 'V': ortho = !ortho;
        case '1': part2::angle += 2.f; moving::angle += 2.0f; break;
        case '2': part2::angle -= 2.f; moving::angle -= 2.0f; break;
        case '3': part2::chot2dis += 0.1f; break;
        case '4': part2::chot2dis -= 0.1f; break;
        case 'x': case 'X': toggleAxes = !toggleAxes; std::cout << toggleAxes; break;
        case 'a': case 'A': animate = !animate; std::cout << animate;
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
    std::cout << "W: " << w << " H: " << h << std::endl;
}

void animation(int state) {
    
    if (animate == true) {
        part2::angle += 2.0f;
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, animation, 0);
    }
    
}

int main(int argc, char** argv) {
    //Init GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Set window position
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);      // window size
    //glutInitWindowPosition(500, 500);  // distance from the top-left screen
    glutCreateWindow("Hello world");    // message displayed on top bar window

    //Tell GLUT whenever main window needs to be repainted that it should call the function display() 
    glutDisplayFunc(displayFunc);

    // Maintain viewport
    glutReshapeFunc(reshapeFunc);

    //Recognize keyboard
    glutKeyboardFunc(keyboardFunc);

    //Set cam direction as mouse clicking position
    glutMotionFunc(motionFunc);

    //Set cam distance by mouse scroll
    glutMouseWheelFunc(mousewheelFunc);



    //Tell GLUT to start raeding and processing event. This function never return
    //The program only exit when user close the main window or kill the process
    glutMainLoop();

}