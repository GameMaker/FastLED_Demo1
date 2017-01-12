/*
   TITLE: FastLED demo
   AUTHOR: Aaron Cammarata
   EMAIL: aaron.cammarata@gmail.com
   DATE: JAN 10, 2017
   LICENSE: Free. Use it. Modify it. Enjoy it.

   This is a demo for new programmers who want to get started making light animations with the FastLED library.
   You'll need an Arduino, some lights, and all the associated power components and wires.
   Unfortunately, given the number of different types of lights, Arduino boards, and development tools, it's
   impossible for me to give instructions on setting up every possible configuration.
   It's geared towards younger learners, or parent/child teams working and learning Arduino together.

   If you're new to programming, I *STRONGLY* recommend you read through this once first, so that when you
   run it, you'll know what's happening and why.

   You'll need to set up your own IDE (software environment). If you're reading this, you probably already have. :)

   You'll also need to install the FastLED library. You can download it and get install instructions here:
   http://fastled.io/

   If you just want to get started, here's what we used:
   1) Arduino Uno R3 - https://www.adafruit.com/products/50
   2) String of lights - note, DO NOT get a "STRIP" of lights. They're different. Or, you can, but just know that a STRING of lights is
   not the same thing as a STRIP of lights. Make sure you get the one you want. We used these: https://smile.amazon.com/dp/B01AG923GI/
   3) A power supply for the lights. We used this one: https://smile.amazon.com/gp/product/B01M0KLECZ. Note that that's a 10 Amp power supply,
   which is more than you need for one of those strings. You can use a 3-Amp, 5V power supply with a positive center pin. If you don't know
   what that is, then you get to learn about power supplies!
   4) You'll need some M-M wires, like these, but if you get your Arduino as part of a kit, you should have a whole assortment.
   https://smile.amazon.com/Solderless-Flexible-Breadboard-Jumper-Wires/dp/B005TZJ0AM/
   5) Alas, you'll also need a breadboard. You really only need one row, which is a drag, or you can avoid it if you feel like
   tying three wires together. As long as we have it, we'll use it twice, actually.
   Nah. Just get the breadboard: https://www.adafruit.com/products/65 You'll want it. You probably already have one.

   The hardware setup is actually pretty easy. Again, these instructions are for the setup I described above. You might need
   to do something different if you buy different equipment. See the instructions with your power supply and lights.

   There are only six wires involved. 3 come from the led string, and 2 from the power supply. The supply above has an adapter with two
   terminals on it, marked + and -. (Note if you buy a different power supply, you might need to buy the adapter separately.)

   PREPARATION:
   a) Each end of the light string has two wires and a plug. One plug is male, the other is female. Find the end with the male plug.
   Push a white M-M breadboard wire into the white side of the plug. You actually leave the blue wire of the plug alone for this.
   This is WIRE #1.
   b) Still on the end of the string with the male plug, find the red wire next to the plug. You might need to strip the end to
   expose some of the metal. I use my teeth to pull off the plastic. Go on, get in there and bite off that plastic! Or, I suppose
   you could use a wire stripper. Seriously, it's easier to just bite it off. :) That's WIRE #2.
   c) On the other side of the plug is a dark blue wire, coming from the led string. WIRE #3. More wire strippers or teeth.

   MAKE SURE THE POWER SUPPLY IS NOT PLUGGED INTO THE ADAPTER BEFORE CONTINUING!

   d) Screw a new red breadboard wire into the "+" terminal of the adapter that came with the power supply. This is WIRE #4.
   e) Screw a new black wire into the "-" terminal of the power supply adapter. WIRE #5.
   f) Find one more black breadboard wire and hold it aside. That's WIRE 6.

   CONNECTION:
   1) Connect WIRE 1 into PWM pin 3 on the Arduino. Remember - they're numbered starting at 0, so it's the FOURTH pin from the end on an Uno.
   2) Connect WIRE 2 into any row on the breadboard. Call that ROW A. (If you've never used a breadboard,
   read this: https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard)
   3) Connect WIRE 3 into any OTHER row on the breadboard. Call that ROW B.
   4) Connect WIRE 4 into another spot on ROW A. You should now have two red wires in one row on the breadboard.
   5) Connect WIRE 5 into another spot on ROW B. You should now have one black and one dark blue wire in the same row on the breadboard as
   each other, but a DIFFERENT row than the red wires.
   6) Connect WIRE 6 into another spot on ROW B. It's now the third wire in that row, two black, one dark blue. Connect the other end of
   WIRE 6 to any Ground pin (marked GND) on the Arduino board.

   GO:
   Remember - read the program all the way through, then come back here and continue.

   I) Plug the power supply into the wall.
   II) Connect the power supply to the adapter. (Plug in the other end.) The lights might flicker or flash.
   They should not spark or ignite. :)
   III) Connect your Arduino, and run this program.
   IV) Have fun!!!
*/

