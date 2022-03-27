#include "Notification.hpp"

Notification::Notification(int uuid, int timestamp, string message) {

    this->uuid = uuid;
    this->timestamp = timestamp;
    this->message = message;
    this->pending = 0;

}

int Notification::getUuid() {
    return this->uuid;
}

int Notification::getTimestamp() {
    return this->timestamp;
}

string Notification::getMessage() {
    return this->message;
}

int Notification::getPending() {
    return this->pending;
}

void Notification::incrementPending() {
    this->pending++;
}

void Notification::decrementPending() {
    this->pending--;
}