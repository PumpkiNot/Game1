#ifndef BULLETS
#define BULLETS

#include <math.h>

void color(int A,int B,int C,int D);
int Round(int Number, int B);
int GetTileStuff(int X, int Y);
void FillRect(int A,int B,int C,int D);
void PlaySoundPro(int SoundId);
int Random(int Min, int Max);

int Direction=1;
int I;
int ShootX, ShootY, ShootEffect;

int GetDistance(int X1, int X2, int Y1, int Y2){
    return sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));
}

Point caulcSpeed(int X1, int Y1, int X2, int Y2, int Speed){
    int VelX;
    int VelY;
    double Distance;
    Distance=sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2))/Speed;
    if(Distance!=0){
        VelX=(X1-X2)/Distance;
        VelY=(Y1-Y2)/Distance;
    }else{
        VelX=0;
        VelY=0;
    }

    Point temp;
    temp.X=VelX;
    temp.Y=VelY;
    return temp;
}

typedef struct bulletType1{
    short X;
    short Y;
    short SpdX;
    short SpdY;
    short Alive;
    short Type;
    short Damage;
    short Image;
    short Width;
    short Height;
    short Enemy;
    short Size;
    short Effect;
}NormalBullet;

typedef struct bulletType2{
    int AmmoCost;
    int Damage;
    int Speed;
    int RapidFire;
    int Cooldown;
    int BlastRadius;
    int Effect;
    int Image;
}SpecialBullet;

NormalBullet Bullets[50];
SpecialBullet Secondary[30];



/// //// ///// Explosions ///// //// ///

void SpawnExplode(int XX, int YY, int Size, int Damage){
    int B;
    for(B=30; B<50; B++){
        if(Bullets[B].Alive==0){
            Bullets[B].Alive=1;
            Bullets[B].X=XX;
            Bullets[B].Y=YY;
            Bullets[B].Width=0;
            Bullets[B].Height=0;
            Bullets[B].Size=Size;
            Bullets[B].Damage=Damage;
            break;
        }
    }
}

void UpdateExplosion(){
    int B;
    for(B=30; B<50; B++){
        if(Bullets[B].Alive==1){
            if(Bullets[B].Width>=Bullets[B].Size){
                Bullets[B].Width=0;
                Bullets[B].Height=0;
                Bullets[B].Alive=0;
            }

            Bullets[B].X-=8;
            Bullets[B].Y-=8;
            Bullets[B].Width+=16;
            Bullets[B].Height+=16;
        }
    }
}

void RenderExplosion(){
    int C;
    for(C=30; C<50; C++){
        if(Bullets[C].Alive==1){
            color(0,0,0,255);
            DrawImg(25,Bullets[C].X +OffsetX , Bullets[C].Y + OffsetY , Bullets[C].Width, Bullets[C].Height);
        }
    }
}

void RemoveBullet(int Id, int Radius, int Dmg){
    if(Id<30){
        if(Bullets[Id].Type!=50){
            SpawnExplode(Bullets[Id].X, Bullets[Id].Y, Radius,Dmg);
            PlaySoundPro(5);
            //Mix_PlayChannel(-1, Explosion, 0);
        }
        Bullets[Id].Alive=0;
        Bullets[Id].Effect=1;
        Charge+=ChargeAmount;
    }
}

void DeleteBullet(int Id, int Radius, int Dmg){
    if(Id<30){
        if(Bullets[Id].Type!=50){
            SpawnExplode(Bullets[Id].X, Bullets[Id].Y, Radius,Dmg);
            PlaySoundPro(5);
            //Mix_PlayChannel(3, Explosion, 0);
        }
        Bullets[Id].Alive=0;
        Bullets[Id].Effect=1;
    }
}

/// //// ////// Bullets ///// //// ///

void SetSecondary(int Id, int AmmoCost, int Damage, int Speed, int RapidFire, int Cooldown, int BlastRadius, int Effect, int Image){
    Secondary[Id].AmmoCost=AmmoCost;
    Secondary[Id].Damage=Damage;
    Secondary[Id].Speed=Speed;
    Secondary[Id].RapidFire=RapidFire;
    Secondary[Id].Cooldown=Cooldown;
    Secondary[Id].BlastRadius=BlastRadius;
    Secondary[Id].Effect=Effect;
    Secondary[Id].Image=Image;
}

void LoadSecondarys(){
    SetSecondary(0, 0, 200, BulletSpeed*2, 0, 20, 0, 0, 11);
    SetSecondary(1, 40, 200, BulletSpeed, 0, 5, 100, 0, 24);
    SetSecondary(2, 10, 20, BulletSpeed, 1, 4, 0, 0, 36);
}

