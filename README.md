# Qt5 Systray

基于QT5的系统状态栏托盘图标Demo程序，适用于UOS、Windows。

## 1. 增加图标资源文件

这次Demo使用的图标如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/52c54c5be5724d418fad6665eba618cc.png#pic_center)


首先将图标文件复制到项目根目录下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/56d600305d064b5d988cf317cb6dc057.png)

右键 项目，点击**Add New**
![在这里插入图片描述](https://img-blog.csdnimg.cn/14eb6985b424487a9d85fe7cf26524e3.png)
选择 **Qt**，**Qt Resource File** 点击**Choose**
![在这里插入图片描述](https://img-blog.csdnimg.cn/5925e1d7304b41518750d20ea3d7ca10.png)
命名为 `icon`，点击**下一步**，直到完成。
![在这里插入图片描述](https://img-blog.csdnimg.cn/320695ec80cb4f78823fb696b0c96cbd.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/5faa30f25d15443ba424bf0caa5a8c19.png)
> 该步骤完成后会向`helloworld.pro`文件中添加`RESOURCES` 配置信息。


完成后项目目录中会增加一个**Resources目录**，右键点击该目录，点击**添加现有文件**
![在这里插入图片描述](https://img-blog.csdnimg.cn/fd513d130ba4414d96d5cdae4101913f.png)
选择我们的icon文件并点击打开。
![在这里插入图片描述](https://img-blog.csdnimg.cn/f846775dd31f483dbc380edc7ad6a5a8.png)

可以看到我们文件位于`/`目录下，在需要使用到该资源的地方通过`:/文件名`的形式就可以取到文件路径，如:`:/icon.png`

## 2. 修改配置文件
本次只需要显示系统状态栏图标仅需使用`libqtwidget`相关API，我们采用简单的一个main函数来完成所有功能，因此那其他文件都给删除。

修改后的**helloworld.pro**内容如下所示：
```c
QT       += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp

HEADERS += \

RESOURCES += \
    icon.qrc
```

由于没有其他的文件所以头文件这边也为空，修改保存之后，项目会自动更新项目结构。
![在这里插入图片描述](https://img-blog.csdnimg.cn/be4c476720554f2b9321ca0adaa5f661.png)

此时项目中只有`main.cpp`和资源文件。

## 3 程序主体

**main.cpp**程序如下：

```c++
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

// 打开点击事件处理器
void handleOpen(){
    qDebug(">> Open button clicked!");
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
    // 退出按钮的处理函数会终止程序的运行
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
```

1. 创建右键菜单，并注册并绑定事件处理器。
2. 加载图标。
3. 创建系统状态栏对象并配置。

完成编写后启动运行程序，可以在右下角看到程序启动的系统状态栏图标，对图标点击右键可以弹出菜单。

![在这里插入图片描述](https://img-blog.csdnimg.cn/5cbc7fc96a9043f8a7580a8344df9933.png)
点击打开，可以在控制台看到回调函数打印信息。

![在这里插入图片描述](https://img-blog.csdnimg.cn/5bbd1b98014145cebbfad5633c47ef79.png)

## 参考文献

[1]. [github . QtExamples .  XMuli . https://github.com/xmuli/QtExamples](https://github.com/xmuli/QtExamples)

[2]. [stackoverflow . How to write QT system tray app without a window class, and integrate it with another process? . Kevin Krammer . 2017.01  . https://stackoverflow.com/questions/41780618/how-to-write-qt-system-tray-app-without-a-window-class-and-integrate-it-with-an](https://stackoverflow.com/questions/41780618/how-to-write-qt-system-tray-app-without-a-window-class-and-integrate-it-with-an)

[3]. [C语言中文网 . Qt教程 . http://c.biancheng.net/qt/](http://c.biancheng.net/qt/)
