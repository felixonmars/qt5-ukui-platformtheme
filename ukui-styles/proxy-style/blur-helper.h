/*
 * Qt5-UKUI's Library
 *
 * Copyright (C) 2020, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#ifndef BLURHELPER_H
#define BLURHELPER_H

#include <QObject>
#include <QTimer>

class BlurHelper : public QObject
{
    Q_OBJECT
public:
    explicit BlurHelper(QObject *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *e);
    void registerWidget(QWidget *widget);
    void unregisterWidget(QWidget *widget);

    bool isApplicationInBlackList();
    const QStringList blackList();

    bool shouldSkip(QWidget *w);

signals:

public slots:
    void onBlurEnableChanged(bool enable);
    void onWidgetDestroyed(QWidget *widget);
    void delayUpdate(QWidget *w);

private:
    QList<QWidget *> m_blur_widgets;

    QList<QWidget *> m_update_list;
    QTimer m_timer;
};

#endif // BLURHELPER_H
