#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>


using namespace std;

typedef struct tempo {
    int minutes;
    int seconds;
    int milliseconds;
} tempo_t;

void printTime(tempo_t *running) {
    if(running->minutes < 10) {cout << "0" << running->minutes << ":";}
    else {cout << running->minutes << ":";}
    if(running->seconds < 10) {cout << "0" << running->seconds << ".";}
    else {cout << running->seconds << ".";}
    cout << running->milliseconds << endl;
}

void checkMilliseconds(tempo_t *running) {
    while(running->milliseconds > 9) {
        running->seconds++;
        running->milliseconds -= 10;
    }
}

void checkSeconds(tempo_t *running) {
    while(running->seconds > 59) {
        running->minutes++;
        running->seconds -= 60;
    }
}

void increaseTime(tempo_t *running) {
    running->milliseconds++;
    checkMilliseconds(running);
    checkSeconds(running);
}

void pause() {
    while(!_kbhit()){}
    _getch();
}

void checkPause() {
    if(_kbhit()) {
        _getch();
        pause();
    }
}

void run(tempo_t *running) {
    this_thread::sleep_for(chrono::milliseconds(100));
    increaseTime(running);
    printTime(running);
}

int main() {
    tempo_t running = {0, 0, 0};
    while(1) {
        run(&running);
        checkPause();
    }
}