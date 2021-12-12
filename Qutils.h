#ifndef QUTILS_H
#define QUTILS_H
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileDialog>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace QUTILS {
class QUtils
{
private:
    QString qfile_name;
public:
    //Default Ctor/Dtor.
    QUtils() = default;
    ~QUtils() = default;

    //Public static methods.
    static QString Qt_GetAppPath(){ return QCoreApplication::applicationDirPath();}
    //Private File setting methods.
     QString Qt_GetFileName(){return (qfile_name.isEmpty())? nullptr : qfile_name;}
     void Qt_SetFileName(QString file){(file.isEmpty())? qfile_name="" : qfile_name=file;}

    //Public non-static methods. Invoke using 'g_Utils' instance.
    //UI Dialogs,Information methods.
    void Qt_ShowInfo(QString info_msg,QString title="INFO");
    void Qt_ShowWarning(QString warning_msg,QString title="WARNING");
    void Qt_ShowError(QString err_msg,QString title="ERROR");
    int Qt_ShowDialog(QString dlg_msg,QString dlg_title);

    //File Manipulation methods.
    QString Qt_ShowOpenFileDlg(QString extension,bool log_dbg=false);
    QString Qt_ShowOpenFileDlg(QString title,QString extension,QString init_path,bool log_dbg=false);
    QString Qt_ShowSaveFileDlg(QString title,bool log_dbg=false);
    QString Qt_ReadFile(QString file_name,bool log_dbg=false);
    void Qt_WriteFile(QString file_name,QString file_data,bool log_dbg=false);
};
inline QUtils g_Utils;
}

#endif // QUTILS_H
