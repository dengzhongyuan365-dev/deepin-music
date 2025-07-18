// Copyright (C) 2020 ~ 2020 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "shaderimageview.h"
#include "util/log.h"

#include <QPainter>
#include <qmath.h>
#include <presenter.h>
#include <QPainterPath>

ShaderImageView::ShaderImageView(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    qCDebug(dmMusic) << "ShaderImageView constructor";
    m_source = QString();
}

ShaderImageView::~ShaderImageView()
{
    qCDebug(dmMusic) << "ShaderImageView destructor";
}

QString ShaderImageView::source() const
{
    qCDebug(dmMusic) << "ShaderImageView source: " << m_source;
    return m_source;
}

void ShaderImageView::setSource(const QString &source)
{
    qCDebug(dmMusic) << "ShaderImageView setSource: " << source;

    m_source = source;
    emit sourceChanged();
}

QVariant ShaderImageView::presenter() const
{
    qCDebug(dmMusic) << "ShaderImageView presenter";
    return QVariant();
}

void ShaderImageView::setPresenter(const QVariant &presenter)
{
    qCDebug(dmMusic) << "ShaderImageView setPresenter";
    m_pPresenter = presenter;
    Presenter *pres = NULL;
    if (m_pPresenter.canConvert<Presenter *>()) { //判断防止空指针
        pres = m_pPresenter.value<Presenter *>();
        if (pres->getActivateMetImage().isNull()) {
            qCDebug(dmMusic) << "ShaderImageView setPresenter: getActivateMetImage is null";
            pres->setEffectImage(QImage(":/dsg/img/test.jpg"));
        } else {
            qCDebug(dmMusic) << "ShaderImageView setPresenter: getActivateMetImage is not null";
            pres->setEffectImage(pres->getActivateMetImage());
        }
    }
    emit presenterChanged();
    qCDebug(dmMusic) << "ShaderImageView setPresenter: presenterChanged";
}



void ShaderImageView::paint(QPainter *painter)
{
    Presenter *presenter = NULL;
    if (m_pPresenter.canConvert<Presenter *>()) { //判断防止空指针
        presenter = m_pPresenter.value<Presenter *>();
    }
    QPainterPath path_fill, path_Opacity, path_Image;


    //填充
    int nWidth = 0;
    QRect rect;
    if (m_source != "noedgeimage") {
        nWidth += 10;
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
        path_fill.addEllipse(nWidth, nWidth, width() - nWidth * 2, height() - nWidth * 2);
        painter->setClipPath(path_fill);
        painter->setOpacity(0.4);
        painter->fillPath(path_fill, Qt::white);
        painter->restore();

        nWidth += 10;
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
        path_Opacity.addEllipse(nWidth, nWidth, width() - nWidth * 2, height() - nWidth * 2);
        painter->setClipPath(path_Opacity);
        painter->setOpacity(0.4);
        rect = QRect(nWidth, nWidth, static_cast<int>(width() - 2 * nWidth), static_cast<int>(height() - 2 * nWidth));
        if (presenter) {
            QImage img = presenter->getEffectImage();
            painter->drawImage(rect, img, QRect(0, 0, img.width(), img.height()));
        }
        painter->restore();
    }
    //绘图
    nWidth += 10;
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
    path_Image.addEllipse(nWidth, nWidth, width() - nWidth * 2, height() - nWidth * 2);
    painter->setClipPath(path_Image);
    rect = QRect(nWidth, nWidth, static_cast<int>(width() - 2 * nWidth), static_cast<int>(height() - 2 * nWidth));
    if (presenter) {
        QImage img = presenter->getEffectImage();
        painter->drawImage(rect, img, QRect(0, 0, img.width(), img.height()));
    }
    painter->restore();
}
