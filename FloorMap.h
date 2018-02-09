#ifndef FLOORMAP
#define FLOORMAP

#include <string.h>

int MakeRoom(int Id, int X, int Y, int Area, int BigRoom, char String[17]);

/// //// ///// /////// ///// //// ///

Room GetRoom(int ZXC, int TYU){
    Room Rom = Rooms[RoomPos[ZXC][TYU]];
    if(Rom.Width<Width){
        Rom.Width=Width;
    }
    if(Rom.Height<Height){
        Rom.Height=Height;
    }
    return Rom;
}

void SetRoom(int I){
        int On=0;
        char Arrayy[5]={'-','-','-','-',0};

        if(RoomPos[Rooms[I].X][Rooms[I].Y-1]!=0||GetRoom(Rooms[I].X,Rooms[I].Y-1).BigRoom!=0){
            if(GetRoom(Rooms[I].X,Rooms[I].Y-1).Direct==3||GetRoom(Rooms[I].X,Rooms[I].Y-1).Direct==0){
                Arrayy[On]='1';
                if(Rooms[I].Direct==0){On+=1;}
            }
        }
        if(RoomPos[Rooms[I].X+1][Rooms[I].Y]!=0||GetRoom(Rooms[I].X+1,Rooms[I].Y).BigRoom!=0){
            if(GetRoom(Rooms[I].X+1,Rooms[I].Y).Direct==4||GetRoom(Rooms[I].X+1,Rooms[I].Y).Direct==0){
                Arrayy[On]='2';
                if(Rooms[I].Direct==0){On+=1;}
            }
        }
        if(RoomPos[Rooms[I].X][Rooms[I].Y+1]!=0||GetRoom(Rooms[I].X,Rooms[I].Y+1).BigRoom!=0){
            if(GetRoom(Rooms[I].X,Rooms[I].Y+1).Direct==1||GetRoom(Rooms[I].X,Rooms[I].Y+1).Direct==0){
                Arrayy[On]='3';
                if(Rooms[I].Direct==0){On+=1;}
            }
        }
        if(RoomPos[Rooms[I].X-1][Rooms[I].Y]!=0||GetRoom(Rooms[I].X-1,Rooms[I].Y).BigRoom!=0){
            if(GetRoom(Rooms[I].X-1,Rooms[I].Y).Direct==2||GetRoom(Rooms[I].X-1,Rooms[I].Y).Direct==0){
                Arrayy[On]='4';
            }
        }

        if(Rooms[I].BigRoom==0){
            int _noobNumberGenerated = Random(1,3+(Rooms[I].Area*3));
            if(_noobNumberGenerated>=10){
                _noobNumberGenerated+=7;
            }// Convert the generated number to a string and put it in _noobNumberAsString
            strcpy((char*) &(Rooms[I].Type), "a/");
            strcat((char*) &(Rooms[I].Type), (const char*) &(Arrayy));
            strcat((char*) &(Rooms[I].Type), "/");
            if(Rooms[I].X==MapX&&Rooms[I].Y==MapY){
                strcat((char*) &(Rooms[I].Type), "star");
                strcat((char*) &(Rooms[I].Type),".txt");
            }else{
                Rooms[I].Type[7]=_noobNumberGenerated+48;
            }
        }
}

int Random(int Min, int Max){
     Max++;
     return ((rand()%(Max-Min))+Min);
}

void StringEqualer(char aaaaaaa[15],char bbbbbbbbb[15]){
    int h;
    for(h=0; h<15; h++){
        aaaaaaa[h]=bbbbbbbbb[h];
    }

}

