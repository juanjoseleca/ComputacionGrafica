#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

class Esquinas {
public:
    GLint minY;
    GLint maxY;
    GLint minX;
    GLint maxX;
    GLfloat xVal;
    GLfloat slope;
    Esquinas(tuple<GLint, GLint> vertexOne, tuple<GLint, GLint> vertexTwo);
};
Esquinas::Esquinas(tuple<GLint, GLint> vertexOne, tuple<GLint, GLint> vertexTwo) {
    this->minY = min(get<1>(vertexOne), get<1>(vertexTwo));
    this->maxY = max(get<1>(vertexOne), get<1>(vertexTwo));
    this->minX = min(get<0>(vertexOne), get<0>(vertexTwo));
    this->maxX = max(get<0>(vertexOne), get<0>(vertexTwo));
    
    
    if (min(get<1>(vertexOne), get<1>(vertexTwo)) == get<1>(vertexOne)) {
        this->xVal = get<0>(vertexOne);
    } else {
        this->xVal = get<0>(vertexTwo);
    }
    this->slope =
    static_cast<GLfloat>(static_cast<GLfloat>(get<1>(vertexOne) - get<1>(vertexTwo)))
    / static_cast<GLfloat>((get<0>(vertexOne) - get<0>(vertexTwo)));
}
struct less_than_key
{
    inline bool operator() (const Esquinas& struct1, const Esquinas& struct2)
    {
        if (struct1.minY != struct2.minY)
            return (struct1.minY < struct2.minY);
        return (struct1.minX < struct2.minX);
    }
};

struct by_x_val_key
{
    inline bool operator() (const Esquinas& struct1, const Esquinas& struct2)
    {
        return (struct1.xVal < struct2.xVal);
    }
};

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

int x_pos;
int y_pos;
int X_DOWN;
GLint scanline;
bool TOGGLE_STATE;
bool MOUSE_STATE;
bool DRAWING; 
bool EDGE_PARITY;
vector<tuple<GLint, GLint>> points; 
vector<Esquinas> allEsquinas; 
vector<Esquinas> activeEsquinas; 
Color *pixels; 

void Colorear(GLfloat x1, GLfloat x2) {

    int i1 = roundf(x1);
    int i2 = roundf(x2);
    int count = 0;
    
    for (int i = ((500 * (500 - scanline)) + i1); i < ((500 * (500 - scanline)) + i2); i++, count++) {
        pixels[i].r = 0;
        pixels[i].b = 0;
        pixels[i].g = 0;
        glutPostRedisplay();

    }

}


void removeActiveEsquinasByScanline() {
    for (vector<Esquinas>::iterator it = activeEsquinas.begin(); it < activeEsquinas.end(); ) {
        if (it->maxY == scanline) {
            activeEsquinas.erase(it);
        } else {
            it++;
        }
    }
}


void updateXValues() {
    for (vector<Esquinas>::iterator it = activeEsquinas.begin(); it < activeEsquinas.end(); it++) {
        it->xVal += (1/it->slope);
    }
}


void updateActiveEsquinas() {
    for (vector<Esquinas>::iterator it = allEsquinas.begin(); it < allEsquinas.end(); it++) {
        if (it->minY == scanline) {
            activeEsquinas.push_back(*it);
        }
        if (it->minY > scanline) {
            return;
        }
    }
}

void initScanline() {
    if (allEsquinas.size() != 0) {
        scanline = allEsquinas.at(0).minY;
        glutPostRedisplay();
    }
}


void sortAndFilterEsquinas() {
    sort(allEsquinas.begin(), allEsquinas.end(), less_than_key());
    for (vector<Esquinas>::iterator it = allEsquinas.begin(); it < allEsquinas.end(); it++) {

        if (it->slope == 0) {
            allEsquinas.erase(it);
        }
    }
}

void sortActiveEsquinasByXValues() {
    sort(activeEsquinas.begin(), activeEsquinas.end(), by_x_val_key());
}


void Llenar() {

    while (activeEsquinas.size() != 0) {
        for (vector<Esquinas>::iterator it = activeEsquinas.begin(); it < activeEsquinas.end(); it++) {
            Colorear(it->xVal, (it+1)->xVal);
            it++;
        }
        scanline++;
        removeActiveEsquinasByScanline();
        updateXValues();
        updateActiveEsquinas();
        sortActiveEsquinasByXValues();
        glutPostRedisplay();
    }
}

