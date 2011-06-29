#ifndef NOTIFICTION_H
#define NOTIFICTION_H

#include <QObject>
#include <QtDBus/QtDBus>

/**
  *
  */
class Notifiction : public QObject
{
    Q_OBJECT
public:
    static Notifiction* instance();


signals:

public slots:
    unsigned int notify(QString text, QString title = QLatin1String("BitCoin-Qt"), QString icon = QString());

protected:
    Notifiction(QObject *parent);

    QDBusInterface *interface;

};

#endif // NOTIFICTION_H
