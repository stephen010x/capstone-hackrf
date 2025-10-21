
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <hackrf.h>

#include "myhackrf.h"
#include "hackrf/debug.h"


#define SAFE_LIBHACKRF_VERSION "2024.02.1 (0.9)"
typedef hackrf_device hackrf_device_t





#define fatalassert(__val, ...)





// TODO: add more user friendly errors
// perhaps an err function that determines what to print and if it is fatal or not



int open_board(hackrf_device **device);
int free_board(hackrf_device *device);
int setup_receiver_params(hackrf_device *device);



typedef struct global_state_t {} state;







int main(void) {
    int err;
    hackrf_device_t* device;

    err = open_board(&device);
    if (err) return err;

    err = setup_receiver_params(device);
    if (err) return err;

    err = free_board(device);
    if (err) return err;

    return 0;
}




// initilizes library and opens board
int open_board(hackrf_device **device) {
    int err;
    uint16_t version, usb_version;
    //hackrf_device_list_t *devices;
    
    
    // initilize the hackrf library
    err = hackrf_init();
    assert(("hackrf failed to initilize", err == HACKRF_SUCCESS), err)
    //if (err) fatal(err);

    // warn user if a different untargeted hackrf lib version is being used
    if (strcmp(hackrf_library_version())) {
        warnf("target hackrf library version is '%s'. Instead, '%s' is being used.",
            SAFE_LIBHACKRF_VERSION, hackrf_library_version());
    }


    // open first available hackrf device
    err = hackrf_open(&device);
    assert(("hackrf device could not be opened", err == HACKRF_SUCCESS), err);


    // print out board info
    ///////////////////////////////

    // get usb api version
    err = hackrf_usb_api_version_read(device, &usb_version);
    
    printf("device %s opened\n", hackrf_board_id_name(hackrf_board_id(device)));

    printf("Firmware Version: %s (API:%x.%02x)\n", version,
        (usb_version >> 8) & 0xFF, usb_version & 0xFF);
    
    
    return 0;


    // // get list of devices
    // devices = hackrf_device_list();
    // assert((hackrf_device_list_t != NULL), HACKRF_ERROR_OTHER);
    // assert(("no hackrf devices detected", devices->devicecount > 0), HACKRF_ERROR_OTHER);


//     // print out detected devices
//     // note devices can be null
//     printf("devices detected\n");
//     for (int i = 0; i < devices->devicecount; i++) {
//     
//         int usb_index = devices->usb_device_index[i];
//         enum hackrf_usb_board_id usb_id = devices->hackrf_usb_board_id[usb_index];
//         
//         char* serial_number = devices->serial_numbers[i];
//         char* usb_id_name = hackrf_usb_board_id_name(usb_id);
// 
//         printf("\tdevice %d: usb_id=%s serial=%s\n", i, usb_id_name, serial_number);
//     }
// 
// 
// 
//     // open first hackrf device in the list
//     // TODO: alternatively you could just call hackrf_open(), which does that anyway
//     // TODO: you could also open it by serial using hackrf_open_by_serial()
//     err = hackrf_device_list_open(devices, 0, &device);
//     assert(("failed to open device", err));
//     //if (err) fatal(err);
}





int free_board(hackrf_device *device) {
    // close opened device
    err = hackrf_close(device);
    assert(err == HACKRF_SUCCESS, err);

    // // free device list
    // hackrf_device_list_free(devices);

    // safely exit hackrf
    int err = hackrf_exit(void);
    assert(err == HACKRF_SUCCESS, err);

    return 0;
}





int setup_receiver_params(hackrf_device *device) {
    uint32_t bandwidth_hz = 10e6;
    uint32_t real_bandwidth_hz;

    // calculate actual bandwidth we will be using
    // will be forced to one of these: 1.75, 2.5, 3.5, 5, 5.5, 6, 7, 8, 
    //      9, 10, 12, 14, 15, 20, 24, 28MHz
    real_bandwidth_hz = hackrf_compute_baseband_filter_bw(bandwidth_hz);

    printf("bandwidth of %uHz selected based on %uHz"\n, 
        real_bandwidth_hz, bandwidth_hz);


    


    // set baseband sampling bandwidth
    // reset after sample rate is set, so call this after sample rate
    hackrf_set_baseband_filter_bandwidth(device, real_bandwidth_hz);

}








