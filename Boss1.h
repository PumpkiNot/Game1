#ifndef BOSS1
#define BOSS1

void FillRect(int A,int B,int C,int D);
int UnlockSomthing(int Type, int Id, char String[30]);
void Save();
void PlaySoundPro(int SoundId);
void MoveCutscene(int X, int Y, int XX, int YY);

int BossAnim = 0;

void BossSpawn1(int XX, int YX, int Type){
    if(Type==1){
        Boss1.Alive=1;
        Boss1.X=XX;
        Boss1.Y=YX;
        Boss1.Size=TileSize*1;
        Boss1.AttackTimer=200;
        Boss1.Timer=1;
        Boss1.Health=1400;
        Boss1.Type=1;
    }
    else if(Type==2){
        Boss1.Alive=1;
        Boss1.X=XX;
        Boss1.Y=YX;
        Boss1.Size=TileSize*1;
        Boss1.AttackTimer=200;
        Boss1.Timer=1;
        Boss1.Health=1200;
        Boss1.Type=2;
    }
    else if(Type==3){
        Boss1.Alive=1;
        Boss1.X=XX;
        Boss1.Y=YX;
        Boss1.Size=TileSize*1;
        Boss1.AttackTimer=200;
        Boss1.Timer=1;
        Boss1.Health=2000;
        Boss1.Type=3;
    }
    else if(Type==4){
        Boss1.Alive=1;
        Boss1.X=XX;
        Boss1.Y=YX;
        Boss1.Size=TileSize*3;
        Boss1.AttackTimer=200;
        Boss1.Timer=1;
        Boss1.Health=4000;
        Boss1.Type=4;
    }else if(Type==5){
        Boss1.Alive=1;
        Boss1.X=XX;
        Boss1.Y=YX;
        Boss1.Size=TileSize*3;
        Boss1.AttackTimer=200;
        Boss1.Timer=1;
        Boss1.Health=7000;
        Boss1.Type=5;
    }

    if(Mode==0){
        Boss1.Health=Boss1.Health/4*3;
    }

    Boss1.MaxHealth=Boss1.Health;

    Mix_Volume(1,Volume);
    Mix_PlayChannel(1,Music[14],-1);
    MoveCutscene(X,Y,Boss1.X,Boss1.Y);


}

int NormalBullets(){
    int Return = 0;
    for(II=0; II<50; II++){
        if(Bullets[II].Alive==1&&Bullets[II].Enemy==0){
            if(intersept(Boss1.X,Boss1.Y,Boss1.Size,Boss1.Size, Bullets[II].X-Bullets[II].SpdX, Bullets[II].Y-Bullets[II].SpdY, TileSize/4, TileSize/4)||intersept(Boss1.X,Boss1.Y,Boss1.Size,Boss1.Size, Bullets[II].X+Bullets[II].SpdX, Bullets[II].Y+Bullets[II].SpdY, TileSize/4, TileSize/4)){
                Boss1.Health-=Bullets[II].Damage;
                if(Boss1.Health<1){
                    Boss1.Alive=0;
                    SpawnSpecial(Boss1.X +(Boss1.Size-TileSize)/2, Boss1.Y +(Boss1.Size-TileSize)/2,0);

                    MapArray[0][14]=0;
                    MapArray[0][15]=0;
                    MapArray[29][14]=0;
                    MapArray[29][15]=0;

                    //Mix_PlayChannel(-1, BigExplosion, 0);
                    PlaySoundPro(4);
                    Mix_FadeOutChannel(1,800);
                    Mix_Volume(1,100);
                    BossCount+=1;

                    Return=1;
                }
                RemoveBullet(II,Secondary[Bullets[II].Type].BlastRadius,Bullets[II].Damage);
            }
        }
    }
    return Return;
}

