#ifndef CUTSCENE
#define CUTSCENE

int ScenX, ScenY;
int TempX, TempY;
int ActiveScen;
int IntroTime=99;
int IntroLength=100;

void loadMap(char FileName[15], int A);

void MoveCutscene(int X, int Y, int XX, int YY){
    TempX=X;
    TempY=Y;
    ScenX=(XX-X)/100.0;
    ScenY=(YY-Y)/100.0;
    Timer=1;
    ActiveScen=1;
    SpdX=0;
    SpdY=0;
}

void UpdateCutscene(){
    if(Timer!=0){
        Timer+=1;
        if(Timer<=100){
            OffsetX=Width/2-TempX-(ScenX*Timer)+200;
            OffsetY=Height/2-TempY-(ScenY*Timer);
        }else if(Timer>=150){
            if(Timer>=250){ Timer=0; }
            OffsetX=Width/2-TempX-(ScenX*(100+149-Timer))+200;
            OffsetY=Height/2-TempY-(ScenY*(100+149-Timer));
        }else{
            OffsetX=Width/2-TempX-(ScenX*100)+200;
            OffsetY=Height/2-TempY-(ScenY*100);
        }
        SpdX=0;
        SpdY=0;
    }
}

void DrawIntro(){
    if(Scene!=115){
        IntroTime+=1;
    }
    if(IntroTime>=IntroLength){
        IntroTime=0;
        Scene+=1;

        switch(Scene){
            case 1:
                IntroLength=200;
            break;
            case 2:
                IntroLength=130;
                OnMenu=1;
                loadMap("a/into/log3.txt",0);
                X=Width/2-TileSize;
                Y=Height/2-TileSize;
                OffsetX=Width/2-TileSize-X+200;
                OffsetY=Height/2-TileSize-Y;
                Rooms[RoomPos[MapX][MapY]].Width=Width*2;
                Rooms[RoomPos[MapX][MapY]].Height=Height;
                Rooms[RoomPos[MapX][MapY]].Area=5;
            break;
            case 3:
                IntroLength=130;
            break;
            case 4:
                IntroLength=400;
                KillAll();
                BRed=100;
                BGreen=10;
                BBlue=10;
            break;
            case 5:
                IntroLength=200;
                OnMenu=1;
                loadMap("a/into/log4.txt",0);
                X=Width-TileSize;
                Y=Height/2-TileSize;
                OffsetX=Width/2-TileSize-X+200;
                OffsetY=Height/2-TileSize-Y;
                Rooms[RoomPos[MapX][MapY]].Width=Width*2;
                Rooms[RoomPos[MapX][MapY]].Height=Height;
                Rooms[RoomPos[MapX][MapY]].Area=0;
            break;
            case 6:
                KillAll();
                IntroLength=250;
                OnMenu=1;
                loadMap("a/into/wid2.txt",0);
                X=Width/2-TileSize;
                Y=Height/2-TileSize;
                OffsetX=Width/2-TileSize-X+200;
                OffsetY=Height/2-TileSize-Y;
                Rooms[RoomPos[MapX][MapY]].Width=Width*4;
                Rooms[RoomPos[MapX][MapY]].Height=Height;
                Rooms[RoomPos[MapX][MapY]].Area=5;
            break;
            case 7:
            break;
            case 8:
                IntroLength=255;
            break;
            case 9:
                KillAll();
                IntroLength=650;
                OnMenu=1;
                loadMap("a/into/wid5.txt",0);
                X=Width/2-TileSize;
                Y=Height/2-TileSize;
                OffsetX=Width/2-TileSize-X+200;
                OffsetY=Height/2-TileSize-Y;
                Rooms[RoomPos[MapX][MapY]].Width=Width*4;
                Rooms[RoomPos[MapX][MapY]].Height=Height;
                Rooms[RoomPos[MapX][MapY]].Area=5;
            break;
            case 10:
                KillAll();
                IntroLength=200;
            break;
            case 11:
                OnMenu=1;
                loadMap("a/into/wid6.txt",0);
                X=Width/2*5-TileSize;
                Y=Height/2-TileSize;
                OffsetX=Width/2-TileSize-X+200;
                OffsetY=Height/2-TileSize-Y;
                Rooms[RoomPos[MapX][MapY]].Width=Width*4;
                Rooms[RoomPos[MapX][MapY]].Height=Height;
                Rooms[RoomPos[MapX][MapY]].Area=0;
            break;
            case 12:
                IntroLength=255;
            break;
            case 13:
                KillAll();
                IntroLength=150;
                OnMenu=0;
            break;
            case 14:
                Scene=115;
            break;
        }

    }

    if(Scene==1){
        color(255,255,255,255);
        FillRect(200,0,Width,Height);

        DrawTextCenter("Once there was a planet.",200+Width/2,Height/4,20,20);
        DrawImg(57,200+Width/2-75,Height/2-75,150,150);
    }else if(Scene==2){
        X+=3;

        DrawTextCenterBox("It was inhabited by stick guys.",200+Width/2,Height/8,30,30);
    }else if(Scene==3){
        X+=2;
        color(0,0,0,255);
        FillRect(200+Width/2-716/2-15,Height/8-45+17,736,90);
        color(255,255,255,255);
        FillRect(200+Width/2-716/2-10,Height/8-40+17,726,80);

        DrawTextCenter("They were happy on their",200+Width/2,Height/8,30,30);
        DrawTextCenter("peaceful planet.",200+Width/2,Height/8+35,30,30);

    }else if(Scene==4){
        if(IntroTime>=45){
            if(IntroTime<=300){
                color(255-IntroTime/2,300-IntroTime,300-IntroTime,255);
            }else{
                color(105,0,0,255);
            }
        }else{
            color(255,255,255,255);
        }
        FillRect(200,0,Width,Height);

        DrawTextCenter("Until another planet approached...",200+Width/2,Height/4,20,20);

        DrawImg(57,200+Width/2-75,Height/2-75,150,150);
        DrawImg(57,200+Width/3-75,Height-IntroTime/4*3,150,150);

    }else if(Scene==5){
        color(0,0,0,255);
        FillRect(200+Width/2-716/2-15,Height/8-45+17,736,90);
        color(255,255,255,255);
        FillRect(200+Width/2-716/2-10,Height/8-40+17,726,80);

        DrawTextCenter("It was filled",200+Width/2,Height/8,30,30);
        DrawTextCenter("with evil monster.",200+Width/2,Height/8+35,30,30);

    }else if(Scene==6){
        X+=7;

        DrawTextCenterBox("It wasn't long before they invaded",200+Width/2,Height/4,20,20);
    }else if(Scene==7){
        X+=3;
    }else if(Scene==8){
        DrawTextCenterBox("Many people had died fighting them.",200+Width/2,Height/4,20,20);
    }else if(Scene==9){
        X+=4;
        DrawTextCenterBox("The stick guys still managed to kill the monsters...",200+Width/2,Height/4,20,20);
    }else if(Scene==10){
        color(105,0,0,255);
        FillRect(200,0,Width,Height);

        DrawImg(57,200+Width/2-75,Height/2-75,150,150);
        DrawImg(57,200+Width/3-75,Height-300,150,150);

        DrawTextCenter("But the stick guys wanted to destroy the evil...",200+Width/2,Height/4,20,20);
    }else if(Scene==11){
        DrawTextCenterBox("For the first time, they entered to evil planet.",200+Width/2,Height/4,20,20);
    }else if(Scene==12){
        color(255,255,255,IntroTime);
        FillRect(200,0,Width,Height);
    }else if(Scene==13){
        if(IntroTime*2>=45){
            color(255,255,255,300-IntroTime*2);
            FillRect(200,0,Width,Height);
        }else{
            color(255,255,255,255);
            FillRect(200,0,Width,Height);
        }
    }
}

#endif
