#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include <QWidget>
#include <QMenuBar>
#include <QMenu>

#include <QAction>

#include <QPointer>

class MenuBar : public QMenuBar
{

    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr);

private:
    void CreateFileMenu();
    void CreateEditMenu();
    void CreateFormatMenu();
    void CreateViewMenu();
    void CreateZoomMenu(QMenu *parent);
    // void CreateWindowMenu();
    void CreateHelpMenu();

signals:
    void NewFilePressed();
    void NewWindowPressed();
    void OpenPressed();
    void SavePressed();
    void SaveAsPressed();
    void CopyFilePathPressed();
    void PrintPressed();
    void QuitPressed();

    void UndoPressed();
    void RedoPressed();
    void CutPressed();
    void CopyPressed();
    void PastePressed();
    void DeletePressed();
    void SelectAllPressed();
    void CurrentDatePressed();

    void AutoWrapTextPressed(bool);

    void ZoomInPressed();
    void ZoomOutPressed();
    void ResetZoomPressed();
    void ShowStatusBarPressed(bool);

    void AboutPressed();
    void AboutQtPressed();

private:
    static QPointer<MenuBar> m_menu_bar;
    QMenu *m_zoom_menu;
    QAction *m_new_file = nullptr;
    QAction *m_new_window = nullptr;
    QAction *m_open = nullptr;
    QAction *m_save = nullptr;
    QAction *m_save_as = nullptr;
    QAction *m_copy_file_path = nullptr;
    QAction *m_print = nullptr;
    QAction *m_quit = nullptr;
    // Edit
    QAction *m_undo = nullptr;
    QAction *m_redo = nullptr;
    QAction *m_cut = nullptr;
    QAction *m_copy = nullptr;
    QAction *m_paste = nullptr;
    QAction *m_delete = nullptr;
    QAction *m_select_all = nullptr;
    QAction *m_current_date = nullptr;
    // Format
    QAction *m_auto_wrap_text = nullptr;
    // View
    QAction *m_zoom_in = nullptr;
    QAction *m_zoom_out = nullptr;
    QAction *m_reset_zoom = nullptr;
    QAction *m_show_status_bar = nullptr;
    // Help
    QAction *m_about = nullptr;
    QAction *m_about_qt = nullptr;
};

#endif