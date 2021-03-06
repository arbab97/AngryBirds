#ifndef GAME_H
#define GAME_H


class Game
{
    private:
        void initLogo();
        void initSun();
        void headShot();
        void noobShot();
        void gameOver();
        void hit();
        void win();
        void helpText();
        int randomNumber(int s);
        void printScenery();
        void initScreen();
        void welcomeScr();
        void userInput();
        void startStage(int i);
        void finish();
        int stagePick;
    public:
        Game();
        virtual ~Game();
        int antMiss;
        int atgrass;
        int speed;
        int angle;
        int createRandomEnemyDistance;
};

#endif // GAME_H
