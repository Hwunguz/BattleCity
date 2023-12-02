#include "source.h"

#include <sstream>
#include <fstream>
#include <algorithm>

#include <iostream>

source::source(std::string _pathSourseFolder)
{
    size_t i = _pathSourseFolder.find("build");
    _pathSourseFolder.erase(i);
    _pathSourseFolder += "res\\";
    std::cout << _pathSourseFolder << std::endl;

    this->_pathSourseFolder = _pathSourseFolder;
}

std::string source::getShader(std::string Name)
{
    return _map[Name].content;
}

void source::loadFile(std::string filepath, std::string fileName)
{
    std::stringstream buf;
    std::string strbuf;
    // std::string strbuf, buf;

    std::string f = _pathSourseFolder+filepath;
    

    std::cout << f << std::endl;

    std::replace(f.begin(), f.end(), '\\', '/');

    std::ifstream file;
    file.open(f, std::ios::in | std::ios::binary);

    std::cout << f << std::endl;

    if (!file.is_open()){
        std::cerr << "file is not open" << std::endl;
    }



    buf << file.rdbuf();

    _map.insert({fileName,  File(buf.str(), f)});
    // _map.insert({fileName,  File(strbuf, f)});
}

File::File(std::string content, std::string FilePath)
{
    this->content = content;
    this->FilePath = FilePath;
}
