#include "../components/menubar.hpp"

QPointer<MenuBar> MenuBar::m_menu_bar;

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{
    m_menu_bar = this;
    CreateFileMenu();
    CreateEditMenu();
    CreateFormatMenu();
    CreateViewMenu();
    CreateHelpMenu();
}

void MenuBar::CreateFileMenu()
{
    QMenu *m_fileMenu = m_menu_bar->addMenu(tr("File"));
    m_new_file = m_fileMenu->addAction(tr("New File"), this, &MenuBar::NewFilePressed);
    m_new_window = m_fileMenu->addAction(tr("New Instance"), this, &MenuBar::NewWindowPressed);
    m_open = m_fileMenu->addAction(tr("Open"), this, &MenuBar::OpenPressed);
    m_save = m_fileMenu->addAction(tr("Save"), this, &MenuBar::SavePressed);
    m_save_as = m_fileMenu->addAction(tr("Save as..."), this, &MenuBar::SaveAsPressed);

    m_fileMenu->addSeparator();

    m_copy_file_path = m_fileMenu->addAction(tr("Copy file path"), this, &MenuBar::CopyFilePathPressed);
    m_print = m_fileMenu->addAction(tr("Print..."), this, &MenuBar::PrintPressed);

    m_fileMenu->addSeparator();

    m_quit = m_fileMenu->addAction(tr("Quit"), this, &MenuBar::QuitPressed);
}

void MenuBar::CreateEditMenu()
{
    QMenu *m_editMenu = m_menu_bar->addMenu(tr("Edit"));
    m_undo = m_editMenu->addAction(tr("Undo"), this, &MenuBar::UndoPressed);
    m_redo = m_editMenu->addAction(tr("Redo"), this, &MenuBar::RedoPressed);

    m_editMenu->addSeparator();

    m_cut = m_editMenu->addAction(tr("Cut"), this, &MenuBar::CutPressed);
    m_copy = m_editMenu->addAction(tr("Copy"), this, &MenuBar::CopyPressed);
    m_paste = m_editMenu->addAction(tr("Delete"), this, &MenuBar::DeletePressed);

    m_editMenu->addSeparator();

    m_select_all = m_editMenu->addAction(tr("Select all"), this, &MenuBar::SelectAllPressed);
    m_current_date = m_editMenu->addAction(tr("Date/Hour"), this, &MenuBar::CurrentDatePressed);
}

void MenuBar::CreateFormatMenu()
{
    QMenu *m_formatMenu = m_menu_bar->addMenu(tr("Format"));
    m_auto_wrap_text = m_formatMenu->addAction(tr("Enable text wrapping"), this, &MenuBar::AutoWrapTextPressed);
}

void MenuBar::CreateViewMenu()
{
    QMenu *m_viewMenu = m_menu_bar->addMenu(tr("Edit"));
    CreateZoomMenu(m_viewMenu);
    m_show_status_bar = m_viewMenu->addAction(tr("Show Status bar"), this, &MenuBar::ShowStatusBarPressed);
}

void MenuBar::CreateZoomMenu(QMenu *parent)
{
    m_zoom_menu = parent->addMenu(tr("Zoom"));
    m_zoom_in = m_zoom_menu->addAction(tr("Zoom In"), this, &MenuBar::ZoomInPressed);
    m_zoom_out = m_zoom_menu->addAction(tr("Zoom Out"), this, &MenuBar::ZoomOutPressed);
    m_reset_zoom = m_zoom_menu->addAction(tr("Reset zoom"), this, &MenuBar::ResetZoomPressed);
}

/*void MenuBar::CreateWindowMenu()
{
    QMenu *m_windowMenu = m_menubar->addMenu(tr("Window"));
    // Lister les toolbars avec un get toolbars
}*/

void MenuBar::CreateHelpMenu()
{
    QMenu *m_helpMenu = m_menu_bar->addMenu(tr("Help"));
    m_about_qt = m_helpMenu->addAction(tr("About Qt..."), this, &MenuBar::MenuBar::AboutQtPressed);
}