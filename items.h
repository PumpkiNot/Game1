#ifndef ITEMS
#define ITEMS

void OpenRoom();
void FinishRoom();
Room GetRoom(int ZXC, int TYU);

typedef struct Entitys1{
int X,Y;
int Set;
int Sets[5];
int *Special;
int *Specials[5];
int SpecialMod;
int SpecialMods[5];
float boosts[5];
char Name[20];
int Used;
int ImageId;
int Once;

int Damage;
int ChargeAmount;
int RapidFire;
int PlayerImage;
int IsPrimary;
int FireRate;
int BulletImage;

int IsHoldAble;
}item;

item ItemPre[30];
item SpecialPre[10];
item Weapons[15];
item Item;

item NewItem(int Set, int *Special, int SpecialMod, char Namee[20], int ImageId){
    item Itemm;

    int T;
    for(T=0; T<20; T++){
        Itemm.Name[T]=Namee[T];
    }
    for(T=0; T<5; T++){
        Itemm.SpecialMods[T]=0;
        Itemm.Sets[T]=0;
    }

    Itemm.Special=Special;
    Itemm.Used=0;
    Itemm.SpecialMod=SpecialMod;
    Itemm.ImageId=ImageId;
    Itemm.Set=Set;
    Itemm.Once=0;
    Itemm.IsHoldAble=0;

    return Itemm;
}

item NewPrimary(int Damage, int ChargeAmount, int RapidFire, int FireRatee, int PlayerImage, int Accuricyy, char Namee[15], int ImageId, int BulletImg){
    item Itemm;

    int T;
    for(T=0; T<15; T++){
        Itemm.Name[T]=Namee[T];
    }
    for(T=0; T<5; T++){
        Itemm.SpecialMods[T]=0;
    }

    Itemm.Used=0;
    Itemm.ImageId=ImageId;

    Itemm.Damage=0;
    Itemm.ChargeAmount=ChargeAmount;
    Itemm.RapidFire=RapidFire;
    Itemm.PlayerImage=PlayerImage;
    Itemm.IsPrimary=1;
    Itemm.IsHoldAble=0;
    Itemm.FireRate=0;
    Itemm.Special=NULL;
    Itemm.BulletImage=BulletImg;
    Itemm.Once=0;
    Itemm.Specials[0]=(int*) &Accuricy;
    Itemm.SpecialMods[0]=Accuricyy;
    Itemm.Sets[0]=1;
    Itemm.Specials[1]=(int*) &DmgMultiply;
    Itemm.SpecialMods[1]=Damage;
    Itemm.Sets[1]=1;
    Itemm.Specials[2]=(int*) &FireMultiply;
    Itemm.SpecialMods[2]=FireRatee;
    Itemm.Sets[2]=1;

    return Itemm;
}

