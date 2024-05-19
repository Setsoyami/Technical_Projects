#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

bool isDigitsOnly(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.rfind('.'); 

    return (atPos != string::npos && dotPos != string::npos && dotPos > atPos + 1 && dotPos < email.length() - 1);
}

string generateCaptcha() {
    string captcha;
    srand(time(0));

    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            captcha += static_cast<char>(rand() % 26 + 'A'); 
        } else {
            captcha += static_cast<char>(rand() % 26 + 'a');
        }
    }

    return captcha;
}

const int MAX_PLAYERS = 10;
struct Player {
    string username;
    string password;
    int winCount;
    int playerMoney;
};

vector<Player> players;
Player currentPlayer;
char cont;
int bankerMoney = 10000;

void showMenu(){
    cout << "Welcome to Lucky 9 Game!" << endl;
    for (int i = 0; i < 14; i++){
        cout << "`-";
    }
    cout << endl;
    cout << "|[1] SIGN-UP                |" << endl;
    cout << "|[2] PLAY GAME              |" << endl;
    cout << "|[3] LEADERBOARD            |" <<endl;
    cout << "|[4] EXIT                   |" << endl;
    for (int i = 0; i < 14; i++){
        cout << "`-";
    }
    cout << endl;
}

void registere() {
    if (players.size() >= MAX_PLAYERS) {
        cout << "Max players reached. Cannot register more players." << endl;
        return;
    }

    Player newPlayer;
    system("cls");
    cout << "Registration" << endl;
    cout << "----------------------------" << endl;

    do {
        cout << "Enter username (at least 3 characters): ";
        cin >> newPlayer.username;
    } while (newPlayer.username.length() < 3);

    bool isValidPassword = false;
    while (!isValidPassword) {
        cout << "(at least 1 uppercase, 1 lowercase, 1 digit, 1 special character, and minimum 8 characters)" << endl;
        cout << "Enter password: ";
        cin >> newPlayer.password;

        bool hasUppercase = false, hasLowercase = false, hasDigit = false, hasSpecialChar = false;
        if (newPlayer.password.length() >= 8) {
            for (char c : newPlayer.password) {
                if (isupper(c)) {
                    hasUppercase = true;
                } else if (islower(c)) {
                    hasLowercase = true;
                } else if (isdigit(c)) {
                    hasDigit = true;
                } else if (!isalnum(c)) {
                    hasSpecialChar = true;
                }
            }
        }

        isValidPassword = (hasUppercase && hasLowercase && hasDigit && hasSpecialChar);
        if (!isValidPassword) {
            cout << "Invalid password! Please try again." << endl;
        }
    }

    string confirmPassword;
    do {
        cout << "Confirm password: ";
        cin >> confirmPassword;
    } while (newPlayer.password != confirmPassword);

    string cp;
    do {
        cout << "Enter CP (11 digits only): ";
        cin >> cp;
    } while (cp.length() != 11 || !isDigitsOnly(cp));

    string email;
    do {
        cout << "Enter email: ";
        cin >> email;
    } while (!isValidEmail(email));

    string captcha, inputCaptcha;
captcha:
    captcha = generateCaptcha();
    cout << "CAPTCHA: " << captcha << endl;
    cout << "Enter CAPTCHA: ";
    cin >> inputCaptcha;
    system("cls");
    if (inputCaptcha == captcha) {
        newPlayer.winCount = 0;
        newPlayer.playerMoney = 1000;
        players.push_back(newPlayer);
        cout << "Registration Successful!" << endl;
    } else {
        cout << "Incorrect CAPTCHA! Please try again." << endl;
        goto captcha;
    }
}

void game() {
    string inputUsername, inputPassword;
    cout << "Play Game" << endl;
    for (int i = 0 ; i < 14; i++){
        cout << "`-";
    }
    cout << endl << endl;
    cout << "Enter username: ";
    cin >> inputUsername;

    auto it = find_if(players.begin(), players.end(), [&](const Player& player) {
        return player.username == inputUsername;
    });

    if (it == players.end()) {
        cout << "Username not found!" << endl;
        return;
    }

    currentPlayer = *it;

    while (true){
        cout << "Enter password: ";
        cin >> inputPassword;
        if (inputPassword == currentPlayer.password) {
            break;
        } else {
            cout << "Incorrect Password! Please try again." << endl;
        }
    }

    do {
        while (currentPlayer.playerMoney > 0 && bankerMoney > 0) {
            int betAmount;
            system("cls");
            do {
                cout << "Enter bet amount (current money: " << currentPlayer.playerMoney << "): ";
                cin >> betAmount;
                 while (cin.fail() || betAmount < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a valid bet amount: ";
                    cin >> betAmount;
                }
            } while (betAmount > currentPlayer.playerMoney || betAmount > bankerMoney);

            int playerCard1 = rand() % 10 + 1;
            int playerCard2 = rand() % 10 + 1;
            int bankerCard1 = rand() % 10 + 1;
            int bankerCard2 = rand() % 10 + 1;

            int playerTotal = (playerCard1 + playerCard2) % 10;
            int bankerTotal = (bankerCard1 + bankerCard2) % 10;

            string result;
            if (playerTotal > bankerTotal) {
                result = "WIN";
                currentPlayer.playerMoney += betAmount;
                bankerMoney -= betAmount;
                currentPlayer.winCount++;
            } else if (playerTotal < bankerTotal) {
                result = "LOSE";
                currentPlayer.playerMoney -= betAmount;
                bankerMoney += betAmount;
            } else {
                result = "DRAW";
            }

            cout << "Player Cards: " << playerCard1 << " + " << playerCard2 << endl;
            cout << "Banker Cards: " << bankerCard1 << " + " << bankerCard2 << endl;
            cout << "Result: " << result << endl;
            cout << "Current Money: Player - " << currentPlayer.playerMoney << ", Banker - " << bankerMoney << endl;
            cout << "----------------------------" << endl;
            cout << "Do you want to continue?" << endl;
            cin >> cont;
            cont = toupper(cont);
            if (cont == 'N'){
                break;
            }
        }
        if (currentPlayer.playerMoney <= 0 || bankerMoney <= 0) {
            cout << "Game over!" << endl;
            cout << "Number of winnings: " << currentPlayer.winCount << endl;
            break;
        }
        
    } while (cont == 'Y');

    *it = currentPlayer; // Update the player in the vector
}

void showLeaderboard() {
     // Sort players by win count in descending order
    sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.winCount > b.winCount;
    });

    cout << "Leaderboard:\n";
    for (const auto& player : players) {
        cout << "Username: " << player.username << " | Wins: " << player.winCount << " | Money: " << player.playerMoney << endl;
    }
}

int main() {
    int opt;

    do {
        system("cls");
        showMenu();
        cout << "OPTION: ";
        cin >> opt;
		while (cin.fail() || opt < 1 || opt > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 4: ";
            cin >> opt;
        }
        switch (opt) {
            case 1:
                registere();
                break;

            case 2:
            	system("cls");
                game();
                break;

            case 3:
                showLeaderboard();
                cout <<"\n\n\n" "Press any key to return to the menu..." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get(); // Wait for user input to continue
                break;

            case 4:
                cout << "Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    } while (true);

    return 0;
}
