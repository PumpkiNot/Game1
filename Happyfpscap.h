#ifndef HAPPYFPSCAP
#define HAPPYFPSCAP

#define MILISECONDSPERFRAME 17

// The milisecodnds at the start of the frame.
unsigned int frameStartMiliseconds;
signed char capEnabled = 1;

void FpsCapStart(){
	frameStartMiliseconds = SDL_GetTicks();
}

void FpsCapWait(){
	unsigned int tempHold;
	tempHold = SDL_GetTicks();
	// LIMIT FPS
	if (tempHold-frameStartMiliseconds<MILISECONDSPERFRAME){
		SDL_Delay( (MILISECONDSPERFRAME - (tempHold-frameStartMiliseconds)));
	}
}

#endif
