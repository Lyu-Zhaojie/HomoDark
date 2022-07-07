#include "main_window.h"
#include "main_window_ui.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

void MainWindow::save_file(int index)
{
    if(doc_states[index].get_is_edited())
    {
        if(doc_states[index].get_path().isEmpty())
        {
            save_as(index);
            return;
        }
        QFile f(doc_states[index].get_path());
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->blur();
            QMessageBox::warning(this, windowTitle(),
                                 QString("无法写入文件 %1: %2").arg(
                                     QDir::toNativeSeparators(doc_states[index].get_path()), f.errorString()));
            ui->clean_blur();
            return;
        }
        QTextStream ofs(&f);
        ofs << doc_states[index].get_string();
        doc_states[index].set_edited(false);
        ui->tab_bar->setTabIcon(index, QIcon());
    }
}

void MainWindow::save_as(int index)
{
    QFileDialog dialog(this, "另存为");
    dialog.setMimeTypeFilters({"text/markdown"});
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("md");
    if (dialog.exec() != QDialog::Accepted)
        return;

    doc_states[index].set_path(dialog.selectedFiles().constFirst());

    ui->tab_bar->setTabText(index, doc_states[index].get_path().split('/').constLast());

    QFile f(doc_states[index].get_path());
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ui->blur();
        QMessageBox::warning(this, windowTitle(),
                             QString("无法写入文件 \"%1\": %2").arg(
                                 QDir::toNativeSeparators(doc_states[index].get_path()), f.errorString()));
        ui->clean_blur();
        return;
    }
    QTextStream ofs(&f);
    ofs << doc_states[index].get_string();
    doc_states[index].set_edited(false);
    ui->tab_bar->setTabIcon(index, QIcon());
}

void MainWindow::open_file()
{
    sys_operation = true;
    QFileDialog dialog(this, "打开文件");
    dialog.setMimeTypeFilters({"text/markdown"});
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString path{dialog.selectedFiles().constFirst()};
        QFile f(path);

        if (!f.open(QIODevice::ReadOnly))
        {
            ui->blur();
            QMessageBox::warning(this, windowTitle(),
                                 QString("无法打开文件 \"%1\": %2").arg(
                                     QDir::toNativeSeparators(path), f.errorString()));
            ui->clean_blur();
        }
        else
        {
            new_document();
            int index{ui->tab_bar->currentIndex()};
            doc_states[index].set_path(path);
            ui->tab_bar->setTabText(index, path.split('/').constLast());
            ui->editor->setPlainText(f.readAll());
            doc_states[index].set_edited(false);
            ui->tab_bar->setTabIcon(index, QIcon());
        }
    }
    sys_operation = false;
}

void MainWindow::save_current()
{
    int index{ui->tab_bar->currentIndex()};
    doc_states[index].set_string(ui->editor->toPlainText());
    save_file(index);
}

void MainWindow::save_as_current()
{
    int index{ui->tab_bar->currentIndex()};
    doc_states[index].set_string(ui->editor->toPlainText());
    save_as(index);
}
