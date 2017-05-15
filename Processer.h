#pragma once
class Processer
{
private:
    std::string filter(std::string input);
    std::wstring read_3character(int i_number);
    std::wstring read_2character(int i_number);
    std::wstring read_multiples(int i_index);
    std::wstring remove_spaces(const std::wstring &s);
    int          m_number;

    Data m_data;

public:
    Processer(void);
    ~Processer(void);
    void init_language(std::wstring language);
    std::wstring convert(std::string input);
};

