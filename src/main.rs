// getdata library
use getdata::*;
mod getdata;

// CString
use std::ffi::CString;
use std::ffi::CStr;

fn main() {
    println!("Hello, world!");

    let dirfile = CString::new("/data/flights/superbit_2023/timestreams/master_2023-05-03-07-24-30")
        .expect("CString::new failed");
    let dirfile_ptr = dirfile.as_ptr();

    let dirfile_open = unsafe { gd_open(dirfile_ptr, GD_RDONLY) };
    println!("dirfile_open: {:?}", dirfile_open);

    // Find the number of fields in the dirfile
    let nfields = unsafe { gd_nfields(dirfile_open) };
    println!("nfields: {:?}", nfields);

    // Get the field code for "period_fsc1"
    let lon_code = CString::new("lon").expect("CString::new failed");
    let lon_code_ptr = lon_code.as_ptr();

    // Get the number of frames in the field "lon"
    let lon_frames = unsafe { gd_nframes(dirfile_open) };

    println!("Total frames: {:?}", lon_frames);

    // Get samples per frame
    let samples_per_frame = unsafe { gd_spf(dirfile_open, lon_code_ptr) };

    println!("Samples per frame for lon: {:?}", samples_per_frame);


    // Total number of samples
    let total_samples: usize = lon_frames as usize * samples_per_frame as usize;

    // Print
    println!("Total samples: {:?}", total_samples);

    // Allocate space for Lon data
    let mut lon_data: Vec<f64> = vec![0.0; total_samples];

    // Get all the data of the field "lon" and store it in the vector
    let lon_data_size = unsafe {
        gd_getdata(
            dirfile_open,
            lon_code_ptr,
            0,
            0,
            lon_frames as usize,
            samples_per_frame as usize,
            gd_type_t_GD_FLOAT64, // Use GD_FLOAT64 to match the f64 data type
            lon_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
        )
    };

    // Print the first 200 elements of the vector (or as many as available)
    let to_print = lon_data.iter().take(200);
    for (i, value) in to_print.enumerate() {
        println!("lon_data[{}]: {:?}", i, value);
    }

    // Print size of lon_data
    println!("lon_data_size: {:?}", lon_data_size);


    // Also get the list of fields
    let field_list = unsafe { gd_field_list(dirfile_open) };

    // Check if the field_list is not null
    if !field_list.is_null() {
        let mut index = 0;

        // Iterate through the list of fields
        loop {
            // Get the pointer to the current field
            let field_ptr = unsafe { *field_list.add(index) };
            if field_ptr.is_null() {
                break; // End of the list
            }

            // Convert the C string to a Rust string
            let field_name = unsafe { CStr::from_ptr(field_ptr) };
            //match field_name.to_str() {
               // Ok(name) => println!("Field {}: {}", index, name),
               // Err(e) => eprintln!("Failed to convert field name: {}", e),
           // }

            index += 1;
        }
    } else {
        println!("No fields found in dirfile.");
    }

}
