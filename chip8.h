#ifndef CHIP8_H
#define CHIP8_H

typedef struct{
	unsigned char  memory[4096];
	unsigned char  V[16];
	unsigned short pc;
	unsigned char  gfx[2048];
	unsigned char  stack[16];
	unsigned char  key[16];
	unsigned short I;
	unsigned short sp;
	unsigned short opcode;
	unsigned char  delay_timer;
	unsigned char  sound_timer;
	unsigned char  draw_flag;
}Chip8;

void emulationCycle(Chip8* chip8);

#endif
