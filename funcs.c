#include <stdio.h>
#include "funcs.h"
#include <math.h> // define math function to be used throughout the code.
#define PI 3.14159265358979323846 // define Pi to be used throughout the menu.

// variables have been defined (global variables). It has been placed here to be used in other menus.
double Resistor = 0;
double Capacitor = 0;
double cut_off_frequency;
char circuit_buffer[64];
char ciruit_detail[64];
char help_and_theory[64];
int high_pass_filter = 0;
int low_pass_filter = 0;

// This is the start of the main script
// MENU ONE SELECT CIRCUIT TYPE.
// code for selecting circuit type
void Select_circuit_type(void) {
printf("\n>> Select circuit type\n");
printf("Enter 1 for High-pass filter\n");
printf("Enter 2 for Low-pass filter\n");
printf("Choice: ");
int choice;

// use switch statment to allow the user to pick frim high pass or low pass filter.
// using a while loop to check if certain conditions are true and if the conditions are not true then the code will not execute and an error 
// message will appear such as invalid option please enter the correct integer.
while (1) {
fgets(circuit_buffer, sizeof(circuit_buffer), stdin);
// If the choice is 1 or 2, input is valid then break the code. sscanf is used as scanf only takes in integers and sscanf can take decimal values
// and fgets is used to turn the string into an integer even if the value is 1.56 it will only identify the first integar.

if (sscanf(circuit_buffer, "%d", &choice) == 1 && (choice == 1 || choice == 2)) {
break;
}

// if the input is invalid it then returns to here and gives an error message
printf("Invalid option, please enter the correct integer\n");
}

// using switch statement to allow the user to pick between two options(High pass or low pass filter).
switch (choice) {
case 1:
high_pass_filter = 1;
low_pass_filter = 0;
printf("High pass filter is selected\n");
break;

case 2:
high_pass_filter = 0;
low_pass_filter = 1;
printf("Low pass filter is selected\n");
break;
}
    
while(1){
// Resistor input code
printf("\nEnter resistor value (ohms): ");
scanf("%lf", &Resistor);

// Capacitor input code 
double Capacitor_nf;
printf("Enter capacitor value (Nano fards): ");
scanf("%lf", &Capacitor_nf);

//convert capacitor values from nanofards to farads
Capacitor= Capacitor_nf*1e-9;

// Validation code for input on both capacitor and resistor.
if (Resistor >0 && Capacitor >0) {
break;
}
// print error if the top condition is not met.
printf("ERROR: Resistor and capacitor must be greater than zero.\n");

}
// calculation of cut off frequency.
cut_off_frequency = 1.0 / (2.0 * PI * Resistor * Capacitor);
printf("Cutoff frequency = %.5f Hz\n", cut_off_frequency);

//to write information to text file
FILE *fw = fopen("circuit_details.txt", "w");
fprintf(fw, "Resistor (Ohms): %lf\n" "Capacitor (Farads): %.9lf\n" "Cutoff_frequency (HZ): %lf\n" "High pass%d\n" "low pass%d\n", Resistor, Capacitor, cut_off_frequency,
        high_pass_filter, low_pass_filter);
fclose(fw);

//notify the user that the circuit has been saved
printf("\nCircuit saved successfully!\n");

}


//MENU 2 VIEW CIRCUIT DETAILS.
// make code to save data in a text or file and then viewing circuit detail it will open that file and show the user input. 
void View_circuit_details(void) {
printf("\n>>View circuit details\n");

FILE *fr = fopen("circuit_details.txt", "r"); // open the text file.
if (fr == NULL) { // if no values have been found in the text file then print no circuit has been found.
printf("No saved circuit found. Please use menu option 1 first.\n");
return;
}
char file[64]; // buffer for this specific menu to read and write files from the first menu.
while (fgets(file, sizeof(file), fr) != NULL) {
}
printf("Resistor value: %.0lf Ohms\n",Resistor);
printf("Capacitor value:  %.9lf Farads\n",Capacitor);             //print the variables that were entered from the first menu into the second menu.
printf("Cut off frequency value: %.6lf HZ\n",cut_off_frequency);

if(high_pass_filter==1 && low_pass_filter==0){
 printf("high pass filter\n");
}
else if (low_pass_filter==1 && high_pass_filter==0){     // this code uses and if statement to them print on the second menu on what filter has been selected from the first menu
  printf("low pass filter");                             // this has been done because there is no variable for the selection of the filter the user would just have to enter in values to select it
}                                                        // from this whatever the user has entered 1 for high pass filter or 2 for low pass filter the selection of filter will be printed into this page.
else{
printf("filter type unknown\n");                         // if no filter has been found a message would appear such as "filter type unknown".
}
  fclose(fr);
}  



