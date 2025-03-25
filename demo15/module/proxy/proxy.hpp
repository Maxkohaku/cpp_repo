#pragma once
#ifndef _PROXY_HPP_
#define _PROXY_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
class FileAbstract
{
public:
    FileAbstract() = default;
    virtual ~FileAbstract() = default;
    virtual void readFile() = 0;
};
class RealFile : public FileAbstract
{
public:
    explicit RealFile(const std::string& filename) :_filename(filename) {}
    void readFile() override
    {
        std::ifstream file(_filename);
        if(!file)
        {
            std::cerr << "Failed to open file: " << _filename << std::endl;
            return;
        }
        std::cout << "reading file: " << _filename << std::endl;
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
        file.close();
    }
private:
    std::string _filename;
};
class FileProxy : public FileAbstract
{
public:
    FileProxy(const std::string& filename, bool isAdmin) :_filename(filename), _isAdmin(isAdmin) {}
    ~FileProxy() = default;
    void readFile() override
    {
        if(_isAdmin == false)
        {
            std::cerr << "access denied !" << std::endl;
            return;
        }

        if(_realFile == nullptr)
        {
            _realFile = std::make_unique<RealFile>(_filename);
        }
        _realFile->readFile();
    }
private:
    std::string _filename;
    bool _isAdmin;
    std::unique_ptr<RealFile> _realFile = nullptr;
};

void proxy()
{
    std::cout << "guest access: " << std::endl;
    FileProxy fileGuest("/home/ynh/git_ws/cpp_repo/demo15/module/main.cpp", false);
    fileGuest.readFile();
    std::cout << "admin access: " << std::endl;
    FileProxy fileAdmin("/home/ynh/git_ws/cpp_repo/demo15/module/main.cpp", true);
    fileAdmin.readFile();
}
#endif /*_PROXY_HPP_*/
