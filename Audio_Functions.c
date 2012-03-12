//
//  File name : Audio_Functions.c
//  Project name : Audio_Editor
//  Verision : 1.0
//
//  Created by Zhe Weng on 3/12/12.
//  Copyleft (c) 2012 YuanZheCSYZ. All rights reserved.
//

#include"Audio_Functions.h"


void Show_Help()
{
    printf(" audioedit [-tb n] [-te m] -i inputfile.wav -o outputfile.wav \n");
}


long String_To_Num(char *Input_String)
{
    int length = strlen(Input_String);
    int i = 0;
    long temp = 0;
    for (i=0; i < length; i++)
        temp = temp * 10 + Input_String[i] - 48;
    return temp;
}


unsigned long Get_Figure(int B_Length, unsigned char Temp_Storage, char flag)
{
    unsigned long temp_long = Temp_Storage;
    int i = 1;
    
    if (flag)
        fputc(Temp_Storage,pOutput);
    while (i <= B_Length )
    {
        Temp_Storage = fgetc(pInput);
        if (flag)
            fputc(Temp_Storage,pOutput);
        temp_long = temp_long + pow(16, 2*i) * Temp_Storage;
        i++;
    }
    return temp_long;
}


void Audio_Trimmer()
{
    unsigned char Temp_Storage;
    int i = 0;
    int j = 0;
    long temp;
    
    while ( EOF != ( Temp_Storage = fgetc(pInput) ) && 0 == feof(pInput) )
    {
        //	  printf("%02x",Temp_Storage);
        
        if (i < 4)			 // "RIFF" -- ChunkID
        {
            fputc ( Temp_Storage, pOutput );
        }
        else if ( i < 8 )	 // ChunkSize
        {
            Input_Chunk_Size = Get_Figure (3, Temp_Storage, 0);
            i = 7;
            printf("Current input audio size is : %ld\n",Input_Chunk_Size);
            
            Output_Chunk_Size = Input_Chunk_Size - 2 * (TB_Num + TE_Num);
			//	Output_Chunk_Size = Input_Chunk_Size - (Bits_Per_Sample * Num_Channels /8) * (TB_Num + TE_Num);
            printf("Current output audio size is : %ld\n",Output_Chunk_Size);
            
            for (j = 0, temp = Output_Chunk_Size ; j < 4 ; j++)
            {
                Temp_Storage = temp % 256;
                fputc(Temp_Storage,pOutput);
                temp /= 256;
            }
        }
        else if ( i < 12 )	 // "WAVE" -- Format
        {
            fputc ( Temp_Storage, pOutput );
        }
        else if ( i < 16)	 // "fmt " -- Subchunk1ID
        {
            fputc ( Temp_Storage, pOutput );
        }
        else if ( i < 20)		 // Subchunk1Size = 16 
        {
            Subchunk_1_Size = Get_Figure (3, Temp_Storage,1);
            i = 19;
            printf("Current input audio subchunk 1 size is : %ld\n",Subchunk_1_Size);
        }
        else if ( i < 22)	 // Audio Format
        {
            Audio_Format = Get_Figure (1, Temp_Storage,1);
            i = 21;
            printf("Current input audio Format is : %ld\n",Audio_Format);
        }
        else if ( i < 24)	 // Num Channels
        {
            Num_Channels = Get_Figure (1, Temp_Storage,1);
            i = 23;
            printf("Current input audio the num of channels is : %ld\n",Num_Channels);
        }
        else if ( i < 28) // Sample Rate
        {
            Sample_Rate = Get_Figure (3, Temp_Storage,1);
            i = 27;
            
            printf("Current input audio sample rate is : %ld\n",(unsigned long)Sample_Rate);
        }
        else if ( i < 32)	 // Byte Rate
        {
            Byte_Rate = Get_Figure (3, Temp_Storage,1);
            i = 31;
            
            printf("Current input audio byte rate is : %ld\n",Byte_Rate);
        }
        else if ( i < 34)	 // Block Align
        {
            Block_Align = Get_Figure (1, Temp_Storage,1);
            i = 33;
            
            printf("Current input audio block align is : %ld\n",Block_Align);
        }
        else if ( i < 36) // Bits Per Sample
        {
            Bits_Per_Sample = Get_Figure (1, Temp_Storage,1);
            i = 35;
            
            printf("Current input audio bits per sample is : %ld\n",Bits_Per_Sample);
        }
        else if (i < 40)	 // "data"
        {
            fputc(Temp_Storage, pOutput);
        }
        else if ( i < 44) // Subchunk 2 Size
        {
            Subchunk_2_Size = Get_Figure (3, Temp_Storage,0);
            i = 43;
            printf("Current input audio subchunk 2 size is : %ld\n",Subchunk_2_Size);
            
            OutPut_Subchunk_2_Size = Subchunk_2_Size - (Bits_Per_Sample * Num_Channels /8) * (TB_Num + TE_Num);
            
            assert (0 <= OutPut_Subchunk_2_Size);
            
            printf("Current output audio subchunk 2 size is : %ld\n",OutPut_Subchunk_2_Size);
            for(j=0;j<4;j++)
            {
                Temp_Storage = OutPut_Subchunk_2_Size % 256;
                fputc(Temp_Storage, pOutput);
                OutPut_Subchunk_2_Size /= 256;
            }
            break;
        }
        else
        {
            assert(0);
        }
        i++;
    }
    
    i = TB_Num * Bits_Per_Sample * Num_Channels / 8;
    printf("Trim %d sample(s) from the beginning of input file\n",i);
    while (i > 0 &&  EOF != ( Temp_Storage = fgetc(pInput) ) && 0 == feof(pInput) )
    {
        if ( 1 == i )
            break;
        i--;
    }
    
    i = Input_Chunk_Size - 36 - 4 - 4 - ( Bits_Per_Sample * Num_Channels / 8 ) * (TB_Num + TE_Num); 
    printf("The rest file size is %d\n",i);
    while ( 0 < i && EOF != ( Temp_Storage = fgetc(pInput) ) )
    {
        i--;
        fputc(Temp_Storage, pOutput);
    }
    
}
