#ifndef GAME_H
#define GAME_H


class Game
{
    private:
        void initLogo();
        void initSun();
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
};

#endif // GAME_H
