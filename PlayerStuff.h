#ifndef PLAYERSTUFF
#define PLAYERSTUFF

int TL,BL,TR,BR,BL2,BR2;
int T,B,L,R;
short MapX=30;
short MapY=30;
int NextX,NextY;
int WalkTimer;

void switchRoom(int Direct){
    if(MapLevel>0){knownRooms[MapX][MapY]=1;}

    for(I=0; I<30; I++){
        Enemys[I].Alive=0;
    }
    for(I=0; I<30; I++){
        Bullets[I].Alive=0;
    }

    Boss1.Alive=0;

    Rooms[RoomPos[OrginX][OrginY]].DropId=0;
    for(I=0; I<10; I++){
        if(Drops[I].Alive==1){
            Rooms[RoomPos[OrginX][OrginY]].DropX=Drops[I].X;
            Rooms[RoomPos[OrginX][OrginY]].DropY=Drops[I].Y;
            Rooms[RoomPos[OrginX][OrginY]].DropId=Drops[I].Type;
        }
        Drops[I].Alive=0;
    }
    Item.Used=1;

    /// finisher ///
	int FinishNow=0;
	if(FinishNow==1&&1==2){
		if(Rooms[RoomPos[MapX][MapY]].BigRoom<1){
			Rooms[RoomPos[MapX][MapY]].Finished=1;
		}else{
			Rooms[RoomPos[OrginX][OrginY]].Finished=1;
			if(Rooms[RoomPos[MapX][MapY]].BigRoom<7){
				Rooms[RoomPos[OrginX+1][OrginY]].Finished=1;
			}
			if(Rooms[RoomPos[MapX][MapY]].BigRoom<5||Rooms[RoomPos[MapX][MapY]].BigRoom==7||Rooms[RoomPos[MapX][MapY]].BigRoom==8){
				Rooms[RoomPos[OrginX][OrginY+1]].Finished=1;
            }
			if(Rooms[RoomPos[MapX][MapY]].BigRoom<5){
				Rooms[RoomPos[OrginX+1][OrginY+1]].Finished=1;
			}
		}
	}

    int NewX=MapX;
    int NewY=MapY;

    if(Direct==1){
        NewY-=1;
        Y=GetRoom(MapX,NewY).Height-TileSize;
    }else if(Direct==2){
        NewX+=1;
        X=1;
    }else if(Direct==3){
        NewY+=1;
        Y=1;
    }else if(Direct==4){
        NewX-=1;
        X=GetRoom(NewX,MapY).Width-TileSize;
    }

    if(RoomPos[NewX][NewY]==0){
        NewX=RoomPair[MapX][MapY].X;
        NewY=RoomPair[MapX][MapY].Y;
        if(Direct==1){
            Y=GetRoom(NewX,NewY).Height-TileSize;
        }
    }

    /// sound ///
    if(LastArea==100){
        Mix_Volume(1,Volume);
        Mix_FadeInChannel(1,Music[GetRoom(NewX,NewY).Area+1],-1,1500);
        LastArea=GetRoom(NewX,NewY).Area;
    }

    if(GetRoom(NewX,NewY).Area!=LastArea){
        LastArea=100;
        Mix_Volume(1,Volume);
        Mix_FadeOutChannel(1,800);
    }
    /// ///// ///

    if(GetRoom(NewX,NewY).BigRoom<1){
        if(OrginX<MapX&&Direct==1){
            X-=Width;
        }
        if(OrginX<MapX&&Direct==3){
            X-=Width;
        }
        if(OrginY<MapY&&Direct==2){
            Y-=Height;
        }
        if(OrginY<MapY&&Direct==4){
            Y-=Height;
        }
    }

    if(GetRoom(MapX,MapY).BigRoom<1&&GetRoom(NewX,NewY).BigRoom>0){
        if(Direct==2){
            if(GetRoom(NewX,NewY).BigRoom==3||GetRoom(NewX,NewY).BigRoom==8){
                Y+=Height;
            }
        }else if(Direct==4){
            if(GetRoom(NewX,NewY).BigRoom==4||GetRoom(NewX,NewY).BigRoom==8){
                Y+=Height;
            }
        }else if(Direct==3){
            if(GetRoom(NewX,NewY).BigRoom==2||GetRoom(NewX,NewY).BigRoom==6){
                X+=Width;
            }
        }else if(Direct==1){
            if(GetRoom(NewX,NewY).BigRoom==4||GetRoom(NewX,NewY).BigRoom==6){
                X+=Width;
            }
        }
    }

    if(Rooms[RoomPos[NewX][NewY]].BigRoom==2||Rooms[RoomPos[NewX][NewY]].BigRoom==4||Rooms[RoomPos[NewX][NewY]].BigRoom==6){
        NewX-=1;
    }
    if(Rooms[RoomPos[NewX][NewY]].BigRoom==3||Rooms[RoomPos[NewX][NewY]].BigRoom==4||Rooms[RoomPos[NewX][NewY]].BigRoom==8){
        NewY-=1;
    }

    if(OrginX-NewX!=0&&(Direct+1)%2==0&&GetRoom(NewX,NewY).BigRoom>0&&GetRoom(MapX,MapY).BigRoom>0){
        X+=Width*(OrginX-NewX);
    }
    if(OrginY-NewY!=0&&(Direct)%2==0&&GetRoom(NewX,NewY).BigRoom>0&&GetRoom(MapX,MapY).BigRoom>0){
        Y+=Height*(OrginY-NewY);
    }

    MapX=NewX;
    MapY=NewY;

    if(MapLevel>0){knownRooms[MapX][MapY]=1;}

    Area = Rooms[RoomPos[MapX][MapY]].Area;

    if(RoomPos[NewX][NewY]!=0){
        loadMap(Rooms[RoomPos[NewX][NewY]].Type,Rooms[RoomPos[NewX][NewY]].Finished);

        OrginX=MapX;
        OrginY=MapY;

        NextX=X+(int)SpdX;
        NextY=Y+(int)SpdY;
    }

    OffsetX=Width/2-TileSize-X+200;
    OffsetY=Height/2-TileSize-Y;
}

