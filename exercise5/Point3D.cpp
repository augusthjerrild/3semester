#include "MsgQueue.h"
#include "Message.h"
#include <unistd.h>

struct Point3D : public Message
{
    int x;
    int y;
    int z;
};

enum
{
    id1,
    id2,
    id3
};

void PointHandler(unsigned int id, Message* msg)
{

    switch(id)
    {
        case id1:
        {
            Point3D* msgPtr = (Point3D*) msg;
            cout << "ID: " << id << "x: " << msgPtr->x << ", " << "y: " << msgPtr->y << ", " << "z: " << msgPtr->z << endl;
            break;
        }
        case id2: 
        {
            Point3D* msgPtr = (Point3D*) msg;
            cout << "ID: " << id << "x: " << msgPtr->x << ", " << "y: " << msgPtr->y << ", " << "z: " << msgPtr->z << endl;
            break;
        }
        case id3: 
        {
            Point3D* msgPtr = (Point3D*) msg;
            cout << "ID: " << id << "x: " << msgPtr->x << ", " << "y: " << msgPtr->y << ", " << "z: " << msgPtr->z << endl;
            break;
        }

    }


}

void* sendFunc(void *arg)
{
    MsgQueue* mq = (MsgQueue*) arg;

    for (;;)
    {
        Point3D* msg1 = new Point3D;
        msg1->x = 1;
        msg1->y = 2;
        msg1->z = 3;
        mq -> send(id1, msg1);
        sleep(1);
        Point3D* msg2 = new Point3D;
        msg2->x = 2;
        msg2->y = 1;
        msg2->z = 4;
        mq -> send(id2, msg2);
        sleep(1);
        Point3D* msg3 = new Point3D;
        msg3->x = 22;
        msg3->y = 1;
        msg3->z = 4;
        mq -> send(id3, msg3);
        sleep(1);
    }   

}

void* receiverFunc(void* arg)
{
    MsgQueue* mq = (MsgQueue*) arg;
    for(;;)
    {
    unsigned long id;
    Message * msg = mq->receive(id);
    PointHandler(id, msg);
    delete(msg);
    }



}



int main()
{
    MsgQueue Point3DQueue(10);

    pthread_t sender, receiver;
    pthread_create(&sender, NULL, sendFunc, (void*) &Point3DQueue);
    pthread_create(&receiver, NULL, receiverFunc, (void*) &Point3DQueue);

    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);




    return 0;
}