#include "StdAfx.h"
#include "Data.h"

Data::Data(void)
{
}


Data::~Data(void)
{
}

int Data::ReadFile(std::wstring str_file_name)
{

    FILE *fStream;
    errno_t errCode = _tfopen_s(&fStream, str_file_name.c_str(), _T("r, ccs=UNICODE"));

    if (0 != errCode)
    {
        return false;
    }

    wchar_t strLine[100];
    std::streamsize size = 100;
    std::wifstream file(fStream);

    while (file.getline(strLine, size))
    {
        //reading line-by-line
        int i_key = -1;
        std::wstring str_value;

        if (ScanLine(strLine, i_key, str_value))
        {
            // push map
            m_list_data[i_key] = str_value;
        }

    }
}

int Data::ScanLine(std::wstring str_input, int& i_key, std::wstring& str_value)
{
    wchar_t str[500];
    COPY_STR(str, str_input.c_str());

    //---- checks
    if (str == NULL) return (false);

    wchar_t *tok_start = str, end;
    //---- find token boundary
    wchar_t *tok_end = tok_start;

    while (*tok_end != '=' && *tok_end != 0)
    {
        tok_end++;
    }

    if (*tok_end == '=')
    {
        end = *tok_end;
        *tok_end = NULL;

        i_key = _wtoi(tok_start);
        //---- restore
        *tok_end = end;
        tok_end++;
        str_value.assign(tok_end);

        //check special key '&'
        if (*tok_start == '&')
        {
            wstr_and.assign(tok_end);
        }

        if (i_key != 0)
            return true;
    }

    return (false);
}

std::map<int, std::wstring>* Data::GetData()
{
    return &m_list_data;
}