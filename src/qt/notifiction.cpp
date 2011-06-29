#include <QtGui/QMessageBox>

#include "notifiction.h"

Notifiction * Notifiction::instance(QSystemTrayIcon *tray)
{
    static Notifiction *_instance = NULL;

    if(_instance == NULL)
    {
        _instance = new Notifiction(NULL);
    }

    return _instance;
}

Notifiction::Notifiction(QObject *parent, QSystemTrayIcon *tray) :
    QObject(parent), m_timeout(10*1000)
{
    interface = new QDBusInterface("org.freedesktop.Notifications",
                "/org/freedesktop/Notifications", "org.freedesktop.Notifications");

#ifdef QT_DBUS
    if(interface->isValid())
    {
        notifier = FreeDesktopNotifier;
    }
    else
#endif
    if(tray != NULL && tray->supportsMessages())
    {
        notifier = QSystemTrayNotifier;
    }
    else
    {
        notifier = UnknowNotifier;
    }
}

unsigned int Notifiction::notify(QString text, QString title, QString icon)
{
#ifdef QT_DBUS
    if( notifier == FreeDesktopNotifier )
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
        args.append(m_timeout);

        QDBusReply<unsigned int> reply = interface->callWithArgumentList(QDBus::Block, "Notify", args);
        return !reply.isValid()? 0 : reply.value();
    }
    else
#endif
    if( notifier == QSystemTrayNotifier )
    {
        tray->showMessage(title, text, QSystemTrayIcon::NoIcon, m_timeout);
    }
    else if( notifier == MessageBoxNotifier )
    {
        QMessageBox::information(NULL, title, text, QMessageBox::Ok);
    }

    return 0;
}

int Notifiction::timeout()
{
    return m_timeout;
}

void Notifiction::setTimeout(int timeout)
{
    m_timeout = timeout;
}
