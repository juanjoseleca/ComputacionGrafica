#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265
void displayMe(void)
{
    int x=8;
    int radio=1;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    double angulo=360.0/x;
    double x_;
    double y_;
    for(int i=0;i<x;i++)
    {
        x_=radio*cos((i*angulo)*((2*PI)/360));
        y_=radio*sin((i*angulo)*((2*PI)/360));
        glVertex3f(x_,y_,0.0);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Poligonos");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}