


#include "Diceroll.h"


//=================================== 静态存储期，外部连接，文件作用域，所有函数外 ===========================================
int roll_count = 0; /* 外部链接 */


static int rollem(int sides) // 该文件属于该私有文件*/
{
    int roll;

    roll = rand() % sides + 1;
    ++roll_count; /* 计算函数被调次数 */

    return roll;
}


int roll_n_dice(int dice, int sides)
{
    int d;
    int total = 0;
    if (sides < 2)
    {
        printf("Need at least 2 sides.\n");
        return -2;
    }
    if (dice < 1)
    {
        printf("Need at least 1 die.\n");
        return -1;
    }

    for (d = 0; d < dice; d++)
        total += rollem(sides);

    return total;
}

void maindice(void)
{
    int dice,roll;
    int sides;
    int status;

    srand((unsigned int) time(0)); /* randomize seed      */
    printf("Enter the number of sides per die, 0 to stop.\n");
    while (scanf("%d", &sides) == 1 && sides > 0 )
    {
        printf("How many dice?\n");
        if ((status =scanf("%d", &dice)) != 1)
        {
            if (status == EOF)
                break;             /* exit loop           */
            else
            {
                printf("You should have entered an integer.");
                printf(" Let's begin again.\n");
                while (getchar() != '\n')
                    continue;     /* dispose of bad input */
                printf("How many sides? Enter 0 to stop.\n");
                continue;         /* new loop cycle       */
            }
        }
        roll = roll_n_dice(dice, sides);
        printf("You have rolled a %d using %d %d-sided dice.\n", roll, dice, sides);
        printf("How many sides? Enter 0 to stop.\n");
    }
    printf("The rollem() function was called %d times.\n",
           roll_count);           /* use extern variable */

    printf("GOOD FORTUNE TO YOU!\n");

}
