#ifndef MENU
#define MENU

void ResetGame();

typedef struct GameThing{
int X;
int Y;
int Width;
int Height;
int ImageId;
int Active;
int ActivateId;
char Info[10];
}Button;

int ButtonCount = 0;
int MaxHats = 8;
Button buttons[10];

void MakeHat(int Id, int Hp, int Hdamage, int HShield, int HSpeed, int ImageId, char Name[20]){
    hats[Id].Hp=Hp*10;
    hats[Id].Damage=Hdamage;
    hats[Id].Sheild=HShield*10;
    hats[Id].Speed=HSpeed;
    hats[Id].ImageId=ImageId;
    int I;
    for(I=0; I<20; I++){
        hats[Id].Name[I] = Name[I];
    }
}

void SpecialHat(int Id, int *Special, int Mod){
    hats[Id].Special=Special;
    hats[Id].SpecialMod=Mod;
}

void LoadHats(){
    strcpy((char*)(&hats[0].Name),"no hat");    hats[0].IsUnlocked=1;
    MakeHat(1,25,0,0,0,4,"Healthy Square"); /// second boss
    MakeHat(2,-25,10,0,0,3,"Headshot"); /// third boss
    MakeHat(3,-50,0,25,0,1,"Shield Up"); ///first boss
    MakeHat(4,0,0,0,1,2,"Shoes = Speeds"); ///first boss
    MakeHat(5,-99,50,0,0,5,"fragile + dangerous"); ///third boss
    SpecialHat(5,&OneHit,1);
    MakeHat(6,0,0,0,0,3,"rapid fire");/// second boss
    SpecialHat(6,&RapidFire,1);
    MakeHat(7,0,0,0,0,6,"noob hat");/// first boss
    SpecialHat(7,(int*) &SaftyPlat,1);
    MakeHat(8,0,0,0,0,500,"corruption"); ///third boss
    SpecialHat(8,(int*) &Corrupted,1);
}

