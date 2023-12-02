#pragma once
#include <string>
#include <map>
#include <memory>

class File
{
    public:
    File() = default;
    File(std::string content, std::string FilePath);
    std::string FilePath;
    std::string content;
};

class source
{
public:
    source(std::string _pathSourseFolder);

    std::string loadFIleObject(std::string fileName, std::string _pathSourseFolder);
    
    std::string getShader(std::string Name);

    void loadFile(std::string filepath, std::string fileName);

private:

    std::string _pathSourseFolder;
    std::map<std::string, File> _map;
};