//MENU 3 FREQUENCY ANALYSER
void Select_frequency_analyser(void) {
    printf("\n>>frequency analyser\n");
    printf("\nPlease enter details\n");
    // load circuit information.
    FILE *fr = fopen("circuit_details.txt", "r");
    if (fr == NULL) {  // if the file contains nothing then print no circuit is found.
    printf("No saved circuit found. Please use menu option 1 first.\n");
    return;
}   
    fscanf(fr, "%lf %lf %lf %d %d", &Resistor, &Capacitor, &cut_off_frequency, // read the variables from the text file so the menu knows the values that have been chosen in the selection of the circuit.
    &high_pass_filter, &low_pass_filter);
    fclose(fr);

// Input buffer has been placed to use functions such as fgets for temporary storage. There is only one buffer that will be used for this menu.
char input_buffer[64];
//selecting the options for calculations.
int calc_magnitude_response_singlef=0, calc_rangeof_f=0, calc_phase_response_singlef=0;
int choice_for_frequency;

// selecting which option to pick
while(1){// to ensure the correct option has been selected
printf("Select calculation type:\n"
       "1. Magnitude response at a single frequency\n"
       "2. Phase response at a single frequency\n"
       "3. Range of frequencies (magnitude + phase)\n"
       "Enter your choice: ");
    fgets(input_buffer,sizeof(input_buffer),stdin);
    sscanf(input_buffer,"%d",&choice_for_frequency);

    if(choice_for_frequency==1||choice_for_frequency==2||choice_for_frequency==3)
{
  break; 
}
else{
printf("please enter correct value either option 1,2 or 3\n");
}
}


switch (choice_for_frequency){
case 1:
  calc_magnitude_response_singlef=1;
  calc_phase_response_singlef=0;
  calc_rangeof_f=0;
  printf("calculation of magnitude response for a single frequency selected\n");
  break; 

case 2:
  calc_magnitude_response_singlef=0;
  calc_phase_response_singlef=1;
  calc_rangeof_f=0;
  printf("calcultion of phase response at a single frequency selected\n");
  break; 

case 3:
  calc_magnitude_response_singlef=0;
  calc_phase_response_singlef=0;
  calc_rangeof_f=1;
  printf("calculation of range of frequencies including phase and magnitude selected\n");
  break;
}

// calculation for magnitude response at a single frequency.
// since the formulas are different for each filter selected 
// low pass filter will have its own formula and high pass
// will have its seperate formula.

double Minumum_Frequency,Maximum_Frequency,Frequency,Step_size_forF;

// Ask for frequency for only the first and second menu option as the third option will ask for min and max range of frequncies.
if(calc_phase_response_singlef==1||calc_magnitude_response_singlef==1){
while(1){
    printf("enter frequency in HZ: ");
   fgets(input_buffer,sizeof(input_buffer),stdin);
  sscanf(input_buffer,"%lf",&Frequency);
 if(Frequency>0){
break;
}
else {
printf("please enter greater value then zero\n");
}
}
}

// calculate the angular frequency W=2*PI*F
double W=2*PI*Frequency;

// selecting the first option calculation
if (calc_magnitude_response_singlef==1&&low_pass_filter==1){
double magnitude_for_lowpassfilter=1.0/sqrt(1+pow(W*Resistor*Capacitor,2));
// convert to db scale using the formula 20log(linear scale value)
double DB= 20*log10(magnitude_for_lowpassfilter);
printf("DB value:%.2lf\n",DB);
printf("Magnitude: %.4lf\n",magnitude_for_lowpassfilter);
printf("Frequency selected:%.4lf\n", Frequency);
}
if(calc_magnitude_response_singlef==1&&high_pass_filter==1){
double magnitude_for_highpassfilter=W*Resistor*Capacitor/sqrt(1+pow(W*Resistor*Capacitor,2)); // formua for magnitude for high pass filter.
double DB= 20*log10(magnitude_for_highpassfilter); // convert to db scale using the formula 20log(linear scale value).
printf("DB value:%.2lf\n",DB); 
printf("Magnitude: %.10lf\n",magnitude_for_highpassfilter); // format the varaibles into a specific decimal value and print them.
printf("Frequency selected:%.4lf\n", Frequency);
}

//selecting the second option calculation.
if(calc_phase_response_singlef==1&&high_pass_filter==1){// checks if the second option has been selected and the high pass filter has been selected.
double phase_radians=atan(1/(W*Resistor*Capacitor));// formula for phase in radians.
double phase_degrees=phase_radians*(180/PI);// formula for phase in degrees conversion.
printf("phase calculate in radians:,%.4lf\n",phase_radians); // format the varaibles into a specific decimal value and print them
printf("phase calculated in degrees:%.4lf\n",phase_degrees);
}
if(calc_phase_response_singlef==1&&low_pass_filter==1){// checks if the second option has been selected and the low pass filter has been selected.
double phase_radians=-atan(1/(W*Resistor*Capacitor));// formula for phase in radians.
double phase_degrees=phase_radians*(180/PI);// formula for phase in degrees conversion.
printf("phase calculate in radians:%.4lf\n",phase_radians); // format the varaibles into a specific decimal value and print them
printf("phase calculated in degrees:%.4lf\n",phase_degrees);
}

//selecting the third option calculation.
// enter min and max range of frequency.
if(calc_rangeof_f==1){
while(1){
printf("Enter minimum, maximum frequency in HZ and enter step size in HZ space each value: ");
fgets(input_buffer,sizeof(input_buffer),stdin);
sscanf(input_buffer,"%lf %lf %lf",&Minumum_Frequency,&Maximum_Frequency,&Step_size_forF);
if(Minumum_Frequency>0&&Maximum_Frequency>0&&Step_size_forF>0){
break;
}
else{
printf("please enter the correct values for each that must be greater than zero\n");
}
}
}
// the ASCII table to print the results out in for low pass configuration.

if(calc_rangeof_f==1&&low_pass_filter==1){
printf("\n------------------------------------------------------------------\n");
printf("|         Freqeuncy    |     Magnitude    |   DB    |phase(degrees)|\n");  // print a table out to show the user the different values that have been calculated in the frequncy simulation.
printf("--------------------------------------------------------------------\n");
for(double f=Minumum_Frequency;f<=Maximum_Frequency;f=f+Step_size_forF){ // for loop to step through the range of desired frequency which has been selected from minimum value to maximum value with a step rate that has also been selected.
//calculations
double W=2*PI*f;
double magnitude= 1.0/sqrt(1+pow(W*Resistor*Capacitor,2)); // formula for magnitude for a low pass filter.
double phase_radians= -atan(1/(W*Resistor*Capacitor));// formula for phase in radians.
double phase_degrees= phase_radians*(180/PI);// formula for phase in degrees conversion.
double DB= 20*log10(magnitude);// calulation to DB from linear scale.
printf("%12.2lf |%12.2lf |%10.2lf |%17.2lf\n", f, magnitude , DB, phase_degrees ); // format the varaibles into a specific decimal value and print them.
}
}

// the ASCII table to print the results out in for high pass filter configuration.
if(calc_rangeof_f==1&&high_pass_filter==1){
printf("\n------------------------------------------------------------------\n");
printf("|         Freqeuncy    |     Magnitude    |   DB    |phase(degrees)|\n");
printf("--------------------------------------------------------------------\n");
// for loop to allow information from the minimum to maximum frequecy selected depending on the frequency step size chosen.
for(double f=Minumum_Frequency;f<=Maximum_Frequency;f=f+Step_size_forF){
//calculations.
double W=2*PI*f;
double magnitude= (W*Resistor*Capacitor)/sqrt(1+pow(W*Resistor*Capacitor,2)); // formula for magnitude for a high pass filter.
double phase_radians= atan(1/(W*Resistor*Capacitor));// formula for phase in radians.
double phase_degrees= phase_radians*(180/PI);// formula for phase in degrees conversion.
double DB= 20*log10(magnitude); // calulation to DB from linear scale.
printf("%18.2lf |%16.4lf |%10.2lf |%16.2lf|\n", f, magnitude , DB, phase_degrees); // format the varaibles into a specific decimal value and print them.

}
}
printf("Freqeuncy-domain simulation complete"); // message to notify the user the simulation has been completed.
}




