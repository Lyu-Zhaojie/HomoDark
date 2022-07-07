#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "doc_state.h"
#include "ll_md_parser.h"
#include <QMainWindow>
#include <QList>
#include <QFile>

class MainWindowUI;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    ~MainWindow();

private slots:
    void new_document();

    void file_menu_slot();

    void close_tab(int index);

    void parse();

    void navigate_to(int index);

    void save_current();

    void save_as_current();

    void close_current();

    void open_file();

private:
    void save_file(int index);

    void save_as(int index);

    MainWindowUI* ui;

    int n_document{0}, previous_index{-1};

    QList<DocState> doc_states;

    bool sys_operation{false};

    ll_markdown::Parser parser;

    QString css;
};
#endif // MAIN_WINDOW_H
