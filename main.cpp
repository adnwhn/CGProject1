#include "Utils.cpp"
#include <string>

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
int vector[4] = { 85, 275, 465, 655 };
double height = vector[rand() % 4];
int GameHelper::score = 0;
double timp = 0.15;
int pct = 1000;
Rocket r(0.0, 85.0, 90.0, 30.0);
Meteorite m(800., vector[rand() % 4], 30., 30.);
int GameHelper::startGame = 0;
char* DisplayHelper::sound_file = const_cast<char*>(".wav");
double starScaleFactor = 1.;
double step = 0.0001;
double rotationAngle = 0.;
double angleStep = 0.01;
Comet c(600., vector[rand() % 4]);
bool GameHelper::immunity = false;
int GameHelper::immunityc = 0;
Color GameHelper::bkg;
GameHelper::Mode GameHelper::mode = GameHelper::Mode::normal;
Color GameHelper::bkgCometMode;


void GameHelper::SetStartGame(int sg) {
    startGame = sg;
}

int GameHelper::GetStartGame() {
    return startGame;
}

bool GameHelper::CheckCollision(Rocket ob, Meteorite ob2)
{
    return (ob2.GetY() == ob.GetY() && (m.GetX() > 45 && m.GetX() < 90) && !GameHelper::immunity);
}

bool GameHelper::CheckCollision(Rocket ob, Comet ob2)
{
    if (ob2.GetY() == ob.GetY() && (c.GetX() > 45 && c.GetX() < 90))
    {

        GameHelper::immunity = true;
        GameHelper::mode = GameHelper::Mode::immunity;
        GameHelper::immunityc = 400;
        cout << "ON Immunity\n";
    }

    // return false so game can continue
    return false;
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

void DisplayHelper::StopMusic()
{
    PlaySound(NULL, 0, 0);
}

void DisplayHelper::ChangeBackground(Color c)
{
    glClearColor(c.r, c.g, c.b, 1.0);
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

Comet::Comet(GLdouble x, GLdouble y)
{
    SetX(x);
    SetY(y);
}


void init(void)
{
    GameHelper::bkg.r = 0.22;
    GameHelper::bkg.g = 0.2;
    GameHelper::bkg.b = 0.3;
    GameHelper::bkgCometMode.r = 0.45;
    GameHelper::bkgCometMode.g = 0.45;
    GameHelper::bkgCometMode.b = 0.62;


    DisplayHelper::ChangeBackground(GameHelper::bkg);
    glMatrixMode(GL_PROJECTION);
    glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);


}

void RenderString(float x, float y, void* font, const unsigned char* string)
{
    glColor3f(0.7f, 0.7f, 0.7f);
    glRasterPos2f(x, y);
    glutBitmapString(font, string);
}

void startgame(void)
{

    if (GameHelper::CheckCollision(r, m) || GameHelper::CheckCollision(r, c))
    {
        GameHelper::SetStartGame(2);
    }
    else
    {
        int is = GameHelper::score;
        if (i < -380)
            i = 0;
        i = i - 2 * timp;

        m.SetX(m.GetX() - timp);

        c.SetX(c.GetX() - timp);

        if (m.GetX() < -150 || c.GetX() < -6000)
        {
            GameHelper::score += 100;
            if (GameHelper::immunity)
            {
                GameHelper::immunityc -= 100;
                cout << "Immunity: " << GameHelper::immunityc << '\n';
                if (GameHelper::immunityc == 0)
                {
                    GameHelper::immunity = false;
                    GameHelper::mode = GameHelper::Mode::normal;
                    cout << "NO Immunity \n";
                }

            }
        }

        if (m.GetX() < -150)
        {
            m.SetY(vector[rand() % 4]);
            m.SetX(800.);
        }
        if (c.GetX() < -6000)
        {
            c.SetY(vector[rand() % 4]);
            c.SetX(800.);
        }

        if (GameHelper::score != is)
            cout << "Score:  " << GameHelper::score << endl;

        if (GameHelper::score >= pct && pct <= 15000)
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

void drawScene(void)
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

            switch (GameHelper::mode)
            {
            case GameHelper::Mode::normal:
                DisplayHelper::ChangeBackground(GameHelper::bkg);
                break;
            case GameHelper::Mode::immunity:
                DisplayHelper::ChangeBackground(GameHelper::bkgCometMode);
            }

            // 1st delimiter
            glColor3f(0.3, 0.28, 0.4);

            glBegin(GL_POLYGON);
            glVertex2i(0, 0); // down left
            glVertex2i(800, 0); // down right
            glVertex2i(800, 40); // up right
            glVertex2i(0, 40); // up left
            glEnd();

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
            string scoremsg = "Score: " + to_string(GameHelper::score);
            RenderString(345.0f, 400.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"GAME OVER");
            RenderString(355.0f, 380.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)(scoremsg.c_str()));
        }

        if (contor == 1 && (r.GetY() != 275 && r.GetY() != 465 && r.GetY() != 655))
            r.SetY(r.GetY() + 1);
        else if (contor == -1 && (r.GetY() != 465 && r.GetY() != 275 && r.GetY() != 85))
            r.SetY(r.GetY() - 1);
        else
            contor = 0;

        // meteorites
        glPushMatrix();
        glTranslated(m.GetX(), m.GetY(), 0.0);

        glColor3f(0.4, 0.4, 0.4);

        glRecti(45, 15, 65, 38);
        glRecti(62, 38, 75, 45);

        glColor3f(0.56, 1., 1.);
        glRecti(50, 20, 58, 28);
        glPopMatrix();

        // comets
        glPushMatrix();
        glTranslatef(c.GetX(), c.GetY(), 0.0);
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
    switch (key)
    {
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

