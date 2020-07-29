/*  This program is used to find a cab within a radius of 50 km using the great-circle distance formula.
    The input is read from a .json file and output is also written to a .json file.
    The json file contains some data enclosed in {} which contains the latitude,longitude,user-id and name.
    A struct with name json is declared in the code which contains the neccessary algorithm to read the latitude,
    longitude and store them into an array of char datatype. The later is casted into double using
    atof().After evaluating the latitude and longitude the values are passed to a function which calculates the distance
    between the cab and the user by the great-circle distance formula.

    The ouput files contain only those drivers which falls in the proximity of 50.00 km.

    The latitude and longitude of the customer has been previously defined in the code.
    
    The great-circle distance formula is used to calculate the distance between two points in a sphere.

    https://en.wikipedia.org/wiki/Great-circle_distance#:~:text=The%20great%2Dcircle%20distance%20or,line%20through%20the%20sphere's%20interior).
    
    I suggest you go through this link before moving on to the source code  */


#include<iostream>

#include<fstream>

#include<math.h>

#include<string>

#include<time.h>


using namespace std;

#define Earth_Radius 6371.00

#define PI 3.1428571428571

#define lat1d 12.9611159 

#define long1d 77.6362214 




double degreeTorad(double deg){
    return (deg*PI/180);
}


//Function to find out the distance between two points in a sphere

double Great_Circle_Distance(double lat2d,double long2d){
    double lat1,lat2,long1,long2,central_angle,delta_long;
    lat1=degreeTorad(lat1d);
    lat2=degreeTorad(lat2d);
    long1=degreeTorad(long1d);
    long2=degreeTorad(long2d);

    delta_long=abs(long2-long1);

    central_angle= acos( sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(delta_long) );

    return (Earth_Radius*central_angle);

}

struct json{

    long long int length,i,j,f,fi,x,y,m,n,id[1000];

    char char_latitude[1000],char_longitude[1000],string_id[1000],name[1000];

    double lat2d,long2d;

    string line;


    //Function to check whether distacne between two points is less than 50.00 km

    void distance_calculator(){
        if(Great_Circle_Distance(lat2d,long2d)<=50.00){
            id[i]=atoll(string_id);
            i++;
            out <<"{\"user_id\":"<<id[i-1]<<",\"name\":"<<name<<"}"<<endl;
        }

    }

    // Function to read data from the .json file 

    void json_parser(){
        if(customer.is_open()){
            while(getline(customer,line)){
                f=fi=x=y=m=n=0;
                length=line.size();
                for(j=0;j<length;j++){

                    if(line[j]=='"'){
                        f++;
                    }

                    else if(line[j]==':'){
                        fi++;
                    }

                    if(f==3){
                        j++;
                        while(line[j]!='"'){
                            char_latitude[x]=line[j];
                            j++;
                            x++;
                        }
                        j--;
                        char_latitude[x]='\0';

                    }

                    else if(f==13){
                        j++;
                        while(line[j]!='"'){
                            char_longitude[y]=line[j];
                            y++;
                            j++;
                        }
                        j--;
                        char_longitude[y]='\0';
                    }

                    if(fi==2){
                        j+=2;
                        while(line[j]!=','){
                            string_id[m]=line[j];
                            m++;
                            j++;
                        }
                        j--;
                        string_id[m]='\0';
                        fi++;
                    }

                    else if(fi==4){
                        j+=2;
                        while(line[j]!=','){
                            name[n]=line[j];
                            n++;
                            j++;
                        }
                        j--;
                        name[n]='\0';
                        fi++;
                        f+=2;
                    }


                }

                lat2d=atof(char_latitude);
                long2d=atof(char_longitude);
                distance_calculator();
                

            }

        }
        customer.close();
        out.close();
    }





};

int main(){
    
    
    json obj;

    obj.json_parser();

    return 0;
}

    
        
