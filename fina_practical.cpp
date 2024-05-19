#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

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
string username, password, confirmPassword, cp, email, captcha, inputCaptcha;
const int MAX_PLAYERS = 10;
char cont;
struct Player {
    string username;
    int winCount;
};
int playerMoney = 1000;
    int bankerMoney = 10000;
    int winCount = 0;
    
void showMenu(){
	
	 cout << "Welcome to Lucky 9 Game!" << endl;
    for (int i = 0; i < 14; i ++){
    cout << "`-" ;
	} cout << endl;
    cout << "|[1] SIGN-UP                |" << endl;
    cout << "|[2] PLAY GAME              |" << endl;
    cout << "|[3] LEADERBOARD            |" <<endl;
    cout << "|[4] EXIT                   |" << endl;
    for (int i = 0; i < 14; i ++){
    cout << "`-" ;
	} cout << endl;

}
    
void registere()
{
		system("cls");
            cout << "Registration" << endl;
            cout << "----------------------------" << endl;

            
            do {
                cout << "Enter username (at least 3 characters): ";
                cin >> username;
            } while (username.length() < 3);
            

            
            bool isValidPassword = false;
            while (!isValidPassword) {
            	cout << "(at least 1 uppercase, 1 lowercase, 1 digit, 1 special character, and minimum 8 characters)" << endl;
                cout << "Enter password: ";
                cin >> password;

                
                bool hasUppercase = false, hasLowercase = false, hasDigit = false, hasSpecialChar = false;
                if (password.length () >= 8) {
                    for (char c : password) {
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

            
            do {
                cout << "Confirm password: ";
                cin >> confirmPassword;
            } while (password != confirmPassword);

            
            do {
                cout << "Enter CP (11 digits only): ";
                cin >> cp;
            } while (cp.length() != 11 || !isDigitsOnly(cp));

            
            do {
                cout << "Enter email: ";
                cin >> email;
            } while (!isValidEmail(email));

            captcha:
            captcha = generateCaptcha();
            cout << "CAPTCHA: " << captcha << endl;
        
            cout <<"Enter CAPTCHA: ";
            cin >>inputCaptcha;
            system("cls");
            if (inputCaptcha == captcha) {
            	cout << "Registration Successful!" << endl;
		}
			else {
				cout << "Incorrect CAPTCHA! Please try again." << endl;
				goto captcha;
			}
}

void game(){
		string inputPassword;
            
            cout << "Play Game" << endl;
            for (int i = 0 ; i < 14; i++){
            	cout << "`-";
			}
			cout << endl << endl;
            while (true){
            cout << "Enter password: ";
            cin >> inputPassword;
            if (inputPassword == password) {
            break;
			}
			else {
				cout << "Incorrect Password! Please try again." << endl;

			}
		}
            do {
			
            while (playerMoney > 0 && bankerMoney > 0) {
                int betAmount;
                do {
                    cout << "Enter bet amount (current money: " << playerMoney << "): ";
                    cin >> betAmount;
                } while (betAmount > playerMoney || betAmount > bankerMoney);

                
                int playerCard1 = rand() % 10 + 1;
                int playerCard2 = rand() % 10 + 1;
                int bankerCard1 = rand() % 10 + 1;
                int bankerCard2 = rand() % 10 + 1;

               
                int playerTotal = (playerCard1 + playerCard2) % 10;
                int bankerTotal = (bankerCard1 + bankerCard2) % 10;

               
                string result;
                if (playerTotal > bankerTotal) {
                    result = "WIN";
                    playerMoney += betAmount;
                    bankerMoney -= betAmount;
                    winCount++;
                } else if (playerTotal < bankerTotal) {
                    result = "LOSE";
                    playerMoney -= betAmount;
                    bankerMoney += betAmount;
                } else {
                    result = "DRAW";
                }

                cout << "Player Cards: " << playerCard1 << " + " << playerCard2 << endl;
                cout << "Banker Cards: " << bankerCard1 << " + " << bankerCard2 << endl;
                cout << "Result: " << result << endl;
                cout << "Current Money: Player - " << playerMoney << ", Banker - " << bankerMoney << endl;
                cout << "----------------------------" << endl;
                cout << "Do you want to continue?" << endl;
       		    cin >> cont;
            	cont = toupper(cont);
          		if (cont == 'N'){
          			break;
				  }
				}
				if(playerMoney <= 0 || bankerMoney <= 0)  {
					 cout << "Game over!" << endl;
           			 cout << "Number of winnings: " << winCount << endl;
           			 break;
				}
				
        } while (cont == 'Y');
           
}

int main() {
	
    int opt;
   
  	do {
  	 system("cls");
    showMenu();
    cout << "OPTION: ";
    cin >> opt;
    	
    switch (opt) {
        case 1: {
			system("cls");
            registere();
            continue;
            break;
    }
    
        case 2: {
        	system("cls");
			game();
			continue;
            break;
        }
        

        case 3: {
        	
			 Player leaderboard[MAX_PLAYERS];

    		leaderboard[0] = {username, winCount};
    		leaderboard[1] = {username, winCount};
    		leaderboard[2] = {username, winCount};
    		
    		cout << "Leaderboard:\n";
   		 for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!leaderboard[i].username.empty()) {
            cout << "Username: " << leaderboard[i].username << " | Wins: " << leaderboard[i].winCount << endl;
            
        }
        
    }
			
		}

        case 4: {
        		
            
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
   	     }
  	  } 
	} while (true);

    return 0;
}