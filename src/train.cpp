// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    countOp = 0;
    first = 0;
}

void Train::insertCarriage(bool lightState) {
    Car* carriage = new Car();
    carriage->light = lightState;
    carriage->next = carriage->prev = carriage;

    if (first) {
        carriage->next = first;
        carriage->prev = first->prev;
        first->prev->next = carriage;
        first->prev = carriage;
    } else {
        first = carriage;
    }
}

int Train::calculateSize() {
    if (!first) return 0;
    if (first->next == first) return 1;

    countOp = 1;
    Car* ptr = first;
    int result = 1;

    if (!ptr->light) {
        ptr->light = 1;
        countOp++;
    }

    ptr = ptr->next;
    countOp++;

    while (!ptr->light) {
        ptr = ptr->next;
        countOp += 2;
        result++;
    }

    ptr->light = 0;
    countOp++;

    if (!first->light) {
        return result;
    }

    while (1) {
        ptr = first;
        result = 1;
        countOp++;

        if (!ptr->light) {
            ptr->light = 1;
            countOp++;
        }

        ptr = ptr->next;
        countOp++;

        while (!ptr->light) {
            ptr = ptr->next;
            countOp += 2;
            result++;
        }

        ptr->light = 0;
        countOp++;

        if (!first->light) {
            return result;
        }
    }
}

int Train::operationsCount() {
    return countOp;
}

Train::~Train() {
    if (!first) return;

    Car* current = first->next;
    while (current != first) {
        Car* temporary = current;
        current = current->next;
        delete temporary;
    }
    delete first;
    first = 0;
}
