#ifndef FRIEND_H
#define FRIEND_H

#include <QString>

class Friend {
public:
    QString name;
    QString avatarPath;

    Friend(const QString& name, const QString& avatarPath)
        : name(name), avatarPath(avatarPath) {}
};


#endif // FRIEND_H
