#pragma once

#include <string>

class Text
{
public:
    using symbol = int32_t;
    using unicode_string = std::basic_string<int32_t>;
    
    Text(const char* byte_string, const char* encoding);
    Text(const char* byte_string); // UTF-8
    Text(const wchar_t* wide_string);
    Text(const std::string& byte_string, const char* encoding);
    Text(const std::string& byte_string); // UTF-8 
    Text(const std::wstring& wide_string);

    template<class _Iter, class = enable_if_t<_Is_iterator<_Iter>::value>>
    Text(_Iter _First, _Iter _Last);

    symbol& operator[](int index);
    const symbol& operator[](int index) const;

    const std::string& byte_string(const std::string& encoding) const;
    const std::string& byte_string() const; // UTF-8
    const std::wstring& wide_string() const;

    const char* byte_c_str(const char* encoding) const;
    const char* byte_c_str() const; // UTF-8
    const wchar_t* wide_c_str() const;

    Text& operator=(const std::string& byte_string); // UTF-8
    Text& operator=(const std::wstring& wide_string);

    // operator+
    // operator+=

private:
     unicode_string mText;

};

template <class data_type>
class copy_on_write
{
public:
    copy_on_write(data_type* data)
        : m_data(data) {
    }
    data_type const* operator -> () const {
        return m_data.get();
    }
    data_type* operator -> () {
        if (!m_data.unique())
            m_data.reset(new data_type(*m_data));
        return m_data.get();
    }
private:
    std::shared_ptr<data_type> m_data;
};