void Boss1Update(int I){
    int Landed=0;
    if(Boss1.Alive==1){
        if(Boss1.Type!=3&&Boss1.Type!=4){
            Landed = CheckCollsions((int*) &Boss1.X, (int*) &Boss1.Y, (int*) &Boss1.SpdX, (int*) &Boss1.SpdY, (int*) &Boss1.Falling, 1, Boss1.Size);
        }

    /// ////////////////////// Boss 1 ////////////////////// ///
    if(Boss1.Type==1){

        if(Timer==0){
            if(X<Boss1.X&&Boss1.SpdX>-30){
                Boss1.SpdX-=1;
            }else if(X>Boss1.X&&Boss1.SpdX<30){
                Boss1.SpdX+=1;
            }else{
                if(Boss1.SpdX>0){Boss1.SpdX-=5;}
                if(Boss1.SpdX<0){Boss1.SpdX+=5;}
                if(abs(Boss1.X-X)<400&&Boss1.SpdY==0&&Boss1.Falling==0){Boss1.SpdY=-30;}
            }

            Boss1.Timer=Boss1.Timer+1;
        }

        if(Boss1.Timer%70==0){
            int EnemyId = SpawnEnemy(0);
            Enemys[EnemyId].X=Boss1.X;
            Enemys[EnemyId].Y=Boss1.Y;
        }

        int IsDead = NormalBullets();
        if(IsDead==1){
            if(Health>=MaxHealth/5*3&&Mode>=2){
                UnlockSomthing(0,4,"u have got an xtra shoo now");
            }else if(Mode<=1){
                UnlockSomthing(0,7,"n000000000000000000000000000b!");
            }
        }
    }

    /// ////////////////////// Boss 2 ////////////////////// ///
    else if(Boss1.Type==2){

        if(Timer==0){
            if(X<Boss1.X&&Boss1.SpdX>-4){
                Boss1.SpdX-=1;
            }else if(X>Boss1.X&&Boss1.SpdX<4){
                Boss1.SpdX+=1;
            }else{
                if(Boss1.SpdX>0){Boss1.SpdX-=1;}
                if(Boss1.SpdX<0){Boss1.SpdX+=1;}
                if(abs(Boss1.X-X)<400&&Boss1.SpdY==0&&Boss1.Falling==0){Boss1.SpdY=-20;}
            }
        }


        /// bullets ///

        for(II=0; II<50; II++){
            if(Bullets[II].Alive==1){
                if(intersept(Boss1.X,Boss1.Y,TileSize,TileSize, Bullets[II].X-Bullets[II].SpdX, Bullets[II].Y-Bullets[II].SpdY, TileSize/4, TileSize/4)||intersept(Boss1.X,Boss1.Y,TileSize,TileSize, Bullets[II].X+Bullets[II].SpdX, Bullets[II].Y+Bullets[II].SpdY, TileSize/4, TileSize/4)){
                    Boss1.Health-=Bullets[II].Damage;

                    int Id = SpawnEnemy(0);
                    Enemys[Id].X=Boss1.X;
                    Enemys[Id].Y=Boss1.Y;

                    if(Boss1.Health<1){
                        Boss1.Alive=0;
                        SpawnSpecial(Boss1.X,Boss1.Y,0);

                        //Mix_PlayChannel(-1, BigExplosion, 0);
                        PlaySoundPro(4);
                        Mix_Volume(1,100);
                        Mix_FadeOutChannel(1,800);
                        BossCount+=1;

                        MapArray[0][14]=0;
                        MapArray[0][15]=0;
                        MapArray[29][14]=0;
                        MapArray[29][15]=0;

                        if(Health>=MaxHealth/5*4&&Mode>=2){
                            UnlockSomthing(0,3,"shield hat unlocked.");
                        }else if(Mode<=1){
                            UnlockSomthing(0,7,"n000000000000000000000000000b!");
                        }
                    }
                    RemoveBullet(II,Secondary[Bullets[II].Type].BlastRadius,Bullets[II].Damage);
                }
            }
        }

        /// end of bullets ///


        if(intersept(X,Y,TileSize,TileSize,Boss1.X,Boss1.Y,TileSize,TileSize)){
            DamagePlayer(2);
        }

    }

    /// ////////////////////// Boss 3 ////////////////////// ///
    else if(Boss1.Type==3){

        if(Timer==0){
            Boss1.Timer+=1;
        }

        if(Boss1.Timer%40==0){
            int EnemyId = SpawnSpclEnemy(Random(0,1),1);
            Enemys[EnemyId].X=Boss1.X;
            Enemys[EnemyId].Y=Boss1.Y;
        }


        /// bullets ///
        for(II=0; II<50; II++){
            if(Bullets[II].Alive==1){
                if(intersept(Boss1.X,Boss1.Y,TileSize,TileSize, Bullets[II].X-Bullets[II].SpdX, Bullets[II].Y-Bullets[II].SpdY, TileSize/4, TileSize/4)||intersept(Boss1.X,Boss1.Y,TileSize,TileSize, Bullets[II].X+Bullets[II].SpdX, Bullets[II].Y+Bullets[II].SpdY, TileSize/4, TileSize/4)){
                    Boss1.Health-=Bullets[II].Damage;

                    int Id = SpawnEnemy(1);
                    Enemys[Id].X=Boss1.X;
                    Enemys[Id].Y=Boss1.Y;

                    if(Boss1.Health<1){
                        Boss1.Alive=0;
                        SpawnSpecial(Boss1.X,Boss1.Y,0);

                        //Mix_PlayChannel(-1, BigExplosion, 0);
                        PlaySoundPro(4);
                        Mix_Volume(1,100);
                        Mix_FadeOutChannel(1,800);
                        BossCount+=1;

                        MapArray[0][14]=0;
                        MapArray[0][15]=0;
                        MapArray[29][14]=0;
                        MapArray[29][15]=0;

                        if(Health>=MaxHealth/5*4){
                            UnlockSomthing(0,1,"health square hat unlocked!");
                        }
                        if(Health>=MaxHealth/5*4&&HatId==2){
                            UnlockSomthing(0,6,"rapid fire!!!");
                        }
                    }
                    RemoveBullet(II,Secondary[Bullets[II].Type].BlastRadius,Bullets[II].Damage);
                }
            }
        }
    }

    /// ////////////////////// Boss 4 ////////////////////// ///
    else if(Boss1.Type==4){

        if(Timer==0){
            Boss1.Timer+=1;
        }

        if(Boss1.Timer%80==0){
            BossAnim=1;
            int A = BossShoot(Boss1.X+TileSize/2*3, Boss1.Y+TileSize/2*3, X+TileSize/2, Y+TileSize/2);
            Bullets[A].X += Bullets[A].SpdX*12;
            Bullets[A].Y += Bullets[A].SpdY*12;
        }

        if(Boss1.Timer%127==0){
            BossAnim=1;
            int A = BossShoot(Boss1.X+TileSize/2*3, Boss1.Y+TileSize/2*3, X+TileSize/2, Y+TileSize/2);
            Bullets[A].X+=Bullets[A].SpdX*12;
            Bullets[A].Y+=Bullets[A].SpdY*12;
            int B = BossShoot(Boss1.X+TileSize/2*3, Boss1.Y+TileSize/2*3, X+TileSize/2, Y+TileSize/2+TileSize*3);
            Bullets[B].X+=Bullets[A].SpdX*12;
            Bullets[B].Y+=Bullets[A].SpdY*12;
            int C = BossShoot(Boss1.X+TileSize/2*3, Boss1.Y+TileSize/2*3, X+TileSize/2, Y+TileSize/2-TileSize*3);
            Bullets[C].X+=Bullets[A].SpdX*12;
            Bullets[C].Y+=Bullets[A].SpdY*12;
        }


        int IsDead = NormalBullets();
        if(IsDead==1){
            if(Mode>0){
                UnlockSomthing(0,2,"got hit, but not wastefull.");
            }
            if(Mode>=3){
                UnlockSomthing(0,5,"-=the lost=-");
            }
            if(Mode>=2&&HatId==5){
                hats[8].IsUnlocked=1;
                Save();
                char String[20];
                int I;
                for(I=0; I<50; I++){
                    String[I]=Random(20,150);
                }
                UnlockSomthing(0,900,String);
            }
        }
    }
    /// ////////////////////// Boss 5 ////////////////////// ///
    else if(Boss1.Type==5){
        if(Timer==0&&Falling==0&&SpdY==0){
            Boss1.Timer+=1;
        }

        if(Boss1.Falling==0&&Boss1.SpdX!=0){
            if(Boss1.SpdX>0){
                Boss1.SpdX=Boss1.SpdX-1;
            }else{
                Boss1.SpdX=Boss1.SpdX+1;
            }
        }

        if(Boss1.Timer%100==0){
            Boss1.Timer=(7000-Boss1.Health)/200;

            if(Random(0,3)!=0){
                Boss1.SpdX=(X-Boss1.X)/45;
                Boss1.SpdY=-20;
                Boss1.Counter=0;
            }else{
                Boss1.Counter=1;
                Boss1.SpdX=(X-Boss1.X)/(45/2*3);
                Boss1.SpdY=-30;
            }
        }

        if(Landed==1){
            int Bullet,I;
            if(Boss1.Counter==1){
                for(I=2; I<8; I++){
                    Bullet = BossShoot(Boss1.X,Boss1.Y+TileSize*3-TileSize/3,Boss1.X-1,Boss1.Y+TileSize*3-TileSize/3);
                    Bullets[Bullet].SpdX*=I;
                    Bullets[Bullet].SpdY=Random(-1,0);
                    Bullet = BossShoot(Boss1.X+TileSize*3-TileSize/3,Boss1.Y+TileSize*3-TileSize/3,Boss1.X+TileSize*3-TileSize/3+1,Boss1.Y+TileSize*3-TileSize/3);
                    Bullets[Bullet].SpdX*=I;
                    Bullets[Bullet].SpdY=Random(-1,0);

                    if(I<3){
                        int Id2 = SpawnEnemy(4);
                        Enemys[Id2].Y=TileSize;
                        Enemys[Id2].X=Random(TileSize,GetRoom(MapX,MapY).Width-TileSize*2);
                    }

                    OffsetX+=Random(-100,100);
                    OffsetY+=Random(-100,100);

                    MapArray[Round(Boss1.X+TileSize/2*3,TileSize)/TileSize][Round(Boss1.Y+TileSize*3+1,TileSize)/TileSize]=0;
                }
            }else{
                for(I=1; I<5; I++){
                    Bullet = BossShoot(Boss1.X,Boss1.Y+TileSize*3-TileSize/3,Boss1.X-1,Boss1.Y+TileSize*3-TileSize/3);
                    Bullets[Bullet].SpdX*=I;
                    Bullet = BossShoot(Boss1.X+TileSize*3-TileSize/3,Boss1.Y+TileSize*3-TileSize/3,Boss1.X+TileSize*3-TileSize/3+1,Boss1.Y+TileSize*3-TileSize/3);
                    Bullets[Bullet].SpdX*=I;
                }
            }
        }

        if(Boss1.Y>=GetRoom(MapX,MapY).Height){
            Boss1.Alive=0;
            SpawnExplode(Boss1.X+TileSize*2,Boss1.Y+TileSize*2,TileSize,1000);
        }

        NormalBullets();
        if(intersept(X,Y,TileSize,TileSize,Boss1.X,Boss1.Y,TileSize*3,TileSize*3)){
            DamagePlayer(1);
        }
    }

    /// //// end //// ///

    if(BossCount>=3){
        printf("to get the secrite code is in the files.");
    }

    }
}