void StartGame(){
    int Held;
    MapX=30;
    MapY=30;

    if(Seed==0){ Seed = Random(0,2000); }
    srand(Seed);

    OnMenu=1;
    RoomAmount = 0;

    RoomAmount += MakeFloor(42,2,1,30,30,0);
    RoomAmount += MakeSaveRoom(RoomAmount,1,43); Held=RoomAmount;

    RoomAmount += MakeFloor(60,3,RoomAmount,30,50,1);
    RoomAmount += MakeSaveRoom(RoomAmount,Held,Held+60); Held=RoomAmount;

    RoomAmount += MakeFloor(70,3,RoomAmount,50,30,2);
    RoomAmount += MakeSaveRoom(RoomAmount,Held,Held+70); Held=RoomAmount;

    RoomAmount += MakeFloor(70,4,RoomAmount,50,50,4);
    RoomAmount += MakeSaveRoom(RoomAmount,Held,Held+70); Held=RoomAmount;

    RoomAmount += MakeElevator(RoomAmount,1,40,45,105);
    RoomAmount += MakeElevator(RoomAmount,109,179,45,105);
    RoomAmount += MakeElevator(RoomAmount,45,105,186,186+70);
    RoomAmount += MakeBossRoom(1,44,RoomAmount,0);
    RoomAmount += MakeBossRoom(45,110,RoomAmount,1);
    RoomAmount += MakeBossRoom(110,180,RoomAmount,2);
    RoomAmount += MakeBossRoom(186,186+70,RoomAmount,4);

    RoomPair[0][0]=Rooms[RoomAmount-1];
    SetRoom(RoomPos[MapX][MapY]);
    loadMap(Rooms[RoomPos[MapX][MapY]].Type,1);

    /// / / // / / ///
    if(Random(0,1)==1){
        RoomAmount += MakeRoom(RoomAmount,0,0,3,1,"a/spc4/biA2.txt");
    }else{ RoomAmount += MakeRoom(RoomAmount,0,0,3,1,"a/spc4/biB2.txt"); }

    if(Random(0,1)==1){
        RoomAmount += MakeRoom(RoomAmount,2,1,3,2,"a/spc4/loA3.txt");
        RoomAmount += MakeRoom(RoomAmount,5,3,3,2,"a/spc4/loB3.txt");
    }else{ RoomAmount += MakeRoom(RoomAmount,2,1,3,2,"a/spc4/loB3.txt");
        RoomAmount += MakeRoom(RoomAmount,5,3,3,2,"a/spc4/loA3.txt");}

    if(Random(0,1)==1){
        RoomAmount += MakeRoom(RoomAmount,4,1,3,2,"a/spc4/loA4.txt");
    }else{ RoomAmount += MakeRoom(RoomAmount,4,1,3,2,"a/spc4/loB4.txt"); }

    if(Random(0,1)==1){
        RoomAmount += MakeRoom(RoomAmount,6,1,3,3,"a/spc4/taA5.txt");
        RoomAmount += MakeRoom(RoomAmount,7,2,3,3,"a/spc4/taB7.txt");
    }else{ RoomAmount += MakeRoom(RoomAmount,6,1,3,3,"a/spc4/taB5.txt");
        RoomAmount += MakeRoom(RoomAmount,7,2,3,3,"a/spc4/taA7.txt");}

    if(Random(0,1)==1){
        RoomAmount += MakeRoom(RoomAmount,3,2,3,1,"a/spc4/biA6.txt");
    }else{ RoomAmount += MakeRoom(RoomAmount,3,2,3,1,"a/spc4/biB6.txt"); }
    /// / / // / / ///

    /// ///// ///// ///
    if(UltraHard==1){
        Mode=3;
        HatId=0;
    }
    /// ///// ///// ///

    Speed=7; JumpPower=20; Damage=25;
    Health=1000; MaxHealth=1000; Sheild=1; MaxSheild=1;
    Ammo=100; MaxAmmo=100; Charge=0; MaxCharge=50;
    DmgMultiply=100; FireMultiply=100;
    ProAim=0;
    FireRate=11;
    RapidFire=0;
    SaftyPlat=0;

    MaxHealth+=hats[(int) HatId].Hp;
    Health+=hats[(int) HatId].Hp;
    MaxSheild+=hats[(int) HatId].Sheild;
    Speed+=hats[(int) HatId].Speed;
    Damage+=hats[(int) HatId].Damage;

    if(hats[(int) HatId].Special!=NULL){
        *hats[(int) HatId].Special=hats[(int) HatId].SpecialMod;
    }

    /// ///// ///// ///
    int I;
    for(I=0; I<10; I++){
        Item.Used=1;
    }

    if(Mode==0){
        Health*=2;
    }

    if(Corrupted==1){
        ZAwaken=1;
    }else{
        ZAwaken=0;
    }

    Mix_FadeOutChannel(1,800);
    LastArea=100;

    Menu=100;

    Save2();
}

void MakeButton(int XX, int YY, int Widthh, int Heightt, int ActiveId, char Info[10]){
    int I;
    for(I=0; I<10; I++){
        if(buttons[I].Active==0){
            buttons[I].X=XX;
            buttons[I].Y=YY;
            buttons[I].Width=Widthh;
            buttons[I].Height=Heightt;
            buttons[I].ActivateId=ActiveId;
            buttons[I].Active=1;
            int II;
            for(II=0; II<10; II++){
                buttons[I].Info[II] = Info[II];
            }
            break;
        }
    }
}

