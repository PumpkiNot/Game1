#ifndef DROPS
#define DROPS

#include <math.h>

int Random(int Min, int Max);
int intersept(int x, int y, int width1, int height1,int x2, int y2, int width2, int height2);

typedef struct Entitys2{
int X;
int Y;
int Alive;
int Id;
int Type;
}Drop;

Drop Drops[10];

void SpawnDrop(int Id, int Type){
    int I;
    for(I=0; I<10; I++){
        if(Drops[I].Alive==0){
            Drops[I].X=Rooms[RoomPos[MapX][MapY]].Width/2-TileSize/2;
            Drops[I].Y=Rooms[RoomPos[MapX][MapY]].Height/2-TileSize/2;
            Drops[I].Alive=1;
            Drops[I].Id=Id;
            Drops[I].Type=Type;
            while(1){
                if(GetTileStuff(Drops[I].X+TileSize/2,Drops[I].Y+TileSize/2)!=0||GetTileStuff(Drops[I].X,Drops[I].Y)!=0){
                    Drops[I].Y-=TileSize;
                }else{
                    break;
                }
            }
            break;
        }
    }
}

void DropsRender(int Id){
    if(Drops[Id].Alive==1){
        if(Drops[Id].Type==3||Drops[Id].Type==1){
            int Scale = Random(-10,10);
            color(0,255,255,255);
            DrawImgI(Drops[Id].Type-1, Drops[Id].X + OffsetX + TileSize*0.2 -Scale/2, Drops[Id].Y + OffsetY + TileSize*0.2 -Scale/2, TileSize/1.2 +Scale, TileSize/1.2 +Scale);
        }else if(Drops[Id].Type==4){
            int Scale = sin(MainAdder/3)*7;
            color(0,255,255,255);
            DrawImgI(Drops[Id].Type-1, Drops[Id].X + OffsetX + TileSize*0.2 -Scale/2, Drops[Id].Y + OffsetY + TileSize*0.2 -Scale/2, TileSize/1.2 +Scale, TileSize/1.2 +Scale);
        }else{
            color(0,255,255,255);
            DrawImgI(Drops[Id].Type-1, Drops[Id].X + OffsetX + TileSize*0.2, Drops[Id].Y + OffsetY + TileSize*0.2, TileSize/1.2 , TileSize/1.2 );
        }
    }
}

void DropsUpdate(){
    for(I=0; I<10; I++){
        if(Drops[I].Alive==1){
            DropsRender(I);

            if(intersept(X, Y, TileSize, TileSize, Drops[I].X + (int)((float)TileSize*0.2), Drops[I].Y + (int)((float)TileSize*0.2),(int)((float)TileSize/1.2), (int)((float)TileSize/1.2))){
                if(Drops[I].Type==1){
                    Sheild+=100;
                }else if(Drops[I].Type==2){
                    Ammo+=30;
                }else if(Drops[I].Type==3){
                    Charge+=10;
                }else if(Drops[I].Type==4){
                    Health+=250;
                }
                Drops[I].Alive=0;
            }
        }
    }
}

#endif
