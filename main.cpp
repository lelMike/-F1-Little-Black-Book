#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Person{
public:
    Person(string department, const string& parseInfo);

    [[nodiscard]] const string& getComparisonField() const {
        return data[3];
    }

    void print_Person();

private:
    string data[8];
};

Person::Person(string department, const string& parseInfo) {
    this->data[0] = std::move(department);

    string buffer; int commaCount = 1;
    for(char i : parseInfo){
        if(i != ','){
            buffer += i;
        }
        else{
            this->data[commaCount++] = buffer;
            buffer = "";
        }
    }
    this->data[commaCount] = buffer;
}

void merge_sort(vector<Person>& leftList, vector<Person>& rightList) {
    auto leftIter = leftList.begin();
    auto rightIter = rightList.begin();

    while (leftIter != leftList.end() && rightIter != rightList.end()) {
        if (rightIter->getComparisonField() < leftIter->getComparisonField()) {
            leftIter = leftList.insert(leftIter, std::move(*rightIter));
            ++rightIter;
        } else {
            ++leftIter;
        }
    }

    std::move(rightIter, rightList.end(), std::back_inserter(leftList));
    rightList.clear();
}

void Person::print_Person() {
    cout << "----------------------------------------" << endl;
    cout << data[1] << " " << data[2] << " " << data[3] << endl;
    cout << data[4] << endl;
    cout << "Department: " << data[0] << endl;
    cout << "Home Phone: " << data[5] << endl;
    cout << "Work Phone: " << data[6] << endl;
    cout << "Campus Box: " << data[7] << endl;
}

int main() {
    int n; vector<Person> leftList, rightList; bool left = true; string removeWhitespace;
    cin >> n; getline(cin, removeWhitespace);
    while(n > 0){
        string department; string line;
        getline(cin, department);

        if(!left && !rightList.empty()){
            merge_sort(leftList, rightList);
        }

        while(getline(cin, line) && !line.empty()){
            if(left){
                leftList.emplace_back(department, line);
            }
            else{
                rightList.emplace_back(department, line);
            }
        }
        left = false;
        n--;
    }
    merge_sort(leftList, rightList);

    for(auto & i : leftList){
        i.print_Person();
    }

    return 0;
}
