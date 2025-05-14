// Copyright 2021 NNTU-CS
#include "train.h"

const int ZERO_INIT = 0;
const int UNIT_VALUE = 1;
const int DOUBLE_STEP = 2;

Train::Train() {
    first = nullptr;
    countOp = ZERO_INIT;
}

void Train::addCar(bool bulb_state) {
    Car* new_node = new Car();
    new_node->light = bulb_state;
    new_node->next = new_node;
    new_node->prev = new_node;

    if (first != nullptr) {
        new_node->next = first;
        new_node->prev = first->prev;
        first->prev->next = new_node;
        first->prev = new_node;
    } else {
        first = new_node;
    }
}

static int processUnits(Car* start, int& counter) {
    Car* current = start->next;
    int units = UNIT_VALUE;
    counter += UNIT_VALUE;

    while (current->light == false) {
        current = current->next;
        counter += DOUBLE_STEP;
        units++;
    }
    current->light = false;
    counter++;
    return units;
}

int Train::getLength() {
    if (first == nullptr) return ZERO_INIT;
    if (first->next == first) return UNIT_VALUE;

    countOp = UNIT_VALUE;
    first->light = true;
    countOp++;

    int result = processUnits(first, countOp);
    if (first->light == false) return result;

    while (true) {
        countOp++;
        first->light = true;
        countOp++;
        result = processUnits(first, countOp);
        if (first->light == false) break;
    }
    return result;
}

int Train::getOpCount() {
    return countOp;
}

Train::~Train() {
    if (first == nullptr) return;

    Car* current = first->next;
    while (current != first) {
        Car* next = current->next;
        delete current;
        current = next;
    }
    delete first;
}
