#include <iostream>
#include "Game.h"
#include "Stage.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int bird;
int target;
float gravity;
int enemydis;

WINDOW * top;
WINDOW * btm;
int toprow, topx, topy;

vector<string> logo(17);
vector<string> sun(7);
vector<string> hs(5);
vector<string> ns(5);
vector<string> go(5);
vector<string> hits(5);
vector<string> won(5);
vector<string> text(12);

void Game::initLogo()
{
logo[0] = "  _______  _        _______  _______           ";
logo[1] = " (  ___  )( (    /|(  ____ \\(  ____ )|\\     /| ";
logo[2] = " | (   ) ||  \\  ( || (    \\/| (    )|( \\   / ) ";
logo[3] = " | (___) ||   \\ | || |      | (____)| \\ (_) /  ";
logo[4] = " |  ___  || (\\ \\) || | ____ |     __)  \\   /   ";
logo[5] = " | (   ) || | \\   || | \\_  )| (\\ (      ) (    ";
logo[6] = " | )   ( || )  \\  || (___) || ) \\ \\__   | |    ";
logo[7] = " |/     \\||/    )_)(_______)|/   \\__/   \\_/    ";
logo[8] = "                                               ";
logo[9] = "  ______  _________ _______  ______   _______  ";
logo[10] = " (  ___ \\ \\__   __/(  ____ )(  __  \\ (  ____ \\ ";
logo[11] = " | (   ) )   ) (   | (    )|| (  \\  )| (    \\/ ";
logo[12] = " | (__/ /    | |   | (____)|| |   ) || (_____  ";
logo[13] = " |  __ (     | |   |     __)| |   | |(_____  ) ";
logo[14] = " | (  \\ \\    | |   | (\\ (   | |   ) |      ) | ";
logo[15] = " | )___) )___) (___| ) \\ \\__| (__/  )/\\____) | ";
logo[16] = " |/ \\___/ \\_______/|/   \\__/(______/ \\_______) ";
}

void Game::initSun()
{
    sun[0] = "############################";
    sun[1] = "#########################";
    sun[2] = "##################";
    sun[3] = "##############";
    sun[4] = "#########";
    sun[5] = "####";
    sun[6] = "#";
}

void Game::headShot()
{
    hs[0] = " _   _ _____    _    ____    ____  _   _  ___ _____ ";
    hs[1] = "| | | | ____|  / \\  |  _ \\  / ___|| | | |/ _ \\_   _|";
    hs[2] = "| |_| |  _|   / _ \\ | | | | \\___ \\| |_| | | | || |  ";
    hs[3] = "|  _  | |___ / ___ \\| |_| |  ___) |  _  | |_| || | ";
    hs[4] = "|_| |_|_____/_/   \\_\\____/  |____/|_| |_|\\___/ |_| ";
}

void Game::noobShot()
{
    ns[0] = " _   _  ___   ___  ____    ____  _   _  ___ _____ ";
    ns[1] = "| \\ | |/ _ \\ / _ \\| __ )  / ___|| | | |/ _ \\_   _|";
    ns[2] = "|  \\| | | | | | | |  _ \\  \\___ \\| |_| | | | || |  ";
    ns[3] = "| |\\  | |_| | |_| | |_) |  ___) |  _  | |_| || | ";
    ns[4] = "|_| \\_|\\___/ \\___/|____/  |____/|_| |_|\\___/ |_| ";
}

void Game::gameOver(){
    go[0] = "  ____    _    __  __ _____    _____     _______ ____ ";
    go[1] = " / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\ ";
    go[2] = "| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) |";
    go[3] = "| |_| |/ ___ \\| |  | | |___  | |_| |\\ \V / | |___|  _ < ";
    go[4] = " \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\";
}

void Game::hit(){
    hits[0] = "   _  _     _   _  ___  _____     _  _   ";
    hits[1] = " _| || |_  | | | ||_ _||_   _|  _| || |_ ";
    hits[2] = "|_  ..  _| | |_| | | |   | |   |_  ..  _|";
    hits[3] = "|_      _| |  _  | | |   | |   |_      _|";
    hits[4] = "  |_||_|   |_| |_||___|  |_|     |_||_| ";
}

