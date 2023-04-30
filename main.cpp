#include <iostream>
#include <windows.h>
#include <GL/freeglut.h>

using namespace std;

#pragma comment(lib, "Winmm.lib")

//class Planet
//{
//public:
//    
//private:
//
//};


class Object
{
public:
    Object()
    {
        x = 0.0;
        y = 0.0;
    }
    Object(GLdouble px, GLdouble py)
    {
        x = px;
        y = py;
    }

    const GLdouble GetX();
    void SetX(GLdouble newX);
    const GLdouble GetY();
    void SetY(GLdouble y);
private:
    GLdouble x;
    GLdouble y;
};

const GLdouble Object::GetX()
{
    return x;
}

const GLdouble Object::GetY()
{
    return y;
}

void Object::SetX(GLdouble newX)
{
    x = newX;
}

void Object::SetY(GLdouble newY)
{
    y = newY;
}


class GameHelper
{
public:
    static bool CheckCollision(Object ob1, Object ob2);

private:
    
};

bool GameHelper::CheckCollision(Object ob, Object ob2)
{
    return false;
}

struct Color
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
};


class DisplayHelper
{
public:
    //static Color GetBackgroundColor();

private:
    DisplayHelper() = delete;
    //static Color bkgColor;

};


//Color DisplayHelper::GetBackgroundColor()
//{
//    return bkgColor;
//}

class Meteorite : public Object
{
public:
    Meteorite() : Object(0.0, 0.0)
    {};
private:


};

class Rocket : public Object
{
public:
    Rocket();
    Rocket(GLdouble x, GLdouble y)
    {
        SetX(x);
        SetY(y);
    }
    bool OnMeteoriteCrash(Meteorite& m);
private:
};

bool Rocket::OnMeteoriteCrash(Meteorite& m)
{
    return true;
}


GLdouble left_m = 0.0;
GLdouble right_m = 800.0;
GLdouble bottom_m = 0.0;
GLdouble top_m = 800.0;

double ok = 1;
double i = 0.0;
double contor = 0;
double loc_vert = 800;
int vector[4] = { 40, 230, 420, 610 };
//int vector[4] = {0, 160, 320, 480};
double height = vector[rand() % 4];
int score = 0;
double timp = 0.15;
int pct = 1000;
Rocket r(0.0, 40.0);
//double rsj, rdj, rss, rds = 0;

/*
void drawStar(double xStart, double yStart)
{
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);

    //first bisection segment
    glVertex2i(xStart, yStart);
    glVertex2i(xStart + 10, yStart + 10);

    //second bisection segment
    glVertex2i(xStart + 10, yStart);
    glVertex2i(xStart, yStart + 10);

    //vertical segment
    glVertex2i(xStart + 5, yStart);
    glVertex2i(xStart + 5, yStart + 10);

    //horizontal segment
    glVertex2i(xStart, yStart + 5);
    glVertex2i(xStart + 10, yStart + 5);

    glEnd();
}
*/

