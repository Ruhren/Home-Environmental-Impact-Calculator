/*
Home Environment Impact Category Calculator 
Author: Ruha Renu 
This program aims to calculate the category scores of the environmental impact of the user's home. The program tries to ask the minimum no of questions 
to calculate the category score . The main idea was to ask the right questions that could help the program easily compute the score. A struct is used store 
the users input. There are few functions like clear_Buffer(); int validate(const char *promt, int min, int max ); for error handling, clear_Buffer will clear
any unwanted charcters left behind by scanf and return s true , if it has found any to inform the user.validate function , clearly focuses on validating input,
it makes sure that scanf has properly read it an integer and not a character , makes sure that there isnt unwanted charcters in the buffer as well as ensures 
input is within valid range. Get_water(), get_energy(), get_power(); get_urban_rural(); all focuses on getting a valid input from user , they simply call the vallidate function
inside it. Lastly display_score(int index); prints the final score of the user and exits the program. All these functions are strategicly used along with if else statements to create 
the logic for the category calculation. There us two seperate logic for house and apartment . This program error handles most of the error a user may make. While sometimes , the program
outputs the score almost immediately , it could ask for more data from the users in other situations to determin the category score
*/

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>

struct data
{
    int type;//house[1]/appartment[2]
    int urban_rural;//urban[1] or rural[2]
    int power;//solar[1] or grid[2]
    int home_age;// age of house , valid input 5+ yrs
    int energy_usage;//KwH per year,valid input 1000-20000
    int water_usage;//gallons per day,valid input 20-300

};//defining data on user's home

bool clear_Buffer();
int validate(const char *promt, int min, int max );
int get_energy();
int get_water();
int get_power();
int get_urban_rural();
void display_score(int index);