int MakeFloor(int FloorSize, int ItemRooms, int Min ,int Xorgin, int Yorgin, int Area){
    RoomCount=FloorSize;
    ItemRoomCount=ItemRooms;
    int Target;
    int I;
    for(I=Min; I<FloorSize+ItemRooms+Min; I++){
        Rooms[I].Width=Width;
        Rooms[I].Height=Height;
        Rooms[I].Id=I;
        Rooms[I].ItemId=0;
        Rooms[I].IsItemRoom=0;
        Rooms[I].RoomSpd=0;
        if(Corrupted==1){
            Rooms[I].Area=Random(0,3);
        }else{
            Rooms[I].Area=Area;
        }
        if(I==Min){
            Rooms[I].X=Xorgin;
            Rooms[I].Y=Yorgin;
            Rooms[I].Id=Min;
        }else{

            if(I<FloorSize+Min){
                Target = Random(Min,I-1);
            }else{
                Target = Random(Min,FloorSize+Min-1);
            }

            int Found=0;
            while(Found==0){
                int ForceRate=6;
                int A = Random(1,4+ForceRate);
                if(A>=5&&A<=4+ForceRate){
                    if(Rooms[Target].RoomSpd!=0){
                        A=Rooms[Target].RoomSpd;
                    }else{
                        A=Random(1,4);
                    }
                }
                if(A==1&&RoomPos[Rooms[Target].X][Rooms[Target].Y+1]==0&&RoomPos[Rooms[Target].X][Rooms[Target].Y+1]<FloorSize+Min){
                    Rooms[I].X=Rooms[Target].X;
                    Rooms[I].Y=Rooms[Target].Y+1;
                    Rooms[I].RoomSpd=A;
                    Found=1;
                }else if(A==2&&RoomPos[Rooms[Target].X+1][Rooms[Target].Y]==0&&RoomPos[Rooms[Target].X+1][Rooms[Target].Y]<FloorSize+Min){
                    Rooms[I].X=Rooms[Target].X+1;
                    Rooms[I].Y=Rooms[Target].Y;
                    Rooms[I].RoomSpd=A;
                    Found=1;
                }else if(A==3&&RoomPos[Rooms[Target].X][Rooms[Target].Y-1]==0&&RoomPos[Rooms[Target].X][Rooms[Target].Y-1]<FloorSize+Min){
                    Rooms[I].X=Rooms[Target].X;
                    Rooms[I].Y=Rooms[Target].Y-1;
                    Rooms[I].RoomSpd=A;
                    Found=1;
                }else if(A==4&&RoomPos[Rooms[Target].X-1][Rooms[Target].Y]==0&&RoomPos[Rooms[Target].X-1][Rooms[Target].Y]<FloorSize+Min){
                    Rooms[I].X=Rooms[Target].X-1;
                    Rooms[I].Y=Rooms[Target].Y;
                    Rooms[I].RoomSpd=A;
                    Found=1;
                }
                if(I<FloorSize+Min){
                    Target = Random(Min,I-1);
                }else{
                    Target = Random(Min,FloorSize+Min-1);
                }
            }
        }

        if(I<FloorSize+Min){
            RoomPos[Rooms[I].X][Rooms[I].Y]=I;
        }
        Rooms[I].Id=I;
    }

    for(I=Min; I<FloorSize+ItemRooms+Min; I++){
        if(I>=FloorSize+Min){RoomPos[Rooms[I].X][Rooms[I].Y]=I;}

        int On=0;
        char Arrayy[5]={'-','-','-','-',0};

        if(RoomPos[Rooms[I].X][Rooms[I].Y-1]!=0&&RoomPos[Rooms[I].X][Rooms[I].Y-1]<FloorSize+Min){
            Arrayy[On]='1';
            if(I<FloorSize+Min){On+=1;}
        }
        if(RoomPos[Rooms[I].X+1][Rooms[I].Y]!=0&&RoomPos[Rooms[I].X+1][Rooms[I].Y]<FloorSize+Min){
            Arrayy[On]='2';
            if(I<FloorSize+Min){On+=1;}
        }
        if(RoomPos[Rooms[I].X][Rooms[I].Y+1]!=0&&RoomPos[Rooms[I].X][Rooms[I].Y+1]<FloorSize+Min){
            Arrayy[On]='3';
            if(I<FloorSize+Min){On+=1;}
        }
        if(RoomPos[Rooms[I].X-1][Rooms[I].Y]!=0&&RoomPos[Rooms[I].X-1][Rooms[I].Y]<FloorSize+Min){
            Arrayy[On]='4';
        }

        if(I>=FloorSize+Min){
            if(Arrayy[On]=='1'){
                Rooms[I].Direct=1;
                SetRoom(RoomPos[Rooms[I].X][Rooms[I].Y-1]);
            }else if(Arrayy[On]=='2'){
                Rooms[I].Direct=2;
                SetRoom(RoomPos[Rooms[I].X+1][Rooms[I].Y]);
            }else if(Arrayy[On]=='3'){
                Rooms[I].Direct=3;
                SetRoom(RoomPos[Rooms[I].X][Rooms[I].Y+1]);
            }else if(Arrayy[On]=='4'){
                Rooms[I].Direct=4;
                SetRoom(RoomPos[Rooms[I].X-1][Rooms[I].Y]);
            }
        }

        int _noobNumberGenerated = Random(1,3+(Rooms[I].Area*3));
        if(_noobNumberGenerated>=10){
            _noobNumberGenerated+=7;
        }
        strcpy((char*) &(Rooms[I].Type), "a/");
        strcat((char*) &(Rooms[I].Type), (const char*) &(Arrayy));
        strcat((char*) &(Rooms[I].Type), "/");
        if(I<FloorSize+Min){
            Rooms[I].Type[7]=_noobNumberGenerated+48;
        }else{
            if(I!=FloorSize+ItemRooms+Min-1){
                strcat((char*) &(Rooms[I].Type), "item");
                int Found2=0, RandomNum;
                while(Found2==0){
                    RandomNum=Random(0,ItemRandom);
                    if(RandomNum<=7||ItemPre[RandomNum].Once==0){
                        ItemPre[RandomNum].Once=1;
                        Found2=1;
                    }
                }
                Rooms[I].ItemId=RandomNum;
                Rooms[I].Finished=UltraHard;
            }else{
                strcat((char*) &(Rooms[I].Type), "spcA");
                Rooms[I].Finished=UltraHard;
            }
            Rooms[I].IsItemRoom=1;
            strcat((char*) &(Rooms[I].Type), ".txt");
        }
    }
    for(I=Min; I<FloorSize+Min; I++){
        if(Rooms[I].X==MapX||Rooms[I].X+1==MapX){
            if(Rooms[I].Y==MapY||Rooms[I].Y+1==MapY){
                continue;
            }
        }
        if(Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].BigRoom==0&&Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y+1]].BigRoom==0&&Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].BigRoom==0&&Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].BigRoom==0){
            if(RoomPos[Rooms[I].X+1][Rooms[I].Y]!=0&&RoomPos[Rooms[I].X+1][Rooms[I].Y+1]!=0&&RoomPos[Rooms[I].X][Rooms[I].Y+1]!=0&&RoomPos[Rooms[I].X][Rooms[I].Y]!=0&&Random(0,3)==1){
                if(RoomPos[Rooms[I].X+1][Rooms[I].Y]!=Min&&RoomPos[Rooms[I].X+1][Rooms[I].Y+1]!=Min&&RoomPos[Rooms[I].X][Rooms[I].Y+1]!=Min&&RoomPos[Rooms[I].X][Rooms[I].Y]!=Min){
                if(RoomPos[Rooms[I].X+1][Rooms[I].Y]<FloorSize+Min&&RoomPos[Rooms[I].X+1][Rooms[I].Y+1]<FloorSize+Min&&RoomPos[Rooms[I].X][Rooms[I].Y+1]<FloorSize+Min&&RoomPos[Rooms[I].X][Rooms[I].Y]<FloorSize+Min){
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].BigRoom=1;
                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].BigRoom=2;
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].BigRoom=3;
                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y+1]].BigRoom=4;

                char sbvfvdhf[16] = {'a','/','b','i','g','r','/','b','i','g','1','.','t','x','t',0};
                int Rand = Random(1,3+(Rooms[I].Area*3));
                if(Rand>=10){ Rand+=7; }
                sbvfvdhf[10]=Rand+48;
                strcpy((char*) &(Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Type), (const char*) &sbvfvdhf);

                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Width=Width*2;
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Height=Height*2;

                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].Width=Width*2;
                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].Height=Height*2;

                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y+1]].Width=Width*2;
                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y+1]].Height=Height*2;

                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].Width=Width*2;
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].Height=Height*2;
                }}
            }
        }
    }

    int UU;
    for(UU=0; UU<2; UU++){
    for(I=Min; I<FloorSize+Min; I++){
        if(Rooms[I].X==MapX||Rooms[I].X+1==MapX){
            if(Rooms[I].Y==MapY){
                continue;
            }
        }
        if(Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].BigRoom==0&&Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].BigRoom==0){
            if(RoomPos[Rooms[I].X][Rooms[I].Y]!=0&&RoomPos[Rooms[I].X+1][Rooms[I].Y]!=0&&Random(0,4)==1){
                if(RoomPos[Rooms[I].X+1][Rooms[I].Y]!=Min&&RoomPos[Rooms[I].X][Rooms[I].Y]!=Min){
                if(RoomPos[Rooms[I].X+1][Rooms[I].Y]<FloorSize+Min&&RoomPos[Rooms[I].X][Rooms[I].Y]<FloorSize+Min){
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].BigRoom=5;
                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].BigRoom=6;

                char sbvfvdhf[16] = {'a','/','l','o','n','g','/','l','o','g','1','.','t','x','t',0};
                int Rand = Random(1,3+(Rooms[I].Area*3));
                if(Rand>=10){ Rand+=7; }
                sbvfvdhf[10]=Rand+48;
                strcpy((char*) &(Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Type), (const char*) &sbvfvdhf);

                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Width=Width*2;
                Rooms[RoomPos[Rooms[I].X+1][Rooms[I].Y]].Width=Width*2;
                }}
            }
        }
    }

    for(I=Min; I<FloorSize+Min; I++){
        if(Rooms[I].X==MapX){
            if(Rooms[I].Y==MapY||Rooms[I].Y+1==MapY){
                continue;
            }
        }
        if(Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].BigRoom==0&&Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].BigRoom==0){
            if(RoomPos[Rooms[I].X][Rooms[I].Y]!=0&&RoomPos[Rooms[I].X][Rooms[I].Y+1]!=0&&Random(0,3)==1){
                if(RoomPos[Rooms[I].X][Rooms[I].Y]!=Min&&RoomPos[Rooms[I].X][Rooms[I].Y+1]!=Min){
                if(RoomPos[Rooms[I].X][Rooms[I].Y]<FloorSize+Min&&RoomPos[Rooms[I].X][Rooms[I].Y+1]<FloorSize+Min){
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].BigRoom=7;
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].BigRoom=8;

                char sbvfvdhf[16] = {'a','/','t','a','l','l','/','t','a','l','1','.','t','x','t',0};
                int Rand = Random(1,3+(Rooms[I].Area*3));
                if(Rand>=10){ Rand+=7; }
                sbvfvdhf[10]=Rand+48;
                strcpy((char*) &(Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Type), (const char*) &sbvfvdhf);

                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y]].Height=Height*2;
                Rooms[RoomPos[Rooms[I].X][Rooms[I].Y+1]].Height=Height*2;
                }}
            }
        }
    }
    }
    return FloorSize+ItemRooms+1;
}