void init(void) {
    

    glClearColor(1.0, 1.0, 1.0, 0.0);
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500, 500, 0.0, 0.0, 1.0);
    

    pixels = new Color[500*500];
    

    for (int i = 0; i < 500*500; i++) {
        pixels[i].r = 1;
        pixels[i].g = 1;
        pixels[i].b = 1;
    }
    
    DRAWING = false;
}


void keyboard(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case 27:
            free(pixels);

            exit(0);
            break;
    }
    glutPostRedisplay();
}


void menu(int id) {
    switch (id) {
        case 1:
        {
            Esquinas newEdge(points.at(0), points.at(points.size()-1));
            allEsquinas.push_back(newEdge);
            sortAndFilterEsquinas();
            initScanline();
            updateActiveEsquinas();
            DRAWING = true;
            glutPostRedisplay();
            Llenar();
            break;
        }
            
        case 2:
        {
            cout<<"menu 2"<<endl;
            int iz=999;int der=0;int top=999; int bot=0;
            for (auto i : points)
            {
                
                cout<<"Punto: "<<get<0>(i)<<"-"<<get<1>(i)<<endl;
                if(get<0>(i)<iz) iz=get<0>(i);
                if(get<0>(i)>der) der=get<0>(i);
                if(get<1>(i)<top) top=get<1>(i);
                if(get<1>(i)>bot) bot=get<1>(i);
            } 
            int p_i =(iz+der)/2;
            int p_j=(top+bot)/2;
            cout<<p_i<<"-----"<<p_j<<endl;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	        glLoadIdentity();
            for (int i = 0; i < 500*500; i++) {
                pixels[i].r = 1;
                pixels[i].g = 1;
                pixels[i].b = 1;
            }
            cout<<"GLOBAL: "<<x_pos<<"-"<<y_pos<<endl;
            int mov_x=x_pos-p_i;
            int mov_y=y_pos-p_j;
            cout<<"LOOK:";
            for(auto i: points)
            {
                cout<<get<0>(i)<<"-"<<get<1>(i)<<"|";
            }
            cout<<endl;
            for(int r=0;r<points.size();r++)
            {
                get<0>(points[r])+=mov_x;
                get<1>(points[r])+=mov_y;
            }

            allEsquinas.clear();
            activeEsquinas.clear();
            cout<<"$$$"<<endl;
            for(int a=0;a<points.size()-1;a++)
            {
                cout<<get<0>(points[a])<<"-"<<get<1>(points[a])<<"|";
                Esquinas newEdge (points[a],points[a+1]);
                allEsquinas.push_back(newEdge);
            }
            Esquinas newEdge(points.at(0), points.at(points.size()-1));
            allEsquinas.push_back(newEdge);
            sortAndFilterEsquinas();
            initScanline();
            updateActiveEsquinas();
            DRAWING = true;
            glutPostRedisplay();
            Llenar();
            break;
            
        }
        case 3:
        {
            
        }
            
    }
    glutPostRedisplay();
}


void click(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
        {
            if(state == GLUT_DOWN && !DRAWING) {
                points.push_back(tuple<GLint, GLint>(x, y));
                if (points.size() > 1) {
                    Esquinas newEdge(points.at(points.size()-2), points.at(points.size()-1));
                    allEsquinas.push_back(newEdge);
                }
                glutPostRedisplay();
            }
            break;
        }
        case GLUT_RIGHT_BUTTON:
        {
            cout<<"==================="<<endl;
            x_pos=x;
            y_pos=y;
        }
    }
    glutPostRedisplay();
}

void display(void) {

    GLenum err_code;
    do {
        err_code = glGetError();
        if (err_code != GL_NO_ERROR)
            printf("Error: %s\n", gluErrorString(err_code));
    } while (err_code != GL_NO_ERROR);

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawPixels(500, 500, GL_RGB, GL_FLOAT, pixels);
    
    glPointSize(5);
    glColor3f(1.0, 0.0, 1.0);

    if (!DRAWING) {
        for (int i = 0; i < points.size(); i++) {
            glBegin(GL_POINTS);
            glVertex2f(get<0>(points.at(i)), get<1>(points.at(i)));
            glEnd();
        }
    }

    if (DRAWING) {
        glDrawPixels(500, 500, GL_RGB, GL_FLOAT, pixels);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        for (int i = 0; i < points.size(); i++) {
            glVertex2f(get<0>(points.at(i)), get<1>(points.at(i)));
        }
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Computacion Grafica");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(click);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Dibujar poligono", 1);
    glutAddMenuEntry("Mover",2);
    glutAddMenuEntry("Limpiar",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    
    return 0;
    
}
