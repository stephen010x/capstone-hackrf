
#include <stdio.h>
#include <string.h>

#include <hackrf.h>

#include "myhackrf.h"
#include "hackrf/debug.h"


#define SAFE_LIBHACKRF_VERSION "2024.02.1 (0.9)"
typedef hackrf_device hackrf_device_t





#define fatalassert(__val, ...)





// TODO: add more user friendly errors
// perhaps an err function that determines what to print and if it is fatal or not




typedef struct global_state_t {} state;





int main(void) {
    int err;
    hackrf_device_list_t *devices;
    hackrf_device_t* device;
    


    // initilize the hackrf library
    err = hackrf_init();
    fassert(("hackrf failed to initilize", err))
    //if (err) fatal(err);

    // warn user if a different untargeted hackrf lib version is being used
    if (strcmp(hackrf_library_version())) {
        warnf("target hackrf library version is '%s'. Instead, '%s' is being used.",
            SAFE_LIBHACKRF_VERSION, hackrf_library_version());
    }


    // get list of devices
    devices = hackrf_device_list();
    fassert(hackrf_device_list_t != NULL);
    assert(("no hackrf devices detected", devices->devicecount > 0));


    // print out detected devices
    // note devices can be null
    printf("devices detected\n");
    for (int i = 0; i < devices->devicecount; i++) {
    
        int usb_index = devices->usb_device_index[i];
        enum hackrf_usb_board_id usb_id = devices->hackrf_usb_board_id[usb_index];
        
        char* serial_number = devices->serial_numbers[i];
        char* usb_id_name = hackrf_usb_board_id_name(usb_id);

        printf("\tdevice %d: usb_id=%s serial=%s\n", i, usb_id_name, serial_number);
    }



    // open first hackrf device in the list
    // TODO: alternatively you could just call hackrf_open(), which does that anyway
    // TODO: you could also open it by serial using hackrf_open_by_serial()
    err = hackrf_device_list_open(devices, 0, &device);
    assert(("failed to open device", err));
    //if (err) fatal(err);






    // close opened device
    err = hackrf_close(hackrf_device);
    if (err) fatal(err);

    // free device list
    hackrf_device_list_free(devices);

    // safely exit hackrf
    int err = hackrf_exit(void);
    if (err) fatal(err);

    return 0;
}




int setup_board(void) {
    
}


int free_board(void) {
    
}



int setup_receiver_params() {

}



