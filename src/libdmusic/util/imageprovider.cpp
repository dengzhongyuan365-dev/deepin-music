// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "imageprovider.h"
#include <QDebug>
#include <QFileInfo>
#include <QUrl>

MusicImageProvider::MusicImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    qDebug() << "MusicImageProvider created";
}

MusicImageProvider::~MusicImageProvider()
{
    qDebug() << "MusicImageProvider destroyed";
}

QPixmap MusicImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug() << "ImageProvider received id:" << id;
    QString filePath = QUrl::fromPercentEncoding(id.toUtf8());
    qDebug() << "Decoded filePath:" << filePath;
    
    // 如果路径以 file:// 开头，需要转换为本地路径
    if (filePath.startsWith("file://")) {
        QUrl url(filePath);
        filePath = url.toLocalFile();
        qDebug() << "Converted to local file path:" << filePath;
    }
    
    // 直接加载图片，不使用缓存
    QPixmap pixmap;
    qDebug() << "Loading image from:" << filePath;
    qDebug() << "File exists:" << QFileInfo::exists(filePath);
    
    if (QFileInfo::exists(filePath)) {
        pixmap.load(filePath);
        
        if (!pixmap.isNull()) {
            qDebug() << "Successfully loaded image, size:" << pixmap.size();
            
            // 调整大小
            if (requestedSize.isValid()) {
                pixmap = pixmap.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
        } else {
            qDebug() << "Failed to load image from:" << filePath;
        }
    } else {
        qDebug() << "File does not exist:" << filePath;
    }
    
    if (size) {
        *size = pixmap.size();
    }
    
    return pixmap;
}