void init(void)
{
    glClearColor(0.22, 0.2, 0.3, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
    PlaySound((LPCTSTR)SND_ALIAS_SYSTEMSTART, NULL, SND_ALIAS_ID);
    cout << "Played sound\n";

}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);

    glutBitmapString(font, string);
}
void startgame(void)
{

    if (height != r.GetY() || (loc_vert > 90 || loc_vert < -90))
    {

        if (i < -380)
            i = 0;
        i = i - 2 * timp;

        loc_vert -= timp;

        if (loc_vert < -150)
        {
            score += 100;
            height = vector[rand() % 4];
            cout << "Score:  " << score << endl;
            loc_vert = 800;
        }

        if (score >= pct && pct <= 15000)
        {
            timp += 0.1;
            pct += 1000;
        }

        glutPostRedisplay();
    }
    else
        ok = 0;

}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Lane delimitation
    // * 4 lanes
    // * 5 delimiters

    // 1st delimiter
    glColor3f(0.3, 0.28, 0.4);

    glBegin(GL_POLYGON);
    glVertex2i(0, 0); // down left
    glVertex2i(800, 0); // down right
    glVertex2i(800, 40); // up right
    glVertex2i(0, 40); // up left
    glEnd();

    // stars on 1st

    //drawStar(20, 15);

    // rhombus body
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(15, 20);
    glVertex2i(20, 15);
    glVertex2i(25, 20);
    glVertex2i(20, 25);
    glEnd();

    // rhombus center
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(17.5, 20);
    glVertex2i(20, 17.5);
    glVertex2i(22.5, 20);
    glVertex2i(22.5, 22.5);
    glEnd();

    // triangles
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(15, 20);
    glVertex2i(16, 19);
    glVertex2i(16, 21);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(25, 20);
    glVertex2i(24, 19);
    glVertex2i(24, 21);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(20, 25);
    glVertex2i(19, 24);
    glVertex2i(21, 24);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(20, 15);
    glVertex2i(19, 16);
    glVertex2i(21, 16);
    glEnd();

    // 2nd delimiter
    glColor3f(0.3, 0.28, 0.4);

    glBegin(GL_POLYGON);
    glVertex2i(0, 190); // down left
    glVertex2i(800, 190); // down right
    glVertex2i(800, 230); // up right
    glVertex2i(0, 230); // up left
    glEnd();

    // 3rd delimiter
    glColor3f(0.3, 0.28, 0.4);

    glBegin(GL_POLYGON);
    glVertex2i(0, 380); // down left
    glVertex2i(800, 380); // down right
    glVertex2i(800, 420); // up right
    glVertex2i(0, 420); // up left
    glEnd();

    // 4th delimiter
    glColor3f(0.3, 0.28, 0.4);

    glBegin(GL_POLYGON);
    glVertex2i(0, 570); // down left
    glVertex2i(800, 570); // down right
    glVertex2i(800, 610); // up right
    glVertex2i(0, 610); // up left
    glEnd();

    // 5th delimiter
    glColor3f(0.3, 0.28, 0.4);

    glBegin(GL_POLYGON);
    glVertex2i(0, 760); // down left
    glVertex2i(800, 760); // down right
    glVertex2i(800, 800); // up right
    glVertex2i(0, 800); // up left
    glEnd();

    /*
    glColor3f(0.22, 0.2, 0.3); // grey



    // Iarba de jos
    glBegin(GL_POLYGON);
    glVertex2i(-100, -140); // Stanga jos
    glVertex2i(700, -140); // Dreapta jos
    glVertex2i(700, -80); // Dreapta sus
    glVertex2i(-100, -80); // Stanga sus
    glEnd();

    // Iarba de sus
    glBegin(GL_POLYGON);
    glVertex2i(-100, 400);// Stanga jos
    glVertex2i(700, 400); // Dreapta jos
    glVertex2i(700, 460); // Dreapta sus
    glVertex2i(-100, 460);// Stanga sus
    glEnd();
    //RenderString(200.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Depaseste masinile!");

    // Delimitare sosea
    glLineWidth(3);
    glColor3f(1, 1, 1);

    // Delimitam soseaua de iarba partea de jos
    glBegin(GL_LINES);
    glVertex2i(-100, -80);
    glVertex2i(1500, -80);
    glEnd();

    // Delimitam soseaua de iarba partea de sus
    glBegin(GL_LINES);
    glVertex2i(-100, 400);
    glVertex2i(1500, 400);
    glEnd();

    // Liniile intrerupte
    glPushMatrix();
    glTranslated(i, 0.0, 0.0);


    glBegin(GL_LINES);
    glVertex2i(-100, 80);
    glVertex2i(1500, 80);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(-100, 240);
    glVertex2i(1500, 240);
    glEnd();
    glPopMatrix();
    */

    //draw rocket
    glPushMatrix();
    glTranslated(r.GetX(), r.GetY(), 0.0);


    //start point 45, 15, 135, 45

    // tip
    glColor3f(0.996, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(115, 20);
    glVertex2i(115, 40);
    glVertex2i(135, 30);
    glEnd();

    // sides
    glColor3f(0.27, 0.26, 0.25);
    glBegin(GL_POLYGON);
    glVertex2i(65, 20);
    glVertex2i(65, 15);
    glVertex2i(70, 20);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(65, 40);
    glVertex2i(65, 45);
    glVertex2i(70, 40);
    glEnd();

    // back
    glColor3f(0.3, 0.3, 0.4);
    glRecti(58, 23, 65, 37);

    // flames
    glColor3f(0.82, 0.4, 0.03);
    glBegin(GL_POLYGON);
    glVertex2i(58, 23);
    glVertex2f(53., 25.5);
    glVertex2i(58, 28);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(58, 32);
    glVertex2f(53., 34.5);
    glVertex2i(58, 37);
    glEnd();

    glColor3f(0.82, 0.10, 0.03);
    glBegin(GL_POLYGON);
    glVertex2i(58, 28);
    glVertex2i(45, 30);
    glVertex2i(58, 32);
    glEnd();


    // body
    glColor3f(0.26, 0.3, 0.4);
    glRecti(65, 20, 115, 40);

    glPopMatrix();


    glPopMatrix();

    if (ok == 0) {
        RenderString(365.0f, 395.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
    }

    if (contor == 1 && (r.GetY() != 230 && r.GetY() != 420 && r.GetY() != 610))
        r.SetY(r.GetY() + 1);
    else if (contor == -1 && (r.GetY() != 420 && r.GetY() != 230 && r.GetY() != 40))
        r.SetY(r.GetY() - 1);
    else
        contor = 0;

    //desenam a doua masina (adversara)
    glPushMatrix();
    glTranslated(loc_vert, height, 0.0);

    glColor3f(0.4, 0.4, 0.4);
    glRecti(45, 15, 75, 45);


    glPopMatrix();

    startgame();
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 800.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void miscasus(void)
{
    if (ok != 0)
    {
        if (r.GetY() < 610)
        {
            contor = 1;
            r.SetY(r.GetY() + 1);
        }

        glutPostRedisplay();
    }
}

void miscajos(void)
{
    if (ok != 0)
    {
        if (r.GetY() > 40)
        {
            contor = -1;
            r.SetY(r.GetY() - 1);
        }

        glutPostRedisplay();
    }
}

void keyboard(int key, int x, int y)
{


    switch (key) {
    case GLUT_KEY_UP:
        miscasus();
        break;
    case GLUT_KEY_DOWN:
        miscajos();
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Space Surf");
    init();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);

    glutMainLoop();
}
