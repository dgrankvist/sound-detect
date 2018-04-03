// constant definitions
#define ESC 0x1B
#define BAR "\u2590"
#define UNICODE		// conditional compiling

enum FGCOLOR {BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
enum BGCOLOR {BGBLACK = 40, BGRED, BGGREEN, BGYELLOW, BGBLUE, BGMAGENTA, BGCYAN, BGWHITE};
// function prototypes

void clearScreen(void);
void gotoxy(int, int);
void bar(int, double);
void setColor(int);
