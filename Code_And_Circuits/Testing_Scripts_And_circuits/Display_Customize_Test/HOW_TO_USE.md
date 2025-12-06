# Customizing display testing for CBR dash project

This testing script has been created to test the functionality of using the [U8g2 graphics library for monochrome displays](https://github.com/olikraus/u8g2) on the [NHD-C12832A1Z-FS(RGB)-FBW-3V](https://newhavendisplay.com/128x32-graphic-cog-lcd-fstn-display-with-rgb-backlight/) Newhaven display that will be used for the dash.

This script will include rendering of speed, trip and odometer data. This will cycle through a few numbers to see what it looks like. It will also cycle through different layouts and fonts to see all of them to choose the best one for the dash.

The circuit is the V1 version of the PCB. You could directly wire it instead of using the PCB but for testing to make sure the PCB was correct i used this.

An important note is that I am using the hardware SPI to run my display. That will effect the setup code. The controller on this display is the ST7565R SPI controller this also has an effect on the code if you are using something different. See code comments for better info on setting up the display correctly.

## Unique non ideal wiring and Pin Assignment

An important note on my setup is that I have used one of the hardware SPI pins as the dc pin also known as the A0 pin or register select pin in my use case. I have specifically used the Controller In Peripheral Out (CIPO) (also known as the Master In Slave Out (MISO)) pin as the dc /register select/ A0 pin. This causes some issues as the pin does not get correctly setup when initializing the display class using hardware SPI. To fix this I added in the following code before and after the `u8g2.begin();` line to fix it:

```c++
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
```

Ideally you would avoid using any of the hardware SPI pins that are not necessary. However for my use case I was running out of available pins to utilize for the dash so used it.

## Custom Graphics (GIMP method)

I have made some custom graphics that I have used in the testing scripts. This was so that I could load them onto the display to see what it would look like. Some of these graphics will also be used on the final design.

To create all the graphics I used [gimp](https://www.gimp.org/) the file of which is saved in the `Custom_Images` folder.

To setup gimp for this display follow the guide bellow. Note that adjustments can be mode if using a different sized display in the appropriate places (eg 128 by 64 instead of 128 by 32):

1. Create a new file through `File > New`. Setting the image size to your specific display in Pixels(px). For my display it is 128 width, 32 height.

2. For new files the default colour setting is RGB. to set the black and white setting of the lcd graphics display enter `Image > Mode > Indexed`. In this menu select the `Use black and white (1-bit pallet)`. This will set your workspace to be only black and white.

3. If your grid has not appeared. It could be beneficial to you to see it by ticking the toggle in `View` called `Show grid`.

4. Use the pencil tool with the colour set to black and the size set to 1 to start making graphics.

5. Now you are able to draw any graphic you like. To allow for multiple graphics i used layers instead of creating many different files. When exporting I just selected the layers I wanted to see when exported. To add a layer go into `Layer > New Layer...`. In the menu make sure to set the layer to transparent. Now just make the relevant layers visible when you want to export the images.

6. You can import images into gimp to convert them to the bitmap type by dragging the image file into gimp. This can allow you to use images that have been created already which contain more detail but contain the overall shape you want to create in a graphic lcd form. I am not responsible for any copy write or trade mark infringement that may come from you doing this. Any images uploaded to this repo have been made by myself.

    - You may have to resize the image to fit on the display. To do this, select the layer the image is on and go into `layer > Scale layer...`. In the menu select the interpolation method of your choosing (I typically just use none but you can experiment with the different types) adn adjust the image pixel size that works for your use case.
    - Sometimes you may also have to reset the colour mode as importing images may add greyscale elements. The best way to handle this is to set the mode to greyscale or colour instead of indexed then index it again like in step 2. I have found that this normally fixes my issues.

7. Now that the images have been created. We are ready to export it to a C++ file we can load into the arduino nano esp32.

    - Activate the layers you want to export.
    - To export correctly go into `file > Export AS...`
    - In the menu that appears choose the file type of `X BitMap Image` with the file extension of xmb.
    - Make sure to uncheck the X10 format bitmap option if it is checked.
    - Make sure you remember what folder you export to.
    - The image is now exported correctly.

8. In the bitmap image file created in step 7 we can open the file in any text editor/ IDE. In it you will see some define terms at the top of your display size described with a charter array like declaration bellow it starting with `static unsigned char` etc. This is what needs to be copied into our script to be loaded.

9. In the script use the `u8g2.drawXBM(<int y position start>,<int x position start>,<int Display width in pixels>,<int Display height in pixels>,high30seg);` class function to display it to the screen.

Something extra you can do is to load all the images into a header file like I have with this script to decrease the clutter in the main script file. Just make sure you import the header file with the command `#import "<file name>.h"` the the start of the main script.

## What was learnt/ Liked

Through the use of this test script on the display the following conclusions on the different graphics have been made.

- Overall the display was readable in the dash and it would not be necessary to get a larger display for the dash. However, if you struggle to see I would recommend getting a larger dash like the [NHD-C12864DA-FSRGB-FBW-3V3](https://newhavendisplay.com/128x64-graphic-cog-lcd-fstn-wide-view-with-rgb-backlight-and-pins/) from [NewHaven Displays](https://newhavendisplay.com/) for readability reasons. It can be slightly difficult at times to read the display perfectly.
- If you are overlaying multiple bitmap images over each other, you must set the bitmap mode to 1 (transparent = true). This is done via the `.setBitmapMode(<1 for transparent, 0 for opaque>);` function of the display object more information can be found on the [u8g2 coding reference wiki page](https://github.com/olikraus/u8g2/wiki/u8g2reference#setbitmapmode).
- Making and loading bitmap images worked very well. Using them to make static non updating components like RPM, fuel and coolant graphics to then overlay data on top like speed is a good practice. I will use some of the graphics in my private library as a startup sequence graphic when the bike first turns on. I cannot upload them to github due to copyright unfortunately. I would recommend using this to help make static graphics.
- When testing the [Tom Thumb](https://robey.lag.net/2010/01/23/tiny-monospace-font.html) (u8g2_font_tom_thumb_4x6_mn) font, it was found to be too small and nearly unreadable even when resting on a desk. Therefore, reading it on a moving/vibrating motorcycle was going to be next to impossible. Although the font was very small it could still be used for things like odometer data when it needs to be squeezed onto the screen like the tachometer display as any other font was a bit too big. Ideally this font will not be used.
- An alternative to the tiny font that was much more readable while still being compact was the [u8g2_font_5x7_mr](https://github.com/olikraus/u8g2/wiki/fntgrpx11#5x7) font. This font will be the preferred one for any very small text and numbers like odometer and trip data.
- Through testing I found non bold fonts looked better for my use case in my opinion. The 30 high segment test shows this the best. I believe the non bold version of the font looks better in that test over the bold version of the font test. Therefore, non bold fonts will be used in the final dash.
- I think that the 30 pixel high digit segments worked ok but, by not utilizing the full height of the screen, it made it not work as well as the 32 pixel high  digit segment. I also really liked the appearance of the segment. Therefore, it will be used in the final solution in some way.
- I liked the [u8g2_font_t0_30_mr](https://github.com/olikraus/u8g2/wiki/fntgrpttyp0#t0_30) font for displaying the kph value so I will be using it in the final solution.
- I did not like the [u8g2_font_VCR_OSD_mr](https://github.com/olikraus/u8g2/wiki/fntgrpdafont#vcr_osd) font. It looked off to me for this use case. Therefore, it will not be used.
- The spacing of the kph lettering and Odometer data was perfect in the font based speed representation test for me. This spacing will be used to represent speed data on the final solution.
- In the font based speed representation test I liked the [u8g2_font_inr33_mn](https://github.com/olikraus/u8g2/wiki/fntgrpinconsolata#inr33) font to represent speed data. This font will be one of the solutions to display speed data in the final solution.
- For the RPM tests I liked the same RPM version (version a/1). The only disadvantage was the font size used for odometer data. This will be available in the final solution with a different odometer font being utilized. This version will be much simpler to code up as well compared to the ramping one as a bonus.
- Although Coolant and Fuel data is supposed to be represented by the lights on the dash, I liked the ramping coolant and fuel bars representation. The large gap in the middle was not ideal. The ramping fuel and coolant representation will be used in the final solution with some data being added between it to fill the large gap.

## Final decision on what will be used

For the final dash, there will be a number of display options available for use. This will display the different properties (Speed, RPM, Fuel, etc) on different screens. You will toggle between the screens using the buttons that are part of the dash. The final screen options that will appear in the final dash are as follows. The order is the order of which you can toggle through them. The last display option will be kept even after a power cycle so that you dod not need to toggle through all the options to get back to the one you wanted.

1) Settings panel - contains just text saying `Settings` centred on the screen. You will be able to select this page to enter the settings panel to adjust dash properties for calibration. This will use the [u8g2_font_5x7_mr](https://github.com/olikraus/u8g2/wiki/fntgrpx11#5x7) font to describe the settings available when you toggle through each page and the calibration instructions where appropriate. This font is used here as it will be used for other aspects of the dash. Reducing the amount of fonts used on the dash will reduce the storage requirement of the program allowing it to more likely fit onto the microcontroller.
2) Font based Speed Representation - This will be identical to the `font based speed representation` test. The speed numbers will be represented by the `u8g2_font_inr33_mn` font with the starting coordinates of X = 0 and Y = 32. The speed unit (kph or mph) will be represented by the `u8g2_font_t0_30_mr` font with the starting coordinates of X = 80 adn Y = 20. The trip/ odometer data will be represented by the `u8g2_font_5x7_mr` font with the starting coordinates X = 79 and Y = 32. There will be a toggle to cycle through the Odometer, Trip A and Trip B values using the dash buttons.
3) 32 High Segment based speed representation - This will use the 32 high segments in the `32 segment size test with trip and odometer` test. It will have a starting coordinate of X = 0 and Y = 32. The other data like speed unit (kph, mph) and trip/ odometer data will be identical to the setup in the font based speed version described in point 2 above.
4) Same RPM Representation - This will be nearly identical to the `RPM version a/1 test (Same)` version tested. It will use a bitmap to represent the RPM values at the top. The rpm bar will be represented/ generated using the [draw box](https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbox) display class method. The odometer and trip data will be represented using the `u8g2_font_5x7_mr` font with the starting coordinates X = 0 and Y = 32.
5) Fuel and coolant ramping representation - This will be nearly identical to the `Coolant and fuel version a/1 test (Ramping)` version. It will use a bitmap to represent the coolant and fuel logos and will use the [draw box](https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbox) display class method to represent each bar. The main additional aspect that was not included for the test will be the odometer and trip data all being displayed leftward between the coolant and fuel parts of the display but past the bar portions of both. The Odometer value will be at the bottom with trip B above it and trip A at the top all evenly spaced vertically using the `u8g2_font_5x7_mr` font.
T
Finally, separate to the main displays used in the dash. If there is enough storage on the microcontroller, I will add a startup graphics from my private library for fun. If there is not enough program storage I will not include the start up graphic.