// MENU 4 TIME ANALYSER
void Select_time_analyser(void) {
printf("\n>>Time domain analyser\n");
printf("\nCircuit that has been selected\n");
   
// print previous circuit data.
FILE *fr = fopen("circuit_details.txt", "r"); // file to open the saved circuit information.
if (fr == NULL) { // if the file does not contain any information then the user would have to go back to the first menu to enter in circuit details.
printf("No saved circuit found. Please use menu option 1 first.\n");
return;
}// read all the values that have been entered from menu 1
fscanf(fr,"%lf %lf %lf %d %d", &Resistor, &Capacitor, &cut_off_frequency,
&high_pass_filter, &low_pass_filter);
fclose(fr); // close the file. file read close


// define variables the full time range, the time step, voltage in and frequency and choice of wave. 
double Time, Step_time, Vin, freq;
int choice_of_wave; 

// This is to enter the variables such as Time, the incremented time(Step_time), the input voltage, and the selection of wave type.
printf("enter simulation time in seconds: \n");
scanf("%lf", &Time);

printf("enter step time: \n");// enter the step time for an example if the user selects a total T of 10 seconds 
scanf("%lf", &Step_time);     // and wants a simulation to check for a step time of one second then it will count from 1 to 10
                              // and increment every one second.
printf("enter input voltage\n"); // enter voltage in
scanf("%lf", &Vin);

printf("step or sin waveform\n"); // select the wave type
printf("1. step input\n"
       "2. sine wave\n");
printf("Choice: ");
scanf("%d", &choice_of_wave);
 
if(choice_of_wave == 2) {
printf("Enter sine frequency (Hz): "); // since step wave does not contain frequency
scanf("%lf", &freq);                   // if the user selects sin wave then the user would 
}                                      // have to enter a frequency varaible.
while(1){
if (Resistor > 0 && Capacitor > 0) {  // Using a while loop to error check if the resistor or capacitor is greater than zero
break;
} else{
printf("ERROR: R or C cannot be zero!\n");
}    
}
// define the RC time constant to be used for stable discharge and charge values.
double RC_time_constant= Resistor*Capacitor; // formula for calculating the RC time constant, variables from the saved circuit files would be loaded into this menu and read and be used for further calculations and analysis.  
double decay_factor= exp(-Step_time/RC_time_constant); // formula for calculating the decay factor, variables from the saved circuit files would be loaded into this menu and read and be used for further calculations and analysis.  


// where the simulation gets conducted.
printf("\nTime\tVin\tVout\n");

// capacitor voltage parameters.
double t=0;
double vin=0;
double Vc=0;   
double Vout=0;

while(t <= Time){ // this while loop runs from the intial time to the final simulation time.
if (choice_of_wave == 1) {
vin = Vin;// Step wave selected.
} 
else {
vin = Vin*sin(2*PI*freq*t);// Sine wave selected
}

// Update capacitor voltage formula. this is to update the capacitor in the simulation.
Vc=decay_factor*Vc+(1.0-decay_factor)*vin;

// Output depends on filter type
if(low_pass_filter)
Vout = Vc; // output voltage for high pass filter. 

else //output voltage for high pass filter
Vout = vin - Vc;

printf("%.4lf\t%.3lf\t%.3lf\n", t, vin, Vout);// the format for each variable that is printed.
t = t + Step_time; // increment time for while loop until the final time.
}
printf("\nTime-domain simulation complete.\n"); // message to state to the user the simulation has completed successfully.
}


