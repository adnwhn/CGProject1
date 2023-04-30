#include <iostream>
#include <windows.h>
#include <GL/freeglut.h>

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
    static bool CheckCollision(Rocket ob1, Meteorite ob2);
    static int score;
    static int startGame;
    static void SetStartGame(int sg);
    static int GetStartGame();

private:
};


