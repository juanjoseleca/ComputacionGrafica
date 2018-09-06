#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265
void displayMe(void)
{
    double x1=-0.5,y1=0.5,x2=0.4,y2=0.4;
    double m,y_;
    float distancia=0.01;
    int radio=1;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    if(x1<x2)
    {
        m=(y2-y1)/(x2-x1);
        for(double x_=x1;x_<=x2;x_+=distancia)
        {
            y_=m*(x_-x1)+y1;
            glVertex3f(x_,y_,0.0);
        }
    }
    else
    {
        m=(y1-y2)/(x1-x2);
        for(double x_=x1;x_<=x2;x_+=distancia)
        {
            y_=m*(x_-x2)+y2;
            glVertex3f(x_,y_,0.0);
        }
    }
    
    
    /*
    double angulo=360.0/x;
    double x_;
    double y_;
    for(int i=0;i<x;i++)
    {
        x_=radio*cos((i*angulo)*((2*PI)/360));
        y_=radio*sin((i*angulo)*((2*PI)/360));
        glVertex3f(x_,y_,0.0);
    }
    */
   //glVertex3f(0.5,0.5,0.0);
   //glVertex3f(0.0,0.5,0.0);
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