#ifndef CHIP8
#define CHIP8

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
}Chip8;

