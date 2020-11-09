// #pragma once
// #include "Message.h"
// #include "MsgQueue.cpp"
// #include <pthread.h>
// #include <iostream>
// #include "MsgQueue.cpp"
// #include "carThread.cpp"

// using namespace std;


// MsgQueue entryDoorMq;
// pthread_t entryDoor;

// enum
// {
// ID_ENTRY_DOOR_OPEN_REQ = 5,
// ID_CAR_DRIVE_THROUGH_ENTRY_IND = 6,
// };

// struct entryDoorOpenReq : public Message
// {
//     MsgQueue* carMq_;
// };

// struct entryDoorOpenCfm : public Message
// {
//     bool result_;
// };

// bool openEntryDoor()
// {
//     cout << "Entry door opens" << endl;
//     return true;
// }

// void entryDoorHandleIdEntryDoorReq(entryDoorOpenReq* req)
// {
//     entryDoorOpenCfm* cfm = new entryDoorOpenCfm;
//     cfm->result_ = openEntryDoor();
 
//     cout << "Car drives in" << endl;
//     req->carMq_->send(ID_ENTRY_DOOR_OPEN_CFM, cfm);
// }

// bool closeEntryDoor()
// {
//     cout << "Entry door closes" << endl;
//     return true;
// }
// void entryDoorHandleIdCarDriveThroughEntryInd()
// {
//     closeEntryDoor();
// }


// void entryDoorHandler(unsigned id, Message* msg)
// {
//     switch(id)
//     {
//         case ID_ENTRY_DOOR_OPEN_REQ:
//             entryDoorHandleIdEntryDoorReq(static_cast<entryDoorOpenReq*>(msg));
//             break;
//         case ID_CAR_DRIVE_THROUGH_ENTRY_IND:
//             entryDoorHandleIdCarDriveThroughEntryInd();
//             break;
//     }

// }

// void* entryDoorFunction(void* arg)
// {
//     for(;;)
//     {
//         unsigned long id;
//         Message* msg = entryDoorMq.receive(id);
//         entryDoorHandler(id, msg);
//         delete(msg);
//     }

// return NULL;
// }

// void startEntryThread()
// {
//     pthread_create(&entryDoor, NULL, entryDoorFunction, NULL);
//     pthread_join(entryDoor, NULL);
// }
