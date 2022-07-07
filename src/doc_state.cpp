#include "doc_state.h"
#include <QString>

void DocState::set_edited(bool val) { is_edited = val; }
bool DocState::get_is_edited() const { return is_edited; }

const QString DocState::get_string() const { return doc; }
void DocState::set_string(const QString &str) { doc = str; }

const QString DocState::get_path() const { return path; }
void DocState::set_path(const QString &str) { path=str; }