void LoadMenu(int Number){
    int I;
    for(I=0; I<10; I++){
        buttons[I].Active=0;
    }

    if(Number==0){

    }else if(Number==1){
        MakeButton(200+Width/2-100, 300, 200, 100, 1,"Start");
        MakeButton(200+Width-50-55, 530, 100, 50, 152,"reset data");
        MakeButton(200+30, Height-140, 100, 50, 16,"+");
        MakeButton(200+30, Height-70, 100, 50, 17,"-");
        MakeButton(200+Width-50-55, 470, 100, 50, 13,"load");
        MakeButton(200+Width/2-75, 540, 150, 50, 18,"Quit");
    }else if(Number==2){
        MakeButton(200+Width/2-50, 530, 100, 50, 2,"Back");
        MakeButton(200+Width/2-100, 400, 200, 100, 1,"Next");

        MakeButton(200+Width/4*3-75, 300, 150, 100, 3,"Hat >>>");
        MakeButton(200+Width/4-75, 300, 150, 100, 4,"<<< Hat");
    }else if(Number==3){
        MakeButton(200+Width/2-150, 030, 300, 100, 6,"Easy");
        MakeButton(200+Width/2-150, 180, 300, 100, 7,"Medium");
        MakeButton(200+Width/2-150, 330, 300, 100, 8,"Hard");
        MakeButton(200+Width/2-150, 480, 300, 100, 9,"Original");
        MakeButton(200+Width-100-150, 255, 200, 100, 20,"Join");
        MakeButton(200+50, 255, 200, 100, 19,"Host");
    }else if(Number==50){
        MakeButton(200+Width/2-150, 480, 300, 100, 10,"Continue");
    }else if(Number==51){
        MakeButton(200+Width/2-350, 20, 700, 200, 11,"-end game-");
        Mix_FadeOutChannel(1,800);
    }else if(Number==52){
        MakeButton(200+Width/2-350, 20, 700, 350, 12,"RESET ALL");
        MakeButton(200+Width/2-200, 390, 400, 200, 100,"Back");
    }else if(Number==53){
        MakeButton(200, 0, Width, Height, 100,"Done...");
    }else if(Number==54){
        MakeButton(200+Width/2-100-130, 100, 200, 100, 14,"Save");
        MakeButton(200+Width/2-100+130, 100, 200, 100, 10,"Don't save");
    }else if(Number==55){
        MakeButton(200+Width/2-250, 80, 500, 200, 15,"Resume");
        MakeButton(200+Width/2-250, 380, 500, 200, 11,"Quit");
        MakeButton(200+30, Height-140, 100, 50, 16,"+");
        MakeButton(200+30, Height-70, 100, 50, 17,"-");
    }
}

void ButtonActivater(int Number){
    if(Number==1){
        Menu+=1;
        LoadMenu(Menu);
    }else if(Number==2){
        Menu-=1;
        LoadMenu(Menu);
    }else if(Number==3){
        int Found=0;
        while(Found==0){
            if(HatId<MaxHats){
                HatId+=1;
            }else{
                HatId=0;
            }
            if(hats[(int) HatId].IsUnlocked==1){
                Found=1;
            }
        }
    }else if(Number==4){
        int Found=0;
        while(Found==0){
            if(HatId>0){
                HatId-=1;
            }else{
                HatId=MaxHats;
            }
            if(hats[(int) HatId].IsUnlocked==1){
                Found=1;
            }
        }
    }else if(Number==5){
        StartGame();
    }else if(Number==6){
        Mode=0;
        StartGame();
    }else if(Number==7){
        Mode=1;
        StartGame();
    }else if(Number==8){
        Mode=2;
        StartGame();
    }else if(Number==9){
        Mode=3;
        StartGame();
    }else if(Number==10){
        OnMenu=1;
        if(Menu==54){
            Speed=OldSpeed;
        }
    }else if(Number==11){
        ResetGame();
    }else if(Number==12){
        int I;
        for(I=0; I<10; I++){
            hats[I].IsUnlocked=0;
        }
        hats[0].IsUnlocked=1;
        Save();

        Menu=53;
        LoadMenu(Menu);
    }else if(Number==13){
        OnMenu=1;
        Load2();
        if(OnMenu==1){
            Menu=100;
            loadMap(Rooms[RoomPos[MapX][MapY]].Type,1);
            HasSaved=1;
        }
    }else if(Number==14){
        if(Menu==54){
            Speed=OldSpeed;
        }
        Save2();
        Save();
        OnMenu=1;
    }else if(Number==15){
        OnMenu=1;
    }else if(Number==16){
        if(Volume<=95){
            Volume+=5;
        }else{
            Volume=100;
        }
        Mix_Volume(1,Volume);
        Mix_Volume(0,Volume);
        int O;
        for(O=2; O<20; O++){
            Mix_Volume(O,Volume);
        }
    }else if(Number==17){
        if(Volume>=5){
            Volume-=5;
        }else{
            Volume=0;
        }
        Mix_Volume(1,Volume);
        Mix_Volume(0,Volume);
        int O;
        for(O=2; O<20; O++){
            Mix_Volume(O,Volume);
        }
    }else if(Number==18){
        Running=0;
    }else if(Number==19){
        Mode=3;
        StartGame();
        Host();
    }else if(Number==20){
        Join();
    }else if(Number>=100){
        Menu=Number-100;
        LoadMenu(Menu);
    }
}

