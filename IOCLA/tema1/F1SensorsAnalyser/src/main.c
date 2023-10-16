#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "operations.h"

void printAll(sensor *sensor, int nrSensors) {  // print all sensors

    for (int i = 0; i < nrSensors; i++) {
        if (sensor[i].sensor_type == 1) { // checking the sensor type before getting data
            power_management_unit *pmu = (power_management_unit *)sensor[i].sensor_data;

            printf("Power Management Unit\n");
            printf("Voltage: %.2f\n", pmu->voltage);
            printf("Current: %.2f\n", pmu->current);
            printf("Power Consumption: %.2f\n", pmu->power_consumption);
            printf("Energy Regen: %d%%\n", pmu->energy_regen);
            printf("Energy Storage: %d%%\n", pmu->energy_storage);
        } else {
            tire_sensor *tire = (tire_sensor *)sensor[i].sensor_data;

            printf("Tire Sensor\n");
            printf("Pressure: %.2f\n", tire->pressure);
            printf("Temperature: %.2f\n", tire->temperature);
            printf("Wear Level: %d%%\n", tire->wear_level);

            if (tire->performace_score != 0) {
                printf("Performance Score: %d\n", tire->performace_score);
            } else {
                printf("Performance Score: Not Calculated\n");
            }
        }
    }
}

void printIndex(sensor *sensor, int index) { // print sensor with a given index
    if (sensor[index].sensor_type == 1) { // checking the sensor type before getting data
        // convert sensor data to type of sensor and get info
        power_management_unit *pmu = (power_management_unit *)sensor[index].sensor_data;

        printf("Power Management Unit\n");
        printf("Voltage: %.2f\n", pmu->voltage);
        printf("Current: %.2f\n", pmu->current);
        printf("Power Consumption: %.2f\n", pmu->power_consumption);
        printf("Energy Regen: %d%%\n", pmu->energy_regen);
        printf("Energy Storage: %d%%\n", pmu->energy_storage);
    } else {
        tire_sensor *tire = (tire_sensor *)sensor[index].sensor_data;

        printf("Tire Sensor\n");
        printf("Pressure: %.2f\n", tire->pressure);
        printf("Temperature: %.2f\n", tire->temperature);
        printf("Wear Level: %d%%\n", tire->wear_level);

        if (tire->performace_score != 0) {
            printf("Performance Score: %d\n", tire->performace_score);
        } else {
            printf("Performance Score: Not Calculated\n");
        }
    }
}

// read values for PMU

void readPMU(sensor *sensors, int index, FILE *input) {
    float voltage, current, pc;
    int er, es;
    power_management_unit *pmu;
    pmu = malloc(sizeof(power_management_unit));

    // using fread for binary files
    fread(&voltage, sizeof(float), 1, input);
    fread(&current, sizeof(float), 1, input);
    fread(&pc, sizeof(float), 1, input); // power consumptiom
    fread(&er, sizeof(int), 1, input); // energy regen
    fread(&es, sizeof(int), 1, input); // energy storage

    pmu->voltage = voltage;
    pmu->current = current;
    pmu->power_consumption = pc;
    pmu->energy_regen = er;
    pmu->energy_storage = es;
    sensors[index].sensor_data = (void *)pmu; // puting the data in the sensor vector

    fread(&sensors[index].nr_operations, sizeof(int), 1, input);
    sensors[index].operations_idxs = malloc(sensors[index].nr_operations * sizeof(int));

    // reading the operations indexes in order
    for (int i = 0; i < sensors[index].nr_operations; i++) {
        int no_op;
        fread(&no_op, sizeof(int), 1, input);
        sensors[index].operations_idxs[i] = no_op;
    }
}

// read data for tire sensor

void readTire(sensor *sensors, int index, FILE *input) {
    float pressure, temperature;
    int wl, ps = 0;
    tire_sensor *tire;
    tire = malloc(sizeof(tire_sensor));

    fread(&pressure, sizeof(float), 1, input);
    fread(&temperature, sizeof(float), 1, input);
    fread(&wl, sizeof(int), 1, input);
    fread(&ps, sizeof(int), 1, input);

    tire->pressure = pressure;
    tire->temperature = temperature;
    tire->wear_level = wl;
    tire->performace_score = ps;
    sensors[index].sensor_data = (void *)tire;

    fread(&sensors[index].nr_operations, sizeof(int), 1, input);
    sensors[index].operations_idxs = malloc(sensors[index].nr_operations * sizeof(int));

    for (int i = 0; i < sensors[index].nr_operations; i++) {
        int no_op;
        fread(&no_op, sizeof(int), 1, input);
        sensors[index].operations_idxs[i] = no_op;
    }
}

// swaping two elements in the sensor vector for sorting it

