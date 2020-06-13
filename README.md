# The Belotte Project
Project realized by Alexis Bouligand, Louis Giacinti and Oscar Dewasmes during their studies at the university of technology of Belfort Montbeliard. Semester P2020, as part of the IFE UV.
****

Resolution used : 1600*900


## How to launch:
You  can use the file compile.bat to compile with gcc or execute the command :
`gcc -L lib -I include main.c src/game/*.c src/menu/*.c src/graphics/*.c src/graphics/menu/*.c src/graphics/game/*.c -o Coinche.exe -lmingw32 -lSDLmain -lSDL -lSDL_ttf `

To compile within Code:Blocks you need to include SDL and TTF to your Code:Blocks.


## Controles:
**[mouse]** to navigate menus and select cards to play
**[Space]** to end the trick

## Abreviations:
D for Diamonds, C for Clubs, S for Spades, H for Heart.
AI2 : Your teammate.
