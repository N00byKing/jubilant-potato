#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <ostream>
#include <fstream>
#include <istream>

using namespace std;
bool ExitProgram;

int main(int argc, char *argv[])
{

	
	//Declare Variables
	ExitProgram = false;
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char V[16];
	unsigned short I;
	unsigned short pc;
	unsigned char delayt;
	unsigned char soundt;
	unsigned short stack[16];
	unsigned short sp;
	unsigned char gfx[64 * 32];
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
	ifstream FileRW;
	ofstream LogRW;
	
	//Initiate SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;
	SDL_CreateWindowAndRenderer(64, 32, SDL_WINDOW_SHOWN, &sdlWindow, &sdlRenderer);
	SDL_Event event;
	SDL_SetRenderDrawColor(sdlRenderer, 200, 211, 0, 0);

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
	
	//Load ROM
	FileRW.open("emu.c8", iostream::binary);
	unsigned char hexarray[1024];
	FileRW.read((char*)&hexarray, 1024);
	for (int i = 0; i < 1024; i++)
	{
		memory[512 + i] = hexarray[i];
	}
	
	//Logging Start
	LogRW.open("log.txt", ofstream::out);
	LogRW << "Start" << "\r\n";

	//Start Emulation
	while (!ExitProgram)
	{
		//To Be Edited, currently only Exit Event
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_KEYUP:
				ExitProgram = true;
		}

		//Get new opcode and log it
		opcode = memory[pc] << 8 | memory[pc + 1];
		LogRW << opcode << "\r\n";

		//Execute opcode
		switch(opcode & 0xF000) 
		{
			case 0x0000:
				switch (opcode)
				{
					case 0x00EE:
						pc = stack[sp];
						sp--;
						pc += 2;
						break;
				}
				break;

			case 0x1000:
				pc = (opcode & 0x0FFF);
				break;
		
			case 0x2000:
				sp++;
				stack[sp] = pc;
				pc = (opcode & 0x0FFF);
				break;
			
			case 0x3000:
				if (V[((opcode & 0x0F00) >> 8)] == (opcode & 0x00FF)) 
				{
					pc += 4;
				}
				else 
				{
					pc += 2;
				}
				break;

			case 0x6000:
				V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
				pc += 2;
				break;
			
			case 0x7000:
				V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] + (opcode & 0x00FF);
				pc += 2;
				break;

			case 0xA000:
				I = (opcode & 0x0FFF);
				pc += 2;
				break;
			
			case 0xC000:
				V[((opcode & 0x0F00) >> 8)] = ((rand() % 256) & (opcode & 0x00FF));
				pc += 2;
				break;

			case 0xD000:
				for (int i = 0; i <= 8; i++)
				{
					for (int j = 0; j <= (opcode & 0x000F); j++) 
					{
						SDL_RenderDrawPoint(sdlRenderer, V[(opcode & 0x0F00) >> 8] + i, V[(opcode & 0x00F0) >> 4] + j);
					}
				}
				SDL_RenderPresent(sdlRenderer);
				pc += 2;
				break;
			
			case 0xE000:
				pc += 2;
				break;

			case 0xF000:
				switch (opcode & 0xF0FF)
				{
					case 0xF007:
						V[((opcode & 0x0F00) >> 8)] = delayt;
						pc += 2;
						break;
				
					case 0xF015:
						delayt = V[((opcode & 0x0F00) >> 8)];
						pc += 2;
						break;

					case 0xF029:
						I = memory[0x50 + 5 * V[((opcode & 0x0F00) >> 8)]];
						pc += 2;
						break;
						
					case 0xF033:
						memory[I] = (V[((opcode & 0x0F00) >> 8)] / 100);
						memory[(I + 1)] = (V[((opcode & 0x0F00) >> 8)] / 10);
						memory[(I + 2)] = (V[((opcode & 0x0F00) >> 8)] / 1);
						pc += 2;
						break;

					case 0xF065:
						for (int i = 0; i < ((opcode & 0x0F00) >> 8); i++) 
						{
							V[i] = (memory[I + i] << 8 | memory[I + i + 1]);
						}
						pc += 2;
						break;
				}
				break;
		}
	
		if (delayt != 0) 
		{
			delayt--;
		}
	}
	
	LogRW << V[12] << "\r\n";
	

	//Exit SDL
	SDL_Quit();

	//Close log.txt
	LogRW.close();

	//Write Memory
	LogRW.open("lastmem.hex", iostream::binary);
	LogRW.write((char*)&memory, 4096);

	//Close IOStreams
	FileRW.close();
	LogRW.close();

	//Exit
	system("pause");
	return 0;
}