void GetBulletPos(int I){
    if(W-S==1){
        if(Direction==-1){
            Bullets[I].X=X+9;
            Bullets[I].Y=Y-3;
        }else{
            Bullets[I].X=X+TileSize-19;
            Bullets[I].Y=Y-3;
        }
    }else if(W-S==-1){
        if(Direction==-1){
            Bullets[I].X=X+9;
            Bullets[I].Y=Y+TileSize-20;
        }else{
            Bullets[I].X=X+TileSize-19;
            Bullets[I].Y=Y+TileSize-20;
        }
    }else{
        if(Direction==-1){
            Bullets[I].X=X-10;
            Bullets[I].Y=Y+TileSize/2-10;
        }else{
            Bullets[I].X=X+TileSize;
            Bullets[I].Y=Y+TileSize/2-10;
        }
    }

    ShootX=Bullets[I].X-X;
    ShootY=Bullets[I].Y-Y;
    ShootEffect=1;
}

void GetBulletPos2(int I, int AA){
    int X=Enemys[AA].X,Y=Enemys[AA].Y;

    switch(Enemys[AA].Friend){
        case 1:
            Bullets[I].X=X-10;
            Bullets[I].Y=Y+TileSize/2-10;
        break;
        case 2:
            Bullets[I].X=X+TileSize;
            Bullets[I].Y=Y+TileSize/2-10;
        break;
        case 3:
            Bullets[I].X=X+9;
            Bullets[I].Y=Y-3;
        break;
        case 4:
            Bullets[I].X=X+TileSize-19;
            Bullets[I].Y=Y-3;
        break;
        case 5:
            Bullets[I].X=X+9;
            Bullets[I].Y=Y+TileSize-20;
        break;
        case 6:
            Bullets[I].X=X+TileSize-19;
            Bullets[I].Y=Y+TileSize-20;
        break;
    }

    Enemys[AA].Number=Bullets[I].X-X;
    Enemys[AA].Number2=Bullets[I].Y-Y;
    Enemys[AA].Number3=1;
}

int ShootNormBullet(){
    for(I=0; I<30; I++){
        if(Bullets[I].Alive==0){
            GetBulletPos(I);
            if(ProAim==1){
                int LineX = Bullets[I].X+OffsetX-MouseX;
                int LineY = Bullets[I].Y+OffsetY-MouseY;
                double Distancee = sqrt((LineX*LineX)+(LineY*LineY))/BulletSpeed;
                int VelX;
                int VelY;
                if(Distancee!=0){
                    VelX=(MouseX-Bullets[I].X-OffsetX)/Distancee;
                    VelY=(MouseY-Bullets[I].Y-OffsetY)/Distancee;
                    Bullets[I].Alive=1;
                }
                Bullets[I].SpdX=VelX;
                Bullets[I].SpdY=VelY;
            }else{
                Bullets[I].SpdX=(BulletSpeed*Direction)*(abs(W-S)*-1+1);
                Bullets[I].SpdY=BulletSpeed*(S-W);
                Bullets[I].Alive=1;
            }
            Bullets[I].SpdX+=Random(Accuricy*-1,Accuricy);
            Bullets[I].SpdY+=Random(Accuricy*-1,Accuricy);

            Bullets[I].Type=50;
            Bullets[I].Damage=Damage;
            Bullets[I].Width=TileSize/4;
            Bullets[I].Height=TileSize/4;
            Bullets[I].Image=BulletImage;
            Bullets[I].Enemy=0;

            if(Bullets[I].SpdX+Bullets[I].SpdY==0){
                Bullets[I].Alive=0;
            }else{
                PlaySoundPro(2);
                //Mix_PlayChannel(-1, ShootSound, 0);
            }

            return I;
            break;
        }
    }
    return 0;
}

int ShootSpclBullet(int Type){
    for(I=0; I<30; I++){
        if(Bullets[I].Alive==0&&Ammo>0){
            GetBulletPos(I);
            if(ProAim==1){
                int LineX = X+OffsetX+TileSize/2-MouseX;
                int LineY = Y+OffsetY+TileSize/2-MouseY;
                double Distancee = sqrt((LineX*LineX)+(LineY*LineY))/Secondary[Type].Speed;
                int VelX;
                int VelY;
                if(Distancee!=0){
                    VelX=(MouseX-X-TileSize/2-OffsetX)/Distancee;
                    VelY=(MouseY-Y-TileSize/2-OffsetY)/Distancee;
                    Bullets[I].Alive=1;
                }
                Bullets[I].SpdX=VelX;
                Bullets[I].SpdY=VelY;
            }else{
                Bullets[I].SpdX=(Secondary[Type].Speed*Direction)*(abs(W-S)*-1+1);
                Bullets[I].SpdY=Secondary[Type].Speed*(S-W);
                Bullets[I].Alive=1;
            }
            Bullets[I].Type=Type;
            Bullets[I].Damage=Secondary[Type].Damage;
            Bullets[I].Image=Secondary[Type].Image;
            Bullets[I].Width=TileSize/4;
            Bullets[I].Height=TileSize/4;
            Bullets[I].Enemy=0;

            Ammo-=Secondary[Type].AmmoCost;

            return I;
            break;
        }
    }
    return 0;
}

