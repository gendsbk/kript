%module arifm
%{
/* Includes the header in the wrapper code */
#include "arifm.h"
%}

/* Parse the header file to generate wrappers */
%include "arifm.h"
