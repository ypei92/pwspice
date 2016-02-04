/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "MyClass.h"
#include "SpParser.hpp"
#include <QtGui>
#include <ctime>


#include "mainwindow.h"
extern FILE *yyin;

MainWindow::MainWindow()
{
    init();
    setCurrentFile("");
}

MainWindow::MainWindow(const QString &fileName)
{
    init();
    loadFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    MainWindow *other = new MainWindow;
    other->move(x() + 40, y() + 40);
    other->show();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        MainWindow *existing = findMainWindow(fileName);
        if (existing) {
            existing->show();
            existing->raise();
            existing->activateWindow();
            return;
        }

        if (isUntitled && textEdit->document()->isEmpty()
                && !isWindowModified()) {
            loadFile(fileName);
        } else {
            MainWindow *other = new MainWindow(fileName);
            if (other->isUntitled) {
                delete other;
                return;
            }
            other->move(x() + 40, y() + 40);
            other->show();
        }
    }
}

bool MainWindow::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("Application Infro"),
            tr("This is only beta one after the toefl test = = "
               ));
}

void MainWindow::documentWasModified()
{
    setWindowModified(true);
}

void MainWindow::init()
{
    setAttribute(Qt::WA_DeleteOnClose);

    isUntitled = true;

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setUnifiedTitleAndToolBarOnMac(true);

    setWindowTitle(tr("PWspice"));
    setMinimumSize(300,300);
    resize(500,500);
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    closeAct = new QAction(tr("&Close"), this);
    closeAct->setShortcut(tr("Ctrl+W"));
    closeAct->setStatusTip(tr("Close this window"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    compileAct = new QAction(QIcon(":/images/compile.png") , tr("&Compile"),this);
    //compileAct->setShortcut(tr("Ctrl+z"));
    compileAct -> setStatusTip(tr("Complile for error"));
    connect(compileAct, SIGNAL(triggered()), this, SLOT(compile()));

    stimulateAct = new QAction(QIcon(":/images/stimulate.png"), tr("&Stimulate"), this);
    //stimulateAct->setShortcuts(tr("Ctrl+x"));
    stimulateAct->setStatusTip(tr("Stimulate the netlist"));
    connect(stimulateAct, SIGNAL(triggered()), this, SLOT(stimulate()));

    endAct = new QAction(QIcon(":/images/end.png"), tr("&End"), this);
    //endAct->setShortcuts(tr("Ctrl+c"));
    endAct->setStatusTip(tr("End the stimulate process"));
    connect(endAct, SIGNAL(triggered()), this, SLOT(shut_down()));


    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
}

void MainWindow::compile()
{
    char* filename;
    QByteArray file = curFile.toLatin1();

    filename = file.data();
    //printf("%s \n",filename);

    yyin = fopen(filename, "r");
    if (yyin == NULL)
    {
        printf("error");
        exit(-1);
    }

    MyClass *pObj = new MyClass();
    yy::SpParser spiceParser(pObj);
    spiceParser.parse();
    printf("\n");
    cir = new circuit;
    cir = pObj->Summarize();
    cir->display_char_node();

    object_name = cir->return_name(object_num);

    Option_selectToolBar = new QToolBar( this );

    hBox = new QWidget( Option_selectToolBar);

    layout = new QHBoxLayout( hBox );
    layout->setSpacing( 0 );
    layout->addWidget( new QWidget( hBox )  ); // spacer
    layout->addWidget( new QLabel( "Option:     ", hBox ), 0 );
    layout->addWidget( new QLabel( "method:", hBox ), 0 );
    layout->addSpacing( 10 );

    method = new QComboBox( hBox);
    method->addItem(QWidget::tr("DC"));
    method->addItem(QWidget::tr("Tran"));
    method->addItem(QWidget::tr("AC"));
    layout->addWidget( method , 0);

    ob = new QComboBox( hBox);
    start = new QwtCounter( hBox );
    step = new QwtCounter( hBox );
    end = new QwtCounter( hBox );
    label_ob = new QLabel;
    label_start = new QLabel;
    label_step = new QLabel;
    label_end = new QLabel;
    get_paint(0);

    connect( method , SIGNAL(  currentIndexChanged(int) ),
        this , SLOT( get_paint( int ) ) );

    //delete pObj;
}

void MainWindow::stimulate()
{

    double start_point = start->value();
    double h = step->value();
    double end_point = end->value();

    int type = method->currentIndex();
    int ob_name = ob ->currentIndex();

    //cir->display_char_node();
    cout << "aaaaaaaaaaaaaaaaaaaastart" << start_point << "  h" << h << "  end" <<end_point << "type =" << type;

    if( type == 0) cir->dc_simulation( object_name[ob_name] , start_point , end_point , h);
    if( type == 1) cir->tran_simulation(h,end_point);
    if( type == 2) cir->ac_simulation( object_name[ob_name], start_point/(2*3.1415926) , end_point/(2*3.1415926)  , h);

    sleep(1);

    w = new Qwtpic( type + 1);
    w->resize( 550, 200);
    w->show();

}

void MainWindow::shut_down()
{
    exit(1);
}

//! [implicit tr context]
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
//! [implicit tr context]
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    StimulateMenu = menuBar()->addMenu(tr("&Stimulate"));
    StimulateMenu -> addAction(compileAct);
    StimulateMenu -> addAction(stimulateAct);
    StimulateMenu -> addAction(endAct);
}

void MainWindow::createToolBars()
{
//! [0]
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
//! [0]
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    stimulateToolBar = addToolBar(tr("Stimulate"));
    stimulateToolBar-> addAction(compileAct);
    stimulateToolBar-> addAction(endAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool MainWindow::maybeSave()
{
    if (textEdit->document()->isModified()) {
	QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("PWspice"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard
		     | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("PWspice"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("PWspice"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    static int sequenceNumber = 1;

    isUntitled = fileName.isEmpty();
    if (isUntitled) {
        curFile = tr("document%1.txt").arg(sequenceNumber++);
    } else {
        curFile = QFileInfo(fileName).canonicalFilePath();
    }

    textEdit->document()->setModified(false);
    setWindowModified(false);
    setWindowFilePath(curFile);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

MainWindow *MainWindow::findMainWindow(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QWidget *widget, qApp->topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin && mainWin->curFile == canonicalFilePath)
            return mainWin;
    }
    return 0;
}


void MainWindow::get_paint(int a)
{
    delete ob;
    delete start;
    delete step;
    delete end;

    delete label_ob;
    delete label_start;
    delete label_step;
    delete label_end;

    if(a == 0 || a == 2)
    {
        label_ob = new QLabel( "   Object ", hBox );
        layout->addWidget( label_ob , 0 );
        ob = new QComboBox( hBox);
        for(int i ; i < object_num ; ++i) ob -> addItem(QWidget::tr(object_name[i]));
        layout->addWidget( ob , 0);

        label_start = new QLabel( "   start ", hBox );
        layout->addWidget( label_start ,  0 );
        start = new QwtCounter( hBox );
        if(a == 0)start->setRange( -50000.0, 50000.0 );
        else start->setRange( -5000000000, 500000000000.0 );
        start->setSingleStep( 0.01 );
        start->setValue( 0 );
        layout->addWidget( start, 0);

        if(a == 0)label_step = new QLabel( "   step ", hBox );
        else label_step = new QLabel( "   amount ", hBox );
        layout->addWidget( label_step , 0 );
        step= new QwtCounter( hBox );
        step->setRange( 0.000000001, 5000.0 );
        step->setSingleStep( 0.01 );
        step->setValue( 0.1 );
        layout->addWidget( step, 0);

        label_end = new QLabel( "   end ", hBox );
        layout->addWidget( label_end, 0 );
        end= new QwtCounter( hBox );
        if(a == 0)end->setRange( 0.0, 50.0 );
        else end->setRange( -500000000000.0, 500000000000.0 );
        end->setSingleStep( 0.01 );
        end->setValue( 3.3 );
        layout->addWidget( end, 0);

        //Option_selectToolBar-> addSeparator();
        Option_selectToolBar-> addAction(stimulateAct);

        ( void )Option_selectToolBar->addWidget( hBox);

        addToolBar( Option_selectToolBar);
    }
    else
    {
        ob = new QComboBox( hBox);
        start = new QwtCounter( hBox );
        label_ob = new QLabel;
        label_start = new QLabel;


        label_step = new QLabel( "     step ", hBox );
        layout->addWidget( label_step , 0 );
        step= new QwtCounter( hBox );
        step->setRange( 0.0000000000000000001, 500.0 );
        step->setSingleStep( 0.01 );
        step->setValue( 0.1 );
        layout->addWidget( step, 0);

        label_end = new QLabel( "      duration ", hBox );
        layout->addWidget( label_end, 0 );
        end= new QwtCounter( hBox );
        end->setRange( 0.0, 5000.0 );
        end->setSingleStep( 0.01 );
        end->setValue( 10 );
        layout->addWidget( end, 0);

        Option_selectToolBar-> addAction(stimulateAct);

        ( void )Option_selectToolBar->addWidget( hBox);

        addToolBar( Option_selectToolBar);
    }
}

/*
double get_start_value(double a){ return a; }
double get_end_value(double a){ return a; }
double get_step_value(double a){ return a; }
int get_method_value(int a){ return a; }
int get_object_value(int a){ return a; }*/

