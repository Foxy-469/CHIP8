#include <stdio.h>
#include  <string.h>
#include "chip8.h"

void initialize(Chip8* chip8){
	memset(chip8->memory, 0, 4096);
	memset(chip8->V, 0, 16);
	memset(chip8->gfx, 0, 2048);
	chip8->pc = 0x200;
	chip8->opcode = 0;
	chip8->I = 0;
	chip8->sp = 0;
	memset(chip8->stack, 0, sizeof(chip8->stack));
	memset(chip8->key, 0, 16);
	chip8->delay_timer = 0;
	chip8->sound_timer = 0;
}

int loadGame(Chip8* chip8, const char* filename){
	FILE* rom = fopen(filename, "rb");

	if (rom == NULL){
		printf("Failedd to open ROK\n");
		return 0;
	}

	fread(&chip8->memory[0x200], 1, 3584, rom); // fread(start, 1, max, rom);
	fclose(rom);
	return 1;
}

void emulationCycle(Chip8* chip8){
	// 1. Fetch opcode
	chip8->opcode = chip8->memory[chip8->pc] << 8 |chip8->memory[ chip8->pc + 1]; 
	//ex- mem[512] = 0xA2, mem[513] = 0xF0, opcode = 0xA2F0, as -xA2 << 8 = 0xA200, and 0xA200 | 0xF0 = 0xA2F0

	//2. Decode and execute
	switch (chip8->opcode & 0xF000){ //isolates first 4 bits (ex- 0xA2F0 -> 0xA000 A-type)
		case 0x0000: // decode inner values (ex- 0x00E0, 0x004E)
			switch (chip8->opcode & 0x00FF){
				case 0x00E0: //clear screen
					memset(chip8->gfx, 0, sizeof(chip8->gfx));
					chip8->draw_flag = 1;
					chip8->pc +=2;
					break;
				
				case 0x00EE: //Return from subroutine
					chip8->sp--;
					chip8->pc = chip8->stack[chip8->sp];
					break;

				default:
					printf("Unknown 0x0000 opcode: 0x%X\n", chip8->opcode);
					break;
			}
			break;
		case 0x2000:
			chip8->stack[chip8->sp] = chip8->pc + 2;
			chip8->sp++;
			chip8->pc = chip8->opcode & 0x0FFF;


		// More cases here later
	}

	// 3. Update timeer
	if (chip8->delay_timer > 0){
		chip8->delay_timer--;
	}
	if (chip8->sound_timer > 0){
		chip8->sound_timer--;
	}
}

int main(){
	Chip8 chip8;
	initialize(&chip8);
	loadGame(&chip8, "test1.ch8");

	while(1){
		emulationCycle(&chip8);
		if (chip8.draw_flag){
			//render screen
			chip8.draw_flag = 0;
		}
	}
	return 0;
}
