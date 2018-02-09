#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <time.h>
#include "Happyfpscap.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>

static const int Width=900;///900
static const int Height=600;///600
int VWidth = 900, VHeight = 600;
int Running=1;
float ScaleX, ScaleY;
const int TileSize=60;
int MapArray[60][20];
SDL_Renderer *Renderer = NULL;
SDL_Window *Window = NULL;

short X=450,Y=300, MapX, MapY, MapFlash, MapOfX=0, MapOfY=0;
char Falling=1;
short MouseX, MouseY;
short SpdX,SpdY;
int Speed=7, JumpPower=20, Damage=25;
int Health=100, MaxHealth=100, Sheild=1, MaxSheild=1;
int Ammo=100, MaxAmmo=100, Charge=0, MaxCharge=50;
short DmgMultiply=100, FireMultiply=100;
short OldSpeed=7;
short SheildRecharge;
char HatId=0;
int CanSwim=0;

int First, Timer;
int ProAim=0;
char Q=0;
int OffsetX, OffsetY;
short OrginX=20, OrginY=20;
short RoomAmount=1;
short PlayerWeaponId=6;
int MainAdder;
char Mouse1, Mouse2;

int W,S,AAAAA,D,A,S2;
SDL_Texture *Images[75], *PlayerImages[6], *ItemImages[40], *TextImg[200], *HatImgs[10];

typedef struct RoomType1{
short Id;
short X;
short Y;

char Type[15];
short Finished;
short BigRoom;
short Height;
short Width;
short Area;
short Direct;
short RoomSpd;
short IsItemRoom;

short ItemId;
short DropId;
short DropX;
short DropY;
short Pair;
}Room;

typedef struct helps{
int X;
int Y;
}Point;

typedef struct Bosses{
int X;
int Y;
int SpdX;
int SpdY;
char Id;
char Alive;
int Falling;
int Health;
int MaxHealth;
int Size;
short AttackTimer;
short Timer;
short Counter;
short Walking;
short Type;
}Boss;

Boss Boss1;

typedef struct Enemy1{
    int X;
    int Y;
    int SpdX;
    int SpdY;
    char MaxSpeed;
    char Alive;
    int Falling;
    int Type;
    float Spawning;
    short Walking;
    short Counter;
    short Health;
    char Special;
    short AttackTimer;
    char Sleeping;
    short Damage;
    char Friend;
    short Number;
    short Number2;
    short Number3;
}NormalEnemy;

NormalEnemy Enemys[30];

typedef struct playerBuff{
short Hp;
short Damage;
short Speed;
short Sheild;
short ImageId;
char Name[20];
int *Special;
short SpecialMod;
char IsUnlocked;
}Hat;

Hat hats[10];

short RoomPos[120][120];
Room Rooms[350];
char knownRooms[120][120];
Room RoomPair[120][120];
short RoomCount,ItemRoomCount;
char Area=0;

short FireRate=10;
int Cooldown;
int RapidFire=0;

/// specials ///

char ItemRandom=15;
char MapLevel=1, MapZoom=2;
char JumpLevel=0;
short BulletSpeed=20;
char Weapon=0, ChargeWeapon=0;
char SaftyPlat=0;
int ChargeAmount=1;
short BulletImage=36;
char Accuricy=0;

int UsableId=0, SecondaryId;

///  other thing ///
char OnMenu=0;
int OneHit=0;
short LandEffect=0;
char LastArea=0;
char Mode=0;
char ZAwaken=0;
short Seed=0;

char Corrupted=0,CorrupAmount=0;
char UltraHard=0;
char BossCount=0;

char TempItemName[20];
short ItemTitle=0;
short Red=255, Blue, Green;
short BRed=50, BBlue=250, BGreen=50;
short Menu;
short Volume=0;
char HasSaved=0;
char Scene=0;
SDL_Texture *IntroImg;

/// -==- server -==- ///

