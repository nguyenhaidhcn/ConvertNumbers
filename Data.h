#pragma once
class Data
{
private:
    std::map<int, std::wstring> m_list_data;
    int ScanLine(std::wstring str_input, int& i_number, std::wstring& str_value);
    std::wstring wstr_and;

public:
    Data(void);
    ~Data(void);
    std::map<int, std::wstring>* GetData();
    int ReadFile(std::wstring str_file_name);
    std::wstring GetWstrAnd() {return wstr_and;};
};

