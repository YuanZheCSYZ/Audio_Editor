//
//  File name : audioedit.c
//  Project name : Audio_Editor
//  Verision : 1.0
//
//  Created by Zhe Weng on 3/12/12.
//  Copyleft (c) 2012 YuanZheCSYZ. All rights reserved.
//


#define STDIO_H
#include<stdio.h>

#define ASSERT_H
#include<assert.h>

#define STRING_H
#include<string.h>

#define MATH_H
#include<math.h>

#include"Audio_Functions.h"

int const Version_Num = 1;

long Input_Chunk_Size = 0;
long Output_Chunk_Size = 0;

long Subchunk_1_Size = 0;
long Audio_Format = 0;
long Num_Channels = 0;
long Sample_Rate = 0;
long Byte_Rate = 0;
long Block_Align = 0;
long Bits_Per_Sample = 0;
long Subchunk_2_Size = 0;
long OutPut_Subchunk_2_Size = 0;

long TB_Num = 0;
long TE_Num = 0;

FILE *pInput;
FILE *pOutput;


int main(int argc, char* argv[])
{
	 int i=0;
	 int mark = 2;

	 if (2 > argc)
	 {
		  printf("Must at least provide input file and output file!!!\n");
		  return 0;
	 }
	 for( i = 1 ; i < argc ; i++ )
	 {
		  if ( '-' != argv[i][0] || 'h' == argv[i][1])	  // Incorrect input and -help	
		  {
				if ( '-' != argv[i][0] )
					 printf("Incorrect parameter!! : %s\n", argv[i]);
				Show_Help();
		  }
		  else if ( 'v' == argv[i][1])						  // version
				printf("The current version of audioedit is : %d\n",Version_Num);
		  else if ( 'i' == argv[i][1])						  // input file
		  {
				i++;
				mark--;
				//assert ( NULL != strcpy( Input_File_Name, argv[i]) );
				pInput = fopen ( argv[i] ,"r");
				assert(NULL != pInput);
		  }
		  else if ( 'o' == argv[i][1])						  // output file
		  {
				i++;
				mark--;
				//assert ( NULL != strcpy ( Input_File_Name, argv[i]) );
				pOutput = fopen ( argv[i], "w");
				assert(NULL != pOutput);
		  }
		  else if ( 'b' == argv[i][2] )						  // trim begin
		  {
				i++;
				TB_Num = String_To_Num(argv[i]);
				assert(0 <= TB_Num);
		  }
		  else if ( 'e' == argv[i][2] )						  // trim end
		  {
				i++;
				TE_Num = String_To_Num(argv[i]);
				assert(0 <= TE_Num);
		  }
		  else
		  {
				printf("Incorrect parameter!! : %s\n",argv[i]);
				return 0;
		  }
	 }

	 if (mark)
	 {
		  printf("Must provide both input and output file name!!\n");
		  return 0;
	 }

	 Audio_Trimmer();
	 
	 return 1;
}