void Boss1Render(int I){
    int AnimationSpeed=5;
    if(Boss1.Type==2){  AnimationSpeed=10;  }
    else if(Boss1.Type==3){  AnimationSpeed=4;  }

    if(Boss1.Alive==1){
        if(Boss1.Type==1){
            if(Boss1.Counter<5){
                Boss1.Counter=Boss1.Counter+1;
            }else{
                if(Boss1.Walking<3){
                    Boss1.Walking=Boss1.Walking+1;
                }else{
                    Boss1.Walking=0;
                }
                Boss1.Counter=0;
            }
            ImgAnim(12,Boss1.X + OffsetX-5, Boss1.Y + OffsetY-10, TileSize+10, TileSize+10,Boss1.Walking,48,35);
        }
        else{
            if(Boss1.Type!=5){
                if(Boss1.Counter<AnimationSpeed){
                    Boss1.Counter=Boss1.Counter+1;
                }else{
                    if(Boss1.Walking<3){
                        Boss1.Walking=Boss1.Walking+1;
                    }else{
                        Boss1.Walking=0;
                    }
                    Boss1.Counter=0;
                }
            }

            if(Boss1.Type==1||Boss1.Type==2){
                ImgAnim(12,Boss1.X + OffsetX-5, Boss1.Y + OffsetY-10, TileSize+10, TileSize+10,Boss1.Walking,48,35);
            }
            else if(Boss1.Type==3){
                ImgAnim(26,Boss1.X + OffsetX-5, Boss1.Y + OffsetY-10, TileSize+10, TileSize+10,Boss1.Walking,32,32);
            }else if(Boss1.Type==4){

                int Moddify = 0;

                if(BossAnim>0){
                    BossAnim+=1;
                    if(BossAnim<8){
                        Moddify=BossAnim/2;
                    }else{
                        BossAnim=0;
                    }
                }

                int LineX, LineY;

                LineX=X+TileSize/2-Boss1.X;
                LineY=Y+TileSize/2-Boss1.Y;

                double tempAng, tempAng2;

                if(LineX!=0){tempAng=(double)LineY/(double)LineX;
                }else{tempAng=0;}

                tempAng2 = atan(tempAng) * 180 /  3.14;

                if(LineX==0){if(LineY>0){tempAng2=90;}else{tempAng2=-90;}}
                if(LineX<0){tempAng2+=180;}

                tempAng2+=180;

                DrawImg(37,Boss1.X +OffsetX -TileSize/2, Boss1.Y +OffsetY, Boss1.Size, Boss1.Size+TileSize);
                RotateAnim(38,Boss1.X +OffsetX-48-Boss1.Size/2, Boss1.Y +OffsetY-17, Boss1.Size, Boss1.Size*2 ,Boss1.Size/4*3+Boss1.Size/2,Boss1.Size/2,tempAng2,SDL_FLIP_NONE,Moddify,128,64);

            }else if(Boss1.Type==5){
                if(Boss1.Timer>=90){
                    ImgAnim(10, Boss1.X+OffsetX, Boss1.Y+OffsetY+(Boss1.Timer-90)*2*3, TileSize*3-(Boss1.Timer-90)*2*3, TileSize*3,GetAnimation(4,5),32,32);
                }else{
                    ImgAnim(10, Boss1.X+OffsetX, Boss1.Y+OffsetY, TileSize*3, TileSize*3,GetAnimation(4,5),32,32);
                }
            }
        }
    }



    if(Boss1.Alive==1){

        int HealthLevel;
        HealthLevel=(float)Boss1.Health/3000;

        if(Boss1.MaxHealth<=3000){
            color(255,0,HealthLevel*50,255);
            FillRect((Width/2+200) - Boss1.MaxHealth/8 -4, 16, Boss1.MaxHealth/4+8, 43);

            color(150,0,HealthLevel*30,255);
            FillRect((Width/2+200) - Boss1.MaxHealth/8 -2, 18, Boss1.MaxHealth/4+4, 39);
        }else{
            color(255,0,HealthLevel*50,255);
            FillRect((Width/2+200) - 3000/8 -4, 16, 3000/4+8, 43);

            color(150,0,HealthLevel*30,255);
            FillRect((Width/2+200) - 3000/8 -2, 18, 3000/4+4, 39);
        }


        int I;
        for(I=0; I<(float)Boss1.Health/3000; I++){
            if(Boss1.Health>I*3000&&Boss1.Health<(I+1)*3000){
                color(255,0,I*50,255);
                FillRect((Width/2+200) - (Boss1.Health-(I*3000))/8, 20, (Boss1.Health-(I*3000))/4, 35);

                color(150,0,HealthLevel*30,255);
                FillRect((Width/2+200) - (Boss1.Health-(I*3000))/8 - 4, 20, 4, 35);

                color(150,0,HealthLevel*30,255);
                FillRect((Width/2+200) - (Boss1.Health-(I*3000))/8 + (Boss1.Health-(I*3000))/4, 20, 4, 35);
            }else{
                color(255,0,I*50,255);
                FillRect((Width/2+200) - 3000/8, 20, 3000/4, 35);
            }
        }
    }
}

#endif