/****************************************************************************
**                                                                         **
**                             HEADER                                      **
**                                                                         **
*****************************************************************************/
/* A HEADER is where you create any helpful things you need later, and
   tell the computer anything it needs to know about the program you want to write.
*/

/* First, we need to tell the computer that we're going to use the
   "FastLED" library to control the lights. Libraries are code that let you
   get things done without writing as much code.
*/
#include <FastLED.h>

/* It's also useful in the header to create "Constants" - that is, a new name that
   means something to our program, that we'll use over and over, and we might want
   to be able to change quickly - but make sure it changes everywhere that it's
   used.
   For example, in this demo, we're going to set the lights to different patterns,
   and then we want it to wait in between each step so we can see it.
   To do that, we'll define a new number called WAIT_TIME, and set it to 3000.
   Since all waiting by the computer is done in milliseconds, this is 3 seconds.
*/
#define WAIT_TIME 3000

/* Now we tell the Arduino which pin we're using to plug in the white wire
   to the lights. Remember we did this in step 1 of the CONNECTION setup.
   IMPORTANT - if you plug the white wire into a different pin,
   you need to change this number to match the pin you use.
*/
#define DATA_PIN 3

/* This is the number that tells FastLED how many lights we have.
   In my example, we have a string of 50 lights.
*/
#define NUM_LEDS 50

/* This variable is an ARRAY of "CRGB" values. CRGB is a Color (C) made of
   Red (R), Green (G), and Blue (B) values. Each light in the string has
   its own color, so we need one CRGB color item for each of the lights
   in the string. Notice that we use the "NUM_LEDS" from above, which makes
   it nice and handy - if we get more lights, we just change the number
   above, and the entire program will just work - if we write it correctly!
   This is called a 'declaration'. We're declaring (saying) that we need
   a CRGB object (the first part of the line),
   that we want to call that new object "leds" (the middle part of the line),
   and that we want a whole bunch of them in an Array (the "[NUM_LEDS]" part).
   So when this is done, we have a whole bunch of CRGB objects, like houses
   on a street. Each one has its own address, and we'll get into the details
   later, but for now, just think of this as a long line of 50 objects
   that we can set to whatever color we want.
*/
CRGB leds[NUM_LEDS];