int MakeBossRoom(int Min, int Max, int Min2, int Type){
    int Found=0,I, Thing;
    while(Found==0){
        for(I=Min; I<Max; I++){
            if(RoomPos[Rooms[I].X-1][Rooms[I].Y]==0&&Rooms[I].Direct==0){
                if(RoomPos[Rooms[I].X-2][Rooms[I].Y]==0&&RoomPos[Rooms[I].X-2][Rooms[I].Y-1]==0&&
                    RoomPos[Rooms[I].X-3][Rooms[I].Y]==0&&RoomPos[Rooms[I].X-3][Rooms[I].Y-1]==0&&RoomPos[Rooms[I].X-4][Rooms[I].Y]==0
                    &&RoomPos[Rooms[I].X-2][Rooms[I].Y+1]==0&&RoomPos[Rooms[I].X-3][Rooms[I].Y+1]==0&&
                    RoomPos[Rooms[I].X-2][Rooms[I].Y-2]==0&&RoomPos[Rooms[I].X-3][Rooms[I].Y-2]==0){

                    Found=1;
                    Rooms[Min2].Direct=2;
                    Rooms[Min2+5].Direct=2;

                    RoomPos[Rooms[I].X-1][Rooms[I].Y]=Min2;
                    RoomPos[Rooms[I].X-2][Rooms[I].Y]=Min2+1;
                    RoomPos[Rooms[I].X-2][Rooms[I].Y-1]=Min2+2;
                    RoomPos[Rooms[I].X-3][Rooms[I].Y]=Min2+3;
                    RoomPos[Rooms[I].X-3][Rooms[I].Y-1]=Min2+4;
                    RoomPos[Rooms[I].X-4][Rooms[I].Y]=Min2+5;
                    Rooms[Min2+1].BigRoom=4;
                    Rooms[Min2+2].BigRoom=2;
                    Rooms[Min2+3].BigRoom=3;
                    Rooms[Min2+4].BigRoom=1;

                    /// pos ///
                    Rooms[Min2].X=Rooms[I].X-1;
                    Rooms[Min2].Y=Rooms[I].Y;
                    Rooms[Min2+1].X=Rooms[I].X-2;
                    Rooms[Min2+1].Y=Rooms[I].Y;
                    Rooms[Min2+2].X=Rooms[I].X-2;
                    Rooms[Min2+2].Y=Rooms[I].Y-1;
                    Rooms[Min2+3].X=Rooms[I].X-3;
                    Rooms[Min2+3].Y=Rooms[I].Y;
                    Rooms[Min2+4].X=Rooms[I].X-3;
                    Rooms[Min2+4].Y=Rooms[I].Y-1;
                    Rooms[Min2+5].X=Rooms[I].X-4;
                    Rooms[Min2+5].Y=Rooms[I].Y;

                    SetRoom(GetRoom(Rooms[I].X,Rooms[I].Y).Id);
                    Thing=2;
                    knownRooms[Rooms[Min2+4].X][Rooms[Min2+4].Y]=1;
                }

                /// //////// //////// //////// //////////////////////// //////// //////// //////////////// //////// ///

            }else if(RoomPos[Rooms[I].X+1][Rooms[I].Y]==0&&Rooms[I].Direct==0){
                if(RoomPos[Rooms[I].X+2][Rooms[I].Y]==0&&RoomPos[Rooms[I].X+2][Rooms[I].Y-1]==0&&
                    RoomPos[Rooms[I].X+3][Rooms[I].Y]==0&&RoomPos[Rooms[I].X+3][Rooms[I].Y-1]==0&&RoomPos[Rooms[I].X+4][Rooms[I].Y]==0
                    &&RoomPos[Rooms[I].X+2][Rooms[I].Y+1]==0&&RoomPos[Rooms[I].X+3][Rooms[I].Y+1]==0
                    &&RoomPos[Rooms[I].X+2][Rooms[I].Y-2]==0&&RoomPos[Rooms[I].X+3][Rooms[I].Y-2]==0){

                    Found=2;
                    Rooms[Min2].Direct=4;
                    Rooms[Min2+5].Direct=4;

                    RoomPos[Rooms[I].X+1][Rooms[I].Y]=Min2;
                    RoomPos[Rooms[I].X+2][Rooms[I].Y]=Min2+1;
                    RoomPos[Rooms[I].X+2][Rooms[I].Y-1]=Min2+2;
                    RoomPos[Rooms[I].X+3][Rooms[I].Y]=Min2+3;
                    RoomPos[Rooms[I].X+3][Rooms[I].Y-1]=Min2+4;
                    RoomPos[Rooms[I].X+4][Rooms[I].Y]=Min2+5;
                    Rooms[Min2+1].BigRoom=3;
                    Rooms[Min2+2].BigRoom=1;
                    Rooms[Min2+3].BigRoom=4;
                    Rooms[Min2+4].BigRoom=2;

                    /// pos ///
                    Rooms[Min2].X=Rooms[I].X+1;
                    Rooms[Min2].Y=Rooms[I].Y;
                    Rooms[Min2+1].X=Rooms[I].X+2;
                    Rooms[Min2+1].Y=Rooms[I].Y;
                    Rooms[Min2+2].X=Rooms[I].X+2;
                    Rooms[Min2+2].Y=Rooms[I].Y-1;
                    Rooms[Min2+3].X=Rooms[I].X+3;
                    Rooms[Min2+3].Y=Rooms[I].Y;
                    Rooms[Min2+4].X=Rooms[I].X+3;
                    Rooms[Min2+4].Y=Rooms[I].Y-1;
                    Rooms[Min2+5].X=Rooms[I].X+4;
                    Rooms[Min2+5].Y=Rooms[I].Y;

                    SetRoom(GetRoom(Rooms[I].X,Rooms[I].Y).Id);
                    Thing=0;
                    knownRooms[Rooms[Min2+2].X][Rooms[Min2+2].Y]=1;
                }
            }
            if(Found!=0){

                /// size ///
                Rooms[Min2+1].Width=Width*2;
                Rooms[Min2+2].Width=Width*2;
                Rooms[Min2+3].Width=Width*2;
                Rooms[Min2+4].Width=Width*2;
                Rooms[Min2+1].Height=Height*2;
                Rooms[Min2+2].Height=Height*2;
                Rooms[Min2+3].Height=Height*2;
                Rooms[Min2+4].Height=Height*2;

                Rooms[Min2].Width=Width;
                Rooms[Min2+5].Width=Width;
                Rooms[Min2].Height=Height;
                Rooms[Min2+5].Height=Height;

                /// other ///

                Rooms[Min2].Id=Min2;
                Rooms[Min2+1].Id=Min2+1;
                Rooms[Min2+2].Id=Min2+2;
                Rooms[Min2+3].Id=Min2+3;
                Rooms[Min2+4].Id=Min2+4;
                Rooms[Min2+5].Id=Min2+5;

                Rooms[Min2].ItemId=0;
                Rooms[Min2+1].ItemId=0;
                Rooms[Min2+2].ItemId=0;
                Rooms[Min2+3].ItemId=0;
                Rooms[Min2+4].ItemId=0;
                Rooms[Min2+5].ItemId=0;

                Rooms[Min2].IsItemRoom=0;
                Rooms[Min2+1].IsItemRoom=0;
                Rooms[Min2+2].IsItemRoom=0;
                Rooms[Min2+3].IsItemRoom=0;
                Rooms[Min2+4].IsItemRoom=0;
                Rooms[Min2+5].IsItemRoom=0;

                if(UltraHard==1){
                    Rooms[I].Area=Random(0,2);
                }

                Rooms[Min2].Area=Rooms[I].Area;
                Rooms[Min2+1].Area=Rooms[I].Area;
                Rooms[Min2+2].Area=Rooms[I].Area;
                Rooms[Min2+3].Area=Rooms[I].Area;
                Rooms[Min2+4].Area=Rooms[I].Area;
                Rooms[Min2+5].Area=Rooms[I].Area;

                /// rooms ///

                char sbvfvdh[16] = {'a','/','2','4','-','-','/','B','.','t','x','t',0};
                strcpy((char*) &(Rooms[Min2].Type), (const char*) &sbvfvdh);

                strcpy((char*) &(Rooms[Min2+1].Type), "a/pre/1.txt");
                strcpy((char*) &(Rooms[Min2+3].Type), "a/pre/1.txt");
                strcpy((char*) &(Rooms[Min2+4-Thing].Type), "a/pre/1.txt");

                if(Found==1){
                    if(Type==0){
                        char sbvfvd[16] = {'a','/','2','-','-','-','/','i','t','e','m','.','t','x','t',0};
                        strcpy((char*) &(Rooms[Min2+5].Type), (const char*) &sbvfvd);
                    }else{
                        if(Rooms[Min2+5].Area==2){
                            char sbvfvd[16] = {'a','/','2','-','-','-','/','s','p','c','C','.','t','x','t',0};
                            strcpy((char*) &(Rooms[Min2+5].Type), (const char*) &sbvfvd);
                        }else{
                            char sbvfvd[16] = {'a','/','2','-','-','-','/','s','p','c','B','.','t','x','t',0};
                            strcpy((char*) &(Rooms[Min2+5].Type), (const char*) &sbvfvd);
                        }
                    }
                }else{
                    if(Type==0){
                        char sbvfvd[16] = {'a','/','4','-','-','-','/','i','t','e','m','.','t','x','t',0};
                        strcpy((char*) &(Rooms[Min2+5].Type), (const char*) &sbvfvd);
                    }else{
                        if(Rooms[Min2+5].Area==2){
                            char sbvfvd[16] = {'a','/','4','-','-','-','/','s','p','c','C','.','t','x','t',0};
                            strcpy((char*) &(Rooms[Min2+5].Type), (const char*) &sbvfvd);
                        }else{
                            char sbvfvd[16] = {'a','/','4','-','-','-','/','s','p','c','B','.','t','x','t',0};
                            strcpy((char*) &(Rooms[Min2+5].Type), (const char*) &sbvfvd);
                        }
                    }
                }
                Rooms[Min2+5].ItemId=Random(0,ItemRandom);
                Rooms[Min2+5].IsItemRoom=1;


                char sbvfvdhf[16] = {'a','/','b','i','g','r','/','b','o','s','2','.','t','x','t',0};
                sbvfvdhf[10]=49+Rooms[I].Area;
                strcpy((char*) &(Rooms[Min2+2+Thing].Type), (const char*) &sbvfvdhf);

                /// directions ///

                Rooms[Min2+1].Direct=3;
                Rooms[Min2+2].Direct=1;
                Rooms[Min2+3].Direct=3;
                Rooms[Min2+4].Direct=1;
                break;
            }
        }
    }
    return 6;
}

