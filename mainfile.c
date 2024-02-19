#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myschedule.h"


void myExit();
void drawLine();
void admin();
void electionSchedule();
int saveElectionSchedule(schedule sd);

int main()
{
    int user_type;

    drawLine();
    printf("\n -- Welcome to VOTING SYSTEM--");
    drawLine();

    printf("\n1.Admin\n2.Voter\n3.Stop");
again:
    printf("\nEnter who you are:(Admin:1/Voter:2/Stop:3): ");
    scanf("%d", &user_type);
    switch (user_type)
    {
    case 1:
        admin();
        break;
    case 2:
        break;
    case 3:

        myExit(0);
        break;
    default:
        printf("\ninvalid Option");
        goto again;
    }
    return 0;
}
int saveElectionSchedule(schedule sd)
{
    FILE *fp;

    fp = fopen("savedfile/schedule.txt", "a");
    if (fp == NULL)
    {
        printf("\n File does not exist\n");
    }
    int n = fwrite(&sd, sizeof(sd), 1, fp);
    if (n > 0)
    {
        printf("\n Election schedule saved in file...");
    }
}

void myExit()
{
    printf("\n ** ~Thanks for using Voting System~ **");
    exit(0);
}

void drawLine()
{
    int i;
    printf("\n");
    for (i = 1; i <= 50; i++)
    {
        printf("*");
    }
    printf("\n");
}
void electionSchedule()
{
    schedule scd;
    char constiuent[30];
    char choice;
    do
    {
        printf("\n Registering Schedule:");
        drawLine();
        printf("\n Enter your constiuency:");
        scanf("%s", scd.constituency);
    again:
        printf("\n Enter Date(dd/mm/yyyy) of election:");
        if (scanf("%d %d %d", &scd.d.day, &scd.d.month, &scd.d.year) != 3 || (is_validate_date(scd.d) != 1))
        {

            printf("\n Invalid input\n");
            goto again;
        }
        printf("\n Process to save in file....");
        saveElectionSchedule(scd);
        printf("\n Do you want to save more....(yes->y/no->n)");
        scanf(" %c", &choice);
    } while (choice == 'y');
    printf("\n Thank you for registering the schedule..\n");
    drawLine();
}

void admin()
{
    int passcount = 3;
    char password[8];
    int adminChoice;
    char choice;
    while (passcount >= 1)
    {
        printf("\n Enter your admin Password: ");
        scanf("%s", password);
        if (strcmp(password, "admin@12") == 0)
        {
            do
            {
                printf("\n   ** Welcome to Admin Dashboard**");
                drawLine();
                printf("\n\t1. Election Schedule-");
                printf("\n\t2. Candidate Registration-");
                printf("\n\t3. Voter Registration-");
                printf("\n\t4. Update Voter's Details-");
                printf("\n\t5. Search Voter's Details-");
                printf("\n\t6. Vote Result-");
                printf("\n\t7. Exit");
            again:
                printf("\nEnter your choice: ");
                scanf("%d", &adminChoice);
                switch (adminChoice)
                {
                case 1:
                    electionSchedule();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                default:
                    printf("\nInvalid option !! try again--");
                    goto again;
                }
                printf("\n Do you want to continue the admin dashboard..(yes-y/no-n)");
                scanf(" %c", &choice);
            } while (choice == 'y');
            printf("\n Thank you admin..you have quit your dashboard...");
            drawLine();
        }
        else
        {
            passcount--;
            if (passcount < 1)
            {
                printf("\n Sorry You have lost your chance!!!");
                myExit();
            }

            printf("\n Sorry! Invalid Password!");
            printf("\n Try again ! you have %d times left", passcount);
        }
    }
}