#ifndef IMAGE
#define IMAGE


void loadImages(){
    SDL_Texture *NullImage = IMG_LoadTexture(Renderer,"Images/Untitled.png");
    int I;
    for(I=0; I<75; I++){
        Images[I]=NullImage;
    }

    Images[0] = IMG_LoadTexture(Renderer,"Images/Stone2.png");
    Images[1] = IMG_LoadTexture(Renderer,"Images/Stone1.png");
    Images[2] = IMG_LoadTexture(Renderer,"Images/Rock1.png");
    Images[3] = IMG_LoadTexture(Renderer,"Images/Rock2.png");
    Images[4] = IMG_LoadTexture(Renderer,"Images/WaterRock1.png");
    Images[5] = IMG_LoadTexture(Renderer,"Images/WaterRock2.png");
    Images[7] = IMG_LoadTexture(Renderer,"Images/SpiderSheet.png");
    Images[8] = IMG_LoadTexture(Renderer,"Images/ZombieAwake.png");
    Images[9] = IMG_LoadTexture(Renderer,"Images/ZombieSheet.png");
    Images[10] = IMG_LoadTexture(Renderer,"Images/SlimeSheet.png");
    Images[11] = IMG_LoadTexture(Renderer,"Images/Bullet.png");
    Images[12] = IMG_LoadTexture(Renderer,"Images/OrangeSheet.png");
    Images[13] = IMG_LoadTexture(Renderer,"Images/Water2Sheet.png");
    Images[16] = IMG_LoadTexture(Renderer,"Images/BatSheet.png");
    Images[24] = IMG_LoadTexture(Renderer,"Images/BulletOld.png");
    Images[25] = IMG_LoadTexture(Renderer,"Images/Explosion.png");
    Images[26] = IMG_LoadTexture(Renderer,"Images/PortalSheet.png");
    Images[31] = IMG_LoadTexture(Renderer,"Images/WaterSheet.png");
    Images[36] = IMG_LoadTexture(Renderer,"Images/Bullet2.png");
    Images[37] = IMG_LoadTexture(Renderer,"Images/Boss3.png");
    Images[38] = IMG_LoadTexture(Renderer,"Images/BossCannonSheet.png");
    Images[42] = IMG_LoadTexture(Renderer,"Images/DarkRock1.png");
    Images[43] = IMG_LoadTexture(Renderer,"Images/DarkRock2.png");
    Images[44] = IMG_LoadTexture(Renderer,"Images/HotStones.png");
    Images[45] = IMG_LoadTexture(Renderer,"Images/HotStoneBack.png");
    Images[46] = IMG_LoadTexture(Renderer,"Images/BrickFront1.png");
    Images[47] = IMG_LoadTexture(Renderer,"Images/BrickBack1.png");
    Images[55] = IMG_LoadTexture(Renderer,"Images/ShooterSheet.png");
    Images[56] = IMG_LoadTexture(Renderer,"Images/SaveStation.png");
    Images[57] = IMG_LoadTexture(Renderer,"Images/Planet.png");
}

void loadPlayerImages(){
    PlayerImages[0] = IMG_LoadTexture(Renderer,"Player/PlayerStand.png");
    PlayerImages[1] = IMG_LoadTexture(Renderer,"Player/PlayerWalk1.png");
    PlayerImages[2] = IMG_LoadTexture(Renderer,"Player/PlayerWalk2.png");
    PlayerImages[3] = IMG_LoadTexture(Renderer,"Player/PlayerWalk3.png");
    PlayerImages[4] = IMG_LoadTexture(Renderer,"Player/PlayerWalk4.png");

    PlayerImages[6] = IMG_LoadTexture(Renderer,"Player/playerPistol.png");
    PlayerImages[7] = IMG_LoadTexture(Renderer,"Player/playerPistolUp.png");
    PlayerImages[5] = IMG_LoadTexture(Renderer,"Player/playerPistolDown.png");

    PlayerImages[10] = IMG_LoadTexture(Renderer,"Player/playerOrginDown.png");
    PlayerImages[11] = IMG_LoadTexture(Renderer,"Player/playerOrgin.png");
    PlayerImages[12] = IMG_LoadTexture(Renderer,"Player/playerOrginUp.png");

    PlayerImages[13] = IMG_LoadTexture(Renderer,"Player/playerSmgDown.png");
    PlayerImages[14] = IMG_LoadTexture(Renderer,"Player/playerSmg.png");
    PlayerImages[15] = IMG_LoadTexture(Renderer,"Player/playerSmgUp.png");

    PlayerImages[9] = IMG_LoadTexture(Renderer,"Player/Dead.png");
}

