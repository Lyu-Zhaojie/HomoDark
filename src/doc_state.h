#ifndef DOC_STATE_H
#define DOC_STATE_H
#include <QString>
class DocState
{
public:
    void set_edited(bool val);
    bool get_is_edited() const;

    const QString get_string() const;
    void set_string(const QString &str);
    const QString get_path() const;
    void set_path(const QString &str);

private:
    bool is_edited{false};
    QString doc;
    QString path;
};
#endif // DOC_STATE_H
