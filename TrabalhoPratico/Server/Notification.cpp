#include "Notification.hpp"

Notification::Notification(string username, string timestamp, string message) {

    this->username = username;
    this->timestamp = timestamp;
    this->message = message;
    this->pending = 0;

}

string Notification::getUsername() {
    return this->username;
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

void Notification::setPending(int pend) {
    this->pending = pend;
}

string Notification::print() {
    return username + " (" + timestamp + "): " + message;
}
