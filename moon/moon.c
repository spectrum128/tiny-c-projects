#include <stdio.h>
#include <time.h>


int moon_phase(int year, int month, int day);
char* get_moon_phase(int year, int month, int day);


int main(int argc, char *argv[]){

    time_t now;
    struct tm *clock;
    int day, month, year;

    time(&now);
    clock = localtime(&now);
    day = clock->tm_mday;
    month = clock->tm_mon;
    year = clock->tm_year + 1900;
    
    char *phase = get_moon_phase(year, month, day);

    printf("The moon is %s\n", phase);

}


char* get_moon_phase(int year, int month, int day){
    /***
    ** Get a string describing the moon phase for the given date.
    ***/

    int current_phase = moon_phase(year, month, day);

    char *phase[8] = {
        "waxing crescent", 
        "at first quarter",
        "waxing gibbous",
        "full",
        "waning gibbous",
        "at last quarter",
        "waning crescent",
        "new"
    };

    return phase[current_phase];
}


int moon_phase(int year, int month, int day){
    /*******
    ** Calculate a integer to represent the phase of the moon (between 0 to 7).
    **
    ** Phases of the moon (orbits anti-clockwise:
    **
    ** 0. Waxing crescent
    ** 1. First quarter
    ** 2. Waxing gibbous
    ** 3. Full moon
    ** 4. Waning gibbous
    ** 5. Third quarter
    ** 6. Waning crescent
    ** 7. New moon
    **
    ********/

    int d,g,e;

    // define d as the day
    d = day;

    // if the month is 2 add 31 to the day
    if(month == 2){
        d += 31;
    }
    else if(month > 2){
        // otherwise add 59 + (month - 3) x 30.6 + 0.5 ???
        d += 59 + (month - 3) * 30.6 + 0.5;
    }

    // substract 1900 from the year and modulo 19
    g = (year - 1900) % 19;

    // do something else with the year ???
    e = (11 * g + 29) % 30;

    // make sure the e is not 24 or 25 ???
    if(e == 25 || e == 24){
        ++e;
    }

    // return this madness ???
    return ((((e + d) * 6 + 5) % 177) / 22 & 7);
}


