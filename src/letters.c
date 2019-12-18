#include <stdlib.h>
#include <stdint.h>

uint16_t** get_char_table()
{
	uint16_t** chars = malloc(256*sizeof(uint16_t*));
	uint16_t* default_char = malloc(2*sizeof(uint16_t));
	default_char[0] = 1, default_char[1] = 0;
	for(int i = 0; i < 256; i++) {
		chars[i] = default_char;
	}

	// Creeper
	chars[1]=malloc(9*sizeof(uint16_t));
	chars[1][0]=8;
	chars[1][1]=0x0;
	chars[1][2]=0x3000;
	chars[1][3]=0x3700;
	chars[1][4]=0xe00;
	chars[1][5]=0xe00;
	chars[1][6]=0x3700;
	chars[1][7]=0x3000;
	chars[1][8]=0x0;

	// heart1
	chars[2]=malloc(8*sizeof(uint16_t));
	chars[2][0]=7;
	chars[2][1]=0x60;
	chars[2][2]=0xf0;
	chars[2][3]=0xf8;
	chars[2][4]=0x7c;
	chars[2][5]=0xf8;
	chars[2][6]=0xf0;
	chars[2][7]=0x60;

	// heart2
	chars[3]=malloc(8*sizeof(uint16_t));
	chars[3][0]=7;
	chars[3][1]=0xc00;
	chars[3][2]=0x1e00;
	chars[3][3]=0x1f00;
	chars[3][4]=0xf80;
	chars[3][5]=0x1f00;
	chars[3][6]=0x1e00;
	chars[3][7]=0xc00;

	// €
	chars[4]=malloc(8*sizeof(uint16_t));
	chars[4][0]=7;
	chars[4][1]=0x500;
	chars[4][2]=0xf80;
	chars[4][3]=0x1540;
	chars[4][4]=0x2520;
	chars[4][5]=0x2020;
	chars[4][6]=0x2020;
	chars[4][7]=0x1040;

	// Space
	chars[32]=malloc(3*sizeof(uint16_t));
	chars[32][0]=2;
	chars[32][1]=0x0;
	chars[32][2]=0x0;

	// !
	chars[33]=malloc(2*sizeof(uint16_t));
	chars[33][0]=1;
	chars[33][1]=0x3fa0;

	// #
	chars[35]=malloc(9*sizeof(uint16_t));
	chars[35][0]=8;
	chars[35][1]=0x480;
	chars[35][2]=0x480;
	chars[35][3]=0x1fe0;
	chars[35][4]=0x480;
	chars[35][5]=0x480;
	chars[35][6]=0x1fe0;
	chars[35][7]=0x480;
	chars[35][8]=0x480;

	// $
	chars[36]=malloc(6*sizeof(uint16_t));
	chars[36][0]=5;
	chars[36][1]=0xc80;
	chars[36][2]=0x1240;
	chars[36][3]=0x3260;
	chars[36][4]=0x1240;
	chars[36][5]=0x980;

	// %
	chars[37]=malloc(7*sizeof(uint16_t));
	chars[37][0]=6;
	chars[37][1]=0x840;
	chars[37][2]=0x1480;
	chars[37][3]=0x900;
	chars[37][4]=0x240;
	chars[37][5]=0x4a0;
	chars[37][6]=0x840;

	// +
	chars[43]=malloc(4*sizeof(uint16_t));
	chars[43][0]=3;
	chars[43][1]=0x200;
	chars[43][2]=0x700;
	chars[43][3]=0x200;

	// ,
	chars[44]=malloc(2*sizeof(uint16_t));
	chars[44][0]=1;
	chars[44][1]=0x30;

	// -
	chars[45]=malloc(4*sizeof(uint16_t));
	chars[45][0]=3;
	chars[45][1]=0x200;
	chars[45][2]=0x200;
	chars[45][3]=0x200;

	// Dot
	chars[46]=malloc(2*sizeof(uint16_t));
	chars[46][0]=1;
	chars[46][1]=0x20;

	// Slash
	chars[47]=malloc(5*sizeof(uint16_t));
	chars[47][0]=4;
	chars[47][1]=0x60;
	chars[47][2]=0x180;
	chars[47][3]=0x600;
	chars[47][4]=0x1800;

	// 0
	chars[48]=malloc(6*sizeof(uint16_t));
	chars[48][0]=5;
	chars[48][1]=0x1dc0;
	chars[48][2]=0x2020;
	chars[48][3]=0x2020;
	chars[48][4]=0x2020;
	chars[48][5]=0x1dc0;

	// 1
	chars[49]=malloc(6*sizeof(uint16_t));
	chars[49][0]=5;
	chars[49][1]=0x0;
	chars[49][2]=0x0;
	chars[49][3]=0x0;
	chars[49][4]=0x0;
	chars[49][5]=0x1dc0;

	// 2
	chars[50]=malloc(6*sizeof(uint16_t));
	chars[50][0]=5;
	chars[50][1]=0x1c0;
	chars[50][2]=0x2220;
	chars[50][3]=0x2220;
	chars[50][4]=0x2220;
	chars[50][5]=0x1c00;

	// 3
	chars[51]=malloc(6*sizeof(uint16_t));
	chars[51][0]=5;
	chars[51][1]=0x0;
	chars[51][2]=0x2220;
	chars[51][3]=0x2220;
	chars[51][4]=0x2220;
	chars[51][5]=0x1dc0;

	// 4
	chars[52]=malloc(6*sizeof(uint16_t));
	chars[52][0]=5;
	chars[52][1]=0x1c00;
	chars[52][2]=0x200;
	chars[52][3]=0x200;
	chars[52][4]=0x200;
	chars[52][5]=0x1dc0;

	// 5
	chars[53]=malloc(6*sizeof(uint16_t));
	chars[53][0]=5;
	chars[53][1]=0x1c00;
	chars[53][2]=0x2220;
	chars[53][3]=0x2220;
	chars[53][4]=0x2220;
	chars[53][5]=0x1c0;

	// 6
	chars[54]=malloc(6*sizeof(uint16_t));
	chars[54][0]=5;
	chars[54][1]=0x1dc0;
	chars[54][2]=0x2220;
	chars[54][3]=0x2220;
	chars[54][4]=0x2220;
	chars[54][5]=0x1c0;

	// 7
	chars[55]=malloc(6*sizeof(uint16_t));
	chars[55][0]=5;
	chars[55][1]=0x0;
	chars[55][2]=0x2000;
	chars[55][3]=0x2000;
	chars[55][4]=0x2000;
	chars[55][5]=0x1dc0;

	// 8
	chars[56]=malloc(6*sizeof(uint16_t));
	chars[56][0]=5;
	chars[56][1]=0x1dc0;
	chars[56][2]=0x2220;
	chars[56][3]=0x2220;
	chars[56][4]=0x2220;
	chars[56][5]=0x1dc0;

	// 9
	chars[57]=malloc(6*sizeof(uint16_t));
	chars[57][0]=5;
	chars[57][1]=0x1c00;
	chars[57][2]=0x2220;
	chars[57][3]=0x2220;
	chars[57][4]=0x2220;
	chars[57][5]=0x1dc0;

	// :
	chars[58]=malloc(2*sizeof(uint16_t));
	chars[58][0]=1;
	chars[58][1]=0x480;

	// ;
	chars[59]=malloc(2*sizeof(uint16_t));
	chars[59][0]=1;
	chars[59][1]=0x130;

	// =
	chars[61]=malloc(4*sizeof(uint16_t));
	chars[61][0]=3;
	chars[61][1]=0x500;
	chars[61][2]=0x500;
	chars[61][3]=0x500;

	// ?
	chars[63]=malloc(6*sizeof(uint16_t));
	chars[63][0]=5;
	chars[63][1]=0x1800;
	chars[63][2]=0x2000;
	chars[63][3]=0x21a0;
	chars[63][4]=0x2200;
	chars[63][5]=0x1c00;

	// @
	chars[64]=malloc(9*sizeof(uint16_t));
	chars[64][0]=8;
	chars[64][1]=0xfc0;
	chars[64][2]=0x1020;
	chars[64][3]=0x2390;
	chars[64][4]=0x2450;
	chars[64][5]=0x2450;
	chars[64][6]=0x27c0;
	chars[64][7]=0x1020;
	chars[64][8]=0xfc0;

	// A
	chars[65]=malloc(7*sizeof(uint16_t));
	chars[65][0]=6;
	chars[65][1]=0x7e0;
	chars[65][2]=0x1a00;
	chars[65][3]=0x2200;
	chars[65][4]=0x2200;
	chars[65][5]=0x1a00;
	chars[65][6]=0x7e0;

	// B
	chars[66]=malloc(6*sizeof(uint16_t));
	chars[66][0]=5;
	chars[66][1]=0x3fe0;
	chars[66][2]=0x2220;
	chars[66][3]=0x2220;
	chars[66][4]=0x2220;
	chars[66][5]=0x1dc0;

	// C
	chars[67]=malloc(7*sizeof(uint16_t));
	chars[67][0]=6;
	chars[67][1]=0x1fc0;
	chars[67][2]=0x2020;
	chars[67][3]=0x2020;
	chars[67][4]=0x2020;
	chars[67][5]=0x2020;
	chars[67][6]=0x18c0;

	// D
	chars[68]=malloc(7*sizeof(uint16_t));
	chars[68][0]=6;
	chars[68][1]=0x3fe0;
	chars[68][2]=0x2020;
	chars[68][3]=0x2020;
	chars[68][4]=0x2020;
	chars[68][5]=0x1040;
	chars[68][6]=0xf80;

	// E
	chars[69]=malloc(7*sizeof(uint16_t));
	chars[69][0]=6;
	chars[69][1]=0x3fe0;
	chars[69][2]=0x2220;
	chars[69][3]=0x2220;
	chars[69][4]=0x2220;
	chars[69][5]=0x2020;
	chars[69][6]=0x2020;

	// F
	chars[70]=malloc(7*sizeof(uint16_t));
	chars[70][0]=6;
	chars[70][1]=0x3fe0;
	chars[70][2]=0x2200;
	chars[70][3]=0x2200;
	chars[70][4]=0x2200;
	chars[70][5]=0x2000;
	chars[70][6]=0x2000;

	// G
	chars[71]=malloc(7*sizeof(uint16_t));
	chars[71][0]=6;
	chars[71][1]=0x1fc0;
	chars[71][2]=0x2020;
	chars[71][3]=0x2020;
	chars[71][4]=0x2020;
	chars[71][5]=0x2120;
	chars[71][6]=0x19c0;

	// H
	chars[72]=malloc(6*sizeof(uint16_t));
	chars[72][0]=5;
	chars[72][1]=0x3fe0;
	chars[72][2]=0x200;
	chars[72][3]=0x200;
	chars[72][4]=0x200;
	chars[72][5]=0x3fe0;

	// I
	chars[73]=malloc(4*sizeof(uint16_t));
	chars[73][0]=3;
	chars[73][1]=0x2020;
	chars[73][2]=0x3fe0;
	chars[73][3]=0x2020;

	// J
	chars[74]=malloc(6*sizeof(uint16_t));
	chars[74][0]=5;
	chars[74][1]=0xc0;
	chars[74][2]=0x20;
	chars[74][3]=0x2020;
	chars[74][4]=0x3fc0;
	chars[74][5]=0x2000;

	// K
	chars[75]=malloc(7*sizeof(uint16_t));
	chars[75][0]=6;
	chars[75][1]=0x3fe0;
	chars[75][2]=0x200;
	chars[75][3]=0x500;
	chars[75][4]=0x880;
	chars[75][5]=0x1040;
	chars[75][6]=0x2020;

	// L
	chars[76]=malloc(6*sizeof(uint16_t));
	chars[76][0]=5;
	chars[76][1]=0x3fe0;
	chars[76][2]=0x20;
	chars[76][3]=0x20;
	chars[76][4]=0x20;
	chars[76][5]=0x20;

	// M
	chars[77]=malloc(8*sizeof(uint16_t));
	chars[77][0]=7;
	chars[77][1]=0x3fe0;
	chars[77][2]=0x1000;
	chars[77][3]=0x800;
	chars[77][4]=0x400;
	chars[77][5]=0x800;
	chars[77][6]=0x1000;
	chars[77][7]=0x3fe0;

	// N
	chars[78]=malloc(7*sizeof(uint16_t));
	chars[78][0]=6;
	chars[78][1]=0x3fe0;
	chars[78][2]=0x1000;
	chars[78][3]=0xc00;
	chars[78][4]=0x300;
	chars[78][5]=0x80;
	chars[78][6]=0x3fe0;

	// O
	chars[79]=malloc(7*sizeof(uint16_t));
	chars[79][0]=6;
	chars[79][1]=0xf80;
	chars[79][2]=0x1040;
	chars[79][3]=0x2020;
	chars[79][4]=0x2020;
	chars[79][5]=0x1040;
	chars[79][6]=0xf80;

	// P
	chars[80]=malloc(6*sizeof(uint16_t));
	chars[80][0]=5;
	chars[80][1]=0x3fe0;
	chars[80][2]=0x2200;
	chars[80][3]=0x2200;
	chars[80][4]=0x2200;
	chars[80][5]=0x1c00;

	// Q
	chars[81]=malloc(7*sizeof(uint16_t));
	chars[81][0]=6;
	chars[81][1]=0xf80;
	chars[81][2]=0x1040;
	chars[81][3]=0x2020;
	chars[81][4]=0x20a0;
	chars[81][5]=0x1040;
	chars[81][6]=0xfa0;

	// R
	chars[82]=malloc(6*sizeof(uint16_t));
	chars[82][0]=5;
	chars[82][1]=0x3fe0;
	chars[82][2]=0x2200;
	chars[82][3]=0x2300;
	chars[82][4]=0x2280;
	chars[82][5]=0x1c60;

	// S
	chars[83]=malloc(6*sizeof(uint16_t));
	chars[83][0]=5;
	chars[83][1]=0x1c40;
	chars[83][2]=0x2220;
	chars[83][3]=0x2220;
	chars[83][4]=0x2220;
	chars[83][5]=0x11c0;

	// T
	chars[84]=malloc(6*sizeof(uint16_t));
	chars[84][0]=5;
	chars[84][1]=0x2000;
	chars[84][2]=0x2000;
	chars[84][3]=0x3fe0;
	chars[84][4]=0x2000;
	chars[84][5]=0x2000;

	// U
	chars[85]=malloc(7*sizeof(uint16_t));
	chars[85][0]=6;
	chars[85][1]=0x3f80;
	chars[85][2]=0x40;
	chars[85][3]=0x20;
	chars[85][4]=0x20;
	chars[85][5]=0x40;
	chars[85][6]=0x3f80;

	// V
	chars[86]=malloc(8*sizeof(uint16_t));
	chars[86][0]=7;
	chars[86][1]=0x3c00;
	chars[86][2]=0x300;
	chars[86][3]=0xc0;
	chars[86][4]=0x20;
	chars[86][5]=0xc0;
	chars[86][6]=0x300;
	chars[86][7]=0x3c00;

	// W
	chars[87]=malloc(8*sizeof(uint16_t));
	chars[87][0]=7;
	chars[87][1]=0x3fe0;
	chars[87][2]=0x40;
	chars[87][3]=0x80;
	chars[87][4]=0x100;
	chars[87][5]=0x80;
	chars[87][6]=0x40;
	chars[87][7]=0x3fe0;

	// X
	chars[88]=malloc(6*sizeof(uint16_t));
	chars[88][0]=5;
	chars[88][1]=0x3060;
	chars[88][2]=0xd80;
	chars[88][3]=0x200;
	chars[88][4]=0xd80;
	chars[88][5]=0x3060;

	// Y
	chars[89]=malloc(6*sizeof(uint16_t));
	chars[89][0]=5;
	chars[89][1]=0x3000;
	chars[89][2]=0xc00;
	chars[89][3]=0x3e0;
	chars[89][4]=0xc00;
	chars[89][5]=0x3000;

	// Z
	chars[90]=malloc(6*sizeof(uint16_t));
	chars[90][0]=5;
	chars[90][1]=0x2060;
	chars[90][2]=0x21a0;
	chars[90][3]=0x2220;
	chars[90][4]=0x2c20;
	chars[90][5]=0x3020;

	// a
	chars[97]=malloc(7*sizeof(uint16_t));
	chars[97][0]=6;
	chars[97][1]=0x1c0;
	chars[97][2]=0x220;
	chars[97][3]=0x220;
	chars[97][4]=0x220;
	chars[97][5]=0x1c0;
	chars[97][6]=0x20;

	// b
	chars[98]=malloc(6*sizeof(uint16_t));
	chars[98][0]=5;
	chars[98][1]=0x3fc0;
	chars[98][2]=0x220;
	chars[98][3]=0x220;
	chars[98][4]=0x220;
	chars[98][5]=0x1c0;

	// c
	chars[99]=malloc(5*sizeof(uint16_t));
	chars[99][0]=4;
	chars[99][1]=0x1c0;
	chars[99][2]=0x220;
	chars[99][3]=0x220;
	chars[99][4]=0x220;

	// d
	chars[100]=malloc(6*sizeof(uint16_t));
	chars[100][0]=5;
	chars[100][1]=0x1c0;
	chars[100][2]=0x220;
	chars[100][3]=0x220;
	chars[100][4]=0x220;
	chars[100][5]=0x3fe0;

	// e
	chars[101]=malloc(5*sizeof(uint16_t));
	chars[101][0]=4;
	chars[101][1]=0x1c0;
	chars[101][2]=0x2a0;
	chars[101][3]=0x2a0;
	chars[101][4]=0x1a0;

	// f
	chars[102]=malloc(6*sizeof(uint16_t));
	chars[102][0]=5;
	chars[102][1]=0x1fe0;
	chars[102][2]=0x2200;
	chars[102][3]=0x2200;
	chars[102][4]=0x2000;
	chars[102][5]=0x1000;

	// g
	chars[103]=malloc(6*sizeof(uint16_t));
	chars[103][0]=5;
	chars[103][1]=0x1c8;
	chars[103][2]=0x228;
	chars[103][3]=0x228;
	chars[103][4]=0x228;
	chars[103][5]=0x3f0;

	// h
	chars[104]=malloc(6*sizeof(uint16_t));
	chars[104][0]=5;
	chars[104][1]=0x3fe0;
	chars[104][2]=0x200;
	chars[104][3]=0x200;
	chars[104][4]=0x200;
	chars[104][5]=0x1e0;

	// i
	chars[105]=malloc(2*sizeof(uint16_t));
	chars[105][0]=1;
	chars[105][1]=0xbe0;

	// j
	chars[106]=malloc(3*sizeof(uint16_t));
	chars[106][0]=2;
	chars[106][1]=0x8;
	chars[106][2]=0xbf0;

	// k
	chars[107]=malloc(5*sizeof(uint16_t));
	chars[107][0]=4;
	chars[107][1]=0x3fe0;
	chars[107][2]=0x80;
	chars[107][3]=0x140;
	chars[107][4]=0x220;

	// l
	chars[108]=malloc(4*sizeof(uint16_t));
	chars[108][0]=3;
	chars[108][1]=0x3fc0;
	chars[108][2]=0x20;
	chars[108][3]=0x20;

	// m
	chars[109]=malloc(6*sizeof(uint16_t));
	chars[109][0]=5;
	chars[109][1]=0x3e0;
	chars[109][2]=0x200;
	chars[109][3]=0x1e0;
	chars[109][4]=0x200;
	chars[109][5]=0x1e0;

	// n
	chars[110]=malloc(5*sizeof(uint16_t));
	chars[110][0]=4;
	chars[110][1]=0x3e0;
	chars[110][2]=0x200;
	chars[110][3]=0x200;
	chars[110][4]=0x1e0;

	// o
	chars[111]=malloc(6*sizeof(uint16_t));
	chars[111][0]=5;
	chars[111][1]=0x1c0;
	chars[111][2]=0x220;
	chars[111][3]=0x220;
	chars[111][4]=0x220;
	chars[111][5]=0x1c0;

	// p
	chars[112]=malloc(6*sizeof(uint16_t));
	chars[112][0]=5;
	chars[112][1]=0x3fc;
	chars[112][2]=0x220;
	chars[112][3]=0x220;
	chars[112][4]=0x220;
	chars[112][5]=0x1c0;

	// q
	chars[113]=malloc(6*sizeof(uint16_t));
	chars[113][0]=5;
	chars[113][1]=0x1c0;
	chars[113][2]=0x220;
	chars[113][3]=0x220;
	chars[113][4]=0x220;
	chars[113][5]=0x3fc;

	// r
	chars[114]=malloc(5*sizeof(uint16_t));
	chars[114][0]=4;
	chars[114][1]=0x1e0;
	chars[114][2]=0x200;
	chars[114][3]=0x200;
	chars[114][4]=0x200;

	// s
	chars[115]=malloc(5*sizeof(uint16_t));
	chars[115][0]=4;
	chars[115][1]=0x120;
	chars[115][2]=0x2a0;
	chars[115][3]=0x2a0;
	chars[115][4]=0x240;

	// t
	chars[116]=malloc(4*sizeof(uint16_t));
	chars[116][0]=3;
	chars[116][1]=0x3fc0;
	chars[116][2]=0x420;
	chars[116][3]=0x420;

	// u
	chars[117]=malloc(6*sizeof(uint16_t));
	chars[117][0]=5;
	chars[117][1]=0x3c0;
	chars[117][2]=0x20;
	chars[117][3]=0x20;
	chars[117][4]=0x20;
	chars[117][5]=0x3e0;

	// v
	chars[118]=malloc(6*sizeof(uint16_t));
	chars[118][0]=5;
	chars[118][1]=0x300;
	chars[118][2]=0xc0;
	chars[118][3]=0x20;
	chars[118][4]=0xc0;
	chars[118][5]=0x300;

	// w
	chars[119]=malloc(8*sizeof(uint16_t));
	chars[119][0]=7;
	chars[119][1]=0x300;
	chars[119][2]=0xc0;
	chars[119][3]=0x20;
	chars[119][4]=0x40;
	chars[119][5]=0x20;
	chars[119][6]=0xc0;
	chars[119][7]=0x300;

	// x
	chars[120]=malloc(6*sizeof(uint16_t));
	chars[120][0]=5;
	chars[120][1]=0x220;
	chars[120][2]=0x140;
	chars[120][3]=0x80;
	chars[120][4]=0x140;
	chars[120][5]=0x220;

	// y
	chars[121]=malloc(6*sizeof(uint16_t));
	chars[121][0]=5;
	chars[121][1]=0x3c8;
	chars[121][2]=0x28;
	chars[121][3]=0x28;
	chars[121][4]=0x28;
	chars[121][5]=0x3f0;

	// z
	chars[122]=malloc(6*sizeof(uint16_t));
	chars[122][0]=5;
	chars[122][1]=0x220;
	chars[122][2]=0x260;
	chars[122][3]=0x2a0;
	chars[122][4]=0x320;
	chars[122][5]=0x220;

	return chars;
}
