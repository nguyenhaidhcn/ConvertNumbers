// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Data.h"
void WriteUnicodetoFile(const char* myFile,  std::wstring output, std::string input);


int _tmain(int argc, _TCHAR* argv[])
{
    Processer processer_vn;
    processer_vn.init_language(L"vn");

    Processer processer_en;
    processer_en.init_language(L"en");


    std::string output_file = "result.txt";

    while (true)
    {
        std::cout << std::endl << "Input number : ";
        std::string input;
        std::cin >> input;
        //EN
        auto output_en = processer_en.convert(input);

        if (output_en.length() > 0)
        {
            WriteUnicodetoFile(output_file.c_str(), output_en, input);
            std::cout << "EN text write to file : " << output_file << std::endl;
        }


        //VN
        auto output_vn = processer_vn.convert(input);

        if (output_vn.length() > 0)
        {
            WriteUnicodetoFile(output_file.c_str(), output_vn, input);
            std::cout << "VN text write to file : " << output_file << std::endl;
        }

    }

    return 0;
}


void WriteUnicodetoFile(const char* myFile,  std::wstring output, std::string input)
{
    input.append(":");
    std::wstring wstr_input(input.begin(), input.end());
    std::ofstream outFile(myFile, std::ios::app | std::ios::binary);
    outFile.write((char *) wstr_input.c_str(), wstr_input.length() * sizeof(wchar_t));
    outFile.write((char *) output.c_str(), output.length() * sizeof(wchar_t));
    std::wstring end_line = L"\r\n";
    outFile.write((char *)end_line.c_str(), end_line.length() * sizeof(wchar_t));
    outFile.close();

}
