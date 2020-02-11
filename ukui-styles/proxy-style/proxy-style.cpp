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

#include "proxy-style.h"
#include <QWidget>
#include "blur-helper.h"

#include <QDebug>

using namespace UKUI;

ProxyStyle::ProxyStyle(const QString &key) : QProxyStyle (key == nullptr? "fusion": key)
{
    m_blur_helper = new BlurHelper;
}

int ProxyStyle::styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    //FIXME:
    switch (hint) {
    case QStyle::SH_Menu_Scrollable: {
        return 1;
    }
    default:
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
}

void ProxyStyle::polish(QWidget *widget)
{
    QProxyStyle::polish(widget);

    //FIXME:
    if(!widget)
        return;

    //qDebug()<<"\n\n\n============widget mask"<<widget->metaObject()->className()<<widget->mask();

    /*!
      \todo
      register transparent widget to blurhelper with better way.
      for now it will let some transparent widget show in error.
      i have to avoid them by limitting widget's class name,
      but that is no my expected.
      */
    if (widget->testAttribute(Qt::WA_TranslucentBackground)) {
        if (QString(widget->metaObject()->className())=="QMenu" ||
                widget->inherits("Peony::DirectoryViewMenu") ||
                widget->inherits("Peony::DesktopMenu")) {
            m_blur_helper->registerWidget(widget);
        }
    }

    //qDebug()<<widget->metaObject()->className();
    //add exception.
}

void ProxyStyle::unpolish(QWidget *widget)
{
    //FIXME:
    QProxyStyle::unpolish(widget);
}

void ProxyStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}
