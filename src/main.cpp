#include <SDL.h>
//#include <SDL_ttf.h>
#include <cstdlib>
#include <SDL_mixer.h>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

SDL_Surface * ekran = NULL;
SDL_Surface * player = NULL;
SDL_Surface * bg = NULL;
SDL_Surface * pocisk = NULL;
SDL_Surface * epocisk = NULL;
SDL_Surface * enemya = NULL;
SDL_Surface * enemyb = NULL;
SDL_Surface * enemyc = NULL;
SDL_Surface * hp = NULL;
SDL_Surface * leveltext = NULL;
SDL_Surface * gameover = NULL;
SDL_Surface * boom = NULL;
SDL_Surface * zero  = NULL;
SDL_Surface * one  = NULL;
SDL_Surface * two  = NULL;
SDL_Surface *  three = NULL;
SDL_Surface *  four = NULL;
SDL_Surface * five  = NULL;
SDL_Surface *  six = NULL;
SDL_Surface * seven  = NULL;
SDL_Surface * eight  = NULL;
SDL_Surface * nine  = NULL;
Mix_Chunk * shot;


SDL_Event zdarzenie;
//SDL_Rect LudekDestination;
Uint8 * keystate = SDL_GetKeyState( NULL );
bool wyjscie = false;
int timer=0;
int cooldown=0;
bool zapiszwynik = true;

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
class POCISKI{
    public:
    POCISKI(){
        x=1000;
        y=1000;
    }

 //   virtual void ruch(){}

    int x;
    int y;
protected:
    void wlewo(){
        x=x-5;
    }
    void wprawo(){
        x=x+5;
    }
};

class PAMMO : public POCISKI{
    public:
        PAMMO()
        {
            x=2000;
            y=2000;
        }
};

class EAMMO : public POCISKI{
    public:
        EAMMO()
        {
            x=-2000;
            y=-2000;
        }
};

class NPC{
    public:
    int attackspeed;
    int oldx;
    int oldy;
    int x;
    int y;
    int health;
    int attackdamage;
    protected:
    virtual void attack(){}
    virtual void movement(){}
    int movementspeed;

};

class PLAYER : public NPC{
    public:
    PLAYER(){
        level=1;
        health=100;
        attackdamage=5;
        attackspeed=15;
        movementspeed=4;
        licznikk=0;
        wynik=0;
        x=310;
        y=370;
    }
    int licznikk;

   // void movement(){};
    void move(){
        oldx=x;
        oldy=y;
       if( keystate[ SDLK_RIGHT ] )
        {
            x=x+movementspeed;
        }

        if( keystate[ SDLK_LEFT ] )
        {
            x=x-movementspeed;
        }

        if( keystate[ SDLK_UP ] )
        {
            y=y-movementspeed;
        }

        if( keystate[ SDLK_DOWN ] )
        {
            y=y+movementspeed;
        }

        if(x<20 || x>1366-25)
        {
            x=oldx;
        }
        if(y<15 || y>768-15)
        {
            y=oldy;
        }
    }
    void addexperience(int a)
    {
        experience=experience+a;
    }

    void experiencecheck(){
        if(10+level*10 <= experience)
        {
            experience=0;
            levelup();
        }
    }

    int getlevel(){return level;}
    int wynik;
    private:
    int level;
    int experience;

private:
        void levelup()
        {
            if(level>=20)
            {
                //nic nie rob
            }
            else
            {
                level++;
                health=100;
                //attackdamage++;
                if(level%5==0)
                {
                    movementspeed++;
                }
                if(level%2==1)
                {
                    attackspeed--;
                }
                //health = 100+getlevel()*5;
                experience=0;
                wynik=wynik+10;
            }
        }
};

class ENEMY : public NPC{
    public:
    ENEMY()
    {
        randy=300;
        randx=1400;
        x=1400;
        y=300;
    }

