#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
    int m_TotalDays;
    int m_WorkDays;
} TResult;

int isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0 && year % 4000 != 0) || (year % 400 == 0));
}

int daysInMonth(int year, int month)
{
    if (month == 2){
        if (isLeapYear(year) == 1){
            return 29;
        }else{
            return 28;
        }
    }
        else if (month == 4 || month == 6 || month == 9 || month == 11){
            return 30;
    }   else{
            return 31;
    }
}

int isValidDate(int y, int m, int d) 
{
    return(!(y < 2000 || m < 1 || m > 12 || d < 1 || d > daysInMonth(y, m)));
}

bool isHoliday (int y, int m, int d){
    if ((m == 1 && d == 1) || (m == 5 && d == 1) 
        || (m == 5 && d == 8)|| (m == 7 && (d == 5 || d == 6)) 
        || (m == 9 && d == 28)|| (m == 10 && d == 28) || (m == 11 && d == 17) 
        || (m == 12 && (d >= 24 && d <= 26))){
        return true;
    } else {
        return false;
    }
}

bool isWorkDay(int y, int m, int d)
{
     if (isValidDate(y, m, d) == 0){
        return false;
    }
     if (isHoliday(y,m,d) == true){
        return false;
     }
       
    int offset, mm, yy;

    offset = (14 - m) / 12;
    yy = y - offset;
    mm = m + 12 * offset - 2;
    int h = (d + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;

    if (h >= 1 && h <= 5){
        return true;
    }else{
        return false;
    }
}

TResult countDays(int y1, int m1, int d1, int y2, int m2, int d2)
{
    TResult result;
    if (isValidDate(y1, m1, d1) == 0 || isValidDate(y2, m2, d2) == 0)
    {
        result.m_TotalDays = -1;
        result.m_WorkDays = -1;
        return result;
    }

    int m_TotalDays = 1;
    int m_WorkDays = 0;

    if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2))
    {
        result.m_TotalDays = -1;
        result.m_WorkDays = -1;
        return result;
    }
    
    while (y1 != y2 || m1 != m2 || d1 != d2)
    {
        if (isWorkDay(y1, m1, d1))
        {
            m_WorkDays++;
        }
        m_TotalDays++;

        d1++;
        if (d1 > daysInMonth(y1, m1))
        {
            d1 = 1;
            m1++;
            if (m1 > 12)
            {
                m1 = 1;
                y1++;
            }
        }
    }
    if (isWorkDay(y1, m1, d1))
    {
        m_WorkDays++;
    }

    result.m_TotalDays = m_TotalDays;
    result.m_WorkDays = m_WorkDays;
    return result;
}

int main(int argc, char *argv[])
{
    TResult r;

    assert(isWorkDay(2023, 10, 10));

    assert(!isWorkDay(2023, 11, 11));

    assert(!isWorkDay(2023, 11, 17));

    assert(!isWorkDay(2023, 11, 31));

    assert(!isWorkDay(2023, 2, 29));

    assert(!isWorkDay(2004, 2, 29));

    assert(isWorkDay(2008, 2, 29));

    assert(!isWorkDay(2001, 2, 29));

    assert(!isWorkDay(1996, 1, 2));

    r = countDays(2023, 11, 1,
                  2023, 11, 30);
    assert(r.m_TotalDays == 30);
    assert(r.m_WorkDays == 21);

    r = countDays(2023, 11, 1,
                  2023, 11, 17);
    assert(r.m_TotalDays == 17);
    assert(r.m_WorkDays == 12);

    r = countDays(2023, 11, 1,
                  2023, 11, 1);
    assert(r.m_TotalDays == 1);
    assert(r.m_WorkDays == 1);

    r = countDays(2023, 11, 17,
                  2023, 11, 17);
    assert(r.m_TotalDays == 1);
    assert(r.m_WorkDays == 0);

    r = countDays(2023, 1, 1,
                  2023, 12, 31);
    assert(r.m_TotalDays == 365);
    assert(r.m_WorkDays == 252);

    r = countDays(2024, 1, 1,
                  2024, 12, 31);
    assert(r.m_TotalDays == 366);
    assert(r.m_WorkDays == 254);

    r = countDays(2000, 1, 1,
                  2023, 12, 31);
    assert(r.m_TotalDays == 8766);
    assert(r.m_WorkDays == 6072);

    r = countDays(2001, 2, 3,
                  2023, 7, 18);
    assert(r.m_TotalDays == 8201);
    assert(r.m_WorkDays == 5682);

    r = countDays(2021, 3, 31,
                  2023, 11, 12);
    assert(r.m_TotalDays == 957);
    assert(r.m_WorkDays == 666);

    r = countDays(2001, 1, 1,
                  2000, 1, 1);
    assert(r.m_TotalDays == -1);
    assert(r.m_WorkDays == -1);

    r = countDays(2001, 1, 1,
                  2023, 2, 29);
    assert(r.m_TotalDays == -1);
    assert(r.m_WorkDays == -1);

    return EXIT_SUCCESS;
}
