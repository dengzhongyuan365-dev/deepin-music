// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QObject>
#include <QtQuick/QQuickImageProvider>
#include <QPixmap>
#include <QFileInfo>

class MusicImageProvider : public QQuickImageProvider
{
public:
    explicit MusicImageProvider();
    ~MusicImageProvider();
    
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // IMAGEPROVIDER_H 