    virtual void ReHealth(){};
    virtual void Display(){};
    void movement()
    {
        if(abs(randx-x)<=movementspeed)
        {
            randx = ( rand() % 1366-20 ) + 20;
        }
        if(abs(randy-y)<=movementspeed)
        {
            randy = ( rand() % 768-15 ) + 15;
        }

        if(randx<x)
        {
            x=x-movementspeed;
        }
        if(randx>x)
        {
            x=x+movementspeed;
        }
        if(randy>y)
        {
            y=y+movementspeed;
        }
        if(randy<y)
        {
            y=y-movementspeed;
        }


      /*  if(x<20)
        {
            x=oldx;
        }
        if(y<15 || y>768-15)
        {
            y=oldy;
        }
        */

        if(oldx==x)
        {
            randx = ( rand() % 1366-20 ) + 20;
        }
        if(oldy==y)
        {
            randy = ( rand() % 768-15 ) + 15;
        }
        oldx=x;
        oldy=y;
    }
    void setrandx(int a)
    {
        randx=a;
    }
private:
    int randy;
    int randx;
};

class LIGHT : public ENEMY{
    public:
    LIGHT()
    {
        movementspeed = 3;
        health = 20;
        attackdamage = 5;
    }

    void ReHealth()
    {
        health=20;
    }
    void Display()
    {
        SDL_SetColorKey( enemya, SDL_SRCCOLORKEY, SDL_MapRGB(enemya->format,255,0,255));
        DrawSurface(ekran,enemya,x,y);
    }
};

class MEDIUM : public ENEMY{
    public:
    MEDIUM()
    {
        movementspeed = 2;
        health = 35;
        attackdamage = 8;
    }
    void ReHealth()
    {
        health = 35;
    }
    void Display()
    {
        SDL_SetColorKey( enemyb, SDL_SRCCOLORKEY, SDL_MapRGB(enemyb->format,255,0,255));
        DrawSurface(ekran,enemyb,x,y);
    }
};