int main(void)
{
    struct data home_data;
    //welcoming user
    printf("Welcome to the Home Environment Impact Category Calculator.\n"
           "This program will help you understand where your home stands in terms of the impacts it has on the environment,\n"
           "You will be asked a series of question and a score category will be awarded to you based on your data.\n"
          );
    printf("\n");
    while(1 == 1){//error handling-house
        printf("what type of home do you own?\n"
        "Enter 1 for house and 2 for apartment\n");//asking user for types of home
        
        if( scanf("%d",&home_data.type) != 1 ) {//non integer input like character           
            printf("Invalid input \n");
            clear_Buffer();
            continue;
        }

        if (clear_Buffer()) {
            printf("Invalid input!\n");
            continue; 
        }
        
        if(home_data.type==1 || home_data.type == 2){            
            if(home_data.type == 1){//logic for house 
                //Asking for age of house
                while(1 == 1){
                    printf("Enter age of house:\n");

                    if( scanf("%d",&home_data.home_age) != 1 ) {
                        //non integer input like character
                        printf("Invalid input \n");
                        clear_Buffer();
                        continue;
                    }
            
                    if (clear_Buffer()) {//if there is extra values detedvted
                        printf("Invalid input!\n");
                        continue; 
                    }
                    if(home_data.home_age>=0){
                        if(home_data.home_age>=60) { //when house is over 60 yrs-> unsatisfactory
                            display_score(0);
                        } else if(home_data.home_age>=0 && home_data.home_age<15){ //house 5-15 yrs -> excellent
                            display_score(5);
                        } else if(home_data.home_age>=50 && home_data.home_age<60) { //house 50-60 yrs     
                            home_data.urban_rural=get_urban_rural(); //Urban or Rural

                            if(home_data.urban_rural == 1) { //urban
                                        home_data.energy_usage=get_energy(); //asking energy use

                                        if(home_data.energy_usage<4000) {//energy < 4000 -> poor
                                            display_score(1);
                                        } else {//energy 4000 and above -> unsatisfactory
                                            display_score(0);
                                        }
                                    } else { //rural
                                        //solar or grid
                                        home_data.power=get_power();

                                        if(home_data.power == 1) { //solar
                                            //asking energy use
                                            home_data.energy_usage=get_energy();
                                                    
                                             if(home_data.energy_usage < 4000) {//energy < 4000 -> satisfactory
                                                display_score(2);
                                            } else { //energy 4000 and above and solar-> poor
                                                display_score(1);
                                             }                                                    
                                        } else { //grid
                                           //asking energy use
                                           home_data.energy_usage=get_energy();

                                            if(home_data.energy_usage < 4000) { //energy < 4000 -> poor
                                                display_score(1);
                                             } else{ //energy 4000 and above and solar-> unsatisfactory
                                                display_score(0);
                                             }  
                                        }
                                    } 
                        } else if(home_data.home_age>=40 && home_data.home_age<50) { //40-50 yrs
                            //urban or rural
                            home_data.urban_rural=get_urban_rural();
                            if(home_data.urban_rural == 1) {//urban
                                //solar or grid
                                home_data.power=get_power();

                                if(home_data.power ==  1) { //solar
                                    //asking for energy use
                                    home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage < 4000) {//energy < 4000 -> ask water usage
                                        //asking water usage
                                        home_data.water_usage=get_water();

                                        if(home_data.water_usage<50) { //water usage <50 -> good
                                            display_score(3);
                                        } else { //water usage 50 and above -> satisfactory
                                            display_score(2);
                                        }  
                                    }  else { //energy 4000 and above and solar-> poor
                                        display_score(1);
                                    }   
                                } else { //grid
                                    //asking energy use
                                    home_data.energy_usage=get_energy();
                                    
                                    if(home_data.energy_usage>=12000) { //energy usage >=12000 -> unsatisfactory
                                        display_score(0);
                                    } else if(home_data.energy_usage>=4000 && home_data.energy_usage<9000){ //energy usage 4000-9000 -> poor
                                        display_score(1);
                                    } else if(home_data.energy_usage<4000 ) { //energy usage <4000 -> satisfactory
                                        display_score(2);
                                    } else if(home_data.energy_usage>=9000 && home_data.energy_usage<12000){//water usage
                                        home_data.water_usage=get_water();

                                        if(home_data.water_usage<50 || (home_data.energy_usage>=50 && home_data.energy_usage<100)) { //water usage <50 or between 50-100 -> poor
                                            display_score(1);
                                        } else{ //water usage in other cases-> unsatisfactory
                                            display_score(0);
                                        }
                                    }
                                } 
                            } else { //rural
                                //solar or grid
                                home_data.power=get_power();

                                if(home_data.power == 1) { //solar
                                 //asking energy
                                  home_data.energy_usage=get_energy();

                                  if(home_data.energy_usage < 4000) { //energy usage < 4000 -> good
                                    display_score(3);
                                  } else {//wenergy usage of 4000 and above->satisfactory
                                         display_score(2);
                                    }                     
                                }
                                else{ //grid
                                    //asking energy
                                     home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage < 4000){ //energy usage < 4000 
                                        // water usage 
                                        home_data.water_usage=get_water();

                                        if(home_data.water_usage < 50) {//water usage < 50 -> good
                                             display_score(3);
                                        } else {//water usage 50 and above->satisfactory
                                             display_score(2);
                                        }
                                    } else { //energy usage of 4000 and above->poor
                                         display_score(1);
                                     }                                                                        
                                }
                            }
                        }
                        else if(home_data.home_age>=30 && home_data.home_age < 40) { //30-40 yrs
                            //urban or rural
                            home_data.urban_rural=get_urban_rural();

                            if(home_data.urban_rural == 1){ //if urban
                                //energy usage
                                home_data.energy_usage=get_energy();

                                if(home_data.energy_usage >= 4000 && home_data.energy_usage < 9000) {//energy 4000-9000 -> good
                                    display_score(3);
                                } else { // all other energy usage
                                    // solar or grid
                                    home_data.power=get_power();

                                    if(home_data.power == 1) { // solar
                                        if(home_data.energy_usage < 4000) { //when solar and energy < 4000 -> very good 
                                            display_score(4);
                                        } else { // all other cases of energy usage except energy 4000-9000 and usage of solar power - > good
                                            display_score(3);
                                        }
                                    } else { // when grid
                                        if(home_data.energy_usage >= 12000 || (home_data.energy_usage >= 9000 && home_data.energy_usage < 12000)) {
                                            // either energy >= 12000 or  energy = 9000-12000 -> satisfactory
                                            display_score(2);
                                        } else if(home_data.energy_usage < 4000) { // energy <4000 and grid power 
                                            // water usage
                                            home_data.water_usage=get_water();

                                            if(home_data.water_usage < 50 || home_data.water_usage >= 150) { // water usage < 50 or water usage > 150 -> very good 
                                                display_score(4);
                                            } else if(home_data.water_usage >= 50 && home_data.water_usage <150) { //water usage = 50 - 150 -> good  
                                                display_score(3);
                                            }
                                        }
                                    }
                                }
                            }
                            else { // if rural
                                //energy usage
                                home_data.energy_usage=get_energy();

                                if(home_data.energy_usage < 4000) { // energu < 4000 -> very good
                                    display_score(4);
                                } else { //other energy usage 
                                    // solar or grid
                                    home_data.power=get_power();

                                    if(home_data.power == 2) { //grid -> good
                                        display_score(3);
                                    } else { //solar
                                        if(home_data.energy_usage >= 4000 && home_data.energy_usage < 12000){
                                            // if solar and energy 9000-12000 or 4000 - 9000 -> very good 
                                            display_score(4);
                                        } else { // if solar and energy >= 12000
                                            // water usage
                                            home_data.water_usage=get_water();

                                            if(home_data.water_usage < 50) { // if solar , energy >= 12000, water usage < 50 -> very good 
                                                display_score(4);
                                            } else { //if solar , energy >= 12000, water usage= 50 and above -> good 
                                                display_score(3);
                                            }
                                        }
                                    }
                                }
                            }
                        } else if(home_data.home_age>=15 && home_data.home_age < 30) { //15-30 yrs
                            //energy usage
                            home_data.energy_usage=get_energy();

                            if(home_data.energy_usage < 4000) { // energy < 4000 -> excellent
                                display_score(5);
                            } else { // all other energy 
                                //urban or rural
                                home_data.urban_rural=get_urban_rural();

                                if(home_data.power == 1) {// urban
                                    if(home_data.energy_usage >= 12000) { // if urban & energy >=12000 -> very good
                                        display_score(4);
                                    } else { //urban and other categories 
                                        // solar or grid
                                        home_data.power=get_power();
                                        
                                        if( home_data.power == 2){ //grid -> very good
                                            display_score(4);
                                        } else { //solar
                                            if(home_data.energy_usage >= 4000 && home_data.energy_usage < 9000) {
                                                // urban, solar, energy = 4000 - 9000 -> excellent
                                                display_score(5);
                                            } else if(home_data.energy_usage >= 9000 && home_data.energy_usage < 12000) {
                                                // urban, solar, energy = 9000 - 120000 
                                                // water usage
                                                home_data.water_usage=get_water();

                                                if(home_data.water_usage < 50 || (home_data.water_usage >= 50 && home_data.water_usage < 100)) {
                                                    //urban,solar,energy = 9000 - 12000, water < 50 or water = 50-100 -> excellent
                                                    display_score(5);
                                                } else if(home_data.water_usage >= 100) {
                                                    //urban,solar,energy = 9000 - 12000, water 100-150 or water >= 150 -> very good
                                                    display_score(4);
                                                }
                                            }
                                        }
                                    }
                                } else { //rural
                                    //solar or grid
                                    home_data.power=get_power();

                                    if(home_data.power == 1) {//solar-> excellent
                                        display_score(5);
                                    } else { // grid
                                        if(home_data.energy_usage >= 4000 && home_data.energy_usage < 9000) {  // energy 4000-9000 -> excellent
                                            display_score(5);
                                        } else if(home_data.energy_usage >= 9000 && home_data.energy_usage < 12000) { //energy 9000-12000 
                                            //water usage
                                            home_data.water_usage=get_water();

                                            if(home_data.water_usage < 100) { //rual,grid,energy 9000-12000, water < 50 or water 50-100 -> excellent
                                                display_score(5);
                                            } else if(home_data.water_usage >= 100 ) { //rual,grid,energy 9000-12000, water 100-150 or water >= 150 -> very good
                                                display_score(4);
                                            }
                                        }else if(home_data.energy_usage >= 12000){ //energy >= 12000
                                            //water usage
                                            home_data.water_usage=get_water();

                                            if(home_data.water_usage < 50){ //rual,grid,energy >=12000, water < 50-> excellent
                                                display_score(5);
                                            } else { //rual,grid,energy >=12000, water 50 and above >= 150 -> very good
                                                display_score(4);
                                            }
                                        }
                                    } 
                                }
                            }
                        }
                    } else {
                        printf("Only houses that are 0+ yrs can be assesed\n");
                    }
                }
            }else if(home_data.type == 2) { //logic for appartment 
                //appartmeant age
                while(1 == 1){
                    printf("How old is you appartmant ? \n");
                    if( scanf("%d",&home_data.home_age) != 1 ) {//non integer input like character
                        printf("Invalid input \n");
                        clear_Buffer();
                        continue;
                    }
            
                    if (clear_Buffer()) {//if there is extra values detedvted
                        printf("Invalid input!\n");
                        continue; 
                    }

                    if(home_data.home_age >= 0){
                        if(home_data.home_age >= 60) { //age >= 60 yrs -> unsatisfactory
                            display_score(0);
                        } else if(home_data.home_age >= 0 && home_data.home_age < 30) { //age = 5-30 yrs -> excellent
                            display_score(5);
                        } else if(home_data.home_age >= 50 && home_data.home_age < 60) { //age = 50 - 60 yrs
                            //urban or rural
                            home_data.urban_rural=get_urban_rural();

                            if(home_data.urban_rural == 1) { //urban
                                // solar or grid
                                home_data.power=get_power();

                                if(home_data.power == 2){ //grid -> unsatisfactory
                                    display_score(0);
                                } else { //solar
                                    //energy use
                                    home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage >= 12000) { //energy >= 12000 -> unsatisfactory
                                        display_score(0);
                                    } else { //energy = 9000-12000,4000-9000,<4000 ->poor
                                        display_score(1);
                                    }
                                }
                            } else { //rural
                                // solar or grid
                                home_data.power=get_power();

                                if(home_data.power == 1) { //solar
                                    //energy usage
                                    home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage >= 12000) { //energy >= 12000,-> poor
                                        display_score(1);
                                    } else { //energy = 9000-12000 ,4000-9000, < 4000 -> satisfactory
                                        display_score(2);
                                    }
                                } else { //grid
                                    //energy usage
                                    home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage >= 12000) { //energy >= 12000,-> unsatisfactory
                                        display_score(0);
                                    } else { //energy = 9000-12000 ,4000-9000, < 4000 -> poor
                                        display_score(1);
                                    }
                                }
                            }
                        } else if(home_data.home_age >= 40 && home_data.home_age < 50) { // age = 40 -50 yrs
                            //urban or rural
                            home_data.urban_rural=get_urban_rural();

                            if(home_data.urban_rural == 1) { //urban
                                //energy usage
                                home_data.energy_usage=get_energy();

                                if(home_data.energy_usage >= 12000){ //energy >= 12000,-> poor
                                    display_score(1);
                                } else { //energy = 9000-12000 ,4000-9000, < 4000 
                                    //solar or grid
                                    home_data.power=get_power();

                                    if(home_data.power == 1) { //solar -> good
                                        display_score(3);
                                    } else { //grid -> satisfactory
                                        display_score(2);
                                    }
                                }
                            } else {  //rural
                                //solar or grid
                                home_data.power=get_power();

                                if(home_data.power == 1) { //solar
                                    //energy usage
                                    home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage >= 12000) { //energy >= 12000,-> good
                                        display_score(3);
                                    } else { //energy = 9000-12000 ,4000-9000, < 4000 -> very good
                                        display_score(4);
                                    }
                                }else { //grid
                                    //energy usage
                                    home_data.energy_usage=get_energy();

                                    if(home_data.energy_usage >= 12000){ //energy >= 12000,-> satisfactory
                                        display_score(2);
                                    } else {  //energy = 9000-12000 ,4000-9000, < 4000 -> good
                                        display_score(3);
                                    }
                                }
                            }
                        } else if(home_data.home_age >= 30 && home_data.home_age < 40) { //age = 30- 40 yrs
                            //urban or rural
                            home_data.urban_rural=get_urban_rural();

                            if(home_data.urban_rural == 1) { //urban
                                //solar or grid
                                home_data.power=get_power();
                                //energy usage
                                home_data.energy_usage=get_energy();

                                if(home_data.power == 1) {//solar
                                    if(home_data.energy_usage >= 12000) {//energy >= 12000,-> good
                                        display_score(3);
                                    } else { //energy = 9000-12000 ,4000-9000, < 4000 -> very goood
                                        display_score(4);
                                    }
                                } else { //grid
                                    if(home_data.energy_usage >= 12000) { //energy >= 12000,-> satisfactory
                                        display_score(2);
                                    } else { //energy = 9000-12000 ,4000-9000, < 4000 -> good
                                        display_score(3);
                                    }
                                }
                            } else { //rural
                                //energy usage
                                home_data.energy_usage=get_energy();

                                if(home_data.energy_usage < 12000) {  //energy = 9000-12000,4000-9000,<4000 -> very good
                                    display_score(4);
                                } else if(home_data.energy_usage >= 12000) { //energy >= 12000 
                                    //solar or grid
                                    home_data.power=get_power();

                                    if(home_data.power == 1) {  //solar- very good
                                        display_score(4);
                                    } else { //grid-> good
                                        display_score(3);
                                    }
                                }
                            }
                        }
                    } else {
                        printf("Only appartments that are 0+ yrs can be assesed\n");
                    }
                }//error handling for age               
            }
        } else {
            printf("Enter valid 1 or 2\n");
        }
    
}
}
bool clear_Buffer() {
    int c;
    bool extra=false;
    while ((c = getchar()) != '\n' && c != EOF){
        extra=true;
    }// Flush input buffer

    return extra;
}//bufferclear-error handling-clears buffer when using scanf and the user enters a non-integer

