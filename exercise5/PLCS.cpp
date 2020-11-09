// #pragma once
// #include "Message.h"
// #include <pthread.h>
// #include <iostream>
// #include "MsgQueue.cpp"

// using namespace std;

// enum
// {

// ID_ENTRY_DOOR_OPEN_REQ = 0,
// ID_ENTRY_DOOR_OPEN_CFM = 1,
// ID_EXIT_DOOR_OPEN_REQ = 2,
// ID_EXIT_DOOR_OPEN_CFM = 3,
// ID_CAR_ENTRY_CFM = 4,
// ID_CAR_EXIT_CFM = 5,
// };

// struct Car
// {
//     int id;
//     MsgQueue* carMq;
// };

// struct entryDoorOpenReq : public Message
// {
//     MsgQueue* carMq;

// };

// struct entryDoorOpenCfm : public Message
// {
//     MsgQueue* carMq;

// };

// struct exitDoorOpenReq : public Message
// {
//     MsgQueue* carMq;

// };

// struct exitDoorOpenCfm : public Message
// {
//     MsgQueue* carMq;

// };

// void* carFunction(void* arg)
// {
// /* Initialization code, if needed */
// for(;;)
// {
//     unsigned long id;
//     Message* msg = mq.receive(id);
//     handleMsg(msg, id);
//     delete msg;
// }

//  /* Clean up, if needed */
// }

// void* exitFunction(void* arg)
// {
// /* Initialization code, if needed */
// for(;;)
// {
//     unsigned long id;
//     Message* msg = mq.receive(id);
//     handleMsg(msg, id);
//     delete msg;
// }

//  /* Clean up, if needed */
// }

// void* entryFunction(void* arg)
// {
// /* Initialization code, if needed */
// for(;;)
// {
//     unsigned long id;
//     Message* msg = mq.receive(id);
//     handleMsg(msg, id);
//     delete msg;
// }

//  /* Clean up, if needed */
// }









// int main()
// {
//     MsgQueue entryMq(10);
//     MsgQueue exitMq(10);

//     pthread_t exitGuard, entryGuard;
//     unsigned int numberOfCars;
//     cout << "How many cars do u want?" << endl;
//     cin >> numberOfCars;

//     numberOfCars = numberOfCars > 0 ? numberOfCars-1 : 1;
    
//     pthread_t car[numberOfCars];
//     Car info[numberOfCars];
//     for (size_t i = 0; i <= numberOfCars; i++)
//     {
//         Car* carPtr = &info[i];
//         carPtr->id = i+1;
//        pthread_create(&car[i], NULL, carFunction, (void*) carPtr);
//     }
//     for (size_t i = 0; i <= numberOfCars; i++)
//     {
//         pthread_join(car[i], NULL);
//     }
    

//     pthread_create(&exitGuard, NULL, entryFunction, NULL);
//     pthread_create(&entryGuard, NULL, exitFunction, NULL);

//     pthread_join(entryFunction, NULL);
//     pthread_join(exitFunction, NULL);
    
//     return 0;
// }