int ShootSpclBullet2(int AA, int X, int Y, int XX, int YY, int Damage, int Speed, int Image, int Type){
    for(I=0; I<30; I++){
        if(Bullets[I].Alive==0){
            GetBulletPos2(I,AA);
            int LineX = X-XX;
            int LineY = Y-YY;
            double Distancee = sqrt((LineX*LineX)+(LineY*LineY))/Speed;
            int VelX;
            int VelY;
            if(Distancee!=0){
                VelX=(XX-X)/Distancee;
                VelY=(YY-Y)/Distancee;
                Bullets[I].Alive=1;
            }
            Bullets[I].SpdX=VelX;
            Bullets[I].SpdY=VelY;

            Bullets[I].Type=Type;
            Bullets[I].Damage=Damage;
            Bullets[I].Image=Image;
            Bullets[I].Width=TileSize/4;
            Bullets[I].Height=TileSize/4;
            Bullets[I].Enemy=0;

            return I;
            break;
        }
    }
    return 0;
}


void EnemyShoot(int Id){
    for(I=0; I<30; I++){
        if(Bullets[I].Alive==0){

            Bullets[I].X=Enemys[Id].X+TileSize/2;
            Bullets[I].Y=Enemys[Id].Y+TileSize/2;

            /// /// ///
            int LineX = X-Enemys[Id].X;
            int LineY = Y-Enemys[Id].Y;
            double Distancee = sqrt((LineX*LineX)+(LineY*LineY))/10;
            int VelX;
            int VelY;
            if(Distancee!=0){
                VelX=(X-Enemys[Id].X)/Distancee;
                VelY=(Y-Enemys[Id].Y)/Distancee;
                Bullets[I].Alive=1;
            }
            Bullets[I].SpdX=VelX;
            Bullets[I].SpdY=VelY;
            /// /// ///

            Bullets[I].Type=50;
            Bullets[I].Damage=Damage;
            Bullets[I].Width=TileSize/4;
            Bullets[I].Height=TileSize/4;
            Bullets[I].Image=11;
            Bullets[I].Enemy=1;

            //Mix_PlayChannel(-1, ShootSound, 0);
            PlaySoundPro(2);

            break;
        }
    }
}

int BossShoot(int X1, int Y1, int X2, int Y2){
    for(I=0; I<30; I++){
        if(Bullets[I].Alive==0){

            Bullets[I].X=X1;
            Bullets[I].Y=Y1;

            /// /// ///
            int LineX = X2-X1;
            int LineY = Y2-Y1;
            double Distancee = sqrt((LineX*LineX)+(LineY*LineY))/10;
            int VelX;
            int VelY;
            if(Distancee!=0){
                VelX=(X2-X1)/Distancee;
                VelY=(Y2-Y1)/Distancee;
                Bullets[I].Alive=1;
            }
            Bullets[I].SpdX=VelX;
            Bullets[I].SpdY=VelY;
            /// /// ///

            Bullets[I].Type=50;
            Bullets[I].Damage=Damage*10;
            Bullets[I].Width=TileSize/4;
            Bullets[I].Height=TileSize/4;
            Bullets[I].Image=11;
            Bullets[I].Enemy=1;

           // Mix_PlayChannel(-1, ShootSound, 0);
            PlaySoundPro(2);

            return I;

            break;
        }
    }
    return 0;
}

void BulletUpdate(int A){
    int TileId = MapArray[(Bullets[A].X+Bullets[A].SpdX)/TileSize][(Bullets[A].Y+Bullets[A].SpdY)/TileSize];
    if((TileId==1||TileId==2)&&A<30){
        DeleteBullet(A,Secondary[Bullets[A].Type].BlastRadius, Bullets[A].Damage);
        Bullets[A].X=0;
        Bullets[A].Y=0;
        Bullets[A].SpdX=0;
        Bullets[A].SpdY=0;
    }else{
        Bullets[A].X+=Bullets[A].SpdX;
        Bullets[A].Y+=Bullets[A].SpdY;
    }
}

void BulletRun(){
    for(I=0; I<sizeof(Bullets)/sizeof(NormalBullet); I++){
        if(Bullets[I].Alive==1){
            BulletUpdate(I);
        }
    }
}

void BulletRender(){
    for(I=0; I<30; I++){
        if(Bullets[I].Alive==1){
            double tempAng,tempAng2;

            if(Bullets[I].SpdX!=0){tempAng=(double)Bullets[I].SpdY/(double)Bullets[I].SpdX;
            }else{tempAng=0;}

            double Speed;
            Speed=(BulletSpeed/(double)20)*32;
            tempAng2 = atan(tempAng) * 180 /  3.14;

            if(Bullets[I].SpdX==0){if(Bullets[I].SpdY>0){tempAng2=90;}else{tempAng2=-90;}}
            if(Bullets[I].SpdX<0){tempAng2+=180;}

            Rotated(Bullets[I].Image, Bullets[I].X +OffsetX-16, Bullets[I].Y +OffsetY-Speed/2, 32, Speed, 16, Speed/2, tempAng2, SDL_FLIP_NONE);

            if(Bullets[I].Effect>0){
                Bullets[I].Effect=Bullets[I].Effect+1;
                int Effect = Bullets[I].Effect;

                if(Effect>=100){
                    Bullets[I].Effect=0;
                }
            }
        }
    }
}


#endif


