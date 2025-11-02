# Eeprom Test for CBR dash project

This testing script is used to test the functionality of the external eeprom chip. The [CAT24C128](https://www.mouser.co.uk/ProductDetail/onsemi/CAT24C128WI-GT3?qs=rZgeL6XvLwaw%2FcBtNmrs8w%3D%3D) eeprom chip is used due to it being an I2C based eeprom chip and the similarity to the 512 Kbit version that is part of the [Sparkfun eeprom break out](https://www.sparkfun.com/sparkfun-qwiic-eeprom-breakout-512kbit.html). This gives a good code reference due to the [library and guide written](https://learn.sparkfun.com/tutorials/qwiic-eeprom-hookup-guide/all) for it. DFrobot have a similar [guide](https://wiki.dfrobot.com/Gravity__I2C_EEPROM_Data_Storage_Module_SKU__DFR0117#Connection%20Diagram) for their eeprom module which uses the same CAT24 eeprom chips that spark fun used. Both guides have been used as reference to create this test script and by effect the full dash code.

The test circuit is the V1 full PCB version with all components included due to the eeprom chip being SMD mounted.

Make sure to include the [sparkfun external eeprom I2C library](https://github.com/sparkfun/SparkFun_External_EEPROM_Arduino_Library/tree/main) in your project.

The script does a few things based on the serial input given to it to test the read and write functionality of the device. In the serial monitor the user is presented with a few options that do different things:

- 1 = Write an integer a user inputs to the first memory address.

- 2 = Read the integer in the first memory address

- 3 = Write a list of numbers into the eeprom starting with the 2nd aviable memory address.

- 4 = Read and find the highest number in the eeprom starting from the 2nd avaliable memory address.

Please note that memory address is dependant on the data types that come before it. For example an int takes 4 bytes (with an esp32 32 bit, 2 bytes with 16bit arduinos) while a float takes 4. Therefore, for an int in the first memory address the next avalaible memory address would be the 5th one (remember indexing starts at 0 thus memory index is 4 for 5th position).

## Why these features are tested

The features above are tested so that we are able to have precistant constantly undating data with the dash. Options 1 and 2 in the testing script is for testing the feasability of saving calibration data to the eeprom chip. Options 3 and 4 are for testing the ability to save odometer data into the eeprom. See the bellow note on odometer data problems.

## Important note on Odometer and trip meter data

Unlike most data that would be saved to this eeprom. Odometer and trip data constantly need to be updated very frequently. One concern is wear of the memory addresses if only one is used for each. Each address has a finite ammount of times it can be written to, thus constatly writting to one will make it fail very quickly. This can be mitigated by using a wear leveling stategy. Implementing this will help the eeprom chip to last longer.

For trip data, the last trip reset value n(when you reset the trip distance) will be retained in the eeprom. This means that the actual value will have to be calculated by comparing it to the current odometer reading. At the initial startup, the eeprom trip reset value will be read and compared against the odometer reading to give the trip value. This will be saved and updated in ram by the same ammount that the odometer reading is updated with. This allows less writes to the eeprom chip saving write lifes.

Odometer data is where wear leveling is nessary as the value must be imediatly saved to eeprom incase the bike suddenly shuts down thus, wear leveling is needed. The way this will work is by iterating over each memory address till the end of the addresses is reached. Once the last memory address is reached, it will return to the first address to continue the same process. This means that the writes are spread over many memory addresses leveling out the wear due to odometer readings. At startup, the memory addresses for the odometer data will be read. The highest value and it's position will be loaded into RAM so that the dash has accurate odometer readings and knows the last location it wrote to. For each increase of 0.1Km the odometer reading will be captured in eeprom. The start memory address for this is dependent on how much memory is required for calibration data for the dash. Similarly the end memory address is dependent on the size of the data type that needs to be written and the size of the eeprom chip. For example, we can write to memory addresses 0 to 9 where each address is a byte (8 bits,10 bytes worth of memory). Assume there is no static data and it is just odometer data. Asssume we are using floats to hold odometer data (4 bytes). We can start at memory address 0 then write to address 4 (first value sits in addresses 0-3, secound in 4-7). Even though we have addresses 8 and 9. We are unable to write to them as we need two more bytes to write the full float value.

Odometer data will be an integer to avoid errors with floating point math. For esp32s they work on 32bit microprocessors meaning that ints are 32 bits instead of the typical 16 bits in arduino. This means that the max int value is 2,147,483,647. This is plenty high enough for an odometer reading if using my ideal unit of Km. The dash will use all SI units for data and convert when displaying data. It must be noted that the first value of the int will represent the 0.1 of a kilometer (100 meters). Everytime the odometer reading updates by that 0.1Km it will be saved to eeprom to reduce writes. At run time, a separate variable will keep track of how much distance has been traveled and once it reaches the 0.1km threshold it will trigger an odomeeer reading update. It will then reset it's self back to 0 to get back to that 0.1km threashold. The exact unit it will use is still to be decided as of writting (could be cm to stick to int math or it could be m to use floating point math). This will clearly lead to the odometer reading being a bit lower than the actual distance traveled but for my use case that is ok. It will also negate any addition problems with floating point math if it is used.

This test script will contain a calculation to find the last memory address it can write for options 3 and 4.
