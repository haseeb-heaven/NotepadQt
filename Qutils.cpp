#include "Qutils.h"
using namespace QUTILS;

void QUtils::Qt_ShowInfo(QString info_msg,QString title){
    QMessageBox::information(nullptr,title,info_msg,QMessageBox::Ok);
}

void QUtils::Qt_ShowWarning(QString warning_msg, QString title){
    QMessageBox::information(nullptr,title,warning_msg,QMessageBox::Ok);
}

void QUtils::Qt_ShowError(QString err_msg, QString title){
    QMessageBox::information(nullptr,title,err_msg,QMessageBox::Ok);
}

int QUtils::Qt_ShowDialog(QString dlg_msg, QString dlg_title){
    QMessageBox dlgBox;
    dlgBox.setText(dlg_title);
    dlgBox.setInformativeText(dlg_msg);
    dlgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dlgBox.setDefaultButton(QMessageBox::Save);
    int dlg_result = dlgBox.exec();
    return dlg_result;
}

QString  QUtils::Qt_ShowOpenFileDlg(QString filter, bool log_dbg){
    auto file_data = QString();
    auto fileContentReady = [&](const QString &file_name, const QByteArray &file_content) {
        if (file_name.isEmpty()) {
            // No file was selected
            g_Utils.Qt_ShowError("File '" +file_name+ "' not found");
            if(log_dbg) qDebug() << "File '" << file_name << "' not found" << "\n";
        } else {
            if(log_dbg) qDebug() << "File '" << file_name << "' selected" << "\n";
            QUtils::Qt_SetFileName(file_name);
            file_data= QString(file_content);
        }
    };
    QFileDialog::getOpenFileContent(filter,  fileContentReady);
    return file_data;
}

QString QUtils::Qt_ShowOpenFileDlg(QString title,QString filter,QString init_path,bool log_dbg){

    QString file_name = QFileDialog::getOpenFileName(nullptr, title,init_path,filter);
    if(log_dbg) qDebug() << "File name: '" << file_name << "' selected";
    QUtils::Qt_SetFileName(file_name);
    auto qstr = Qt_ReadFile(file_name);
    return qstr;
}

QString QUtils::Qt_ShowSaveFileDlg(QString title,bool log_dbg){

    QString file_name = QFileDialog::getSaveFileName(nullptr, title);
    if(log_dbg) qDebug() << "File name: '" << file_name << "' selected";
    return file_name;
}

QString QUtils::Qt_ReadFile(QString file_name,bool log_dbg){
    QFile file(file_name);
    if(log_dbg) qDebug() << "Trying to read file '" << file_name << "'";
    QString qstr;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        if(log_dbg) qDebug() << "File size: " << file.size();
        qstr = QString(in.readAll());
        file.close();
    }
    return qstr;
}

void QUtils::Qt_WriteFile(QString file_name,QString file_data,bool log_dbg){
    QFile file(file_name);
    if(log_dbg) qDebug() << "Trying to write file '" << file_name << "'";

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        if(log_dbg) qDebug() << "File size: " << file.size();
        out << file_data << "\n";
        if(log_dbg) qDebug() << "File data written successfully";
        file.close();
    }
}

