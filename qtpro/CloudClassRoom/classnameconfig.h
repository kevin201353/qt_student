#ifndef CLASSNAMECONFIG_H
#define CLASSNAMECONFIG_H
#include <QString>
#include <QWidget>
#include "classmould.h"
#define MAXCLASS    10
struct ClassNameAndChoose
{
    QString s_strClassName;
    QString s_strClassID;
    QString s_strClassRoomName;
    bool    s_bChooseFlag;
};
class ClassNameConfig
{
public:
    ClassNameConfig();
    void AddClass(QString name,QString ID,QString RoomName);
    void AddLabel(ClassMould *label);

    void SetLabelName();
    void AddInode();
    void MinusInode();
    void ChooseOne();
    QString GetClassName();
    QString GetID();
    QString GetRoomID();
    int m_iClassNum;
private:
    int m_iClassLabelNum;
    int m_iInode;
    ClassNameAndChoose m_ClassNameArray[MAXCLASS];
    ClassMould *m_pClassLabel[MAXCLASS];
    void ClearOtherChoose(int inode);

};

#endif // CLASSNAMECONFIG_H
