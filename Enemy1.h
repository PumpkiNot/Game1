#ifndef ENEMY1
#define ENEMY1

int CheckCollsions(int *X, int *Y, int *SpdX, int *SpdY, int *Falling, int HasGravity, int Size);
int GetAnimation(int Count, int Scaler);

Room GetRoom(int ZXC, int TYU);

void FinishRoom(){
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

void FinishRoom2(int Num){
    if(Rooms[RoomPos[MapX][MapY]].BigRoom<1){
        Rooms[RoomPos[MapX][MapY]].Finished=Num;
    }else{
        Rooms[RoomPos[OrginX][OrginY]].Finished=Num;
        if(Rooms[RoomPos[MapX][MapY]].BigRoom<7){
            Rooms[RoomPos[OrginX+1][OrginY]].Finished=Num;
        }
        if(Rooms[RoomPos[MapX][MapY]].BigRoom<5||Rooms[RoomPos[MapX][MapY]].BigRoom==7||Rooms[RoomPos[MapX][MapY]].BigRoom==8){
            Rooms[RoomPos[OrginX][OrginY+1]].Finished=Num;
        }
        if(Rooms[RoomPos[MapX][MapY]].BigRoom<5){
            Rooms[RoomPos[OrginX+1][OrginY+1]].Finished=Num;
        }
    }
}

void OpenRoom(){
    int V=0, Number=1;
    for(V=0; V<30; V++){
        if(Enemys[V].Alive==1&&Enemys[V].Sleeping==0){
            break;
        }else if(Enemys[V].Sleeping==1&&Enemys[V].Type<20&&Enemys[V].Alive==1){
            Number=2;
        }
        if(V==29&&Rooms[RoomPos[MapX][MapY]].BigRoom==0&&Boss1.Alive==0){
            if(Random(2,3)==3){
                if(MaxSheild==1){
                    SpawnDrop(1, Random(2,4));
                }else{
                    SpawnDrop(1, Random(1,4));
                }
            }

            int O=0,OO=0;
            for(O=0; O<15; O++){
                for(OO=0; OO<10; OO++){
                    if(OO==9){
                        if(MapArray[O][OO]==2){MapArray[O][OO]=4*SaftyPlat;}
                    }else{
                        if(Area!=3){
                            if(MapArray[O][OO]==2){MapArray[O][OO]=0;}
                        }else{
                            if(MapArray[O][OO]==2){MapArray[O][OO]=5;}
                        }
                    }
                }
            }
            FinishRoom2(Number);

        }else if(V==29&&Rooms[RoomPos[MapX][MapY]].BigRoom!=0&&Boss1.Alive==0){
            if(Random(2,3)==3){
                if(MaxSheild==1){
                    SpawnDrop(1, Random(2,4));
                }else{
                    SpawnDrop(1, Random(1,4));
                }
            }

            int O=0,OO=0;
            for(O=0; O<30; O++){
                for(OO=0; OO<20; OO++){
                    if(OO==19||OO==9){
                        if(MapArray[O][OO]==2){MapArray[O][OO]=4*SaftyPlat;}
                    }else{
                        if(Area!=3){
                            if(MapArray[O][OO]==2){MapArray[O][OO]=0;}
                        }else{
                            if(MapArray[O][OO]==2){MapArray[O][OO]=5;}
                        }
                    }
                }
            }
            FinishRoom2(Number);
        }
    }
}

int SpawnEnemy(int Tipe){
    int I;
    for(I=0; I<sizeof(Enemys)/sizeof(NormalEnemy); I++){
        if(Enemys[I].Alive!=1){
            Enemys[I].X=X;
            Enemys[I].Y=Y;
            Enemys[I].SpdX=0;
            Enemys[I].SpdY=0;
            Enemys[I].Alive=1;
            Enemys[I].Falling=1;
            Enemys[I].Type=Tipe;
            Enemys[I].Spawning=0;
            Enemys[I].Walking=0;
            Enemys[I].Counter=0;
            Enemys[I].MaxSpeed=5;
            Enemys[I].Sleeping=0;
            Enemys[I].Special=0;
            Enemys[I].Damage=10;
            Enemys[I].AttackTimer=Random(0,40);
            Enemys[I].Friend=0;
            if(Tipe==0){
                Enemys[I].Health=50;
            }else if(Tipe==1){
                Enemys[I].Health=80;
            }else if(Tipe==2){
                Enemys[I].Health=80;
            }else if(Tipe==3){
                Enemys[I].Health=70;
                Enemys[I].Sleeping=1;
            }else if(Tipe==4){
                Enemys[I].Health=90;
            }else if(Tipe==25){
                Enemys[I].Health=1000;
                Enemys[I].Friend=1;
            }else if(Tipe==26){
                Enemys[I].Health=1000;
                Enemys[I].Friend=1;
                Enemys[I].Damage=8;
            }else if(Tipe>=20&&Tipe<=24){
                Enemys[I].Health=100;
                Enemys[I].Sleeping=1;
                Enemys[I].AttackTimer=0;
            }
            if(Tipe==21){
                Enemys[I].SpdY=-3;
            }else if(Tipe==22){
                Enemys[I].SpdX=3;
            }else if(Tipe==23){
                Enemys[I].SpdY=3;
            }else if(Tipe==24){
                Enemys[I].SpdX=-3;
            }

            if(Mode==0){
                Enemys[I].Health=Enemys[I].Health/4*3;
            }else if(Mode==2){
                if(Tipe<Area){
                    Enemys[I].Health+=30*(float)(Area-Tipe)/2;
                }
            }else if(Mode==3){
                if(Tipe<Area){
                    Enemys[I].Health*=1+(Area-Tipe);
                }
            }

            if(Menu<10){
                Enemys[I].Spawning=50;
            }

            return I;
            break;
        }
    }
    return 0;
}

int SpawnSpclEnemy(int Tipe, int Type2){
    int I;
    for(I=0; I<sizeof(Enemys)/sizeof(NormalEnemy); I++){
        if(Enemys[I].Alive==0){
            Enemys[I].X=X;
            Enemys[I].Y=Y;
            Enemys[I].SpdX=0;
            Enemys[I].SpdY=0;
            Enemys[I].Alive=1;
            Enemys[I].Falling=1;
            Enemys[I].Type=Tipe;
            Enemys[I].Spawning=0;
            Enemys[I].Walking=0;
            Enemys[I].Counter=0;
            Enemys[I].Special=Type2;
            if(Type2==1){
                if(Tipe==0){
                    Enemys[I].Health=20;
                }else if(Tipe==1){
                    Enemys[I].Health=40;
                }
                Enemys[I].MaxSpeed=8;
            }
            else if(Type2==2){
                if(Tipe==0){
                    Enemys[I].Health=250;
                }else if(Tipe==1){
                    Enemys[I].Health=300;
                }
                Enemys[I].MaxSpeed=3;
            }
            return I;
            break;
        }
    }
    return 0;
}

int II;

void EnemyUpdate(int AA){
    int Held3 = abs(X-Enemys[AA].X);
    int PlayerX=X, PlayerY=Y;
    int X=PlayerX,Y=PlayerY;

    if(Menu<10){
        Held3=100000;
    }

    int I;
    for(I=0; I<30; I++){
        NormalEnemy E = Enemys[I];

        if(I==AA||E.Alive!=1||E.Friend==0){
            continue;
        }

        if(abs(E.X-Enemys[AA].X)<Held3){
            X=E.X;
            Y=E.Y;
        }
    }

    if(abs(ClieX-Enemys[AA].X)<Held3&&IsServer!=0){
        if(CRoomId==RoomPos[OrginX][OrginY]){
            X=ClieX;
            Y=ClieY;
        }
    }

    if(Enemys[AA].Spawning>=50){
        if(Enemys[AA].Type!=2&&(Enemys[AA].Type<20||Enemys[AA].Type>24)){
            CheckCollsions((int*) &Enemys[AA].X,(int*) &Enemys[AA].Y,(int*) &Enemys[AA].SpdX,(int*) &Enemys[AA].SpdY,(int*) &Enemys[AA].Falling,1,TileSize);
        }
        /// bullets ///
        for(II=0; II<50; II++){
            if(Bullets[II].Alive==1&&Enemys[AA].Friend==0){
                if(intersept(Enemys[AA].X,Enemys[AA].Y,TileSize,TileSize, Bullets[II].X-Bullets[II].SpdX, Bullets[II].Y-Bullets[II].SpdY, Bullets[II].Width, Bullets[II].Height)
                   ||intersept(Enemys[AA].X,Enemys[AA].Y,TileSize,TileSize, Bullets[II].X+Bullets[II].SpdX, Bullets[II].Y+Bullets[II].SpdY, Bullets[II].Width, Bullets[II].Height)){
                        if(Bullets[II].Enemy==0&&Enemys[AA].Sleeping==0){

                        Enemys[AA].Health-=Bullets[II].Damage;

                        if(Enemys[AA].Health<1){
                            Enemys[AA].Alive=0;
                            Enemys[AA].X=0;
                            Enemys[AA].Y=0;
                         }

                        OpenRoom();

                        if(Enemys[AA].Special!=1){
                            RemoveBullet(II,Secondary[Bullets[II].Type].BlastRadius,Bullets[II].Damage);
                        }
                    }
                }
            }
        }

        if(Enemys[AA].Type==0){

            if(X+15<Enemys[AA].X&&Enemys[AA].SpdX>Enemys[AA].MaxSpeed*-1){
                Enemys[AA].SpdX-=2;
            }else if(X-15>Enemys[AA].X&&Enemys[AA].SpdX<Enemys[AA].MaxSpeed){
                Enemys[AA].SpdX+=2;
            }else{
                if(Enemys[AA].SpdX>0){Enemys[AA].SpdX-=2;}
                if(Enemys[AA].SpdX<0){Enemys[AA].SpdX+=2;}
                if(Enemys[AA].SpdX==0&&Enemys[AA].SpdY==0&&Enemys[AA].Falling==0){Enemys[AA].SpdY=-15;}
            }

        }
        else if(Enemys[AA].Type==1){

            Point temp;
            temp = caulcSpeed(X,Y,Enemys[AA].X,Enemys[AA].Y,Enemys[AA].MaxSpeed);
            Enemys[AA].SpdX=temp.X;
            Enemys[AA].SpdY=temp.Y;

        }
        else if(Enemys[AA].Type==2){

            Enemys[AA].AttackTimer+=1;
            if(Enemys[AA].AttackTimer>=150){
                EnemyShoot(AA);
                Enemys[AA].AttackTimer=0;
            }
        }
        else if(Enemys[AA].Type==3&&Enemys[AA].Sleeping==0){

            if(X+15<Enemys[AA].X&&Enemys[AA].SpdX>Enemys[AA].MaxSpeed*-1){
                Enemys[AA].SpdX-=2;
            }else if(X-15>Enemys[AA].X&&Enemys[AA].SpdX<Enemys[AA].MaxSpeed){
                Enemys[AA].SpdX+=2;
            }else{
                if(Enemys[AA].SpdX>0){Enemys[AA].SpdX-=2;}
                if(Enemys[AA].SpdX<0){Enemys[AA].SpdX+=2;}
                if(Enemys[AA].SpdX==0&&Enemys[AA].SpdY==0&&Enemys[AA].Falling==0){Enemys[AA].SpdY=-15;}
            }
        }
        else if(Enemys[AA].Type==4){
            Enemys[AA].AttackTimer=Enemys[AA].AttackTimer+1;
            if(Enemys[AA].AttackTimer>=100){
                Enemys[AA].AttackTimer=0;

                if(Enemys[AA].X>=X){
                    Enemys[AA].SpdY=-15;
                    Enemys[AA].SpdX=-10;
                }else{
                    Enemys[AA].SpdY=-15;
                    Enemys[AA].SpdX=10;
                }
            }

            if(Enemys[AA].Falling==0){
                if(Enemys[AA].SpdX>0){
                    Enemys[AA].SpdX=Enemys[AA].SpdX-2;
                }else if(Enemys[AA].SpdX<0){
                    Enemys[AA].SpdX=Enemys[AA].SpdX+2;
                }
            }
        }
        else if(Enemys[AA].Type==25||Enemys[AA].Type==26){       /// /////////////////////////////////////////////////////////
            int Shortest=100000, Held=-1;

            for(I=0; I<30; I++){
                NormalEnemy E = Enemys[I];
                if(I==AA||E.Friend!=0||E.Alive==0){continue;}

                if(intersept(E.X,E.Y,TileSize,TileSize,Enemys[AA].X,Enemys[AA].Y,TileSize,TileSize)==1){
                    Enemys[AA].Health-=E.Damage;
                    if(Enemys[AA].Health<=0){
                        Enemys[AA].Alive=2;
                    }
                }

                if(abs(E.X-Enemys[AA].X)<Shortest||Enemys[Held].Alive==0){
                    Shortest=abs(E.X-Enemys[AA].X);
                    Held=I;
                }
            }

            if(Held!=-1){
                if(Enemys[Held].X<=Enemys[AA].X){
                    Enemys[AA].Friend=1;
                }else{
                    Enemys[AA].Friend=2;
                }

                if(abs(Enemys[AA].Y-Enemys[Held].Y)>abs(Enemys[AA].X-Enemys[Held].X)){
                    if(Enemys[AA].Y>Enemys[Held].Y){
                        Enemys[AA].Friend=Enemys[AA].Friend+2;
                    }else{
                        Enemys[AA].Friend=Enemys[AA].Friend+4;
                    }
                }
                /// ///////// ///

                if(Scene!=11&&Scene!=12){
                    Enemys[AA].AttackTimer=Enemys[AA].AttackTimer+1;
                }
                if(Enemys[AA].AttackTimer>=100){
                    int Id;
                    Enemys[AA].AttackTimer=0;
                    if(Enemys[AA].Type==26){
                        Id = ShootSpclBullet2(AA,Enemys[AA].X+TileSize/2,Enemys[AA].Y+TileSize/2,Enemys[Held].X+TileSize/2,Enemys[Held].Y+TileSize/2,10,20,24,1);
                    }else{
                        Id = BossShoot(Enemys[AA].X+TileSize/2,Enemys[AA].Y+TileSize/2,Enemys[Held].X+TileSize/2,Enemys[Held].Y+TileSize/2);
                        Bullets[Id].Enemy=0;
                        GetBulletPos2(Id,AA);
                    }
                    Bullets[Id].Damage=Enemys[AA].Damage;
                }

                if(abs(Enemys[Held].X-Enemys[AA].X)<=150){
                    if(Enemys[Held].X<Enemys[AA].X){
                        Enemys[AA].SpdX=4;
                    }else{
                        Enemys[AA].SpdX=-4;
                    }
                    if(abs(Enemys[Held].X-Enemys[AA].X)<=TileSize/2&&Enemys[AA].Falling==0&&Enemys[AA].Y-Enemys[Held].Y<TileSize*2){
                        Enemys[AA].SpdY=-20;
                    }
                }else if(abs(Enemys[Held].X-Enemys[AA].X)>=300){
                    if(Enemys[Held].X<Enemys[AA].X){
                        Enemys[AA].SpdX=-4;
                    }else{
                        Enemys[AA].SpdX=4;
                    }
                }

            }else{
                Enemys[AA].MaxSpeed=Enemys[AA].MaxSpeed+1;

                if(Enemys[AA].MaxSpeed>=50){
                    Enemys[AA].MaxSpeed=0;
                    int Rand = Random(0,4);
                    if(Rand==0||Rand==1){
                        Enemys[AA].SpdX=0;
                    }else if(Rand==2){
                        Enemys[AA].SpdX=5;
                        Enemys[AA].Friend=2;
                    }else if(Rand==3){
                        Enemys[AA].SpdX=-5;
                        Enemys[AA].Friend=1;
                    }else if(Rand==4){
                        Enemys[AA].SpdX=0;
                        Enemys[AA].SpdY=-15;
                    }
                }
            }

            if(Enemys[AA].SpdX!=0&&Held!=-1){
                if(Enemys[AA].SpdX>0){
                    Enemys[AA].SpdX=Enemys[AA].SpdX-1;
                }else if(Enemys[AA].SpdX<0){
                    Enemys[AA].SpdX=Enemys[AA].SpdX+1;
                }
            }
        /// ///////////////////////////////////////////////////////// /// /////////////////////////////////////////////////////////
        }else if(Enemys[AA].Type>=20&&Enemys[AA].Type<=24){
            Enemys[AA].AttackTimer=Enemys[AA].AttackTimer+1;
            if(Enemys[AA].AttackTimer>=90){
                Enemys[AA].AttackTimer=0;
                Enemys[AA].SpdX*=-1;
                Enemys[AA].SpdY*=-1;
            }
            Enemys[AA].X+=Enemys[AA].SpdX;
            Enemys[AA].Y+=Enemys[AA].SpdY;
        }
        /// enemy collide ///

        int IA=0;
        for(IA=0; IA<30; IA++){
            if(Enemys[IA].Alive!=1||IA==AA||Enemys[AA].Sleeping==1||Enemys[IA].Sleeping==1||Enemys[IA].Friend!=Enemys[AA].Friend||Scene==2||Scene==3||Enemys[AA].Type==2||Enemys[IA].Type==2){ continue; }

            if(intersept(Enemys[AA].X, Enemys[AA].Y, TileSize, TileSize, Enemys[IA].X, Enemys[IA].Y, TileSize, TileSize)){
                if(Enemys[AA].X!=Enemys[IA].X){
                    Enemys[AA].SpdX=(TileSize-(Enemys[IA].X-Enemys[AA].X))/10;
                    Enemys[AA].X+=Enemys[AA].SpdX;
                    if(Enemys[IA].Sleeping==0){
                        Enemys[IA].SpdX=(-TileSize+(Enemys[IA].X-Enemys[AA].X))/10;
                        Enemys[IA].X+=Enemys[IA].SpdX;
                    }
                }else{
                    Enemys[AA].X=Enemys[AA].X+10;
                    Enemys[AA].SpdX=4;
                    if(Enemys[IA].Sleeping==0){
                        Enemys[IA].X=Enemys[IA].X-10;
                        Enemys[IA].SpdX=-4;
                    }
                }
                break;
            }
        }

        if(intersept(PlayerX,PlayerY,TileSize,TileSize,Enemys[AA].X,Enemys[AA].Y,TileSize,TileSize)&&Enemys[AA].Sleeping==0){
            DamagePlayer(Enemys[AA].Damage);
        }

    }else{
        Enemys[AA].Spawning=Enemys[AA].Spawning+1;
    }
}

void EnemyRun(){
    int J;
    for(J=0; J<30; J++){
        if(Enemys[J].Alive==1){
            EnemyUpdate(J);
        }
    }
}

void EnemyRender(){
    for(I=0; I<30; I++){
        if(Enemys[I].Alive==1){
            if(Enemys[I].Type!=25&&Enemys[I].Type!=26){
                if(Enemys[I].Counter<=(9-Enemys[I].MaxSpeed+abs(9-Enemys[I].MaxSpeed))/2){
                    Enemys[I].Counter=Enemys[I].Counter+1;
                }else{
                    if(Enemys[I].Type!=3){
                        if(Enemys[I].Walking<3){
                            Enemys[I].Walking=Enemys[I].Walking+1;
                        }else{
                            Enemys[I].Walking=0;
                        }
                        Enemys[I].Counter=0;
                    }else{
                        if(Enemys[I].Walking<5){
                            Enemys[I].Walking=Enemys[I].Walking+1;
                        }else{
                            Enemys[I].Walking=0;
                        }
                        Enemys[I].Counter=0;
                    }
                }
            }else{
                if(Enemys[I].SpdX!=0){
                    Enemys[I].Walking=Enemys[I].Walking+1;
                    if(Enemys[I].Walking>=28){
                        Enemys[I].Walking=0;
                    }
                }else{
                    Enemys[I].Walking=0;
                }
            }

            float HIHBHJ;
            HIHBHJ = TileSize*(Enemys[I].Spawning/50);
            if(Enemys[I].Type==0){
                ImgAnim(7, Enemys[I].X + OffsetX + (TileSize-HIHBHJ)/2, Enemys[I].Y + OffsetY + (TileSize-HIHBHJ)/1, HIHBHJ, HIHBHJ,Enemys[I].Walking,48,35);
            }else if(Enemys[I].Type==1){
                if(Enemys[I].SpdX<0){
                    ImgAnim(16, Enemys[I].X + OffsetX + (TileSize-HIHBHJ)/2, Enemys[I].Y + OffsetY + (TileSize-HIHBHJ)/1, HIHBHJ, HIHBHJ,Enemys[I].Walking,48,48);
                }else{
                    RotateAnim(16, Enemys[I].X + OffsetX + (TileSize-HIHBHJ)/2, Enemys[I].Y + OffsetY + (TileSize-HIHBHJ)/1, HIHBHJ, HIHBHJ,0,0,0,1,Enemys[I].Walking,48,48);
                }
            }else if(Enemys[I].Type==2){
                ImgAnim(55, Enemys[I].X + OffsetX + (TileSize-HIHBHJ)/2, Enemys[I].Y + OffsetY + (TileSize-HIHBHJ)/1, HIHBHJ, HIHBHJ, GetAnimation(4,5), 32, 32);
            }else if(Enemys[I].Type==3){
                if(Enemys[I].Sleeping==1){
                    DrawImgP(9, Enemys[I].X+OffsetX-TileSize*0.3, Enemys[I].Y+OffsetY-TileSize*0.3, TileSize*1.3, TileSize*1.3);
                }else if(Enemys[I].Sleeping==2){
                    if(Enemys[I].Spawning<50){
                        ImgAnim(8, Enemys[I].X+OffsetX-TileSize*0.3, Enemys[I].Y+OffsetY-TileSize*0.3, TileSize*1.3, TileSize*1.3,Enemys[I].Spawning/10,64,64);
                    }else{
                        Enemys[I].Sleeping=0;
                        ImgAnim(8, Enemys[I].X+OffsetX-TileSize*0.3, Enemys[I].Y+OffsetY-TileSize*0.3, TileSize*1.3, TileSize*1.3,4,64,64);
                    }
                }else{
                    ImgAnim(9, Enemys[I].X+OffsetX-TileSize*0.3, Enemys[I].Y+OffsetY-TileSize*0.3, TileSize*1.3, TileSize*1.3,GetAnimation(6,5),64,64);
                }
            }else if(Enemys[I].Type==4){
                if(Enemys[I].AttackTimer>=90){
                    ImgAnim(10, Enemys[I].X+OffsetX, Enemys[I].Y+OffsetY+(Enemys[I].AttackTimer-90)*2, TileSize-(Enemys[I].AttackTimer-90)*2, TileSize,GetAnimation(4,5),32,32);
                }else{
                    ImgAnim(10, Enemys[I].X+OffsetX, Enemys[I].Y+OffsetY+(TileSize-HIHBHJ)/1, HIHBHJ, TileSize,GetAnimation(4,5),32,32);
                }
            }else if(Enemys[I].Type==25||Enemys[I].Type==26){       /// /////////////////////////////////////////////////////////
                if(Enemys[I].Friend<3){
                    Rotated2(1+Enemys[I].Walking/7,Enemys[I].X+OffsetX,Enemys[I].Y+OffsetY,TileSize,TileSize,Enemys[I].Friend-1);
                    Rotated2(6,Enemys[I].X+OffsetX,Enemys[I].Y+OffsetY,TileSize,TileSize,Enemys[I].Friend-1);
                }else if(Enemys[I].Friend<5){
                    Rotated2(1+Enemys[I].Walking/7,Enemys[I].X+OffsetX,Enemys[I].Y+OffsetY,TileSize,TileSize,Enemys[I].Friend-3);
                    Rotated2(7,Enemys[I].X+OffsetX,Enemys[I].Y+OffsetY,TileSize,TileSize,Enemys[I].Friend-3);
                }else if(Enemys[I].Friend<7){
                    Rotated2(1+Enemys[I].Walking/7,Enemys[I].X+OffsetX,Enemys[I].Y+OffsetY,TileSize,TileSize,Enemys[I].Friend-5);
                    Rotated2(5,Enemys[I].X+OffsetX,Enemys[I].Y+OffsetY,TileSize,TileSize,Enemys[I].Friend-5);
                }

                if(Enemys[I].Number3>0){
                    int TimesFive, MinusTen;

                    Enemys[I].Number3+=1;

                    TimesFive=Enemys[I].Number3*3;
                    MinusTen=14-Enemys[I].Number3*2;

                    color(255,255,255,255);
                    FillRect(Enemys[I].Number+OffsetX +TimesFive +Enemys[I].X,Enemys[I].Number2+OffsetY -TimesFive +Enemys[I].Y,MinusTen,MinusTen);
                    FillRect(Enemys[I].Number+OffsetX -TimesFive +Enemys[I].X,Enemys[I].Number2+OffsetY +TimesFive +Enemys[I].Y,MinusTen,MinusTen);
                    FillRect(Enemys[I].Number+OffsetX +TimesFive +Enemys[I].X,Enemys[I].Number2+OffsetY +TimesFive +Enemys[I].Y,MinusTen,MinusTen);
                    FillRect(Enemys[I].Number+OffsetX -TimesFive +Enemys[I].X,Enemys[I].Number2+OffsetY -TimesFive +Enemys[I].Y,MinusTen,MinusTen);
                    if(Enemys[I].Number3>7){
                        Enemys[I].Number3=0;
                    }
                }
            /// ///////////////////////////////////////////////////////// /// /////////////////////////////////////////////////////////

            }else if(Enemys[I].Type>=20&&Enemys[I].Type<=24&&Enemys[I].X!=0&&Enemys[I].Y!=0){
                DrawImg(42+(GetRoom(MapX,MapY).Area-3)*2, Enemys[I].X + OffsetX, Enemys[I].Y + OffsetY, TileSize, TileSize);
            }
        }else if((Enemys[I].Type==25||Enemys[I].Type==26)&&Enemys[I].Alive==2){
            CheckCollsions((int*) &Enemys[I].X,(int*) &Enemys[I].Y,(int*) &Enemys[I].SpdX,(int*) &Enemys[I].SpdY,(int*) &Enemys[I].Falling,1,TileSize);
            DrawImgP(9, Enemys[I].X+OffsetX-TileSize*0.3, Enemys[I].Y+OffsetY-TileSize*0.3, TileSize*1.3, TileSize*1.3);

            if(Enemys[I].SpdX!=0){
                if(Enemys[I].SpdX>0){
                    Enemys[I].SpdX=Enemys[I].SpdX-1;
                }else if(Enemys[I].SpdX<0){
                    Enemys[I].SpdX=Enemys[I].SpdX+1;
                }
            }
        }
    }
}

#endif
