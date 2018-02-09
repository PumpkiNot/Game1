#ifndef DRAWFUNCTIONSH // CHANGE THIS DEPENDING ON THE HEADER FILE
#define DRAWFUNCTIONSH // CHANGE THIS TO BE THE SAME AS BEFORE
// put code here

#include <string.h>

void LoadMenu(int Number);

void color(int A,int B,int C,int D){
    if(D!=255){
        SDL_SetRenderDrawBlendMode(Renderer,SDL_BLENDMODE_BLEND);
    }else{
        SDL_SetRenderDrawBlendMode(Renderer,SDL_BLENDMODE_NONE);
    }
    SDL_SetRenderDrawColor(Renderer,A,B,C,D);
}

void point(int A,int B){
    SDL_RenderDrawPoint(Renderer,A,B);
}

void EmptyRect(int A,int B,int C,int D){
    SDL_Rect Rectangle;
    Rectangle.x=A*ScaleX;
    Rectangle.y=B*ScaleY;
    Rectangle.w=C*ScaleX;
    Rectangle.h=D*ScaleY;
    SDL_RenderDrawRect(Renderer,&Rectangle);
}

void FillRect(int A,int B,int C,int D){
    SDL_Rect Rectangle;
    Rectangle.x=A*ScaleX;
    Rectangle.y=B*ScaleY;
    Rectangle.w=C*ScaleX;
    Rectangle.h=D*ScaleY;
    SDL_RenderFillRect(Renderer,&Rectangle);
}

/// /////////////////// - Map Functions - /////////////////// ///

int Round(int Number, int B){
    int C;

    if(Number%B>B/2){
        C = Number+(B-(Number%B));
    }else{
        C = Number - (Number%B);
    }

    return C;
}

int GetTileStuff(int X, int Y){
    return MapArray[X/TileSize][Y/TileSize];
}

void Jump(int JumpPower){
    SpdY=JumpPower*-1;
    PlaySoundPro(0);
}

/// ///////////////////////// - collision stuff - ///////////////////////// ///

int T,B,L,R,TL,BL,TR,BR,BR2=0,BL2=0;

void updateCollsion(int XX, int YY, int Size, int SpdY){
    T=Round(YY-(Size-TileSize/2)+1,TileSize);
    B=Round(YY+(Size-TileSize/2),TileSize);
    L=Round(XX-(Size-TileSize/2)+1,TileSize);
    R=Round(XX+(Size-TileSize/2),TileSize);
    TL=GetTileStuff(L,T);
    TR=GetTileStuff(R,T);
    BL=GetTileStuff(L,B);
    BR=GetTileStuff(R,B);
    BL2=BL;
    BR2=BR;

    if(TL==2){TL=1;}
    if(TR==2){TR=1;}
    if(BL==2){BL=1;}
    if(BR==2){BR=1;}

    int B2=Round(YY+Size+TileSize/2-SpdY-1,TileSize);
    if(BL==4&&GetTileStuff(L,B2)==4){BL=1;}
    if(BR==4&&GetTileStuff(R,B2)==4){BR=1;}
}

