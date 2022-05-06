#include <QApplication>
#include <QMenu>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QtGlobal>
#include <QDesktopServices>
#include <QUrl>


// 打开点击事件处理器
void handleOpen(){
    qDebug(">> Open button clicked!");
    QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建右键菜单
    QMenu menu;
    QAction openAct("打开");
    QAction  quitAct("退出");

    menu.addAction(&openAct);
    menu.addAction(&quitAct);
    // 菜单绑定事件回调
    QObject::connect(&quitAct, &QAction::triggered, qApp, &QCoreApplication::quit);
    QObject::connect(&openAct, &QAction::triggered, qApp, &handleOpen);

    // 加载图标
    QPixmap oPixmap(32, 32);
    oPixmap.load(":/icon.png");
    QIcon qIcon(oPixmap);

    // 创建并配置状态栏icon
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(qIcon);
    trayIcon->setContextMenu(&menu);
    trayIcon->setToolTip("Some thing");
    trayIcon->setVisible(true);
    // 消息提示
    // trayIcon->showMessage("Test Message", "Text", QSystemTrayIcon::Information, 3000);

    return a.exec();
}