void LoadItemImages(){
    SDL_Texture *NullImage = IMG_LoadTexture(Renderer,"Images/Untitled.png");
    int I;
    for(I=0; I<40; I++){
        ItemImages[I]=NullImage;
    }

    ItemImages[19] = IMG_LoadTexture(Renderer,"Images/ItemStand.png");

    ItemImages[0] = IMG_LoadTexture(Renderer,"Images/SheildOrb.png");
    ItemImages[1] = IMG_LoadTexture(Renderer,"Images/Ammo.png");
    ItemImages[2] = IMG_LoadTexture(Renderer,"Images/ChargeOrb.png");
    ItemImages[3] = IMG_LoadTexture(Renderer,"Images/Heal.png");

    ItemImages[4] = IMG_LoadTexture(Renderer,"Images/HealthUp.png");
    ItemImages[5] = IMG_LoadTexture(Renderer,"Images/JumpBoost.png");
    ItemImages[6] = IMG_LoadTexture(Renderer,"Images/SpeedBoost.png");
    ItemImages[7] = IMG_LoadTexture(Renderer,"Images/FireRateUp.png");
    ItemImages[8] = IMG_LoadTexture(Renderer,"Images/DamageUp.png");
    ItemImages[9] = IMG_LoadTexture(Renderer,"Images/SheildUp.png");
    ItemImages[10] = IMG_LoadTexture(Renderer,"Images/ChargeUp.png");
    ItemImages[11] = IMG_LoadTexture(Renderer,"Images/AmmoUp.png");
    ItemImages[22] = IMG_LoadTexture(Renderer,"Images/SheildHp.png");
    ItemImages[23] = IMG_LoadTexture(Renderer,"Images/SniperDown.png");
    ItemImages[24] = IMG_LoadTexture(Renderer,"Images/Bat2Hp.png");
    ItemImages[25] = IMG_LoadTexture(Renderer,"Images/ShockHp.png");
    ItemImages[26] = IMG_LoadTexture(Renderer,"Images/Shoe2.png");
    ItemImages[27] = IMG_LoadTexture(Renderer,"Images/Shoe3.png");
    ItemImages[29] = IMG_LoadTexture(Renderer,"Images/MachineUp.png");
    ItemImages[30] = IMG_LoadTexture(Renderer,"Images/SMGPower.png");

    ItemImages[12] = IMG_LoadTexture(Renderer,"Images/MapUpgrade.png");
    ItemImages[13] = IMG_LoadTexture(Renderer,"Images/JumpUpgrade.png");
    ItemImages[14] = IMG_LoadTexture(Renderer,"Images/RPGNoob.png");
    ItemImages[15] = IMG_LoadTexture(Renderer,"Images/Platform.png");

    ItemImages[16] = IMG_LoadTexture(Renderer,"Images/BombB.png");
    ItemImages[17] = IMG_LoadTexture(Renderer,"Images/HealUse.png");
    ItemImages[18] = IMG_LoadTexture(Renderer,"Images/MachineGun.png");
    ItemImages[20] = IMG_LoadTexture(Renderer,"Images/OriginalWeapon.png");
    ItemImages[32] = IMG_LoadTexture(Renderer,"Images/PrimarySmg.png");

    ItemImages[21] = IMG_LoadTexture(Renderer,"Images/ProAim.png");
    ItemImages[28] = IMG_LoadTexture(Renderer,"Images/SwimUp.png");
    ItemImages[31] = IMG_LoadTexture(Renderer,"Images/RedDotSight.png");
}

