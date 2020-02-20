#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;


struct Book {
public:
    long long id = 100001;
    long long score = 0;

    Book() {}

    Book(long long _id, long long _score) : id(_id), score(_score) {} // same as id=_id; score=_score etc

    bool operator>(const Book& other) const {
        return score > other.score;
    }
};

struct Library {
public:
    long long id;
    long long num_books;
    long long signup_time;
    long long books_day; // books per day which can be shipped
    vector<Book> books;

    Library() {}

    Library(long long _id, long long _numbooks, long long _signuptime, long long _booksday) :
            id(_id), num_books(_numbooks), signup_time(_signuptime), books_day(_booksday) {}

    long long calculate_worth() {
        long long score = 0;
        // calculate score by taking current day into account and then adding the time to signup
        // then calculate how much we can get from books up to the END of the days
        // When we pick the next library, we should also set the scores of the books it is going to send off to 0
        // (in idbook first then in libraries)
        return score;
    }
};

// variables
long long books, libraries, days, curr_day = 0;
Book idbook[100001]; // idbook[id] keeps book with ID equal to id
Library idlib[100001]; // idlib[id] keeps lib with ID equal to id
int main() {
//    scanf("%lld%lld%lld", &books, &libraries, &days); // equal to cin>>books>>... but faster
    cin >> books >> libraries >> days;

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
        sort(lib.books.begin(), lib.books.end(), greater<Book>());

        idlib[i] = move(lib); // faster assignment
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