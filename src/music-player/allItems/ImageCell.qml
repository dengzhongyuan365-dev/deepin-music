// Copyright (C) 2022 UnionTech Technology Co., Ltd.
// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.11
import QtQuick.Controls 2.4
import audio.global 1.0
import org.deepin.dtk 1.0

Rectangle {
    id: control
    property string source: ""  // 接收外部传入的路径
    property bool m_isPlaying: (globalVariant.curPlayingStatus === DmGlobal.Playing) ? true : false
    signal clicked
    property string pageHash: ""
    property bool isCurPlay: false
    property bool isCurHover: false
    property var curMediaData
    
    // 新增：原始文件路径属性
    property string filePath: ""

    width: 40; height: 40
    color: "transparent"

    Image {
        id: image
        width: parent.width; height: parent.height
        visible: false
        smooth: true
        antialiasing: true
<<<<<<< Updated upstream
=======
        cache: false
        
        // 关键修改：自动将file://路径转换为ImageProvider调用
        source: {
            if (control.source && control.source !== "") {
                // 如果是qrc资源，直接使用
                if (control.source.startsWith("qrc:")) {
                    return control.source;
                }
                // 如果是file://路径，转换为ImageProvider调用
                else if (control.source.startsWith("file://")) {
                    var cleanPath = control.source.replace("file:///", "");
                    return "image://musiccover/" + encodeURIComponent(cleanPath);
                }
                // 如果是普通路径，也转换为ImageProvider调用
                else {
                    return "image://musiccover/" + encodeURIComponent(control.source);
                }
            }
            return "qrc:/dsg/img/no_music.svg";
        }
        
        onStatusChanged: {
            if (status === Image.Error) {
                // 加载失败时使用默认图片
                source = "qrc:/dsg/img/no_music.svg";
            }
        }
        
>>>>>>> Stashed changes
        Rectangle {
            id: curMask
            anchors.fill: parent
            color: isCurPlay || isCurHover ? Qt.rgba(0, 0, 0, 0.5) : Qt.rgba(0, 0, 0, 0)
        }
    }
    Rectangle {
        id: mask
        anchors.fill: parent
        radius: 3
        visible: false
    }
    OpacityMask {
        anchors.fill: parent
        source: image
        maskSource: mask
    }

    // border
    Rectangle {
        id: borderRect
        anchors.fill: parent
        color: "transparent"
        border.color: Qt.rgba(0, 0, 0, 0.1)
        border.width: 1
        visible: true
        radius: 3
    }

    ActionButton {
        id: playActionButton
        anchors.centerIn: image
        icon.name: globalVariant.playingIconName
        icon.width: 20
        icon.height: 20
        visible: control.isCurPlay
        palette.windowText: "white"
        onClicked:{
            if(control.m_isPlaying && control.isCurPlay){
                icon.name = "list_play"
                Presenter.pause();
            }else{
                icon.name = "list_pussed"
                if(control.pageHash === "album"){
                    Presenter.playAlbum(curMediaData.name);
                }else if(control.pageHash === "artistSublist"){
                    Presenter.playArtist(curMediaData.artist, curMediaData.hash);
                }else if(control.pageHash === "fav"){
                    Presenter.playPlaylist(pageHash, curMediaData.hash);
                }else if(control.pageHash === "play"){
                    if(globalVariant.curPlayingHash !== curMediaData.hash)
                        Presenter.setActivateMeta(curMediaData.hash)
                    Presenter.play()
                }else{
                    Presenter.playPlaylist(control.pageHash, curMediaData.hash);
                }
            }
       }
    }

    function itemHoveredChanged(value) {
        if(value === true){
            playActionButton.visible = true;
            if(control.m_isPlaying && control.isCurPlay){
                playActionButton.icon.name = "list_pussed";
            }else{
                playActionButton.icon.name = "list_play";
            }
        } else {
            playActionButton.visible = control.isCurPlay;
            playActionButton.icon.name = Qt.binding(function(){return globalVariant.playingIconName});
            return;
        }
    }
    function setplayActionButtonIcon(value){playActionButton.icon.name = value}
    onIsCurPlayChanged: {
        playActionButton.visible = control.isCurPlay
    }
}
