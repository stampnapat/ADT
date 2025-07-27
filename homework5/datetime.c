#include <stdio.h>
#include <stdlib.h>

typedef struct datetime {
  int date; // 1-31
  int month; // 1-12
  int year; // 1970++
  int dayOfWeek; // 0-6
  int hour; // 0-23
  int minute; // 0-59
  int second; // 0-59

} datetime_t;

int check_leap(int year);
int cal_year(int *timestamp);
int cal_month(int *timestamp, int year, int *date);
int cal_dayofweek(int *timestamp);
int cal_hour(int *timestamp);
int cal_minute(int *timestamp);
int second(int *timestamp);


datetime_t createDate(int timestamp) {
  datetime_t d;
  int time = timestamp;

  d.year = cal_year(&time);
  d.month = cal_month(&time, d.year, &d.date);
  d.dayOfWeek = cal_dayofweek(&timestamp);
  d.hour = cal_hour(&time);
  d.minute = cal_minute(&time);
  d.second = second(&time);
  return d;

}


int check_leap(int year) {
  if (year % 4 == 0 && (year % 100 != 0 ||  year % 400 == 0)) return 1;
  return 0;

}

int cal_year(int *timestamp) {
  int year = 1970;
  int day = *timestamp / (24 * 60 * 60);
  int used = 0;

  while (1) {
    int is_leap = check_leap(year) ? 366: 365;
    if (day >= is_leap) {
        day -= is_leap;
        used += is_leap;
        year++;
    }else break;
  }

  *timestamp -= used * (24 * 60 * 60);
  return year;
}


int cal_month(int *timestamp,int year,int *date){
  int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int month = 0;
  int day = *timestamp / (24 * 60 * 60);
  int minus_day = 0;
  if (check_leap(year)) months[1] = 29;

  for (int i = 0; i<12; i++){
      if (day >= months[i]){
        day -= months[i];
        month += 1;
        minus_day += months[i];
      }
  }
  *timestamp -= minus_day * (24 * 60 * 60);
  *date = day +1;

  return month + 1;
}



int cal_dayofweek(int *timestamp) {
  int total_day = *timestamp / (24 * 60 * 60);
  total_day = (total_day +4)%7;
  return total_day;

}

int cal_hour(int *timestamp) {
  return (*timestamp / 3600) % 24;

}

int cal_minute(int *timestamp) {
  return (*timestamp / 60) % 60;

}

int second(int *timestamp) {
  return *timestamp%60;
}

void printDate(datetime_t t) {
  const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
  const char *months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP" ,"OCT", "NOV", "DEC"};
  const char *day0 = days[t.dayOfWeek];
  const char *month0 = months[t.month -1];

  printf("%s %d %s %d %02d:%02d:%02d", day0, t.date, month0,t.year,  t.hour, t.minute, t.second);
}


int main(void) {
  datetime_t inputDate;
  int timestamp;
  scanf("%d", &timestamp);
  inputDate = createDate(timestamp);
  printDate(inputDate);
return 0;
}
