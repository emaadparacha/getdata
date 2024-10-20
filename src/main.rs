// getdata library
mod getdata;
use getdata::DirFile;
mod getdata_bindings; // Declare the bindings module

fn main() {
    // New Code

    let dirfile = DirFile::new("/data/flights/superbit_2023/timestreams/master_2023-05-03-07-24-30");

    // Get the number of fields in the dirfile
    let nfields = dirfile.nfields();
    println!("nfields: {:?}", nfields);

    // Get the number of frames in the dirfile
    let total_frames = dirfile.nframes();
    println!("Total frames: {:?}", total_frames);

    // Get samples per frame for "lon"
    let samples_per_frame = dirfile.spf("lon");
    println!("Samples per frame for lon: {:?}", samples_per_frame);

    // Get the type of the field "lon"
    let lon_type = dirfile.field_type("lon");
    println!("lon_type: {:?}", lon_type);

    // Get the data of the field "lon"
    let lon_data = dirfile.get_data("lon");

    // Match on the FieldData type to get the underlying data
    match lon_data[0] {  // Access the first element in the vector
        FieldData::Uint8(data) => {
            println!("lon_data size: {:?}", data.len());
            // Print the last 15 elements of the lon_data vector
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Int8(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Uint16(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Int16(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Uint32(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Int32(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Uint64(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Int64(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Float32(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::Float64(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        FieldData::String(data) => {
            println!("lon_data size: {:?}", data.len());
            let to_print = data.iter().skip(data.len().saturating_sub(15));
            for (i, value) in to_print.enumerate() {
                println!("lon_data[{}]: {:?}", i + data.len() - 15, value);
            }
        }
        _ => {
            println!("Unexpected data type for 'lon'");
        }
    }

    // Old Code
    // let dirfile = CString::new("/data/flights/superbit_2023/timestreams/master_2023-05-03-07-24-30")
    //     .expect("CString::new failed");
    // let dirfile_ptr = dirfile.as_ptr();

    // let dirfile_open = unsafe { gd_open(dirfile_ptr, GD_RDONLY) };
    // println!("dirfile_open: {:?}", dirfile_open);

    // // Find the number of fields in the dirfile
    // let nfields = unsafe { gd_nfields(dirfile_open) };
    // println!("nfields: {:?}", nfields);

    // // Get the field code for "period_fsc1"
    // let lon_code = CString::new("lon").expect("CString::new failed");
    // let lon_code_ptr = lon_code.as_ptr();

    // // Get the number of frames in the field "lon"
    // let lon_frames = unsafe { gd_nframes(dirfile_open) };

    // println!("Total frames: {:?}", lon_frames);

    // // Get samples per frame
    // let samples_per_frame = unsafe { gd_spf(dirfile_open, lon_code_ptr) };

    // println!("Samples per frame for lon: {:?}", samples_per_frame);

    // // Total number of samples
    // let total_samples: usize = lon_frames as usize * samples_per_frame as usize;

    // // Print
    // println!("Total samples: {:?}", total_samples);

    // // Allocate space for Lon data
    // let mut lon_data: Vec<f64> = vec![0.0; total_samples];

    // // Get all the data of the field "lon" and store it in the vector
    // let lon_data_size = unsafe {
    //     gd_getdata(
    //         dirfile_open,
    //         lon_code_ptr,
    //         0,
    //         0,
    //         lon_frames as usize,
    //         samples_per_frame as usize,
    //         gd_type_t_GD_FLOAT64, // Use GD_FLOAT64 to match the f64 data type
    //         lon_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
    //     )
    // };

    // // Print the first 15 elements of the vector (or as many as available)
    // let to_print = lon_data.iter().take(15);
    // for (i, value) in to_print.enumerate() {
    //     println!("lon_data[{}]: {:?}", i, value);
    // }

    // // Also print the middle 15 elements
    // let to_print = lon_data.iter().skip(lon_data.len() / 2).take(15);
    // for (i, value) in to_print.enumerate() {
    //     println!("lon_data[{}]: {:?}", i + lon_data.len() / 2, value);
    // }

    // // Print the last 15 elements
    // let to_print = lon_data.iter().skip(lon_data.len() - 15);
    // for (i, value) in to_print.enumerate() {
    //     println!("lon_data[{}]: {:?}", i + lon_data.len() - 15, value);
    // }

    // // Print the last 200 elements of "lat" data
    // let lat_code = CString::new("lat").expect("CString::new failed");
    // let lat_code_ptr = lat_code.as_ptr();

    // // Get the number of frames in the field "lat"
    // let lat_frames = unsafe { gd_nframes(dirfile_open) };

    // println!("Total frames: {:?}", lat_frames);

    // // Get samples per frame
    // let samples_per_frame = unsafe { gd_spf(dirfile_open, lat_code_ptr) };

    // println!("Samples per frame for lat: {:?}", samples_per_frame);

    // // Total number of samples
    // let total_samples: usize = lat_frames as usize * samples_per_frame as usize;

    // // Print
    // println!("Total samples: {:?}", total_samples);

    // // Allocate space for Lon data
    // let mut lat_data: Vec<f64> = vec![0.0; total_samples];

    // // Get all the data of the field "lat" and store it in the vector
    // let lat_data_size = unsafe {
    //     gd_getdata(
    //         dirfile_open,
    //         lat_code_ptr,
    //         0,
    //         0,
    //         lat_frames as usize,
    //         samples_per_frame as usize,
    //         gd_type_t_GD_FLOAT64, // Use GD_FLOAT64 to match the f64 data type
    //         lat_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
    //     )
    // };

    // // Print the first 15 elements of the vector (or as many as available)
    // let to_print = lat_data.iter().take(15);
    // for (i, value) in to_print.enumerate() {
    //     println!("lat_data[{}]: {:?}", i, value);
    // }

    // // Also print the middle 15 elements
    // let to_print = lat_data.iter().skip(lat_data.len() / 2).take(15);
    // for (i, value) in to_print.enumerate() {
    //     println!("lat_data[{}]: {:?}", i + lat_data.len() / 2, value);
    // }

    // // Print the last 15 elements
    // let to_print = lat_data.iter().skip(lat_data.len() - 15);
    // for (i, value) in to_print.enumerate() {
    //     println!("lat_data[{}]: {:?}", i + lat_data.len() - 15, value);
    // }

    // // Print size of lon_data
    // println!("lon_data_size: {:?}", lon_data_size);

    // // Get the type of the field "lon"
    // let lon_type = unsafe { gd_native_type(dirfile_open, lon_code_ptr) };

    // // Print the type of the field "lon"
    // println!("lon_type: {:?}", lon_type);

    // // Print the value of gd_type_t_GD_FLOAT64
    // println!("gd_type_t_GD_FLOAT64: {:?}", gd_type_t_GD_FLOAT64);


    // // Also get the list of fields
    // let field_list = unsafe { gd_field_list(dirfile_open) };

    // // Check if the field_list is not null
    // if !field_list.is_null() {
    //     let mut index = 0;

    //     // Iterate through the list of fields
    //     loop {
    //         // Get the pointer to the current field
    //         let field_ptr = unsafe { *field_list.add(index) };
    //         if field_ptr.is_null() {
    //             break; // End of the list
    //         }

    //         // Convert the C string to a Rust string
    //         let field_name = unsafe { CStr::from_ptr(field_ptr) };
    //         //match field_name.to_str() {
    //            // Ok(name) => println!("Field {}: {}", index, name),
    //            // Err(e) => eprintln!("Failed to convert field name: {}", e),
    //        // }

    //         index += 1;
    //     }
    // } else {
    //     println!("No fields found in dirfile.");
    // }

}
