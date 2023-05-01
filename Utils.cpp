#include <iostream>
#include <windows.h>
#include <GL/freeglut.h>

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
    static char* sound_file;
    static void StartMusic();
    static void StopMusic();
    static void ChangeBackground(Color c);

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
    Meteorite(GLdouble x, GLdouble y, GLdouble xdim, GLdouble ydim);
private:
    GLdouble xDim;
    GLdouble yDim;

};

class Comet : public Object
{
public:
    Comet(GLdouble x, GLdouble y);

private:
};




class Rocket : public Object
{
public:
    Rocket(GLdouble x, GLdouble y, GLdouble xdim, GLdouble ydim);
    bool OnMeteoriteCrash(Meteorite& m);
private:
    GLdouble xDim;
    GLdouble yDim;
};



class GameHelper
{
public:

    enum class Mode
    {
        normal,
        immunity
    };

    static bool CheckCollision(Rocket ob1, Meteorite ob2);
    static bool CheckCollision(Rocket ob1, Comet ob2);
    static void SetStartGame(int sg);
    static int GetStartGame();

    static int score;
    static int startGame;
    static bool immunity;
    static int immunityc;
    static Mode mode;
    static Color bkg;
    static Color bkgCometMode;


private:
};