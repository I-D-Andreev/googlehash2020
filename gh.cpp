#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

long long TOTAL_DAYS = 0;
long long CURRENT_DAY = 0;

// answers
long long ANS_LIBS_TAKEN = 0;
vector<long long> ANS_LIBRARIES_TAKEN_IDS;


struct Book {
public:
    long long id = 100001;
    long long score = 0;

    Book() {}

    Book(long long _id, long long _score) : id(_id), score(_score) {} // same as id=_id; score=_score etc

    bool operator>(const Book &other) const {
        return score > other.score;
    }
};

Book idbook[100001]; // idbook[id] keeps book with ID equal to id
struct Library {
public:
    long long id;
    long long num_books;
    long long signup_time;
    long long books_day; // books per day which can be shipped
    vector<Book> books;
    bool is_taken = false;

    long long score = 0;
    long long books_to_be_taken = 0;

    Library() {}

    Library(long long _id, long long _numbooks, long long _signuptime, long long _booksday) :
            id(_id), num_books(_numbooks), signup_time(_signuptime), books_day(_booksday) {}


    long long update() {
        for (Book &book : books) {
            book.score = idbook[book.id].score; //update the score
        }
        sort(books.begin(), books.end(), greater<Book>());
    }

    long long calculate_worth() {
        if (is_taken) {
            score = 0;
            return 0;
        }

        if (CURRENT_DAY + signup_time >= TOTAL_DAYS) {
            return 0;
        }

        long long _score = 0;
        long long days_left = TOTAL_DAYS - (CURRENT_DAY + signup_time);
        days_left = max(days_left, 0LL);

        unsigned long long books_able_shipped = days_left * books_day;
        books_to_be_taken = min(books_able_shipped, books.size());
        for (int i = 0; i < books_to_be_taken; i++) {
            _score += books[i].score;
        }

        _score = _score / signup_time;
        score = _score;
        return _score;
    }

    void take_this_lib() {
        is_taken = true;
        ANS_LIBS_TAKEN++;
        ANS_LIBRARIES_TAKEN_IDS.push_back(id);

        for (int i = 0; i < books_to_be_taken; i++) {
            idbook[books[i].id].score = 0;
        }

        CURRENT_DAY = CURRENT_DAY + signup_time;
    }
};

Library idlib[100001]; // idlib[id] keeps lib with ID equal to id

// variables
long long books, libraries;

int main() {
    cin >> books >> libraries >> TOTAL_DAYS;
    long long score = 0;
    for (int i = 0; i < books; ++i) {
        cin >> score;
        idbook[i] = Book(i, score);
    }

    long long numbooks, signtime, bookshp, bookid;
    for (int i = 0; i < libraries; i++) {
        cin >> numbooks >> signtime >> bookshp;

        Library lib(i, numbooks, signtime, bookshp);
        for (int j = 0; j < numbooks; j++) {
            cin >> bookid;
            lib.books.push_back(idbook[bookid]);
        }
        // sort them Biggest score first
//        sort(lib.books.begin(), lib.books.end(), greater<Book>());

        idlib[i] = move(lib); // faster assignment
    }


    long long maxlibsc = 0;
    long long maxlibid = -1;
    for (CURRENT_DAY = 0; CURRENT_DAY < TOTAL_DAYS;) {
        maxlibsc = 0;
        maxlibid = -1;
        for (int i = 0; i < libraries; i++) {
            if (!idlib[i].is_taken) {
                idlib[i].update();

                idlib[i].calculate_worth();
                if (idlib[i].score > maxlibsc) {
                    maxlibsc = idlib[i].score;
                    maxlibid = idlib[i].id;
                }
            }
        }

        if (maxlibid == -1) {
            break;
        }
//        cout << maxlibid << " |  sc: " << idlib[maxlibid].score << " | bt: " << idlib[maxlibid].books_to_be_taken<<endl;
        idlib[maxlibid].take_this_lib();
    }

    cout << ANS_LIBS_TAKEN << endl;
    for (long long lid: ANS_LIBRARIES_TAKEN_IDS) {
        cout << lid << " " << idlib[lid].books_to_be_taken << endl;
        for (int i = 0; i < idlib[lid].books_to_be_taken; i++) {
            cout << idlib[lid].books[i].id << " ";
        }
        cout << endl;
    }


}


/*
6 2 7
1 2 3 6 5 4
5 2 2
0 1 2 3 4
4 3 1
3 2 5 0

     for(int i=0; i<libraries; i++){
        cout << "Library" << i<<endl;
        for(auto& book : idlib[i].books){
            cout << "id: " << book.id << " score: " << book.score <<" |";
        }
        cout<<endl;
    }
 */