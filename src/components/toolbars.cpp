#include "../components/toolbars.hpp"

ToolBar::ToolBar(QWidget *parent, ActID id, bool movable, bool floatable,
                 Qt::ToolButtonStyle style) : QToolBar(parent)
{
    m_icons_path = new QString(":/icons/");

    switch(id){
    case ActID::Actions:
        m_new_file = addAction(tr("New"), this, &ToolBar::NewFilePressed);
        m_open = addAction(tr("Open"), this, &ToolBar::OpenPressed);
        m_save = addAction(tr("Save"), this, &ToolBar::SavePressed);
        m_save_as = addAction(tr("Save as..."), this, &ToolBar::SaveAsPressed);
        m_quit = addAction(tr("Quit"), this, &ToolBar::QuitPressed);

        m_new_file->setIcon(IC(New, m_icons_path, "png"));
        m_open->setIcon(IC(Folder, m_icons_path, "png"));
        m_save->setIcon(IC(Save, m_icons_path, "png"));
        m_save_as->setIcon(IC(Save, m_icons_path, "png"));
        m_quit->setIcon(IC(Quit, m_icons_path, "png"));
        break;
    case ActID::Edit:
        m_copy = addAction(tr("Copy"), this, &ToolBar::CopyPressed);
        m_cut = addAction(tr("Cut"), this, &ToolBar::CutPressed);
        m_paste = addAction(tr("Paste"), this, &ToolBar::PastePressed);
        m_delete = addAction(tr("Delete"), this, &ToolBar::DeletePressed);

        m_cut->setIcon(IC(Cut, m_icons_path, "png"));
        m_copy->setIcon(IC(Copy, m_icons_path, "png"));
        m_paste->setIcon(IC(Paste, m_icons_path, "png"));
        m_delete->setIcon(IC(Delete, m_icons_path, "png"));
        break;
    case ActID::Font:
        break;
    case ActID::TextFormat:
        break;
    case ActID::UndoRedo:
        m_undo = addAction(tr("Undo"), this, &ToolBar::UndoPressed);
        m_redo = addAction(tr("Redo"), this, &ToolBar::RedoPressed);

        m_undo->setIcon(IC(Undo, m_icons_path, "png"));
        m_redo->setIcon(IC(Redo, m_icons_path, "png"));
        break;
    case ActID::Zoom:
        m_zoom_in = addAction(tr("Zoom In"), this, &ToolBar::ZoomInPressed);
        m_zoom_out = addAction(tr("Zoom Out"), this, &ToolBar::ZoomOutPressed);
        m_reset_zoom = addAction(tr("Reset zoom"), this, &ToolBar::ResetZoomPressed);

        m_zoom_in->setIcon(IC(NoIcon, m_icons_path, "png"));
        m_zoom_out->setIcon(IC(NoIcon, m_icons_path, "png"));
        m_reset_zoom->setIcon(IC(NoIcon, m_icons_path, "png"));
        break;
    default: // Custom toolbar ?
        break;
    }
    setMovable(movable);
    setFloatable(floatable);
    setToolButtonStyle(style);
}