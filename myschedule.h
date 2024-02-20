struct Date
{
    int day;
    int month;
    int year;
};
typedef struct Date date;

struct Schedule{
    char constituency[100];
    date d;
};

typedef struct Schedule schedule;

struct Voter{
    int SNO;
    char voterName[50];
    date birthDate;
    char address[50];
    char password[10];
};

typedef struct Voter voter;

int is_validate_date(date d);

// check if the entered data is validate or not
int is_validate_date(date d)
{
    if (d.year < 0 || d.month < 1 || d.month > 12 || d.day < 0 || d.day > 31)
        return 0;

    return 1;
}