int MakeSaveRoom(int Id, int Min, int Max){
    int Found=0;
    while(Found==0){
        int Num = Random(Min,Max);
        int Rand = Random(1,4);
        int RomX = Rooms[Num].X, RomY = Rooms[Num].Y;

        if(Rooms[Num].IsItemRoom==0){
            if(Rand==1){
                if(RoomPos[Rooms[Num].X][Rooms[Num].Y-1]==0&&Rooms[Num].Direct==0){
                    RoomPos[RomX][RomY-1]=Id;
                    SetRoom(RoomPos[RomX][RomY]);
                    RomY-=1;
                    Rooms[Id].Direct=3;
                    Found=1;
                }
            }else if(Rand==2){
                if(RoomPos[Rooms[Num].X+1][Rooms[Num].Y]==0&&Rooms[Num].Direct==0){
                    RoomPos[RomX+1][RomY]=Id;
                    SetRoom(RoomPos[RomX][RomY]);
                    RomX+=1;
                    Rooms[Id].Direct=4;
                    Found=1;
                }
            }else if(Rand==3){
                if(RoomPos[Rooms[Num].X][Rooms[Num].Y+1]==0&&Rooms[Num].Direct==0){
                    RoomPos[RomX][RomY+1]=Id;
                    SetRoom(RoomPos[RomX][RomY]);
                    RomY+=1;
                    Rooms[Id].Direct=1;
                    Found=1;
                }
            }else if(Rand==4){
                if(RoomPos[Rooms[Num].X-1][Rooms[Num].Y]==0&&Rooms[Num].Direct==0){
                    RoomPos[RomX-1][RomY]=Id;
                    SetRoom(RoomPos[RomX][RomY]);
                    RomX-=1;
                    Rooms[Id].Direct=2;
                    Found=1;
                }
            }
        }

        if(Found==1){
            Rooms[Id].X=RomX;
            Rooms[Id].Y=RomY;
            Rooms[Id].Width=Width;
            Rooms[Id].Height=Height;
            Rooms[Id].BigRoom=0;
            Rooms[Id].Area=Rooms[Num].Area;
            Rooms[Id].Id=Id;

            char String[17]="a/0---/save.txt";
            String[2] = 48+Rooms[Id].Direct;
            strcpy((char*)&Rooms[Id].Type,(const char*)&String);

            SetRoom(Num);
        }
    }



    return 1;
}


/// /////////////// enemy spawns /////////////// ///



#endif



