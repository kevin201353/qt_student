#include "classnameconfig.h"

ClassNameConfig::ClassNameConfig()
{
    m_iClassNum = 0;
    m_iClassLabelNum = 0;
    m_iInode = 0;
}
void ClassNameConfig::AddClass(QString name,QString id)
{
    if(m_iClassNum < MAXCLASS)
    {
        m_ClassNameArray[m_iClassNum].s_strClassName = name;
        m_ClassNameArray[m_iClassNum].s_strClassID = id;
        m_ClassNameArray[m_iClassNum].s_bChooseFlag = false;
        m_iClassNum++;
    }
    else
    {
    }
}

void ClassNameConfig::AddLabel(ClassMould *label)
{
    if(label)
    {
        m_pClassLabel[m_iClassLabelNum++] = label;
    }
}
void ClassNameConfig::AddInode()
{
    if(m_iInode < m_iClassNum-3)
        m_iInode++;
}
void ClassNameConfig::MinusInode()
{
    if(m_iInode > 0)
        m_iInode--;
}
void ClassNameConfig::SetLabelName()
{
    int itemp = m_iInode;
    for(int i = 0;i < m_iClassLabelNum;i++)
    {
        m_pClassLabel[i]->SetClassName(m_ClassNameArray[itemp].s_strClassName);

        if(!m_ClassNameArray[itemp].s_bChooseFlag)
        {
            m_pClassLabel[i]->SetChecked(false);

        }
        else
        {
            m_pClassLabel[i]->SetChecked(true);
        }
        itemp++;
    }
}

void ClassNameConfig::ClearOtherChoose(int inode)
{
    for(int i = 0;i < m_iClassNum;i++)
    {
        m_ClassNameArray[i].s_bChooseFlag = false;
    }
    for(int i = 0;i < m_iClassLabelNum;i++)
    {
        m_pClassLabel[i]->SetCheckedFlag(false);
    }
    if(inode < m_iClassNum)
    {
        m_ClassNameArray[inode].s_bChooseFlag = true;
    }
}
void ClassNameConfig::ChooseOne()
{
    for(int i = 0;i < m_iClassLabelNum;i++)
    {
        if(m_pClassLabel[i]->IsChecked())
        {
            ClearOtherChoose(m_iInode+i);
            break ;
        }
    }
}

QString ClassNameConfig::GetClassName()
{
    for(int i = 0;i < m_iClassNum;i++)
    {
        if(m_ClassNameArray[i].s_bChooseFlag)
            return m_ClassNameArray[i].s_strClassName;
    }
}
QString ClassNameConfig::GetClassID()
{
    for(int i = 0;i < m_iClassNum;i++)
    {
        if(m_ClassNameArray[i].s_bChooseFlag)
            return m_ClassNameArray[i].s_strClassID;
    }
}
