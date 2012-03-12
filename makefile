audioedit:audioedit.o Audio_Functions.o
	 gcc -o audioedit audioedit.o Audio_Functions.o
audioedit.o:audioedit.c Audio_Functions.h
	 gcc -c audioedit.c
Audio_Functions.o:Audio_Functions.c Audio_Functions.h
	 gcc -c Audio_Functions.c
