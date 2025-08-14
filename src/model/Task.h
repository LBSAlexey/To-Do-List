#ifndef TASK_H
#define TASK_H

#include <cstdint>
#include <string> // строки
#include <wx/datetime.h> // работа со временнем


class Task {
public:
    Task(const std::string& name, const std::string& description, const wxDateTime& dateFinish, bool completed = false);

    // геттеры
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const wxDateTime &getDateNow() const;
    const wxDateTime &getDateFinish() const;
    const int getId() const;

    // сеттеры
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    bool setDateFinish(const wxDateTime &dateFinish);

    bool IsOverdue() const;
    wxTimeSpan TimeRemaining() const;

private:
    int id;
    static int nId;
    std::string title{};
    std::string description{};
    bool completed{};
    wxDateTime start;
    wxDateTime finish;
};



#endif //TASK_H
