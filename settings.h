/*
    Copyright 2016, Mitch Curtis

    This file is part of Slate.

    Slate is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Slate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Slate. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QUrl>

class Settings : public QSettings
{
    Q_OBJECT
//    Q_PROPERTY(QUrl lastProjectUrl READ lastProjectUrl WRITE setLastProjectUrl NOTIFY lastProjectUrlChanged)

    Q_PROPERTY(QString quitShortcut READ quitShortcut WRITE setQuitShortcut NOTIFY quitShortcutChanged)

public:
    explicit Settings(QObject *parent = 0);

//    QUrl lastProjectUrl() const;
//    void setLastProjectUrl(const QUrl &url);

    Q_INVOKABLE void resetShortcutsToDefaults();

    QString defaultQuitShortcut() const;
    QString quitShortcut() const;
    void setQuitShortcut(const QString &shortcut);

signals:
//    void lastProjectUrlChanged();

    void quitShortcutChanged();
};

#endif // SETTINGS_H
