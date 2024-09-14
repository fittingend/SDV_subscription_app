#ifndef __API_RCURTAIN_LOCAL_HPP__
#define __API_RCURTAIN_LOCAL_HPP__

#include <Common.h>
#include <SoaDataType.h>

extern void Api_Rcurtain_Init(void);
extern void Api_Rcurtain_Term(void);
extern int Api_Rcurtain_Method_RequestRearCurtainOperation(RCtnSwitch_e eDirection);
extern int Api_Rcurtain_Method_RequestRearCurtainPosition(int percentage);
extern void Api_Rcurtain_Field_SoaRctnStatus();

#endif