void loadItems(){
    ItemRandom=23;
    ItemPre[7]=NewItem(0,(int*) &MaxSheild,240,"Sheild Boost",6);
    ItemPre[0]=NewItem(0,(int*) &MaxHealth,250,"Health Boost",1);
    ItemPre[1]=NewItem(0,(int*) &JumpPower,1,"Jump Boost",2);
    ItemPre[2]=NewItem(0,(int*) &Speed,1,"Speed Boost",3);
    ItemPre[3]=NewItem(0,(int*) &FireRate,-2,"FireRate Boost",4);
    ItemPre[4]=NewItem(0,(int*) &Damage,30,"Damage Boost",5);
    ItemPre[6]=NewItem(0,(int*) &MaxCharge,25,"Charge Boost",7);
    ItemPre[5]=NewItem(0,(int*) &MaxAmmo,50,"Ammo Boost",8);

    ItemPre[14]=NewItem(0,(int*) &MaxHealth,150,"Health + Sheild",19);
    ItemPre[14].Specials[0]=(int*) &MaxSheild;   ItemPre[14].SpecialMods[0]=150;
    ItemPre[15]=NewItem(0,(int*) &FireRate,5,"Slow Shots",20);
    ItemPre[15].Specials[0]=(int*) &Damage;   ItemPre[15].SpecialMods[0]=20;
    ItemPre[16]=NewItem(0,(int*) &MaxCharge,-15,"Battery -> Hp",21);
    ItemPre[16].Specials[0]=(int*) &MaxHealth;   ItemPre[16].SpecialMods[0]=250;
    ItemPre[19]=NewItem(0,(int*) &MaxHealth,-250,"Electric Shock",22);
    ItemPre[19].Specials[0]=(int*) &MaxSheild;   ItemPre[16].SpecialMods[0]=250;
    ItemPre[20]=NewItem(0,(int*) &FireRate,-5,"Fast Shots",26);
    ItemPre[20].Specials[0]=(int*) &Damage;   ItemPre[20].SpecialMods[0]=-15;
    ItemPre[21]=NewItem(0,(int*) &FireRate,-1,"blind shooting",27); ///
    ItemPre[21].Specials[0]=(int*) &Accuricy;   ItemPre[21].SpecialMods[0]=3;
    ItemPre[21].Specials[1]=&RapidFire;   ItemPre[21].SpecialMods[1]=1; ItemPre[21].Sets[1]=1;
    ItemPre[21].Specials[2]=(int*) &Damage;   ItemPre[21].SpecialMods[2]=-10;

    ItemPre[8]=NewItem(1,(int*) &SaftyPlat, 1,"moron proofing",12);
    ItemPre[9]=NewItem(1,(int*) &Weapon,2,"noob machine gun",15);  ItemPre[9].IsHoldAble=9;  ItemPre[9].IsPrimary=1;
    ItemPre[10]=NewItem(1,(int*) &ChargeWeapon,1,"portable bomb",13);  ItemPre[10].IsHoldAble=10;  ItemPre[10].IsPrimary=2;
    ItemPre[11]=NewItem(1,(int*) &ChargeWeapon,2,"charge -> health",14);  ItemPre[11].IsHoldAble=11;  ItemPre[11].IsPrimary=2;
    ItemPre[12]=NewPrimary(200,2,0,200,11,0,"original pistol", 17, 11);
    ItemPre[13]=NewItem(1,(int*) &Weapon,1,"Fire Launcher",11);  ItemPre[13].IsHoldAble=13;  ItemPre[13].IsPrimary=1;
    ItemPre[17]=NewItem(1,(int*) &Speed, 8,"pr0 sh03s",23);
    ItemPre[18]=NewItem(1,(int*) &Speed, 9,"ULTRA SHOOS",24);
    ItemPre[22]=NewItem(1,(int*) &Accuricy, 0,"Red Dot Sight",28); ///
    ItemPre[23]=NewPrimary(40,1,1,50,14,3,"smg", 29, 36); ///

    /// special ///
    SpecialPre[0]=NewItem(0,(int*) &MapLevel,1,"Map Boost",9);
    SpecialPre[2]=NewItem(0,(int*) &JumpLevel,1,"Short Hops",10);
    SpecialPre[4]=NewItem(1,(int*) &Weapon,1,"Fire Launcher",11); SpecialPre[4].IsHoldAble=13;  SpecialPre[4].IsPrimary=1;
    SpecialPre[5]=NewItem(0,(int*) &MaxSheild,24,"Shield Boost",6);
    SpecialPre[6]=NewItem(0,(int*) &Damage,25,"Helper",5);
    SpecialPre[7]=NewItem(1,(int*) &ProAim,1,"360",18);
    SpecialPre[8]=NewItem(1,(int*) &CanSwim,1,"Swimming lessons",25);
    SpecialPre[9]=NewItem(1,(int*) &CanSwim,1,"Swimming lessons",25);

    /// secondarys ///
    Weapons[1]=SpecialPre[4];
    Weapons[2]=ItemPre[9];
}

