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

    enum class currentSound {
        intro,
        play,
        playComet,
        lose
    };

    static void IntroMusic();
    static void PlayMusic();
    static void CometMusic();
    static void LoseMusic();
    static void StopMusic();
    static void SoundConsole();
    static void ChangeBackground(Color c);

    static currentSound cSound;

private:
    DisplayHelper() = delete;

};



class Asteroid : public Object
{
public:
    Asteroid(GLdouble x, GLdouble y, GLdouble xdim, GLdouble ydim);
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
    bool OnAsteroidCrash(Asteroid& m);
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

    static bool CheckCollision(Rocket ob1, Asteroid ob2);
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