void Game::win(){
    won[0] = "__   __ ___   _   _  __        __ ___   _   _      ____  ";
    won[1] = "\\ \\ / // _ \\ | | | | \\ \\      / // _ \\ | \\ | |  _ |  _ \\ ";
    won[2] = " \\ \V /| | | || | | |  \\ \\ /\\ / /| | | ||  \\| | (_)| | | |";
    won[3] = "  | | | |_| || |_| |   \\ \V  \V / | |_| || |\\  |  _ | |_| |";
    won[4] = "  |_|  \\___/  \\___/     \\_/\\_/   \\___/ |_| \\_| (_)|____/ ";
}

void Game::helpText()
{
    text[0] = "Velkommen til Angry Birds - spillet som er en skamfull rip-off av det mindre kjente spillet Angry...Birds.";
    text[1] = "==========================================================================================================";
    text[2] = "1. Du velger først et brett/en planet";
    text[3] = "2. Deretter bruker du piltastene til å sette ønsket fart og vinkel på fuglen";
    text[4] = "3. Trykk 'a' for å slippe den løs";
    text[5] = "4. Se fuglens praktfulle ferd mot den stygge nerden";
    text[6] = "5. Om du treffer rett i knollen på nerden, dreper du han umiddelbart";
    text[7] = "   Treffer du nerden mister han 50 Health Points";
    text[8] = "   Bommer du...da har du bommet";
    text[9] = "- Du får maks tre forsøk på å drepe nerden -";
    text[10] = "";
    text[11] = "--Trykk en tast for å se den fine fuglen fly--";
}

int Game::randomNumber(int s)
{
    srand(time(0));
    return (rand()%s);
}

void Game::printScenery()
{
    box(top, 0, 0);
    box(btm, 0, 0);
    wattron(top, A_BOLD | COLOR_PAIR(4));
    //Printe ut sola...
    for(int i = 0; i < sun.size(); i++)
        mvwaddstr(top,i+1,1, sun[i].c_str());
    wattroff(top, A_BOLD | COLOR_PAIR(4));

    wattron(top, COLOR_PAIR(7));
    //...og litt gress og blomster
    for(int i = 1; i < topx-1; i++)
        mvwaddstr(top,topy-2,i, "|");

    for(int i = 1; i < topx-1; i+=8)
    {
        wattron(top, A_BOLD | COLOR_PAIR(8+(i%3)));
        mvwaddstr(top,topy-3,i, "*");
    }
    wattroff(top, COLOR_PAIR(4));
    wrefresh(top);
}

void Game::initScreen()
{
    // Start ncurses
    initscr();

    int row, col, topcol, btmrow, btmcol;

    //Ikke tegn på skjermen ved brukerinput
    noecho();
    // Slå av cursor
    curs_set(0);
    //Keypad og function keys
    keypad(stdscr, TRUE);
    start_color();

    //Kalkuler størrelse på topp- og bunnvindu (3/4 og 1/4 av høyde)
    getmaxyx(stdscr, row, col);

    toprow = (row*3)/4;
    btmrow = ((row*1)/4)-1;
    btmcol = ((row*3)/4)+1;

    top = newwin(toprow, col, 0, 0);
    btm = newwin(btmrow, col, btmcol, 0);

    topy = getmaxy(top);
    topx = getmaxx(top);

    refresh();

    //Opprette noen fargepar
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_GREEN);
    init_pair(9, COLOR_BLUE, COLOR_GREEN);
    init_pair(10, COLOR_YELLOW, COLOR_GREEN);

}

