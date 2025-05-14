// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (first) {
        Car* current = first->next;
        while (current != first) {
            Car* temp = current;
            current = current->next;
            delete temp;
        }
        delete first;
    }
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    countOp = 0;
    if (!first) return 0;

    Car* current = first;
    int length = 0;
    
    do {
        length++;
        current = current->next;
        countOp++;
    } while (current != first);

    return length;
}

int Train::getOpCount() {
    return countOp;
}
