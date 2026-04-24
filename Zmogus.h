#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string name_;
    std::string surname_;

public:
    Zmogus() = default;
    Zmogus(const std::string& name, const std::string& surname) : name_(name), surname_(surname) {}
    virtual ~Zmogus() = 0;
    virtual std::string getName() const = 0;
    virtual std::string getSurname() const = 0;
};

inline Zmogus::~Zmogus() {}

#endif