void Game::welcomeScr()
{
    headShot();
    noobShot();
    gameOver();
    hit();
    win();
    helpText();
    wattroff(top, A_BOLD);
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);

    int tmpspeed = 0;
    int tmpangle = 0;
    int ranstart = 0;

    int key;
    nodelay(stdscr, TRUE);
    mvwaddstr(btm,1,1, "Trykk en tast for å begynne! (om du har gjort det, må du vente til fuglen har landet)");
    mvwaddstr(btm,7,1, "Et spill utviklet av Ravi Agnihotri og Andreas Baaserud ifm. emnet \"Effektiv kode med C og C++\" våren 2013");
    wrefresh(btm);

    while(true) //oppstartsskjerm, printer ut en fugl som flyr fra tilfeldige startpunkter til bruker trykker på en tast
    {
        ranstart = randomNumber(100)+2;
        tmpspeed = randomNumber(15)+15;
        tmpangle = randomNumber(70)+10;

        Stage *stage = new Stage(randomNumber(2)+1, 1);
        vector<string> bird = stage->getBird();

        if(key = getch() == ERR)
        {
            stage->setUserInput((float) tmpspeed, (float) tmpangle, 1); //regner ut bane/trajectory
            int atgrass = ((topy-2)-bird.size()); //bakkenivå
            for(int i = 0; i < (int) stage->getVector_Y().size(); i++)
            {
                wclear(top);

                wattron(top, A_BOLD | COLOR_PAIR(1));
                //Printe ut logoen i midten
                for(int i = 0; i < logo.size(); i++)
                    mvwaddstr(top,i+9,(topx-55)/2, logo[i].c_str());
                wattroff(top, COLOR_PAIR(1));

                for(int j = 0; j < bird.size(); j++)
                    mvwaddstr(top, atgrass+stage->getVector_Y().at(i)+j, i+ranstart, bird[j].c_str());
                printScenery();
                wrefresh(top);
                usleep(60000);
            }
            delete stage;
        }
        else
        {
            delete stage;
            break;
        }
    }

    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);

    wattron(top, A_BOLD | COLOR_PAIR(1));
    //Printe ut logoen i midten
    for(int i = 0; i < logo.size(); i++)
        mvwaddstr(top,i+9,(topx-55)/2, logo[i].c_str());
    wattroff(top, COLOR_PAIR(1));

    printScenery();

    //Printe ut menyen
    mvwaddstr(btm,0,1, "Meny");
    mvwaddstr(btm,1,1, "1. Start spill");
    mvwaddstr(btm,2,1, "2. Hjelp");
    mvwaddstr(btm,3,1, "3. Avslutt");

    wrefresh(top);
    wrefresh(btm);

}

void Game::userInput()
{
    antMiss = 3;
    bool exit = false;

    while(true)
    {
        int in = getch();
        if(in == 49) //Nytt spill
        {
            createRandomEnemyDistance = randomNumber(65)+topx-65;
            wclear(btm);
            box(btm, 0, 0);
            mvwaddstr(btm,0,1, "Velg et brett:");
            mvwaddstr(btm,1,1, "1 - Jorden  (Vanlig gravitasjon)");
            mvwaddstr(btm,2,1, "2 - Månen  (Lav gravitasjon)");
            mvwaddstr(btm,3,1, "3 - Jupiter  (Høy gravitasjon)");
            mvwaddstr(btm,4,1, "4 - Avbryt");
            wrefresh(btm);

            while(true)
            {
                int in2 = getch();
                if(in2 == 49) //tallet 1
                {
                    stagePick = 1;
                    startStage(1);
                    welcomeScr();
                    break;
                }
                else if(in2 == 50) //tallet 2
                {
                    stagePick = 2;
                    startStage(2);
                    welcomeScr();
                    break;
                }
                else if(in2 == 51) //tallet 3
                {
                    stagePick = 3;
                    startStage(3);
                    welcomeScr();
                    break;
                }
                else if(in2 == 52) //tallet 4
                {
                    welcomeScr();
                    break;
                }
            }
        }
        else if(in == 50) //Hjelp
        {
            wclear(top);
            printScenery();
            box(top, 0, 0);

            wattron(top, A_BOLD | COLOR_PAIR(1));
            for(int i=0; i < text.size(); i++)
                mvwaddstr(top, i+10, 25, text[i].c_str());
            wrefresh(top);
            nodelay(stdscr, FALSE);
            getch();
            welcomeScr();
            break;

        }
        else if(in == 51) //Avslutt
        {
            exit = true;
            break;

        }
    }
    if(!exit) userInput();

}

