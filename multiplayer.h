#ifndef MULTIPLAYER
#define MULTIPLAYER

void StartGame();

void Host(){
    if(IsServer!=0){return;}

    IPaddress Ip;
    SDLNet_ResolveHost(&Ip,NULL,9351);
    server = SDLNet_TCP_Open(&Ip);

    IsServer=1;
}

void Join(){
    if(IsServer!=0){return;}

    IPaddress Ip;
    SDLNet_ResolveHost(&Ip,"192.168.1.214",9351); ///127.0.0.1
    client = SDLNet_TCP_Open(&Ip);

    IsServer=2;
}

int DataAmount=7;

void DoMulti(){
    short In[DataAmount],Out[DataAmount];
    Out[0] = X;
    Out[1] = Y;
    Out[2] = RoomPos[OrginX][OrginY];
    Out[3] = HatId;
    Out[4] = PlayerAnim;
    Out[5] = PlayerAnim2;
    Out[6] = LastShot;
    SDLNet_TCP_Send(client,(short*) Out,sizeof(short)*DataAmount);
    if(LastShot!=0&&RoomPos[OrginX][OrginY]==CRoomId){
        NormalBullet TempBullet = Bullets[(int) LastShot-1];
        SDLNet_TCP_Send(client, &TempBullet,sizeof(NormalBullet));
        LastShot=0;
    }

    if(IsServer==1&&RoomPos[OrginX][OrginY]==CRoomId){
        short Info[90];
        int I;
        for(I=0; I<30; I++){
            Info[I*3]=Enemys[I].X;
            Info[I*3+1]=Enemys[I].Y;
            Info[I*3+2]=Enemys[I].Alive;
        }

        SDLNet_TCP_Send(client,(short*) Info,sizeof(short)*90);
    }

    /// In ///
    SDLNet_TCP_Recv(client,In,sizeof(short)*DataAmount);
    ClieX = In[0];
    ClieY = In[1];
    CRoomId = In[2];

    if(In[0]==-175&&In[1]==69){
        Seed=In[2];
        StartGame();
        return;
    }

    if(In[2]!=RoomPos[OrginX][OrginY]){return;}

    /// drawing ///
    if(In[4]>=100){
        Rotated2(In[5],In[0]+OffsetX,In[1]+OffsetY,TileSize,TileSize,1);
        Rotated2(In[4]-100,In[0]+OffsetX,In[1]+OffsetY,TileSize,TileSize,1);
    }else{
        Rotated2(In[5],In[0]+OffsetX,In[1]+OffsetY,TileSize,TileSize,0);
        Rotated2(In[4],In[0]+OffsetX,In[1]+OffsetY,TileSize,TileSize,0);
    }
    DrawHat(hats[In[3]].ImageId , ClieX + 14 +OffsetX, ClieY - 24 +OffsetY, TileSize/2, TileSize);

    /// bullets ///
    if(In[6]!=0){
        NormalBullet ClientBullet;
        SDLNet_TCP_Recv(client,&ClientBullet,sizeof(NormalBullet));
        int Held = ShootSpclBullet2(0,0,0,0,0,0,0,0,0);
        Bullets[Held] = ClientBullet;
    }

    /// enemy sync ///
    if(IsServer==2){
        short Info[90];
        int I;
        SDLNet_TCP_Recv(client,Info,sizeof(short)*90);

        for(I=0; I<30; I++){
            Enemys[I].X=Info[I*3];
            Enemys[I].Y=Info[I*3+1];
            Enemys[I].Alive=Info[I*3+2];
        }
    }
}

void RunMulti(){
    if(IsServer==0){return;}

    if(IsServer==1){
        if(client){
            DoMulti();
        }else{
            client = SDLNet_TCP_Accept(server);

            if(client){
                short IntArray[DataAmount];
                IntArray[0] = -175;
                IntArray[1] = 69;
                IntArray[2] = Seed;

                SDLNet_TCP_Send(client,(short*) IntArray,sizeof(short)*DataAmount);
            }
        }
    }else if(IsServer==2){
        DoMulti();
    }
}

#endif
