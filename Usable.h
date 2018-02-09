#ifndef USABLE
#define USABLE

typedef struct weapons{
int Cost;
int ImageId;
}Ability;

Ability Abilities[15];

void SetAbility(int Id, int Cost, int ImageId){
    Abilities[Id].Cost=Cost;
    Abilities[Id].ImageId=ImageId;
}

void LoadAbilitys(){
    SetAbility(1, 17, 16);
    SetAbility(2, 1, 17);
}

void UseUsable(int Usable){
    if(Usable==1 && Charge>=17){
        SpawnExplode(X+TileSize/2, Y+TileSize/2,400,150);
        Charge-=17;
    }
    else if(Usable==2 && Charge>=1){
        Health+=Charge*15;
        Charge-=Charge;
    }
    else if(Usable==3 && Charge>=1){
        Ammo+=Charge/3;
        Charge-=Charge;
    }
}

#endif
