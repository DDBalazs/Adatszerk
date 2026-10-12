#ifndef AVLEXCEPTIONS_HPP_INCLUDED
#define AVLEXCEPTIONS_HPP_INCLUDED
#include <exception>

class CopyNotImplemented final : public std::exception {
public:
    const char *what() const throw() override { return "Masolas nincs implementalva!"; }
};

class InternalError final : public std::exception {
    const char *message;

public:
    explicit InternalError(const char *msg = "Hiba van az implementacioban!")
        : message(msg) {
    }

    const char *what() const throw() override { return message; }
};

class InvalidBinarySearchTree : public std::exception {
public:
    const char *what() const throw() override {
        return "Serulnek a binaris keresofa kriteriumok!";
    }
};

class InvalidAvlTree final : public std::exception {
public:
    const char *what() const throw() override {
        return "Serulnek az AVL fa tulajdonsagok!";
    }
};

class InvalidIterator final : public std::exception {
public:
    const char *what() const throw() override { return "nullptr elemre mutat az iterator!"; }
};

#endif // AVLEXCEPTIONS_HPP_INCLUDED
