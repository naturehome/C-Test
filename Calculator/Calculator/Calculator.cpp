// Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <vector>


bool ReadFileData(const char * fileName, std::string & fileContent)
{
    //static int s_share = 12;
    //std::cout << "ReadFileData address:" << &s_share << std::endl;
    //std::locale loc = std::locale::global(std::locale(""));
    //std::ifstream file(fileName, std::ios_base::binary);
    //std::locale::global(loc);
    //if (!file)
    //{
    //    return false;
    //}

    //std::istreambuf_iterator<char> src(file);
    //std::istreambuf_iterator<char> eof;
    //file >> std::noskipws;
    //std::copy(src, eof, std::back_inserter(fileContent));

    //file.close();

    return true;
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//
//    wchar_t a[50];
//
//    int size = sizeof(a)/sizeof(a[0]);
//
//    std::vector<int> vec;
//    for (int i = 0; i<10; i++)
//    {
//        vec.push_back(i);//增加一个元素
//    }
//
//    auto iter = std::find(vec.begin(), vec.end(), 11);
//
//    int index = std::distance(vec.begin(), iter);
//
//    std::string strWindowId = "DiskSpaceNotUsed";
//    const std::vector<std::string> SpecWinIdvec{ "DiskSpaceNotUsed", "AskTeacherQuestion", "DiskSpaceWarning" };
//    auto itor1 = std::find(SpecWinIdvec.begin(), SpecWinIdvec.end(), strWindowId);
//    if (itor1 != SpecWinIdvec.end())
//        return 0;
//
//
//    static int s_share = 12;
//    std::cout << "main address:" << &s_share << std::endl;
//    std::string strJsonData;
//    std::string strJson;
//    ReadFileData("html.txt", strJsonData);
//
//    int pos1 = strJsonData.find_first_of('{');
//    int pos2 = strJsonData.find_last_of('}');
//    int pos3 = strJsonData.find(':');
//
//    if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) // 返回json数据组
//    {
//        strJson = strJsonData.substr(pos1, pos2 - pos1 + 1);
//    }
//    else
//    {
//        std::string strError = "服务器未返回JSON数据";
//    }
//
//    try
//    {
//        std::istringstream jsonIStream;
//        jsonIStream.str(strJson.c_str());
//
//        boost::property_tree::ptree ptParse;
//        boost::property_tree::json_parser::read_json(jsonIStream, ptParse);
//
//
//        boost::property_tree::ptree::assoc_iterator itor = ptParse.find("key");
//        if (itor == ptParse.not_found())
//        {
//            std::string strError = "服务器未返回JSON数据";
//        }
//    }
//    catch (...)
//    {
//        std::string strError = "服务器未返回JSON数据";
//    }
//   
//    return 0;
//}