/****************************************************************************
**                                                                         **
**                               MAIN                                      **
**                                                                         **
*****************************************************************************/
/* An Arduino program has two 'required' functions, and they have special names.
   The setup function runs once when you press reset or power on the board.
   This is where you do all the one-time 'initialization' tasks to prepare
   for the rest of the program to run. Usually it's things like setting counters
   to 0, initializing memory for things you'll need, etc.
*/
void setup() {
	/* The first thing we need to do is tell the FastLED library all about the
	   lights attached to the Arduino. We have lights that use the "WS2811"
	   standard, and they're connected by a wire plugged in to the
	   DATA_PIN (remember, number 3). We've created an Array of CRGB
	   objects above, and we called it "leds". Finally, we need to tell it
	   how many lights there are - but instead of just putting "50", we use
	   the name we defined above. This a) makes it easier to read, and b) lets us
	   change NUM_LEDS up above, and it will change here as well when we re-run
	   the program. That way if we add another string, we change the 50 to 100
	   above, and it all just works!
	*/
	FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

/* The loop function is the second 'special', required function.
   It runs until you turn off the Arduino or reset it.
   It runs through everything you put in here, and then goes back to the top of the loop
   and does it all again.
   It's capable of running very, very fast, so if you put anything in here it can get
   run many thousands of times per second.
*/
void loop() {

	/* Now let's do some fun things with the lights!
	   First, let's see how to light up just one light.
	   In general, to make the lights do what we want, we do three things:
	   1) Update the "leds" array, and tell it what color we want each light to be.
	   2) Tell FastLED to "show" the colors we asked for.
	   3) Wait a little bit. This is called a "delay". If we don't do this, it will flash on
	   and off so quickly we don't even see it! This is why we created "WAIT_TIME" above.

	   One more note - in step 1, when we tell it what color we want each light to be, we only have to tell it
	   which lights we want to CHANGE. If we don't tell FastLED what color to make
	   a light, it will stay whatever color it was set to last.

	   At the beginning, when we called "FastLED.addLeds" in the setup, it already set all the
	   lights to "Black" - which is, 'off'.

	   So to get started, let's turn the first light green to get going!

	   First, we tell it which light we want to change, and what color to use. Remember, we use the "leds" array to
	   tell it what color we want. An "Array" is like a list of objects, with a number. Like houses on a street,
	   you can get to the object you want by using the 'index' (like an address) of that object.

	   In an array, the first object is number 0, then number 1, 2, etc. Note that because the counting starts at
	   0, the number of houses on the street is ONE MORE THAN THE BIGGEST INDEX.

	   For example, if we have an array with 3 objects, they would have index 0, 1, and 2. If you tried to go to
	   object number 3 in the list, your program would crash! There are 3 things in the list, but no house with address
	   number 3! Only houses 0, 1, and 2.

	   So the first light in the list is called "leds[0]". That tells it, "look on the streed called 'leds', and find
	   the house with address '0'."

	   Then we need to tell it what color we want.

	   To do that, we'll use a new function called "CRGB". You might remember we used those letters above to define the leds
	   array. In that case, it told the computer that we want a bunch of things in memory that are places that we
	   can store "CRGB" information.

	   Now, we're going to create a new CRGB object, and store it in the first object of leds.

	   To create a new CRGB object, you use "CRGB(<red>, <green>, <blue>)".
	   Where "<red>", "<green>", and "<blue>" are the amount of that color that you want to use in the final color.
	   Each of those is a number from 0 (darkest) to 255 (brightest).
	   Since we want to do no red (0), all green (255), and no blue (0) for the color we want, the final code looks like this:
	*/
	leds[0] = CRGB(0, 255, 0);

	/* And that's it! We just told the computer that we want the first light to be all green, no red, and no blue.
	   But if that's all you typed, nothing would happen on the lights.
	   Now you need to tell it to SHOW the colors you've set. That's easy: */
	FastLED.show();

	/* If you could speed up and see what's happening at computer speed, THIS is when the first light would light up
	   green. Now that it's done "show"ing us the colors we asked for, the computer would happily keep going along
	   without waiting. Since we want to be able to see our green color before it disappears, we use a 'delay'
	   to tell the computer to slow down here and wait a bit.
	   Delay is a function that takes one number: the number of milliseconds you want it to wait.
	   Remember that we already created a new constant to use every time we want it to wait - this is where we use it.
	*/
	FastLED.delay(WAIT_TIME);

	/* Let's explore color a little bit more.
	   Let's turn the fifth light (remember - the fifth one is NUMBER 4) a different color. Here's the code - try
	   and guess what it does:
	*/
	leds[4] = CRGB(255, 255, 0);
	FastLED.show();
	FastLED.delay(WAIT_TIME);
	/* It creates a new color, with full-power red, full-power green, and no blue. What color do you think that makes?
	   Well, if you're used to mixing paints, red and green makes grey-brown-blah.
	   But when you're working with light, the colors mix differently! Red and green LIGHT make YELLOW light.
	   To learn more, Google 'Additive Color': https://en.wikipedia.org/wiki/Additive_color
	*/

	/* But wait - the green light is still on! Now we have a green AND a yellow light.
	   That's right! Remember, if you don't change the 'leds' value before you call 'show', the light stays the same
	   as whatever you told it to do before.

	   To see this in action, let's turn on the 10th light a new color (try and guess it!), but let's ALSO turn off the other two.
	   You 'turn off' a light by setting it to the color black.
	*/
	leds[0] = CRGB(0, 0, 0);
	leds[4] = CRGB(0, 0, 0);
	leds[9] = CRGB(128, 0, 128);
	/* That's half-red, no green, half-blue, so it's purple...but not quite as bright! */
	FastLED.show();
	FastLED.delay(WAIT_TIME);


	/* Did you notice that in the last one, for leds[9], we used a different number? We used 128 for red and blue.
	   That's how you can control the color. It'll take some time, but let's do an experiment. Let's try different numbers
	   for each light and see how the colors change. We'll have the colors go up and down in little increments, one on
	   each light, and then we can see the colors they make.*/
	leds[0] = CRGB(64, 0, 0);
	leds[1] = CRGB(128, 0, 0);
	leds[2] = CRGB(192, 0, 0);
	leds[3] = CRGB(255, 0, 0);
	leds[4] = CRGB(192, 64, 0);
	leds[5] = CRGB(128, 128, 0);
	leds[6] = CRGB(64, 192, 0);
	leds[7] = CRGB(0, 255, 0);
	leds[8] = CRGB(0, 192, 64);
	leds[9] = CRGB(0, 128, 128);
	leds[10] = CRGB(0, 64, 192);
	leds[11] = CRGB(0, 0, 255);
	leds[12] = CRGB(64, 0, 192);
	leds[13] = CRGB(128, 0, 128);
	leds[14] = CRGB(192, 0, 64);

	FastLED.show();
	FastLED.delay(WAIT_TIME);

	/* Neat! So if we mix colors, we can get the whole rainbow, bright colors and dim.
	   Before we continue, though, we need to turn all those lights off, otherwise they'll interfere
	   with whatever design we do next.
	   We could do a bunch of "leds[0] = CRGB(0,0,0);", like we did before, one for each led, but that's
	   big, and wasteful, and a lot of typing.
	   Instead, what if we could change a whole bunch of lights at once?
	   Well, we can! We can use a new function to fill a string of lights with a color, all in one shot.
	   First, we tell it which leds to fill in (the "leds" array), then the number of lights to set,
	   then the color to set them to. It looks like this:
	*/

	fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
	FastLED.show();
	FastLED.delay(WAIT_TIME);

	/* That turns the WHOLE string, from start to finish, to black. But what if we wanted to quickly turn a
	   bunch of lights on in a row, but not the whole thing? Like, turn on lights number 10 through 30 to
	   white?
	   That looks like this. First we tell it where to start (leds[10]), and instead of telling it to
	   turn them ALL on (NUM_LEDS), we tell it to only change 20 lights (30 minus 10 is 20).
	   Notice that the syntax (the format) of this is a little different. Instead of "leds", we have to
	   use an ampersand (&) and tell it which light to start with (10), like this:
	*/

	fill_solid(&leds[10], 20, CRGB(255, 255, 255));
	FastLED.show();
	FastLED.delay(WAIT_TIME);

	/* Did you notice that we're doing a lot of the same stuff, over and over? Every time we want the lights to update,
	   we tell it to show(), then delay(), and from now on, we should probably get in the habit of clearing the lights
	   to set it up for the next pattern.
	   Instead of having to type it over and over, let's make a new function, called "updateLights", which does all that for us.
	   If you look later on in the file, you can find "updateLights" at the end of this file
	   under the "UTILITIES" section, but for now, we'll use it here.
	   All it does is:
	   1) show
	   2) delay the amount of time we tell it
	   3) clear the string for the next pattern
	*/

	updateLights(WAIT_TIME);

	/* Now let's learn a faster way to set the light colors. So far, we've had to set every color by hand, telling it exactly
	   how much red, gren, and blue light to use.
	   It turns out there are a lot of colors already set up, that we can use to make it easier to both write our code,
	   and to understand what it's doing.
	   The way you use these pre-made colors is like this:
	   CRGB::<colorname>
	   where <colorname> is one of the colors that are already set up.
	   To see the full list, you can Google "X11 Color Names", or look here: https://en.wikipedia.org/wiki/X11_color_names
	   To show an example, we'll set the first two lights to red, but first we'll do it manually, and the second light
	   we'll do with the pre-made color.
	*/
	// First, the old-fashioned, manual way.
	leds[0] = CRGB(255, 0, 0);
	// Now, the fancy new, easy to read way. Isn't this much clearer?
	leds[1] = CRGB::Red;
	// Now let's see some more colors:
	leds[2] = CRGB::Blue;
	leds[3] = CRGB::PaleGoldenrod;
	leds[4] = CRGB::DarkGreen;
	leds[5] = CRGB::Purple;
	updateLights(WAIT_TIME);

	/* That doesn't mean you'll never use CRGB(r, g, b). If you want to use a color that's not on the color chart, you have to
	   go back to the old fashioned way.
	   But there are tricks to that, too. Instead of writing out one line of code per light, you can use something called a
	   "for loop".
	   A loop is a small piece of code that runs over and over, doing pretty much the same thing, until it hits a stop point
	   that you tell it.
	   This for loop creates a new variable called 'i' (short for 'index'). i is a counter that starts at 0, and counts up
	   to NUM_LEDS. Each time we go through the loop, i gets one bigger.
	   The way you define a for loop is:
	   for (<setup> ; <thing to check> ; <thing to do every time through>) {
		  <body>
	   }
	   <setup> is what you want it to do before starting the loop. In our case, we're going to create 'i', as an 'integer',
	   and set it to 0.
	   <thing to check> is how we tell the loop when it's done. The loop will keep going as long as whatever we put in there
	   remains true. Here, we say "keep going as long as i is less than NUM_LEDS". Advanced users: note that we say 'less than',
	   not 'less than or equal'. Why do you think that is?
	   <thing to do every time through> is what we want the code to do every time it hits the bottom of the loop. Here, we say
	   "i++", which is just a fancy computer-ese way to say "add one to i".
	   <body> goes between curly braces, and is what the loop does every time, from top to bottom.
	   So here, we say "start a new counter. Call it 'i'. Start it at 0, and do this loop while i is less than NUM_LEDS.
	   Inside the loop, turn on light number 'i', and then update the lights.
	   Every time you get to the bottom, make i one bigger, then check and see if i is still less than NUM_LEDS. If so,
	   do it again."
	*/

	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::DarkViolet;
		// note that since we're going through the whole string, let's go 25 times as fast - which means we want to
		// wait for 1/25 as much time. Notice that we still use WAIT_TIME, though - that way, if we want to make the whole
		// program faster or slower, we can just go up to the top and change the number for WAIT_TIME and re-run it.
		// Feel free to give it a try!

		updateLights(WAIT_TIME / 25);
		// Also note that since we 'clear' the string in updateLights, we see only one light 'walking' along the string.
		// If we didn't clear the string, we would see the first light light up, then the second light - while the first
		// was still lit.
	}

	/* You can use for loops to do all kinds of things. Like here's one that uses the loop variable to change the colors
	   along the string. See if you can sort out how it works! There's a hint in the code - see how writing clean code helps
	   you understand and work with it?
	*/

	for (int brightness = 0; brightness < NUM_LEDS; brightness++) {
		leds[brightness] = CRGB(brightness, brightness, brightness);
	}

	// Notice that this time, the update is OUTSIDE the loop. So it's going to do the whole loop, finish, and THEN turn on the lights.
	// What happens? How is that different than the last time?
	updateLights(WAIT_TIME);

	/* Now for a really strange math tool that comes in quite handy.
	   What if you wanted to go through the whole string, but turn the first light red, the second light green,
	   the third light blue, and then repeat (fourth light red, etc.)?
	   That's where you'd use a new piece of math called "modulo".
	   Modulo, or "mod" lets you divide two numbers and get the remainder.
	   You write it like this:
	   <n1> % <n2>
	   n1 is the first number, and n2 is the second number, and "%" is the symbol that tells the computer to do a
	   modulo operation, just like "+" tells it to add.
	   It's very useful in a loop to take a number that counts up from 0 until the end of the loop, and instead create
	   a new number that cycles like 0, 1, 2, 3, 0, 1, 2, 3, 0, 1...etc.
	   Here's an example where we go through all the lights, and set the lights to a repeating sequence of three colors.
	*/
	for (int i = 0; i < NUM_LEDS; i++) {
		// Note that when you're checking something in an "if" statement, you use two equals signs next to each other!!!
		if (i % 3 == 0) {
			// i is a multiple of three - no remainder
			leds[i] = CRGB::Red;
		}
		else if (i % 3 == 1) {
			// i is one more than a multiple of three, such as '4'. The remainder is 1.
			leds[i] = CRGB::Green;
		}
		else if (i % 3 == 2) {
			// i is one LESS than a multiple of three, like '2' or '5'. The remainder is 2.
			leds[i] = CRGB::Blue;
		}
	}

	updateLights(WAIT_TIME);

	/* If you take any number and divide it by 3, the remainder will ONLY be 0, 1, or 2, so our loop above will
	   give every light a color, repeating through red, green, and blue.
	   It turns out there's a shorter, faster way to do this. It's not much shorter in this example, but it's useful to
	   see once anyway. It's called a 'switch' statement. You give it a variable to use as a switch, and then
	   go into one of the different 'case's that it can match, like this.
	   I'll use different colors so you can see that it's basically the same code, and has the same result (setting the whole light
	   string, in repeating pattern of three), just written differently.
	*/

	for (int i = 0; i < NUM_LEDS; i++) {
		switch (i % 3) {
		case 0:
			leds[i] = CRGB::Yellow;
			// "break" tells it "ok, you're done with what you should do with the '0' case. Skip to the curly brace at the end."
			break;
		case 1:
			leds[i] = CRGB::Cyan;
			break;
		case 2:
			leds[i] = CRGB::Violet;
			break;
		}
	}

	updateLights(WAIT_TIME);

	/* Another neat thing you can do is put one loop inside another.
	   Here we have an 'inside' loop that goes from the start of the string to the end, and sets the color of each light.
	   The 'outside' loop tells it to update a bunch of times, and changes another variable (j) each time.
	   See if you can work out what this does. It uses only stuff we've learned, but is a little tricky.
	   Note that it uses a new variable called "brightness", which we'll need inside the loop.
	*/
	int brightness;
	for (int j = 0; j < NUM_LEDS * 3; j++) {
		for (int i = 0; i < NUM_LEDS; i++) {
			brightness = ((i + j) * 5) % 255;
			leds[i] = CRGB(brightness, brightness, brightness);
		}
		updateLights(WAIT_TIME / 50);
	}

	/* One last thing, and then you're on your own!
	   Notice that our "loop" has gotten pretty darned big! If we wanted to change anything, we'd have to hunt through to find it.
	   Instead, a nice way to clean up and keep your code more manageable is to make your own 'functions' that do things you want,
	   and you can use them over and over.
	   Here's a for loop, but all it does is repeat some other functions 10 times.
	   If you look below under "USER FUNCTIONS", you'll find the actual code for them. This lets us write code we can use a whole
	   bunch, just like we did with updateLights().

	   Enjoy!
	*/

	for (int finale = 0; finale < 3; finale++) {
		doPingPong(finale + 1); // Why + 1, do you think?
		doMeter();
	}

}

