#include <GL/glut.h>
void drawTurtle()
{

}
void displayMe(void)
{
    double _x[17]={1.3,1.4,1.8,1.8,1.5,1.6,1.3,1.5,1.5,1.3,1.1,1.0,0.5,0.5,0.7,0.9,0.0};
    double _y[17]={-1.6,-1.9,-1.9,-1.6,-1.4,-1.2,-0.5,-0.4,-0.1,0.0,-0.1,-0.2,-0.2,0.0,0.2,0.5,0.8};
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<17;i++)
        {
            glVertex3f(_x[i]*0.1,_y[i]*0.1, 0.0);
        }
        for(int i=16;i>=0;i--)
        {
            glVertex3f(-1*_x[i]*0.1,_y[i]*0.1, 0.0);
        }
    glRotatef(-8,0.,1.,0.5);
        
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}