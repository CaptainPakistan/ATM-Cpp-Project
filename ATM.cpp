#include <iostream>
#include <fstream>
using namespace std;


const int MAX_USERS = 5;

char userNames[MAX_USERS][100];  
int userPINs[MAX_USERS];         
int userBalances[MAX_USERS];     
int userCount = 0;               

void accountMenu() {
    cout << "\nAccount Menu:\n";
    cout << "1. Sign Up (Create new account)\n";
    cout << "2. Log In (Access your account)\n";
    cout << "3. View Accounts\n";
    cout << "4. Delete Accounts\n";
    cout << "5. Exit\n";
}

void atmMenu() {
    cout << "\nATM Menu:\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Log Out\n";
}

void signUp() {
    if (userCount >= MAX_USERS) {
        
		cout << "Sorry, maximum user accounts reached.\n";
        return;
    }

    cin.ignore(); 
    cout << "Enter your full name: ";
    cin.getline(userNames[userCount], 100);
    int newPin;
    int confirmPin;
    cout << "Set a 4-digit PIN: ";
    
    
    while (true){
    	
        cin>>newPin;
        if (cin.fail()){
            cout<<"Invalid Input\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
    if (newPin < 1000 || newPin > 9999) {
    	
    cout << "PIN must be a 4-digit number.\n";
    continue;}
    int pinUsed = false;
     for (int i = 0; i < userCount; i++) {
    if (userPINs[i] == newPin) {
        cout <<"PIN already used. Choose a different one.\n";
        pinUsed = true;
        break;}
}

if (!pinUsed){
	cout<<"Confirm PIN: ";
	cin>>confirmPin;
	if (confirmPin== newPin){
	break;	
	}
	else{
		cout<<"PIN did not match\n";
		continue;
	}
    }
}

   
    userPINs[userCount]= newPin;
    userBalances[userCount] = 1000;  

    cout << "Successfully created Account for " << userNames[userCount] << "!\n";
    
    userCount++;
    
}

int logIn() {
    if (userCount == 0) {
        cout << "No users signed up yet. Please sign up first.\n";
        return -1;
    }

    int enteredPin;
    int attempts=0;
    int maxAttempts=3;
    
    while (attempts<maxAttempts){
	
    cout << "\nNow Enter your PIN to LOGIN: ";
    cin >> enteredPin;
    cout<<endl;
	attempts++;
 if (cin.fail()) {
            cout << "Invalid Input!\nYou have " << maxAttempts - attempts << " attempts left\n";
            cin.clear();
            cin.ignore(1000, '\n');
            if (maxAttempts - attempts == 0) {
            cout << "Too many attempts, LOGIN failed....\n";
            return -1;
        }
		continue;             
        }

	

    for (int i = 0; i < userCount; i++) {
        if (userPINs[i] == enteredPin) {
            cout << "Welcome back, " << userNames[i] << "!\n";
            return i;
        }
    }
 
        if (attempts == maxAttempts) {
            cout << "Incorrect PIN.\nToo many attempts, LOGIN failed....\n";
            cin.ignore(1000, '\n');
            return -1;
        } else {
            cout << "Incorrect PIN.\nYou have " << maxAttempts - attempts << " attempts left\n";
            cin.ignore(1000, '\n');
        }

    }
    
    return -1;  
}

void view() {
    if (userCount == 0) {
        cout << "No users to view. Please sign up first.\n";
        return ;
    }
  for (int i=0; i<userCount; i++){
      cout<<i+1<<". "<<userNames[i]<<endl;
  }
    
}
void delAccount() {
    if (userCount == 0) {
        cout << "No users to delete.\n";
        return;
    }

    cout << "Enter the PIN of the account to delete: ";
    int enteredPin;
    cin >> enteredPin;

    int indexToDelete = -1;

    for (int i = 0; i < userCount; i++) {
        if (userPINs[i] == enteredPin) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "No account found with that PIN.\n";
        return;
    }

    
    for (int i = indexToDelete; i < userCount - 1; i++) {
    
        int j = 0;
        while (userNames[i + 1][j] != '\0') {
            userNames[i][j] = userNames[i + 1][j];
            j++;
        }
        userNames[i][j] = '\0';  

        
        userPINs[i] = userPINs[i + 1];
        userBalances[i] = userBalances[i + 1];
    }

    userCount--;
    cout << "Account deleted successfully.\n";
    view();
}


void checkBalance(int userIndex) {
    cout << "Your current balance is: $" << userBalances[userIndex] << endl;
}

void deposit(int userIndex) {
    int amount;
    cout << "Enter amount to deposit: $";
    cin >> amount;
    cout<<endl;
    
    if (amount > 0) {
        userBalances[userIndex] += amount;
        cout << "Deposited successfully!\n";
        cout << "Your updated balance is now: $" << userBalances[userIndex] << endl;
    } else {
        cout << "Invalid amount.\n";
    }
}

void withdraw(int userIndex) {
    int amount;
    cout << "Enter amount to withdraw: $";
    cin >> amount;
    cout<<endl;
    if (amount > userBalances[userIndex]) {
        cout << "Insufficient funds.\n";
    } else if (amount <= 0) {
        cout << "Invalid amount.\n";
    } else {
        userBalances[userIndex] -= amount;
        cout << "Withdrawn successfully!\n";
        cout << "Your updated balance is now: $" << userBalances[userIndex] << endl;
    }
}

void saveDataToFile(){
	ofstream outFile("data.txt");
	outFile<<userCount<<endl;
	
	for (int i=0; i<userCount ;i++){
		outFile<<userNames[i];
		outFile<<endl;  
        outFile<<userPINs[i];
        outFile<<endl;
        outFile<<userBalances[i];
        outFile<<endl;
	} 
	outFile.close();
}
void loadDataFromFile(){
	ifstream inFile("data.txt");
	if(!inFile){
		return;
	}
	inFile>>userCount;
	inFile.ignore();
	
	for (int i=0; i<userCount ;i++){
		inFile.getline(userNames[i],100);  
        inFile>>userPINs[i];
        inFile>>userBalances[i];
        inFile.ignore();
	} 
	inFile.close();
}
int main() {
	loadDataFromFile();
	cout<<"This ATM is designed by Captain Pakistan......\nWELCOME!!"<<endl;
	
    int mainChoice;

    do {
        accountMenu();
        cout << "Choose an option: ";
        cin >> mainChoice;
        system("clear");

        switch(mainChoice) {
            case 1:  // Sign Up
                {
				signUp();
                saveDataToFile();
                
                
                	int userIndex = logIn();
                if (userIndex != -1) {
                    int atmChoice;
                     do {
                        atmMenu();
                        cout << "Choose an option: ";
                        cin >> atmChoice;

                        switch(atmChoice) {
                            case 1:
                                checkBalance(userIndex);
                                            break;
                            case 2:
                                deposit(userIndex);
                                saveDataToFile();
                        
                                break;
                            case 3:
                                withdraw(userIndex);
                                saveDataToFile();
                                  
                                break;
                            case 4:
                                cout << "Logging out...\n";
                                break;
                            default:
							cout << "Invalid option.\n";
    
                            if (cin.fail()) {
                            cin.clear();
                           cin.ignore(1000, '\n');}
                        }
                    } while (atmChoice != 4);
                }
            
                break;}

            case 2: { 
                int userIndex = logIn();
                if (userIndex != -1) {
                    int atmChoice;
                     do {
                        atmMenu();
                        cout << "Choose an option: ";
                        cin >> atmChoice;

                        switch(atmChoice) {
                            case 1:
                                checkBalance(userIndex);
                                
                                break;
                            case 2:
                                deposit(userIndex);
                                saveDataToFile();
                                  
                                break;
                            case 3:
                                withdraw(userIndex);
                                saveDataToFile();
                                 
                                break;
                            case 4:
                                cout << "Logging out...\n";
                                break;
                            default:{ if (cin.fail()){
                                cout << "Invalid option.\n";
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                                
                            }
                        }
                    } while (atmChoice != 4);
                }
                break;
            }
            case 3: view() ; break;
             
            case 4: delAccount(); saveDataToFile();
             break;

            case 5:
                cout << "Thank you for using the ATM. Goodbye!\n";
                break;

            default: { if(cin.fail()){
                 cout << "Invalid option. Try again.\n";
                 cin.clear();
                 cin.ignore(10000, '\n');}
            }
               
        
}
    } while (mainChoice != 5);
    saveDataToFile();
    return 0;
}
