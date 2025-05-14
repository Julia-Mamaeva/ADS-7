// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : operationsCounter(0), entryCar(nullptr) {}

Train::~Train() {
    if (entryCar) {
        Car* currentCar = entryCar->nextCar;
        while (currentCar != entryCar) {
            Car* tempCar = currentCar;
            currentCar = currentCar->nextCar;
            delete tempCar;
        }
        delete entryCar;
    }
}

void Train::addCar(bool bulbState) {
    Car* newCar = new Car{bulbState, nullptr, nullptr};
    if (!entryCar) {
        entryCar = newCar;
        newCar->nextCar = newCar;
        newCar->prevCar = newCar;
    } else {
        Car* lastCar = entryCar->prevCar;
        lastCar->nextCar = newCar;
        newCar->prevCar = lastCar;
        newCar->nextCar = entryCar;
        entryCar->prevCar = newCar;
    }
}

int Train::getLength() {
    operationsCounter = 0;
    if (!entryCar) return 0;

    Car* currentPosition = entryCar;
    if (!currentPosition->bulbState) {
        currentPosition->bulbState = true;
    }

    int totalCars = 1;
    bool moveForward = true;

    while (true) {
        Car* nextPosition = moveForward ? 
            currentPosition->nextCar : currentPosition->prevCar;
        operationsCounter++;

        if (nextPosition->bulbState) {
            nextPosition->bulbState = false;
            totalCars++;
            currentPosition = nextPosition;
        } else {
            moveForward = !moveForward;
        }

        if (nextPosition == entryCar) {
            if (!entryCar->bulbState) {
                return totalCars;
            }
        }
    }
}

int Train::getOpCount() const {
    return operationsCounter;
}