void Game::startStage(int in)
{
//    createRandomEnemyDistance = randomNumber(65)+topx-65;
    Stage *stage = new Stage(in, createRandomEnemyDistance);
    vector<string> bird = stage->getBird();
    vector<string> enemy = stage->getEnemy();
    atgrass = ((topy-2)-bird.size()); //bakkenivå
    speed = 10;
    angle = 30;
    wclear(top);
    wclear(btm);
    box(top, 0, 0);
    box(btm, 0, 0);
    wrefresh(top);
    wrefresh(btm);

    //Printer ut fuglen og enemy før launch
    for(int i = 0; i < bird.size(); i++)
    {
        mvwaddstr(top, atgrass+i, 1, bird[i].c_str());
        mvwaddstr(top, atgrass+i, stage->getEnemyDistance()-6, enemy[i].c_str());
    }
    printScenery();

    mvwprintw(btm, 1, 1, "Fart: %d", speed);
    mvwprintw(btm, 2, 1, "Vinkel: %d", angle);
    mvwprintw(btm, 3, 1, "Nerdens HP: %d", stage->getEnemyHP());
    mvwprintw(btm, 4, 1, "Avstand til nerden: %d", stage->getEnemyDistance());
    wrefresh(top);
    wrefresh(btm);

    while(true)
    {
        int in = getch();
        if(in == KEY_UP) //Juster fart opp
        {
            mvwprintw(btm, 1, 1, "                ");
            if(speed < 200) speed++;
            mvwprintw(btm, 1, 1, "Fart: %d", speed);
            wrefresh(btm);
        }
        else if(in == KEY_DOWN) //...ned
        {
            mvwprintw(btm, 1, 1, "                ");
            if(speed > 1) speed--;
            mvwprintw(btm, 1, 1, "Fart: %d", speed);
            wrefresh(btm);
        }
        else if(in == KEY_RIGHT) //Juster vinkel opp
        {
            mvwprintw(btm, 2, 1, "                ");
            if(angle < 90) angle++;
            mvwprintw(btm, 2, 1, "Vinkel: %d", angle);
            wrefresh(btm);
        }
        else if(in == KEY_LEFT) //...ned
        {
            mvwprintw(btm, 2, 1, "                ");
            if(angle > 1) angle--;
            mvwprintw(btm, 2, 1, "Vinkel: %d", angle);
            wrefresh(btm);
        }
        else if(in == 97){ //Liftoff!
            wclear(top);
            printScenery();
            mvwprintw(btm, 3, 1, "                ");
            mvwprintw(btm, 3, 1, "Nerdens HP: %d", stage->getEnemyHP());
            stage->setUserInput((float)speed, (float)angle, 1);
            for(int i = 0; i < (int)stage->getVector_Y().size(); i++)
            {
                wclear(top);
                printScenery();
                for(int k = 0; k < bird.size(); k++)
                {
                    mvwaddstr(top, atgrass+stage->getVector_Y().at(i)+k, i+2, bird[k].c_str());
                    mvwaddstr(top, atgrass+k, stage->getEnemyDistance()-6, enemy[k].c_str());
                }
                wrefresh(top);
                wrefresh(btm);
                speed > 30 ? usleep(100000 * (1+((speed-30))/100)) : usleep(100000); //litt rar?
                //if( i!= stage->getVector_Y().size()-1) wclear(top);
            }

            if(stage->enemyHit()){
                if(stage->gameOver()){
                    wclear(top);
                    printScenery();
                    mvwprintw(btm, 3, 1, "                ");
                    mvwprintw(btm, 3, 1, "Nerdens HP: %d", stage->getEnemyHP());
                    if(stage->getHeadshot()){
                        //print ut headshotlogo
                        for(int j = 0; j < hs.size(); j++)
                            mvwaddstr(top,j+9,(topx-55)/2, hs[j].c_str());
                    }
                    else{
                        //print ut winLogo
                        wclear(top);
                        printScenery();
                        for(int j = 0; j < won.size(); j++)
                            mvwaddstr(top,j+9,(topx-55)/2, won[j].c_str());
                        for(int j = 0; j < enemy.size(); j++)
                        {
                            if(j == 3) enemy[3] = "<| -DØD- |>";
                            mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                        }
                        mvwprintw(btm, 3, 1, "                ");
                        mvwprintw(btm, 3, 1, "Nerdens HP: %d", stage->getEnemyHP());
                    }
                    wrefresh(top);
                    wrefresh(btm);
                    stage->resetEnemyHP();
                    delete stage;
                    finish();
                }
                else{
                    wclear(top);
                    printScenery();

                    mvwprintw(btm, 3, 1, "                ");
                    mvwprintw(btm, 3, 1, "Nerdens HP: %d", stage->getEnemyHP());
                    //printer ut hit logo
                    for(int j = 0; j < hits.size(); j++)
                        mvwaddstr(top,j+9,(topx-55)/2, hits[j].c_str());
                    for(int j = 0; j < enemy.size(); j++)
                    {
                        if(j == 3) enemy[3] = "<| -50HP |>";
                        mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                    }
                    wrefresh(top);
                    wrefresh(btm);
                    sleep(2);
                    delete stage;
                    startStage(stagePick);
                }
            }
            else if(!stage->enemyHit()){
                antMiss--;
                if(antMiss != 0){
                    wclear(top);
                    printScenery();
                    for(int j = 0; j < ns.size(); j++)
                        mvwaddstr(top,j+9,(topx-55)/2, ns[j].c_str());
                    for(int j = 0; j < enemy.size(); j++)
                    {
                        if(j == 3) enemy[3] = "<| -MISS |>";
                        mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                    }
                    wrefresh(top);
                    sleep(2);
                    delete stage;
                    startStage(stagePick);
                }
                else if(antMiss == 0){
                    //GAME OVER logo
                    wclear(top);
                    printScenery();
                    mvwprintw(btm, 3, 1, "                ");
                    mvwprintw(btm, 3, 1, "Nerdens HP: %d", stage->getEnemyHP());
                    for(int j = 0; j < go.size(); j++)
                        mvwaddstr(top,j+9,(topx-55)/2, go[j].c_str());
                    for(int j = 0; j < enemy.size(); j++)
                    {
                        if(j == 3) enemy[3] = "<| -HAHA! |>";
                        mvwaddstr(top, atgrass+j, stage->getEnemyDistance()-6, enemy[j].c_str());
                    }
                    wrefresh(top);
                    wrefresh(btm);
                    stage->resetEnemyHP();
                    delete stage;
                    finish();
                }
            }
        }
    }
    delete stage;
}

void Game::finish()
{
    while( enemydis < topx-15 )
        enemydis = randomNumber(65)+topx-65;
    wclear(btm);
    box(btm, 0, 0);
    //Printe ut menyen
    mvwaddstr(btm,0,1, "Meny");
    mvwaddstr(btm,1,1, "1. Start spill");
    mvwaddstr(btm,2,1, "2. Hjelp");
    mvwaddstr(btm,3,1, "3. Avslutt");
    wrefresh(btm);
    userInput();
}

Game::Game()
{
    initScreen();
    initSun();
    initLogo();
    attron(COLOR_PAIR(6));

    box(top, 0, 0);
    box(btm, 0, 0);

    welcomeScr();
    while( enemydis < topx-15 )
        enemydis = randomNumber(65)+topx-65;
    wrefresh(top);
    wrefresh(btm);

    userInput();

    delwin(top);
    delwin(btm);

    endwin();
}

Game::~Game()
{
    //dtor
}
