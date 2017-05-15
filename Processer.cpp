#include "StdAfx.h"
#include "Processer.h"

Processer::Processer(void)
    : m_number(0)
{
}


Processer::~Processer(void)
{
}

/*
  init language, support en and vn
  input: language file
  output: void
*/
void Processer::init_language(std::wstring language_file)
{
    m_data.ReadFile(language_file);
}

/*
  coverts number to text
  input: number
  output: text
*/
std::wstring Processer::convert(std::string input)
{
    std::wstringstream output;
    //filter
    auto string_number = filter(input);
    //int length = string_number.length();
    m_number = atoi(string_number.c_str());
    //remainder %3
    int remainder3 = (string_number.length()) % 3;

    if (remainder3 != 0)
    {
        std::stringstream temp;
        temp.str("");

        for (int i = 0; i < remainder3; i++)
        {
            temp << string_number[i];
        }

        output << this->read_3character(atoi(temp.str().c_str())) << " ";
        //check multiples
        int index = string_number.length() - remainder3;
        //read multiples
        output << this->read_multiples(index) << " ";
    }

    //read each of 3 characters
    for (int i = remainder3; i < string_number.length(); i = i + 3)
    {
        std::stringstream temp;

        for (int j = i; j < (i + 3); j++)
        {
            temp << string_number.c_str()[j];
        }

        output << this->read_3character(atoi(temp.str().c_str())) << " ";

        //check multiples
        int index = string_number.length() - (i + 3);
        //read multiples
        output << read_multiples(index) << " ";
    }

    std::wstring wstr_output = output.str();

    return this->remove_spaces(wstr_output);
    //remove last space
}

/*
  filter string, handle incorrect input data
  input: string
  output: string
*/
std::string Processer::filter(std::string input)
{
    std::stringstream ss;

    for (int i = 0; i < input.length(); i++)
    {
        if ((input.c_str()[i] < '0')  || (input.c_str()[i] > '9'))
            continue;

        ss << input.c_str()[i];
    }

    return (ss.str().c_str());
}

/*
  read number number 100 - 999
  input: number
  output: text
*/
std::wstring Processer::read_3character(int i_number)
{
    std::wstringstream output;

    //check length
    if (i_number > 999)
    {
        return L"";
    }

    int remainder_100 = (i_number % 100);
    int coefficient_100 = (i_number / 100);

    if (coefficient_100 > 0)
    {
        auto map_data = m_data.GetData()->find(coefficient_100);

        if (map_data != m_data.GetData()->end())
        {
            output << map_data->second << " ";
            // multiples
            int index = 2;//hundred
            output << this->read_multiples(index) << " ";

        }
    }

    //read 2charcacter

    /*
    HaiNT Fix error 103: Mot tram ba
    ----> Mot tram linh ba
    */
    if (i_number > 100 && remainder_100 < 10)
    {
        output << m_data.GetWstrAnd() << " ";
    }

    output << this->read_2character(remainder_100);
    return output.str();
}


/*
  read number number 10 - 99
  input: number
  output: text
*/
std::wstring Processer::read_2character(int i_number)
{
    std::wstringstream output;

    if (i_number > 99)
        return L"";

    //check special
    auto map_data = m_data.GetData()->find(i_number);

    if (map_data != m_data.GetData()->end())
    {
        output << map_data->second;
        return output.str();
    }

    //normal
    int remainder_10 = (i_number % DECIMAL);
    //find number  20, 30, 40...90
    map_data = m_data.GetData()->find(i_number - remainder_10);

    if (map_data != m_data.GetData()->end())
    {
        /*
        HaiNT correct output.
        [twenty three] --> [twenty-three]
        Edit data file en, vn
        */
        //output << map_data->second << " ";
        output << map_data->second << "";

    }
    else
    {
        //TODO update
    }

    // read remainder
    map_data = m_data.GetData()->find(remainder_10);

    if (map_data != m_data.GetData()->end())
    {
        output << map_data->second;
    }

    return output.str();
}

/*
  read multiple
  ex: 100, 1000, 1000000
  input: number
  output: text
*/
std::wstring Processer::read_multiples(int index)
{
    if (index == 0) return L"";

    int multiples = 1;

    for (int i = 0; i < index; i++)
        multiples *= DECIMAL;

    auto map_data = m_data.GetData()->find(multiples);

    if (map_data != m_data.GetData()->end())
    {
        return map_data->second;

    }
    else
    {
        return L"";
    }
}

//remove last space
std::wstring Processer::remove_spaces(const std::wstring &s)
{
    int last = s.size() - 1;

    while (last >= 0 && s[last] == ' ')
        --last;

    return s.substr(0, last + 1);
}