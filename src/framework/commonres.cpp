#include "../framework/commonres.hpp"

QIcon resources::icon::Get(resources::icon::ID icon, QString *icons_path, QString format)
{
    using namespace resources::icon;
    // Custom icons name in a xml file
    format.push_front(".");
    QMap<ID, QString> icon_list =
    {
        { ID::NoIcon, *icons_path + "no_icon" + format },
        { ID::Quit, *icons_path + "app_quit" + format },
        { ID::ChangeColor, *icons_path + "change_color" + format },
        { ID::Copy, *icons_path + "copy" + format },
        { ID::CopyFilePath, *icons_path + "copy_file_path" + format },
        { ID::Cut, *icons_path + "cut" + format },
        { ID::Delete, *icons_path + "delete" + format },
        { ID::FileExplorer, *icons_path + "file_explorer" + format },
        { ID::Folder, *icons_path + "folder" + format },
        { ID::Help, *icons_path + "help" + format },
        { ID::Informations, *icons_path + "informations" + format },
        { ID::MovePath, *icons_path + "move_path" + format },
        { ID::MoveTo, *icons_path + "move_to" + format },
        { ID::New, *icons_path + "new" + format },
        { ID::OneDrive, *icons_path + "onedrive" + format },
        { ID::OneDriveFolder, *icons_path + "onedrive_folder" + format },
        { ID::Paste, *icons_path + "paste" + format },
        { ID::Pin, *icons_path + "pin" + format },
        { ID::Pinned, *icons_path + "pinned" + format },
        { ID::Printer1, *icons_path + "printer_1" + format },
        { ID::Printer2, *icons_path + "printer_2" + format },
        { ID::RecentFiles, *icons_path + "recent_files" + format },
        { ID::Redo, *icons_path + "redo" + format },
        { ID::Refresh, *icons_path + "refresh" + format },
        { ID::Rename, *icons_path + "rename" + format },
        { ID::Save, *icons_path + "save" + format },
        { ID::Search, *icons_path + "search" + format },
        { ID::SelectionAll, *icons_path + "selection_all" + format },
        { ID::SelectionInvert, *icons_path + "selection_invert" + format },
        { ID::SelectionUnselect, *icons_path + "selection_unselected" + format },
        { ID::Shortcut, *icons_path + "shortcut" + format },
        { ID::TabClose, *icons_path + "tab_close" + format },
        { ID::Undo, *icons_path + "undo" + format }
    };

    QString ico_path = icon_list.value(icon);
    return QIcon(ico_path);
}
