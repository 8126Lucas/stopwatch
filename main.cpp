#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <vector>


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
    cout << running->milliseconds;
}

void printStopwatch(tempo_t *running) {
    printTime(running);
    cout << endl;
}

void printFlags(vector<tempo_t> *flags) {
    cout << "\n\nFlags: ";
    for(int i = 0; i < flags->size(); i++) {
        cout << "| " << i+1 << ". ";
        printTime(&flags->at(i));
        cout << "\t";
    }
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

void markFlag(tempo_t *running, vector<tempo_t> *flags) {
    flags->push_back(*running);
}

void checkHit(tempo_t *running, vector<tempo_t> *flags) {
    char hit = '\0';
    if(_kbhit()) {
        hit = _getch();
    }
    if(hit == 's' || hit == 'S') {
        pause();
    }
    else if(hit == 'f' || hit == 'F') {
        markFlag(running, flags);
    }
    else if(hit == 'o' || hit == 'O') {
        printFlags(flags); 
        exit(0);
    }
}

void run(tempo_t *running) {
    this_thread::sleep_for(chrono::milliseconds(100));
    increaseTime(running);
    printStopwatch(running);
}

int main() {
    tempo_t running = {0, 0, 0};
    vector<tempo_t> flags;
    while(1) {
        run(&running);
        checkHit(&running, &flags);
    }

}