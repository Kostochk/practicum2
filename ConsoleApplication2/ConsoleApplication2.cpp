#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
    string name;
    int age;
    double mark;
public:
    Student() {
        name = "Kostya";
        age = 11.1;
        mark = 10.2;
    }

    void Writer() {
        ofstream outFile("Student.bin", ios::binary);
        if (!outFile) {
            cerr << "Error while openning file.\n";
        }
        outFile.write(reinterpret_cast<const char*>(&age), sizeof(age));
        outFile.write(reinterpret_cast<const char*>(&mark), sizeof(mark));

        size_t messageSize = name.size();
        outFile.write(reinterpret_cast<const char*>(&messageSize), sizeof(messageSize));
        outFile.write(name.c_str(), messageSize);
        outFile.close();
    }

    void Reader() {
        ifstream inFile("Student.bin", ios::binary);
        if (!inFile) {
            cerr << "Error while readding.\n";
        }

        int readAge;
        double readMark;
        size_t readMessageSize;
        string readMessage;

        inFile.read(reinterpret_cast<char*>(&readAge), sizeof(readAge));
        inFile.read(reinterpret_cast<char*>(&readMark), sizeof(readMark));

        inFile.read(reinterpret_cast<char*>(&readMessageSize), sizeof(readMessageSize));
        readMessage.resize(readMessageSize);
        inFile.read(&readMessage[0], readMessageSize);

        inFile.close();


        cout << "Info from file:\n";
        cout << "Age: " << readAge << "\n";
        cout << "Mark: " << readMark << "\n";
        cout << "Message: " << readMessage << "\n";
    }
};

int main()
{
    Student st;
    st.Writer();
    st.Reader();

   



}