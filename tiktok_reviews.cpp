#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAX_REVIEWS = 500;

string trends[MAX_REVIEWS];
int ratings[MAX_REVIEWS];
string reviewers[MAX_REVIEWS];

int reviewCount = 0;

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void loadReviews() {
    ifstream file("tiktok_reviews.txt");
    if (!file) return;

    string line;
    while (getline(file, line) && reviewCount < MAX_REVIEWS) {
        if (line.empty()) continue;

        size_t lastSpace = line.find_last_of(' ');
        size_t secondLastSpace = line.find_last_of(' ', lastSpace - 1);

        string trend = line.substr(0, secondLastSpace);
        int rating = stoi(line.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1));
        string reviewer = line.substr(lastSpace + 1);

        trends[reviewCount] = trend;
        ratings[reviewCount] = rating;
        reviewers[reviewCount] = reviewer;

        reviewCount++;
    }

    file.close();
}


void displayReviews() {
    if (reviewCount == 0) {
        cout << "No reviews found.\n";
        return;
    }

    cout << left << setw(25) << "TikTok Trend"
         << setw(10) << "Rating"
         << setw(15) << "Reviewer" << endl;

    cout << "-----------------------------------------------------\n";

    for (int i = 0; i < reviewCount; i++) {
        cout << left << setw(25) << trends[i]
             << setw(10) << ratings[i]
             << setw(15) << reviewers[i] << endl;
    }
}

void searchReview() {
    cout << "Enter trend/influencer name: ";
    string searchTerm;
    cin.ignore();
    getline(cin, searchTerm);

    string lowerSearch = toLowerCase(searchTerm);
    bool found = false;

    for (int i = 0; i < reviewCount; i++) {
        if (toLowerCase(trends[i]) == lowerSearch) {
            cout << "\nTrend: " << trends[i]
                 << ", Rating: " << ratings[i]
                 << ", Reviewed by: " << reviewers[i] << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No review found for '" << searchTerm << "'.\n";
    }
}

void addReview() {
    if (reviewCount >= MAX_REVIEWS) {
        cout << "Database is full.\n";
        return;
    }

    cin.ignore();
    string trend, reviewer;
    int rating;

    cout << "Enter trend/influencer name: ";
    getline(cin, trend);

    cout << "Enter rating (1-10): ";
    cin >> rating;

    cout << "Enter reviewer name: ";
    cin >> reviewer;

    trends[reviewCount] = trend;
    ratings[reviewCount] = rating;
    reviewers[reviewCount] = reviewer;

    reviewCount++;

    ofstream file("tiktok_reviews.txt", ios::app);
    file << trend << " " << rating << " " << reviewer << endl;
    file.close();

    cout << "Review added successfully!\n";
}

void menu() {
    int choice = 0;

    while (choice != 4) {
        cout << "\n==============================\n";
        cout << "  TikTok Review Database\n";
        cout << "==============================\n";
        cout << "1. View All Reviews\n";
        cout << "2. Search for a Trend/Influencer\n";
        cout << "3. Add a New Review\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << endl;

        switch (choice) {
            case 1:
                displayReviews();
                break;
            case 2:
                searchReview();
                break;
            case 3:
                addReview();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    loadReviews();
    menu();
    return 0;
}