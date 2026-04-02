#include <iostream>
#include <string>
#include <vector>

class Studentas {
private:
    std::string name_;
    std::string surname_;
    double examGrade_;
    std::vector<double> homeworkGrades_;

public:
    Studentas() : examGrade_(0.0) {}
    Studentas(const std::string& name,
              const std::string& surname,
              double examGrade,
              const std::vector<double>& homeworkGrades)
        : name_(name),
          surname_(surname),
          examGrade_(examGrade),
          homeworkGrades_(homeworkGrades) {}
    Studentas(std::istream& is);
    ~Studentas() {
        name_.clear();
        surname_.clear();
        homeworkGrades_.clear();
        examGrade_ = 0.0;
    }
    inline std::string getName() const { return name_; }
    inline std::string getSurname() const { return surname_; }
    inline double getExamGrade() const { return examGrade_; }
    inline std::vector<double> getHomeworkGrades() const { return homeworkGrades_; }
    double calculateFinalGrade(double (*calcFunc)(const std::vector<double>&)) const;
    std::istream& readStudent(std::istream&);
    void setName(const std::string& name) { name_ = name; }
    void setSurname(const std::string& surname) { surname_ = surname; }
    void setExamGrade(double examGrade) { examGrade_ = examGrade; }
    void setHomeworkGrades(const std::vector<double>& homeworkGrades) {homeworkGrades_ = homeworkGrades;}
    void addHomeworkGrade(double grade) {homeworkGrades_.push_back(grade);}
};