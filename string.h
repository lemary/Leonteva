#include <iostream>
#include <cstring>

class String {
private:
    char* value;
    size_t len;
    size_t buffer;
    static constexpr double COEF = 2;// constexpr??
    
    void swap(String&);
    void reallocate();
public:
    String();
    String(size_t, char);
    String(char);
    String(const char*);
    String(const String&);
    String& operator=(String);
    
    bool operator==(const String&) const;
    char& operator[](size_t);
    const char& operator[](size_t) const;
    String& operator+=(const String&);
    
    size_t length() const;
    
    void push_back(char);
    void pop_back();
    char& front();
    char& back();
    const char& front() const;
    const char& back() const;
    
    size_t find(const String&) const;
    size_t rfind(const String&) const;
    String substr(size_t, size_t) const;
    
    bool empty() const;
    void clear();
    ~String();
    void out() const;
};

void String::out() const{
    for(size_t i = 0; i < len; i++) {
        std::cout << value[i];
    }
    std::cout << std::endl;
}

String::String() {
    len = 0;
    buffer = 1;
    value = new char[buffer];
}

String::String(size_t n, char c = '\0') {
    len = n;
    buffer = COEF*n + 1;
    value = new char[buffer];
    memset(value, c, buffer);
}

String::String(char c) : String(1, c) {
}

String::String(const char* value2) {
    len = 0;
    while (value2[len] != '\0') {// Для этого есть специальная функция в стандартных библиотеках strlen
        ++len;
    }
    buffer = COEF*len + 1;
    value = new char[buffer];
    memcpy(value, value2, len);
}

String::String(const String& s) : String(s.len) { //конструктор копирования
    memcpy(value, s.value, s.len);// Два заполнения памяти, эххх
}

String& String::operator=(String s) { //copy and swap
    swap(s);
    return *this;
}

bool String::operator==(const String& s) const {
    if (len != s.len) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (value[i] != s.value[i]) {
            return false;
        }
    }
    return true;
}

char& String::operator[](size_t ind) {
    return value[ind];
}

const char& String::operator[](size_t ind) const {
    return value[ind];
}

String& String::operator+=(const String& s) {
    size_t size = s.len;
    for (size_t i = 0; i < size; i++) {// ?? Почему бы не расширить память сразу на нужную величину, если места не хватает? Плюс memcpy работает
        // в разы быстрее, нужно поменять
        push_back(s.value[i]);
    }
    return *this;
}

String operator+(const String s1, const String s2) {
    String copy = s1;
    return copy += s2;// Лучше написать copy+=2; return copy, тогда компилятор не будет делать лишнего копирования, а переместит сразу copy
    // на место наначения
}

std::ostream& operator<<(std::ostream& out, const String& s) {
    for (size_t i = 0; i < s.length(); ++i) {
        out << s[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    s = String();
    char c;
    while (in.get(c)) {
        if(c == ' ' || c == '\n') {// \t, \r ещё стоит учитывать, а в целом есть спец функция isspace(c)
            break;
        }
        s += c;
    }
    return in;
}

size_t String::length() const {
    return len;
}

void String::push_back(char c) {
    reallocate();
    value[len] = c;
    len++;
}

void String::pop_back() {
    len--;
    reallocate();
}

char& String::front() {
    return value[0];
}

char& String::back() {
    return value[len - 1];
}

const char& String::front() const {
    return value[0];
}

const char& String::back() const {
    return value[len - 1];
}

size_t String::find(const String& s) const {
    size_t ind = len;
    for (size_t i = 0; i <= len - s.len; i++) {
        bool ok = true;
        for (size_t j = 0; j < s.len; j++) {
            if (s.value[j] != value[i+j]) {
                ok = false;
            }
        }
        if (ok) {
            ind = i;
            return ind;
        }
    }
    return ind;
}

size_t String::rfind(const String& s) const {// Можно оптимизировать проходом с другой стороны. Для нормальной работы с size_t сдвинь счётчик на 1 вверх (i>=1)
    size_t ind = len;
    for (size_t i = 0; i <= len - s.len; i++) {
        bool ok = true;
        for (size_t j = 0; j < s.len; j++) {
            if (s.value[j] != value[i+j]) {
                ok = false;
            }
        }
        if (ok) {
            ind = i;
        }
    }
    return ind;
}

String String::substr(size_t start, size_t count) const {
    String s(count);
    memcpy(s.value, value + start, count);
    return s;
}

bool String::empty() const {
    if (len == 0) 
        return true;
    else 
        return false;
}

void String::clear() {
    *this = String();//Здесь утечка памяти, так как старый экземпляр не будет удалён. Поправь
}

String::~String() {
    delete[] value;
}

///////////////////////

void String::swap(String& s) {
    std::swap(len, s.len);
    std::swap(buffer, s.buffer);
    std::swap(value, s.value);
}

void String::reallocate() {
    if (buffer == len) {
        buffer *= COEF;
        char* new_value = new char[buffer];
        memcpy(new_value, value, len);
        delete[] value;
        value = new_value;
    } else if (len + 1 < buffer/COEF/COEF) {
        buffer /= COEF;
        char* new_value = new char[buffer];
        memcpy(new_value, value, len);
        delete[] value;
        value = new_value;
    }
}

// int main() {
//     String s1 = "abacaba"; //s(str);
//     String s2;
//     std::cin >> s2;
//     std::cout << s1 + s2 << std::endl;
//     const String s3 = s1 + '_' + s2;
//     std::cout << s3 << std::endl;
//     String s4 = s3;
//     s4 += s4;
//     std::cout << s4 << std::endl;
//     std::cout << s4.find("lox") << std::endl;
//     std::cout << s4.rfind("lox") << std::endl;
//     std::cout << s4.substr(0, 4) << std::endl;
//     s4.clear();
//     std::cout << s4 << std::endl;
//     s4 = "kek";
// }
