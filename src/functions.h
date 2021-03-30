// autogenerated by xop-stub-generator.pl from interface.h
#pragma once
#include "XOPStandardHeaders.h" // Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h

XOPIORecResult RegisterFunction();

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_client_connectParams
{
  Handle remotePoint;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_client_connectParams zeromq_client_connectParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_client_recvParams
{
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  Handle result;
};
typedef struct zeromq_client_recvParams zeromq_client_recvParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_client_sendParams
{
  Handle msg;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_client_sendParams zeromq_client_sendParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_handler_startParams
{
  double result;
};
typedef struct zeromq_handler_startParams zeromq_handler_startParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_handler_stopParams
{
  double result;
};
typedef struct zeromq_handler_stopParams zeromq_handler_stopParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_server_bindParams
{
  Handle localPoint;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_server_bindParams zeromq_server_bindParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_server_recvParams
{
  Handle *identity;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  Handle result;
};
typedef struct zeromq_server_recvParams zeromq_server_recvParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_server_sendParams
{
  Handle msg;
  Handle identity;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_server_sendParams zeromq_server_sendParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_setParams
{
  double flags;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_setParams zeromq_setParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_set_logging_templateParams
{
  Handle jsonString;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_set_logging_templateParams
    zeromq_set_logging_templateParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_stopParams
{
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  double result;
};
typedef struct zeromq_stopParams zeromq_stopParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_test_callfunctionParams
{
  Handle msg;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  Handle result;
};
typedef struct zeromq_test_callfunctionParams zeromq_test_callfunctionParams;
#pragma pack()

#pragma pack(2) // All structures passed to Igor are two-byte aligned.
struct zeromq_test_serializeWaveParams
{
  waveHndl wv;
  UserFunctionThreadInfoPtr tp; // needed for thread safe functions
  Handle result;
};
typedef struct zeromq_test_serializeWaveParams zeromq_test_serializeWaveParams;
#pragma pack()

// variable zeromq_client_connect(string remotePoint)
extern "C" int zeromq_client_connect(zeromq_client_connectParams *p);

// string zeromq_client_recv()
extern "C" int zeromq_client_recv(zeromq_client_recvParams *p);

// variable zeromq_client_send(string msg)
extern "C" int zeromq_client_send(zeromq_client_sendParams *p);

// variable zeromq_handler_start()
extern "C" int zeromq_handler_start(zeromq_handler_startParams *p);

// variable zeromq_handler_stop()
extern "C" int zeromq_handler_stop(zeromq_handler_stopParams *p);

// variable zeromq_server_bind(string localPoint)
extern "C" int zeromq_server_bind(zeromq_server_bindParams *p);

// string zeromq_server_recv(string *identity)
extern "C" int zeromq_server_recv(zeromq_server_recvParams *p);

// variable zeromq_server_send(string identity, string msg)
extern "C" int zeromq_server_send(zeromq_server_sendParams *p);

// variable zeromq_set(variable flags)
extern "C" int zeromq_set(zeromq_setParams *p);

// variable zeromq_set_logging_template(string jsonString)
extern "C" int
zeromq_set_logging_template(zeromq_set_logging_templateParams *p);

// variable zeromq_stop()
extern "C" int zeromq_stop(zeromq_stopParams *p);

// string zeromq_test_callfunction(string msg)
extern "C" int zeromq_test_callfunction(zeromq_test_callfunctionParams *p);

// string zeromq_test_serializeWave(WAVE wv)
extern "C" int zeromq_test_serializeWave(zeromq_test_serializeWaveParams *p);