void swap(sensor *sensors, int index) {
    sensor temp = sensors[index];
    sensors[index] = sensors[index - 1];
    sensors[index - 1] = temp;
}

/* deleting the sensor which is not within the
 * right parameters and resizing the vector
 */

void freeSensor(sensor *sensors, int *nrSensors, int *index) {
    free(sensors[*index].sensor_data);
    free(sensors[*index].operations_idxs);

    for (int j = *index; j < (*nrSensors) - 1; j++) {
        sensors[j] = sensors[j + 1];
    }

    (*index)--; // update the index in order to keep the position in the vector
    (*nrSensors)--; // update the number of elements
}

/* function for searching for anomalies in
 * sensor data and deleting them when found
 * using freeSensor function
 */

void clear(sensor *sensors, int *nrSensors) {
    for (int i = 0; i < *nrSensors; i++) {
        if (sensors[i].sensor_type == 0) { // checking for the type in order to verify the right values
            tire_sensor *tire = (tire_sensor *)sensors[i].sensor_data;
            if (tire->pressure < 19 || tire->pressure > 28) {
                freeSensor(sensors, nrSensors, &i);
            } else if (tire->temperature < 0 || tire->temperature > 120) {
                freeSensor(sensors, nrSensors, &i);
            } else if (tire->wear_level < 0 || tire->wear_level > 100) {
                freeSensor(sensors, nrSensors, &i);
            }
        } else {
            power_management_unit *pmu = (power_management_unit *)sensors[i].sensor_data;
            if (pmu->voltage < 10 || pmu->voltage > 20) {
                freeSensor(sensors, nrSensors, &i);
            } else if (pmu->current < -100 || pmu->current > 100) {
                freeSensor(sensors, nrSensors, &i);
            } else if (pmu->power_consumption < 0 || pmu->power_consumption > 1000) {
                freeSensor(sensors, nrSensors, &i);
            } else if (pmu->energy_regen < 0 || pmu->energy_regen > 100) {
                freeSensor(sensors, nrSensors, &i);
            } else if (pmu->energy_storage < 0 || pmu->energy_storage > 100) {
                freeSensor(sensors, nrSensors, &i);
            }
        }
    }
}

// free all the memory allocated for the vector

void freeAll(sensor* sensors, int nrSensors) {
    for (int i = 0; i < nrSensors; i++) {
        free(sensors[i].sensor_data);
        free(sensors[i].operations_idxs);
    }
    free(sensors);
}

int main(int argc, char const *argv[]) {
    FILE *input;
    input = fopen(argv[1], "rb"); // reading binary file from argument to executable

    int nrSensors;
    fread(&nrSensors, sizeof(int), 1, input); // read no of sensors
    sensor *sensors = malloc(nrSensors * sizeof(sensor)); // get memory for the vector of sensors

    for (int i = 0; i < nrSensors; i++) {
        //get sensor type PMU/tire and then read the values
        fread(&(sensors[i].sensor_type), sizeof(int), 1, input);
        int sensorType = sensors[i].sensor_type;

        // if type is 1 read PMU and then sort the vector by
        // moving the sensor to the left until last element or PMU sensor is found,
        // else read tire sensor data

        if (sensorType == 1) {
            readPMU(sensors, i, input);
            if ((i >= 1) && (sensors[i - 1].sensor_type != 1)) {
                int index = i;
                while (sensors[index - 1].sensor_type != 1) {
                    swap(sensors, index);
                    index--;
                    if (index == 0) {
                        break;
                    }
                }
            }
        } else {
            readTire(sensors, i, input);
        }
    }

    char *command = malloc(10 * sizeof(char));
    scanf("%s", command); // read command from STDIN

    void (*operations[8])(void*);
    get_operations((void **)operations); // get operations from function

    while (strcmp(command, "exit") != 0) {
        if (strcmp(command, "clear") == 0) {
            clear(sensors, &nrSensors); // deleting sensors with wrong data
        } else {
            int index;
            scanf("%d", &index); // getting the index of a sensor to print
            if (index < 0 || index > nrSensors) { // checking if the index is within the parameters
                printf("Index not in range!\n");
            } else if (strcmp(command, "print") == 0) {
                printIndex(sensors, index); // print the sensor with from the index
            } else if (strcmp(command, "analyze") == 0) {
                for (int j = 0; j < sensors[index].nr_operations; j++) {
                    // getting the function from the function vector and apply it to the data
                    (*operations[sensors[index].operations_idxs[j]])(sensors[index].sensor_data);
                }
            }
        }
        scanf("%s", command); // read the next command
    }

    // free all the memory and close the opened files
    free(command);
    freeAll(sensors, nrSensors);
    fclose(input);

    return 0;
}