#include <Arduino.h>

//Library imports required for I2C eeprom communication.
#include <Wire.h>
#include <SparkFun_External_EEPROM.h>

const int eeprom_chip_size = 128; // In Kibibit (kib) defined by what chip you have factors of 1024. 1 kib = 1024 bits.
int odometer_start_index = 4; // In actual script this will need to be coded in to account for all calibration settings. May help to automate to avoid errors.
// For this script Due to int in memory index 0, the first four memory addresses (bytes) will be taken (0,1,2,3) therefore we need to start writting at index 4.
int odometer_last_potential_index = ((eeprom_chip_size * 1024)/8)-4; // converted to bits then bytes, then -1 for last index and -3 for bytes required as one is already counted as last index.
// For above indexes it is assumed a int 32 value is used (4 bytes)
// Note on the esp32s int is also 4 bytes unlike the normal arduinos where int in 2 bytes. the arduino nano esp32 is 32 bit while traditional arduinos are 16bit or 8 bit.
char option_selection;
char temp[1] = {'2'}; //Just to setup the digit input for setting saving test.
int digit_to_write;
int digit_read;
// For actual settings, data type is adjusted depending on what is sutable and takes up the least amount of storage space.
// It must be noted that memory addresses will also need to be adjusted for the final design depending on the data type lengths.
int list_read;
int odometer_reading = 0; // Floats are being used to retain accurate odometer readings. anything less than 0.1 will not be displayed in final design.
int odometer_address = odometer_start_index;

ExternalEEPROM eeprom_object;

char input_digit();


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Used for user selection code.
  }

  Wire.begin();
  eeprom_object.setMemoryType(eeprom_chip_size); // Set as 128 as that is my eeprom chip. Adjust if needed.
  if (eeprom_object.begin() == false){
    Serial.println("No memory detected code will break.");
    while (true){};
  }
  Serial.println("Memory Detected");
  Serial.print("Mem size in bytes: ");
  Serial.println(eeprom_object.length());
  eeprom_object.erase(); // Clear eeprom so that previous code execution does not mess with tests.
}


void loop() {

  // Option input section
  Serial.println("Please input option digit");
  option_selection = input_digit();

  if (option_selection == '1'){
    // Writting to the first address of the eeprom.
    Serial.println("Type digit to save");
    temp[0] = input_digit();
    digit_to_write = atoi(temp);
    eeprom_object.put(0,digit_to_write);
  }

  else if (option_selection == '2'){
    // Reading from the first eeprom address.
    eeprom_object.get(0,digit_read);
    Serial.println("The digit read is:");
    Serial.println(digit_read);
  }

  else if (option_selection == '3'){
    // Writting many odometer readings to eeprom incrementing by 1 which will represent 0.1Km
    // As each int on the esp32 arduino is 4 bytes, we must iterate 4 memory addresses over so that we do not over write portions of previous int values.
    Serial.print("Writting data to eeprom");
    // For testing reasons I am writting 1005 values where it increments by 1 for each step.
    // This helps to test writitng of data and the the resetting of memory addresses.
    for (int i=1; i<=1005;i++){
      odometer_address = odometer_address + 4;
      if (odometer_address > odometer_last_potential_index){
        // Catch to reset odometer indexes if it reaches the end of the eeprom memory
        odometer_address = odometer_start_index; 
      }
      odometer_reading ++;
      eeprom_object.put(odometer_address,odometer_reading);
    }
  }

  else if (option_selection == '4'){
    // Reading number list and outputting highest value and eeprom position
    //TODO: Add in functionality to handle when reaching the end of the eeprom memopry to be able to write over some original data at the first index.
    Serial.println("Finding Highest value and address of the value");
    for (int i = odometer_start_index; i<=odometer_last_potential_index; i = i+4){
      // Reading each eeprom odometer address in turn to find the highest value
      // Returning value and address position.
      eeprom_object.get(i,list_read);
      if (odometer_reading < list_read){
        odometer_reading = list_read;
        odometer_address = i;
      }
    }
    Serial.print("Highest Odometer reading = ");
    Serial.println(odometer_reading);
    Serial.print("Highest Odometer reading address = ");
    Serial.println(odometer_address);


  }
  else{
    // Error catch.
    Serial.println("Option does not exist please type in opions 1-4");
  }
}


// Function which makes sure a digit is inputed into the serial terminal.
char input_digit(){
  char input;
  boolean is_digit = false;
  Serial.println("type digit:");
  while (is_digit == false){
    while (!Serial.available()) {};
    input = Serial.read();
    if (isdigit(input)){
      is_digit = true;
    }
    else{
      Serial.println("Not a digit please type in a digit:");
    }
  }
  return(input);
}