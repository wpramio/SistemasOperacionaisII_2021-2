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

    time_t _tm =time(NULL );
    struct tm * curtime = localtime ( &_tm );

    return asctime(curtime);

}
