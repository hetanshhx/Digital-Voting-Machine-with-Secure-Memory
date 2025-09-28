#include <LiquidCrystal.h>
#include <EEPROM.h>

// LCD Pin Mapping
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button Pins
const int candidateA_Button = 2;
const int candidateB_Button = 3;
const int results_Button   = 4;
const int home_Button      = 5;

// EEPROM Addresses
const int candidateA_Address = 0;
const int candidateB_Address = 1;

// State Machine
enum State { VOTING_MODE, RESULTS_MODE, MESSAGE_MODE };
State currentState = VOTING_MODE;

// Debounce Handling
unsigned long lastActionTime = 0;
const unsigned long debounceDelay = 250;

// ==================================================
// Function Prototypes
// ==================================================
void displayVotingScreen();
void displayResults();
void recordVote(int candidateAddress, const char* candidateName);
bool isButtonPressed(int pin);
void handleVotingMode();
void handleResultsMode();
void handleMessageMode();

// ==================================================
// Initialize EEPROM
// ==================================================
void initializeVoteCounts() {
  EEPROM.write(candidateA_Address, 0);
  EEPROM.write(candidateB_Address, 0);
}

// ==================================================
// SETUP
// ==================================================
void setup() {
  lcd.begin(16, 2);
  initializeVoteCounts();

  lcd.print("Digital Voting");
  lcd.setCursor(0, 1);
  lcd.print("Machine Ready");
  delay(1000);

  pinMode(candidateA_Button, INPUT_PULLUP);
  pinMode(candidateB_Button, INPUT_PULLUP);
  pinMode(results_Button,   INPUT_PULLUP);
  pinMode(home_Button,      INPUT_PULLUP);

  displayVotingScreen();
}

// ==================================================
// MAIN LOOP
// ==================================================
void loop() {
  // Check for a valid button press only once per loop
  int pressedButton = 0; // 0 means no button pressed
  
  // Check if enough time has passed since the last action
  if ((millis() - lastActionTime) > debounceDelay) {
    if (digitalRead(candidateA_Button) == LOW) {
      pressedButton = candidateA_Button;
    } else if (digitalRead(candidateB_Button) == LOW) {
      pressedButton = candidateB_Button;
    } else if (digitalRead(results_Button) == LOW) {
      pressedButton = results_Button;
    } else if (digitalRead(home_Button) == LOW) {
      pressedButton = home_Button;
    }

    // If a button was pressed, update the timer and handle the action
    if (pressedButton != 0) {
      lastActionTime = millis();
      handleButtonPress(pressedButton);
    }
  }
}

// ==================================================
// Central Button Handler
// ==================================================
void handleButtonPress(int button) {
  switch (currentState) {
    case VOTING_MODE:
      if (button == candidateA_Button) {
        recordVote(candidateA_Address, "Candidate A");
      } else if (button == candidateB_Button) {
        recordVote(candidateB_Address, "Candidate B");
      } else if (button == results_Button) {
        currentState = RESULTS_MODE;
        displayResults();
      }
      break;

    case RESULTS_MODE:
      if (button == home_Button) {
        currentState = VOTING_MODE;
        displayVotingScreen(); // Takes you back to the main screen
      }
      break;

    case MESSAGE_MODE:
      if (button == home_Button) {
        currentState = VOTING_MODE;
        displayVotingScreen(); // Takes you back to the main screen
      }
      break;
  }
}

// ==================================================
// RECORD VOTES
// ==================================================
void recordVote(int candidateAddress, const char* candidateName) {
  byte currentVotes = EEPROM.read(candidateAddress);
  if (currentVotes < 255) {
    currentVotes++;
  }
  EEPROM.write(candidateAddress, currentVotes);

  lcd.clear();
  lcd.print("Vote Cast For:");
  lcd.setCursor(0, 1);
  lcd.print(candidateName);

  currentState = MESSAGE_MODE;
}

// ==================================================
// DISPLAY RESULTS
// ==================================================
void displayResults() {
  lcd.clear();
  lcd.print("--- Results ---");
  
  int votesA = EEPROM.read(candidateA_Address);
  int votesB = EEPROM.read(candidateB_Address);

  lcd.setCursor(0, 1);
  lcd.print("A:");
  lcd.print(votesA);
  lcd.print("   B:");
  lcd.print(votesB);
}

// ==================================================
// DISPLAY VOTING SCREEN
// ==================================================
void displayVotingScreen() {
  lcd.clear();
  lcd.print("Press to Vote");
  lcd.setCursor(0, 1);
  lcd.print("or view results");
}

void handleVotingMode() {}
void handleResultsMode() {}
void handleMessageMode() {}