void SetRoomMap(){
    Item.Used=1;

    for(I=0; I<30; I++){
        Enemys[I].Alive=0;
    }
    for(I=0; I<30; I++){
        Bullets[I].Alive=0;
    }

    Boss1.Alive=0;

    if(RoomPos[MapX][MapY]!=0){
        loadMap(Rooms[RoomPos[MapX][MapY]].Type,Rooms[RoomPos[MapX][MapY]].Finished);

        OrginX=MapX;
        OrginY=MapY;

        Area = Rooms[RoomPos[MapX][MapY]].Area;
    }

}

void RenderPlayer(){

    if(WalkTimer<24){
        WalkTimer+=1;
    }else{
        WalkTimer=0;
    }


    if(Health>0){
        if(SpdX!=0){
            Rotated2(WalkTimer/8+1,X+OffsetX,Y+OffsetY,TileSize,TileSize,(Direction+1)/2);
            PlayerAnim2=WalkTimer/8+1;
        }else{
            Rotated2(1,X+OffsetX,Y+OffsetY,TileSize,TileSize,(Direction+1)/2);
            WalkTimer=0;
            PlayerAnim2=1;
        }

        if(Direction!=0){
            if(ProAim==0){
                Rotated2(PlayerWeaponId+W-S,X+OffsetX,Y+OffsetY,TileSize,TileSize,(Direction+1)/2);
                PlayerAnim=PlayerWeaponId+W-S+(Direction+1)/2*100;
            }else{
                int Direct;
                int RS, RN;
                RS=Y-MouseY+OffsetY;
                RN=X-MouseX+OffsetX;
                if(RN!=0){
                    if(abs((float)abs(RS)/abs(RN))>=1){
                        if(RS>0){
                            Direct=1;
                            W=1;
                        }else{
                            Direct=-1;
                            S=1;
                        }
                    }else{
                        Direct=0;
                        W=0;
                        S=0;
                    }
                }else{
                    Direct=1;
                    W=1;
                }
                if(RN<=0){Direction=1;}
                if(RN>0){Direction=-1;}
                Rotated2(PlayerWeaponId+Direct,X+OffsetX,Y+OffsetY,TileSize,TileSize,(Direction+1)/2);
                PlayerAnim=PlayerWeaponId+Direct+(Direction+1)/2*100;
            }
        }else{
            PlayerAnim=0;
            DrawImgP(0,X+OffsetX,Y+OffsetY,TileSize,TileSize);
        }

        DrawHat(hats[(int) HatId].ImageId , X + 14 +OffsetX, Y - 24 +OffsetY, TileSize/2, TileSize);
    }else{
        DrawImgP(9, X+OffsetX-TileSize*0.3, Y+OffsetY-TileSize*0.3, TileSize*1.3, TileSize*1.3);
        DrawHat(hats[(int) HatId].ImageId , X + 14 +OffsetX, Y + TileSize/2 +OffsetY, TileSize/2, TileSize);

        if(OnMenu==1){
            OnMenu=2;
            Menu=51;
            LoadMenu(51);
            if(Corrupted==0){
                strcpy((char*)TempItemName,"U died, sad n00b.");
                Save();
                Save2();
            }else{
                Save();
                Save2();
                char String[100];
                int I;
                for(I=0; I<1000; I++){
                    String[I]=Random(20,150);
                }
                strcpy((char*)TempItemName,(const char*)String);
            }
        }
    }

    if(ShootEffect>0&&Direction!=0){
        int TimesFive, MinusTen;

        ShootEffect+=1;

        TimesFive=ShootEffect*3;
        MinusTen=14-ShootEffect*2;

        color(255,255,255,255);
        FillRect(ShootX+OffsetX +TimesFive +X,ShootY+OffsetY -TimesFive +Y,MinusTen,MinusTen);
        FillRect(ShootX+OffsetX -TimesFive +X,ShootY+OffsetY +TimesFive +Y,MinusTen,MinusTen);
        FillRect(ShootX+OffsetX +TimesFive +X,ShootY+OffsetY +TimesFive +Y,MinusTen,MinusTen);
        FillRect(ShootX+OffsetX -TimesFive +X,ShootY+OffsetY -TimesFive +Y,MinusTen,MinusTen);
        if(ShootEffect>7){
            ShootEffect=0;
        }
    }

    if(LandEffect>0){
        int MinusTen, TimeTen;

        LandEffect+=1;

        MinusTen = 14-LandEffect*2;
        TimeTen = LandEffect*4;

        color(255,255,255,255);
        FillRect(X+TileSize/2+OffsetX+LandEffect-7+TimeTen ,Y+TileSize+OffsetY+LandEffect-8 ,MinusTen,MinusTen);
        FillRect(X+TileSize/2+OffsetX+LandEffect-7-TimeTen ,Y+TileSize+OffsetY+LandEffect-8 ,MinusTen,MinusTen);

        if(LandEffect>7){
            LandEffect=0;
        }
    }

    if(ItemTitle>=1){
        ItemTitle-=1;

        int LoopAmount=40;
        if(ItemTitle<=40){
            LoopAmount=(ItemTitle);
        }

        int I;
        for(I=0; I<LoopAmount; I++){
            int Size = 15*I;
            color(255,255,255,10);
            FillRect(Width/2+200-Size/2, 40, Size, 100);
        }

        if(ItemTitle>30){
            DrawTextCenter(TempItemName, Width/2+200, 90, 20, 20);
        }
    }
}

