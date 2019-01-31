// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PRIVATEPAGE_H
#define BITCOIN_QT_PRIVATEPAGE_H

#include "amount.h"

#include <QWidget>
#include <memory>

class ClientModel;
class TransactionFilterProxy;
class TxViewDelegate;
class PlatformStyle;
class WalletModel;

namespace Ui {
    class PrivatePage;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Overview ("home") page widget */
class PrivatePage : public QWidget
{
    Q_OBJECT

public:
    explicit PrivatePage(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~PrivatePage();

    void setClientModel(ClientModel *clientModel);
    void setModel(WalletModel *walletModel);
    void showOutOfSyncWarning(bool fShow);

public Q_SLOTS:
    void privateSendStatus();
    void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& anonymizedBalance,
                    const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);

Q_SIGNALS:
    void outOfSyncWarningClicked();

private:
    QTimer *timer;
    Ui::PrivatePage *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;
    CAmount currentBalance;
    CAmount currentAnonymizedBalance;
    CAmount currentUnconfirmedBalance;
    CAmount currentImmatureBalance;
    CAmount currentWatchOnlyBalance;
    CAmount currentWatchUnconfBalance;
    CAmount currentWatchImmatureBalance;
    int nDisplayUnit;
    bool fShowAdvancedPSUI;

    TxViewDelegate *txdelegate;

    void DisablePrivateSendCompletely();

private Q_SLOTS:
    void togglePrivateSend();
    void privateSendAuto();
    void privateSendReset();
    void privateSendInfo();
    void updateDisplayUnit();
    void updatePrivateSendProgress();
    void updateAdvancedPSUI(bool fShowAdvancedPSUI);
    void updateAlerts(const QString &warnings);
    void handleOutOfSyncWarningClicks();
};

#endif // BITCOIN_QT_PRIVATEPAGE_H
