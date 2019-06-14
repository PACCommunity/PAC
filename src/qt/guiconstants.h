// Copyright (c) 2011-2015 The Bitcoin Core developers
// Copyright (c) 2014-2018 The Dash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <QColor>

#ifndef BITCOIN_QT_GUICONSTANTS_H
#define BITCOIN_QT_GUICONSTANTS_H

/* Milliseconds between model updates */
static const int MODEL_UPDATE_DELAY = 250;

/* AskPassphraseDialog -- Maximum passphrase length */
static const int MAX_PASSPHRASE_SIZE = 1024;

/* PACGUI -- Size of icons in status bar */
static const int STATUSBAR_ICONSIZE = 16;

static const bool DEFAULT_SPLASHSCREEN = true;

/* Invalid field background style */
#define STYLE_INVALID "background:#FF8080"

/* Transaction list -- unconfirmed transaction */
#define COLOR_UNCONFIRMED QColor(128, 128, 128)
/* Transaction list -- negative amount */
#define COLOR_NEGATIVE QColor(223,31,56)
/* Transaction list -- bare address (without label) */
#define COLOR_BAREADDRESS QColor(140, 140, 140)
/* Transaction list -- TX status decoration - open until date */
#define COLOR_TX_STATUS_OPENUNTILDATE QColor(64, 64, 255)
/* Transaction list -- TX status decoration - offline */
#define COLOR_TX_STATUS_OFFLINE QColor(192, 192, 192)
/* Transaction list -- TX status decoration - danger, tx needs attention */
#define COLOR_TX_STATUS_DANGER QColor(200, 100, 100)

/* Transaction list -- TX status decoration - LockedByInstantSend color */
#define COLOR_TX_STATUS_LOCKED QColor(0, 128, 255)
/* Transaction list -- TX status decoration - positive tansactions color */
#define COLOR_POSITIVE QColor(46,222,95)
/* Transaction list -- TX status decoration - default color */
#define COLOR_BLACK QColor(20,20,20)
#define COLOR_WHITE QColor(255,255,255)

/* Color of the general text */
static QColor COLOR_TEXT = QColor(128,128,128);

/* Tooltips longer than this (in characters) are converted into rich text,
   so that they can be word-wrapped.
 */
static const int TOOLTIP_WRAP_THRESHOLD = 80;

/* Maximum allowed URI length */
static const int MAX_URI_LENGTH = 255;

/* QRCodeDialog -- size of exported QR Code image */
#define QR_IMAGE_SIZE 256

/* Number of frames in spinner animation */
#define SPINNER_FRAMES 36

#define QAPP_ORG_NAME "PAC"
#define QAPP_ORG_DOMAIN "paccoin.org"
#define QAPP_APP_NAME_DEFAULT "Paccoin-Qt"
#define QAPP_APP_NAME_TESTNET "Paccoin-Qt-testnet"
#define QAPP_APP_NAME_DEVNET "Paccoin-Qt-%s"

#endif // BITCOIN_QT_GUICONSTANTS_H
