#include "terminalconfig.h"
TerminalConfig::TerminalConfig()
{
    m_iLabelNum = 0;
    m_ppMyLabel = NULL;
}
void TerminalConfig::SetppMyLabel(myLable **mylabel)
{
    if(mylabel)
    {
        m_ppMyLabel = mylabel;
    }
}
void TerminalConfig::SetUPHand(bool flag)
{
    for(int i = 0;i < m_iLabelNum;i++)
    {
        m_ppMyLabel[i]->ShowUpHand(flag);
    }
}
void TerminalConfig::SetLabelNum(int num)
{
    if(num > 0)
    {
        m_iLabelNum = num;
    }
}
