#include <iostream>
#include "td3.hpp"
#include "support.hpp"
#include <stdlib.h>
#include <math.h>       // sin, cos
#include <assert.h>

using namespace std;

using namespace support;

double* extend_array(double* array, int length, int new_size) {
    double *newarray;
    newarray = new double [new_size];
    for (int x= 0; x<= length; x++){
        newarray[x] = array[x];
    }
    for (int x= length; x<= (new_size-length); x++){
        newarray[x] = 0;
    }
    delete array;

  return newarray; // YOU CAN CHANGE THIS
}

double* shrink_array(double* array, int length, int new_size) {
    double *newarray;
    newarray = new double [new_size];
    for (int x= 0; x<= length; x++){
        newarray[x] = array[x];
    }
    delete array;

  return newarray;
}

double* append_to_array(double element,
                        double* array,
                        int &current_size,
                        int &max_size) {
    double *newarray;
    if (current_size==max_size){
        newarray = extend_array(array,max_size,max_size+5);
        max_size = max_size+5;
    }
    else{
        newarray= array;
    }

    newarray[current_size] = element;

    current_size+=1;

  return newarray; // YOU CAN CHANGE THIS
}

double* remove_from_array(double* array,
                          int &current_size,
                          int &max_size) {
   if (max_size-current_size >= 4){
       double *newarray;
       newarray = new double [max_size-5];
       for (int x= 0; x< current_size; x++){
           newarray[x] = array[x];
       }
       max_size = max_size-5;
       current_size += -1;
       return newarray;
   }
   array[current_size] = 0;
   current_size+=-1;

  return array; // YOU CAN CHANGE THIS
}

bool simulate_projectile(const double magnitude, const double angle,
                         const double simulation_interval,
                         double *targets, int &tot_targets,
                         int *obstacles, int tot_obstacles,
                         double* &telemetry,
                         int &telemetry_current_size,
                         int &telemetry_max_size) {
  // YOU CAN MODIFY THIS FUNCTION TO RECORD THE TELEMETRY

  bool hit_target, hit_obstacle;
  double v0_x, v0_y, x, y, t;
  double PI = 3.14159265;
  double g = 9.8;

  v0_x = magnitude * cos(angle * PI / 180);
  v0_y = magnitude * sin(angle * PI / 180);

  t = 0;
  x = 0;
  y = 0;

  hit_target = false;
  hit_obstacle = false;
  while (y >= 0 && (! hit_target) && (! hit_obstacle)) {
    double * target_coordinates = find_collision(x, y, targets, tot_targets);
    if (target_coordinates != NULL) {
      remove_target(targets, tot_targets, target_coordinates);
      hit_target = true;
    } else if (find_collision(x, y, obstacles, tot_obstacles) != NULL) {
      hit_obstacle = true;
    } else {
      t = t + simulation_interval;
      y = v0_y * t  - 0.5 * g * t * t;
      x = v0_x * t;
    }
    telemetry = append_to_array(t,telemetry,telemetry_current_size,telemetry_max_size);
    telemetry = append_to_array(x,telemetry,telemetry_current_size,telemetry_max_size);
    telemetry = append_to_array(y,telemetry,telemetry_current_size,telemetry_max_size);
  }

  return hit_target;
}

void merge_telemetry(double **telemetries,
                     int tot_telemetries,
                     int *telemetries_sizes,
                     double* &global_telemetry,
                     int &global_telemetry_current_size,
                     int &global_telemetry_max_size) {
    int k = 0;
    //sort the telemetries size then do it for the first one then for the second one and so on
    for (int j = 0; j<=telemetries_sizes[k]*3; j+=3){
        for (int i=0;i<=tot_telemetries;i++){
            //append_to_array(telemetries[i][j])
        }

    }
}