TCPsocket server;
TCPsocket client;
char IsServer=0;
short ClieX, ClieY;
short CRoomId=0;
char PlayerAnim=0;
char PlayerAnim2=0;
char LastShot=0;

void DamagePlayer(float Damage){
    if(MaxSheild!=1){
        if(Sheild>0){
            if(Sheild>=Damage){
                Sheild-=Damage;
            }else{
                Sheild=0;
            }
        }else{
            Health-=Damage;
        }
    }else{
        Health-=Damage;
    }
}

#include "Sound.h"
#include "Image.h"

#include "Bullets.h"
#include "drops.h"
#include "items.h"
#include "Enemy1.h"

#include "Boss1.h"

#include "FloorMap.h"
#include "DrawFunctions.h"
#include "cutscene.h"

/// ////////////////////////////////////Player Stuff///////////////////////////////////////
#include "multiplayer.h"

#include "menu.h"

#include "PlayerStuff.h"
#include "Usable.h"

#include "Map.h"

/// ////////////////////////////////////Main Stuff///////////////////////////////////////

int main(int argc,char **argv){
    srand(time(NULL));

    /// /// /// ///// /// /// ///

    ScaleX = (float)VWidth/900;
    ScaleY = (float)VHeight/600;

    /// / // / /// / // / ///

    loadItems();
    LoadSecondarys();
    LoadMenu(0);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLNet_Init();

    Load();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VWidth+400*ScaleX, VHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED /*| SDL_WINDOW_BORDERLESS*/);//SDL_WINDOW_FULLSCREEN_DESKTOP
    Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface *Surface = IMG_Load("Images/gameIcon.png");
    SDL_SetWindowIcon(Window, Surface);

    loadImages();
    loadPlayerImages();
    LoadItemImages();
    LoadSounds();
    LoadAbilitys();

    LoadText();
    LoadHats();
    LoadHatImg();

    Mix_PlayChannel(1,Music[0],-1);
    Mix_Volume(1,Volume);
    Mix_Volume(0,Volume);
    int O;
    for(O=2; O<20; O++){
        Mix_Volume(O,Volume);
    }

    Corrupted=UltraHard;

    for(I=0; I<270; I++){
        Rooms[I].Id=0;
        Rooms[I].X=0;
        Rooms[I].Y=0;

        strcpy((char*)&Rooms[I].Type,"a/1234/1.txt");
        Rooms[I].Finished=0;
        Rooms[I].BigRoom=0;
        Rooms[I].Height=Height;
        Rooms[I].Width=Width;
        Rooms[I].Area=0;
        Rooms[I].Direct=0;
        Rooms[I].RoomSpd=0;
        Rooms[I].IsItemRoom=0;

        Rooms[I].ItemId=0;
        Rooms[I].DropId=0;
        Rooms[I].DropX=0;
        Rooms[I].DropY=0;
        Rooms[I].Pair=0;
    }

    Running = 1;
    SDL_Event Event;
    while(Running){
            FpsCapStart();
        while(SDL_PollEvent(&Event)){//answers.yahoo.com/question/index?qid=20110309151642AA3VCD1
            switch (Event.type){
                case SDL_QUIT:
                    Running = 0;
                break;
                case SDL_KEYDOWN:
                    if(Menu==0&&OnMenu==0&&Scene==115){
                        ButtonActivater(1);
                    }

                    switch (Event.key.keysym.sym){
                    case SDLK_w:
                        W=1;
                    break;
                    case SDLK_s:
                        S=1;
                        S2=1;
                    break;
                    case SDLK_a:
                        AAAAA=1;
                        Direction=-1;
                    break;
                    case SDLK_d:
                        D=1;
                        Direction=1;
                    break;
                    case SDLK_SPACE:
                        if(MapArray[(X+TileSize/2)/TileSize][(Y+TileSize/2)/TileSize]==5){
                            if(CanSwim==1&&Health>0){
                                Jump((float)JumpPower/4*5);
                            }else if(CanSwim==0&&Health>0&&Falling==0){
                                Jump(JumpPower);
                            }
                        }else{
                            if(Falling==0&&Health>0){
                                Jump(JumpPower);
                            }
                        }
                    break;
                    case SDLK_ESCAPE:
                        if(OnMenu==1&&Menu>10){
                            OnMenu=0;
                            Menu=55;
                            LoadMenu(Menu);
                        }
                    break;
                    case SDLK_e:
                        UseUsable(ChargeWeapon);
                    break;
                    case SDLK_u:
                        if(UltraHard==0){
                            MapLevel=3;
                            for(I=0; I<120; I++){
                                for(II=0; II<120; II++){
                                    if(RoomPos[I][II]!=0){
                                        knownRooms[I][II]=1;
                                    }
                                }
                            }
                        }
                    break;
                    case SDLK_o:
                        IntroTime=IntroLength-1;
                    break;
                    }
                break;
                case SDL_KEYUP:
                    switch (Event.key.keysym.sym){
                    case SDLK_w:
                        W=0;
                    break;
                    case SDLK_d:
                        D=0;
                    break;
                    case SDLK_s:
                        S=0;
                        S2=0;
                    break;
                    case SDLK_a:
                        AAAAA=0;
                    break;
                    case SDLK_SPACE:
                        if(SpdY<-1&&JumpLevel>0&&Health>0){
                            SpdY=-6;
                        }
                    break;
                    }
                break;
                case SDL_MOUSEMOTION:
                        MouseX=Event.motion.x*(900/(float)VWidth);
                        MouseY=Event.motion.y*(600/(float)VHeight);
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(Health>0&&Menu>=10){
                        switch (Event.button.button){
                            case SDL_BUTTON_LEFT:
                                Mouse1=1;
                            break;
                            case SDL_BUTTON_RIGHT:
                                Mouse2=1;
                            break;
                        }
                        if(MouseX<=200&&MouseY<=200&&UltraHard==0){
                            MapX = (MouseX-MapOfX)/(10/MapZoom);
                            MapY = (MouseY-MapOfY)/(10/MapZoom);
                            SetRoomMap(0);
                        }
                    }

                    if(OnMenu==1&&Menu<10&&Event.button.button==SDL_BUTTON_LEFT){
                        int Id = SpawnEnemy(25);
                        Enemys[Id].X=MouseX-200;
                        Enemys[Id].Y=MouseY;
                    }
                    if(OnMenu==1&&Menu<10&&Event.button.button==SDL_BUTTON_RIGHT){
                        int Id = SpawnEnemy(0);
                        Enemys[Id].X=MouseX-200;
                        Enemys[Id].Y=MouseY;
                    }

                    if(Scene==115){
                        PressButton();
                    }

                    if(Scene<13){
                        Scene=12;
                        IntroTime=IntroLength-1;
                    }

                    if(Menu==0&&OnMenu==0&&Scene==115){
                        ButtonActivater(1);
                        Mouse1=0;
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    switch (Event.button.button){
                        case SDL_BUTTON_LEFT:
                            Mouse1=0;
                        break;
                        case SDL_BUTTON_RIGHT:
                            Mouse2=0;
                        break;
                    }
                break;
            }
        }

        /// ////////////////////// ///

        if(MainAdder%60==0){
            SDL_GetRendererOutputSize(Renderer,&VWidth,&VHeight);
            VWidth*=((float)9/13);
            ScaleX = (float)VWidth/900;
            ScaleY = (float)VHeight/600;
        }

        /// //////////////////// ///
        if(Red==255&&Green<255&&Blue==0){
            Green=Green+5;
        }else if(Green==255&&Red>0){
            Red=Red-5;
        }else if(Green==255&&Red==0&&Blue<255){
            Blue=Blue+5;
        }else if(Blue==255&&Green>0){
            Green=Green-5;
        }else if(Green==0&&Blue==255&&Red<255){
            Red=Red+5;
        }else if(Blue>=1&&Red==255){
            Blue=Blue-5;
        }
	/// /// /// /// /// /// /// ///


        if(Cooldown==0&&Mouse1==1){
            Mouse1=RapidFire;
            Cooldown=FireRate;
            LastShot = ShootNormBullet() +1;
        }

        if(Cooldown==0&&Weapon!=0&&Mouse2==1){
            Mouse2=Secondary[(int) Weapon].RapidFire;
            Cooldown=Secondary[(int) Weapon].Cooldown;
            LastShot = ShootSpclBullet(Weapon) +1;
        }

        /// //////////////////// ////// ////// //////////////////// ///

        MainAdder+=1;

        if(OnMenu!=0){
            BulletRun();
            EnemyRun();
            Boss1Update(1);
            UpdateExplosion();
        }

        if(Cooldown>0){
            Cooldown-=1;
        }

        /// ////////////////////////////////////movement//////////////////////////////////// ///

        if(Health>0){
            SpdX+=(D-AAAAA);
        }

        if(SpdX>Speed){
            SpdX=Speed;
        }else if(SpdX<-Speed){
            SpdX=-Speed;
        }
        if(AAAAA+D==0||AAAAA+D==2){
            if(Timer==0){
                if(SpdX>0){SpdX-=Speed/6;}
                if(SpdX<0){SpdX+=Speed/6;}
            }
        }

        RunMulti();
        /// ////////////////////////////////////images///////////////////////////////////////

        color(150,150,150,255);
        SDL_RenderClear(Renderer);

        //OffsetX=Width/2-TileSize-X+200;
        //OffsetY=Height/2-TileSize-Y;
        OffsetX+=((Width/2-TileSize-X+200)-OffsetX)/7;
        OffsetY+=((Height/2-TileSize-Y)-OffsetY)/7;
        UpdateCutscene();

        MapOfX=MapX*-(10/MapZoom)/MapZoom;
        MapOfY=MapY*-(10/MapZoom)/MapZoom;

        if(OffsetX>200){ OffsetX=200;}
        if(OffsetX<GetRoom(MapX,MapY).Width*-1+Width+200){ OffsetX=GetRoom(MapX,MapY).Width*-1+Width+200; }
        if(OffsetY>0){ OffsetY=0;}
        if(OffsetY<GetRoom(MapX,MapY).Height*-1+Height){ OffsetY=GetRoom(MapX,MapY).Height*-1+Height; }

        if(OnMenu!=0){
            RoomMap();

            BulletRender();
            EnemyRender();
            if(Menu>=10){
                playerStuff();
            }
            DrawFourground();
            Boss1Render(1);
            RenderExplosion();

            UpdateItem();
            DropsUpdate();

            RunMulti();
        }

        color(0,0,0,255);
        FillRect(0,0,200,Height);
        FillRect(Width+200,0,200,Height);

        if(OnMenu!=0&&Menu>=10){ MiniMap(); }

        MenuRender();

        if(Corrupted==1){
            color(0,0,0,150+sin(MainAdder/10)*20+CorrupAmount);
            FillRect(0,0,Width+400,Height);
        }
        if(MainAdder%20==0){
            CorrupAmount+=1;
        }

        if(IntroTime<100*17*0-1){
            if(IntroTime%100==0||IntroTime==0){
                char String[18];
                strcpy((char*) &String, "Images/intro/A.png");
                String[13]=IntroTime/100+65;
                IntroImg = IMG_LoadTexture(Renderer,String);
            }
            SDL_Rect Rect;
            Rect.x=200*ScaleX;
            Rect.y=0;
            Rect.h=Height*ScaleY;
            Rect.w=Width*ScaleX;
            SDL_RenderCopy(Renderer,IntroImg,NULL,&Rect);
            IntroTime+=1;
        }

        DrawIntro();

        SDL_RenderPresent(Renderer);
        FpsCapWait();
    }

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDLNet_TCP_Close(client);
    SDLNet_TCP_Close(server);

    Mix_CloseAudio();
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}




