#ifndef TERMINALCONFIG_H
#define TERMINALCONFIG_H

#include "mylable.h"

class TerminalConfig
{
public:
    TerminalConfig();
    void SetppMyLabel(myLable  **mylabel);
    void SetUPHand(bool flag);
    void SetLabelNum(int num);
private:
    myLable  **m_ppMyLabel;
    int m_iLabelNum;
};

#endif // TERMINALCONFIG_H
