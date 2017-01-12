#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
	//Declaration
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
	unsigned char chip8font[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	//Initialization
	pc = 0x200;  // Program counter starts at 0x200
	opcode = 0;	
	I = 0;      
	sp = 0;      

	//Load Font into Memory at 0x50
	for (int i = 0; i < 80; i++ )
	{
		memory[i + 0x50] = chip8font[i];
	}

	FILE * romfile = fopen("emu.c8", "r");

	system("pause");

	return 0;
}