int validate(const char *promt, int min, int max ) {
    int input;
    while (1==1) {
        printf("%s\n",promt);
        if( scanf("%d",&input) != 1 ) {
            //non integer input like character
            printf("Invalid input \n");
            clear_Buffer();
            continue;
        }

        if (clear_Buffer()) {//if there is extra values detedvted
            printf("Invalid input!\n");
            continue; 
        }
         
        if(input>=min && input<=max) {
            return input;
        } else{ printf("Invalid input. Please enter a value between %d and %d.\n", min, max);}
    }
    }//validation function-error handling

int get_energy() {
    return validate("Enter your energy usage in KwH per yr ",1000,20000);
}//getting energy usage

int get_water() {
    return validate("Enter your water usage in gallons per day",20,300);
}//getting water usage

int get_power() {
    return validate("Do you use solar or grid power(1 for solar , 2 for grid)",1,2);
}//getting the type of power

int get_urban_rural() {
    return validate("Do you live in a urban or rural area (1 for urban , 2 for rural)",1,2);
}//getting urban or rural home

void display_score(int index) {
    char category_score[6][80]={ {"unsatisfactory"}, {"poor"}, {"satisfactory"}, {"good"}, {"very Good"}, {"Excellent"} };//score categories
    printf("Your environmental impact category is %s\n", category_score[index]);
    exit(0);
}//displaying output