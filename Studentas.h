#include <iostream>
#include <string>
#include <vector>

class Studentas {
private:
    std::string name_;
    std::string surname_;
    int examGrade_;
    std::vector<int> homeworkGrades_;

public:
    Studentas() : examGrade_(0) {}
    Studentas(const std::string& name,
              const std::string& surname,
              int examGrade,
              const std::vector<int>& homeworkGrades)
        : name_(name),
          surname_(surname),
          examGrade_(examGrade),
          homeworkGrades_(homeworkGrades) {}
    Studentas(const char* eilute, std::size_t namuDarbuKiekis);
    Studentas(bool generuotiPazymius, int ndKiekis);
    ~Studentas() {
        name_.clear();
        surname_.clear();
        homeworkGrades_.clear();
        examGrade_ = 0.0;
    }
    inline std::string getName() const { return name_; }
    inline std::string getSurname() const { return surname_; }
    inline int getExamGrade() const { return examGrade_; }
    inline std::vector<int> getHomeworkGrades() const { return homeworkGrades_; }
    double calculateFinalGrade(double (*calcFunc)(const std::vector<int>&)) const;
    void setName(const std::string& name) { name_ = name; }
    void setSurname(const std::string& surname) { surname_ = surname; }
    void setExamGrade(int examGrade) { examGrade_ = examGrade; }
    void setHomeworkGrades(const std::vector<int>& homeworkGrades) {homeworkGrades_ = homeworkGrades;}
    void addHomeworkGrade(int grade) {homeworkGrades_.push_back(grade);}
    void clearHomeworkGrades() {homeworkGrades_.clear();}
    void reserveHomeworkGrades(std::size_t n) {homeworkGrades_.reserve(n);}
};