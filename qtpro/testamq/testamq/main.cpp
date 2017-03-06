#include <QCoreApplication>
#include "activemq.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    activemq::library::ActiveMQCPP::initializeLibrary();
    ActiveMQConsumer  consumer;
    ActiveMQProduce   produce;

    consumer.start("tcp://192.168.0.19:61616?wireFormat.maxInactivityDuration=0", "zhaoTopic", true, false);
    consumer.runConsumer();
    return a.exec();
}
