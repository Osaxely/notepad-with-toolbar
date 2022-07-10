#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// Standard C++ Lib
#include <vector>
#include <iostream>
#include <fstream>

#include <QMainWindow>
#include <QTabWidget>
#include <QTabBar>
#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLabel>

#include <QFileDialog>
#include <QFontDialog> // Temporary
#include <QMessageBox>

#include <QFile>
#include <QLockFile>
#include <QFileInfo>

#include <QTextStream>
#include <QList>

#include "../framework/commonres.hpp"

// Temporary
#include <QPlainTextEdit>

#include "../components/menubar.hpp"
#include "../components/toolbars.hpp"

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    enum class FileStatus{
        Opened,
        AlreadyOpened,
        Closed,
        FailedToOpen,
        Canceled,
        Saved,
        Unsaved,
        FailedToSave
    };

    MainWindow();

private:
    int TAREA_COUNTER;

    MenuBar *m_menubar;
    ToolBar *m_toolbar;

    // Tab manager
    QTabWidget *m_tab_widget;

    QWidget *m_page;
    QWidget *m_tabButtonsPanel;
    QWidget *m_no_doc_page;

    QPushButton *m_addTabButton;

    std::vector<QPlainTextEdit*> m_tarea;

    // Others
    QLabel *m_drag_drop_text;

    // Data
    QString m_filters = tr("Plain text files (*.txt, *.text);;comma-separated value files(*.csv);;Extensible markup language files (*.xml);;All files(*.*)");
    QString m_default_dir = QDir::homePath();

    std::vector<QString> m_doc_path;
    std::vector<QString> m_doc_name;
    std::vector<QString> m_doc_ext;

signals:
    void FileOpened(QFile &file);
    void NewTabAdded();
    void DisableSave();

private slots:
    void UpdateActions();
    // Tabs
    void NewTabFrom(QFile &f_path);
    void CloseTab(unsigned index);
    void CreateEmptyPage();

    void ArrayData();

    // Toolbar and menubar
    //FileStatus NewFile();
    MainWindow::FileStatus Open();
    MainWindow::FileStatus OpenSaveFileDialog();
    //FileStatus SaveChange();
    FileStatus Save();
};

#endif