void updateCollsionA(int XX, int YY){
    T=Round(YY-TileSize/2+1,TileSize);
    B=Round(YY+TileSize/2,TileSize);
    L=Round(XX-TileSize/2+1,TileSize);
    R=Round(XX+TileSize/2,TileSize);
    TL=GetTileStuff(L,T);
    BL=GetTileStuff(L,B);
    TR=GetTileStuff(R,T);
    BR=GetTileStuff(R,B);
    BL2=BL;
    BR2=BR;

    if(TL==2){TL=1;}
    if(BL==2){BL=1;}
    if(TR==2){TR=1;}
    if(BR==2){BR=1;}

    int B2=Round(YY+TileSize/2*3-SpdY-1,TileSize);
    if(BL==4&&GetTileStuff(L,B2)==4){BL=1;}
    if(BR==4&&GetTileStuff(R,B2)==4){BR=1;}
}

void playerStuff(){
    if(First==0){
        First=1;
        X=Width/2-TileSize/2;
        Y=Height/2-TileSize/2;
        OrginX=MapX;
        OrginY=MapY;
    }

    //////////////////stuff that should of been at the top but would let me//////////////////

    if(GetRoom(MapX,MapY).BigRoom>0){
        if(X>GetRoom(OrginX,OrginY).Width/2&&GetRoom(MapX,MapY).BigRoom<7){ MapX=OrginX+1;}else{ MapX=OrginX; }
        if(Y>GetRoom(OrginX,OrginY).Height/2&&GetRoom(MapX,MapY).BigRoom!=5&&GetRoom(MapX,MapY).BigRoom!=6){ MapY=OrginY+1;}else{ MapY=OrginY; }
    }

    int SpdX2, SpdY2;

    if(MapArray[(X+TileSize/2)/TileSize][(Y+TileSize/2)/TileSize]==5){
        if(CanSwim==0){
            SpdX2=SpdX/2;
            SpdY2=SpdY/2;
        }else{
            if(Falling==0){
                SpdX2=SpdX/2;
                SpdY2=SpdY/2;
            }else{
                SpdX2=SpdX/5*4;
                SpdY2=SpdY/3;
            }
        }
    }else{
        SpdX2=SpdX;
        SpdY2=SpdY;
    }


    NextX=X+(int)SpdX2;
    NextY=Y+(int)SpdY2;

    if(NextX<0&&GetRoom(MapX,MapY).Width>1){
        switchRoom(4);
        if(Rooms[RoomPos[MapX][MapY]].Finished==0){X+=-TileSize;}
    }else if(NextX>GetRoom(MapX,MapY).Width-TileSize&&GetRoom(MapX,MapY).Width>1){
        switchRoom(2);
        if(Rooms[RoomPos[MapX][MapY]].Finished==0){X+=TileSize;}
    }

    if(NextY<0){
        switchRoom(1);
        if(Rooms[RoomPos[MapX][MapY]].Finished==0){Y+=-TileSize;}
    }else if(NextY>GetRoom(MapX,MapY).Height-TileSize){
        switchRoom(3);
        if(Rooms[RoomPos[MapX][MapY]].Finished==0){Y+=TileSize;}
    }

    /// /////// - tile collision - /////// ///
    updateCollsionA(NextX,Y);
    if(SpdX2<0){
        if(TL==1||BL==1){
            SpdX=0;
            SpdX2=0;
            X=Round(X,TileSize);
        }else{
            X+=(int)SpdX2;
        }
    }
    updateCollsionA(NextX,Y);
    if(SpdX2>0){
        if(TR==1||BR==1){
            SpdX=0;
            SpdX2=0;
            X=Round(X,TileSize);
        }else{
            X+=(int)SpdX2;
        }
    }

    updateCollsionA(X,NextY);
    if(SpdY2<0){
        if(TL==1||TR==1){
            SpdY=0;
            SpdY2=0;
            Y=Round(Y,TileSize);
        }else{
            Y+=(int)SpdY2;
        }
    }
    if(SpdY2>0){
        if(BR==1||BL==1){
            if(SpdY2>0){
                //Mix_PlayChannel(2, LandSound, 0);
                PlaySoundPro(1);
                LandEffect=1;
            }

            SpdY=0;
            SpdY2=0;
            Y=Round(Y,TileSize);
            Falling=0;
        }else{
            Y+=(int)SpdY2;
        }
    }

    /// ////// ////// ///
    int I, ShouldFall=0;
    for(I=0; I<30; I++){
        if(intersept(X,Y,TileSize,TileSize+5,Enemys[I].X,Enemys[I].Y,TileSize,TileSize)&&Enemys[I].Type>=20&&Enemys[I].Type<=24&&Enemys[I].Alive==1){
            int X2, Y2;
            int Number;
            X2=X-Enemys[I].X;
            Y2=Y-Enemys[I].Y;

            updateCollsionA(X,Y+1);
            if(((BL!=1&&BR!=1)||(Enemys[I].SpdY<0&&X-Enemys[I].X>0))){
                Number=1;
            }

            if(abs(X2)<abs(Y2) &&Y>Enemys[I].Y&&Number==1){
                Y=Enemys[I].Y+TileSize+1;
                SpdY=1;
            }else if(abs(Y2)<abs(X2) &&X<Enemys[I].X){
                X=Enemys[I].X-TileSize;
                SpdX=0;
            }else if(abs(X2)<abs(Y2)&&Number==1){
                updateCollsionA(X,Y-1);
                if(TL!=1&&TR!=1){
                    Y=Enemys[I].Y-TileSize;
                    SpdY=0;
                    Falling=0;
                    ShouldFall=1;
                }
            }else if(abs(Y2)<abs(X2) &&X>Enemys[I].X){
                X=Enemys[I].X+TileSize;
                SpdX=0;
            }
        }
    }
    /// /////// ////// ///

    updateCollsionA(X,Y+1);
    if(BL!=1&&BR!=1&&ShouldFall==0){//&&BL!=4&&BR!=4
        Falling=1;
        SpdY+=1;
    }else{
        Falling=0;
    }
    if((BR2==4||BR<=0||BR==5)&&(BL2==4||BL<=0||BL==5)&&S2==1&&SpdY>=0&&BL+BR!=0&&BL+BR!=10&&BL+BR!=5&&ShouldFall==0){
        Y+=2;
        Falling=1;
    }

    /// stuff ///

    RenderPlayer();

    SheildRecharge+=1;
    if(SheildRecharge==50||SheildRecharge==100||SheildRecharge==150){
        if(Sheild<MaxSheild){
            Sheild+=(int)((float)MaxSheild/25);
        }
        if(SheildRecharge>=150){
            SheildRecharge=0;
            Charge-=1;
        }
    }

    /// bullet collision ///

    int II;
    for(II=0; II<30; II++){
        if(intersept(X,Y,TileSize,TileSize, Bullets[II].X-Bullets[II].SpdX, Bullets[II].Y-Bullets[II].SpdY, Bullets[II].Width, Bullets[II].Height)
        ||intersept(X,Y,TileSize,TileSize, Bullets[II].X+Bullets[II].SpdX, Bullets[II].Y+Bullets[II].SpdY, Bullets[II].Width, Bullets[II].Height)){
            if(Bullets[II].Enemy==1&&Bullets[II].Alive==1){
                DamagePlayer(200);
                Bullets[II].Alive=0;
            }
        }
    }
}


#endif
