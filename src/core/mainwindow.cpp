#include "mainwindow.hpp"
// Set palet avec le thème sombre de Windows
// Handle same path file -> if the file is at the same path, the user will be move to the tab where the file is

MainWindow::MainWindow(){
    setMinimumSize(1280, 720);

    // Menubar and toolbar initialization
    m_menubar = new MenuBar(this);
    m_toolbar = new ToolBar(this, ToolBar::ActID::Actions, true, true, Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

    m_addTabButton = new QPushButton("Get Array Data");
    m_toolbar->addWidget(m_addTabButton);

    setMenuBar(m_menubar);
    addToolBar(m_toolbar);

    QFile tempfile("C:/");

    // ========================= CREATE A NEW TAB BAR
    m_tab_widget = new QTabWidget;
    m_tab_widget->setTabsClosable(true);
    m_tab_widget->setDocumentMode(true);

    setCentralWidget(m_tab_widget);

    // ========================== CONNECT BUTTONS
    connect(m_tab_widget, &QTabWidget::tabCloseRequested, this, &MainWindow::CloseTab);
    connect(this, &MainWindow::FileOpened, this, &MainWindow::NewTabFrom);

    connect(m_menubar, &MenuBar::OpenPressed, this, &MainWindow::Open);
    connect(m_toolbar, &ToolBar::SaveAsPressed, this, &MainWindow::OpenSaveFileDialog);
    connect(m_toolbar, &ToolBar::OpenPressed, this, &MainWindow::Open);
    connect(m_addTabButton, &QPushButton::clicked, this, &MainWindow::ArrayData);
    connect(this, &MainWindow::NewTabAdded, this, &MainWindow::UpdateActions);
    connect(this, &MainWindow::DisableSave, [&](){
        m_toolbar->SaveAs()->setEnabled(false);
        m_toolbar->Save()->setEnabled(false);
    });
    connect(m_toolbar, &ToolBar::SavePressed, this, &MainWindow::Save);

    // ========================== CREATE A NEW PAGE IN THE TAB BAR
    NewTabFrom(tempfile);
}

void MainWindow::UpdateActions()
{
    m_toolbar->SaveAs()->setEnabled(true);
    m_toolbar->Save()->setEnabled(true);
}

void MainWindow::ArrayData()
{
    int i = 0;
    for(std::vector<QString>::const_iterator it = m_doc_path.begin(); it != m_doc_path.end(); ++it){
        qDebug() << "Tab index:" << i << " value:" << *it << "/" << m_doc_name.at(i);
        ++i;
        for(auto it = m_tarea.begin(); it != m_tarea.end(); ++it){
            qDebug() << "Text Area " << i << "=" << *it;
        }
        qDebug() << m_tarea.size();
    }
}

void MainWindow::NewTabFrom(QFile &f_path){
    // ============= Update the current document path
    QFileInfo fileInfo(f_path);

    m_doc_path.push_back(fileInfo.absolutePath());
    m_doc_name.push_back(fileInfo.baseName());
    m_doc_ext.push_back(fileInfo.completeSuffix());

    // ====================== CREATE A NEW TAB FROM REQUESTED FILE
    m_tarea.push_back(new QPlainTextEdit);
    int index{ m_tab_widget->count() };
    m_tarea[index]->setFrameStyle(0x000);
    m_tab_widget->addTab(m_tarea[index], "");
    // Another condition when tab system is disabled
    if(m_tab_widget->tabBar()->isHidden()){
        CloseTab(0);
        m_tab_widget->tabBar()->setHidden(false);
    }

    // ============ Verify file
    QString tab_name = "";

    if(m_doc_path[index].isEmpty()){
        tab_name.append(tr("Untitled %0").arg(index));
    }
    else{
        if(m_doc_name[index].isEmpty()){
            if(!m_doc_ext[index].isEmpty()){
                tab_name.append(tr("Untitled_%1").arg(index) + "." + m_doc_ext[index]);
            }
            else{ // Everything is empty
                tab_name.append(tr("Untitled_%1").arg(index));
            }
        }
        else{ // There is a name but is there an extension ?
            tab_name.append(m_doc_name[index]);
            if(!m_doc_ext[index].isEmpty()){
                tab_name.append("." + m_doc_ext[index]);
            }
        }
    }

    m_tarea[index]->setPlainText(f_path.readAll());

    m_tab_widget->setTabText(index, tab_name);
    m_tab_widget->setCurrentIndex(index);

    emit NewTabAdded();
}

void MainWindow::CloseTab(unsigned int index){
    m_doc_path.erase(std::begin(m_doc_path) + index);
    m_doc_name.erase(std::begin(m_doc_name) + index);
    m_doc_ext.erase(std::begin(m_doc_ext) + index);
    m_tab_widget->removeTab(index);
    delete m_tarea[index];
    m_tarea[index] = nullptr;
    m_tarea.erase(std::begin(m_tarea) + index);
    if(m_tab_widget->count() == 0){
        emit DisableSave();
        qDebug("No more tabs!");
    }
}

void MainWindow::CreateEmptyPage()
{
    m_no_doc_page = new QWidget(this);
    m_drag_drop_text = new QLabel(tr("Drag and drop here to start."));
    QVBoxLayout *vertical_layout = new QVBoxLayout;
    vertical_layout->addWidget(m_drag_drop_text);
    vertical_layout->setAlignment(m_drag_drop_text, Qt::AlignCenter);
    m_no_doc_page->setLayout(vertical_layout);
}

MainWindow::FileStatus MainWindow::Open(){
    // Check save change here
    // Lock the file when open
    QString path = QFileDialog::getOpenFileName(this, tr("Open a file..."), QString() /*Dir in settings*/, "All files (*.*)");
    if(path == ""){
        return FileStatus::Canceled;
    }
    else{
        // Create a new file and emit UpdateCurrentDocument
        QFile document(path);
        if(!document.open(QFileDevice::ReadOnly)){
            QMessageBox::information(this, "Notepad with toolbars", tr("Unable to open the file in :\n%1").arg(path));
            return FileStatus::FailedToOpen;
        }
#ifdef Q_OS_WIN
        qDebug() << "You're on Windows";
        qDebug()<<document.fileName();
        QLockFile lock(document.fileName());
        lock.setStaleLockTime(0);
        lock.tryLock(5);
#endif
        emit FileOpened(document);
        // Add a security in Windows
    }
    return FileStatus::Opened;
}

MainWindow::FileStatus MainWindow::OpenSaveFileDialog()
{
    // Custom filters, Default file name
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                     QDir::homePath() /* Configurable in settings, can make the default filename */, "Plain Text Document (*.txt);;Markdown File (*.md)");
    qDebug()<<file_name;
    if(file_name == ""){
        return FileStatus::Canceled;
    }
    else{
        QFile file(file_name);

        if(file.open(QFileDevice::WriteOnly)){
            QTextStream out(&file);
            out << m_tarea[m_tab_widget->currentIndex()]->toPlainText();
            file.close();
        }
        else{
            QMessageBox::critical(this, tr("Notepad with toolbar"), tr("Unable to open the file in \"%0\"").arg(m_doc_path[m_tab_widget->currentIndex()]));
            return FileStatus::FailedToOpen;
        }
    }
    return FileStatus::Saved;
}

MainWindow::FileStatus MainWindow::Save()
{
    // Status bar->"File saved successfully"
    int index = m_tab_widget->currentIndex();

    if(!m_doc_path[index].isEmpty()){
        QFile file(m_doc_path[index] + "/" + m_doc_name[index] + "." + m_doc_ext[index]);
        if(file.open(QIODevice::WriteOnly | QIODevice::ExistingOnly)){
            QTextStream out(&file);
            out << m_tarea[index]->toPlainText();

            file.close();

            return FileStatus::Saved;
        }
    }
    return OpenSaveFileDialog();
}