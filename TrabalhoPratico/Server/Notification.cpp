#include "Notification.hpp"

Notification::Notification(string user, string timestamp, string message) {

    this->user = user;
    this->timestamp = timestamp;
    this->message = message;
    this->pending = 0;

}

string Notification::getUser() {
    return this->user;
}

string Notification::getTimestamp() {
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