// MENU 5, HELP AND THEORY
void Help_and_theory(void) {
int choice_help_and_theory;
printf("\n>>Help and theory\n");

// Define the variables here to be used in this menu.
int information_filter_circuits,information_on_graphs,information_on_formulas;

// the options or choices to pick from.
printf("1. Information on filter circuits\n"
       "2. Information on graphs\n"
       "3. Information on formulas\n"
);
printf("choice: ");

while  (1){
fgets(help_and_theory, sizeof(help_and_theory), stdin);

// user inputs
if (sscanf(help_and_theory,"%d", &choice_help_and_theory) == 1 && (choice_help_and_theory== 1 || choice_help_and_theory == 2||choice_help_and_theory == 3)) {
break;
}
}

 //using switch statement to allow the user to pick between three options.
switch(choice_help_and_theory){
case 1:
// Case 1, description of filter circuits high pass and low pass RC filters. 
information_filter_circuits=1;
information_on_graphs=0;
information_on_formulas=0;
printf("information on filter circuits- \n");

printf("what is a filter circuit-\n\n" 
       "A filter circuit is a circuit that allows the user to eliminate certain frequencies\n"
       "while keeping in the frequency component that is desired. This can be done by using certain\n"
       "type of filters such as low pass filters,\n"
       "high pass filters, bandpass filters and many more. Each filter has its own\n" 
       "purpose of eliminating different frequency ranges whilst allowing certain\n"
       "frequency ranges for an example a low pass filter only keeps in low frequency\n"
       "components whilst attenuating high freqeuncy components\n"
);

// graph for the high pass filter
printf(
"\n           ----HIGH-PASS RC FILTER----\n\n"
"                Vin-------||-- (Capacitor\n"
"                              |\n"
"                              |\n"
"                              |\n"
"                              |\n"
"                              |\n"
"                              +--------- Vout\n"
"                              |\n"
"                              R      (Resistor)\n"
"                              |\n"
"                              |\n"
"                              GND\n\n");

printf("A high pass filter is a circuit that allows high frequencies\n"
       "to pass through while reducing the low frequency components\n"
       "What the high pass filter does is that above the cutoff frequency\n"
       "the frequencies are passed through easily whilst frequency\n"                   //DESCRIPTION OF HIGH PASS FILTER
       "that are below the cut off frequency are reduced.\n"
       "In a high pass filter circuit the capacitor is connected to the Vin\n"
       "and the capacitor is connected to the ground then the output is between\n"
       "the connections of the resistor and capacitor (same node)\n"
       "At low frequencies the capacitor will have high resistance which leads to\n"
       "most of the signals being blocked ie (most of the low pass frequncies have been attentuated).\n"
       "At high frequencies the capacitor will have low resistance which leads to the signal\n"
       "to pass through the resistor leading to the ouput.\n"
);
      
// graph for the high pass filter
printf(
"\n         ----LOW PASS RC FILTER----\n\n"
"                Vin-------+--R- (Resistor\n"
"                              |\n"
"                              |\n"
"                              |\n"
"                              |\n"
"                              |\n"
"                              +--------- Vout\n"
"                              |\n"
"                           ------\n"
"                           ------ (Capacitor)\n"
"                              |\n"
"                              |\n"
"                              GND\n\n"
);

printf("A low pass filter is a circuit that allows low frequencies\n"
       "to pass through while reducing the high frequency components.\n"
       "What the low pass filter does is that below the cutoff frequency\n"
       "the frequencies are passed through easily whilst frequency\n"                             //DESCRIPTION OF LOW PASS FILTER
       "that are above the cut off frequency are reduced.\n" 
       "Looking at the filter configuration above which shows the low pass RC filter.\n" 
       "The resisitor is connected to Vin and the capacitor is grounded and the reason for this\n"
       "because it creates a frequency dependant voltage divider. At low frequencies\n"                                                                                      
       "the impedance of the capacitor is high which leads to majority of the input voltage\n"
       "to appear accross it however this allows the signal to pass towards the output.\n"
       "At frequency the impedance of the capacitor becomes extremely low which then\n"
       "it acts like a short circuit.\n"
);

break;

case 2:
//second case to view information on graphs and how to analyse them.
information_filter_circuits=0;
information_on_graphs=1;
information_on_formulas=0;
printf("Information on graphs\n\n");
printf("In the frequency response graphs of any RC filters, there is a clear demonstration\n"
       "of how the circuit controls the flow of signals with some form of attenuations.\n"                  //Description of graph analysis.
       "looking at a graphical point of view on this as you can see a sharp cut off also\n"
       "known as the 3db cut off where the output drops to 70 percent of the input and this\n"
       "is called the cut off frequency.\n"
);
break;

case 3:
// case 3, stating key formulas for both low pass and high pass RC filters.
information_filter_circuits=0;
information_on_graphs=0;
information_on_formulas=1;
printf("information on formulas\n\n"
       "key formulas\n"              
);
printf("The cut off frequency\n\n"
       "W=2*PI*F*C\n\n"
       "FC=1/2PIRC\n\n"
       "Magnitude\n\n"
       "|H(JW)|=1/sqrt(1+(WRC)^2)\n\n"
       "Phase response\n\n"
       "phi=arctan(WRC)- High pass configuaration  or phi=-arctan(WRC)- Low pass configuration\n\n"
);
printf("Formulas will differ due to chosen filter circuit configuration\n\n");
// for low pass configuration
printf("---- low pass filter ----\n\n"
       "The cut off frequency- \n\n"
       "FC=1/2PIRC\n\n"
       "Magnitude- \n\n"
       "|H(JW)|=1/sqrt(1+(WRC)^2)\n\n"
       "phase response- \n\n"
       "phi=-arctan(WRC)\n\n"
);

// for High pass configuration
printf("\n---- High pass filter ----\n\n"
       "The cut off frequency- \n\n"
       "FC=1/2PIRC\n\n"
       "Magnitude- \n\n"
       "|H(JW)|=WRC/sqrt(1+(WRC)^2)\n\n"
       "phase response- \n\n"
       "phi=arctan(WRC)\n\n"
);

break;
}
}
// This is the end of the script.