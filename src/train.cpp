// Copyright 2021 NNTU-CS
#include "train.h"

#define INIT_COUNT 0
#define NULL_PTR 0

Train::Train() noexcept {
    this->first = NULL_PTR;
    this->countOp = INIT_COUNT;
}

void Train::addCar(bool light) {
    Car* new_node = new Car{light, nullptr, nullptr};
    
    if (!first) {
        new_node->next = new_node->prev = new_node;
        first = new_node;
        return;
    }
    
    new_node->prev = first->prev;
    new_node->next = first;
    first->prev->next = new_node;
    first->prev = new_node;
}

namespace {
    constexpr int SINGLE_UNIT = 1;
    constexpr int COUNT_STEP = 2;
}

int Train::getLength() {
    if (this->first == NULL_PTR) return INIT_COUNT;
    if (this->first->next == this->first) return SINGLE_UNIT;

    this->countOp = SINGLE_UNIT;
    Car* current_unit = this->first;
    int units_found = SINGLE_UNIT;

    if (current_unit->light == false) {
        current_unit->light = true;
        this->countOp++;
    }

    current_unit = current_unit->next;
    this->countOp++;

    auto process_units = [&]() {
        while (current_unit->light == false) {
            current_unit = current_unit->next;
            this->countOp += COUNT_STEP;
            units_found++;
        }
        current_unit->light = false;
        this->countOp++;
    };

    process_units();

    if (this->first->light == false) {
        return units_found;
    }

    for (;;) {
        current_unit = this->first;
        units_found = SINGLE_UNIT;
        this->countOp++;

        if (current_unit->light == false) {
            current_unit->light = true;
            this->countOp++;
        }

        current_unit = current_unit->next;
        this->countOp++;

        process_units();

        if (this->first->light == false) {
            return units_found;
        }
    }
}

int Train::getOpCount() const noexcept {
    return this->countOp;
}

Train::~Train() {
    if (this->first == NULL_PTR) return;

    Car* unit_to_delete = this->first->next;
    while (unit_to_delete != this->first) {
        Car* next_unit = unit_to_delete->next;
        delete unit_to_delete;
        unit_to_delete = next_unit;
    }
    delete this->first;
    this->first = NULL_PTR;
}
