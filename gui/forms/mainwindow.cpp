#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/driveengine.h"
#include "share/debug.h"
#include "share/registration.h"
#include "settings/settingsmanager.h"
#include "gui/forms/authdialog.h"
#include <QTextCodec>
#include <QKeyEvent>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    SUi::inst()->setupUi(this);

}

MainWindow::~MainWindow()
{
    SDriveEngine::freeInst();
    SUi::freeInst();
    SQueries::freeInst();
}

void MainWindow::init(void)
{
    if(!CheckUI().checkReg())
    {
        CommonTools::msg(tr("You need to register the application in <a href=\"https://code.google.com/apis/console/\">API Console - Google Code</a>"));
        //return;
    }

    SDriveEngine::inst(this)->init();
    SDriveEngine::inst()->getCheckUI()->slotCheckWorkDir(false);

    setConnections();

    SDriveEngine::inst()->getFilePanel(ELeft)->getFileView()->installEventFilter(this);
    SDriveEngine::inst()->getFilePanel(ERight)->getFileView()->installEventFilter(this);

    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    //SDriveEngine::inst()->getFilePanel(ELeft)->getFileView()->header()->setClickable(true);
    //SDriveEngine::inst()->getFilePanel(ERight)->getFileView()->header()->setClickable(true);

    SDriveEngine::inst()->getFilePanel(ELeft)->getFileView()->header()->resizeSection(0, 250);
    SDriveEngine::inst()->getFilePanel(ERight)->getFileView()->header()->resizeSection(0, 250);
}

void MainWindow::setConnections(void)
{
    connect(SUi::inst()->actionLogin, SIGNAL(triggered()), this, SLOT(slotAuthDialog()));
    connect(SUi::inst()->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(SUi::inst()->actionDownload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotDownload()));
    connect(SUi::inst()->actionUpload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotUpload()));
    connect(SUi::inst()->actionSettings, SIGNAL(triggered()), SDriveEngine::inst()->getCheckUI(), SLOT(slotCheckWorkDir()));
    connect(SUi::inst()->actionDelete, SIGNAL(triggered()), SDriveEngine::inst()->getOpUI(), SLOT(slotTriggeredDel()));
    connect(SUi::inst()->actionNewFolder, SIGNAL(triggered()), SDriveEngine::inst()->getOpUI(), SLOT(slotNewFolder()));
    connect(SUi::inst()->copyButton, SIGNAL(clicked()), SDriveEngine::inst()->getOpUI(), SLOT(slotCopyWebFile()));
    connect(SUi::inst()->moveButton, SIGNAL(clicked()), SDriveEngine::inst()->getOpUI(), SLOT(slotMoveWebFile()));
    connect(SUi::inst()->newFolderButton, SIGNAL(clicked()), SDriveEngine::inst()->getOpUI(), SLOT(slotNewFolder()));
    connect(SUi::inst()->deleteButton, SIGNAL(clicked()), SDriveEngine::inst()->getOpUI(), SLOT(slotTriggeredDel()));
    connect(SUi::inst()->renameButton, SIGNAL(clicked()), SDriveEngine::inst()->getOpUI(), SLOT(slotRenameWebFile()));
    connect(SUi::inst()->shareButton, SIGNAL(clicked()), SDriveEngine::inst()->getOpUI(), SLOT(slotShareWebFile()));
    connect(SDriveEngine::inst()->getFilePanel(ELeft)->getFileView(), SIGNAL(clicked(const QModelIndex&)), SDriveEngine::inst()->getfilesUI(), SLOT(slotLeftViewClicked(const QModelIndex&)));
    connect(SDriveEngine::inst()->getFilePanel(ERight)->getFileView(), SIGNAL(clicked(const QModelIndex&)), SDriveEngine::inst()->getfilesUI(), SLOT(slotRightViewClicked(const QModelIndex&)));
    connect(SDriveEngine::inst()->getFilePanel(ELeft)->getFileView(), SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SDriveEngine::inst()->getfilesUI(), SLOT(slotLeftPanelItemDoubleClicked(QTreeWidgetItem*, int)));
    connect(SDriveEngine::inst()->getFilePanel(ERight)->getFileView(), SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SDriveEngine::inst()->getfilesUI(), SLOT(slotRightPanelItemDoubleClicked(QTreeWidgetItem*, int)));
    connect(SDriveEngine::inst()->getFilePanel(ELeft)->getFileView()->header(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), SDriveEngine::inst()->getfilesUI(), SLOT(slotLeftSortIndicatorChanged(int, Qt::SortOrder)));
    connect(SDriveEngine::inst()->getFilePanel(ERight)->getFileView()->header(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), SDriveEngine::inst()->getfilesUI(), SLOT(slotRightSortIndicatorChanged(int, Qt::SortOrder)));
    connect(SDriveEngine::inst()->getFilesMngr()->self(), SIGNAL(signalAccessTokenRequired()), this, SLOT(slotAccessTokenRequired()));
    connect(SDriveEngine::inst()->getFilesMngr(true)->self(), SIGNAL(signalAccessTokenRequired()), this, SLOT(slotAccessTokenRequired()));
    connect(SDriveEngine::inst()->getFilesMngr(), SIGNAL(signalFirstPanelIsLoaded()), SDriveEngine::inst(), SLOT(slotFirstPanelIsLoaded()));
    connect(SQueries::inst(), SIGNAL(signalAccountInfoReadyToUse()), this, SLOT(slotAccountInfoReadyToUse()));
}

void MainWindow::slotAuthDialog(void)
{
    AuthDialog authDialog(SUi::inst()->centralWidget);    
    connect(&authDialog, SIGNAL(signalTokens(const QString&, const QString&)), this, SLOT(slotTokens(const QString&, const QString&)));
    authDialog.exec();
}

void MainWindow::slotTokens(const QString &accessToken, const QString &refreshToken)
{
    SQueries::inst()->setAccountInfo(accessToken, refreshToken);
}

void MainWindow::slotAccountInfoReadyToUse(void)
{
    SDriveEngine::inst()->updatePanel(LEFT_PANEL_VALUE, true);
}

void MainWindow::slotAccessTokenRequired(void)
{
    DEBUG << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    auth = new Auth;

    SettingsManager settingsManager;

    QString id, secret, uri;
    id =  settingsManager.getValueFromGroup(COMMON_GROUP, CLIENT_ID_KEY, "").toString();
    secret =  settingsManager.getValueFromGroup(COMMON_GROUP, CLIENT_SECRET_KEY, "").toString();
    uri =  settingsManager.getValueFromGroup(COMMON_GROUP, REDIRECT_URI_KEY, "").toString();

    auth->getAccessToken(id, secret, SettingsManager().refreshToken());
    connect(auth, SIGNAL(signalAuthResponse(const QString&)), this, SLOT(slotAuthResponse(const QString&)));
}

void MainWindow::slotAuthResponse(const QString &accessToken)
{
    DEBUG << "-----------------------------------> accessToken" << accessToken;

    SQueries::inst()->setAccountInfo(accessToken);
    auth->deleteLater();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    return SDriveEngine::inst()->getEventHandler()->event(object, event);
}