int CheckCollsions(int *X, int *Y, int *SpdX, int *SpdY, int *Falling, int HasGravity, int Size){
    int NextX=*X+*SpdX;
    int NextY=*Y+*SpdY;
    int Landed=0;

    /// /////// - tile collision - /////// ///
    updateCollsion(*X,NextY,Size,*SpdY);
    if(*SpdY<0){
        if(TL==1||TR==1){
            *SpdY=0;
            *Y=Round(*Y,TileSize);
        }else{
            *Y+=*SpdY;
        }
    }
    if(*SpdY>0){
        if(BR==1||BL==1){
            *SpdY=0;
            *Y=Round(*Y,TileSize);
            *Falling=0;
            Landed=1;
        }else{
            *Y+=*SpdY;
        }
    }


    updateCollsion(NextX,*Y,Size,*SpdY);
    if(*SpdX<0){
        if(TL==1||BL==1){
            *SpdX=0;
            *X=Round(*X,TileSize);
            if(*Falling==0){*SpdY=-15;}
        }else{
            *X+=*SpdX;
        }
    }
    if(*SpdX>0){
        if(TR==1||BR==1){
            *SpdX=0;
            *X=Round(*X,TileSize);
            if(*Falling==0){*SpdY=-15;}
        }else{
            *X+=*SpdX;
        }
    }


    int IQ, ShouldFall=0;
    for(IQ=0; IQ<30; IQ++){
        if( intersept(*X,*Y,TileSize,TileSize+5,Enemys[IQ].X,Enemys[IQ].Y,TileSize,TileSize)&&Enemys[IQ].Alive==1&&Enemys[IQ].Type>=20&&Enemys[IQ].Type<=24){
            int X2, Y2;
            int Number=0;
            X2=*X-Enemys[IQ].X;
            Y2=*Y-Enemys[IQ].Y;

            updateCollsion(*X,*Y+1,Size,*SpdY);
            if(((BL!=1&&BR!=1)||(Enemys[IQ].SpdY<0&&*X-Enemys[IQ].X>0))){
                Number=1;
            }

            if(abs(X2)<abs(Y2) && *Y>Enemys[IQ].Y &&Number==1){
                *Y=Enemys[IQ].Y+TileSize+1;
                *SpdY=1;
            }else if(abs(Y2)<abs(X2) && *X<Enemys[IQ].X){
                *X=Enemys[IQ].X-TileSize;
                *SpdX=0;
            }else if(abs(X2)<abs(Y2) &&Number==1){
                updateCollsion(*X,*Y-1,Size,*SpdY);
                if(TL!=1&&TR!=1){
                    *Y=Enemys[IQ].Y-TileSize;
                    *SpdY=0;
                    *Falling=0;
                    ShouldFall=1;
                }
            }else if(abs(Y2)<abs(X2) && *X>Enemys[IQ].X){
                *X=Enemys[IQ].X+TileSize;
                *SpdX=0;
            }
        }
    }


    updateCollsion(*X,*Y+1,Size,*SpdY);
    if(BL!=1&&BR!=1&&ShouldFall==0){
        *Falling=1;
        *SpdY+=1*HasGravity;
    }else{ // if(BL||BR)
        *Falling=0;
    }

    if(HasGravity==0){Falling=0;}

    return Landed;
}

int intersept(int x, int y, int width1, int height1, int x2, int y2, int width2, int height2){
    int Awnser=0;
    if(x+width1>x2&&x<x2+width2){
        if(y+height1>y2&&y<y2+height2){
            Awnser=1;
        }
    }
    return Awnser;
}

/// ////////////////////// - Map loading - ////////////////////// ///

