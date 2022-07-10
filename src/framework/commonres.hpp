#ifndef COMMONPATHS_HPP
#define COMMONPATHS_HPP

#include <QMap>
#include <QStringList>
#include <QDebug>

#include <QIcon>

namespace resources
{
    namespace icon
    {
        enum class ID
        {
            NoIcon,
            Quit,
            ChangeColor,
            Copy,
            CopyFilePath,
            Cut,
            Delete,
            FileExplorer,
            Folder,
            Help,
            Informations,
            MovePath,
            MoveTo,
            New,
            OneDrive,
            OneDriveFolder,
            Paste,
            Pin,
            Pinned,
            Printer1,
            Printer2,
            RecentFiles,
            Redo,
            Refresh,
            Rename,
            Save,
            Search,
            SelectionAll,
            SelectionInvert,
            SelectionUnselect,
            Shortcut,
            TabClose,
            Undo
        };

        QIcon Get(ID icon, QString *icons_path, QString format = "png");
    }
}

#endif