class HEAVY : public ENEMY{
    public:
    HEAVY()
    {
        movementspeed = 1;
        health = 55;
        attackdamage = 12;
    }
    void ReHealth()
    {
        health = 55;
    }
    void Display()
    {
        SDL_SetColorKey( enemyc, SDL_SRCCOLORKEY, SDL_MapRGB(enemyc->format,255,0,255));
        DrawSurface(ekran,enemyc,x,y);
    }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int Distance(int x1,int x2,int y1,int y2);
void TextDisplay();
void eammomovement(EAMMO *eammo);
void ammomovement(PAMMO *pammo);
void wyswietl(PLAYER *player1);
void ewyswietl(ENEMY *player1);
void game();
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


int main( int argc, char * args[] )
{
    srand( time( NULL ) );
    game();
    return 0;
}




//@@@@@@@@@@@@@@@@@@@@@@@@

void game()
{
    ofstream plik("wynik.txt", ios::app);
    //plik.open("wynik.txt");
    time_t czas;
    time( & czas );
    plik<<"Rozpoczeto gre: "<<ctime( & czas );
    plik.close();
    //SDL_Init(SDL_INIT_AUDIO);
    //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    bool koniecgry=false;
    //SDL_BlitSurface ( bg, NULL, ekran, NULL);
    //TTF_Init();
  //  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    //Initialize SDL_mixer
//    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    //SDL_WM_SetCaption( "Monitor Music", NULL );
    int elos;
    int los;
    PLAYER player1;
    ENEMY *enemy[20];

    for(int i=0;i<20;i++) //rozlosowanie przeciwnikow
    {
        elos = ( rand() % 3 ) + 1;
        switch(elos)
        {
            case 1: enemy[i] = new LIGHT;
            break;
            case 2: enemy[i] = new MEDIUM;
            break;
            case 3: enemy[i] = new HEAVY;
            break;
        }
    }
    PAMMO pammo[20];
    EAMMO eammo[20];

    ekran = SDL_SetVideoMode( 1366, 768, 32, SDL_FULLSCREEN );
    player = SDL_LoadBMP( "player.bmp" );
    bg = SDL_LoadBMP ( "bg.bmp" );
    pocisk = SDL_LoadBMP ( "pocisk.bmp" );
    epocisk = SDL_LoadBMP ( "epocisk.bmp" );
    enemya = SDL_LoadBMP ("enemya.bmp");
    enemyb = SDL_LoadBMP ("enemyb.bmp");
    enemyc = SDL_LoadBMP ("enemyc.bmp");
    hp = SDL_LoadBMP ("hp.bmp");
    leveltext = SDL_LoadBMP ("level.bmp");
    gameover = SDL_LoadBMP ("gameover.bmp");
    boom = SDL_LoadBMP ("boom.bmp");
    zero = SDL_LoadBMP ("0.bmp");
     one = SDL_LoadBMP ("1.bmp");
      two = SDL_LoadBMP ("2.bmp");
       three = SDL_LoadBMP ("3.bmp");
        four = SDL_LoadBMP ("4.bmp");
         five = SDL_LoadBMP ("5.bmp");
          six = SDL_LoadBMP ("6.bmp");
           seven = SDL_LoadBMP ("7.bmp");
            eight = SDL_LoadBMP ("8.bmp");
             nine = SDL_LoadBMP ("9.bmp");
//    shot = Mix_LoadWAV("shot.wav");

    while( !wyjscie )
    {
        SDL_BlitSurface ( bg, NULL, ekran, NULL);

//        SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "This is mytext.",foregroundColor, backgroundColor);


        //obsluga kolizji
        for(int i=0;i<20;i++)
        {
            for(int q=0;q<player1.getlevel();q++)
            {
                if(Distance(enemy[q]->x,pammo[i].x,enemy[q]->y,pammo[i].y)<20)
                {
                    SDL_SetColorKey( boom, SDL_SRCCOLORKEY, SDL_MapRGB(player->format,255,0,255));
                    DrawSurface(ekran,boom,enemy[q]->x,enemy[q]->y);
                    enemy[q]->health=enemy[q]->health-player1.attackdamage;
                    pammo[i].x=2000;
                    SDL_Flip( ekran );
                }
            }
            if(Distance(player1.x,eammo[i].x,player1.y,eammo[i].y)<20)
            {
                SDL_SetColorKey( boom, SDL_SRCCOLORKEY, SDL_MapRGB(player->format,255,0,255));
                DrawSurface(ekran,boom,player1.x,player1.y);
                player1.health=player1.health-enemy[i]->attackdamage;
                eammo[i].x=0;
                SDL_Flip( ekran );
            }
            if(player1.health<=0)
            {
                koniecgry=true;
            }
            for(int q=0;q<player1.getlevel();q++)
            {
                if(enemy[q]->health<=0)
                {
                    enemy[q]->ReHealth();
                    enemy[q]->x=1300;
                    enemy[q]->oldx=1300;
                    //enemy[q]->setrandx(1300);
                    player1.addexperience(10);
                    player1.experiencecheck();
                    player1.wynik=player1.wynik+1;
                }
            }

            if(Distance(player1.x,enemy[i]->x,player1.y,enemy[i]->y)<20)
            {
                koniecgry=true;
                player1.health=0;
            }
        }

        while( SDL_PollEvent( & zdarzenie ) )
        {
            if( zdarzenie.type == SDL_QUIT )
            {
                wyjscie = true;
            }
        }

        if(koniecgry==false)
        {
            player1.move();
            if( keystate[ SDLK_SPACE] )
            {
                if((timer-cooldown)>player1.attackspeed) //cooldown na strzal
                {

                    if(player1.licznikk>=20)
                    {
                        player1.licznikk=0;
                    }
                    //Mix_PlayChannel(-1,shot,0);
                    pammo[player1.licznikk].x=player1.x;
                    pammo[player1.licznikk].y=player1.y;
                    cooldown=timer;
                    player1.licznikk=player1.licznikk+1;
                }
            }
            /*if( keystate[ SDLK_0 ] )
            {
                player1.addexperience(100);
                player1.experiencecheck();
            }*/ //kody

        }
        else
        {
            SDL_SetColorKey( gameover, SDL_SRCCOLORKEY, SDL_MapRGB(gameover->format,255,0,255));
            DrawSurface(ekran,gameover,1390/2,766/2);
        }

        if( keystate[ SDLK_ESCAPE] )
        {

            if(zapiszwynik==true)
            {
                wyjscie=true;
                ofstream plik("wynik.txt", ios::app);
                //plik.open("wynik.txt");
                time_t czas;
                time( & czas );
                plik<<"Zdobyte punkty: "<<player1.wynik<<endl<<"Wylaczono gre: "<<ctime( & czas )<<endl<<endl;
                plik.close();
            }
            wyjscie=true;
        }


        for(int i=0;i<player1.getlevel();i++) // obsluga przeciwnikow
        {
            enemy[i]->movement();
            enemy[i]->Display();
            //ewyswietl(enemy[i]);
        }

        for(int i=0;i<player1.getlevel();i++)
        {
            if(eammo[i].x<=0)
            {
                los = ( rand() % 100 ) + 0;
                if(los==5)
                {
                    eammo[i].x=enemy[i]->x;
                    eammo[i].y=enemy[i]->y;
                }

            }
            else
            {
                eammomovement(&eammo[i]);
            }
        }


        wyswietl(&player1);
        SDL_SetColorKey( zero, SDL_SRCCOLORKEY, SDL_MapRGB(zero->format,255,0,255));
        SDL_SetColorKey( one, SDL_SRCCOLORKEY, SDL_MapRGB(one->format,255,0,255));
        SDL_SetColorKey( two, SDL_SRCCOLORKEY, SDL_MapRGB(two->format,255,0,255));
        SDL_SetColorKey( three, SDL_SRCCOLORKEY, SDL_MapRGB(three->format,255,0,255));
        SDL_SetColorKey( four, SDL_SRCCOLORKEY, SDL_MapRGB(four->format,255,0,255));
        SDL_SetColorKey( five, SDL_SRCCOLORKEY, SDL_MapRGB(five->format,255,0,255));
        SDL_SetColorKey( six, SDL_SRCCOLORKEY, SDL_MapRGB(six->format,255,0,255));
        SDL_SetColorKey( seven, SDL_SRCCOLORKEY, SDL_MapRGB(seven->format,255,0,255));
        SDL_SetColorKey( eight, SDL_SRCCOLORKEY, SDL_MapRGB(eight->format,255,0,255));
        SDL_SetColorKey( nine, SDL_SRCCOLORKEY, SDL_MapRGB(nine->format,255,0,255));
        switch(player1.getlevel())
        {
        case 1: DrawSurface(ekran,one,100,35); break;
        case 2: DrawSurface(ekran,two,100,35); break;
        case 3: DrawSurface(ekran,three,100,35); break;
        case 4: DrawSurface(ekran,four,100,35); break;
        case 5: DrawSurface(ekran,five,100,35); break;
        case 6: DrawSurface(ekran,six,100,35); break;
        case 7: DrawSurface(ekran,seven,100,35); break;
        case 8: DrawSurface(ekran,eight,100,35); break;
        case 9: DrawSurface(ekran,nine,100,35); break;
        case 10: DrawSurface(ekran,one,100,35); DrawSurface(ekran,zero,115,35); break;
        case 11: DrawSurface(ekran,one,100,35); DrawSurface(ekran,one,115,35); break;
        case 12: DrawSurface(ekran,one,100,35); DrawSurface(ekran,two,115,35); break;
        case 13: DrawSurface(ekran,one,100,35); DrawSurface(ekran,three,115,35); break;
        case 14: DrawSurface(ekran,one,100,35); DrawSurface(ekran,four,115,35); break;
        case 15: DrawSurface(ekran,one,100,35); DrawSurface(ekran,five,115,35); break;
        case 16: DrawSurface(ekran,one,100,35); DrawSurface(ekran,six,115,35); break;
        case 17: DrawSurface(ekran,one,100,35); DrawSurface(ekran,seven,115,35); break;
        case 18: DrawSurface(ekran,one,100,35); DrawSurface(ekran,eight,115,35); break;
        case 19: DrawSurface(ekran,one,100,35); DrawSurface(ekran,nine,115,35); break;
        case 20: DrawSurface(ekran,two,100,35); DrawSurface(ekran,zero,115,35); break;

        }
        if(player1.health==100)
        {
            DrawSurface(ekran,one,100,65);
            DrawSurface(ekran,zero,115,65);
            DrawSurface(ekran,zero,130,65);
        }
        else if(player1.health >=90)
        {
            DrawSurface(ekran,nine,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=80)
        {
            DrawSurface(ekran,eight,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=70)
        {
            DrawSurface(ekran,seven,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=60)
        {
            DrawSurface(ekran,six,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=50)
        {
            DrawSurface(ekran,five,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=40)
        {
            DrawSurface(ekran,four,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=30)
        {
            DrawSurface(ekran,three,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=20)
        {
            DrawSurface(ekran,two,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>=10)
        {
            DrawSurface(ekran,one,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else if(player1.health>0)
        {
            //DrawSurface(ekran,zero,100,65);
            if(player1.health%10==0)
            DrawSurface(ekran,zero,115,65);
            if(player1.health%10==1)
            DrawSurface(ekran,one,115,65);
            if(player1.health%10==2)
            DrawSurface(ekran,two,115,65);
            if(player1.health%10==3)
            DrawSurface(ekran,three,115,65);
            if(player1.health%10==4)
            DrawSurface(ekran,four,115,65);
            if(player1.health%10==5)
            DrawSurface(ekran,five,115,65);
            if(player1.health%10==6)
            DrawSurface(ekran,six,115,65);
            if(player1.health%10==7)
            DrawSurface(ekran,seven,115,65);
            if(player1.health%10==8)
            DrawSurface(ekran,eight,115,65);
            if(player1.health%10==9)
            DrawSurface(ekran,nine,115,65);
        }
        else
        {
            DrawSurface(ekran,zero,100,65);
        }


       for(int i=0;i<20;i++) //wyswietlanie pociskow
       {
               ammomovement(&pammo[i]);
       }

       if(zapiszwynik == true && player1.health <= 0)
       {
            ofstream plik("wynik.txt", ios::app);
            //plik.open("wynik.txt");
            time_t czas;
            time( & czas );
            plik<<"Zdobyte punkty: "<<player1.wynik<<endl<<"Zakonczono gre: "<<ctime( & czas )<<endl<<endl;
            plik.close();
            zapiszwynik = false;
       }

        TextDisplay();
        SDL_Flip( ekran );
        timer++;
        void SDL_Delay(Uint32 ms);

    }
    SDL_FreeSurface(enemyb);
    SDL_FreeSurface(pocisk);
    SDL_FreeSurface( player );
    SDL_FreeSurface(bg);
    SDL_Quit();
}


void TextDisplay()
{
    SDL_SetColorKey( leveltext, SDL_SRCCOLORKEY, SDL_MapRGB(leveltext->format,255,0,255));
    SDL_SetColorKey( hp, SDL_SRCCOLORKEY, SDL_MapRGB(hp->format,255,0,255));
    DrawSurface(ekran,leveltext,50,30);
    DrawSurface(ekran,hp,50,60);
}

void wyswietl(PLAYER *player1)
{
    SDL_SetColorKey( player, SDL_SRCCOLORKEY, SDL_MapRGB(player->format,255,0,255));
    //SDL_BlitSurface ( bg, NULL, ekran, NULL);
    DrawSurface(ekran,player,player1->x,player1->y);
}

void ewyswietl(ENEMY *en)
{
    SDL_SetColorKey( enemyb, SDL_SRCCOLORKEY, SDL_MapRGB(enemyb->format,255,0,255));
    //SDL_BlitSurface ( bg, NULL, ekran, NULL);
    DrawSurface(ekran,enemyb,en->x,en->y);
}


void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
   SDL_Rect dest;
   dest.x = x - sprite->w / 2;
   dest.y = y - sprite->h / 2;
   dest.w = sprite->w;
   dest.h = sprite->h;
   SDL_BlitSurface(sprite, NULL, screen, &dest);
   //SDL_Flip( ekran );
   };

void ammomovement(PAMMO *pammo)
{
    pammo->x=pammo->x+10;
    DrawSurface(ekran,pocisk,pammo->x,pammo->y);


}

void eammomovement(EAMMO *eammo)
{
    eammo->x=eammo->x-10;
    DrawSurface(ekran,epocisk,eammo->x,eammo->y);


}


int Distance(int x1,int x2,int y1,int y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

