// #pragma once
// #include "Message.h"
// #include "MsgQueue.cpp"
// #include <pthread.h>
// #include <iostream>
// #include "MsgQueue.cpp"
// #include "carThread.cpp"
// #include "entryDoorThread.cpp"


// using namespace std;

// MsgQueue exitDoorMq;
// pthread_t exitDoor;
// enum
// {
//     ID_EXIT_DOOR_OPEN_REQ = 8,
//     ID_CAR_DRIVE_THROUGH_EXIT_IND = 9
// };


// struct exitDoorOpenReq : public Message
// {
//     MsgQueue* carMq_;
// };

// struct exitDoorOpenCfm : public Message
// {
//     bool result_;
// };

// bool openExitDoor()
// {
//     cout << "Exit door opens" << endl;
//     return true;
// }

// void exitDoorHandleIdEntryDoorReq(exitDoorOpenReq* req)
// {
//     exitDoorOpenCfm* cfm = new exitDoorOpenCfm;
//     cfm->result_ = openExitDoor();

//     req->carMq_->send(ID_EXIT_DOOR_OPEN_CFM, cfm);

// }

// bool closeExitDoor()
// {
//     cout << "Entry door closes" << endl;
// }
// void exitDoorHandleIdCarDriveThroughEntryInd()
// {
//     closeExitDoor();
// }


// void exitDoorHandler(unsigned id, Message* msg)
// {
//     switch(id)
//     {
//         case ID_EXIT_DOOR_OPEN_REQ:
//             exitDoorHandleIdEntryDoorReq(static_cast<exitDoorOpenReq*>(msg));
//             break;
//         case ID_CAR_DRIVE_THROUGH_EXIT_IND:
//             exitDoorHandleIdCarDriveThroughEntryInd();
//             break;
//     }

// }

// void* exitDoorFunction(void* arg)
// {
//     for(;;)
//     {
//         unsigned long id;
//         Message* msg = exitDoorMq.receive(id);
//         exitDoorHandler(id, msg);
//         delete(msg);
//     }
//     return NULL;

// }

// // void startExitThread()
// // {
// //     pthread_create(&exitDoor, NULL, exitDoorFunction, NULL);
// //     pthread_join(exitDoor, NULL);
// // }