/****************************************************************************
**                                                                         **
**                           USER FUNCTIONS                                **
**                                                                         **
*****************************************************************************/
/* These are usually larger functions, or blocks of code, that do something useful
   that is specific to the program. As a demonstration, we'll do two. One that does
   a ping-pong, and one that does an inside-out meter effect like a stereo sound meter.
*/

void doPingPong(int numberOfBounces) {
	// One way to make your code faster is to create all the variables you'll need at the top, and then
	// you can just use them inside the function.
	int i;
	int j;
	for (i = 0; i < numberOfBounces; i++) {
		for (j = 0; j < NUM_LEDS; j++) {
			leds[j] = CRGB::Blue;
			updateLights(WAIT_TIME / 50);
		}
		// If you have a speaker, this might be a good time to play a sound. :)
		// "j--" is just another way to say "subtract one from j".
		for (j = NUM_LEDS - 1; j >= 0; j--) {
			leds[j] = CRGB::Blue;
			updateLights(WAIT_TIME / 50);
		}
		// Another sound here might work, too...
	}
}

/* Creates an effect like a sound meter.
   This one uses a little bit of fancier math, which you can read about online.
*/
void doMeter() {
	// You can declare more than one number at a time, like this.
	int i, j, strength, middle, base;
	middle = NUM_LEDS / 2;
	base = NUM_LEDS / 6;
	fill_solid(&leds[middle - base], base * 2, CRGB::Green);
	for (i = 0; i < 15; i++) {
		strength = random(base, (middle - 1) - base);
		for (j = base; j < base + strength; j++) {
			if (j > middle* 0.8) {
				// top of the range - use red!
				leds[middle + j] = CRGB::Red;
				leds[middle - j] = CRGB::Red;
			}
			else if (j > middle * 0.6) {
				leds[middle + j] = CRGB::Yellow;
				leds[middle - j] = CRGB::Yellow;
			}
			else {
				leds[middle + j] = CRGB::Green;
				leds[middle - j] = CRGB::Green;
			}
			// Note that we don't use updateLights, because we want to turn the lights on/off one at a time
			// but NOT have them turn off between updates. updateLights clears the string, remember?
			// So we have to go back to doing it the old way, by hand each time.
			FastLED.show();
			FastLED.delay(WAIT_TIME / 200);
		}
		for (j = base + strength - 1; j >= base; j--) {
			leds[middle + j] = CRGB::Black;
			leds[middle - j] = CRGB::Black;
			FastLED.show();
			FastLED.delay(WAIT_TIME / 200);
		}
	}
	// Though we didn't clear between each frame of our animation, we need to clean up after ourselves for the next effect!
	fill_solid(leds, NUM_LEDS, CRGB::Black);
}

/****************************************************************************
**                                                                         **
**                             UTILITIES                                   **
**                                                                         **
*****************************************************************************/
/* These are useful bits of code that we'll use over and over, both in the
   main loop and in our custom user functions. They're usually pretty small,
   and do just one very specific thing.
*/

/* updateLights(int delayTime)
   Updates the string of lights based on the 'leds' array, then waits for the specified amount of time before clearing the string
   (i.e. turning off all the lights)
*/
void updateLights(int delayTime) {
	FastLED.show();
	FastLED.delay(delayTime);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
}