void loadMap(char FileName[15],int VGKVUHKJB){
    Area=GetRoom(MapX,MapY).Area;
    HasSaved=0;
    OnMenu=1;
    Item.Used=1;

    int I,II;
    int IsBoss=0;

    int Size=1,SizeB=1,Special=0;
    if(FileName[7]=='b'||FileName[9]=='s'){
        Size=2;
        SizeB=2;
    }else if(FileName[8]=='o'){
        Size=2;
    }else if(FileName[8]=='a'){
        SizeB=2;
    }else if(FileName[7]=='w'){
        printf("a\n");
        Size=4;
    }

    if(FileName[3]=='p'){
        Special=1;
    }

    FILE *File;
    File = fopen(FileName,"r");
    char line[60];

    for(I=0; I<10*SizeB; I++){
        // A new line makes this function stop reading. Here's what the problem was. The first line was read. The loop stuff happened. THe second line tried to be read, but ran into a new line, so it stopped reading early. The third line would start to read, but it's messed up because the second line was never actually read.
        fread(&line,1,15*Size,File); // Read 15 elements of size 1 into memory at the address of line.
        for(II=0; II<15*Size; II++){
            if(line[II]=='1'){
                MapArray[II][I]=1;
            }else if(line[II]=='2'){
                if(VGKVUHKJB==0||(VGKVUHKJB==2&&ZAwaken==1)){
                    MapArray[II][I]=2;
                }else{
                    if(I==19||I==9){
                        MapArray[II][I]=4*SaftyPlat;
                    }else{
                        if(Area!=3){
                            MapArray[II][I]=0;
                        }else{
                            MapArray[II][I]=5;
                        }
                    }
                }
                IsBoss=1;
            }else if(line[II]=='3'&&UltraHard==0){
                MapArray[II][I]=0;
                if(GetRoom(MapX,MapY).Area==3){
                    MapArray[II][I]=5;
                }
                if(FileName[7]!='s'&&GetRoom(MapX,MapY).Area!=3){
                    if(VGKVUHKJB==0){
                        SpawnItem(II*TileSize, I*TileSize, GetRoom(MapX,MapY).ItemId);
                    }else{
                        SpawnItem(II*TileSize, I*TileSize, GetRoom(MapX,MapY).ItemId);
                        Item.Used=1;
                    }
                }else{
                    if(VGKVUHKJB==0){
                        if(FileName[10]=='A'){
                            SpawnSpecial(II*TileSize,I*TileSize,(GetRoom(MapX,MapY).Area+1)*2);
                        }else{
                            SpawnSpecial(II*TileSize,I*TileSize,(GetRoom(MapX,MapY).Area+1)*2+1);
                        }
                    }else{
                        SpawnItem(II*TileSize, I*TileSize, GetRoom(MapX,MapY).ItemId);
                        Item.Used=1;
                    }
                }
            }else if(line[II]=='4'){
                MapArray[II][I]=4;
            }else if(line[II]=='5'){
                MapArray[II][I]=5;
            }else if(line[II]=='.'){
                MapArray[II][I]=-1;
            }else{
                MapArray[II][I]=0;
                if(line[II]>57&&I>0){
                    if(MapArray[II][I-1]==-1){
                        MapArray[II][I]=-1;
                    }
                }
            }
            if(line[II]=='a'&&Corrupted==0){
                if(VGKVUHKJB==0){
                    int EnemyId = SpawnEnemy(0);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='b'){
                if(VGKVUHKJB==0){
                    int EnemyId = SpawnEnemy(1);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='c'){
                if(VGKVUHKJB==0){
                    int EnemyId = SpawnEnemy(2);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='d'||(line[II]=='a'&&Corrupted==1)){
                if(Area==3){
                    MapArray[II][I]=5;
                }
                if(VGKVUHKJB!=1){
                    int EnemyId = SpawnEnemy(3);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='e'){
                if(VGKVUHKJB==0){
                    int EnemyId = SpawnEnemy(4);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='s'){
                if(VGKVUHKJB==0){
                    int EnemyId = SpawnEnemy(26);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='t'){
                if(VGKVUHKJB==0){
                    int EnemyId = SpawnEnemy(25);
                    Enemys[EnemyId].X=II*TileSize;
                    Enemys[EnemyId].Y=I*TileSize;
                }
            }
            else if(line[II]=='u'){
                int EnemyId = SpawnEnemy(20);
                Enemys[EnemyId].X=II*TileSize;
                Enemys[EnemyId].Y=I*TileSize;
            }
            else if(line[II]=='v'){
                int EnemyId = SpawnEnemy(21);
                Enemys[EnemyId].X=II*TileSize;
                Enemys[EnemyId].Y=I*TileSize;
            }
            else if(line[II]=='w'){
                int EnemyId = SpawnEnemy(22);
                Enemys[EnemyId].X=II*TileSize;
                Enemys[EnemyId].Y=I*TileSize;
            }
            else if(line[II]=='x'){
                int EnemyId = SpawnEnemy(23);
                Enemys[EnemyId].X=II*TileSize;
                Enemys[EnemyId].Y=I*TileSize;
            }
            else if(line[II]=='y'){
                int EnemyId = SpawnEnemy(24);
                Enemys[EnemyId].X=II*TileSize;
                Enemys[EnemyId].Y=I*TileSize;
            }
            else if(line[II]=='z'){
                if(VGKVUHKJB!=1){
                    if(GetRoom(MapX,MapY).Area==0){
                        BossSpawn1(II*TileSize,I*TileSize,Random(1,2));
                    }else if(GetRoom(MapX,MapY).Area==1){
                        BossSpawn1(II*TileSize,I*TileSize,3);
                    }else if(GetRoom(MapX,MapY).Area==2){
                        BossSpawn1(II*TileSize,I*TileSize,4);
                    }else if(GetRoom(MapX,MapY).Area==4){
                        BossSpawn1(II*TileSize,I*TileSize,5);
                    }
                }
            }
        }
        fseek(File,2,SEEK_CUR); // On Windows, a newline character is two bytes. 0D and then 0A. THis function will seek past those.
    }
    fclose(File);

    if(IsBoss==0&&Scene==115){
        Mix_FadeOutChannel(1,800);
        LastArea=100;
    }else{
        Mix_Volume(1,Volume);
    }

    if((Rooms[RoomPos[MapX][MapY]].BigRoom==1||Rooms[RoomPos[MapX][MapY]].BigRoom==5||Rooms[RoomPos[MapX][MapY]].BigRoom==7)&&Rooms[RoomPos[MapX][MapY]].Direct==0&&Special==0){

        if((RoomPos[MapX][MapY-1]==0||GetRoom(MapX,MapY-1).Direct!=3)&&(GetRoom(MapX,MapY-1).Direct!=0||RoomPos[MapX][MapY-1]==0)){MapArray[6][0]=1;MapArray[7][0]=1;MapArray[8][0]=1;}
        if((RoomPos[MapX-1][MapY]==0||GetRoom(MapX-1,MapY).Direct!=2)&&(GetRoom(MapX-1,MapY).Direct!=0||RoomPos[MapX-1][MapY]==0)){MapArray[0][4]=1; MapArray[0][5]=1;}

        /// big and long
        if(Rooms[RoomPos[MapX][MapY]].BigRoom<7){
            if((RoomPos[MapX+2][MapY]==0||GetRoom(MapX+2,MapY).Direct!=4)&&(GetRoom(MapX+2,MapY).Direct!=0||RoomPos[MapX+2][MapY]==0)){MapArray[29][4]=1; MapArray[29][5]=1;}
            if((RoomPos[MapX+1][MapY-1]==0||GetRoom(MapX+1,MapY-1).Direct!=3)&&(GetRoom(MapX+1,MapY-1).Direct!=0||RoomPos[MapX+1][MapY-1]==0)){MapArray[21][0]=1; MapArray[22][0]=1; MapArray[23][0]=1;}
        }

        /// big and tall
        if(Rooms[RoomPos[MapX][MapY]].BigRoom<5||Rooms[RoomPos[MapX][MapY]].BigRoom>6){
            if((RoomPos[MapX][MapY+2]==0||GetRoom(MapX,MapY+2).Direct!=1)&&(GetRoom(MapX,MapY+2).Direct!=0||RoomPos[MapX][MapY+2]==0)){MapArray[6][19]=1; MapArray[7][19]=1; MapArray[8][19]=1;}
            if((RoomPos[MapX-1][MapY+1]==0||GetRoom(MapX-1,MapY+1).Direct!=2)&&(GetRoom(MapX-1,MapY+1).Direct!=0||RoomPos[MapX-1][MapY+1]==0)){MapArray[0][14]=1; MapArray[0][15]=1;}

            if(Rooms[RoomPos[MapX][MapY]].BigRoom<5){
                /// big
                if((RoomPos[MapX+1][MapY+2]==0||GetRoom(MapX+1,MapY+2).Direct!=1)&&(GetRoom(MapX+1,MapY+2).Direct!=0||RoomPos[MapX+1][MapY+2]==0)){MapArray[21][19]=1; MapArray[22][19]=1; MapArray[23][19]=1;}
                if((RoomPos[MapX+2][MapY+1]==0||GetRoom(MapX+2,MapY+1).Direct!=4)&&(GetRoom(MapX+2,MapY+1).Direct!=0||RoomPos[MapX+2][MapY+1]==0)){MapArray[29][14]=1; MapArray[29][15]=1;}
            }else{
                /// tall
                if((RoomPos[MapX+1][MapY]==0||GetRoom(MapX+1,MapY).Direct!=4)&&(GetRoom(MapX+1,MapY).Direct!=0||RoomPos[MapX+1][MapY]==0)){MapArray[14][4]=1; MapArray[14][5]=1;}
                if((RoomPos[MapX+1][MapY+1]==0||GetRoom(MapX+1,MapY+1).Direct!=4)&&(GetRoom(MapX+1,MapY+1).Direct!=0||RoomPos[MapX+1][MapY+1]==0)){MapArray[14][14]=1; MapArray[14][15]=1;}
            }

        }else{
            /// long
            if((RoomPos[MapX][MapY+1]==0||GetRoom(MapX,MapY+1).Direct!=3)&&(GetRoom(MapX,MapY+1).Direct!=0||RoomPos[MapX][MapY+1]==0)){MapArray[6][9]=1; MapArray[7][9]=1; MapArray[8][9]=1;}
            if((RoomPos[MapX+1][MapY+1]==0||GetRoom(MapX+1,MapY+1).Direct!=3)&&(GetRoom(MapX+1,MapY+1).Direct!=0||RoomPos[MapX+1][MapY+1]==0)){MapArray[21][9]=1; MapArray[22][9]=1; MapArray[23][9]=1;}
        }
    }
    if(GetRoom(MapX,MapY).DropId!=0){
        SpawnDrop(1, GetRoom(MapX,MapY).DropId);
    }

    if(ZAwaken==1){
        for(I=0; I<30; I++){
            if(Enemys[I].Type==3){
                Enemys[I].Sleeping=2;
                Enemys[I].Walking=0;
                Enemys[I].Counter=0;
            }
        }
    }
}

int MakeElevator(int StartId, int Min1, int Max1, int Min2, int Max2){
    int I;
    for(I=Min1; I<Min1+Max1; I++){
        if(GetRoom(Rooms[I].X,Rooms[I].Y+1).Id==0&&GetRoom(Rooms[I].X,Rooms[I].Y+2).Id==0&&GetRoom(Rooms[I].X-1,Rooms[I].Y+1).Id==0&&GetRoom(Rooms[I].X+1,Rooms[I].Y+1).Id==0&&Rooms[I].Direct==0){
            Rooms[StartId].X=Rooms[I].X;
            Rooms[StartId].Y=Rooms[I].Y+1;
            Rooms[StartId].Width=Width;
            Rooms[StartId].Height=Height;
            Rooms[StartId].Id=StartId;
            Rooms[StartId].Area=Rooms[I].Area;
            Rooms[StartId].BigRoom=-1;
            RoomPos[Rooms[StartId].X][Rooms[StartId].Y]=StartId;
            strcpy((char*)&(Rooms[StartId].Type),"a/13--/d.txt");
            SetRoom(I);
            break;
        }
    }
    StartId+=1;
    for(I=Min2; I<Min2+Max2; I++){
        if(GetRoom(Rooms[I].X,Rooms[I].Y-1).Id==0&&GetRoom(Rooms[I].X,Rooms[I].Y-2).Id==0&&GetRoom(Rooms[I].X-1,Rooms[I].Y-1).Id==0&&GetRoom(Rooms[I].X+1,Rooms[I].Y-1).Id==0&&Rooms[I].Direct==0){
            Rooms[StartId].X=Rooms[I].X;
            Rooms[StartId].Y=Rooms[I].Y-1;
            Rooms[StartId].Width=Width;
            Rooms[StartId].Height=Height;
            Rooms[StartId].Id=StartId;
            Rooms[StartId].Area=Rooms[I].Area;
            Rooms[StartId].BigRoom=-2;
            RoomPos[Rooms[StartId].X][Rooms[StartId].Y]=StartId;
            strcpy((char*)&(Rooms[StartId].Type),"a/13--/u.txt");
            SetRoom(I);

            RoomPair[Rooms[StartId-1].X][Rooms[StartId-1].Y]=Rooms[StartId];
            RoomPair[Rooms[StartId].X][Rooms[StartId].Y]=Rooms[StartId-1];

            Rooms[StartId].IsItemRoom=0;
            Rooms[StartId-1].IsItemRoom=0;
            Rooms[StartId].ItemId=0;
            Rooms[StartId-1].ItemId=0;
            Rooms[StartId].Pair=StartId-1;
            Rooms[StartId-1].Pair=StartId;

            break;
        }
    }
    return 2;
}

void MakeRect(SDL_Rect *Rect, int X,int Y, int Width, int Height){
    Rect->x=X;
    Rect->y=Y;
    Rect->w=Width;
    Rect->h=Height;
}

int GetDirect(int number){
    if(number<0){
        return -1;
    }else{
        return 1;
    }
}

int GetAnimation(int Count, int Scaler){
    return (MainAdder/Scaler)%Count;
}

void DrawText(char String[], int X, int Y, int Width, int Height){
    int I;
    int Size = strlen(String);
    for(I=0; I<Size; I++){
        int Number = String[I];
        Text(Number, X + (Width*0.77)*I, Y, Width, Height);
    }
}

int DrawTextCenter(char String[], int X, int Y, int Width, int Height){
    int I;
    int Size = strlen(String);

    int Width2 = ((Width*0.77)*Size)/2;
    int Height2 = Height/2;

    for(I=0; I<Size; I++){
        int Number = String[I];
        Text(Number, X + (Width*0.77)*I -Width2, Y -Height2, Width, Height);
    }

    return ((Width*0.77)*Size);
}

int DrawTextCenterBox(char String[], int X, int Y, int Width, int Height){
    int I;
    int Size = strlen(String);

    int Width2 = ((Width*0.77)*Size)/2;
    int Height2 = Height/2;

    color(0,0,0,255);
    FillRect(X-Width2-14,Y-Height2-10,Width2*2+20,Height2*2+28);
    color(255,255,255,255);
    FillRect(X-Width2-9,Y-Height2-5,Width2*2+10,Height2*2+18);

    for(I=0; I<Size; I++){
        int Number = String[I];
        Text(Number, X + (Width*0.77)*I -Width2, Y -Height2, Width, Height);
    }

    return ((Width*0.77)*Size);
}

int MakeRoom(int Id, int X, int Y, int Area, int BigRoom, char String[17]){
    Rooms[Id].IsItemRoom=0;
    Rooms[Id].ItemId=0;
    if(BigRoom==0){
        Rooms[Id].Width=Width;
        Rooms[Id].Height=Height;
        Rooms[Id].Id=Id;
        Rooms[Id].Area=Area;
        Rooms[Id].X=0;
        Rooms[Id].Y=0;
        RoomPos[X][Y]=Id;
        strcpy((char*) &Rooms[Id].Type, "a/area4/1.txt");

        return 1;
    }else if(BigRoom==1){

        Rooms[Id+0].X=X;
        Rooms[Id+1].X=X+1;
        Rooms[Id+2].X=X;
        Rooms[Id+3].X=X+1;
        Rooms[Id+0].Y=Y;
        Rooms[Id+1].Y=Y;
        Rooms[Id+2].Y=Y+1;
        Rooms[Id+3].Y=Y+1;

        Rooms[Id+0].Width=Width*2;
        Rooms[Id+1].Width=Width*2;
        Rooms[Id+2].Width=Width*2;
        Rooms[Id+3].Width=Width*2;
        Rooms[Id+0].Height=Height*2;
        Rooms[Id+1].Height=Height*2;
        Rooms[Id+2].Height=Height*2;
        Rooms[Id+3].Height=Height*2;

        Rooms[Id+0].Id=Id+0;
        Rooms[Id+1].Id=Id+1;
        Rooms[Id+2].Id=Id+2;
        Rooms[Id+3].Id=Id+3;

        RoomPos[X+0][Y+0]=Id+0;
        RoomPos[X+1][Y+0]=Id+1;
        RoomPos[X+0][Y+1]=Id+2;
        RoomPos[X+1][Y+1]=Id+3;

        Rooms[Id+0].BigRoom=1;
        Rooms[Id+1].BigRoom=2;
        Rooms[Id+2].BigRoom=3;
        Rooms[Id+3].BigRoom=4;

        Rooms[Id].Area=Area;
        Rooms[Id+1].Area=Area;
        Rooms[Id+2].Area=Area;
        Rooms[Id+3].Area=Area;

        strcpy((char*) &Rooms[Id+0].Type, (const char*) String);
        strcpy((char*) &Rooms[Id+1].Type, (const char*) String);
        strcpy((char*) &Rooms[Id+2].Type, (const char*) String);
        strcpy((char*) &Rooms[Id+3].Type, (const char*) String);

        return 4;
    }else if(BigRoom==2){

        Rooms[Id+0].X=X;
        Rooms[Id+1].X=X+1;
        Rooms[Id+0].Y=Y;
        Rooms[Id+1].Y=Y;

        Rooms[Id+0].Width=Width*2;
        Rooms[Id+1].Width=Width*2;
        Rooms[Id+0].Height=Height;
        Rooms[Id+1].Height=Height;

        Rooms[Id+0].Id=Id+0;
        Rooms[Id+1].Id=Id+1;

        RoomPos[X+0][Y+0]=Id+0;
        RoomPos[X+1][Y+0]=Id+1;

        Rooms[Id+0].BigRoom=5;
        Rooms[Id+1].BigRoom=6;

        Rooms[Id].Area=Area;
        Rooms[Id+1].Area=Area;

        strcpy((char*) &Rooms[Id+0].Type, (const char*) String);
        strcpy((char*) &Rooms[Id+1].Type, (const char*) String);

        return 2;
    }else if(BigRoom==3){

        Rooms[Id+0].X=X;
        Rooms[Id+1].X=X;
        Rooms[Id+0].Y=Y;
        Rooms[Id+1].Y=Y+1;

        Rooms[Id+0].Width=Width;
        Rooms[Id+1].Width=Width;
        Rooms[Id+0].Height=Height*2;
        Rooms[Id+1].Height=Height*2;

        Rooms[Id+0].Id=Id+0;
        Rooms[Id+1].Id=Id+1;

        RoomPos[X+0][Y+0]=Id+0;
        RoomPos[X+0][Y+1]=Id+1;

        Rooms[Id+0].BigRoom=7;
        Rooms[Id+1].BigRoom=8;

        Rooms[Id].Area=Area;
        Rooms[Id+1].Area=Area;

        strcpy((char*) &Rooms[Id+0].Type, (const char*) String);
        strcpy((char*) &Rooms[Id+1].Type, (const char*) String);

        return 2;
    }
    return 0;
}

void PlaySoundPro(int SoundId){
    int Id = Mix_PlayChannel(-1,Sounds[SoundId],0);
    Mix_Volume(Id,Volume);
}

/// ///// ///// // save stuff // ///// ///// ///

void Save(){
    char Data;
    FILE *File;
    File = fopen("SavedDate.save","w");
    int I;
    for(I=0; I<10; I++){
        Data = hats[I].IsUnlocked;
        fprintf(File,"%c",Data);
    }
    fclose(File);
}

void Load(){
    FILE *File;
    File = fopen("SavedDate.save","r");
    char line[10];
    fread(&line,1,10,File);
    int I;
    for(I=0; I<10; I++){
        hats[I].IsUnlocked=line[I];
    }
    fclose(File);
}

int UnlockSomthing(int Type, int Id, char String[30]){
    if(UltraHard==1){return 0;}

    if(Type==0){
        if(hats[Id].IsUnlocked==0){
            hats[Id].IsUnlocked=1;
            Save();
            OnMenu=2;
            Menu=50;
            LoadMenu(50);
            FinishRoom();
            strcpy((char*)TempItemName,String);
            int I;
            for(I=0; I<30; I++){
                //Enemys[I].Alive=0;
            }
        }else{
            return 1;
        }
    }

    return 0;
}


void Save2(){
    int Data2[30];
    FILE *File;
    File = fopen("SavedGame.save","wb");
    FILE *File2;
    File2 = fopen("SavedPlayer.save","wb");

    Data2[0]=Speed;
    Data2[1]=JumpPower;
    Data2[2]=Damage;
    Data2[3]=Health;
    Data2[4]=MaxHealth;
    Data2[5]=Sheild;
    Data2[6]=MaxSheild;
    Data2[7]=Ammo;
    Data2[8]=MaxAmmo;
    Data2[9]=Charge;
    Data2[10]=MaxCharge;
    Data2[11]=ProAim;
    Data2[12]=FireRate;
    Data2[13]=RapidFire;
    Data2[14]=SaftyPlat;
    Data2[15]=RoomAmount;
    Data2[16]=X;
    Data2[17]=Y;
    Data2[18]=MapX;
    Data2[19]=MapY;
    Data2[20]=Mode;
    Data2[21]=HatId;
    Data2[22]=UsableId;
    Data2[23]=ChargeWeapon;
    Data2[24]=SecondaryId;
    Data2[25]=Weapon;
    Data2[26]=JumpLevel;
    Data2[27]=CanSwim;
    Data2[28]=PlayerWeaponId;
    Data2[29]=BulletImage;

    fwrite(Data2,sizeof(int),30,File2);

    /// /////////////////////////////// ///

    int I;
    for(I=0; I<RoomAmount; I++){
        Rooms[I].Id=knownRooms[Rooms[I].X][Rooms[I].Y];
    }

    fwrite(&Rooms,sizeof(Room),RoomAmount,File);

    for(I=0; I<RoomAmount; I++){
        Rooms[I].Id=I;
    }

    fclose(File);
    fclose(File2);
}

void Load2(){
    FILE *File;
    File = fopen("SavedGame.save","rb");
    FILE *File2;
    File2 = fopen("SavedPlayer.save","rb");
    int Info[30];
    int I;

    fread(&Info,sizeof(int),30,File2);

    Speed       =Info[0];
    JumpPower   =*((int*)(&(Info[1])));
    Damage      =*((int*)(&(Info[2])));
    Health      =*((int*)(&(Info[3])));
    MaxHealth   =*((int*)(&(Info[4])));
    Sheild      =*((int*)(&(Info[5])));
    MaxSheild   =*((int*)(&(Info[6])));
    Ammo        =*((int*)(&(Info[7])));
    MaxAmmo     =*((int*)(&(Info[8])));
    Charge      =*((int*)(&(Info[9])));
    MaxCharge   =*((int*)(&(Info[10])));
    ProAim      =*((int*)(&(Info[11])));
    FireRate    =*((int*)(&(Info[12])));
    RapidFire   =*((int*)(&(Info[13])));
    SaftyPlat   =*((int*)(&(Info[14])));
    RoomAmount  =*((int*)(&(Info[15])));
    X           =Info[16];
    Y           =Info[17];
    MapX        =*((int*)(&(Info[18])));
    MapY        =*((int*)(&(Info[19])));
    Mode        =Info[20];
    HatId       =Info[21];
    UsableId    =Info[22];
    ChargeWeapon=Info[23];
    SecondaryId =Info[24];
    Weapon      =Info[25];
    JumpLevel   =Info[26];
    CanSwim     =Info[27];
    PlayerWeaponId =Info[28];
    BulletImage =Info[29];

    if(Health<=0){
        OnMenu=0;
    }

    /// ///////////////////////////////// ///

    fread(&Rooms,sizeof(Room),RoomAmount,File);

    for(I=0; I<RoomAmount; I++){
        if(Rooms[I].X<250&&Rooms[I].Y<250){
            RoomPos[Rooms[I].X][Rooms[I].Y]=I;
            RoomPair[Rooms[I].X][Rooms[I].Y]=Rooms[Rooms[I].Pair];
            knownRooms[Rooms[I].X][Rooms[I].Y]=Rooms[I].Id;
            Rooms[I].Id=I;
        }
    }

    fclose(File);
    fclose(File2);
}

/// ///// ///// // not save stuff // ///// ///// ///

void KillAll(){
    int I;
    for(I=0; I<50; I++){
        if(I<30){
            Enemys[I].Alive=0;
        }
        Bullets[I].Alive=0;
    }
}





#endif

