#include <iostream>
#include <windows.h>
#include <GL/freeglut.h>

using namespace std;

GLdouble left_m = 0.0;
GLdouble right_m = 800.0;
GLdouble bottom_m = 0.0;
GLdouble top_m = 800.0;
/*
GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;
*/
double ok = 1;
double j = 40.0;
double i = 0.0;
double contor = 0;
double loc_vert = 800;
int vector[4] = { 40, 230, 420, 610 };
//int vector[4] = {0, 160, 320, 480};
double height = vector[rand() % 4];
int score = 0;
double timp = 0.15;
int pct = 1000;
//double rsj, rdj, rss, rds = 0;

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

void init(void)
{
	glClearColor(0.22, 0.2, 0.3, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);

    glutBitmapString(font, string);
}
void startgame(void)
{

    if (height != j || (loc_vert > 90 || loc_vert < -90))
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

    glColor3f(0.3, 0.28, 0.4);
   
    // 1st delimiter
    glBegin(GL_POLYGON);
    glVertex2i(0, 0); // down left
    glVertex2i(800, 0); // down right
    glVertex2i(800, 40); // up right
    glVertex2i(0, 40); // up left
    glEnd();

    // stars on 1st
    drawStar(20, 15);

    // 2nd delimiter
    glBegin(GL_POLYGON);
    glVertex2i(0, 190); // down left
    glVertex2i(800, 190); // down right
    glVertex2i(800, 230); // up right
    glVertex2i(0, 230); // up left
    glEnd();

    // 3rd delimiter
    glBegin(GL_POLYGON);
    glVertex2i(0, 380); // down left
    glVertex2i(800, 380); // down right
    glVertex2i(800, 420); // up right
    glVertex2i(0, 420); // up left
    glEnd();

    // 4th delimiter
    glBegin(GL_POLYGON);
    glVertex2i(0, 570); // down left
    glVertex2i(800, 570); // down right
    glVertex2i(800, 610); // up right
    glVertex2i(0, 610); // up left
    glEnd();

    // 5th delimiter
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

    //desenam masina
    glPushMatrix();
    glTranslated(0.0, j, 0.0);

    glColor3f(0.996, 0.365, 0.149);
    glRecti(45, 15, 135, 45);
    /*
    if (ok == 0)
    {
        rsj = 8;
        rss = -8;
        rdj = -8;
        rds = 8;
    }
    */

    glPopMatrix();
    glPopMatrix();

    if (ok == 0) {
        RenderString(365.0f, 395.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
    }

    if (contor == 1 && (j != 230 && j != 420 && j != 610))
        j = j + 1;
    else if (contor == -1 && (j != 420 && j != 230 && j != 40))
        j = j - 1;
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
        if (j < 610)
        {
            contor = 1;
            j += 1;
        }

        glutPostRedisplay();
    }
}

void miscajos(void)
{
    if (ok != 0)
    {
        if (j > 40)
        {
            contor = -1;
            j -= 1;
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