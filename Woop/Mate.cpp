#include <iostream>
#include <SDL.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char V[16];
	unsigned short I;
	unsigned short pc;
	unsigned char gfx[64 * 32];
	unsigned char delayt;
	unsigned char soundt;
	unsigned short stack[16];
	unsigned short sp;

	pc = 0x200;  // Program counter starts at 0x200
	opcode = 0;	
	I = 0;      
	sp = 0;      

	system("pause");

	return 0;
}