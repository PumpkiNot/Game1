#ifndef SOUND
#define SOUND

Mix_Chunk *Music[15];

Mix_Chunk *Sounds[15];

void LoadSounds(){
    if(UltraHard==0){
        Music[0] = Mix_LoadWAV("Sound/Music/new/SongD.wav");
        Music[1] = Mix_LoadWAV("Sound/Music/songA.wav");
        Music[2] = Mix_LoadWAV("Sound/Music/new/SongB.wav");
        Music[3] = Mix_LoadWAV("Sound/Music/songC.wav");
        Music[4] = Mix_LoadWAV("Sound/Music/songD.wav");
        Music[5] = Mix_LoadWAV("Sound/Music/new/songE.wav");
        Music[14] = Mix_LoadWAV("Sound/Music/new/Bossong.wav");
    }else{
        Music[4] = Mix_LoadWAV("Sound/Music/songD.wav");
        Music[0] = Mix_LoadWAV("Sound/Music/songC.wav");
        Music[1] = Music[4];
        Music[2] = Music[4];
        Music[3] = Music[4];
    }

    Sounds[0] = Mix_LoadWAV("Sound/Sounds/JumpSound.wav");
    Sounds[2] = Mix_LoadWAV("Sound/Sounds/ShootA.wav");
    Sounds[1] = Mix_LoadWAV("Sound/Sounds/Land.wav");
    Sounds[3] = Mix_LoadWAV("Sound/Sounds/Collect.wav");

    Sounds[4] = Mix_LoadWAV("Sound/Sounds/ExplosionB.wav");
    Sounds[5] = Mix_LoadWAV("Sound/Sounds/ExplosionA.wav");
}

#endif // SOUND






