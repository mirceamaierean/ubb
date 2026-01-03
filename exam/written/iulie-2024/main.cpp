#include <vector>
#include <stdexcept>
#include <deque>
#include <unordered_set>
#include <iostream>

using namespace std;

class Encoder
{
public:
    Encoder() {};
    virtual ~Encoder() {};
    virtual string encode(string s) = 0;
};

class NaiveEncoding : public Encoder
{
public:
    NaiveEncoding() {};
    string encode(string s) override
    {
        // TODO
    }
};

class CircularEncoding : public Encoder
{
private:
    int length;

public:
    CircularEncoding(int len)
    {
        if (len <= 2)
            throw invalid_argument("Length must be greater than 2");
        this->length = len;
    }
    string encode(string s) override
    {
        int rotationLength = this->length % s.length();

        if (rotationLength == 0)
            return s;
        string firstLetters = s.substr(0, rotationLength);

        // for (int i = 0; i < rotationLength; ++i)
        //     firstLetters += s[i];

        for (int i = rotationLength; s[i]; ++i)
            s[i - rotationLength] = s[i];

        for (int i = s.length() - 1 - rotationLength; i < s.length(); ++i)
            s[i] = firstLetters[i - (s.length() - 1 - rotationLength)];

        return s;
    }
};

class Communication
{
private:
    deque<string> encodedMessages;
    Encoder *code;

public:
    Communication(Encoder *code = nullptr) : code{code} {};
    ~Communication()
    {
        if (code != nullptr)
            delete code;
    }
    void addMessage(string m)
    {
        encodedMessages.push_back(code->encode(m));
    }
    deque<string> getEncodedMessages()
    {
        return encodedMessages;
    }
    string toString()
    {
        if (encodedMessages.size() == 0)
            return "";
        string allEncodings = encodedMessages.front();

        for (int i = 1; i < encodedMessages.size(); ++i)
            allEncodings += "#" + encodedMessages[i];

        return allEncodings;
    }
};

// Theta(m + n), since at each step, we access the front of our list in O(1), and pop it in constant time, and we are repeating the step in m + n
deque<string> interclasare(deque<string> &l1, deque<string> &l2)
{

    string crt;
    if (l1.size() == 0 && l2.size() == 0)
        return deque<string>();

    if (l1.size() == 0)
    {
        crt = l2.front();
        l2.pop_front();
    }
    else if (l2.size() == 0)
    {
        crt = l1.front();
        l1.pop_front();
    }
    else
    {
        if (l1.front() < l2.front())
        {
            crt = l1.front();
            l1.pop_front();
        }
        else
        {
            crt = l2.front();
            l2.pop_front();
        }
    }

    deque<string> res = interclasare(l1, l2);
    res.push_front(crt);

    return res;
}

bool checkCircular(string m1, string m2)
{
    if (m1.size() != m2.size())
        return false;
    for (int i = 0; i < m1.size(); ++i)
    {
        bool ok = true;
        // am setat i ca si pozitia din care sa fie inceputul
        for (int j = 0; j < m2.size(); ++j)
        {
            int index = (j + i) % m2.size();
            if (m2[j] != m1[index])
            {
                ok = false;
                break;
            }
        }
        if (ok == true)
            return true;
    }
    return false;
}

int countDistinctMessages(Communication &c)
{
    unordered_set<string> messages;
    for (auto &s : c.getEncodedMessages())
    {
        messages.insert(s);
    }
    return messages.size();
}

void e()
{
    Encoder *circularEncoding = new CircularEncoding(10);
    Encoder *naiveEncoding = new NaiveEncoding();

    Communication o1(circularEncoding), o2(naiveEncoding);

    o1.addMessage("bac");
    o1.addMessage("cod");
    o1.addMessage("apt");

    o2.addMessage("bac");
    o2.addMessage("cod");
    o2.addMessage("apt");

    deque<string> o1Strings = o1.getEncodedMessages();
    deque<string> o2Strings = o2.getEncodedMessages();

    deque<string> inter = interclasare(o1Strings, o2Strings);
    for (auto &s : inter)
        cout << s << " ";
}

int main()
{
}
