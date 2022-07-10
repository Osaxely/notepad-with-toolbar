#ifndef TOOLBARS_HPP
#define TOOLBARS_HPP

#include <QWidget>
#include <QToolBar>

#include <QAction>
#include <QIcon>
#include <QDir>

#include <QMap>
#include <QPointer>

#include "../framework/commonres.hpp"

#define IC(id, path, format) resources::icon::Get(resources::icon::ID::id, path, format)

class ToolBar : public QToolBar
{

    Q_OBJECT

public:
    enum class ActID
    {
        Actions,
        UndoRedo,
        Edit,
        Zoom,
        TextFormat,
        Font,
        Custom
    };

    explicit ToolBar(QWidget *parent = nullptr, ActID tool_bar_id = ActID::Custom, bool isMovable = true, bool isFloatable = true,
            Qt::ToolButtonStyle style = Qt::ToolButtonStyle::ToolButtonTextOnly);

signals:
    void NewFilePressed();
    void OpenPressed();
    void SavePressed();
    void SaveAsPressed();
    void PrintPressed();
    void QuitPressed();

    void UndoPressed();
    void RedoPressed();
    void CutPressed();
    void CopyPressed();
    void PastePressed();
    void DeletePressed();

    void ZoomInPressed();
    void ZoomOutPressed();
    void ResetZoomPressed();

private:
    QMap<QString, QString> *m_icons_list;

    // Toolbars
    QToolBar *m_actions_toolbar = nullptr;
    QToolBar *m_edit_toolbar = nullptr;
    QToolBar *m_zoom_toolbar = nullptr;
    QToolBar *m_txt_format_toolbar = nullptr;
    QToolBar *m_font_toolbar = nullptr;

    QAction *m_new_file = nullptr;
    QAction *m_open = nullptr;
    QAction *m_save = nullptr;
    QAction *m_save_as = nullptr;
    QAction *m_print = nullptr;
    QAction *m_quit = nullptr;

    // Edit
    QAction *m_undo = nullptr;
    QAction *m_redo = nullptr;
    QAction *m_cut = nullptr;
    QAction *m_copy = nullptr;
    QAction *m_paste = nullptr;
    QAction *m_delete = nullptr;

    // View
    QAction *m_zoom_in = nullptr;
    QAction *m_zoom_out = nullptr;
    QAction *m_reset_zoom = nullptr;

    QString *m_icons_path;
};

#endif