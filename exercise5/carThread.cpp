#pragma once
#include "Message.h"
#include <pthread.h>
#include <iostream>
#include "MsgQueue.cpp"
#include "unistd.h"

using namespace std;

//Car 
MsgQueue carMq(10);
pthread_t car;

//Entry
MsgQueue entryDoorMq(1);
pthread_t entryDoor;

//Exit door
MsgQueue exitDoorMq(1);
pthread_t exitDoor;

enum
{
    //CARS håndteringer
ID_ENTRY_DOOR_OPEN_CFM = 1,
ID_EXIT_DOOR_OPEN_CFM = 2,
ID_START_IND = 3,
    //EntryDoors håndteringer
ID_ENTRY_DOOR_OPEN_REQ = 5,
ID_CAR_DRIVE_THROUGH_ENTRY_IND = 6,
    //Exit doors håndteringer
ID_EXIT_DOOR_OPEN_REQ = 8,
ID_CAR_DRIVE_THROUGH_EXIT_IND = 9
};


struct entryDoorOpenReq : public Message
{
    MsgQueue* carMq_;

};

struct entryDoorOpenCfm : public Message
{
    bool result_;
};

struct exitDoorOpenReq : public Message
{
    MsgQueue* carMq_;

};

struct exitDoorOpenCfm : public Message
{
    bool result_;
};


// CAR IMPLEMENTERING
struct Car
{
    int carID;
};

void driveThroughEntry()
{
    cout << "Car drives into parking lot" << endl;
    //HER SKAL SKRIVES KODE TIL AT KØRE IND
}

void driveThroughExit()
{
    cout << "Car drives out of parking lot" << endl;
    //HER SKAL SKRIVES KODE TIL AT KØRE UD
}


void Park()
{
    cout << "Car parks for 3 sec" << endl;
    sleep(3);
    //HER SKAL SKRIVES KODE TIL AT PARKERE

    exitDoorOpenReq* req = new exitDoorOpenReq;
    cout << "Car request exit" << endl;
    req->carMq_ = &carMq;
    exitDoorMq.send(ID_EXIT_DOOR_OPEN_REQ, req);
}

void carHandleIdEntryDoorCfm(entryDoorOpenCfm* cfm)
{
    if(cfm->result_)
    {
        driveThroughEntry();
    }
    Park();
}

void carHandleIdExitDoorCfm(exitDoorOpenCfm *cfm)
{
    if(cfm->result_)
    {
        driveThroughExit();
    }

}

void carHandleIdStartInd()
{
    entryDoorOpenReq* req = new entryDoorOpenReq;
    req->carMq_ = &carMq;

    cout << "Car request entry" << endl;
    entryDoorMq.send(ID_ENTRY_DOOR_OPEN_REQ, req);
}


void carHandler(unsigned int id, Message *msg)
{
    switch(id)
    {
        case ID_START_IND:
            carHandleIdStartInd();
            break;
        case ID_ENTRY_DOOR_OPEN_CFM:
            carHandleIdEntryDoorCfm(static_cast<entryDoorOpenCfm*>(msg));
             break;
        case ID_EXIT_DOOR_OPEN_CFM:
            carHandleIdExitDoorCfm(static_cast<exitDoorOpenCfm*>(msg));
            break;
    }      
}

void* carFunction(void* arg)
{
// MsgQueue* carID = (MsgQueue*) arg; //HVORDAN FÅR JEG ID MED

for(;;)
{
    unsigned long id;
    Message* msg = carMq.receive(id);
    carHandler(id, msg);
    delete msg;
}

}


//ENTRY DOOR IMPLEMENTERING
bool openEntryDoor()
{
    cout << "Entry door opens" << endl;
    return true;
}

void entryDoorHandleIdEntryDoorReq(entryDoorOpenReq* req)
{
    entryDoorOpenCfm* cfm = new entryDoorOpenCfm;
    cfm->result_ = openEntryDoor();
 
    cout << "Car drives in" << endl;
    req->carMq_->send(ID_ENTRY_DOOR_OPEN_CFM, cfm);
}

bool closeEntryDoor()
{
    cout << "Entry door closes" << endl;
    return true;
}
void entryDoorHandleIdCarDriveThroughEntryInd()
{
    closeEntryDoor();
}


void entryDoorHandler(unsigned id, Message* msg)
{
    switch(id)
    {
        case ID_ENTRY_DOOR_OPEN_REQ:
            entryDoorHandleIdEntryDoorReq(static_cast<entryDoorOpenReq*>(msg));
            break;
        case ID_CAR_DRIVE_THROUGH_ENTRY_IND:
            entryDoorHandleIdCarDriveThroughEntryInd();
            break;
    }

}

void* entryDoorFunction(void* arg)
{
    for(;;)
    {
        unsigned long id;
        Message* msg = entryDoorMq.receive(id);
        entryDoorHandler(id, msg);
        delete(msg);
    }

return NULL;
}


//EXIT DOOR IMPLEMENTERING
bool openExitDoor()
{
    cout << "Exit door opens" << endl;
    return true;
}

void exitDoorHandleIdEntryDoorReq(exitDoorOpenReq* req)
{
    exitDoorOpenCfm* cfm = new exitDoorOpenCfm;
    cfm->result_ = openExitDoor();

    req->carMq_->send(ID_EXIT_DOOR_OPEN_CFM, cfm);

}

bool closeExitDoor()
{
    cout << "Entry door closes" << endl;
    return true;
}
void exitDoorHandleIdCarDriveThroughEntryInd()
{
    closeExitDoor();
}


void exitDoorHandler(unsigned id, Message* msg)
{
    switch(id)
    {
        case ID_EXIT_DOOR_OPEN_REQ:
            exitDoorHandleIdEntryDoorReq(static_cast<exitDoorOpenReq*>(msg));
            break;
        case ID_CAR_DRIVE_THROUGH_EXIT_IND:
            exitDoorHandleIdCarDriveThroughEntryInd();
            break;
    }

}

void* exitDoorFunction(void* arg)
{
    for(;;)
    {
        unsigned long id;
        Message* msg = exitDoorMq.receive(id);
        exitDoorHandler(id, msg);
        delete(msg);
    }
    return NULL;

}


void startCarThread()
{

    // unsigned int numberOfCars;
    // cout << "How many cars do u want?" << endl;
    // cin >> numberOfCars;
    // numberOfCars = numberOfCars > 0 ? numberOfCars-1 : 1;
    // pthread_t car[numberOfCars];
    // Car info[numberOfCars];
    // for (size_t i = 0; i <= numberOfCars; i++)
    // {
    //     Car* carPtr = &info[i];
    //     carPtr->carID = i+1;
        pthread_create(&car, NULL, carFunction, NULL);
        pthread_join(car, NULL);

        pthread_create(&entryDoor, NULL, entryDoorFunction, NULL);
        pthread_join(entryDoor, NULL);

        pthread_create(&exitDoor, NULL, exitDoorFunction, NULL);
        pthread_join(exitDoor, NULL);
    
        carMq.send(ID_START_IND);
    //}
    
}