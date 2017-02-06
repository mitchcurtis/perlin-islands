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

#include "settings.h"

#include <QDebug>
#include <QKeySequence>
#include <QLoggingCategory>
#include <QVector>

Q_LOGGING_CATEGORY(lcSettings, "app.settings")

Settings::Settings(QObject *parent) :
    QSettings(parent)
{
    qCDebug(lcSettings) << "Loading settings from" << fileName();
}

//QUrl Settings::lastProjectUrl() const
//{
//    return value("lastProjectUrl").toUrl();
//}

//void Settings::setLastProjectUrl(const QUrl &url)
//{
//    QVariant existingValue = value("lastProjectUrl");
//    QUrl existingUrl;
//    if (contains("lastProjectUrl")) {
//        existingUrl = existingValue.toUrl();
//    }

//    if (url == existingUrl)
//        return;

//    setValue("lastProjectUrl", url);
//    emit lastProjectUrlChanged();
//}

void Settings::resetShortcutsToDefaults()
{
    static QVector<QString> allShortcuts;
    if (allShortcuts.isEmpty()) {
        allShortcuts.append(QLatin1String("quitShortcut"));
    }

    foreach (const QString &shortcut, allShortcuts) {
        remove(shortcut);
    }
}

#define GET_SHORTCUT(shortcutName, defaultValueFunction) \
    return contains(shortcutName) ? value(shortcutName).toString() : defaultValueFunction();

#define SET_SHORTCUT(shortcutName, defaultValueFunction, notifySignal) \
    QVariant existingValue = value(shortcutName); \
    QString existingStringValue = defaultValueFunction(); \
    if (contains(shortcutName)) { \
        existingStringValue = existingValue.toString(); \
    } \
    \
    if (shortcut == existingStringValue) \
        return; \
    \
    setValue(shortcutName, shortcut); \
    emit notifySignal();

QString Settings::defaultQuitShortcut() const
{
    return QKeySequence(QKeySequence::Quit).toString();
}

QString Settings::quitShortcut() const
{
    GET_SHORTCUT("quitShortcut", defaultQuitShortcut)
}
void Settings::setQuitShortcut(const QString &shortcut)
{
    SET_SHORTCUT("quitShortcut", defaultQuitShortcut, quitShortcutChanged)
}
