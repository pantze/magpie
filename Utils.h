#pragma once

// Uncomment for debugging
#define SERIAL_TRACE

#if defined(SERIAL_TRACE)
  #define TRACE0(msg) Serial.printf(msg);
  #define TRACE1(msg, arg1) Serial.printf(msg, arg1);
  #define TRACE2(msg, arg1, arg2) Serial.printf(msg, arg1, arg2);
  #define TRACE3(msg, arg1, arg2, arg3) Serial.printf(msg, arg1, arg2, arg3);
  #define TRACE4(msg, arg1, arg2, arg3, arg4) Serial.printf(msg, arg1, arg2, arg3, arg4);
  #define TRACE5(msg, arg1, arg2, arg3, arg4, arg5) Serial.printf(msg, arg1, arg2, arg3, arg4, arg5);

  #define CALL_TRACE(_1, _2, _3, _4, _5,NAME,...) NAME
  #define TRACE(...) CALL_TRACE(__VA_ARGS__, TRACE5, TRACE4, TRACE3, TRACE2, TRACE0)(__VA_ARGS__)

#else
  #define TRACE(msg)
  #define TRACE1(msg, arg1)
  #define TRACE2(msg, arg1, arg2)
  #define TRACE3(msg, arg1, arg2, arg3)
  #define TRACE4(msg, arg1, arg2, arg3, arg4)
  #define TRACE5(msg, arg1, arg2, arg3, arg4, arg5)
  
  #define CALL_TRACE(_1, _2, _3, _4, _5,NAME,...) NAME
  #define TRACE(...) CALL_TRACE(__VA_ARGS__, TRACE5, TRACE4, TRACE3, TRACE2, TRACE0)(__VA_ARGS__)
#endif

#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define FOO(...) GET_MACRO(__VA_ARGS__, FOO3, FOO2)(__VA_ARGS__)