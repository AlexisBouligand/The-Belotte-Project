gcc -L lib -I include main.c src/game/*.c src/menu/*.c src/graphics/*.c src/graphics/menu/*.c src/graphics/game/*.c -o Coinche.exe -lmingw32 -lSDLmain -lSDL -lSDL_ttf 
start Coinche.exe
