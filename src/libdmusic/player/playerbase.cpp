// Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "playerbase.h"
#include "../util/log.h"

PlayerBase::PlayerBase(QObject *parent)
    : QObject(parent)
{
    qCDebug(dmMusic) << "PlayerBase initialized";
}
