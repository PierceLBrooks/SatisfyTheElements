
// Author: Pierce Brooks

#include <STE/STE.hpp>
#include <iostream>

std::string STE::SatisfyTheElements::assetsPath = "./";

const std::string& STE::SatisfyTheElements::getAssetsPath()
{
    return assetsPath;
}

void STE::SatisfyTheElements::setAssetsPath(const std::string& path)
{
    assetsPath = path;
    std::cout << "Assets Path: " << path << std::endl;
}

const std::string& STE::getAssetsPath()
{
    return SatisfyTheElements::getAssetsPath();
}

void STE::setAssetsPath(const std::string& path)
{
    SatisfyTheElements::setAssetsPath(path);
}
