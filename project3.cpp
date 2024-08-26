#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip> // For formatting output

using namespace std;

class ItemTracker {
public:
    ItemTracker(const string& inputFileName) {
        ifstream inputFile(inputFileName);
        string item;
        while (inputFile >> item) {
            itemFrequency[item]++;
        }
        inputFile.close();
        BackupData("frequency.dat");
    }

    int GetItemFrequency(const string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0;
    }

    void PrintAllItems() const {
        for (const auto& entry : itemFrequency) {
            cout << entry.first << " " << entry.second << endl;
        }
    }

    void PrintHistogram() const {
        for (const auto& entry : itemFrequency) {
            cout << setw(15) << left << entry.first << " ";
            cout << string(entry.second, '*') << endl;
        }
    }

    void BackupData(const string& outputFileName) const {
        ofstream outputFile(outputFileName);
        for (const auto& entry : itemFrequency) {
            outputFile << entry.first << " " << entry.second << endl;
        }
        outputFile.close();
    }

private:
    map<string, int> itemFrequency;
};

int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");

    int choice;
    do {
        cout << "Menu Options:" << endl;
        cout << "1. Look up an item" << endl;
        cout << "2. Print all items with frequencies" << endl;
        cout << "3. Print histogram of item frequencies" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter the item name: ";
            getline(cin, item);
            int frequency = tracker.GetItemFrequency(item);
            cout << item << " was purchased " << frequency << " times." << endl;
            break;
        }
        case 2:
            tracker.PrintAllItems();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    } while (choice != 4);

    return 0;
}
