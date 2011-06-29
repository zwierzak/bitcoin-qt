#ifndef NOTIFICTION_H
#define NOTIFICTION_H

#include <QObject>
#include <QtGui/QSystemTrayIcon>

#ifdef QT_DBUS
# include <QtDBus/QtDBus>
#endif

/**
  *
  */
class Notifiction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout)
public:
    static Notifiction* instance(QSystemTrayIcon *tray = NULL);

    int timeout();

signals:

public slots:
    unsigned int notify(QString text, QString title = QLatin1String("BitCoin-Qt"), QString icon = QString());

    void setTimeout(int timeout);

protected:
    Notifiction(QObject *parent, QSystemTrayIcon *tray = NULL);

    QDBusInterface *interface;
    QSystemTrayIcon *tray;

    int m_timeout;

    enum Notifier {
        UnknowNotifier = 0,
#ifdef QT_DBUS
        FreeDesktopNotifier = 10,
#endif
        QSystemTrayNotifier = 11,
        MessageBoxNotifier = 12 //< QMessageBox, use never!
    } notifier;

};

#endif // NOTIFICTION_H
