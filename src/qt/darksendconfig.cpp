#include "darksendconfig.h"
#include "ui_darksendconfig.h"

#include "guiutil.h"
#include "bitcoinunits.h"
#include "guiconstants.h"
#include "optionsmodel.h"
#include "privatesend-client.h"
#include "walletmodel.h"

#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>
#include <QSettings>

DarksendConfig::DarksendConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DarksendConfig),
    model(0)
{
    ui->setupUi(this);

    // set the typography correctly
    QString fontType = GUIUtil::getFontType();
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    for (int i = 0; i < widgets.length(); i++){
        widgets.at(i)->setFont(QFont(fontType,13, 1, false));
    }

    connect(ui->buttonBasic, SIGNAL(clicked()), this, SLOT(clickBasic()));
    connect(ui->buttonHigh, SIGNAL(clicked()), this, SLOT(clickHigh()));
    connect(ui->buttonMax, SIGNAL(clicked()), this, SLOT(clickMax()));
}

DarksendConfig::~DarksendConfig()
{
    delete ui;
}

void DarksendConfig::setModel(WalletModel *model)
{
    this->model = model;
}

void DarksendConfig::clickBasic()
{
    configure(true, 100000, 2);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 100000 * COIN));
    QMessageBox::information(this, tr("PrivatePAC Configuration"),
        tr(
            "PrivatePAC was successfully set to basic (%1 and 2 rounds). You can change this at any time by opening $PAC's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void DarksendConfig::clickHigh()
{
    configure(true, 100000, 8);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 100000 * COIN));
    QMessageBox::information(this, tr("PrivatePAC Configuration"),
        tr(
            "PrivatePAC was successfully set to high (%1 and 8 rounds). You can change this at any time by opening $PAC's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void DarksendConfig::clickMax()
{
    configure(true, 100000, 16);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 100000 * COIN));
    QMessageBox::information(this, tr("PrivateSend Configuration"),
        tr(
            "PrivatePAC was successfully set to maximum (%1 and 16 rounds). You can change this at any time by opening $PAC's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void DarksendConfig::configure(bool enabled, int coins, int rounds) {

    QSettings settings;

    settings.setValue("nPrivatePACRounds", rounds);
    settings.setValue("nPrivatePACAmount", coins);

    privateSendClient.nPrivateSendRounds = rounds;
    privateSendClient.nPrivateSendAmount = coins;
}
