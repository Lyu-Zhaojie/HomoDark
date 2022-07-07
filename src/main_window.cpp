#include "main_window.h"
#include "main_window_ui.h"
#include "doc_state.h"
#include <QString>
#include <QAction>
#include <QPushButton>
#include <QPoint>
#include <QPlainTextEdit>
#include <QMessageBox>

MainWindow::MainWindow() :
    QMainWindow{nullptr},
    ui{new MainWindowUI(this)}
{
    connect(ui->action_new, &QAction::triggered, this, &MainWindow::new_document);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::save_current);
    connect(ui->action_save_as, &QAction::triggered, this, &MainWindow::save_as_current);
    connect(ui->action_close_current, &QAction::triggered, this, &MainWindow::close_current);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::open_file);

    connect(ui->new_document_btn, &QPushButton::clicked, this, &MainWindow::new_document);
    connect(ui->file_menu_btn, &QPushButton::clicked, this, &MainWindow::file_menu_slot);

    connect(ui->tab_bar, &QTabBar::currentChanged, this, &MainWindow::navigate_to);
    connect(ui->tab_bar, &QTabBar::tabCloseRequested, this, &MainWindow::close_tab);

    connect(ui->editor, &QPlainTextEdit::textChanged, this, &MainWindow::parse);

    QFile css_loader(":/theme.css");
    css_loader.open(QFile::ReadOnly);
    css = css_loader.readAll();
    new_document();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::new_document()
{
    sys_operation = true;
    n_document++;
    doc_states.push_back(DocState());
    ui->tab_bar->addTab(QString("新建文档 %1").arg(n_document));

    int new_index{ui->tab_bar->count()-1};
    ui->tab_bar->setCurrentIndex(new_index);
    doc_states[new_index].set_edited(false);
    sys_operation = false;
}

void MainWindow::navigate_to(int index)
{
    if(index >=0)
    {
        sys_operation = true;
        if(previous_index >= 0)
            doc_states[previous_index].set_string(ui->editor->toPlainText());
        previous_index = index;
        ui->editor->setPlainText(doc_states[index].get_string());
        sys_operation = false;
    }
}

void MainWindow::file_menu_slot()
{
    QPoint pos{ui->file_menu_btn->pos()};
    pos.setX(pos.x() + 1);
    pos.setY(pos.y() + ui->file_menu_btn->height()-1);
    ui->file_menu->exec(mapToGlobal(pos));
}

void MainWindow::close_tab(int index)
{
    sys_operation = true;
    doc_states[ui->tab_bar->currentIndex()].set_string(ui->editor->toPlainText());
    if(doc_states[index].get_is_edited())
    {
        QMessageBox m(QMessageBox::Question,
                      "HomoDark",
                      QString("保存对文件 \"%1\" 所做的更改?").arg(ui->tab_bar->tabText(index)),
                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                      this);
        ui->blur();
        int button{m.exec()};
        ui->clean_blur();
        switch (button)
        {
        case QMessageBox::Yes:
            save_file(index);
            break;
        case QMessageBox::Cancel:
            sys_operation = false;
            return;
        }
    }
    previous_index = -10;
    if(ui->tab_bar->count() == 1)
        this->close();
    doc_states.remove(index);
    ui->tab_bar->removeTab(index);
    sys_operation = false;
}

void MainWindow::close_current() { close_tab(ui->tab_bar->currentIndex()); }

void MainWindow::parse()
{
    if(!sys_operation)
    {
        int index{ui->tab_bar->currentIndex()};
        if(!doc_states[index].get_is_edited())
        {
            doc_states[index].set_edited(true);
            ui->tab_bar->setTabIcon(index, QIcon(":/pics/file-edit-fill.svg"));
        }
    }
    auto s{ui->editor->toPlainText().toStdString()};
    std::istringstream is{std::move(s)};
    auto ans{R"(<!DOCTYPE html><html><head><meta charset="utf-8" name="viewport" content="width=device-width,initial-scale=1" /><style>)"
                    + css + "</style></head>" + QString::fromStdString(parser.parse(is)) + "</html>"};
    ui->previewer->setHtml(ans);
}