void LoadText(){
    int I;
    for(I=32; I<128; I++){
        char A[12];
        char B[13] = "text/000.png";
        sprintf(A, "%d", I);

        if(I>=100){
            B[5]=A[0];
            B[6]=A[1];
            B[7]=A[2];
        }else{
            B[6]=A[0];
            B[7]=A[1];
        }

        TextImg[I] = IMG_LoadTexture(Renderer,B);
    }
}

void LoadHatImg(){
    HatImgs[1] = IMG_LoadTexture(Renderer,"Images/Hats/Sheild.png");
    HatImgs[2] = IMG_LoadTexture(Renderer,"Images/Hats/Shoe.png");
    HatImgs[3] = IMG_LoadTexture(Renderer,"Images/Hats/Bullet.png");
    HatImgs[4] = IMG_LoadTexture(Renderer,"Images/Hats/MedPack.png");
    HatImgs[5] = IMG_LoadTexture(Renderer,"Images/Hats/Glass.png");
    HatImgs[6] = IMG_LoadTexture(Renderer,"Images/Hats/Stone2.png");
}

void DrawImg(int Id, int X, int Y, int Height, int Width){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY+1;
    Rect.w=Width*ScaleX+1;
    SDL_RenderCopy(Renderer,Images[Id],NULL,&Rect);
}

void DrawImgP(int Id, int X, int Y, int Height, int Width){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_RenderCopy(Renderer,PlayerImages[Id],NULL,&Rect);
}

void DrawImgI(int Id, int X, int Y, int Height, int Width){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_RenderCopy(Renderer,ItemImages[Id],NULL,&Rect);
}

void SeeThru(int Id,int Alpha){
    SDL_SetTextureAlphaMod(Images[Id],Alpha);
}

void Rotated(int Id, int X, int Y, int Height, int Width, int CX, int CY, double Angle, int Flip){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_Point Point;
    Point.x=CX*ScaleX;
    Point.y=CY*ScaleY;
    SDL_RenderCopyEx(Renderer,Images[Id],NULL,&Rect,Angle,&Point,Flip);
}

void Rotated2(int Id, int X, int Y, int Height, int Width, int Flip){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_Point Point;
    Point.x=0;
    Point.y=0;
    SDL_RenderCopyEx(Renderer,PlayerImages[Id],NULL,&Rect,0,&Point,Flip);
}

void Text(int Id, int X, int Y, int Width, int Height){
    if(Id==112||Id==113||Id==103){
        Y+=Width/3;
    }
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_RenderCopy(Renderer,TextImg[Id],NULL,&Rect);
}

void DrawHat(int Id, int X, int Y, int Width, int Height){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_RenderCopy(Renderer,HatImgs[Id],NULL,&Rect);
}

void ImgAnim(int Id, int X, int Y, int Height, int Width, int Number, int Size, int Height2){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY+1;
    Rect.w=Width*ScaleX+1;

    SDL_Rect Rect2;
    Rect2.x=Size*Number;
    Rect2.y=0;
    Rect2.h=Height2;
    Rect2.w=Size;

    SDL_RenderCopy(Renderer,Images[Id],&Rect2,&Rect);
}

void RotateAnim(int Id, int X, int Y, int Height, int Width, int CX, int CY, double Angle, int Flip, int Number, int Size, int Height2){
    SDL_Rect Rect;
    Rect.x=X*ScaleX;
    Rect.y=Y*ScaleY;
    Rect.h=Height*ScaleY;
    Rect.w=Width*ScaleX;
    SDL_Point Point;
    Point.x=CX*ScaleX;
    Point.y=CY*ScaleY;

    SDL_Rect Rect2;
    Rect2.x=Size*Number;
    Rect2.y=0;
    Rect2.h=Height2;
    Rect2.w=Size;

    SDL_RenderCopyEx(Renderer,Images[Id],&Rect2,&Rect,Angle,&Point,Flip);
}


#endif
