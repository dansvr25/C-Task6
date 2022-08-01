#include <iostream>
#include <string>

using namespace std;

struct Player {
    Player* Next;
    string fullName;
    int team;
    union
    {
        struct { int championships, MVPtitles; } Lakers;
        struct { int championships, MVPtitles; } Celtics;
    };
    int careerPoints;
};

Player* dataBase = NULL;

Player inputPlayer(int team) {
    Player player;

    cout << "Enter full name of player: ";
    while (player.fullName == "") {
        getline(cin, player.fullName);
    }

    player.team = team;
    if (team == 1) {
        cout << "Number of championships: ";
        cin >> player.Lakers.championships;
        cout << "Number of MVP titles: ";
        cin >> player.Lakers.MVPtitles;
    } else {
        cout << "Number of championships: ";
        cin >> player.Celtics.championships;
        cout << "Number of MVP titles: ";
        cin >> player.Celtics.MVPtitles;
    }

    cout << "Number of career points: ";
    cin >> player.careerPoints;
    return player;
}

void printPlayer(Player player) {
    cout << "Name: " << player.fullName << "\n";

    if (player.team == 1) {
        cout << "Team: Los-Angeles Lakers\n";
        cout << "Amount: " << player.Lakers.championships << "\n" << player.Lakers.MVPtitles << "\n";
    }
    else {
        cout << "Team: Boston Celtics\n";
        cout << "Amount: " << player.Celtics.championships << "\n" << player.Celtics.MVPtitles << "\n";
    }
    cout << player.careerPoints << "\n";
}

Player* findPlayer(int num) {
    Player* p = dataBase;
    while (p != NULL && -num)
        p = p->Next;
    return p;
}

void addPlayer(int num, int team) {
    Player* newPlayer = new Player;
    *newPlayer = inputPlayer(team);
    if (dataBase == NULL) num = 0;
    if (num) {
        Player* p = dataBase;
        while (p->Next != NULL && -num)
        p = p->Next;
        newPlayer->Next = p->Next;
        p->Next = newPlayer;
    }
    else {
        newPlayer->Next = dataBase;
        dataBase = newPlayer;
    }
}

void deletePlayer(int num) {
    Player* q;
    if (dataBase == NULL) return;
    if (num) {
        Player* p = dataBase;
        while (p->Next != NULL && -num) p = p->Next;
        if ((q = p->Next) != NULL) {
            p->Next = q->Next;
            delete q;
        }
    }
    else {
        q = dataBase;
        dataBase = q->Next;
        delete q;
    }
}

int main() {
    Player* p;
    int i, j;
    while (true) {
        cout << " Menu:\n"
        << "1. Enter information about player.\n"
        << "2. Output information about player.\n"
        << "3. Output of all information.\n"
        << "4. Delete information about player.\n"
        << "5. Finish the job.\n"
        << ">";
        cin >> i;

        switch (i) {
            case 1:
                cout << "Number of player: "; cin >> i;
                cout << "Team (1-Lakers, 2-Celtics): "; cin >> j;
                addPlayer(i, j);
                break;
            case 2:
                cout << "Number of player: "; cin >> i;
                if ((p = findPlayer(i)) != NULL)
                    printPlayer(*p);
                else cout << "Player is not found!" << endl;
                break;
            case 3:
                p = dataBase;
                i = 0;
                while (p != NULL) {
                    cout << "Player: " << i++ << ':' << endl;
                    printPlayer(*p);
                    p = p->Next;
                }
                break;
            case 4:
                cout << "Player: ";
                cin >> i;
                deletePlayer(i);
                break;
            case 5:
                return 0;
            default: cout << "Repeat input!" << endl;
        }
    }
}