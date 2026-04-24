#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>

class Studentas : public Zmogus {
private:
    std::string name_;
    std::string surname_;
    int examGrade_;
    std::vector<int> homeworkGrades_;
    double finalGrade_;

public:
    static bool arSpausdintiDestruktoriu;
    Studentas() : Zmogus(), examGrade_(0), finalGrade_(0) {}
    Studentas(const std::string& name,
              const std::string& surname,
              int examGrade,
              const std::vector<int>& homeworkGrades,
              double finalGrade)
        : Zmogus(name, surname),
          examGrade_(examGrade),
          homeworkGrades_(homeworkGrades),
          finalGrade_(finalGrade) {}
    Studentas(const char* eilute, std::size_t namuDarbuKiekis);
    Studentas(bool generuotiPazymius, int ndKiekis);
    ~Studentas() {
        if (arSpausdintiDestruktoriu) std::cout << "[DTOR] Naikinamas studentas: " << name_ << ' ' << surname_ << '\n';
        name_.clear();
        surname_.clear();
        homeworkGrades_.clear();
        examGrade_ = 0;
        finalGrade_ = 0.0;
    }
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(Studentas&& other) noexcept;
    inline std::string getName() const { return name_; }
    inline std::string getSurname() const { return surname_; }
    inline double getFinalGrade() const { return finalGrade_; }
    inline int getExamGrade() const { return examGrade_; }
    inline const std::vector<int>& getHomeworkGrades() const { return homeworkGrades_; }
    double calculateFinalGrade(char method) const;
    void setName(const std::string& name) { name_ = name; }
    void setSurname(const std::string& surname) { surname_ = surname; }
    void setExamGrade(int examGrade) { examGrade_ = examGrade; }
    void setFinalGrade(double finalGrade) { finalGrade_ = finalGrade; }
    void setHomeworkGrades(const std::vector<int>& homeworkGrades) {homeworkGrades_ = homeworkGrades;}
    void addHomeworkGrade(int grade) {homeworkGrades_.push_back(grade);}
    void clearHomeworkGrades() {homeworkGrades_.clear();}
    void reserveHomeworkGrades(std::size_t n) {homeworkGrades_.reserve(n);}
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

struct StudentasLentelei {
    const Studentas& s;
};

std::ostream& operator<<(std::ostream& os, const StudentasLentelei& s);

#endif