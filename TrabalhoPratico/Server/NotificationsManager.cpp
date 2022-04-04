#include "NotificationsManager.hpp"

void NotificationsManager::registerReceivedNotification(Profile* profile, string message) {

    Notification newNotification(profile->getUserName(), getDateTime(), message);
    newNotification.setPending(profile->getFollowersSize());

    profile->pushToReceivedByServer(newNotification);

    pushNotificationToFollowers(profile, &newNotification);

    cout << "Notification registered:" << endl;
    cout << newNotification.print() << endl;

}

// Itera pela lista de seguidores do profile e adiciona a notification na
// fila toBeSent de cada um
void NotificationsManager::pushNotificationToFollowers(Profile* profile, Notification* notification) {

    list<Profile*> followers = profile->getFollowers();
    for (auto prof = followers.begin(); prof != followers.end(); ++prof) {
        (*prof)->pushToBeSent(*notification);
        (*prof)->printToBeSent();
    }

}

string NotificationsManager::getDateTime() {

    time_t t = time(nullptr);
    char dateTime[100];
    locale::global(locale("pt_BR.utf8"));
    strftime(dateTime, sizeof(dateTime), "%c", localtime(&t));

    return dateTime;

}
