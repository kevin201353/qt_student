#include "activemq.h"
#include <QDebug>

ActiveMQProduce::ActiveMQProduce()
{

}

ActiveMQProduce::~ActiveMQProduce()
{
    delete bytesMessage;
    cleanup();
}

void ActiveMQProduce::start( const std::string& brokerURI, unsigned int numMessages, const std::string& destURI, bool useTopic, bool clientAck)
{
    this->connection = NULL;
    this->session = NULL;
    this->destination = NULL;
    this->producer = NULL;
    this->numMessages = numMessages;
    this->useTopic = useTopic;
    this->brokerURI = brokerURI;
    this->destURI = destURI;
    this->clientAck = clientAck;

    initialize();
}

void ActiveMQProduce::initialize()
{
    try {
        // Create a ConnectionFactory
        auto_ptr<ActiveMQConnectionFactory> connectionFactory(new ActiveMQConnectionFactory( brokerURI ) );

        // Create a Connection
        try{
            connection = connectionFactory->createConnection();
            connection->start();
        } catch( CMSException& e )
        {
            e.printStackTrace();
            throw e;
        }

        // Create a Session
        if( clientAck ) {
            session = connection->createSession( Session::CLIENT_ACKNOWLEDGE );
        } else {
            session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
        }

        // Create the destination (Topic or Queue)
        if( useTopic ) {
            destination = session->createTopic( destURI );
        } else {
            destination = session->createQueue( destURI );
        }

        // Create a MessageProducer from the Session to the Topic or Queue
        producer = session->createProducer( destination );
        producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
    }catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}


void ActiveMQProduce::send(const char* Message,int nSize)
{
    // 消息内容
 //      std::string threadIdStr = Long::toString( Thread::getId() );
    // 创建一个文本类型的消息
    bytesMessage = session->createBytesMessage((unsigned char*)Message,nSize);
    // 发送消息
      // printf( "Sent message  from thread %s\n", threadIdStr.c_str() );
    producer->send(bytesMessage );
}


void ActiveMQProduce::cleanup()
{
    // Destroy resources.
    try{
        if( destination != NULL )
            delete destination;
    }catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    destination = NULL;

    try{
        if( producer != NULL )
            delete producer;
    }catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    producer = NULL;

    // Close open resources.
    try{
        if( session != NULL )
            session->close();
        if( connection != NULL )
            connection->close();
    }catch ( CMSException& e )
    {
        e.printStackTrace();
    }

    try{
        if( session != NULL )
            delete session;
    }catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    session = NULL;

    try{
        if( connection != NULL )
            delete connection;
    }catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    connection = NULL;
}



//////////////////////////////////////////////////////////////////////////////////////

ActiveMQConsumer::ActiveMQConsumer()
{

}
ActiveMQConsumer::~ActiveMQConsumer()
{
    cleanup();
}

void ActiveMQConsumer::close()
{
    cleanup();
}

void ActiveMQConsumer::runConsumer()
{
    try {
        // Create a ConnectionFactory
        ActiveMQConnectionFactory* connectionFactory = new ActiveMQConnectionFactory( brokerURI );

        // Create a Connection
        connection = connectionFactory->createConnection();
        delete connectionFactory;

       // ActiveMQConnection* amqConnection = dynamic_cast<ActiveMQConnection*>(connection);
        ActiveMQConnection *amqConnection = (ActiveMQConnection *)connection;
        if( amqConnection != NULL )
        {
 //           amqConnection->addTransportListener((TransportListener*)this);
           // amqConnection->add
        }
        connection->start();
        connection->setExceptionListener(this);
        // Create a Session
        if( clientAck )
        {
            session = connection->createSession( Session::CLIENT_ACKNOWLEDGE );
        }
        else
        {
            session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
        }

        // Create the destination (Topic or Queue)
        if( useTopic )
        {
            destination = session->createTopic( destURI );
        }
        else
        {
            destination = session->createQueue( destURI );
        }

        // Create a MessageConsumer from the Session to the Topic or Queue
        consumer = session->createConsumer( destination );
        producer = session->createProducer(destination);
        consumer->setMessageListener( this );

    } catch (CMSException& e)
    {
        e.printStackTrace();
    }
}

// Called from the consumer since this class is a registered MessageListener.
void ActiveMQConsumer::onMessage( const Message* message )
{
    static int count = 0;
    try
    {
        count++;
//        const BytesMessage* bytesMessage = dynamic_cast< const BytesMessage* >( message );
//        string text;
//        if( bytesMessage != NULL )
//        {
//            text.assign((char *)(bytesMessage->getBodyBytes()),(bytesMessage->getBodyLength()));
//        }
//        else
//        {
//            text = "NOT A BYTESMESSAGE!";
//        }
        const TextMessage *txtMsg = dynamic_cast<const TextMessage*>(message);
        if (txtMsg != NULL) {
            std::string body = txtMsg->getText();
            char sztmp[100] = {0};
            sprintf(sztmp, "Message #%d Received: %s\n", count, body.c_str());
            qDebug() << QString(sztmp);
        }
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}


void ActiveMQConsumer::onException( const CMSException& ex AMQCPP_UNUSED )
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    //to here, network inter
    ex.printStackTrace();
    exit(1);
}

void ActiveMQConsumer::transportInterrupted()
{
    std::cout << "The Connection's Transport has been Interrupted." << std::endl;
}

void ActiveMQConsumer::transportResumed()
{
    std::cout << "The Connection's Transport has been Restored." << std::endl;
}



void ActiveMQConsumer::cleanup(){

    //*************************************************
    // Always close destination, consumers and producers before
    // you destroy their sessions and connection.
    //*************************************************

    // Destroy resources.
    try{
        if( destination != NULL )
            delete destination;
    }catch (CMSException& e)
    {

    }
    destination = NULL;

    try{
        if( consumer != NULL )
            delete consumer;
    }catch (CMSException& e)
    {

    }
    consumer = NULL;

    // Close open resources.
    try{
        if( session != NULL )
            session->close();
        if( connection != NULL )
            connection->close();
    }catch (CMSException& e)
    {

    }

    // Now Destroy them
    try{
        if( session != NULL )
            delete session;
    }catch (CMSException& e)
    {

    }
    session = NULL;

    try{
        if( connection != NULL )
            delete connection;
    }catch (CMSException& e)
    {

    }
    connection = NULL;
}

void ActiveMQConsumer::start( const std::string& brokerURI,const std::string& destURI,bool useTopic = false,bool clientAck = false )
{
    this->connection = NULL;
    this->session = NULL;
    this->destination = NULL;
    this->consumer = NULL;
    this->useTopic = useTopic;
    this->brokerURI = brokerURI;
    this->destURI = destURI;
    this->clientAck = clientAck;
}
