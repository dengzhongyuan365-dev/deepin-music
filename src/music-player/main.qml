// Copyright (C) 2020 ~ 2020 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import org.deepin.dtk 1.0
import "./mainwindow"

// 简化版，只加载Toolbar和Titlebar用于内存测试
ApplicationWindow {
    property Item globalVariant: GlobalVariant{}
    property bool isLyricShow : false
    property bool isPlaylistShow : false
    property int windowMiniWidth: 1070
    property int windowMiniHeight: 680
    
    id: rootWindow
    visible: true
    minimumWidth: windowMiniWidth
    minimumHeight: windowMiniHeight
    width: windowMiniWidth
    height: windowMiniHeight
    DWindow.enabled: true
    DWindow.alphaBufferSize: 8
    flags: Qt.Window | Qt.WindowMinMaxButtonsHint | Qt.WindowCloseButtonHint | Qt.WindowTitleHint
    
    // 保留titlebar
    header: WindowTitlebar { id: musicTitle }
    
    // 保留背景
    background: Rectangle {
        anchors.fill: parent
        color: "transparent"
        Row {
            anchors.fill: parent
            BehindWindowBlur {
                id: leftBgArea
                width: 220
                height: parent.height
                anchors.top: parent.top
                blendColor: DTK.themeType === ApplicationHelper.LightType ? "#bbf7f7f7" : "#dd252525"
                Rectangle {
                    width: 1
                    height: parent.height
                    anchors.right: parent.right
                    color: DTK.themeType === ApplicationHelper.LightType ? "#eee7e7e7" : "#ee252525"
                }
            }
            Rectangle {
                id: rightBgArea
                width: parent.width - leftBgArea.width
                height: 50
                anchors.top: parent.top
                color: Qt.rgba(0, 0, 0, 0.01)
            }
        }
    }

    // 中间区域留空
    Rectangle {
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.bottomMargin: 90
        color: "transparent"
    }
    
    // 保留Toolbar
    Toolbar {
        id: toolbox
        width: parent.width
        z: 10
    }
    
    Component.onCompleted: {
        console.log("==== 简化版音乐播放器启动：仅加载Toolbar和Titlebar ====")
    }
}