void UpdateItem(){
    if(intersept(Item.X,Item.Y,TileSize,TileSize,X,Y,TileSize,TileSize)){
        if(Item.Used==0){
            Item.Used=1;
            //Mix_PlayChannel(-1, CollectSound, 0);
            PlaySoundPro(3);

            if(Item.Special!=NULL){
                if(Item.Set==0){
                    *Item.Special+=Item.SpecialMod;
                }else{
                    *Item.Special=Item.SpecialMod;
                }
            }else if(Item.IsPrimary==1&&Item.IsHoldAble==0){
                ChargeAmount = Item.ChargeAmount;
                RapidFire = Item.RapidFire*FireMultiply;
                PlayerWeaponId = Item.PlayerImage;
                BulletImage = Item.BulletImage;
                RapidFire = Item.RapidFire;
            }
            if(Damage<=2){
                Damage=3;
            }

            if(Item.IsHoldAble!=0){
                int HoldNumber;
                int HeldX, HeldY;

                HeldX=Item.X;
                HeldY=Item.Y;
                if(Item.IsPrimary==1){
                    if(SecondaryId!=0){
                        HoldNumber=SecondaryId;
                        SecondaryId=Item.IsHoldAble;

                        Rooms[RoomPos[MapX][MapY]].ItemId=HoldNumber;
                        Item=ItemPre[HoldNumber];
                        Item.X=HeldX;
                        Item.Y=HeldY;

                        Item.Used=1;
                    }else{
                        SecondaryId=Item.IsHoldAble;
                        Rooms[RoomPos[MapX][MapY]].ItemId=0;
                        Item.IsHoldAble=0;
                        Item.Used=1;
                    }
                }else if(Item.IsPrimary==2){
                    if(UsableId!=0){
                        HoldNumber=UsableId;
                        UsableId=Item.IsHoldAble;

                        Rooms[RoomPos[MapX][MapY]].ItemId=HoldNumber;
                        Item=ItemPre[HoldNumber];
                        Item.X=HeldX;
                        Item.Y=HeldY;

                        Item.Used=1;
                    }else{
                        UsableId=Item.IsHoldAble;
                        Rooms[RoomPos[MapX][MapY]].ItemId=0;
                        Item.IsHoldAble=0;
                        Item.Used=1;
                    }
                }
            }


            int II;
            for(II=0; II<5; II++){
                if(Item.SpecialMods[II]!=0&&Item.Specials[II]!=NULL){
                    if(Item.Sets[II]==0){
                        *Item.Specials[II]+=Item.SpecialMods[II];
                    }else{
                        if(Item.Specials[II]==(int*) &DmgMultiply){
                            if(DmgMultiply<100){
                                Damage=Damage*(100/DmgMultiply);
                            }else{
                                Damage=Damage/(DmgMultiply/100);
                            }
                            DmgMultiply=Item.SpecialMods[II];
                            if(DmgMultiply<100){
                                Damage=Damage/(100/DmgMultiply);
                            }else{
                                Damage=Damage*(DmgMultiply/100);
                            }
                        }else if(Item.Specials[II]==(int*) &FireMultiply){
                            if(FireMultiply<100){
                                FireRate=FireRate*(100/FireMultiply);
                            }else{
                                FireRate=FireRate/(FireMultiply/100);
                            }
                            FireMultiply=Item.SpecialMods[II];
                            if(FireMultiply<100){
                                FireRate=FireRate/(100/FireMultiply);
                            }else{
                                FireRate=FireRate*(FireMultiply/100);
                            }
                        }else{
                            *Item.Specials[II]=Item.SpecialMods[II];
                        }
                    }
                }
            }

            int O=0,OO=0;
            for(O=0; O<30; O++){
                for(OO=0; OO<20; OO++){
                    if(Area!=3){
                        if(MapArray[O][OO]==2){MapArray[O][OO]=0;}
                    }else{
                        if(MapArray[O][OO]==2){MapArray[O][OO]=5;}
                    }
                }
            }

            for(O=0; O<20; O++){
                TempItemName[O] = 0;
                TempItemName[O] = Item.Name[O];
            }
            ItemTitle=100;

            FinishRoom();

            if(Area==3){
                ZAwaken=1;
                int I;
                for(I=0; I<30; I++){
                    if(Enemys[I].Type==3){
                        Enemys[I].Sleeping=2;
                        Enemys[I].Walking=0;
                        Enemys[I].Counter=0;
                        Enemys[I].Spawning=0;
                    }
                }
            }
        }
    }else if(Item.IsHoldAble!=0&&GetRoom(MapX,MapY).IsItemRoom==1){
        if(Item.IsPrimary==1&&Item.IsHoldAble!=SecondaryId){
            Item.Used=0;
        }else if(Item.IsPrimary==2&&Item.IsHoldAble!=UsableId){
            Item.Used=0;
        }
    }


    if(Rooms[RoomPos[MapX][MapY]].IsItemRoom==1){
        DrawImgI(19, Item.X+OffsetX, Item.Y+OffsetY, TileSize, TileSize);
    }
    if(Item.Used!=1||(Item.IsHoldAble!=0&&Item.IsPrimary!=0&&GetRoom(MapX,MapY).IsItemRoom==1)){
        DrawImgI(Item.ImageId+3, Item.X+OffsetX, Item.Y+OffsetY + (int)(sin(MainAdder/4)*5) - 14, TileSize, TileSize);
    }
}

void SpawnItem(int XX,int YY, int Id){
    Item=ItemPre[Id];
    Item.X=XX;
    Item.Y=YY;
}

void SpawnSpecial(int XX,int YY, int Id){
    Item=SpecialPre[Id];
    Item.X=XX;
    Item.Y=YY;
}

#endif
