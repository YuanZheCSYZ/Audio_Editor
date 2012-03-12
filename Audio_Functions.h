//
//  File name : Audio_Functions.h
//  Project name : Audio_Editor
//  Verision : 1.0
//
//  Created by Zhe Weng on 3/12/12.
//  Copyleft (c) 2012 YuanZheCSYZ. All rights reserved.
//

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STRING_H
#include<string.h>
#endif

#ifndef MATH_H
#include<math.h>
#endif

#ifndef ASSERT_H
#include<assert.h>
#endif

extern FILE *pInput;
extern FILE *pOutput;
extern long Input_Chunk_Size;
extern long Output_Chunk_Size;

extern long Subchunk_1_Size;
extern long Audio_Format;
extern long Num_Channels;
extern long Sample_Rate;
extern long Byte_Rate;
extern long Block_Align;
extern long Bits_Per_Sample;
extern long Subchunk_2_Size;
extern long OutPut_Subchunk_2_Size;

extern long TB_Num;
extern long TE_Num;



void Show_Help();

long String_To_Num(char *Input_String);

unsigned long Get_Info( int B_Length, unsigned char Temp_Storage, char flag);

void Audio_Trimmer();