#ifndef MAP
#define MAP

void RoomMap(){
    int ForX,ForY;

    for(ForX=0; ForX<GetRoom(MapX,MapY).Width/TileSize; ForX++){
        for(ForY=0; ForY<GetRoom(MapX,MapY).Height/TileSize; ForY++){
            if(GetRoom(MapX,MapY).Area>2){
                if(ForX%3==0&&ForY%3==0){
                    DrawImg(43+(GetRoom(MapX,MapY).Area-3)*2, TileSize*ForX + OffsetX, TileSize*ForY + OffsetY, TileSize*3, TileSize*3);
                }
                if(MapArray[ForX][ForY]==1||MapArray[ForX][ForY]==2){
                    DrawImg(42+(GetRoom(MapX,MapY).Area-3)*2,TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize,TileSize);
                }
                if(MapArray[ForX][ForY]==4){
                    DrawImg(42+(GetRoom(MapX,MapY).Area-3)*2,TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize/2,TileSize);
                }
            }else{
                if(ForX%3==0&&ForY%3==0){
                    DrawImg(1+GetRoom(MapX,MapY).Area*2, TileSize*ForX + OffsetX, TileSize*ForY + OffsetY, TileSize*3, TileSize*3);
                }
                if(MapArray[ForX][ForY]==1||MapArray[ForX][ForY]==2){
                    DrawImg(0+GetRoom(MapX,MapY).Area*2,TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize,TileSize);
                }
                if(MapArray[ForX][ForY]==4){
                    DrawImg(0+GetRoom(MapX,MapY).Area*2,TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize/2,TileSize);
                }
            }
            if(MapArray[ForX][ForY]==-1){
                //color(30+Random(-1,1),30+Random(-1,1),200+Random(-1,1),255);
                color(BRed+Random(0,1),BGreen+Random(0,1),BBlue+Random(0,1),255);
                FillRect(TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize+1,TileSize+1);
            }
        }
    }
}

void DrawFourground(){
    int ForX,ForY;

    for(ForX=0; ForX<GetRoom(MapX,MapY).Width/TileSize; ForX++){
        for(ForY=0; ForY<GetRoom(MapX,MapY).Height/TileSize; ForY++){
            if(GetRoom(MapX,MapY).Area==3){
                if(MapArray[ForX][ForY]==5){
                    ImgAnim(13,TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize,TileSize,GetAnimation(5,10),32,32);
                }
            }else{
                if(MapArray[ForX][ForY]==5){
                    ImgAnim(31,TileSize*ForX +OffsetX,TileSize*ForY +OffsetY,TileSize,TileSize,GetAnimation(5,10),32,32);
                }
            }
        }
    }

    if(GetRoom(MapX,MapY).Type[9]=='v'){
        DrawImg(56,6*TileSize+200,4*TileSize,TileSize*2, TileSize*3);

        if(intersept(X,Y,TileSize,TileSize,7*TileSize+TileSize/2,4*TileSize,1,TileSize*2)){
            if(HasSaved==0){
                HasSaved=1;
                Menu=54;
                LoadMenu(Menu);
                OnMenu=2;
                OldSpeed=Speed;
                Speed=0;
                X=7*TileSize;
                Direction=0;
            }
        }
    }
}

