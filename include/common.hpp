
#define Fevo_check_eq(e1, e2)\
{\
  if(e1 != e2) {\
    printf("ERROR: %s:%d,",__FILE__,__LINE__);\
    throw std::runtime_error("Fevo_check_eq failed: " #e1 " != " #e2);\
  }\
}