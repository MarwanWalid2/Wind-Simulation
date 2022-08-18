                        ///* Marwan AbdElhameed *///
///* Mechanical Engineering Case Study – Flight Simulator Wind Speed///

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;
//functions prototype
void loadConfiguration(int arr1[], int arr2[], int arr3[]);
void generateStormData (int speedarr[], int storms[], int arr1[], int arr3[]);
void generateBurstData (int speedarr[],int stormarr[], int config[], int arr1[]);
void generateWindSimulation(int speedarr[], int stormarr[], int burstarr[], int arr1[]);
//main function
int main()
{
    //opening the config file to get the data from
    ifstream file1;
    file1.open("simulationConfiguration.txt" , ios::in );
    //print error message if file does not open
    if (file1.fail())
    {
        cerr << "Error opening the file \n";
        exit (0);
    }
//saving data from each line of the file into an array
    int arr[4],arr2[5], arr3[5];
    for(int i = 0; i < 4; i++){
        file1 >> arr[i];
    }
    for(int i = 0; i < 5; i++){
        file1 >> arr2[i];
    }
    for(int i = 0; i < 5; i++){
        file1 >> arr3[i];
    }

    loadConfiguration(arr, arr2, arr3);
    //close the file
    file1.close();
    return 0;
}
void loadConfiguration(int arr1[], int arr2[], int arr3[]){
    //creating filestream and create and open windspeeddata.txt to save the new data into
    ofstream config;
    config.open("WindSpeedData.txt",ios::out);
    //print error message if file does not open
    if (config.fail())
    {
    cerr << "Error opening the file \n";
    exit (0);
    }
    int speedarr[arr1[2]];
    //writing the new values into the file
    config << left << setw(10) << "duration" << left << setw(10) << "windspeed" << endl;
srand (time(NULL));
    for(int i = 0; i <= arr1[2]; i += arr1[3]){

        int randomwind =  rand()% (((arr1[0]+arr1[1]) - (arr1[0] - arr1[1]))+1)+(arr1[0] - arr1[1]);
        config << left << setw(10) << i << left << setw(10) << randomwind << endl;
                speedarr[i]=randomwind;

    }
generateStormData (speedarr, arr2, arr1, arr3);
//close the file
config.close();
}


void generateStormData (int speedarr[], int config[], int arr1[], int arr3[]){
   srand (time(NULL));
   //creating filestream and creating and opening stormdata.txt
    ofstream stormdata;
    stormdata.open("StormData.txt",ios::out);
    //print error message if file does not open
    if (stormdata.fail())
    {
    cerr << "Error opening the file \n";
    exit (0);
    }
    //declaring variables
   float newspeed;
    float randProbability = (rand()%100);
    randProbability = randProbability/100;
    float probability = config[0];
    float prob = probability/100;
    int i=0;
    int stormarr[arr1[2]];
    //reading the new data into the file (if the conditions are true)
 stormdata << left << setw(10) << "duration" << left << setw(10) << "windspeed" << endl;

while ( i <= arr1[2]){
    float randomstorm = config[1]+rand()% ((config[2]-config[1]+1));
    float T = config[3]+rand()% ((config[4]-config[3]+1));
    float newtime = T +i;

    if (randProbability <= prob){
     for (i; i <= newtime && i <= arr1[2]; i+= arr1[3]){
   newspeed = randomstorm + speedarr[i];
   stormdata << left << setw(10) << i << left << setw(10) << newspeed << endl;
   stormarr[i]=newspeed;
        }
   }
   else {stormdata << left << setw(10) << i << left << setw(10) << speedarr[i] << endl;
   stormarr[i]=speedarr[i];
   i+= arr1[3];
   }

    randProbability = (rand()%100);
    randProbability = randProbability/100;

   }
generateBurstData (speedarr,stormarr, arr3,arr1);
//close the file
stormdata.close();
   }


   void generateBurstData (int speedarr[],int stormarr[], int config[], int arr1[]){
   srand (time(NULL));
   bool isStorm;
   //creating filestream and creating and opening burstdata.txt
   ofstream burstdata;
    burstdata.open("BurstData.txt",ios::out);
     //print error message if file does not open
    if (burstdata.fail())
    {
    cerr << "Error opening the file \n";
    exit (0);
    }
    //declaring variables
    float newspeed;
    float randProbability = (rand()%100);
    randProbability = randProbability/100;
    float probability = config[0];
    float prob = probability/100;
    int burstarr[arr1[2]];
    int i=0;
    //reading the new data into the file (if the conditions are true)
 burstdata << left << setw(10) << "duration" << left << setw(10) << "windspeed" << endl;

while ( i <= arr1[2]){
    float randomburst = config[1]+rand()% ((config[2]-config[1]+1));
    float T = config[3]+rand()% ((config[4]-config[3]+1));
    float bursttime = T +i;
    if (stormarr[i]>speedarr[i]){
        isStorm = true;
    }
    else {
        isStorm = false;
    }
    if (randProbability <= prob){
    for (i; isStorm == true &&i <= bursttime; i+= arr1[3]){
    newspeed = randomburst + stormarr[i];
    burstdata << left << setw(10) << i << left << setw(10) << newspeed << endl;
    burstarr[i]=newspeed;
        }
   }
   else {burstdata << left << setw(10) << i << left << setw(10) << stormarr[i] << endl;
   burstarr[i]=stormarr[i];
   i+= arr1[3];
   }

    randProbability = (rand()%100);
    randProbability = randProbability/100;

   }
generateWindSimulation(speedarr, stormarr, burstarr, arr1);
//close the file

burstdata.close();
   }


   void generateWindSimulation(int speedarr[], int stormarr[], int burstarr[], int arr1[]){
//creating filestream and creating and opening WindSimulation.txt
   ofstream windsimulation;
    windsimulation.open("WindSimulation.txt",ios::out);
    //collecting the values from the other files and reading the new data into the file (if the conditions are true)
   windsimulation << left << setw(10) << "duration" << left << setw(10) << "windspeed" << left << setw(12)<< "stormspeed" << left << setw(10) << "burstspeed" << endl;
   for(int i = 0; i <= arr1[2]; i += arr1[3]){
   windsimulation << left << setw(10) << i << left << setw(10) << speedarr[i] << left << setw(12)<< stormarr[i] << left << setw(10) << burstarr[i];
   if (stormarr[i] > speedarr[i]){

    windsimulation << left << setw(10) << "1" << endl;

   }
   else {windsimulation << endl;}
   }
   cout << "done reading data"<<endl;
   //close the file
  windsimulation.close();
   }