void MiniMap(){
    /// //////////////////////////////// not stats //////////////////////////////// ///

    if(MapLevel>0){

    color(150,150,150,255);
    FillRect(0,0,200,200);
    color(0,0,0,255);
    EmptyRect(0,0,200,200);

    int ForX,ForY;
    int Scale = 5;

    SDL_Rect rect;
    MakeRect(&rect,0,0,200*ScaleX,200*ScaleY);

    SDL_RenderSetClipRect(Renderer,&rect);

    for(ForX=0; ForX<120; ForX++){
        for(ForY=0; ForY<120; ForY++){
            if(knownRooms[ForX][ForY]!=0&&GetRoom(ForX,ForY).BigRoom<1){
                if(GetRoom(ForX,ForY).Type[8]=='p'){
                    color(255,0,0,255);
                }else if(GetRoom(ForX,ForY).Type[7]=='i'){
                    color(0,0,255,255);
                }else if(GetRoom(ForX,ForY).Type[9]=='v'){
                    color(150,0,255,255);
                }else if(GetRoom(ForX,ForY).BigRoom<0){
                    color(0,255,0,255);
                }else{
                    color(255,255,255,255);
                }

                FillRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,Scale,Scale);
                color(0,0,0,255);
                EmptyRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,Scale,Scale);
            }
            /// big rooms ///
            if(knownRooms[ForX][ForY]!=0&&GetRoom(ForX,ForY).BigRoom==1&&RoomPos[ForX][ForY]!=0){
                color(255,255,255,255);
                FillRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,20/MapZoom,20/MapZoom);
                color(0,0,0,255);
                EmptyRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,20/MapZoom,20/MapZoom);
            }
            if(knownRooms[ForX][ForY]!=0&&GetRoom(ForX,ForY).BigRoom==5&&RoomPos[ForX][ForY]!=0){
                color(255,255,255,255);
                FillRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,20/MapZoom,Scale);
                color(0,0,0,255);
                EmptyRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,20/MapZoom,Scale);
            }
            if(knownRooms[ForX][ForY]!=0&&GetRoom(ForX,ForY).BigRoom==7&&RoomPos[ForX][ForY]!=0){
                color(255,255,255,255);
                FillRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,Scale,20/MapZoom);
                color(0,0,0,255);
                EmptyRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,Scale,20/MapZoom);
            }

            if((MouseX-MapOfX)/(Scale)==ForX&&(MouseY-MapOfY)/(Scale)==ForY){
                color(255,0,255,255);
                FillRect(ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,Scale,Scale);
            }
            if(Rooms[RoomPos[ForX][ForY]].DropId!=0){
                DrawImgI(Rooms[RoomPos[ForX][ForY]].DropId-1,ForX*(Scale)+MapOfX,ForY*(Scale)+MapOfY,Scale,Scale);
            }
        }
    }

    MakeRect(&rect,0,0,VWidth+400*ScaleX,VHeight);
    SDL_RenderSetClipRect(Renderer,&rect);

    if(MapFlash>15){
        color(0,0,0,255);
        FillRect(MapX*(10/MapZoom)+MapOfX, MapY*(10/MapZoom)+MapOfY, 10/MapZoom, 10/MapZoom);
    }

    MapFlash+=1;
    if(MapFlash>=31){MapFlash=0;}

    }


    /// ///// //// // -=limits=- // //// ///// ///

    if(FireRate<3){FireRate=3;}
    if(Speed>11){Speed=11;}

    if(Charge>MaxCharge){Charge=MaxCharge;}
    if(Charge<0){Charge=0;}
    if(Ammo>MaxAmmo){Ammo=MaxAmmo;}
    if(Ammo<0){Ammo=0;}
    if(Health>MaxHealth){Health=MaxHealth;}
    if(Sheild>MaxSheild){Sheild=MaxSheild;}


    /// stats ///

    color(150,0,0,255);
    FillRect(Width+210,260,180,30);
    color(255,0,0,255);
    EmptyRect(Width+210,260,180,30);

    color(255,0,0,255);//176
    if(Health>0){
        FillRect(Width+212,262,((float)Health/(float)MaxHealth)*176,26);
    }

    if(MaxSheild>1){
        color(200,150,0,255);
        FillRect(Width+210,210,180,30);
        color(255,200,0,255);
        EmptyRect(Width+210,210,180,30);

        color(255,200,0,255);//176
        FillRect(Width+212,212,(Sheild/(float)MaxSheild)*176,26);
    }


    if(Weapon!=0){
        color(50,50,50,255);
        FillRect(Width+210,310,180,30);
        color(100,100,100,255);
        EmptyRect(Width+210,310,180,30);

        color(100,100,100,255);//176
        FillRect(Width+212,312,(Ammo/(float)MaxAmmo)*176,26);
    }


    if(ChargeWeapon!=0){
        color(0,150,100,255);
        FillRect(Width+210,360,180,30);
        color(0,255,200,255);
        EmptyRect(Width+210,360,180,30);

        color(0,255,200,255);//176
        FillRect(Width+212,362,(Charge/(float)MaxCharge)*176,26);

        color(0,255,200,255);
        FillRect(Width+212+(Abilities[(int) ChargeWeapon].Cost/(float)MaxCharge)*176,360,2,30);
    }


    /// //////////////////////////////// stats 2 //////////////////////////////// ///

    if(MapLevel>1){

    color(0,150,0,255);
    FillRect(10,210,180,30);
    color(0,255,0,255);
    EmptyRect(10,210,180,30);

    color(0,255,0,255);//176
    FillRect(12,212,25*(Speed-4),26);


    color(150,150,0,255);
    FillRect(10,260,180,30);
    color(255,255,0,255);
    EmptyRect(10,260,180,30);

    color(255,255,0,255);//176
    FillRect(12,262,20*(JumpPower-18)+16,26);


    color(150,25,25,255);
    FillRect(10,310,180,30);
    color(255,50,50,255);
    EmptyRect(10,310,180,30);

    color(255,50,50,255);//176
    FillRect(12,312,11*(12-(FireRate-7)),26);


    color(75,0,0,255);
    FillRect(10,360,180,30);
    color(150,0,0,255);
    EmptyRect(10,360,180,30);

    color(150,0,0,255);//176ItemRooms
    FillRect(12,362,6*(Damage)/10,26);

    if(MapLevel>2){

        color(150,0,0,255);
        FillRect(10,410,180,30);
        color(255,0,0,255);
        EmptyRect(10,410,180,30);

        color(255,0,0,255);//176
        FillRect(12,412,(MaxHealth)/15,26);

        color(200,150,0,255);
        FillRect(10,460,180,30);
        color(255,200,0,255);
        EmptyRect(10,460,180,30);

        color(255,200,0,255);//176
        FillRect(12,462,(MaxSheild)/10,26);


        color(50,50,50,255);
        FillRect(10,510,180,30);
        color(100,100,100,255);
        EmptyRect(10,510,180,30);

        color(100,100,100,255);//176
        FillRect(12,512,(MaxAmmo)*5/10,26);


        color(0,150,100,255);
        FillRect(10,560,180,30);
        color(0,255,200,255);
        EmptyRect(10,560,180,30);

        color(0,255,200,255);//176
        FillRect(12,562,(MaxCharge),26);
    }

    }


    /// //// ///// weapon picture ///// //// ////


    color(50,50,50,255);
    FillRect(Width +210, Height-190, 180, 180);

    int I;
    for(I=0; I<100; I+=10){
        color(50 + I/2, 50 + I/2, 50 + I/2, 255);
        FillRect(Width +210+I/2, Height-190+I/2, 180-I, 180-I);
    }

    if(Weapon!=0){
        DrawImgI(Weapons[(int) Weapon].ImageId+3, Width +210, Height-190, 180, 180);
    }

    color(50,50,255,255);
    FillRect(Width +210, 10, 180, 180);

    for(I=0; I<100; I+=10){
        color(50 + I/3, 150 + I/3, 255, 255);
        FillRect(Width +210+I/2, 10+I/2, 180-I, 180-I);
    }

    if(ChargeWeapon!=0){
        DrawImgI(Abilities[(int) ChargeWeapon].ImageId, Width +210, 10, 180, 180);
    }

}

#endif
