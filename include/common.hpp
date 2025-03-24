#include <stdio.h>
#define Fevo_check_eq(e1, e2)\
{\
  if(e1 != e2) {\
    printf("ERROR: %s:%d, ",__FILE__,__LINE__);\
    fflush(stdout);\
    throw std::runtime_error("Fevo_check_eq failed: " #e1 " != " #e2);\
  }\
}

#define Fevo_check_empty(e)\
{\
  if(e.empty()) {\
    printf("ERROR: %s:%d, ",__FILE__,__LINE__);\
    fflush(stdout);\
    throw std::runtime_error("Fevo_check_empty failed: " #e " is empty");\
  }\
}
