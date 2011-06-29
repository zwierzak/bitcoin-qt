#include "notifiction.h"

Notifiction * Notifiction::instance()
{
    static Notifiction *_instance = NULL;

    if(_instance == NULL)
    {
        _instance = new Notifiction(NULL);
    }

    return _instance;
}

Notifiction::Notifiction(QObject *parent) :
    QObject(parent)
{
    interface = new QDBusInterface("org.freedesktop.Notifications",
                "/org/freedesktop/Notifications", "org.freedesktop.Notifications");
}

unsigned int Notifiction::notify(QString text, QString title, QString icon)
{
    // Arguments for DBus call:
    QList<QVariant> args;

    // Program Name:
    args.append("BitCoin-Qt");

    // Replaces ID:
    args.append(0U);

    // Application Icon, full path
    args.append(icon);

    // Summary
    args.append(title);

    // Body
    args.append(text);

    // Actions
    QStringList actions;
    args.append(actions); // Temporary no actions

    // Hints
    QVariantMap hints;
    args.append(hints); // Temporary no hints

    // Timeout (in msec)
    args.append(10 * 1000); // Hardcoded to 10 sec

    QDBusReply<unsigned int> reply = interface->callWithArgumentList(QDBus::Block, "Notify", args);
    return !reply.isValid()? 0 : reply.value();
}
