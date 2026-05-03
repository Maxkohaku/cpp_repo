#pragma once
#ifndef _PROXY_HPP_
#define _PROXY_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
using namespace std;
class FileReaderAbstract {
public:
    FileReaderAbstract() = default;
    virtual ~FileReaderAbstract() = default;
    virtual void fileReader() = 0;
};
class FileReader : public FileReaderAbstract {
public:
    explicit FileReader(const string& fileName) : _fileName(fileName) {}
    void fileReader() override {
        ifstream file(_fileName);
        if (!file)
            throw invalid_argument("Failed to open file");
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
private:
    string _fileName;
};
class FileReaderProxy : public FileReaderAbstract {
public:
    FileReaderProxy(const string& fileName, bool isAdmin = false) : _fileName(fileName), _isAdmin(isAdmin) {}
    void fileReader() override {
        if (!_isAdmin)
        {
            cout << "No Permission to Access " << _fileName << endl;
            return;
        }
        if (_fileReader == nullptr)
            _fileReader = make_unique<FileReader>(_fileName);
        _fileReader->fileReader();
    }
private:
    string _fileName;
    bool _isAdmin;
protected:
    unique_ptr<FileReader> _fileReader;
};
void proxy() {
    FileReaderProxy admin = FileReaderProxy("module/main.cpp", true);
    admin.fileReader();
    FileReaderProxy guest = FileReaderProxy("module/main.cpp");
    guest.fileReader();
}
#endif /*_PROXY_HPP_*/