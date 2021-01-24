CC = gcc
WINDRES  = windres.exe

CFLAGS  = -g -Wall -municode -mwindows
INCLUDES_i686 = -I/mingw32/include
INCLUDES_x86_64 = -I/mingw64/include
LFLAGS_i686 = -L/mingw32/lib
LFLAGS_x86_64 = -L/mingw64/lib
LIBS = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
MACROS = -D__ASSETS__=\"\\\"${CURDIR}/src/assets/\\\"\"
INPUT = '${CURDIR}/src/main.c' version.res
OUTPUT_i686 = '${CURDIR}/bin/i686/Royal Chess.exe'
OUTPUT_x86_64 = '${CURDIR}/bin/x86_64/Royal Chess.exe'

TARGET = main

all: versionInfo-i686 game-i686 versionInfo-x86_64 game-x86_64

versionInfo-i686: 
	/msys2_shell.cmd -defterm -mingw32 -no-start -full-path -here -c "${WINDRES} version.rc -O coff -o version.res"

game-i686:
	/msys2_shell.cmd -defterm -mingw32 -no-start -full-path -here -c "$(CC) $(CFLAGS) -o $(OUTPUT_i686) ${INPUT} ${INCLUDES_i686} ${LFLAGS_i686} ${LIBS} ${MACROS} -m32"

versionInfo-x86_64: 
	/msys2_shell.cmd -defterm -mingw64 -no-start -full-path -here -c "${WINDRES} version.rc -O coff -o version.res"

game-x86_64:
	/msys2_shell.cmd -defterm -mingw64 -no-start -full-path -here -c "$(CC) $(CFLAGS) -o $(OUTPUT_x86_64) ${INPUT} ${INCLUDES_x86_64} ${LFLAGS_x86_64} ${LIBS} ${MACROS}"