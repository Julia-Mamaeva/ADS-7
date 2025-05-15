// Copyright 2021 NNTU-CS
#include "train.h"

constexpr int BASE_COUNT = 0;
constexpr int UNIT_COUNT = 1;
constexpr int DOUBLE_INCREMENT = 2;

Train::Train() {
    first = nullptr;
    countOp = BASE_COUNT;
}

void Train::addCar(bool light) {
    Car* fresh_node = new Car();
    fresh_node->light = light;
    fresh_node->next = fresh_node;
    fresh_node->prev = fresh_node;

    if (first) {
        fresh_node->prev = first->prev;
        fresh_node->next = first;
        first->prev->next = fresh_node;
        first->prev = fresh_node;
    } else {
        first = fresh_node;
    }
}

int Train::getLength() {
    if (!first) return BASE_COUNT;
    if (first->next == first) return UNIT_COUNT;

    countOp = UNIT_COUNT;
    Car* tracker = first;
    tracker->light = true;
    countOp++;

    int detected = UNIT_COUNT;
    tracker = tracker->next;
    countOp++;

    while (true) {
        while (!tracker->light) {
            tracker = tracker->next;
            countOp += DOUBLE_INCREMENT;
            detected++;
        }

        tracker->light = false;
        countOp++;

        if (tracker == first) {
            if (!first->light) return detected;
            break;
        }
    }

    while (true) {
        detected = UNIT_COUNT;
        first->light = true;
        countOp += DOUBLE_INCREMENT;

        tracker = first->next;
        countOp++;

        while (!tracker->light) {
            tracker = tracker->next;
            countOp += DOUBLE_INCREMENT;
            detected++;
        }

        tracker->light = false;
        countOp++;

        if (!first->light) return detected;
    }
}

int Train::getOpCount() {
    return countOp;
}

Train::~Train() {
    if (!first) return;

    Car* current = first->next;
    while (current != first) {
        Car* next_node = current->next;
        delete current;
        current = next_node;
    }
    delete first;
    first = nullptr;
}