void PressButton(){
    if(OnMenu==1){return;}

    int I;
    for(I=0; I<10; I++){
        Button but = buttons[I];
        if(intersept(MouseX,MouseY,0,0,but.X,but.Y,but.Width,but.Height)==1&&but.Active==1){
            ButtonActivater(but.ActivateId);
            break;
        }
    }
}

void DrawButton(){
    int I;
    for(I=0; I<10; I++){
        Button But = buttons[I];
        if(But.Active==1){
            color(0,0,0,255);
            FillRect(But.X, But.Y, But.Width, But.Height);
            color(255,255,255,255);
            FillRect(But.X+4, But.Y+4, But.Width-8, But.Height-8);

            DrawTextCenter(But.Info,But.X +But.Width/2 ,But.Y +But.Height/2,But.Width/10,But.Width/10);
        }
    }
}

void MenuRender(){
    if(OnMenu==1){return;}

    if(Menu==0){
        DrawTextCenter("Title Screen", 200+Width/2, Height/2, 70, 70);
    }else if(Menu==1){
        if(UltraHard==1){
            char String[100];
            int I;
            for(I=0; I<100; I++){
                String[I]=Random(20,150);
            }
            DrawTextCenter(String, 200+Width/2, 50, 70, 70);
        }else{
            DrawTextCenter("Title Screen", 200+Width/2, 50, 70, 70);
        }
    }else if(Menu==2){
        DrawImgP(0,Width/2+200-100, Height/2-200, 200,200);
        DrawHat(hats[(int) HatId].ImageId,Width/2+200-100 +47, Height/2-200 -80, 100,200);
        DrawTextCenter(hats[(int) HatId].Name, Width/2+200, Height/2+50, 20,20);
    }else if(Menu==50){
        color(Red,Blue,Green,150);
        FillRect(200,0,Width,Height);
        DrawTextCenter(TempItemName,Width/2+200, Height/2, 40,40);
    }else if(Menu==51){
        color((Red+Blue+Green)/2,(Red+Blue+Green)/2,(Red+Blue+Green)/2,150);
        FillRect(200,Height/6*5-25,Width,50);
        DrawTextCenter(TempItemName,Width/2+200, Height/6*5, 40,40);
    }
    DrawButton();
}

void ResetGame(){
    srand(time(NULL));
    Seed=0;

    OnMenu=0;
    Menu=1;
    LoadMenu(Menu);
    Health=100;
    MapLevel=1;
    X=450;
    Y=300;
    UsableId=0;
    SecondaryId=0;
    Weapon=0;
    ChargeWeapon=0;
    Boss1.Timer=0;
    PlayerWeaponId=6;
    BulletImage=36;
    Accuricy=0;
    ZAwaken=0;

    int I, II;
    for(I=0; I<120; I++){
        for(II=0; II<120; II++){
            RoomPos[I][II]=0;
            knownRooms[I][II]=0;
            RoomPair[I][II]=Rooms[0];
        }
    }
    for(I=0; I<ItemRandom; I++){
        ItemPre[I].Used=0;
    }
    for(I=0; I<350; I++){
        Rooms[I].BigRoom=0;
        Rooms[I].Direct=0;
        Rooms[I].Id=0;
        Rooms[I].Finished=0;
        Rooms[I].DropId=0;
        strcpy((char*)Rooms[I].Type,"a/1234/1.txt");
    }
    for(I=0; I<30; I++){
        Enemys[I].Alive=0;
    }
    for(I=0; I<30; I++){
        Bullets[I].Alive=0;
    }
    Boss1.Alive=0;
}

#endif
