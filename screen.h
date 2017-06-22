//frontground color value
enum FGCOLOR { BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
//define macro 
#define bg(a) (a+10)    
//replace all "BAR" with the character code
#define BAR "\u2590"
//declare functions
void clearScreen(void);
void gotoxy(short x, short y);
void setColors(short fg, short bg);
void dispBar(short x, short y, short bottom);
void resetColors(void);
