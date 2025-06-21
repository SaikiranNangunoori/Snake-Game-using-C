// Sample Program to implement Snake game
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
int length;
int bend_no;
int len;
int life;
void record();
void load();
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
struct coordinate 
{
    int x;
    int y;
    int direction;
};
typedef struct coordinate coordinate;
coordinate head, bend[500], food, body[30];
int main() 
{
    Print();
    system("cls");
    system("color 3f");
    load();
    length = 5;
    head.x = 25;
    head.y = 20;
    head.direction = RIGHT;
    Boarder();
    Food();
    life = 3;
    bend[0] = head;
    Move();
    return 0;
}
void Move() 
{
    int a, i;
    do 
	{
        Food();
        fflush(stdin);
        len = 0;
        for (i = 0; i < 30; i++) 
		{
            body[i].x = 0;
            body[i].y = 0;
            if (i == length)
                break;
        }
        Delay(length);
        Boarder();
        printf("Lives: %d", life); // Display the remaining lives
        if (head.direction == RIGHT)
            Right();
        else if (head.direction == LEFT)
            Left();
        else if (head.direction == DOWN)
            Down();
        else if (head.direction == UP)
            Up();
        ExitGame();
    } 
	while (!kbhit());
    a = getch();
    if (a == 27) 
	{
        system("cls");
        exit(0);
    }
    char key = getch();
    if ((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) ||
        (key == LEFT && head.direction != RIGHT && head.direction != LEFT) ||
        (key == UP && head.direction != DOWN && head.direction != UP) ||
        (key == DOWN && head.direction != UP && head.direction != DOWN)) {
        bend_no++;
        bend[bend_no] = head;
        head.direction = key;
        if (key == UP)
            head.y--;
        if (key == DOWN)
            head.y++;
        if (key == RIGHT)
            head.x++;
        if (key == LEFT)
            head.x--;
        Move();
    } 
	else if (key == 27) 
	{
        system("cls");
        exit(0);
    } 
	else 
	{
        printf("\a");
        Move();
    }
}
void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GotoXY(int x, int y) 
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}
void load() 
{
    int row, col, r, c, q;
    gotoxy(36, 14);
    printf("Loading...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++) 
	{
        for (q = 0; q <= 100000000; q++); // to display the character slowly
        printf("%c", 177);
    }
    getch();
}
void Down() 
{
    int i;
    for (i = 0; i <= (head.y - bend[bend_no].y) && len < length; i++) 
	{
        GotoXY(head.x, head.y - i);
        if (len == 0)
            printf("v");
        else
            printf("*");
        body[len].x = head.x;
        body[len].y = head.y - i;
        len++;
    }
    Bend();
    if (!kbhit())
        head.y++;
}
void Delay(long double k) 
{
    Score();
    long double i;
    for (i = 0; i <= (10000000); i++);
}
void ExitGame() 
{
    int i, check = 0;
    for (i = 4; i < length; i++) 
	{
        if (body[0].x == body[i].x && body[0].y == body[i].y) 
		{
            check++;
        }
        if (i == length || check != 0)
            break;
    }
    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0) 
	{
        life--;
        if (life >= 0) 
		{
            head.x = 25;
            head.y = 20;
            bend_no = 0;
            head.direction = RIGHT;
            Move();
        } else {
            system("cls");
            printf("All Lives Completed\nBetter Luck Next Time!!!\nPress Any Key To Quit The Game\n");
            record();
            exit(0);
        }
    }
}
void Food() 
{
    if (head.x == food.x && head.y == food.y) 
	{
        length++;
        time_t a;
        a = time(0);
        srand(a);
        food.x = rand() % 70;
        if (food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if (food.y <= 10)
            food.y += 11;
    } 
	else if (food.x == 0) 
	{
        food.x = rand() % 70;
        if (food.x <= 10)
            food.x += 11;
        food.y = rand() % 30;
        if (food.y <= 10)
            food.y += 11;
    }
}
void Left() 
{
    int i;
    for (i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++) 
	{
        body[len].x = head.x + i;
        body[len].y = head.y;
        GotoXY(body[len].x, body[len].y);
        if (len == 0)
            printf("<");
        else
            printf("*");
        len++;
    }
    Bend();
    if (!kbhit())
        head.x--;
}
void Right() 
{
    int i;
    for (i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++) 
	{
        body[len].x = head.x - i;
        body[len].y = head.y;
        GotoXY(body[len].x, body[len].y);
        if (len == 0)
            printf(">");
        else
            printf("*");
        len++;
    }
    Bend();
    if (!kbhit())
        head.x++;
}
void Bend() 
{
    int i, j, diff;
    for (i = bend_no; i >= 0 && len < length; i--) 
	{
        if (bend[i].x == bend[i - 1].x) 
		{
            diff = bend[i].y - bend[i - 1].y;
            if (diff < 0)
                for (j = 1; j <= (-diff); j++) 
				{
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y + j;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff; j++) 
				{
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y - j;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
        } 
		else if (bend[i].y == bend[i - 1].y) 
		{
            diff = bend[i].x - bend[i - 1].x;
            if (diff < 0)
                for (j = 1; j <= (-diff) && len < length; j++) 
				{
                    body[len].x = bend[i].x + j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff && len < length; j++) 
				{
                    body[len].x = bend[i].x - j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
        }
    }
}
void Boarder() 
{
    system("cls");
    int i;
    GotoXY(food.x, food.y);
    printf("F");
    for (i = 10; i < 71; i++) 
	{
        GotoXY(i, 10);
        printf("!");
        GotoXY(i, 30);
        printf("!");
    }
    for (i = 10; i < 31; i++) 
	{
        GotoXY(10, i);
        printf("!");
        GotoXY(70, i);
        printf("!");
    }
}
void Print() 
{
    printf("Knowledge 360\n\n");
    printf("\tWelcome To The Snake Game.\n\n (Press Any Key To Continue...)\n");
    getch();
    system("cls");
    printf("\tGame Instructions:\n");
    printf("\n-> Use Arrow Keys To Move The Snake.\n\n-> You Will Be Provided Foods (F) at The random Coordinates Of The Screen Which You Have To Eat, To Make Score.\n");
    printf("Everytime You Eat A Food The Length Of The Snake Will Be Increased By 1 Element indicating the score.");
    printf("\n\n-> Here You Are Provided With Three Lives. Your Life Will Decrease As You Hit The Wall Or Snake's Body.");
    printf("\n\n-> You Can Pause The Game While Playing By Pressing Any Key, To Continue The Paused Game Press Any Key Once Again.");
    printf("\n\n-> If You Want To Exit Press ESC.\n");
    printf("\n\n\nPress Any Key To Play The Game...");
    if (getch() == 27)
        exit(0);
}
void record() 
{
    char plname[20], nplname[20], cha, c;
    int i, j, px;
    FILE *info;
    info = fopen("record.txt", "a+");
    getch();
    system("cls");
    printf("Enter Your Name: ");
    scanf("%[^\n]", plname);
    for (j = 0; plname[j] != '\0'; j++) 
	{
        nplname[0] = toupper(plname[0]);
        if (plname[j - 1] == ' ') 
		{
            nplname[j] = toupper(plname[j]);
            nplname[j - 1] = plname[j - 1];
        } else
            nplname[j] = plname[j];
    }
    nplname[j] = '\0';
    fprintf(info, "\n\nPlayer Name: %s\n", nplname);
    time_t mytime;
    mytime = time(NULL);
    fprintf(info, "\nPlayed Date:%s", ctime(&mytime));
    fprintf(info, "Score: %d\n", px = Scoreonly());
    for (i = 0; i <= 50; i++)
    fprintf(info, "%c", '_');
    fprintf(info, "\n");
    fclose(info);
    printf("Press 'y' if you want to see past records (y/n): ");
    cha = getch();
    system("cls");
    if (cha == 'y') 
	{
        info = fopen("record.txt", "r");
        do
        {
            putchar(c = getc(info));
        } while (c != EOF);
    }
    fclose(info);
}
int Score() 
{
    int score;
    GotoXY(20, 8);
    score = length - 5;
    printf("Score: %d", score);
    score = length - 5;
    GotoXY(50, 8);
    printf("Length: %d", length);
    return score;
}
int Scoreonly() 
{
    int score;
    score = length - 5;
    return score;
}
void Up() 
{
    int i;
    for (i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++) 
	{
        GotoXY(head.x, head.y + i);
        if (len == 0)
            printf("^");
        else
            printf("*");
        body[len].x = head.x;
        body[len].y = head.y + i;
        len++;
    }
    Bend();
    if (!kbhit())
        head.y--;
}
void record_list() 
{
    int i;
    char name[20], cha, ch, c;
    FILE *list;
    list = fopen("record.txt", "r");
    do {
        putchar(c = getc(list));
    } 
	while (c != EOF);
}
void snake_game() 
{
    system("cls");
    system("color 5e");
    char key;
    Print();
    system("cls");
    load();
    length = 5;
    head.x = 25;
    head.y = 20;
    head.direction = RIGHT;
    Boarder();
    Food();
    life = 3;
    bend[0] = head;
    Move();
}
