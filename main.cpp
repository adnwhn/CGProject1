#include "Utils.cpp"

using namespace std;

#pragma once
#pragma comment(lib, "Winmm.lib")


GLdouble left_m = 0.0;
GLdouble right_m = 800.0;
GLdouble bottom_m = 0.0;
GLdouble top_m = 800.0;

double ok = 1;
double i = 0.0;
double contor = 0;
double loc_vert = 800;
int vector[4] = { 85, 275, 465, 655 };
double height = vector[rand() % 4];
int GameHelper::score = 0;
double timp = 0.15;
int pct = 1000;
Rocket r(0.0, 85.0, 90.0, 30.0);
Meteorite m(800., vector[rand() % 4], 30., 30.);
int GameHelper::startGame = 0;
char* DisplayHelper::sound_file = const_cast<char*>(".wav");


void GameHelper::SetStartGame(int sg) {
    startGame = sg;
}

int GameHelper::GetStartGame() {
    return startGame;
}

bool GameHelper::CheckCollision(Rocket ob, Meteorite ob2)
{
    return (ob2.GetY() == ob.GetY() && (m.GetX() > 45 && m.GetX() < 90));
}

Rocket::Rocket(GLdouble x, GLdouble y, GLdouble xdim, GLdouble ydim)
{
    SetX(x);
    SetY(y);
    xDim = xdim;
    yDim = ydim;
}

bool Rocket::OnMeteoriteCrash(Meteorite& m)
{
    return true;
}

Meteorite::Meteorite(GLdouble x, GLdouble y, GLdouble xdim, GLdouble ydim)
{
    SetX(x);
    SetY(y);
    xDim = xdim;
    yDim = ydim;
}

void DisplayHelper::StartMusic()
{
    PlaySound((LPCTSTR)sound_file, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

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

}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

    glutBitmapString(font, string);
}
void startgame(void)
{

    if (GameHelper::CheckCollision(r, m))
    {
        GameHelper::SetStartGame(2);
    }
    else
    {

        if (i < -380)
            i = 0;
        i = i - 2 * timp;

        m.SetX(m.GetX() - timp);

        if (m.GetX() < -150)
        {
            GameHelper::score += 100;
            m.SetY(vector[rand() % 4]);
            cout << "Score:  " << GameHelper::score << endl;
            m.SetX(800.);
        }

        if (GameHelper::score >= pct && pct <= 15000)
        {
            timp += 0.1;
            pct += 1000;
        }

        glutPostRedisplay();
    }
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (GameHelper::GetStartGame() == 0) {
        //start game
        RenderString(350.0f, 400.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"START GAME");
        RenderString(315.0f, 385.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"Press \"s\" to start");

        // stars 
        glPushMatrix();
        //glScalef(1.25, 1.25, 0.0);
        // 1st up left
        // body
        glColor3f(0.8, 0.5, 0.3);
        // rhombus vertical
        glBegin(GL_POLYGON);
        glVertex2i(100, 600);
        glVertex2i(200, 550);
        glVertex2i(300, 600);
        glVertex2i(200, 650);
        glEnd();
        // rhombus horizontal
        glBegin(GL_POLYGON);
        glVertex2i(150, 600);
        glVertex2i(200, 500);
        glVertex2i(250, 600);
        glVertex2i(200, 700);
        glEnd();
        // rhombus center
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex2i(175, 600);
        glVertex2i(200, 575);
        glVertex2i(225, 600);
        glVertex2i(200, 625);
        glEnd();

        //2nd up right
        // body
        glColor3f(0.8, 0.5, 0.3);
        // rhombus vertical
        glBegin(GL_POLYGON);
        glVertex2i(500, 600);
        glVertex2i(600, 550);
        glVertex2i(700, 600);
        glVertex2i(600, 650);
        glEnd();
        // rhombus horizontal
        glBegin(GL_POLYGON);
        glVertex2i(550, 600);
        glVertex2i(600, 500);
        glVertex2i(650, 600);
        glVertex2i(600, 700);
        glEnd();
        // rhombus center
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex2i(575, 600);
        glVertex2i(600, 575);
        glVertex2i(625, 600);
        glVertex2i(600, 625);
        glEnd();

        //3rd down center
        // body
        glColor3f(0.8, 0.5, 0.3);
        // rhombus vertical
        glBegin(GL_POLYGON);
        glVertex2i(300, 150);
        glVertex2i(400, 100);
        glVertex2i(500, 150);
        glVertex2i(400, 200);
        glEnd();
        // rhombus horizontal
        glBegin(GL_POLYGON);
        glVertex2i(350, 150);
        glVertex2i(400, 50);
        glVertex2i(450, 150);
        glVertex2i(400, 250);
        glEnd();
        // rhombus center
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex2i(375, 150);
        glVertex2i(400, 125);
        glVertex2i(425, 150);
        glVertex2i(400, 175);
        glEnd();

        glPopMatrix();
    }
    else {

        {
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
        }



        {
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
        }


        if (GameHelper::GetStartGame() == 2) {
            //game over
            RenderString(365.0f, 395.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
        }

        if (contor == 1 && (r.GetY() != 275 && r.GetY() != 465 && r.GetY() != 655))
            r.SetY(r.GetY() + 1);
        else if (contor == -1 && (r.GetY() != 465 && r.GetY() != 275 && r.GetY() != 85))
            r.SetY(r.GetY() - 1);
        else
            contor = 0;

        //desenam a doua masina (adversara)
        glPushMatrix();
        glTranslated(m.GetX(), m.GetY(), 0.0);

        glColor3f(0.4, 0.4, 0.4);
        glBegin(GL_POLYGON);
        glVertex2i(45, 15);
        glVertex2i(45, 37);
        glVertex2i(62, 37);
        glVertex2i(62, 45);
        glVertex2i(75, 45);
        glVertex2i(75, 38);
        glVertex2i(65, 38);
        glVertex2i(45, 38);
        glEnd();

        glColor3f(0.56, 1., 1.);
        glRecti(50, 20, 58, 28);


        glPopMatrix();

        startgame();
    }

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
    if (GameHelper::GetStartGame() != 2)
    {
        if (r.GetY() < 655)
        {
            contor = 1;
            r.SetY(r.GetY() + 1);
        }

        glutPostRedisplay();
    }
}

void miscajos(void)
{
    if (GameHelper::GetStartGame() != 2)
    {
        if (r.GetY() > 85)
        {
            contor = -1;
            r.SetY(r.GetY() - 1);
        }

        glutPostRedisplay();
    }
}

void keyboardNormal(unsigned char key, int xx, int yy)
{
    switch (key) {
    case 's':
        GameHelper::SetStartGame(1);
        break;
    }
}

void keyboardSpecial(int key, int x, int y)
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
    glutKeyboardFunc(keyboardNormal);
    glutSpecialFunc(keyboardSpecial);

    glutMainLoop();
}