/*

hackrf_exit
hackrf_library_version
hackrf_library_release
hackrf_device_list
hackrf_device_list_open
hackrf_device_list_free
hackrf_open
hackrf_open_by_serial
hackrf_close
hackrf_start_rx
hackrf_stop_rx
hackrf_start_tx
hackrf_set_tx_block_complete_callback
hackrf_enable_tx_flush
hackrf_stop_tx
hackrf_get_m0_state
hackrf_set_tx_underrun_limit
hackrf_set_rx_overrun_limit
hackrf_is_streaming
hackrf_max2837_read
hackrf_max2837_write
hackrf_si5351c_read
hackrf_si5351c_write
hackrf_set_baseband_filter_bandwidth
hackrf_rffc5071_read
hackrf_rffc5071_write
hackrf_spiflash_erase
hackrf_spiflash_write
hackrf_spiflash_read
hackrf_spiflash_status
hackrf_spiflash_clear_status
hackrf_cpld_write
hackrf_board_id_read
hackrf_version_string_read
hackrf_usb_api_version_read
hackrf_set_freq
hackrf_set_freq_explicit
hackrf_set_sample_rate_manual
hackrf_set_sample_rate
hackrf_set_amp_enable
hackrf_board_partid_serialno_read
hackrf_set_lna_gain
hackrf_set_vga_gain
hackrf_set_txvga_gain
hackrf_set_antenna_enable
hackrf_error_name
hackrf_board_id_name
hackrf_board_id_platform
hackrf_usb_board_id_name
hackrf_filter_path_name
hackrf_compute_baseband_filter_bw_round_down_lt
hackrf_compute_baseband_filter_bw
hackrf_set_hw_sync_mode
hackrf_get_operacake_boards
hackrf_set_operacake_mode
hackrf_get_operacake_mode
hackrf_set_operacake_ports
hackrf_set_operacake_dwell_times
hackrf_set_operacake_freq_ranges
hackrf_reset
hackrf_set_operacake_ranges
hackrf_set_clkout_enable
hackrf_get_clkin_status
hackrf_operacake_gpio_test
hackrf_cpld_checksum
hackrf_set_ui_enable
hackrf_start_rx_sweep
hackrf_get_transfer_buffer_size
hackrf_get_transfer_queue_depth
hackrf_board_rev_read
hackrf_board_rev_name
hackrf_supported_platform_read
hackrf_set_leds
hackrf_set_user_bias_t_opts






typedef struct {
	hackrf_device* device;
	uint8_t* buffer;
	int buffer_length;
	int valid_length;
	void* rx_ctx;
	void* tx_ctx;
} hackrf_transfer;

typedef struct {
	uint32_t part_id[2];
	uint32_t serial_no[4];
} read_partid_serialno_t;

typedef struct {
	uint32_t dwell;
	uint8_t port;
} hackrf_operacake_dwell_time;

typedef struct {
	uint16_t freq_min;
	uint16_t freq_max;
	uint8_t port;
} hackrf_operacake_freq_range;

typedef struct {
	bool do_update;
	bool change_on_mode_entry;
	bool enabled;
} hackrf_bool_user_settting;

typedef struct {
	hackrf_bool_user_settting tx;
	hackrf_bool_user_settting rx;
	hackrf_bool_user_settting off;
} hackrf_bias_t_user_settting_req;

typedef struct {
	uint16_t requested_mode;
	uint16_t request_flag;
	uint32_t active_mode;
	uint32_t m0_count;
	uint32_t m4_count;
	uint32_t num_shortfalls;
	uint32_t longest_shortfall;
	uint32_t shortfall_limit;
	uint32_t threshold;
	uint32_t next_mode;
	uint32_t error;
} hackrf_m0_state;


struct hackrf_device_list {
	char** serial_numbers;
	enum hackrf_usb_board_id* usb_board_ids;
	int* usb_device_index;
	int devicecount;
	void** usb_devices;
	int usb_devicecount;
};

*/
