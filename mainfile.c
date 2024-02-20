#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "myschedule.h"
#include "candidate.h"

void myExit();
void drawLine();
void admin();
void electionSchedule();
void saveElectionSchedule(schedule sd);
void saveCandidateRegistration(candidate can);
int autoGenerate();
int ageEligibility(date d);
void viewCandidateList();
void viewVoterList();
void updateVoterDetails();

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
int ageEligibility(date d)
{
    time_t current_time = time(NULL);

    // convert the current time to a local time structure
    struct tm *local_time = localtime(&current_time);

    // Extract the year form the local time structure
    int current_year = local_time->tm_year + 1900;

    if ((current_year - d.year) <= 18)
    {
        return 0;
    }
    return 1;
}
void saveElectionSchedule(schedule sd)
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
    fclose(fp);
}
void saveCandidateRegistration(candidate can)
{
    FILE *fp;

    fp = fopen("savedfile/candidatelist.txt", "a");
    if (fp == NULL)
    {
        printf("\n File does not exist\n");
    }
    int n = fwrite(&can, sizeof(can), 1, fp);
    if (n > 0)
    {
        printf("\n Candidate Registered sucessfully....");
    }
    fclose(fp);
}
void saveVoterRegistration(voter v)
{
    FILE *fp;

    fp = fopen("savedfile/voterlist.txt", "a");
    if (fp == NULL)
    {
        printf("\n File does not exist\n");
    }
    int n = fwrite(&v, sizeof(v), 1, fp);
    if (n > 0)
    {
        printf("\n Candidate Registered sucessfully....");
    }
    fclose(fp);
}

int autoGenerate()
{
    srand(time(NULL));

    // Generate a random number between 0 and RAND_MAX
    return rand();
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

void candidateRegistration()
{
    candidate can;
    char choice;
    printf("\n** Welcome to candiate Registration **\n");
    drawLine();
    do
    {
        printf("\n Enter Candidate Name, Poltical Party and Constituency: ");
        scanf("%s%s%s", can.name, can.pParty, can.canFrom);
        printf("\n Processing to save ....");

        saveCandidateRegistration(can);
        printf("\n Do you want to add more candidate list....(yes->y/no->n)");
        scanf(" %c", &choice);
    } while (choice == 'y');
    printf("\n Thanks for candidate registration...");
}

void viewCandidateList()
{
    FILE *fp;
    candidate can;
    fp = fopen("savedfile/candidatelist.txt", "r");
    if (fp == NULL)
    {
        printf("\n Error in opening file...");
        myExit();
    }
    printf("\n----------------------------------------------------------------\n");
    printf("\n Name\t\t | Poltical Party\t | Candidacy From");
    printf("\n----------------------------------------------------------------\n");
    while (fread(&can, sizeof(candidate), 1, fp) == 1)
    {
        printf("%s              ", can.name);
        printf("\t%s              ", can.pParty);
        printf("\t%s             \n", can.canFrom);
    }
    printf("\n----------------------------------------------------------------\n");

    fclose(fp);
}

void voterRegistraiton()
{
    voter v;
    char choice;
    printf("\n **Welcome to Voter Registration **\n");
    drawLine();
    do
    {
        v.SNO = autoGenerate();
        printf("SNO:%d", v.SNO);
        printf("\n Enter voter name:");
        scanf("%s", v.voterName);
    again:
        printf("\n Enter Date of birth(dd/mm/yyyy):");
        scanf("%d%d%d", &v.birthDate.day, &v.birthDate.month, &v.birthDate.year);
        if (is_validate_date(v.birthDate) != 1)
        {
            printf("\n INvalid Date ...try again..");
            goto again;
        }
        if (ageEligibility(v.birthDate) != 1)
        {
            printf("\n  Not eligible to vote....less than 18.");
            goto next;
        }
        printf("\n Enter the address of voter:");
        scanf("%s", &v.address);
        printf("\n Enter the password:");
        scanf("%s", v.password);

        printf("\n processing to save voterlist.....");
        saveVoterRegistration(v);

    next:
        printf("\n Do you want to add more voter list....(yes->y/no->n)");
        scanf(" %c", &choice);
    } while (choice == 'y');
    printf("\n Thanks for voter registration..");
}
void viewVoterList()
{
    FILE *fp;
    voter v;
    fp = fopen("savedfile/voterlist.txt", "r");
    if (fp == NULL)
    {
        printf("\n Error in opening file...");
        myExit();
    }
    printf("\n----------------------------------------------------------------\n");
    printf("\nSNO\t|Name of Voter\t|Date of Birth\t|Address|Password");
    printf("\n----------------------------------------------------------------\n");
    while (fread(&v, sizeof(voter), 1, fp) == 1)
    {
        printf("%d\t", v.SNO);
        printf("%s\t\t", v.voterName);
        printf("%d/%d/%d\t", v.birthDate.day, v.birthDate.month, v.birthDate.year);
        printf("%s\t", v.address);
        printf("%s\n", v.password);
    }
    printf("\n----------------------------------------------------------------\n");

    fclose(fp);
}

void updateVoterDetails()
{
    voter v;
    FILE *fp;
    int vid;
    unsigned flag = 0;
    char choice;
    printf("\n ** Welcome to voter update section..");
    drawLine();
    do
    {
        fp = fopen("savedfile/voterlist.txt", "r+");
        if (fp == NULL)
        {
            printf("\n Error in opening file...");
            myExit();
        }
        printf("\n Enter the SNO of voter whose record is to be updated: ");
        scanf("%d", &vid);
        drawLine();
        while (fread(&v, sizeof(voter), 1, fp) == 1)
        {
            if (v.SNO == vid)
            {
                printf("\n Enter new Data -->\n");
                printf("\n Enter voter name: ");
                scanf("%s", &v.voterName);
                printf("\n Enter Date of Birth:(dd mm yyyy):");
                scanf("%d%d%d", &(v.birthDate.day), &(v.birthDate.month), &(v.birthDate.year));
                printf("\n Enter address: ");
                scanf("%s", &v.address);
                printf("\n Enter New password: ");
                scanf("%s", &v.password);
                fseek(fp, -sizeof(voter), 1);
                fwrite(&v, sizeof(voter), 1, fp);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n Record not found in list...");
            drawLine();
        }
        else
        {
            printf("\n Record updated successfully...\n");
            drawLine();
        }
        printf("\n Do you want to update more..(yes-y/no-n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');
    fclose(fp);
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
        if (strcmp(password, "ad") == 0)
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
                printf("\n\t7. View Candidate list:");
                printf("\n\t8. View Voter List:");
                printf("\n\t9. Exit");
            again:
                printf("\nEnter your choice: ");
                scanf("%d", &adminChoice);
                switch (adminChoice)
                {
                case 1:
                    electionSchedule();
                    break;
                case 2:
                    candidateRegistration();
                    break;
                case 3:
                    voterRegistraiton();
                    break;
                case 4:
                    updateVoterDetails();
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    viewCandidateList();
                    break;
                case 8:
                    viewVoterList();
                    break;

                case 9:
                    myExit();
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
            myExit();
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