/*
 * Copyright (C) 2016 ~ 2018 Wuhan Deepin Technology Co., Ltd.
 *
 * Author:     Iceyer <me@iceyer.net>
 *
 * Maintainer: Iceyer <me@iceyer.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <DListView>

#include "../../core/playlist.h"

DWIDGET_USE_NAMESPACE

class MusicListInfoViewPrivate;
class MusicListInfoView : public QListView
{
    Q_OBJECT
public:
    explicit MusicListInfoView(QWidget *parent = Q_NULLPTR);
    ~MusicListInfoView() override;

    MetaPtr activingMeta() const;
    MetaPtr firstMeta() const;
    PlaylistPtr playlist() const;
    QModelIndex findIndex(const MetaPtr meta);
    QString curName() const;
    void setPlaying(const MetaPtr meta);
    MetaPtr playing() const;

    void setThemeType(int type);
    int getThemeType() const;

    void setPlayPixmap(QPixmap pixmap, QPixmap sidebarPixmap);
    QPixmap getPlayPixmap() const;
    QPixmap getSidebarPixmap() const;

    QStringList allMetaNames() const;

signals:
    void addToPlaylist(PlaylistPtr playlist, const MetaPtrList &metalist);
    void removeMusicList(const MetaPtrList  &metalist);
    void deleteMusicList(const MetaPtrList  &metalist);
    void playMedia(const MetaPtr meta);
    void resume(const MetaPtr meta);
    void updateMetaCodec(const MetaPtr meta);
    void showInfoDialog(const MetaPtr meta);
    void requestCustomContextMenu(const QPoint &pos);
    void customSort();
    void pause(const MetaPtr meta);
    void addMetasFavourite(const MetaPtrList  &metalist);
    void removeMetasFavourite(const MetaPtrList  &metalist);

public:
    void onMusiclistChanged(PlaylistPtr playlist, const QString name);
    void onMusicListAdded(const MetaPtrList metalist);
    void onMusicListRemoved(const MetaPtrList metalist);
    void onMusicError(const MetaPtr meta, int error);
    void onLocate(const MetaPtr meta);
    void showContextMenu(const QPoint &pos,
                         PlaylistPtr selectedPlaylist,
                         PlaylistPtr favPlaylist,
                         QList<PlaylistPtr > newPlaylists);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    virtual void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual void keyboardSearch(const QString &search) Q_DECL_OVERRIDE;

private:
    QScopedPointer<MusicListInfoViewPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), MusicListInfoView)

};
