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





void GameHelper::SetStartGame(int sg) 
{
    startGame = sg;
}

int GameHelper::GetStartGame() 
{
    return startGame;
}

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

class Asteroid : public Object
{
public:
    Asteroid() : Object(0.0, 0.0)
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
    bool OnAsteroidCrash(Asteroid& m);
private:
};

bool Rocket::OnAsteroidCrash(Asteroid& m)
{
    return true;
}


int currentTheme;
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
int GameHelper::startGame = 0;
//double rsj, rdj, rss, rds = 0;
double starScaleFactor = 1.;
double step = 0.0001;
double rotationAngle = 0.;
double angleStep = 0.01;
double comet_x = 600;
double comet_y = vector[rand() % 4];

void init(void)
{
    glClearColor(0.22, 0.2, 0.3, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);

}

void callback_main(int key)
{
    if (key == 0)
    {
        exit(0);
    }
}

void callback_theme(int key)
{
    currentTheme = key;
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{
    glColor3f(0.7f, 0.7f, 0.7f);
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
    else
    
    
    if (comet_y != r.GetY() || (comet_x > 90 || comet_x < -90))
    {
        if (i < -380)
            i = 0;
        i = i - 2 * timp;

        comet_x -= timp;

        if (comet_x < -6000)
        {
            score += 100;
            comet_y = vector[rand() % 4];
            cout << "Score:  " << score << endl;
            comet_x = 800;
        }

        if (score >= pct && pct <= 15000)
        {
            timp += 0.1;
            pct += 1000;
        }

        glutPostRedisplay();
    }
}

void scaleStars(void)
{
    if (starScaleFactor <= 1.01)
    {
        step = 0.0001;
    }
    else if (starScaleFactor >= 1.19)
    {
        step = -0.0001;
    }

    starScaleFactor += step;
}

void rotateRocket(void)
{

    rotationAngle += angleStep;
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (GameHelper::GetStartGame() == 0) {
        //start game
        RenderString(340.0f, 470.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"START GAME");
        RenderString(350.0f, 385.0f, GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"Press \"s\" to start");

        // big stars 
        {
            // 1st up left
            glPushMatrix();
            glTranslatef(200.0, 600.0, 0.0);
            glScalef(starScaleFactor, starScaleFactor, 0.0);
            glTranslatef(0.0, 0.0, 0.0);
            // body
            glColor3f(0.82, 0.4, 0.03);
            // rhombus horizontal
            glBegin(GL_POLYGON);
            glVertex2i(-100, 0);
            glVertex2i(0, -50);
            glVertex2i(100, 0);
            glVertex2i(0, 50);
            glEnd();
            // rhombus vertical
            glBegin(GL_POLYGON);
            glVertex2i(-50, 0);
            glVertex2i(0, -100);
            glVertex2i(50, 0);
            glVertex2i(0, 100);
            glEnd();
            // rhombus center
            glColor3f(1.0, 0.8, 0.5);
            glBegin(GL_POLYGON);
            glVertex2i(-25, 0);
            glVertex2i(0, -25);
            glVertex2i(25, 0);
            glVertex2i(00, 25);
            glEnd();
            glPopMatrix();

            //2nd up right
            glPushMatrix();
            glTranslatef(600.0, 600.0, 0.0);
            glScalef(starScaleFactor, starScaleFactor, 0.0);
            glTranslatef(0.0, 0.0, 0.0);
            // body
            glColor3f(0.82, 0.4, 0.03);
            // rhombus horizontal
            glBegin(GL_POLYGON);
            glVertex2i(-100, 0);
            glVertex2i(0, -50);
            glVertex2i(100, 0);
            glVertex2i(0, 50);
            glEnd();
            // rhombus vertical
            glBegin(GL_POLYGON);
            glVertex2i(-50, 0);
            glVertex2i(0, -100);
            glVertex2i(50, 0);
            glVertex2i(0, 100);
            glEnd();
            // rhombus center
            glColor3f(1.0, 0.8, 0.5);
            glBegin(GL_POLYGON);
            glVertex2i(-25, 0);
            glVertex2i(0, -25);
            glVertex2i(25, 0);
            glVertex2i(00, 25);
            glEnd();
            glPopMatrix();

            //3rd down center
            glPushMatrix();
            glTranslatef(400.0, 150.0, 0.0);
            glScalef(starScaleFactor, starScaleFactor, 0.0);
            // body
            glColor3f(0.82, 0.4, 0.03);
            // rhombus horizontal
            glBegin(GL_POLYGON);
            glVertex2i(-100, 0);
            glVertex2i(0, -50);
            glVertex2i(100, 0);
            glVertex2i(0, 50);
            glEnd();
            // rhombus vertical horizontal
            glBegin(GL_POLYGON);
            glVertex2i(-50, 0);
            glVertex2i(0, -100);
            glVertex2i(50, 0);
            glVertex2i(0, 100);
            glEnd();
            // rhombus center
            glColor3f(1.0, 0.8, 0.5);
            glBegin(GL_POLYGON);
            glVertex2i(-25, 0);
            glVertex2i(0, -25);
            glVertex2i(25, 0);
            glVertex2i(00, 25);
            glEnd();
            glPopMatrix();
        }
        
        // small stars
        {
            // 1st left
            glPushMatrix();
            glTranslatef(250.0, 350.0, 0.0);
            glScalef(starScaleFactor, starScaleFactor, 0.0);
            // body
            glColor3f(1.0, 0.8, 0.5);
            // rhombus horizontal
            glBegin(GL_POLYGON);
            glVertex2i(-75, 0);
            glVertex2i(0, -25);
            glVertex2i(75, 0);
            glVertex2i(0, 25);
            glEnd();
            // rhombus vertical
            glBegin(GL_POLYGON);
            glVertex2i(-25, 0);
            glVertex2i(0, -75);
            glVertex2i(25, 0);
            glVertex2i(0, 75);
            glEnd();
            // rhombus center
            glColor3f(0.82, 0.4, 0.03);
            glBegin(GL_POLYGON);
            glVertex2i(-20, 0);
            glVertex2i(0, -20);
            glVertex2i(20, 0);
            glVertex2i(0, 20);
            glEnd();
            glPopMatrix();

            // 2nd right 
            glPushMatrix();
            glTranslatef(550.0, 350.0, 0.0);
            glScalef(starScaleFactor, starScaleFactor, 0.0);
            // body
            glColor3f(1.0, 0.8, 0.5);
            // rhombus horizontal
            glBegin(GL_POLYGON);
            glVertex2i(-75, 0);
            glVertex2i(0, -25);
            glVertex2i(75, 0);
            glVertex2i(0, 25);
            glEnd();
            // rhombus vertical
            glBegin(GL_POLYGON);
            glVertex2i(-25, 0);
            glVertex2i(0, -75);
            glVertex2i(25, 0);
            glVertex2i(0, 75);
            glEnd();
            // rhombus center
            glColor3f(0.82, 0.4, 0.03);
            glBegin(GL_POLYGON);
            glVertex2i(-20, 0);
            glVertex2i(0, -20);
            glVertex2i(20, 0);
            glVertex2i(0, 20);
            glEnd();
            glPopMatrix();
        }
        
        scaleStars();

        //draw rocket
        {
            glPushMatrix();
            glTranslated(400.0, 600.0, 0.0);
            glRotated(rotationAngle, 0, 0, 1);
            glTranslated(-90.0, -30.0, 0.0);

            // tip
            glColor3f(0.996, 0.0, 0.0);
            glBegin(GL_POLYGON);
            glVertex2i(115, 20);
            glVertex2i(115, 40);
            glVertex2i(135, 30);
            glEnd();

            // sides
            glColor3f(0.3, 0.26, 0.3);
            glBegin(GL_POLYGON);
            glVertex2i(70, 20);
            glVertex2i(70, 15);
            glVertex2i(75, 20);
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2i(70, 40);
            glVertex2i(70, 45);
            glVertex2i(75, 40);
            glEnd();

            // back
            glColor3f(0.3, 0.26, 0.3);
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
        
        rotateRocket();
        
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
            glColor3f(0.3, 0.26, 0.3);
            glBegin(GL_POLYGON);
            glVertex2i(70, 20);
            glVertex2i(70, 15);
            glVertex2i(75, 20);
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2i(70, 40);
            glVertex2i(70, 45);
            glVertex2i(75, 40);
            glEnd();

            // back
            glColor3f(0.3, 0.26, 0.3);
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
            RenderString(345.0f, 395.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"GAME OVER");
        }

        if (contor == 1 && (r.GetY() != 275 && r.GetY() != 465 && r.GetY() != 655))
            r.SetY(r.GetY() + 1);
        else if (contor == -1 && (r.GetY() != 465 && r.GetY() != 275 && r.GetY() != 85))
            r.SetY(r.GetY() - 1);
        else
            contor = 0;

        // asteroids
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

        // comets
        glPushMatrix();
        glTranslatef(comet_x, comet_y, 0.0);
        // tail
        glColor3f(0.82, 0.4, 0.03);
        glBegin(GL_POLYGON);
        glVertex2i(7.5, 15);
        glVertex2i(60, 25);
        glVertex2i(45, 15);
        glVertex2i(60, 5);
        glEnd();
        // body
        glColor3f(1.0, 0.8, 0.5);
        // rhombus horizontal
        glBegin(GL_POLYGON);
        glVertex2i(0, 15);
        glVertex2i(15, 7.5);
        glVertex2i(30, 15);
        glVertex2i(15, 22.5);
        glEnd();
        // rhombus vertical
        glBegin(GL_POLYGON);
        glVertex2i(7.5, 15);
        glVertex2i(15, 0);
        glVertex2i(22.5, 15);
        glVertex2i(15, 30);
        glEnd();
        // rhombus center
        glColor3f(0.82, 0.4, 0.03);
        glBegin(GL_POLYGON);
        glVertex2i(10.25, 15);
        glVertex2i(15, 10.25);
        glVertex2i(18.75, 15);
        glVertex2i(15, 18.75);
        glEnd();
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
    int menuTheme, menuMain;

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

    menuTheme = glutCreateMenu(callback_theme);
    glutAddMenuEntry("Classic", 1);
    glutAddMenuEntry("Asteroids belt (hard)", 2);

    menuMain = glutCreateMenu(callback_main);
    glutAddSubMenu("Mode ", menuTheme);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
