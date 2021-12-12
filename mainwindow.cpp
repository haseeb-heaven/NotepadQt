#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Qutils.h"

using namespace QUTILS;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->notepadTxt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    ui->notepadTxt->clear();
}


void MainWindow::on_actionOpen_triggered()
{
    ui->notepadTxt->clear();
    auto qstr = g_Utils.Qt_ShowOpenFileDlg("Selecte text file","Text Files(*.txt);;All Files(*.*)",QUtils::Qt_GetAppPath(),true);
    if(!qstr.isEmpty()) ui->notepadTxt->insertPlainText(qstr);
}

void MainWindow::on_actionSave_triggered()
{
    auto qstr = ui->notepadTxt->toPlainText();
    if(qstr.isEmpty()) {on_actionSave_As_triggered(); return;}
    g_Utils.Qt_WriteFile(g_Utils.Qt_GetFileName(),qstr,true);
    QFileInfo fi(g_Utils.Qt_GetFileName());
    g_Utils.Qt_ShowInfo("File '" + fi.completeBaseName() + "' saved successfully");
}

void MainWindow::on_actionSave_As_triggered()
{
    auto file_name = g_Utils.Qt_ShowSaveFileDlg("Open the file");
    auto file_data = ui->notepadTxt->toPlainText();
    g_Utils.Qt_WriteFile(file_name,file_data,true);
    QFileInfo fi(file_name);
    g_Utils.Qt_ShowInfo("File '" + fi.completeBaseName() + "' saved successfully");
}


void MainWindow::on_actionQuit_triggered()
{
    int dlg_result = g_Utils.Qt_ShowDialog("Notepad is about to exit","Do you want to save unsaved changes");
    if(dlg_result == QMessageBox::Yes){//Ask for to save changes before exit.
        on_actionSave_As_triggered();
    }
    QCoreApplication::quit();
}

void MainWindow::on_actionCut_triggered()
{
    ui->notepadTxt->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->notepadTxt->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->notepadTxt->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->notepadTxt->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->notepadTxt->redo();
}


void MainWindow::on_actionAbout_NotepadQt_triggered()
{
    g_Utils.Qt_ShowInfo("Qt-Notepad is simple notepad application\nWritten by Haseeb Mir\n\nLanguage Framework  C++(17) / Qt version 6.2.2");
}

