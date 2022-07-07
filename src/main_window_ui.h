#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H
#include <QAction>
#include <QString>
#include <QPushButton>
#include <QTabBar>
#include <QMainWindow>
#include <QMenu>
#include <QGraphicsBlurEffect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QSizePolicy>
#include <QFrame>
#include <QShortcut>

const QString BUTTON_QSS{
R"(QPushButton {
    font-family: Segoe MDL2 Assets;
    font-size: 13px;
    text-align: center center;
    border: none;
    border-radius: 5px;
    background-color: rgb(232, 232, 232);
    min-width: 28px;
    max-width: 28px;
    min-height: 28px;
    max-height: 28px;
}
QPushButton::menu-indicator { image: none; }
QPushButton:hover { background-color: rgb(180, 180, 180); })"};

const QString TAB_BAR_QSS(
R"(
QTabBar::tab {
    height: 26px;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
    border: none;
    background: rgb(232, 232, 232);
    font-size: 13px;
    text-align: center center;
}
QTabBar::tab:selected, QTabBar::tab:hover {
    border: 1px solid #C4C4C3;
    background: white;
}
QTabBar::close-button { image: url(:/pics/close.svg) }
QTabBar::close-button:hover { image: url(:/pics/close_hover.svg) }
)");

class MainWindowUI
{
public:
    QWidget *central_widget;

    QAction *action_new;
    QAction *action_save;
    QAction *action_save_as;
    QAction *action_close_current;
    QAction *action_open;

    QPushButton *file_menu_btn;
    QPushButton *new_document_btn;
    QTabBar *tab_bar;

    QFrame *h_line;

    QPlainTextEdit *editor;
    QWebEngineView *previewer;

    QVBoxLayout *main_view;
    QHBoxLayout *main_bar;
    QHBoxLayout *preview_view;
    QMenu *file_menu;

    MainWindowUI(QMainWindow *main_window):
        central_widget{new QWidget(main_window)},

        action_new{new QAction(main_window)},
        action_save{new QAction(main_window)},
        action_save_as{new QAction(main_window)},
        action_close_current{new QAction(main_window)},
        action_open{new QAction(main_window)},

        file_menu_btn{new QPushButton(central_widget)},
        new_document_btn{new QPushButton(central_widget)},
        tab_bar{new QTabBar(central_widget)},

        h_line{new QFrame(central_widget)},

        editor{new QPlainTextEdit(central_widget)},
        previewer{new QWebEngineView(central_widget)},

        main_view{new QVBoxLayout(central_widget)},
        main_bar{new QHBoxLayout()},
        preview_view{new QHBoxLayout()},
        file_menu{new QMenu(file_menu_btn)},

        ef{new QGraphicsBlurEffect}
    {
        main_window->resize(800, 600);
        main_window->setCentralWidget(central_widget);
        main_window->setWindowTitle("HomoDark");
        main_window->setWindowIcon(QIcon(":/pics/logo.svg"));

        central_widget->setStyleSheet(QStringLiteral("QWidget { background: rgb(232, 232, 232); }"));

        action_new->setText(QStringLiteral("新建文档"));
//        action_new->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
        action_new->setIcon(QIcon(":/pics/file-add-line.svg"));

        action_open->setText(QStringLiteral("打开"));
//        action_open->setShortcut(Qt::CTRL | Qt::Key_O);
        action_open->setIcon(QIcon(":/pics/folder-5-line.svg"));

        action_save->setText(QStringLiteral("保存"));
//        action_save->setShortcut(Qt::CTRL | Qt::Key_S);
        action_save->setIcon(QIcon(":/pics/save-3-line.svg"));

        action_save_as->setText(QStringLiteral("另存为..."));

        action_close_current->setText(QStringLiteral("关闭当前文档"));
//        action_close_current->setShortcut(Qt::CTRL | Qt::Key_W);
        action_close_current->setIcon(QIcon(":/pics/close-circle-fill.svg"));

        file_menu->addActions({action_new, action_open, action_save, action_save_as, action_close_current});

        file_menu_btn->setText("\uea37");
        file_menu_btn->setStyleSheet(BUTTON_QSS);

        new_document_btn->setText("\ue710");
        new_document_btn->setStyleSheet(BUTTON_QSS);

        tab_bar->setTabsClosable(true);
        tab_bar->setMovable(true);
        tab_bar->setFixedHeight(28);
        tab_bar->setStyleSheet(TAB_BAR_QSS);
        tab_bar->setMovable(false);

        main_bar->setContentsMargins(0, 0, 0, 0);

        h_line->setFrameShape(QFrame::HLine);
        h_line->setFrameShadow(QFrame::Plain);

        main_bar->addWidget(file_menu_btn);
        main_bar->addWidget(tab_bar);
        main_bar->addWidget(new_document_btn);

        editor->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        editor->setStyleSheet("QPlainTextEdit { background: white; }");
        QFont font;
        font.setFamilies({QString("Source Code Variable Medium"), QString("微软雅黑")});
        font.setPointSize(12);
        font.setStyleStrategy(QFont::PreferAntialias);
        editor->setFont(font);

        previewer->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

        preview_view->addWidget(editor);
        preview_view->addWidget(previewer);

        main_view->setSpacing(0);
        main_view->setContentsMargins(0, 0, 0, 0);
        main_view->addLayout(main_bar);
        main_view->addWidget(h_line);
        main_view->addLayout(preview_view);
        main_view->setStretch(0, 0);

        file_menu->setWindowFlags(file_menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        file_menu->setAttribute(Qt::WA_TranslucentBackground);
        file_menu->setStyleSheet(
R"(
QMenu {
    color: black;
    background-color: white;
    border: 1px solid rgb(125,125,125);
    border-radius: 5px;
    padding: 5px;
}
QMenu::item {
    padding: 3px 5px;
    margin: 5px 5px;
}
QMenu::item:selected {
    color: rgb(26, 163, 255);
    background-color: rgb(229, 245, 255);
    border-radius: 5px;
}
)");

        ef->setBlurRadius(8);
        ef->setBlurHints(QGraphicsBlurEffect::AnimationHint);
        ef->setEnabled(false);
        main_window->setGraphicsEffect(ef);
    }

    void blur() { ef->setEnabled(true); }

    void clean_blur() { ef->setEnabled(false); }

private:
    QGraphicsBlurEffect *ef;
};
#endif // MAIN_WINDOW_UI_H
